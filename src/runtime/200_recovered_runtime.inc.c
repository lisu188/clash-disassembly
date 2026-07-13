/* Recovered CRT, C++ support, streams, threading, and library runtime.
 * Original function-marker range: 0x004D0560..0x004E7F70.
 * Included by clash95.c; not a standalone translation unit. */

//----- (004D0560) --------------------------------------------------------
int  ObjectsCompiler_WriteClassPointerArray(
        const char *a1,
        const char *a2,
        int a3,
        int a4,
        int a5,
        int *a6)
{
  int result; // eax
  int v7; // ecx
  int v8; // edi
  int v9; // esi
  int v10; // ebp
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  int v14; // ecx
  char v15; // [esp+0h] [ebp-14h]
  int v16; // [esp+0h] [ebp-14h]

  v15 = a4;
  result = Rules_ConstructCodeFileOpen(
             0,
             a1,
             a3,
             a2,
             a6,
             1,
             a4,
             (char)aDefclass_7,
             *(const char **)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 44),
             0,
             0);
  v8 = result;
  if ( result )
  {
    v9 = 0;
    v10 = 0;
    while ( v9 < (unsigned __int16)g_ClipsDefclassIdCount )
    {
      if ( v9 > 0 )
        Output_WriteFormatted(v7, (unsigned __int16)g_ClipsDefclassIdCount, v8, (int)asc_50C57C, v15);
      v10 += 4;
      ++v9;
      ObjectsCompiler_WriteDefclassPointerRef(v8, *(_DWORD *)(g_ClipsDefclassIdTable + v10 - 4), a5);
    }
    Output_WriteFormatted(v7, (unsigned __int16)g_ClipsDefclassIdCount, v8, (int)asc_50C580, v15);
    Output_WriteFormatted(
      v11,
      *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 48),
      v8,
      (int)aUnsignedSDU,
      *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 48));
    Output_WriteFormatted(v13, v12, v16, (int)aExternUnsign_0, *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 48));
    fclose_(v14);
    return 1;
  }
  return result;
}
// 4D05BB: variable 'v7' is possibly undefined
// 4D05BB: variable 'v15' is possibly undefined
// 4D0619: variable 'v11' is possibly undefined
// 4D0638: variable 'v13' is possibly undefined
// 4D0638: variable 'v12' is possibly undefined
// 4D0638: variable 'v16' is possibly undefined
// 4D0642: variable 'v14' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51AD64: using guessed type int dword_51AD64;
// 51AD6C: using guessed type __int16 word_51AD6C;
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004D0660) --------------------------------------------------------
signed int  ObjectsCompiler_WriteClassHashTable(
        const char *a1,
        const char *a2,
        int a3,
        int a4,
        int a5,
        int *a6)
{
  int v6; // esi
  int v7; // ecx
  int v8; // edx
  int v10; // [esp+0h] [ebp-14h] BYREF
  int v11[4]; // [esp+4h] [ebp-10h] BYREF

  v11[0] = 1;
  v6 = Rules_ConstructCodeFileOpen(
         0,
         a1,
         a3,
         a2,
         a6,
         1,
         a4,
         (char)aDefclass_7,
         *(const char **)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 40),
         0,
         0);
  if ( !v6 )
    return 0;
  v10 = 0;
  while ( 1 )
  {
    ObjectsCompiler_WriteDefclassPointerRef(v6, *(_DWORD *)(g_DefclassHashTable + 4 * v10), a5);
    v8 = v10 + 1;
    v10 = v8;
    if ( v8 >= 167 )
      break;
    if ( v8 > 0 )
      Output_WriteFormatted(v7, v8, v6, (int)asc_50C57C, v10);
  }
  Rules_ConstructCodeFileClose(v6, &v10, v8, v11, 0, 0);
  return 1;
}
// 4D06A4: control flows out of bounds to 4D05E2
// 4D06DE: variable 'v7' is possibly undefined
// 51AD68: using guessed type int dword_51AD68;
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004D0710) --------------------------------------------------------
void  ObjectsCompiler_WriteSlotNameHashTable(const char *a1, const char *a2, int a3, int a4, int a5, int *a6)
{
  int v6; // esi
  int v7; // ecx
  int v8; // edx
  int v9; // [esp+0h] [ebp-14h]
  int v10[4]; // [esp+4h] [ebp-10h] BYREF

  v10[0] = 1;
  v6 = Rules_ConstructCodeFileOpen(
         0,
         a1,
         a3,
         a2,
         a6,
         1,
         a4,
         (char)aSlot_name,
         *(const char **)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 36),
         0,
         0);
  if ( !v6 )
    return;
  v9 = 0;
  while ( 1 )
  {
    ObjectsCompiler_WriteSlotNamePointerRef(v6, *(_DWORD *)(g_Defclass_SlotNameHashTablePtr + 4 * v9), a5);
    v8 = v9 + 1;
    v9 = v8;
    if ( v8 >= 167 )
      break;
    if ( v8 > 0 )
      Output_WriteFormatted(v7, v8, v6, (int)asc_50C57C, v8);
  }
  Rules_ConstructCodeFileClose(v6, &v9, v8, v10, 0, 0);
}
// 4D0754: control flows out of bounds to 4D05E2
// 4D0782: control flows out of bounds to 4D06E8
// 4D076B: variable 'v9' is possibly undefined
// 4D0792: variable 'v7' is possibly undefined
// 51AD70: using guessed type int dword_51AD70;
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004D07A0) --------------------------------------------------------
signed int  ObjectsCompiler_WriteSlotNameRecords(
        const char *a1,
        const char *a2,
        int a3,
        int a4,
        int a5,
        int *a6)
{
  int v7; // eax
  int *v8; // edi
  signed int result; // eax
  int v10; // ecx
  int v11; // esi
  int v12; // ecx
  int v13; // edx
  int v14; // ecx
  int v15; // ecx
  int v16; // edx
  int v17; // ecx
  int v18; // edx
  int v19; // ecx
  int v20; // [esp+0h] [ebp-28h] BYREF
  int v21; // [esp+4h] [ebp-24h] BYREF
  int v22; // [esp+8h] [ebp-20h]
  int v23; // [esp+Ch] [ebp-1Ch]
  const char *v24; // [esp+10h] [ebp-18h]
  int v25; // [esp+14h] [ebp-14h]
  const char *v26; // [esp+18h] [ebp-10h]

  v26 = a1;
  v24 = a2;
  v25 = a4;
  v7 = 0;
  v20 = 0;
  v21 = 1;
  v23 = 0;
  v22 = 0;
  while ( 1 )
  {
    v8 = *(int **)(v22 + g_Defclass_SlotNameHashTablePtr);
    if ( v8 )
      break;
LABEL_5:
    v22 += 4;
    if ( (unsigned int)++v23 >= 0xA7 )
    {
      if ( v7 )
        Rules_ConstructCodeFileClose(v7, &v20, v20, &v21, 0, 0);
      return 1;
    }
  }
  while ( 1 )
  {
    result = Rules_ConstructCodeFileOpen(
               v7,
               v26,
               a3,
               v24,
               a6,
               v21,
               v25,
               (char)aSlot_name_0,
               *(const char **)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 32),
               0,
               0);
    v11 = result;
    if ( !result )
      return result;
    Output_WriteFormatted(v10, *v8, result, (int)aU1U, *v8);
    Compiler_WriteSymbolReference(v11, v8[3], v12);
    Output_WriteFormatted(v14, v13, v11, (int)asc_50C5DC, v20);
    Compiler_WriteSymbolReference(v11, v8[4], v15);
    Output_WriteFormatted(v17, v16, v11, (int)asc_50C5DC, v20);
    ObjectsCompiler_WriteSlotNamePointerRef(v11, v8[5], a5);
    Output_WriteFormatted(v19, v18, v11, (int)a0l, v20++);
    v7 = Rules_ConstructCodeFileClose(v11, &v20, a5, &v21, 0, 0);
    v8 = (int *)v8[5];
    if ( !v8 )
      goto LABEL_5;
  }
}
// 4D082B: variable 'v10' is possibly undefined
// 4D0838: variable 'v12' is possibly undefined
// 4D0843: variable 'v14' is possibly undefined
// 4D0843: variable 'v13' is possibly undefined
// 4D0850: variable 'v15' is possibly undefined
// 4D085D: variable 'v17' is possibly undefined
// 4D085D: variable 'v16' is possibly undefined
// 4D0879: variable 'v19' is possibly undefined
// 4D0879: variable 'v18' is possibly undefined
// 51AD70: using guessed type int dword_51AD70;
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004D0900) --------------------------------------------------------
int  ObjectsCompiler_CloseConstructFileGroup(int *a1, _DWORD *a2, int a3, int a4)
{
  _DWORD *v6; // edi
  int v7; // eax
  int result; // eax
  int v9; // [esp+0h] [ebp-1Ch] BYREF
  int v10; // [esp+4h] [ebp-18h] BYREF
  _DWORD *v11; // [esp+8h] [ebp-14h]
  int v12; // [esp+Ch] [ebp-10h]

  v9 = a3;
  v6 = a2;
  v12 = a4;
  v10 = 0;
  v11 = a2 + 8;
  do
  {
    v9 = a3;
    v7 = *a1++;
    *(a1 - 1) = Rules_ConstructCodeFileClose(v7, &v9, a3, &v10, v6, v12);
    result = v12 + 12;
    ++v6;
    v12 += 12;
  }
  while ( v6 != v11 );
  return result;
}

//----- (004D0960) --------------------------------------------------------
int  ObjectsCompiler_WriteModuleRecord(int a1, int a2, int a3)
{
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  char v9; // [esp+0h] [ebp-Ch]
  char v10; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(a3, a2, a1, (int)asc_50C5E8, v9);
  Rules_WriteConstructModuleItemHeaderToCode(a1, v4, v5, g_CLIPS_DefclassModuleItemIndex, *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 4));
  return Output_WriteFormatted(v7, v6, a1, (int)asc_50C5EC, v10);
}
// 4D096B: variable 'v9' is possibly undefined
// 4D0988: variable 'v4' is possibly undefined
// 4D0988: variable 'v5' is possibly undefined
// 4D0993: variable 'v7' is possibly undefined
// 4D0993: variable 'v6' is possibly undefined
// 4D0993: variable 'v10' is possibly undefined
// 54E6BC: using guessed type int dword_54E6BC;
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004D09A0) --------------------------------------------------------
int  ObjectsCompiler_WriteClassRecord(
        int a1,
        int a2,
        int a3,
        char a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        int a11,
        int a12,
        int a13,
        int a14,
        int a15,
        int a16,
        int a17)
{
  int v19; // ecx
  int v20; // ecx
  int v21; // edx
  int v22; // edx
  unsigned __int16 v23; // bx
  int v24; // ecx
  int v25; // edx
  int v26; // edx
  int v27; // ecx
  int v28; // edx
  int v29; // ecx
  int v30; // edx
  int v31; // ecx
  int v32; // edx
  int v33; // ecx
  int v34; // edx
  int v35; // ecx
  int v36; // edx
  int v37; // ecx
  int v38; // edx
  int v39; // ecx
  int v40; // ecx
  int v41; // edx
  int v42; // ecx
  signed int v44; // [esp+0h] [ebp-10h]
  char v45; // [esp+0h] [ebp-10h]

  Output_WriteFormatted(a3, a2, a1, (int)asc_50C5E8, a4);
  Rules_WriteConstructHeaderToCode(a1, a3, v44, a5, **(_DWORD **)(g_ClipsConstructCompilerData + 20), *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 4));
  Output_WriteFormatted(v19, *(_DWORD *)(a3 + 20) << 30 >> 31, a1, (int)a1UUU00U0U, (*(_DWORD *)(a3 + 20) & 2) != 0);
  LOWORD(v21) = *(_WORD *)(a3 + 34);
  if ( (_WORD)v21 )
    Output_WriteFormatted(a7, *(unsigned __int16 *)(a3 + 34), a1, (int)aUSD_DD, *(_WORD *)(a3 + 34));
  else
    Output_WriteFormatted(v20, v21, a1, (int)a0Null, v44);
  HIWORD(v22) = 0;
  v23 = *(_WORD *)(a3 + 40);
  if ( v23 )
  {
    Output_WriteFormatted(*(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 8), v23, a1, (int)aUSD_DD, v23);
  }
  else
  {
    LOWORD(v22) = *(_WORD *)(a3 + 34);
    Output_WriteFormatted((unsigned __int16)v22 + a7, v22, a1, (int)a0Null, v44);
  }
  HIWORD(v25) = 0;
  LOWORD(v24) = *(_WORD *)(a3 + 46);
  if ( (_WORD)v24 )
  {
    Output_WriteFormatted(
      *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 8),
      *(unsigned __int16 *)(a3 + 46),
      a1,
      (int)aUSD_DD,
      *(_WORD *)(a3 + 46));
  }
  else
  {
    LOWORD(v25) = *(_WORD *)(a3 + 40);
    Output_WriteFormatted(v24, v25, a1, (int)a0Null_0, v44);
  }
  if ( *(_DWORD *)(a3 + 52) )
    Output_WriteFormatted(
      *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 12),
      *(_DWORD *)(g_ClipsConstructCompilerData + 20),
      a1,
      (int)aSD_DD_8,
      *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 12));
  else
    Output_WriteFormatted(v27, v26, a1, (int)aNull_27, v44);
  if ( *(_DWORD *)(a3 + 56) )
    Output_WriteFormatted(
      *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 16),
      *(_DWORD *)(g_ClipsConstructCompilerData + 20),
      a1,
      (int)aSD_DD_8,
      *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 16));
  else
    Output_WriteFormatted(v29, v28, a1, (int)aNull_27, v44);
  if ( *(_DWORD *)(a3 + 60) )
    Output_WriteFormatted(
      *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 20),
      *(_DWORD *)(g_ClipsConstructCompilerData + 20),
      a1,
      (int)aSD_DD_8,
      *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 20));
  else
    Output_WriteFormatted(v31, v30, a1, (int)aNull_27, v44);
  Output_WriteFormatted(*(_DWORD *)(a3 + 64), *(_DWORD *)(a3 + 68), a1, (int)aUUUUNullNull, *(_DWORD *)(a3 + 64));
  if ( *(_DWORD *)(a3 + 88) )
    Output_WriteFormatted(
      *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 24),
      *(_DWORD *)(g_ClipsConstructCompilerData + 20),
      a1,
      (int)aSD_DD_8,
      *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 24));
  else
    Output_WriteFormatted(v33, v32, a1, (int)aNull_27, v44);
  if ( *(_DWORD *)(a3 + 92) )
    Output_WriteFormatted(
      *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 28),
      *(_DWORD *)(g_ClipsConstructCompilerData + 20),
      a1,
      (int)aSD_DD_8,
      *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 28));
  else
    Output_WriteFormatted(v35, v34, a1, (int)aNull_27, v44);
  Output_WriteFormatted(v37, v36, a1, (int)aU_0, *(_DWORD *)(a3 + 96));
  ObjectsCompiler_WriteDefclassPointerRef(a1, *(_DWORD *)(a3 + 100), v44);
  Output_WriteFormatted(v39, v38, a1, (int)asc_50C5DC, v44);
  Compiler_WriteBitMapReference(a1, *(_DWORD *)(a3 + 104), v40);
  return Output_WriteFormatted(v42, v41, a1, (int)asc_50C67C, v45);
}
// 4D09DC: variable 'v44' is possibly undefined
// 4D0A10: variable 'v19' is possibly undefined
// 4D0A2B: variable 'v20' is possibly undefined
// 4D0A2B: variable 'v21' is possibly undefined
// 4D0BD9: variable 'v37' is possibly undefined
// 4D0BD9: variable 'v36' is possibly undefined
// 4D0BF4: variable 'v39' is possibly undefined
// 4D0BF4: variable 'v38' is possibly undefined
// 4D0C01: variable 'v40' is possibly undefined
// 4D0C0C: variable 'v42' is possibly undefined
// 4D0C0C: variable 'v41' is possibly undefined
// 4D0C0C: variable 'v45' is possibly undefined
// 4D0C68: variable 'v24' is possibly undefined
// 4D0C7B: variable 'v27' is possibly undefined
// 4D0C7B: variable 'v26' is possibly undefined
// 4D0C8E: variable 'v29' is possibly undefined
// 4D0C8E: variable 'v28' is possibly undefined
// 4D0CA1: variable 'v31' is possibly undefined
// 4D0CA1: variable 'v30' is possibly undefined
// 4D0CB4: variable 'v33' is possibly undefined
// 4D0CB4: variable 'v32' is possibly undefined
// 4D0CC7: variable 'v35' is possibly undefined
// 4D0CC7: variable 'v34' is possibly undefined
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004D0CE0) --------------------------------------------------------
int  ObjectsCompiler_WriteClassLinkPointerArray(
        int *a1,
        const char *a2,
        int a3,
        const char *a4,
        int a5,
        int *a6,
        int a7,
        int a8,
        int *a9,
        int *a10,
        int *a11,
        const char **a12)
{
  int result; // eax
  int v14; // ecx
  int v15; // edx
  int v16; // [esp+0h] [ebp-2Ch]
  int i; // [esp+4h] [ebp-28h]
  int v18; // [esp+8h] [ebp-24h]
  int v19; // [esp+Ch] [ebp-20h]
  unsigned int v20; // [esp+10h] [ebp-1Ch]
  unsigned int v21; // [esp+14h] [ebp-18h]
  unsigned int v22; // [esp+18h] [ebp-14h]
  int v23; // [esp+1Ch] [ebp-10h]

  v23 = 0;
  v16 = *(unsigned __int16 *)(a8 + 40) + *(unsigned __int16 *)(a8 + 34) + *(unsigned __int16 *)(a8 + 46);
  if ( !v16 )
    return 1;
  result = Rules_ConstructCodeFileOpen(
             *a1,
             a2,
             a3,
             a4,
             a6,
             *a9,
             a5,
             (char)aDefclass_7,
             *(const char **)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 8),
             *a11,
             a12);
  *a1 = result;
  if ( result )
  {
    v14 = 0;
    v20 = 0;
    for ( i = 0; ; i += 4 )
    {
      v15 = v20;
      if ( *(unsigned __int16 *)(a8 + 34) <= v20 )
        break;
      if ( v23 )
        Output_WriteFormatted(v14, *a1, *a1, (int)asc_50C5DC, v16);
      ObjectsCompiler_WriteDefclassPointerRef(*a1, *(_DWORD *)(i + *(_DWORD *)(a8 + 36)), a7);
      v23 = 1;
      ++v20;
    }
    v22 = 0;
    v18 = 0;
    while ( *(unsigned __int16 *)(a8 + 40) > v22 )
    {
      if ( v23 )
        Output_WriteFormatted(*a1, v15, *a1, (int)asc_50C5DC, v16);
      ObjectsCompiler_WriteDefclassPointerRef(*a1, *(_DWORD *)(v18 + *(_DWORD *)(a8 + 42)), a7);
      v23 = 1;
      v15 = v18 + 4;
      v18 += 4;
      ++v22;
    }
    v21 = 0;
    v19 = 0;
    while ( *(unsigned __int16 *)(a8 + 46) > v21 )
    {
      if ( v23 )
        Output_WriteFormatted(*a1, v15, *a1, (int)asc_50C5DC, v16);
      ObjectsCompiler_WriteDefclassPointerRef(*a1, *(_DWORD *)(v19 + *(_DWORD *)(a8 + 48)), a7);
      v23 = 1;
      v15 = v19 + 4;
      v19 += 4;
      ++v21;
    }
    *a10 += v16;
    *a1 = Rules_ConstructCodeFileClose(*a1, a10, a7, a9, a11, (int)a12);
    return 1;
  }
  return result;
}
// 4D0E9F: variable 'v16' is possibly undefined
// 4D0E39: variable 'v14' is possibly undefined
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004D0EF0) --------------------------------------------------------
int  ObjectsCompiler_WriteSlotDescArray(
        int *a1,
        const char *a2,
        DWORD a3,
        const char *a4,
        int a5,
        int *a6,
        int a7,
        int a8,
        int *a9,
        int *a10,
        int *a11,
        const char **a12)
{
  int result; // eax
  int v15; // edx
  int v16; // ecx
  int v17; // esi
  int v18; // ecx
  int v19; // edx
  int v20; // ecx
  int v21; // edx
  int v22; // ecx
  int v23; // ecx
  int v24; // edx
  int v25; // edx
  int v26; // ecx
  int v27; // edx
  int v28; // ecx
  __int16 *v29; // eax
  int v30; // ecx
  int v31; // [esp+0h] [ebp-14h]
  char v32; // [esp+0h] [ebp-14h]
  char v33; // [esp+0h] [ebp-14h]
  char v34; // [esp+0h] [ebp-14h]
  char v35; // [esp+0h] [ebp-14h]
  int v36; // [esp+0h] [ebp-14h]
  unsigned int v37; // [esp+4h] [ebp-10h]

  if ( !*(_DWORD *)(a8 + 64) )
    return 1;
  result = Rules_ConstructCodeFileOpen(
             *a1,
             a2,
             a3,
             a4,
             a6,
             *a9,
             a5,
             (char)aSlot_desc,
             *(const char **)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 12),
             *a11,
             a12);
  *a1 = result;
  if ( result )
  {
    v37 = 0;
    if ( *(_DWORD *)(a8 + 64) )
    {
      v31 = 0;
      do
      {
        v15 = v31;
        v16 = v37;
        v17 = v31 + *(_DWORD *)(a8 + 52);
        if ( v37 )
          Output_WriteFormatted(v37, v31, *a1, (int)asc_50C57C, v31);
        Output_WriteFormatted(v16, v15, *a1, (int)aUUUUUUUUUUUUUU, *(_BYTE *)v17 & 1);
        ObjectsCompiler_WriteDefclassPointerRef(*a1, *(_DWORD *)(v17 + 4), a7);
        Output_WriteFormatted(v18, *a1, *a1, (int)asc_50C5DC, v31);
        ObjectsCompiler_WriteSlotNamePointerRef(*a1, *(_DWORD *)(v17 + 8), a7);
        Output_WriteFormatted(*a1, v19, *a1, (int)asc_50C6C0, v32);
        Compiler_WriteSymbolReference(*a1, *(_DWORD *)(v17 + 12), v20);
        if ( *(_DWORD *)(v17 + 16) )
        {
          Output_WriteFormatted(v22, *a1, *a1, (int)aVoid_2, v33);
          if ( (*(_BYTE *)v17 & 0x40) != 0 )
          {
            Rules_ExpressionToCode(*a1, *(__int16 **)(v17 + 16), v23, a3);
          }
          else
          {
            v29 = (__int16 *)AST_BuildExpressionFromValue(*(_DWORD **)(v17 + 16));
            Rules_ExpressionToCode(*a1, v29, (int)v29, a3);
            AST_Free(v30);
          }
        }
        else
        {
          Output_WriteFormatted(v22, v21, *a1, (int)aNull_28, v33);
        }
        Output_WriteFormatted(*a1, v24, *a1, (int)asc_50C5DC, v34);
        Compiler_WriteConstraintReference(*a1, *(_DWORD *)(v17 + 20), a7, a3);
        Output_WriteFormatted(v26, v25, *a1, (int)a00l, v35);
        if ( (*(_BYTE *)v17 & 1) != 0 )
        {
          Output_WriteFormatted(
            *a1,
            *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 12),
            *a1,
            (int)aSD_UU000Null,
            *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 12));
        }
        else
        {
          LOBYTE(v27) = *(_BYTE *)v17;
          Output_WriteFormatted(v28, v27, *a1, (int)aNull000Null, v36);
        }
        v31 = v36 + 44;
        ++v37;
      }
      while ( v37 < *(_DWORD *)(a8 + 64) );
    }
    *a10 += *(_DWORD *)(a8 + 64);
    *a1 = Rules_ConstructCodeFileClose(*a1, a10, a7, a9, a11, (int)a12);
    return 1;
  }
  return result;
}
// 4D1010: variable 'v16' is possibly undefined
// 4D1010: variable 'v15' is possibly undefined
// 4D1030: variable 'v18' is possibly undefined
// 4D1030: variable 'v31' is possibly undefined
// 4D104E: variable 'v19' is possibly undefined
// 4D104E: variable 'v32' is possibly undefined
// 4D105B: variable 'v20' is possibly undefined
// 4D1072: variable 'v22' is possibly undefined
// 4D1072: variable 'v33' is possibly undefined
// 4D108A: variable 'v23' is possibly undefined
// 4D1099: variable 'v24' is possibly undefined
// 4D1099: variable 'v34' is possibly undefined
// 4D10B7: variable 'v26' is possibly undefined
// 4D10B7: variable 'v25' is possibly undefined
// 4D10B7: variable 'v35' is possibly undefined
// 4D110B: variable 'v36' is possibly undefined
// 4D1169: variable 'v30' is possibly undefined
// 4D117B: variable 'v21' is possibly undefined
// 4D1190: variable 'v28' is possibly undefined
// 4D1190: variable 'v27' is possibly undefined
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004D11A0) --------------------------------------------------------
signed int  ObjectsCompiler_WriteSlotDescPointerArray(
        int *a1,
        const char *a2,
        int a3,
        const char *a4,
        int a5,
        int *a6,
        int a7,
        int a8,
        int *a9,
        int *a10,
        int *a11,
        const char **a12)
{
  int v14; // eax
  unsigned int v15; // edx
  int v16; // ecx
  char v17; // [esp+0h] [ebp-Ch]

  if ( !*(_DWORD *)(a8 + 72) )
    return 1;
  v14 = Rules_ConstructCodeFileOpen(
          *a1,
          a2,
          a3,
          a4,
          a6,
          *a9,
          a5,
          (char)aSlot_desc_0,
          *(const char **)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 16),
          *a11,
          a12);
  *a1 = v14;
  if ( !v14 )
    return 0;
  v15 = 0;
  if ( *(_DWORD *)(a8 + 72) )
  {
    v16 = 0;
    do
    {
      if ( v15 )
        Output_WriteFormatted(v16, v15, *a1, (int)asc_50C5DC, v17);
      Output_WriteFormatted(v16 + 4, v15 + 1, *a1, (int)aSD_UU, *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 12));
    }
    while ( v15 < *(_DWORD *)(a8 + 72) );
  }
  *a10 += *(_DWORD *)(a8 + 72);
  *a1 = Rules_ConstructCodeFileClose(*a1, a10, a7, a9, a11, (int)a12);
  return 1;
}
// 4D1212: variable 'v15' is possibly undefined
// 4D121C: variable 'v16' is possibly undefined
// 4D121C: variable 'v17' is possibly undefined
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004D12A0) --------------------------------------------------------
int  ObjectsCompiler_WriteSlotIndexMapArray(
        int *a1,
        const char *a2,
        int a3,
        const char *a4,
        int a5,
        int *a6,
        int a7,
        _DWORD *a8,
        int *a9,
        int *a10,
        int *a11,
        const char **a12)
{
  int result; // eax
  unsigned int v14; // edx
  int v15; // ecx
  char v16; // [esp+0h] [ebp-Ch]

  if ( !a8[18] )
    return 1;
  result = Rules_ConstructCodeFileOpen(
             *a1,
             a2,
             a3,
             a4,
             a6,
             *a9,
             a5,
             (char)aUnsigned,
             *(const char **)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 20),
             *a11,
             a12);
  *a1 = result;
  if ( result )
  {
    v14 = 0;
    v15 = 0;
    do
    {
      if ( v14 )
        Output_WriteFormatted(v15, v14, *a1, (int)asc_50C5DC, v16);
      Output_WriteFormatted(v15 + 4, v14 + 1, *a1, (int)aU_1, *(_DWORD *)(v15 + a8[15]));
    }
    while ( v14 <= a8[19] );
    *a10 += a8[19] + 1;
    *a1 = Rules_ConstructCodeFileClose(*a1, a10, a7, a9, a11, (int)a12);
    return 1;
  }
  return result;
}
// 4D12FA: variable 'v14' is possibly undefined
// 4D1304: variable 'v15' is possibly undefined
// 4D1304: variable 'v16' is possibly undefined
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004D1370) --------------------------------------------------------
int  ObjectsCompiler_WriteHandlerArray(
        int *a1,
        const char *a2,
        char a3,
        const char *a4,
        int a5,
        int *a6,
        int a7,
        int a8,
        int *a9,
        int *a10,
        int *a11,
        const char **a12)
{
  int result; // eax
  int v14; // edx
  int v15; // ecx
  DWORD v16; // ebp
  int v17; // esi
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // edx
  char v22; // [esp+0h] [ebp-14h]
  char v23; // [esp+0h] [ebp-14h]
  int v24; // [esp+4h] [ebp-10h]

  v22 = a3;
  if ( !*(_DWORD *)(a8 + 96) )
    return 1;
  result = Rules_ConstructCodeFileOpen(
             *a1,
             a2,
             a3,
             a4,
             a6,
             *a9,
             a5,
             (char)aHandler_1,
             *(const char **)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 24),
             *a11,
             a12);
  *a1 = result;
  if ( result )
  {
    v15 = *(_DWORD *)(a8 + 96);
    v16 = 0;
    if ( v15 )
    {
      v24 = 0;
      do
      {
        if ( v16 )
          Output_WriteFormatted(v15, v14, *a1, (int)asc_50C57C, v22);
        v17 = v24 + *(_DWORD *)(a8 + 88);
        Output_WriteFormatted(v15, v14, *a1, (int)aUU000, *(_BYTE *)v17 & 1);
        Compiler_WriteSymbolReference(*a1, *(_DWORD *)(v17 + 8), v18);
        Output_WriteFormatted(v19, *a1, *a1, (int)asc_50C5DC, v22);
        ObjectsCompiler_WriteDefclassPointerRef(*a1, *(_DWORD *)(v17 + 12), a7);
        Output_WriteFormatted(*(_DWORD *)(v17 + 24), *a1, *a1, (int)aDDD_0, *(_DWORD *)(v17 + 16));
        Rules_ExpressionToCode(*a1, *(__int16 **)(v17 + 28), v20, v16);
        Output_WriteFormatted(*a1, v21, *a1, (int)aNull_29, v23);
        ++v16;
        v24 += 36;
      }
      while ( v16 < *(_DWORD *)(a8 + 96) );
    }
    *a10 += *(_DWORD *)(a8 + 96);
    *a1 = Rules_ConstructCodeFileClose(*a1, a10, a7, a9, a11, (int)a12);
    return 1;
  }
  return result;
}
// 4D13F3: variable 'v15' is possibly undefined
// 4D13F3: variable 'v14' is possibly undefined
// 4D13F3: variable 'v22' is possibly undefined
// 4D142C: variable 'v18' is possibly undefined
// 4D1439: variable 'v19' is possibly undefined
// 4D1473: variable 'v20' is possibly undefined
// 4D1480: variable 'v21' is possibly undefined
// 4D1480: variable 'v23' is possibly undefined
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004D14F0) --------------------------------------------------------
int  ObjectsCompiler_WriteHandlerIndexMapArray(
        int *a1,
        const char *a2,
        int a3,
        const char *a4,
        int a5,
        int *a6,
        int a7,
        int a8,
        int *a9,
        int *a10,
        int *a11,
        const char **a12)
{
  int result; // eax
  unsigned int v14; // edx
  int v15; // ecx
  char v16; // [esp+0h] [ebp-Ch]

  if ( !*(_DWORD *)(a8 + 96) )
    return 1;
  result = Rules_ConstructCodeFileOpen(
             *a1,
             a2,
             a3,
             a4,
             a6,
             *a9,
             a5,
             (char)aUnsigned,
             *(const char **)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 28),
             *a11,
             a12);
  *a1 = result;
  if ( result )
  {
    v14 = 0;
    if ( *(_DWORD *)(a8 + 96) )
    {
      v15 = 0;
      do
      {
        if ( v14 )
          Output_WriteFormatted(v15, v14, *a1, (int)asc_50C5DC, v16);
        Output_WriteFormatted(v15 + 4, v14 + 1, *a1, (int)aU_1, *(_DWORD *)(v15 + *(_DWORD *)(a8 + 92)));
      }
      while ( v14 < *(_DWORD *)(a8 + 96) );
    }
    *a10 += *(_DWORD *)(a8 + 96);
    *a1 = Rules_ConstructCodeFileClose(*a1, a10, a7, a9, a11, (int)a12);
    return 1;
  }
  return result;
}
// 4D1551: variable 'v14' is possibly undefined
// 4D155B: variable 'v15' is possibly undefined
// 4D155B: variable 'v16' is possibly undefined
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004D15C0) --------------------------------------------------------
signed int __thiscall Rules_RegisterObjectPatternType(void *this)
{
  int v1; // ecx

  Rules_EnsureObjectPatternVTable();
  if ( Rules_IsReservedPatternSymbol((int)this, 0) == 1 )
  {
    Rules_ReportSystemError(v1, 1);
    IO_RunRouterExitCallbacks();
  }
  Rules_AddReservedPatternSymbol((int)aObject, 0);
  Rules_AddPatternParser(
    (int)aObjects_0,
    20,
    (int)Rules_IsObjectPatternKeyword,
    (int)(uintptr_t)g_Rules_ObjectPatternVTable,
    (int)Rules_ParseObjectPattern,
    (int)Rules_AnalyzeObjectPatternRestrictions,
    (int)Rules_AddObjectPatternNode,
    (int)Rules_RemoveObjectPatternNode,
    0,
    (int)Rules_BuildSlotBoundTestNode,
    (int)Rules_BuildSlotBoundTestExpression,
    (int)Rules_BuildSlotRangeTestNode,
    (int)Rules_BuildMultifieldIndexTestNode,
    (int)mblen_,
    (int)Rules_BuildSlotUnboundTestExpression,
    (int)mblen__0,
    (int)Rules_DecrementBitmapRefCountIfSet,
    (int)Rules_IncrementBitmapRefCount,
    (int)Rules_SetObjectPatternNegatedFlag,
    (int)Rules_TriggerObjectPatternMatchForAll,
    (int)Rules_CreateDefaultObjectPatternRestriction,
    (int)Compiler_WriteObjectPatternSecondaryIndexRef);
  Rules_RegisterHostFunction(aObjectPatternM, 117, (int)aObjectmatchdel, (int)Rules_EvaluatePatternQueryExpression, 0);
  Rules_AddFunctionParser(aObjectPatternM);
  Rules_SetFunctionSeqOverloadFlags(aObjectPatternM, 0);
  Compiler_RegisterObjectPatternNetworkCodeGenerator();
  Rules_RegisterObjectPatternConstraintEvaluators();
  return Rules_RegisterObjectPatternNetworkBinaryItem();
}
// 4D16A6: variable 'v1' is possibly undefined
// 4D88F0: using guessed type int sub_4D88F0(void);
// 4E15D0: using guessed type int mblen_();
// 4E1600: using guessed type int mblen__0();

//----- (004D16C0) --------------------------------------------------------
BOOL __thiscall Rules_IsObjectPatternKeyword(void *this)
{
  return strcmp_(this, aObject) == 0;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004D16E0) --------------------------------------------------------
_DWORD * Rules_ParseObjectPattern(int a1)
{
  unsigned __int16 *v2; // esi
  unsigned __int16 *v3; // ebp
  unsigned __int16 *v4; // esi
  int v5; // edx
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  _BYTE *v10; // eax
  int v11; // edx
  int v12; // eax
  _DWORD *v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int *v16; // ebx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // ecx
  _DWORD *v24; // eax
  int v25; // edx
  int v26; // ecx
  int v27; // [esp+0h] [ebp-30h] BYREF
  int v28; // [esp+4h] [ebp-2Ch]
  char *v29; // [esp+8h] [ebp-28h]
  int v30; // [esp+Ch] [ebp-24h] BYREF
  int v31; // [esp+10h] [ebp-20h]
  int v32; // [esp+14h] [ebp-1Ch]
  _DWORD *v33; // [esp+18h] [ebp-18h]

  v33 = 0;
  v32 = 0;
  v31 = 0;
  v2 = (unsigned __int16 *)Rules_AllocateClassBitmap((unsigned __int16)g_ClipsDefclassIdCount - 1, 1);
  v3 = v2;
  if ( Rules_IsClassBitmapEmpty(v2) )
  {
    Rules_PrintErrorID((int)aObjrtbld, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoObjectsOfExi, v7);
    Mem_SmallBlockFree(v2, ((int)*v2 >> 3) + 3);
    return 0;
  }
  else
  {
    v4 = (unsigned __int16 *)Rules_AllocateClassBitmap((unsigned __int16)g_ClipsDefclassIdCount - 1, 1);
    Rules_IncrementIndentDepth(7);
    Parser_NextToken(a1, v5);
    if ( v27 != 101 )
    {
      while ( 1 )
      {
        v31 = 1;
        IO_OutNewline();
        IO_OutWriteToken(asc_50C7F8);
        IO_OutWriteToken(v29);
        if ( v27 != 100 || (Parser_NextToken(a1, (int)&v27), v27 != 2) )
        {
          Parser_ReportSyntaxError();
          goto LABEL_5;
        }
        if ( Rules_CheckDuplicateAttributeRestriction((int)v33, v28) )
          goto LABEL_5;
        if ( v28 == g_Symbol_IsA )
        {
          if ( !Rules_ParseObjectPatternClassRestriction(a1, (int)&v27) )
            goto LABEL_5;
          Rules_ResetClassBitmapToScope(v4, 0);
          if ( !Rules_ProcessObjectPatternClassRestriction(v4, (int *)(v14 + 68), 1) )
          {
            AST_FreeNode(v15);
            goto LABEL_5;
          }
          Rules_AndClassBitmaps((int)v3, v4);
        }
        else if ( v28 == g_Clips_NameSymbol )
        {
          if ( !Rules_ParseObjectPatternNameRestriction(a1, (int)&v27) )
            goto LABEL_5;
          Rules_ResetClassBitmapToScope(v4, 1);
        }
        else
        {
          v16 = Rules_ResolveSlotConstraintAcrossClasses((int)v3, v28, &v30);
          if ( v16 )
          {
            Rules_ResetClassBitmapToScope(v4, 1);
            if ( !Rules_ParseObjectPatternSlotRestriction(a1, (int)&v27, v30, v16) )
              goto LABEL_5;
          }
          else
          {
            Rules_ResetClassBitmapToScope(v4, 0);
            *(_DWORD *)(AST_AllocNode() + 36) = v28;
          }
        }
        if ( Rules_IsClassBitmapEmpty(v4) )
        {
          Rules_PrintErrorID((int)aObjrtbld, 2, 0);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoObjectsOfE_0, v17);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(*(_DWORD *)(v18 + 36) + 16), v18);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aRestrictionInO, v19);
          AST_FreeNode(v20);
          goto LABEL_5;
        }
        if ( Rules_IsClassBitmapEmpty(v3) )
          break;
        if ( v9 )
        {
          if ( v33 )
            *(_DWORD *)(v32 + 64) = v9;
          else
            v33 = (_DWORD *)v9;
          v32 = v9;
        }
        AST_Append(v9, v8);
        Parser_NextToken(a1, (int)&v27);
        if ( v27 == 101 )
          goto LABEL_20;
      }
      Rules_PrintErrorID((int)aObjrtbld, 1, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoObjectsOfExi, v21);
      AST_FreeNode(v22);
      goto LABEL_5;
    }
LABEL_20:
    if ( !v33 )
    {
      if ( Rules_IsClassBitmapEmpty(v3) )
      {
        Rules_PrintErrorID((int)aObjrtbld, 1, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoObjectsOfExi, v23);
LABEL_5:
        Mem_SmallBlockFree(v3, ((int)*v3 >> 3) + 3);
        Mem_SmallBlockFree(v4, ((int)*v4 >> 3) + 3);
        AST_FreeNode((int)v33);
        Rules_DecrementIndentDepth(7);
        return 0;
      }
      v24 = (_DWORD *)AST_AllocNode();
      *v24 = 17;
      v25 = g_Symbol_IsA;
      v24[8] = 1;
      v24[9] = v25;
      v33 = v24;
      v24[10] = v26;
    }
    if ( v31 )
    {
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(v29);
    }
    Mem_SmallBlockFree(v4, ((int)*v4 >> 3) + 3);
    v10 = Rules_TrimClassBitmapToHighestBit(v3);
    LOWORD(v11) = *(_WORD *)v10;
    v12 = Rules_AddBitmapValue(v10, ((v11 - (__CFSHL__(v11 >> 31, 3) + 8 * (v11 >> 31))) >> 3) + 3);
    v33[15] = v12;
    ++*(_DWORD *)(v12 + 4);
    Mem_SmallBlockFree(v13, ((int)*(unsigned __int16 *)v13 >> 3) + 3);
    Rules_DecrementIndentDepth(7);
    return v33;
  }
}
// 4D173D: variable 'v5' is possibly undefined
// 4D17F2: variable 'v7' is possibly undefined
// 4D18A1: variable 'v9' is possibly undefined
// 4D18B6: variable 'v8' is possibly undefined
// 4D1926: variable 'v11' is possibly undefined
// 4D195A: variable 'v13' is possibly undefined
// 4D199B: variable 'v14' is possibly undefined
// 4D19A9: variable 'v15' is possibly undefined
// 4D1A35: variable 'v17' is possibly undefined
// 4D1A3A: variable 'v18' is possibly undefined
// 4D1A54: variable 'v19' is possibly undefined
// 4D1A5B: variable 'v20' is possibly undefined
// 4D1A80: variable 'v21' is possibly undefined
// 4D1A87: variable 'v22' is possibly undefined
// 4D1AC3: variable 'v23' is possibly undefined
// 4D1AEC: variable 'v26' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51AD6C: using guessed type __int16 word_51AD6C;
// 54E6F8: using guessed type int dword_54E6F8;
// 54E6FC: using guessed type int dword_54E6FC;

//----- (004D1B00) --------------------------------------------------------
int  Rules_AnalyzeObjectPatternRestrictions(int a1)
{
  int v1; // eax
  int result; // eax
  unsigned __int16 *v3; // edi
  int v4; // ebx
  int v5; // esi
  int *v6; // eax
  int v7; // ecx
  int v8; // ebx
  int v9; // eax
  char *v10; // edi
  unsigned int v11; // eax
  int v12; // ecx
  int v13; // esi
  char *v14; // eax
  _DWORD *v15; // edx
  int v16; // ecx
  char v17; // dl
  _DWORD *v18; // ebx
  int v19; // ecx
  int v20; // ebp
  int v21; // edi
  char *v22; // eax
  int v23; // ecx
  _DWORD *v24; // edx
  int v25; // ecx
  char *v26; // ebx
  char v27; // dh
  _WORD *v28; // eax
  _BYTE *v29; // ecx
  int v30; // edx
  int v31; // eax
  _DWORD *v32; // ecx
  int v33; // ecx
  int v34; // ecx
  int v35; // ecx
  _DWORD *v36; // [esp+0h] [ebp-3Ch] BYREF
  _DWORD *v37; // [esp+4h] [ebp-38h] BYREF
  _DWORD *v38; // [esp+8h] [ebp-34h] BYREF
  BOOL v39; // [esp+Ch] [ebp-30h]
  int v40; // [esp+10h] [ebp-2Ch]
  _WORD *v41; // [esp+14h] [ebp-28h]
  int v42; // [esp+18h] [ebp-24h]
  _DWORD *v43; // [esp+1Ch] [ebp-20h]
  int v44; // [esp+20h] [ebp-1Ch]

  v42 = a1;
  v39 = 0;
  v1 = Rules_ExtractObjectPatternRestrictionNodes(*(_DWORD *)(a1 + 24), *(_DWORD *)(a1 + 64), &v37, (int)&v36, (int *)&v38);
  *(_DWORD *)(v42 + 64) = v1;
  result = Rules_StaticConstraintCheckingEnabled();
  if ( result )
  {
    v3 = *(unsigned __int16 **)(v36[15] + 16);
    v41 = (_WORD *)Rules_AllocateClassBitmap(*v3, 0);
    if ( v37 && (v4 = v37[4]) != 0 && *(_DWORD *)(v4 + 6) )
    {
      v5 = *(_DWORD *)(v4 + 6);
      do
      {
        v6 = Class_LookupInScope(*(_BYTE **)(*(_DWORD *)(v5 + 2) + 16));
        if ( v6 )
        {
          v7 = *((unsigned __int16 *)v6 + 12);
          if ( (unsigned __int16)v7 <= (int)*v3 )
          {
            v8 = (int)*((unsigned __int16 *)v6 + 12) >> 3;
            v9 = 1 << (v7 % 8);
            if ( ((unsigned __int8)v9 & *((_BYTE *)v3 + v8 + 2)) != 0 )
              *((_BYTE *)v41 + v8 + 2) |= v9;
          }
        }
        v5 = *(_DWORD *)(v5 + 10);
      }
      while ( v5 );
      v39 = Rules_ClassBitmapsIdentical(v41, v3) == 0;
    }
    else
    {
      qmemcpy(v41 + 1, v3 + 1, ((int)(unsigned __int16)*v41 >> 3) + 1);
    }
    v43 = *(_DWORD **)(v42 + 64);
    if ( v43 != v36 )
    {
      while ( v43 == v37 || v43 == v38 )
      {
LABEL_6:
        v43 = (_DWORD *)v43[16];
        if ( v43 == v36 )
          goto LABEL_7;
      }
      v44 = 0;
      while ( 1 )
      {
LABEL_20:
        if ( (unsigned __int16)v44 > (int)(unsigned __int16)*v41 )
          goto LABEL_6;
        v10 = (char *)v41 + ((int)(unsigned __int16)v44 >> 3);
        v40 = 1 << ((unsigned __int16)v44 % 8);
        if ( ((unsigned __int8)v40 & (unsigned __int8)v10[2]) != 0 )
        {
          v11 = Instance_ResolveSlotIndex(*(_DWORD *)(g_ClipsDefclassIdTable + 4 * (unsigned __int16)v44), v43[9]);
          v13 = *(_DWORD *)(*(_DWORD *)(v12 + 56) + 4 * v11);
          v14 = Rules_IntersectConstraints(v43[4], *(_DWORD *)(v13 + 20));
          Rules_ConstraintIsUnmatchable(v14);
          AST_DecrementNodeRefCount(v15);
          if ( v16 )
          {
            v17 = ~(_BYTE)v40 & v10[2];
            v39 = 1;
            v10[2] = v17;
            ++v44;
          }
          else
          {
            if ( *v43 != 18 )
              goto LABEL_22;
            v18 = (_DWORD *)v43[17];
            if ( !v18 )
              goto LABEL_22;
            do
            {
              if ( *v18 == 18 || *v18 == 16 )
                v19 = *(_DWORD *)(v18[4] + 26);
              else
                v19 = v18[4];
              v20 = *(_DWORD *)(v19 + 18);
              *(_DWORD *)(v19 + 18) = *(_DWORD *)(*(_DWORD *)(v13 + 20) + 18);
              v21 = *(_DWORD *)(v19 + 22);
              *(_DWORD *)(v19 + 22) = *(_DWORD *)(*(_DWORD *)(v13 + 20) + 22);
              v22 = Rules_IntersectConstraints(v19, *(_DWORD *)(v13 + 20));
              *(_DWORD *)(v23 + 18) = v20;
              *(_DWORD *)(v23 + 22) = v21;
              Rules_ConstraintIsUnmatchable(v22);
              AST_DecrementNodeRefCount(v24);
              if ( v25 )
              {
                v26 = (char *)v41 + ((int)(unsigned __int16)v44 >> 3);
                v27 = ~(1 << ((unsigned __int16)v44 % 8)) & v26[2];
                v39 = 1;
                v26[2] = v27;
                ++v44;
                goto LABEL_20;
              }
              v18 = (_DWORD *)v18[16];
            }
            while ( v18 );
            ++v44;
          }
        }
        else
        {
LABEL_22:
          ++v44;
        }
      }
    }
LABEL_7:
    if ( v39 )
    {
      if ( Rules_IsClassBitmapEmpty(v41) )
      {
        Rules_PrintErrorID((int)aObjrtbld, 3, 1);
        Mem_SmallBlockFree(v41, ((int)(unsigned __int16)*v41 >> 3) + 3);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoObjectsOfE_1, v33);
        Rules_PrintLongInteger(v34, *(_DWORD *)(v42 + 28));
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__25, v35);
        return 1;
      }
      else
      {
        v28 = Rules_TrimClassBitmapToHighestBit(v41);
        Rules_DecrementBitmapRefCountIfSet(v36[15], (int)v28);
        LOWORD(v30) = *(_WORD *)v29;
        v31 = Rules_AddBitmapValue(v29, ((v30 - (__CFSHL__(v30 >> 31, 3) + 8 * (v30 >> 31))) >> 3) + 3);
        v36[15] = v31;
        ++*(_DWORD *)(v36[15] + 4);
        Mem_SmallBlockFree(v32, ((int)*(unsigned __int16 *)v32 >> 3) + 3);
        return 0;
      }
    }
    else
    {
      Mem_SmallBlockFree(v41, ((int)(unsigned __int16)*v41 >> 3) + 3);
      return 0;
    }
  }
  return result;
}
// 4D1D3E: variable 'v12' is possibly undefined
// 4D1D5E: variable 'v15' is possibly undefined
// 4D1D65: variable 'v16' is possibly undefined
// 4D1DCA: variable 'v23' is possibly undefined
// 4D1DDB: variable 'v24' is possibly undefined
// 4D1DE2: variable 'v25' is possibly undefined
// 4D1E7D: variable 'v29' is possibly undefined
// 4D1E88: variable 'v30' is possibly undefined
// 4D1EC1: variable 'v32' is possibly undefined
// 4D1F12: variable 'v33' is possibly undefined
// 4D1F23: variable 'v34' is possibly undefined
// 4D1F32: variable 'v35' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51AD64: using guessed type int dword_51AD64;

//----- (004D1F50) --------------------------------------------------------
_DWORD * Rules_AddObjectPatternNode(int a1)
{
  int v2; // ebp
  int v3; // eax
  _DWORD *v4; // edx
  int v5; // eax
  int v6; // esi
  BOOL v7; // edi
  int *v8; // edx
  _DWORD *v9; // edx
  _DWORD *v10; // ebp
  _DWORD *v11; // ebx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  _DWORD *v17; // [esp+0h] [ebp-2Ch] BYREF
  int v18; // [esp+4h] [ebp-28h]
  int v19; // [esp+8h] [ebp-24h]
  int v20; // [esp+Ch] [ebp-20h]
  int *v21; // [esp+10h] [ebp-1Ch]

  v20 = Rules_GetObjectPatternNetworkRoot();
  v2 = 0;
  v19 = Rules_BuildAttributeIndexBitmap(*(_DWORD *)(a1 + 64));
  v3 = *(_DWORD *)(a1 + 64);
  v21 = 0;
  v5 = Rules_PruneEmptyObjectPatternNodes(v3, v4);
  *(_DWORD *)(a1 + 64) = v5;
  v6 = v5;
  do
  {
    if ( (*(_BYTE *)(v6 + 8) & 4) != 0 )
    {
      v2 = v6;
      v6 = *(_DWORD *)(v6 + 68);
    }
    v7 = !*(_DWORD *)(v6 + 64) && v2;
    v8 = (int *)Rules_FindObjectPatternNode(v20, v6, v7, (int *)&v17);
    if ( !v8 )
      v8 = Rules_CreateObjectPatternNode(v6, v17, v7, (int)v21);
    if ( !*(_DWORD *)(v6 + 64) && v2 )
    {
      v6 = v2;
      v2 = 0;
    }
    v21 = v8;
    v6 = *(_DWORD *)(v6 + 64);
    v20 = v8[4];
  }
  while ( v6 && !*(_DWORD *)(v6 + 60) );
  v9 = (_DWORD *)v21[8];
  if ( v9 )
  {
    while ( v18 != v9[5] || v19 != v9[6] )
    {
      v9 = (_DWORD *)v9[8];
      if ( !v9 )
        goto LABEL_18;
    }
    return v9;
  }
  else
  {
LABEL_18:
    v10 = *(_DWORD **)(g_ClipsMemoryTable + 176);
    if ( v10 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 176);
      *(_DWORD *)(g_ClipsMemoryTable + 176) = *v10;
      v11 = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      v11 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x2C);
    }
    Rules_ResetDataObjectValue((int)v11);
    v12 = (int)v21;
    v11[4] = 0;
    v11[7] = v12;
    v13 = v18;
    v11[5] = v18;
    ++*(_DWORD *)(v13 + 4);
    Rules_AdjustClassBusyCountFromBitmap(v18, 1);
    v14 = v19;
    v11[6] = v19;
    if ( v14 )
      ++*(_DWORD *)(v14 + 4);
    v15 = (int)v21;
    v11[10] = 0;
    v11[8] = *(_DWORD *)(v15 + 32);
    v21[8] = (int)v11;
    v11[9] = Rules_GetReactiveRuleList();
    Rules_SetReactiveRuleList((int)v11);
    return v11;
  }
}
// 4D1F7D: variable 'v4' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004D20F0) --------------------------------------------------------
int  Rules_FindObjectPatternNode(int a1, int a2, int a3, int *a4)
{
  int v4; // esi
  BOOL v6; // eax

  v4 = a1;
  *a4 = 0;
  if ( !a1 )
    return 0;
  while ( 1 )
  {
    v6 = *(_DWORD *)a2 == 18 || *(_DWORD *)a2 == 16 ? *(_DWORD *)v4 << 30 >> 31 : (*(_BYTE *)v4 & 2) == 0;
    if ( v6
      && *(_DWORD *)(a2 + 40) == *(_DWORD *)(v4 + 8)
      && *(_DWORD *)v4 << 21 >> 24 == *(_DWORD *)(a2 + 32)
      && *(_DWORD *)(a2 + 12) << 18 >> 25 == *(_DWORD *)v4 << 13 >> 24
      && a3 == *(_DWORD *)v4 << 29 >> 31
      && AST_NodeListsEqual(*(__int16 **)(v4 + 12), *(__int16 **)(a2 + 52)) )
    {
      break;
    }
    if ( !*a4 && *(_DWORD *)v4 << 21 >> 24 == *(_DWORD *)(a2 + 32) && *(_DWORD *)(a2 + 40) == *(_DWORD *)(v4 + 8) )
      *a4 = v4;
    v4 = *(_DWORD *)(v4 + 28);
    if ( !v4 )
      return 0;
  }
  return v4;
}
// 4D2152: variable 'a3' is possibly undefined

//----- (004D21C0) --------------------------------------------------------
int * Rules_CreateObjectPatternNode(int a1, _DWORD *a2, int a3, int a4)
{
  _DWORD *v7; // edx
  signed int v8; // edx
  char v9; // ah
  __int16 *v10; // eax
  int *v11; // edx
  char v12; // cl
  int *v13; // ebx
  int v14; // edx
  int v15; // ecx
  _DWORD *v17; // edx
  _DWORD *v18; // edi
  int v19; // eax
  int v20; // ecx
  int v21; // esi
  int v22; // [esp+0h] [ebp-10h]
  int v23; // [esp+0h] [ebp-10h]

  v7 = *(_DWORD **)(g_ClipsMemoryTable + 160);
  if ( v7 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 160);
    *(_DWORD *)(g_ClipsMemoryTable + 160) = *v7;
    v8 = g_ClipsMemFreeListTemp;
  }
  else
  {
    v8 = Mem_HeapAllocWithRetry((_DWORD *)0x28);
  }
  *(_DWORD *)(v8 + 32) = 0;
  *(_DWORD *)(v8 + 4) = 0;
  *(_DWORD *)(v8 + 16) = 0;
  *(_DWORD *)(v8 + 28) = 0;
  *(_DWORD *)(v8 + 24) = 0;
  v9 = *(_BYTE *)v8;
  *(_DWORD *)(v8 + 36) = 0;
  *(_BYTE *)v8 = v9 & 0xFC;
  v10 = AST_AddHashedNodeChain(*(__int16 **)(a1 + 52), v8, a3);
  v11[3] = (int)v10;
  v22 = (unsigned __int8)*(_DWORD *)(a1 + 32);
  *(_WORD *)v11 &= 0xF807u;
  *v11 |= 8 * v22;
  v23 = *(_DWORD *)(a1 + 12) << 18 >> 25;
  *v11 &= 0xFFF807FF;
  *v11 |= v23 << 11;
  v11[2] = *(_DWORD *)(a1 + 40);
  v13 = v11;
  if ( *(_DWORD *)a1 == 18 || *(_DWORD *)a1 == 16 )
    *(_BYTE *)v11 |= 2u;
  *(_BYTE *)v11 &= ~4u;
  v14 = *v11;
  v13[5] = a4;
  *v13 = (4 * (v12 & 1)) | v14;
  if ( a2 )
  {
    v17 = a2;
    v18 = 0;
    do
    {
      if ( v17[2] != a2[2] )
        break;
      if ( *v17 << 21 >> 24 != *a2 << 21 >> 24 )
        break;
      v19 = v17[3];
      if ( v19 )
      {
        if ( *(_WORD *)v19 == 50 && (**(_DWORD **)(*(_DWORD *)(v19 + 2) + 16) & 0x80) != 0 )
          break;
      }
      v18 = v17;
      v17 = (_DWORD *)v17[7];
    }
    while ( v17 );
    if ( v17 )
    {
      v13[6] = v17[6];
      v13[7] = (int)v17;
      v20 = v17[6];
      if ( v20 )
      {
        *(_DWORD *)(v20 + 28) = v13;
      }
      else
      {
        v21 = v17[5];
        if ( v21 )
          *(_DWORD *)(v21 + 16) = v13;
        else
          Rules_SetObjectPatternNetworkRoot((int)v13);
      }
      v17[6] = v13;
      return v13;
    }
    else
    {
      v13[6] = (int)v18;
      v18[7] = v13;
      return v13;
    }
  }
  else
  {
    if ( a4 )
    {
      v13[7] = *(_DWORD *)(a4 + 16);
      *(_DWORD *)(a4 + 16) = v13;
    }
    else
    {
      v13[7] = Rules_GetObjectPatternNetworkRoot();
      Rules_SetObjectPatternNetworkRoot((int)v13);
    }
    v15 = v13[7];
    if ( v15 )
      *(_DWORD *)(v15 + 24) = v13;
    return v13;
  }
}
// 4D2227: variable 'a3' is possibly undefined
// 4D222C: variable 'v11' is possibly undefined
// 4D2281: variable 'v12' is possibly undefined
// 4D2330: variable 'v17' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004D2380) --------------------------------------------------------
int  Rules_RemoveObjectPatternNode(int *a1)
{
  int v2; // edx
  int v3; // ecx
  int v4; // ecx
  int v5; // edx
  _DWORD *v6; // ecx
  int i; // ebx
  _DWORD *v8; // edx
  _DWORD *j; // eax
  int v10; // ebx
  int result; // eax
  int v12; // edx
  int v13; // ebp
  int v14; // ecx
  int v15; // edx
  _DWORD *v16; // ecx
  int v17; // eax
  _DWORD *v18; // ecx
  int v19; // ecx
  int v20; // edx
  _DWORD *v21; // ecx

  Rules_UnlinkObjectPatternFromGlobalLists(a1);
  Rules_AdjustClassBusyCountFromBitmap(a1[5], v2);
  Rules_DecrementBitmapRefCountIfSet(a1[5], v3);
  if ( a1[6] )
    Rules_DecrementBitmapCount(a1[6], v4);
  v5 = Rules_GetReactiveRuleList();
  for ( i = 0; (_DWORD *)v5 != v6; v5 = *(_DWORD *)(v5 + 36) )
    i = v5;
  if ( i )
    *(_DWORD *)(i + 36) = *(_DWORD *)(v5 + 36);
  else
    Rules_SetReactiveRuleList(*(_DWORD *)(v5 + 36));
  v8 = *(_DWORD **)(v6[7] + 32);
  for ( j = 0; v8 != v6; v8 = (_DWORD *)v8[8] )
    j = v8;
  if ( j )
  {
    j[8] = v6[8];
    g_ClipsMemFreeListTemp = (int)v6;
    *v6 = *(_DWORD *)(g_ClipsMemoryTable + 176);
    result = g_ClipsMemoryTable;
    *(_DWORD *)(g_ClipsMemoryTable + 176) = g_ClipsMemFreeListTemp;
  }
  else
  {
    v10 = v6[8];
    if ( v10 )
    {
      *(_DWORD *)(v6[7] + 32) = v10;
      g_ClipsMemFreeListTemp = (int)v6;
      *v6 = *(_DWORD *)(g_ClipsMemoryTable + 176);
      result = g_ClipsMemFreeListTemp;
      *(_DWORD *)(g_ClipsMemoryTable + 176) = g_ClipsMemFreeListTemp;
    }
    else
    {
      *(_DWORD *)(v6[7] + 32) = 0;
      g_ClipsMemFreeListTemp = (int)v6;
      *v6 = *(_DWORD *)(g_ClipsMemoryTable + 176);
      result = g_ClipsMemoryTable;
      *(_DWORD *)(g_ClipsMemoryTable + 176) = g_ClipsMemFreeListTemp;
      v12 = v6[7];
      if ( !*(_DWORD *)(v12 + 16) )
      {
        while ( v12 )
        {
          if ( *(_DWORD *)(v12 + 24) || (v13 = *(_DWORD *)(v12 + 28)) != 0 )
          {
            if ( *(_DWORD *)(v12 + 24) )
            {
              v17 = *(_DWORD *)(v12 + 28);
              *(_DWORD *)(*(_DWORD *)(v12 + 24) + 28) = v17;
              if ( v17 )
                *(_DWORD *)(v17 + 24) = *(_DWORD *)(v12 + 24);
              AST_RemoveHashedNodeChain(*(__int16 **)(v12 + 12), v12);
              g_ClipsMemFreeListTemp = (int)v18;
              *v18 = *(_DWORD *)(g_ClipsMemoryTable + 160);
              result = g_ClipsMemFreeListTemp;
              *(_DWORD *)(g_ClipsMemoryTable + 160) = g_ClipsMemFreeListTemp;
            }
            else
            {
              v19 = v12;
              v20 = *(_DWORD *)(v12 + 20);
              if ( v20 )
                *(_DWORD *)(v20 + 16) = *(_DWORD *)(v19 + 28);
              else
                Rules_SetObjectPatternNetworkRoot(*(_DWORD *)(v19 + 28));
              *(_DWORD *)(*(_DWORD *)(v19 + 28) + 24) = 0;
              AST_RemoveHashedNodeChain(*(__int16 **)(v19 + 12), v19);
              g_ClipsMemFreeListTemp = (int)v21;
              *v21 = *(_DWORD *)(g_ClipsMemoryTable + 160);
              result = g_ClipsMemFreeListTemp;
              *(_DWORD *)(g_ClipsMemoryTable + 160) = g_ClipsMemFreeListTemp;
            }
            return result;
          }
          v14 = v12;
          v15 = *(_DWORD *)(v12 + 20);
          if ( v15 )
            *(_DWORD *)(v15 + 16) = v13;
          else
            Rules_SetObjectPatternNetworkRoot(v13);
          AST_RemoveHashedNodeChain(*(__int16 **)(v14 + 12), v14);
          g_ClipsMemFreeListTemp = (int)v16;
          *v16 = *(_DWORD *)(g_ClipsMemoryTable + 160);
          result = g_ClipsMemoryTable;
          *(_DWORD *)(g_ClipsMemoryTable + 160) = g_ClipsMemFreeListTemp;
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
  int v1; // ebx
  int i; // ecx
  int v3; // ecx
  int *v4; // ecx
  int v5; // ecx

  v1 = (int)result;
  for ( i = g_Clips_InstanceListHead; i; i = *(_DWORD *)(v3 + 68) )
    result = Rules_RemoveMatchingPatternListEntry(i, v1);
  v4 = (int *)g_Instance_DeletedListHead;
  if ( g_Instance_DeletedListHead )
  {
    do
    {
      result = Rules_RemoveMatchingPatternListEntry(*v4, v1);
      v4 = *(int **)(v5 + 4);
    }
    while ( v4 );
  }
  return result;
}
// 4D25F8: variable 'v3' is possibly undefined
// 4D2613: variable 'v5' is possibly undefined
// 51A28C: using guessed type int dword_51A28C;
// 51AD0C: using guessed type int dword_51AD0C;

//----- (004D2630) --------------------------------------------------------
int * Rules_RemoveMatchingPatternListEntry(int a1, int a2)
{
  int *result; // eax
  int *v5; // edx

  result = *(int **)(a1 + 16);
  v5 = 0;
  if ( result )
  {
    do
    {
      while ( 1 )
      {
        while ( a2 != result[2] )
        {
          v5 = result;
          result = (int *)*result;
          if ( !result )
            return result;
        }
        --*(_DWORD *)(a1 + 40);
        if ( v5 )
          break;
        *(_DWORD *)(a1 + 16) = *result;
        g_ClipsMemFreeListTemp = (int)result;
        *result = *(_DWORD *)(g_ClipsMemoryTable + 48);
        *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
        result = *(int **)(a1 + 16);
        if ( !result )
          return result;
      }
      *v5 = *result;
      g_ClipsMemFreeListTemp = (int)result;
      *result = *(_DWORD *)(g_ClipsMemoryTable + 48);
      *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
      result = (int *)*v5;
    }
    while ( *v5 );
  }
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004D26C0) --------------------------------------------------------
signed int  Rules_CheckDuplicateAttributeRestriction(int a1, int a2)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx

  if ( !a1 )
    return 0;
  while ( a2 != *(_DWORD *)(a1 + 36) )
  {
    a1 = *(_DWORD *)(a1 + 64);
    if ( !a1 )
      return 0;
  }
  Rules_PrintErrorID((int)aObjrtbld, 4, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aMultipleRestri, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(v4 + 16), v4);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNotAllowed_, v5);
  return 1;
}
// 4D26F6: variable 'v3' is possibly undefined
// 4D2700: variable 'v4' is possibly undefined
// 4D2712: variable 'v5' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004D2720) --------------------------------------------------------
unsigned int * Rules_ParseObjectPatternClassRestriction(int a1, int a2)
{
  int *v4; // esi
  char v5; // dl
  int v6; // ecx
  unsigned int *result; // eax
  int v8; // ecx
  int *v9; // eax

  v4 = (int *)Rules_CreateLHSParseNode();
  v5 = *(_BYTE *)v4 & 0xFC;
  *(_BYTE *)v4 = v5;
  *(_BYTE *)v4 = v5 | 2;
  IO_OutWriteToken(asc_50C7F8);
  Parser_NextToken(a1, a2);
  result = Rules_ParsePatternFieldList(a1, (int *)a2, v6, 0, 0, v4, 0);
  if ( !result )
  {
    v9 = v4;
LABEL_7:
    AST_DecrementNodeRefCount(v9);
    return 0;
  }
  if ( *(_DWORD *)a2 != 101 || *result == 18 || *result == 16 )
  {
    IO_OutNewline();
    if ( *(_DWORD *)a2 != 101 )
    {
      IO_OutWriteToken(asc_50C7F8);
      IO_OutWriteToken(*(char **)(a2 + 8));
    }
    Parser_ReportSyntaxError();
    AST_FreeNode(v8);
    v9 = v4;
    goto LABEL_7;
  }
  *((_BYTE *)result + 8) |= 0x10u;
  return result;
}
// 4D2765: variable 'v6' is possibly undefined
// 4D27A4: variable 'v8' is possibly undefined

//----- (004D27E0) --------------------------------------------------------
unsigned int * Rules_ParseObjectPatternNameRestriction(int a1, int a2)
{
  int *v4; // esi
  char v5; // dl
  int v6; // ecx
  unsigned int *result; // eax
  int v8; // ecx
  int *v9; // eax

  v4 = (int *)Rules_CreateLHSParseNode();
  v5 = *(_BYTE *)v4 & 0xDE;
  *(_BYTE *)v4 = v5;
  *(_BYTE *)v4 = v5 | 0x20;
  IO_OutWriteToken(asc_50C7F8);
  Parser_NextToken(a1, a2);
  result = Rules_ParsePatternFieldList(a1, (int *)a2, v6, 0, 1u, v4, 0);
  if ( !result )
  {
    v9 = v4;
LABEL_7:
    AST_DecrementNodeRefCount(v9);
    return 0;
  }
  if ( *(_DWORD *)a2 != 101 || *result == 18 || *result == 16 )
  {
    IO_OutNewline();
    if ( *(_DWORD *)a2 != 101 )
    {
      IO_OutWriteToken(asc_50C7F8);
      IO_OutWriteToken(*(char **)(a2 + 8));
    }
    Parser_ReportSyntaxError();
    AST_FreeNode(v8);
    v9 = v4;
    goto LABEL_7;
  }
  *((_BYTE *)result + 8) |= 0x10u;
  return result;
}
// 4D2825: variable 'v6' is possibly undefined
// 4D2864: variable 'v8' is possibly undefined

//----- (004D28A0) --------------------------------------------------------
unsigned int * Rules_ParseObjectPatternSlotRestriction(int a1, int a2, int a3, int *a4)
{
  int v8; // edx
  int v9; // ecx
  unsigned int v10; // eax
  int v11; // ecx
  unsigned int *result; // eax
  int v13; // edx
  unsigned int *v14; // ecx

  IO_OutWriteToken(asc_50C7F8);
  Parser_NextToken(a1, v8);
  v10 = Class_FindSlotNameID(v9);
  result = Rules_ParsePatternFieldList(a1, (int *)a2, v11, a3, v10, a4, 1);
  if ( result )
  {
    if ( *(_DWORD *)a2 == 101 )
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
      IO_OutWriteToken(*(char **)(a2 + 8));
      Parser_ReportSyntaxError();
      AST_FreeNode(v13);
      AST_DecrementNodeRefCount(a4);
      return 0;
    }
  }
  else
  {
    AST_DecrementNodeRefCount(a4);
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
int  Rules_AllocateClassBitmap(int a1, int a2)
{
  int v2; // ebx
  _BYTE *v4; // eax
  int v5; // edx
  _WORD *v6; // ecx
  int v7; // ecx

  v2 = a1;
  if ( a1 == -1 )
    v2 = 0;
  v4 = Mem_SmallBlockAlloc(((v2 - (__CFSHL__(v2 >> 31, 3) + 8 * (v2 >> 31))) >> 3) + 3);
  Mem_AllocArray(v4, v5);
  *v6 = v2;
  Rules_ResetClassBitmapToScope(v6, a2);
  return v7;
}
// 4D2989: variable 'v5' is possibly undefined
// 4D2992: variable 'v6' is possibly undefined
// 4D299A: variable 'v7' is possibly undefined

//----- (004D29A0) --------------------------------------------------------
__int16  Rules_ResetClassBitmapToScope(_WORD *a1, int a2)
{
  int v3; // eax
  int v4; // ebx
  char *v5; // esi
  int v6; // ebx
  int v7; // esi
  int v8; // ecx
  char v9; // ah
  char *v10; // edi
  int v12; // [esp+0h] [ebp-18h]

  v3 = (int)(unsigned __int16)*a1 >> 3;
  v4 = v3 + 1;
  if ( v3 + 1 > 0 )
  {
    v5 = (char *)a1 + v4;
    do
    {
      --v5;
      --v4;
      v5[2] = 0;
    }
    while ( v4 > 0 );
  }
  if ( a2 )
  {
    v12 = Module_GetCurrent();
    v6 = 0;
    v7 = 0;
    while ( 1 )
    {
      LOWORD(v3) = *a1;
      if ( v6 > (unsigned __int16)*a1 )
        break;
      if ( *(_DWORD *)(v7 + g_ClipsDefclassIdTable)
        && Class_IsInScope(*(_DWORD *)(v7 + g_ClipsDefclassIdTable), v12)
        && (v9 = *(_BYTE *)(v8 + 20), (v9 & 8) != 0)
        && (v9 & 4) == 0 )
      {
        v10 = (char *)a1 + ((v6 - (__CFSHL__(v6 >> 31, 3) + 8 * (v6 >> 31))) >> 3);
        v10[2] |= 1 << (v6 % 8);
        v7 += 4;
        ++v6;
      }
      else
      {
        v7 += 4;
        ++v6;
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
    ++*(_DWORD *)(result + 4);
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
void  Rules_AdjustClassBusyCountFromBitmap(int a1, int a2)
{
  unsigned __int16 *v2; // edi
  unsigned __int16 i; // si

  if ( !g_Rules_ClearInProgressFlag )
  {
    v2 = *(unsigned __int16 **)(a1 + 16);
    for ( i = 0; i <= (int)*v2; ++i )
    {
      if ( ((unsigned __int8)(1 << (i % 8)) & *((_BYTE *)v2 + ((int)i >> 3) + 2)) != 0 )
        *(_DWORD *)(*(_DWORD *)(g_ClipsDefclassIdTable + 4 * i) + 26) += a2;
    }
  }
  return;
}
// 4D2AD2: control flows out of bounds to 4D29E4
// 51A180: using guessed type int dword_51A180;
// 51AD64: using guessed type int dword_51AD64;

//----- (004D2B40) --------------------------------------------------------
signed int  Rules_IsClassBitmapEmpty(unsigned __int16 *a1)
{
  int v2; // eax

  v2 = ((int)*a1 >> 3) + 1;
  if ( !(_WORD)v2 )
    return 1;
  while ( !*((_BYTE *)a1 + (unsigned __int16)v2 + 1) )
  {
    LOWORD(v2) = v2 - 1;
    if ( !(_WORD)v2 )
      return 1;
  }
  return 0;
}

//----- (004D2B80) --------------------------------------------------------
signed int  Rules_ClassBitmapsIdentical(unsigned __int16 *a1, _WORD *a2)
{
  unsigned __int16 *v2; // edi
  int v3; // ecx
  _WORD *v4; // ebx
  unsigned __int16 *v5; // esi
  int i; // ecx

  v2 = a1;
  v3 = *a1;
  HIWORD(a1) = 0;
  if ( (unsigned __int16)v3 != (unsigned __int16)*a2 )
    return 0;
  v4 = a2;
  v5 = v2;
  LOWORD(a1) = *a2;
  for ( i = (unsigned int)a1 ^ v3; i < ((int)*v2 >> 3) + 1; ++i )
  {
    if ( *((_BYTE *)v5 + 2) != *((_BYTE *)v4 + 2) )
      return 0;
    v4 = (_WORD *)((char *)v4 + 1);
    v5 = (unsigned __int16 *)((char *)v5 + 1);
  }
  return 1;
}

//----- (004D2BD0) --------------------------------------------------------
signed int  Rules_ProcessObjectPatternClassRestriction(_WORD *a1, int *a2, int a3)
{
  unsigned __int16 *v5; // ebp
  int v6; // ecx
  int v7; // eax
  _DWORD **v8; // ecx
  _DWORD *v9; // ecx
  unsigned __int16 *v10; // esi
  int v11; // edi
  int v12; // eax
  int *v13; // ecx
  int *v14; // eax
  int v15; // ecx
  int v16; // ecx
  int v17; // ebx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v23; // [esp+8h] [ebp-14h]

  while ( 1 )
  {
    v23 = 1;
    if ( !*a2 )
      break;
    v5 = (unsigned __int16 *)Rules_AllocateClassBitmap((unsigned __int16)g_ClipsDefclassIdCount - 1, 1);
    v7 = Rules_AllocateClassBitmap((unsigned __int16)g_ClipsDefclassIdCount - v6, 0);
    v9 = *v8;
    v10 = (unsigned __int16 *)v7;
    if ( v9 )
    {
      v11 = v7 + 2;
      do
      {
        if ( *v9 == 2 )
        {
          v14 = Class_LookupInScope(*(_BYTE **)(v9[1] + 16));
          *(_DWORD *)(v15 + 4) = v14;
          if ( !v14 )
          {
            Rules_PrintErrorID((int)aObjrtbld, 5, 0);
            Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUndefinedClass, v18);
            Mem_SmallBlockFree(v5, ((int)*v5 >> 3) + 3);
            Mem_SmallBlockFree(v10, ((int)*v10 >> 3) + 3);
            return 0;
          }
          if ( (*(_BYTE *)(v15 + 8) & 1) != 0 )
          {
            Rules_ResetClassBitmapToScope(v10, 1);
            v17 = 0;
          }
          else
          {
            v17 = 1;
            Rules_ResetClassBitmapToScope(v10, 0);
          }
          Class_MarkBitmapSubclasses(v11, *(_DWORD *)(v16 + 4), v17);
          Rules_AndClassBitmaps((int)v5, v10);
        }
        else
        {
          v23 = 0;
        }
        v9 = (_DWORD *)v9[16];
      }
      while ( v9 );
    }
    if ( Rules_IsClassBitmapEmpty(v5) )
    {
      Rules_PrintErrorID((int)aObjrtbld, 2, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoObjectsOfE_0, v19);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIsARestriction, v20);
      Mem_SmallBlockFree(v5, ((int)*v5 >> 3) + 3);
      Mem_SmallBlockFree(v10, ((int)*v10 >> 3) + 3);
      return 0;
    }
    if ( v23 )
    {
      v12 = *a2;
      *a2 = *(_DWORD *)(*a2 + 68);
      *(_DWORD *)(v12 + 68) = 0;
      AST_FreeNode(v12);
    }
    Rules_OrClassBitmaps((int)a1, v5);
    Mem_SmallBlockFree(v5, ((int)*v5 >> 3) + 3);
    a2 = v13;
    Mem_SmallBlockFree(v10, ((int)*v10 >> 3) + 3);
    a3 = 0;
  }
  if ( a3 )
    Rules_ResetClassBitmapToScope(a1, 1);
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
_DWORD * Rules_ResolveSlotConstraintAcrossClasses(int a1, int a2, _DWORD *a3)
{
  _DWORD *v4; // esi
  int i; // ebx
  int v6; // ecx
  unsigned int v7; // eax
  _BYTE *v8; // edx
  _DWORD *v9; // edx
  int v11; // edi
  int v13; // [esp+4h] [ebp-18h]

  v4 = 0;
  v13 = 0;
  *a3 = 0;
  do
  {
    for ( i = *(_DWORD *)(v13 + g_DefclassHashTable); i; i = *(_DWORD *)(i + 100) )
    {
      v6 = 8;
      if ( ((unsigned __int8)(1 << (*(unsigned __int16 *)(i + 24) % 8)) & *(_BYTE *)(a1
                                                                                   + ((int)*(unsigned __int16 *)(i + 24) >> 3)
                                                                                   + 2)) != 0 )
      {
        LOBYTE(v6) = *(unsigned __int16 *)(i + 24) % 8;
        v7 = Instance_ResolveSlotIndex(v6, a2);
        if ( v7 == -1 || (v8 = *(_BYTE **)(4 * v7 + *(_DWORD *)(i + 56)), (*(_DWORD *)v8 & 0x200) == 0) )
        {
          v11 = ((int)*(unsigned __int16 *)(i + 24) >> 3) + a1;
          *(_BYTE *)(v11 + 2) &= ~(1 << (*(unsigned __int16 *)(i + 24) % 8));
        }
        else
        {
          if ( (*v8 & 2) != 0 )
            *a3 = 1;
          Rules_UnionConstraints(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(i + 56) + 4 * v7) + 20), (int)v4);
          AST_DecrementNodeRefCount(v4);
          v4 = v9;
        }
      }
    }
    v13 += 4;
  }
  while ( v13 != 668 );
  return v4;
}
// 4D2EE2: variable 'v9' is possibly undefined
// 51AD68: using guessed type int dword_51AD68;

//----- (004D2F50) --------------------------------------------------------
int  Rules_AndClassBitmaps(int a1, unsigned __int16 *a2)
{
  int result; // eax
  int v5; // edx
  char v6; // ch

  result = ((int)*a2 >> 3) + 1;
  if ( (int)*a2 >> 3 != 0xFFFF )
  {
    do
    {
      v5 = a1 + (unsigned __int16)result;
      v6 = *((_BYTE *)a2 + (unsigned __int16)result-- + 1) & *(_BYTE *)(v5 + 1);
      *(_BYTE *)(v5 + 1) = v6;
    }
    while ( (_WORD)result );
  }
  return result;
}

//----- (004D2FA0) --------------------------------------------------------
int  Rules_OrClassBitmaps(int a1, unsigned __int16 *a2)
{
  int result; // eax
  int v5; // edx
  char v6; // ch

  result = ((int)*a2 >> 3) + 1;
  if ( (int)*a2 >> 3 != 0xFFFF )
  {
    do
    {
      v5 = a1 + (unsigned __int16)result;
      v6 = *((_BYTE *)a2 + (unsigned __int16)result-- + 1) | *(_BYTE *)(v5 + 1);
      *(_BYTE *)(v5 + 1) = v6;
    }
    while ( (_WORD)result );
  }
  return result;
}

//----- (004D2FF0) --------------------------------------------------------
_WORD * Rules_TrimClassBitmapToHighestBit(_WORD *result)
{
  _DWORD *v1; // ebp
  unsigned __int16 i; // bx
  int v3; // ebx
  int v4; // ecx

  v1 = result;
  for ( i = *result; i; --i )
  {
    if ( ((unsigned __int8)(1 << (i % 8)) & *((_BYTE *)result + ((int)i >> 3) + 2)) != 0 )
      break;
  }
  if ( i != (unsigned __int16)*result )
  {
    v3 = Rules_AllocateClassBitmap(i, 0);
    qmemcpy((void *)(v3 + 2), (char *)v1 + 2, ((v4 - (__CFSHL__(v4 >> 31, 3) + 8 * (v4 >> 31))) >> 3) + 1);
    Mem_SmallBlockFree(v1, ((int)*(unsigned __int16 *)v1 >> 3) + 3);
    return (_WORD *)v3;
  }
  return result;
}
// 4D3071: variable 'v4' is possibly undefined

//----- (004D30C0) --------------------------------------------------------
int  Rules_ExtractObjectPatternRestrictionNodes(int a1, int a2, _DWORD *a3, int a4, int *a5)
{
  _DWORD *v6; // eax
  int *v7; // ecx
  int v8; // eax
  int v9; // edx
  int v10; // edx

  *a3 = 0;
  *a5 = 0;
  v6 = (_DWORD *)AST_AllocNode();
  *(_DWORD *)a4 = v6;
  *v6 = 17;
  *(_DWORD *)(*(_DWORD *)a4 + 36) = g_Symbol_IsA;
  *(_DWORD *)(*(_DWORD *)a4 + 40) = 0;
  *(_DWORD *)(*(_DWORD *)a4 + 32) = 1;
  *(_DWORD *)(*(_DWORD *)a4 + 24) = a1;
  *(_DWORD *)(*(_DWORD *)a4 + 60) = *(_DWORD *)(a2 + 60);
  v8 = a2;
  *(_DWORD *)(a2 + 60) = 0;
  do
  {
    v9 = *(_DWORD *)(v8 + 36);
    if ( v9 == g_Symbol_IsA )
    {
      *v7 = v8;
    }
    else if ( v9 == g_Clips_NameSymbol )
    {
      *a5 = v8;
    }
    v10 = v8;
    v8 = *(_DWORD *)(v8 + 64);
  }
  while ( v8 );
  if ( !v10 )
    return *(_DWORD *)a4;
  *(_DWORD *)(v10 + 64) = *(_DWORD *)a4;
  return a2;
}
// 4D3150: variable 'v7' is possibly undefined
// 54E6F8: using guessed type int dword_54E6F8;
// 54E6FC: using guessed type int dword_54E6FC;

//----- (004D3170) --------------------------------------------------------
int  Rules_BuildAttributeIndexBitmap(int a1)
{
  int v1; // esi
  int i; // ebx
  int v3; // ebp
  _BYTE *v4; // edi
  _WORD *v5; // ecx
  int j; // ebx
  _BYTE *v7; // esi
  int v8; // ecx

  v1 = a1;
  for ( i = -1; a1; a1 = *(_DWORD *)(a1 + 64) )
  {
    if ( i < *(_DWORD *)(a1 + 40) )
      i = *(_DWORD *)(a1 + 40);
  }
  if ( (unsigned int)i < 2 )
    return 0;
  v3 = ((i - (__CFSHL__(i >> 31, 3) + 8 * (i >> 31))) >> 3) + 3;
  v4 = Mem_SmallBlockAlloc(v3);
  Mem_AllocArray(v4, v3);
  *v5 = i;
  for ( j = v1; j; j = *(_DWORD *)(j + 64) )
  {
    v7 = &v4[(*(_DWORD *)(j + 40) - (__CFSHL__(*(int *)(j + 40) >> 31, 3) + 8 * (*(int *)(j + 40) >> 31))) >> 3];
    v7[2] |= 1 << (*(_DWORD *)(j + 40) % 8);
  }
  Rules_AddBitmapValue(v4, ((int)*(unsigned __int16 *)v4 >> 3) + 3);
  Mem_SmallBlockFree(v4, v3);
  return v8;
}
// 4D3191: simplified comparisons for 'ebx.4': ==0 || ==1 became <2u
// 4D31C6: variable 'v5' is possibly undefined
// 4D3237: variable 'v8' is possibly undefined

//----- (004D3250) --------------------------------------------------------
int  Rules_PruneEmptyObjectPatternNodes(int a1, _DWORD *a2)
{
  int v3; // ecx
  int v4; // esi
  int v5; // ebx
  int v6; // edx
  int v8; // ecx
  int v9; // ecx
  int v10; // eax

  v3 = a1;
  v4 = a1;
  v5 = 0;
  if ( !a1 )
    return v4;
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
                v6 = *(_DWORD *)(v3 + 60);
                if ( v6 )
                {
                  *a2 = v6;
                  v5 = v3;
                  v3 = *(_DWORD *)(v3 + 64);
                  goto LABEL_9;
                }
                if ( *(_DWORD *)v3 != 17 && *(_DWORD *)v3 != 15 || *(_DWORD *)(v3 + 52) )
                  break;
                if ( v5 )
                  *(_DWORD *)(v5 + 64) = *(_DWORD *)(v3 + 64);
                else
                  v4 = *(_DWORD *)(v3 + 64);
                *(_DWORD *)(v3 + 64) = 0;
                AST_FreeNode(v3);
                if ( !v5 )
                  goto LABEL_24;
                v3 = *(_DWORD *)(v5 + 64);
LABEL_9:
                if ( !v3 )
                  return v4;
              }
              if ( *(_DWORD *)v3 != 18 && *(_DWORD *)v3 != 16
                || (*(_BYTE *)(v3 + 8) & 4) != 0
                || *(_DWORD *)(v3 + 52)
                || (*(_DWORD *)(v3 + 8) & 0x3F8000) != 0
                || (*(_WORD *)(v3 + 10) & 0x1FC0) != 0 )
              {
                break;
              }
              if ( v5 )
                *(_DWORD *)(v5 + 64) = *(_DWORD *)(v3 + 64);
              else
                v4 = *(_DWORD *)(v3 + 64);
              *(_DWORD *)(v3 + 64) = 0;
              AST_FreeNode(v3);
              if ( !v5 )
                goto LABEL_24;
              v3 = *(_DWORD *)(v5 + 64);
              if ( !v3 )
                return v4;
            }
            if ( *(_DWORD *)v3 != 18 && *(_DWORD *)v3 != 16
              || (*(_BYTE *)(v3 + 8) & 4) != 0
              || !*(_DWORD *)(v3 + 52)
              || (*(_DWORD *)(v3 + 8) & 0x3F8000) != 0
              || (*(_WORD *)(v3 + 10) & 0x1FC0) != 0 )
            {
              break;
            }
            *(_DWORD *)v3 = 17;
            v5 = v3;
            v3 = *(_DWORD *)(v3 + 64);
            if ( !v3 )
              return v4;
          }
          if ( *(_DWORD *)v3 != 18 || (*(_BYTE *)(v3 + 8) & 4) == 0 || *(_DWORD *)(v3 + 68) )
            break;
          *(_DWORD *)v3 = 17;
          Rules_AppendMultifieldWildcardBitmapTest(v3, 0);
          *(_BYTE *)(v8 + 8) &= ~4u;
LABEL_44:
          v5 = v8;
          v3 = *(_DWORD *)(v8 + 64);
          if ( !v3 )
            return v4;
        }
        if ( *(_DWORD *)v3 == 18 && (*(_BYTE *)(v3 + 8) & 4) != 0 )
          break;
        v5 = v3;
        v3 = *(_DWORD *)(v3 + 64);
        if ( !v3 )
          return v4;
      }
      Rules_AppendFieldCardinalityBitmapTest(*(_DWORD **)(v3 + 68));
      v10 = Rules_PruneEmptyObjectPatternNodes(*(_DWORD *)(v9 + 68), (int)a2);
      *(_DWORD *)(v8 + 68) = v10;
      if ( v10 )
        goto LABEL_44;
      if ( v5 )
        *(_DWORD *)(v5 + 64) = *(_DWORD *)(v8 + 64);
      else
        v4 = *(_DWORD *)(v8 + 64);
      *(_DWORD *)(v8 + 64) = 0;
      AST_FreeNode(v8);
      if ( v5 )
        break;
LABEL_24:
      v3 = v4;
      if ( !v4 )
        return 0;
    }
    v3 = *(_DWORD *)(v5 + 64);
  }
  while ( v3 );
  return v4;
}
// 4D33BA: variable 'v8' is possibly undefined
// 4D33DD: variable 'v9' is possibly undefined

//----- (004D3430) --------------------------------------------------------
int Rules_CreateDefaultObjectPatternRestriction()
{
  int v0; // ecx
  _WORD *v1; // eax
  int v2; // ecx
  char *v3; // esi
  _WORD *v4; // ebx
  int v5; // edx
  int v6; // eax
  int v7; // ecx
  _DWORD *v8; // ecx
  int v9; // eax
  _DWORD *v10; // eax
  int v11; // ecx

  LOWORD(v0) = *((_WORD *)Class_LookupInScope(aInitialObjec_2) + 12);
  v1 = (_WORD *)Rules_AllocateClassBitmap(v0, 0);
  v3 = (char *)v1 + ((v2 - (__CFSHL__(v2 >> 31, 3) + 8 * (v2 >> 31))) >> 3);
  v3[2] |= 1 << (v2 % 8);
  v4 = Rules_TrimClassBitmapToHighestBit(v1);
  AST_AllocNode();
  LOWORD(v5) = *v4;
  v6 = Rules_AddBitmapValue(v4, v5 / 8 + 3);
  *(_DWORD *)(v7 + 60) = v6;
  ++*(_DWORD *)(v6 + 4);
  Mem_SmallBlockFree(v4, (unsigned __int16)*v4 / 8 + 3);
  *v8 = 17;
  v8[8] = 1;
  v9 = g_Clips_NameSymbol;
  v8[10] = 1;
  v8[9] = v9;
  v10 = (_DWORD *)AST_AllocNode();
  *(_DWORD *)(v11 + 68) = v10;
  *v10 = 8;
  *(_DWORD *)(*(_DWORD *)(v11 + 68) + 4) = g_Rules_InitialObjectSymbol;
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
int  Rules_ParseActionExpressionList(int a1, int a2)
{
  int v4; // edx
  int v5; // ecx
  unsigned int *v6; // edx
  char *v8; // [esp+0h] [ebp-14h]

  Rules_IncrementIndentDepth(3);
  AST_Append(v5, v4);
  *(_DWORD *)(a1 + 6) = Parser_ParseProgram(a2, v6, 1);
  IO_OutNewline();
  IO_OutNewline();
  IO_OutWriteToken(v8);
  Rules_DecrementIndentDepth(3);
  if ( *(_DWORD *)(a1 + 6) )
    return a1;
  AST_Free(a1);
  return 0;
}
// 4D351C: variable 'v5' is possibly undefined
// 4D351C: variable 'v4' is possibly undefined
// 4D3525: variable 'v6' is possibly undefined
// 4D353B: variable 'v8' is possibly undefined

//----- (004D3570) --------------------------------------------------------
int  Rules_SetObjectPatternNegatedFlag(int result, char a2)
{
  char v2; // bl

  v2 = *(_BYTE *)(result + 12);
  if ( (v2 & 8) != 0 )
  {
    *(_BYTE *)(result + 12) = v2 & 0xF7;
    *(_DWORD *)(result + 12) |= 8 * (a2 & 1);
  }
  return result;
}

//----- (004D35A0) --------------------------------------------------------
void  Rules_TriggerObjectPatternMatchForAll(double a1)
{
  _DWORD *v1; // ecx
  int v2; // ecx

  v1 = (_DWORD *)g_Clips_InstanceListHead;
  if ( g_Clips_InstanceListHead )
  {
    do
    {
      Rules_ObjectMatchAction((unsigned __int16 *)1, v1, -1, a1);
      v1 = *(_DWORD **)(v2 + 68);
    }
    while ( v1 );
  }
}
// 4D35BE: variable 'v2' is possibly undefined
// 51AD0C: using guessed type int dword_51AD0C;

//----- (004D35E0) --------------------------------------------------------
signed int  Rules_ParseDefclass(char *a1, double a2)
{
  int *v3; // edi
  int v4; // ecx
  int v6; // ecx
  unsigned __int16 *v7; // eax
  unsigned __int16 *v8; // ecx
  int v9; // ebp
  char v10; // dl
  char v11; // dl
  int v12; // eax
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // edx
  int v23; // ecx
  int v24; // [esp+0h] [ebp-38h] BYREF
  int v25; // [esp+4h] [ebp-34h] BYREF
  int v26; // [esp+8h] [ebp-30h] BYREF
  int v27; // [esp+Ch] [ebp-2Ch] BYREF
  int v28; // [esp+10h] [ebp-28h] BYREF
  int v29; // [esp+14h] [ebp-24h]
  unsigned __int16 *v30; // [esp+18h] [ebp-20h]
  int v31; // [esp+1Ch] [ebp-1Ch]

  v3 = 0;
  v25 = 0;
  v26 = 0;
  v27 = 0;
  v28 = 1;
  Rules_SetPPBufferStatus(1);
  Rules_FlushPPBuffer();
  Rules_SetIndentDepth(3);
  IO_OutWriteToken(aDefclass_3);
  if ( Rules_IsBloaded() )
  {
    Rules_ReportCannotLoadWithBload();
    return 1;
  }
  v4 = Rules_GetConstructNameAndComment((int)a1, (int)&g_ParserCurrentTokenType, (int (*)(void))Class_LookupCurrentScopedName, aDefclass_4, 0, asc_50C9A0, 1, 1, 1);
  v29 = v4;
  if ( !v4 )
    return 1;
  if ( !Rules_ValidateClassRedefinition(v4, &v24) )
    return 1;
  v7 = (unsigned __int16 *)Class_ParseSuperclasses((int)a1, v6);
  v30 = v7;
  if ( !v7 )
    return 1;
  v9 = Class_BuildPrecedenceList(v24, v7);
  if ( !v9 )
  {
    Class_FreeOrRecycleArray(v8, 1);
    return 1;
  }
  Parser_NextToken((int)a1, (int)&g_ParserCurrentTokenType);
  v31 = 0;
  if ( g_ParserCurrentTokenType == 101 )
    goto LABEL_11;
  while ( 1 )
  {
    if ( g_ParserCurrentTokenType != 100
      || (IO_OutNewline(),
          AST_Append(v14, v13),
          IO_OutWriteToken(asc_50C9A4),
          Parser_NextToken((int)a1, v15),
          g_ParserCurrentTokenType != 2) )
    {
      Parser_ReportSyntaxError();
      v31 = 1;
      goto LABEL_11;
    }
    if ( !strcmp_(v16, aRole) )
    {
      if ( !Rules_ParseClassAttributeFlag((int)a1, (int)aRole, (int)aConcrete, &v25, &v26) )
      {
        v31 = 1;
        goto LABEL_11;
      }
      goto LABEL_44;
    }
    if ( !strcmp_(v17, aPatternMatch) )
    {
      if ( !Rules_ParseClassAttributeFlag((int)a1, (int)aPatternMatch, (int)aNonReactive, &v27, &v28) )
      {
        v31 = 1;
        goto LABEL_11;
      }
      goto LABEL_44;
    }
    if ( !strcmp_(v18, aSlot_6) )
    {
      v3 = Class_ParseSlot(a1, v3, 0, (unsigned __int16 *)v9, a2, 0);
      if ( !v3 )
      {
        v31 = 1;
        goto LABEL_11;
      }
      goto LABEL_44;
    }
    if ( !strcmp_(v19, aSingleSlot) )
    {
      v3 = Class_ParseSlot(a1, v3, 0, (unsigned __int16 *)v9, a2, 1);
      if ( !v3 )
      {
        v31 = 1;
        goto LABEL_11;
      }
      goto LABEL_44;
    }
    if ( !strcmp_(v20, aMultislot_0) )
    {
      v3 = Class_ParseSlot(a1, v3, 1, (unsigned __int16 *)v9, a2, 1);
      if ( !v3 )
      {
        v31 = 1;
        goto LABEL_11;
      }
      goto LABEL_44;
    }
    if ( strcmp_(v21, aMessageHandl_6) )
      break;
    if ( !Rules_SkipMessageHandlerBody((int)a1) )
    {
      v31 = 1;
      goto LABEL_11;
    }
LABEL_44:
    Parser_NextToken((int)a1, (int)&g_ParserCurrentTokenType);
    if ( g_ParserCurrentTokenType == 101 )
      goto LABEL_11;
  }
  Parser_ReportSyntaxError();
  v31 = v22;
LABEL_11:
  if ( g_ParserCurrentTokenType != 101 || v31 == 1 )
  {
    Class_FreeOrRecycleArray(v30, 1);
    Class_FreeOrRecycleArray((unsigned __int16 *)v9, 1);
    Class_DeleteSlotList((int)v3);
    return 1;
  }
  else
  {
    IO_OutWriteToken(asc_50CA24);
    if ( !v25 )
      v26 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v9 + 2) + 4) + 20) << 29 >> 31;
    if ( !v27 )
      v28 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v9 + 2) + 4) + 20) << 28 >> 31;
    if ( v26 && v28 )
    {
      Rules_PrintErrorID((int)aClasspsr, 1, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAnAbstractClas, v23);
      Class_FreeOrRecycleArray(v30, 1);
      Class_FreeOrRecycleArray((unsigned __int16 *)v9, 1);
      Class_DeleteSlotList((int)v3);
      return 1;
    }
    else
    {
      v24 = Class_AllocateRecord(v29);
      v10 = v26;
      *(_BYTE *)(v24 + 20) &= ~4u;
      *(_DWORD *)(v24 + 20) |= 4 * (v10 & 1);
      v11 = v28;
      *(_BYTE *)(v24 + 20) &= ~8u;
      *(_DWORD *)(v24 + 20) |= 8 * (v11 & 1);
      *(_WORD *)(v24 + 34) = *v30;
      *(_DWORD *)(v24 + 36) = *(_DWORD *)(v30 + 1);
      v12 = v24;
      **(_DWORD **)(v9 + 2) = v24;
      *(_WORD *)(v12 + 46) = *(_WORD *)v9;
      *(_DWORD *)(v24 + 48) = *(_DWORD *)(v9 + 2);
      g_ClipsMemFreeListTemp = (int)v30;
      *(_DWORD *)v30 = *(_DWORD *)(g_ClipsMemoryTable + 24);
      *(_DWORD *)(g_ClipsMemoryTable + 24) = g_ClipsMemFreeListTemp;
      g_ClipsMemFreeListTemp = v9;
      *(_DWORD *)v9 = *(_DWORD *)(g_ClipsMemoryTable + 24);
      *(_DWORD *)(g_ClipsMemoryTable + 24) = g_ClipsMemFreeListTemp;
      if ( v3 )
        Class_FlattenSlotLinksToArray(v24, v3);
      Rules_InstallDefclass(v24);
      return 0;
    }
  }
}
// 4D367E: variable 'v6' is possibly undefined
// 4D382E: variable 'v8' is possibly undefined
// 4D3847: variable 'v14' is possibly undefined
// 4D3847: variable 'v13' is possibly undefined
// 4D385D: variable 'v15' is possibly undefined
// 4D3878: variable 'v16' is possibly undefined
// 4D38DB: variable 'v17' is possibly undefined
// 4D3926: variable 'v18' is possibly undefined
// 4D3961: variable 'v19' is possibly undefined
// 4D399D: variable 'v20' is possibly undefined
// 4D39D8: variable 'v21' is possibly undefined
// 4D3A0D: variable 'v22' is possibly undefined
// 4D3A7F: variable 'v23' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E8FC: using guessed type int dword_54E8FC;
// 54E900: using guessed type int dword_54E900;

//----- (004D3AC0) --------------------------------------------------------
signed int __fastcall Rules_ValidateClassRedefinition(int a1, int *a2)
{
  int v2; // eax
  int v4; // ecx
  int *v5; // ecx
  int v6; // eax
  int v7; // ecx
  int v8; // ecx

  v2 = Class_LookupCurrentScopedName();
  *a2 = v2;
  if ( !v2 )
    return 1;
  if ( (*(_BYTE *)(v2 + 20) & 2) != 0 )
  {
    Rules_PrintErrorID((int)aClasspsr, 2, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotRedefi_0, v4);
    return 0;
  }
  else
  {
    if ( Class_IsDeletable() )
      return 1;
    Rules_PrintErrorID((int)aClasspsr, 3, 0);
    v6 = Rules_GetConstructNameString(*v5);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], v6, (int)g_IO_LogicalNameTable_WError[0]);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aClassCannotBeR, v7);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOutstandingRef, v8);
    return 0;
  }
}
// 4D3B01: variable 'v4' is possibly undefined
// 4D3B1C: variable 'v5' is possibly undefined
// 4D3B3C: variable 'v7' is possibly undefined
// 4D3B4B: variable 'v8' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004D3B60) --------------------------------------------------------
signed int  Rules_ParseClassAttributeFlag(int a1, int a2, int a3, _DWORD *a4, _DWORD *a5)
{
  int v7; // edx
  int v8; // ecx
  int v9; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx

  if ( *a4 )
  {
    Rules_PrintErrorID((int)aClasspsr, 4, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aClass_2, v11);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], a2, v12);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAlreadyDeclare, v13);
    return 0;
  }
  IO_OutWriteToken(asc_50CAF8);
  Parser_NextToken(a1, v7);
  if ( g_ParserCurrentTokenType == 2 )
  {
    if ( !strcmp_(v8, v8) )
    {
      *a5 = 1;
      goto LABEL_5;
    }
    if ( !strcmp_(v9, a3) )
    {
      *a5 = 0;
LABEL_5:
      Parser_NextToken(a1, (int)&g_ParserCurrentTokenType);
      if ( g_ParserCurrentTokenType == 101 )
      {
        *a4 = 1;
        return 1;
      }
    }
  }
  Parser_ReportSyntaxError();
  return 0;
}
// 4D3B80: variable 'v7' is possibly undefined
// 4D3B9C: variable 'v8' is possibly undefined
// 4D3BF3: variable 'v11' is possibly undefined
// 4D3BFF: variable 'v12' is possibly undefined
// 4D3C0E: variable 'v13' is possibly undefined
// 4D3C24: variable 'v9' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 54E8FC: using guessed type int dword_54E8FC;
// 54E900: using guessed type int dword_54E900;

//----- (004D3C50) --------------------------------------------------------
signed int  Rules_SkipMessageHandlerBody(int a1)
{
  int v2; // ebx
  int v3; // esi
  int *v4; // ecx
  int v5; // edx

  v2 = 1;
  v3 = 0;
LABEL_2:
  IO_OutWriteToken(asc_50CAF8);
  while ( 1 )
  {
    Parser_NextToken(a1, (int)v4);
    v5 = *v4;
    if ( *v4 == 102 )
    {
      Parser_ReportSyntaxError();
      return 0;
    }
    if ( v5 == 100 )
    {
      v3 = 1;
      ++v2;
    }
    else
    {
      if ( v5 == 101 )
      {
        --v2;
        if ( !v3 )
        {
          IO_OutNewline();
          IO_OutNewline();
          IO_OutWriteToken(asc_50CB18);
        }
      }
      v3 = 0;
    }
    if ( v2 <= 0 )
      return 1;
    if ( !v3 )
      goto LABEL_2;
  }
}
// 4D3C70: variable 'v4' is possibly undefined

//----- (004D3CE0) --------------------------------------------------------
_DWORD * Rules_InstallDefclass(int a1)
{
  int v1; // eax
  unsigned int v2; // eax
  unsigned int v3; // ebx
  int v4; // ecx
  unsigned int v5; // esi
  int v6; // eax
  int v7; // ecx
  int v8; // ecx
  __int16 *v9; // ecx
  int v10; // ecx
  int v11; // ecx
  _DWORD *v12; // ecx
  int v13; // ecx
  int v14; // ecx
  char v15; // ah
  _DWORD *v16; // ecx
  _DWORD *v17; // ecx
  int v19; // ebx
  int v20; // esi
  char *v21; // eax
  signed int v22; // ecx

  v1 = Rules_GetConstructNameSymbol(a1);
  v2 = Class_HashClassName(v1);
  v3 = 0;
  *(_DWORD *)(v4 + 30) = v2;
  v5 = 0;
  Rules_GetConstructNameString(v4);
  v6 = Class_LookupCurrentScopedName();
  if ( v6 )
  {
    v19 = *(_DWORD *)(v6 + 20);
    v20 = v19;
    Class_DeleteRecursive(v6);
    v3 = (unsigned int)(v19 << 27) >> 31;
    v5 = (unsigned int)(v20 << 26) >> 31;
  }
  Class_AddToHashTable(v7);
  Rules_LinkClassToSuperclasses(v8);
  Class_SetInstallState(v9, 1);
  Rules_AppendConstructToModuleList(v10);
  Rules_BuildInheritedSlotArray(v11);
  Class_BuildSlotIndexMap(v12);
  Class_AssignID(v13);
  v15 = *(_BYTE *)(v14 + 20);
  if ( (v15 & 4) != 0 )
  {
    *(_BYTE *)(v14 + 20) = v15 & 0xCF;
  }
  else
  {
    if ( v3 )
      *(_BYTE *)(v14 + 20) = v15 | 0x10;
    if ( v5 )
      *(_BYTE *)(v14 + 20) |= 0x20u;
  }
  if ( !Mem_GetAllocFlag() )
  {
    v21 = Rules_CopyPPBuffer();
    Rules_ReplaceConstructPPForm(v22, (int)v21);
  }
  Class_BuildModuleScopeBitmap(v16);
  return Class_GenerateDefaultSlotHandlersAndFlag(v17);
}
// 4D3CF2: variable 'v4' is possibly undefined
// 4D3D09: variable 'v7' is possibly undefined
// 4D3D15: variable 'v8' is possibly undefined
// 4D3D1C: variable 'v9' is possibly undefined
// 4D3D23: variable 'v10' is possibly undefined
// 4D3D2A: variable 'v11' is possibly undefined
// 4D3D31: variable 'v12' is possibly undefined
// 4D3D38: variable 'v13' is possibly undefined
// 4D3D3D: variable 'v14' is possibly undefined
// 4D3DA1: variable 'v22' is possibly undefined
// 4D3D58: variable 'v16' is possibly undefined
// 4D3D5F: variable 'v17' is possibly undefined

//----- (004D3DC0) --------------------------------------------------------
unsigned __int16  Rules_LinkClassToSuperclasses(int a1)
{
  int v1; // ecx
  unsigned int v2; // esi
  int v3; // edi
  unsigned __int16 result; // ax
  int v5; // eax

  v1 = a1;
  v2 = 0;
  v3 = 0;
  result = *(_WORD *)(a1 + 34);
  if ( result )
  {
    do
    {
      v5 = *(_DWORD *)(v3 + *(_DWORD *)(v1 + 36));
      v3 += 4;
      ++v2;
      Class_InsertLinkEntry((unsigned __int16 *)(v5 + 40), v1, -1);
      result = *(_WORD *)(v1 + 34);
    }
    while ( v2 < result );
  }
  return result;
}
// 4D3DDB: variable 'v1' is possibly undefined

//----- (004D3E10) --------------------------------------------------------
_DWORD * Rules_BuildInheritedSlotArray(int a1)
{
  unsigned int v2; // ebp
  int *v3; // esi
  _DWORD *result; // eax
  unsigned int v5; // edx
  int v6; // ebp
  int *v7; // eax
  _BYTE *v8; // ebx
  unsigned int v9; // [esp+0h] [ebp-24h] BYREF
  _DWORD *v10; // [esp+4h] [ebp-20h]
  int v11; // [esp+8h] [ebp-1Ch]

  v9 = 0;
  v2 = 1;
  v3 = Class_AppendNonPrivateSlotLinks(0, a1, 0, &v9);
  v11 = 4;
  while ( v2 < *(unsigned __int16 *)(a1 + 46) )
  {
    ++v2;
    v3 = Class_AppendNonPrivateSlotLinks(v3, *(_DWORD *)(v11 + *(_DWORD *)(a1 + 48)), 1, &v9);
    v11 += 4;
  }
  result = (_DWORD *)v9;
  *(_DWORD *)(a1 + 68) = 0;
  *(_DWORD *)(a1 + 72) = result;
  if ( v9 )
  {
    result = Mem_SmallBlockAlloc(4 * v9);
    *(_DWORD *)(a1 + 56) = result;
  }
  v5 = 0;
  if ( v9 )
  {
    v6 = 0;
    do
    {
      v10 = (_DWORD *)(v6 + *(_DWORD *)(a1 + 56));
      v7 = v3;
      v8 = (_BYTE *)*v3;
      v3 = (int *)v3[1];
      *v10 = v8;
      if ( (*v8 & 1) == 0 )
        ++*(_DWORD *)(a1 + 68);
      g_ClipsMemFreeListTemp = (int)v7;
      *v7 = *(_DWORD *)(g_ClipsMemoryTable + 32);
      result = (_DWORD *)g_ClipsMemoryTable;
      *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
      ++v5;
      v6 += 4;
    }
    while ( v5 < v9 );
  }
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004D3F00) --------------------------------------------------------
_DWORD * Class_BuildSlotIndexMap(_DWORD *result)
{
  _DWORD *v1; // edx
  int v2; // ecx
  unsigned int v3; // ecx
  int v4; // eax
  unsigned int v5; // esi
  _DWORD *v6; // eax
  _DWORD *v7; // edx
  unsigned int v8; // ecx
  int v9; // eax
  int v10; // ecx

  v1 = result;
  result[19] = 0;
  v2 = result[18];
  result[15] = 0;
  if ( v2 )
  {
    v3 = 0;
    if ( result[18] )
    {
      v4 = 0;
      do
      {
        v5 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v1[14] + v4) + 8) + 8);
        if ( v5 > v1[19] )
          v1[19] = v5;
        ++v3;
        v4 += 4;
      }
      while ( v3 < v1[18] );
    }
    v6 = Mem_SmallBlockAlloc(4 * (v1[19] + 1));
    v7[15] = v6;
    v8 = 0;
    v9 = 0;
    do
    {
      *(_DWORD *)(v7[15] + v9) = 0;
      ++v8;
      v9 += 4;
    }
    while ( v8 <= v7[19] );
    result = 0;
    if ( v7[18] )
    {
      v10 = 0;
      do
      {
        result = (_DWORD *)((char *)result + 1);
        *(_DWORD *)(v7[15] + 4 * *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v10 + v7[14]) + 8) + 8)) = result;
        v10 += 4;
      }
      while ( (unsigned int)result < v7[18] );
    }
  }
  return result;
}
// 4D3F5D: variable 'v7' is possibly undefined

//----- (004D3FC0) --------------------------------------------------------
int * Class_AppendNonPrivateSlotLinks(int *a1, int a2, int a3, _DWORD *a4)
{
  int v5; // ebp
  int v6; // edi
  int v7; // ebx
  int *i; // eax
  _DWORD *v9; // edx
  int *v10; // eax
  bool v14; // [esp+8h] [ebp-10h]

  v5 = *(_DWORD *)(a2 + 64) - 1;
  if ( v5 >= 0 )
  {
    v14 = a3 == 0;
    v6 = 44 * v5;
    do
    {
      v7 = v6 + *(_DWORD *)(a2 + 52);
      if ( (*(_BYTE *)v7 & 8) == 0 || v14 )
      {
        for ( i = a1; i; i = (int *)i[1] )
        {
          if ( *(_DWORD *)(v7 + 8) == *(_DWORD *)(*i + 8) )
            break;
        }
        if ( !i )
        {
          v9 = *(_DWORD **)(g_ClipsMemoryTable + 32);
          if ( v9 )
          {
            g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
            *(_DWORD *)(g_ClipsMemoryTable + 32) = *v9;
            v10 = (int *)g_ClipsMemFreeListTemp;
          }
          else
          {
            v10 = (int *)Mem_HeapAllocWithRetry((_DWORD *)8);
          }
          *v10 = v7;
          v10[1] = (int)a1;
          a1 = v10;
          ++*a4;
        }
      }
      v6 -= 44;
      --v5;
    }
    while ( v6 >= 0 );
  }
  return a1;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004D4070) --------------------------------------------------------
_DWORD * Class_FlattenSlotLinksToArray(int a1, int *a2)
{
  int *i; // edi
  _DWORD *result; // eax
  int v5; // ebp
  int v6; // edx
  int *v7; // ebp
  const void *v8; // esi
  _DWORD *v9; // [esp+0h] [ebp-1Ch]
  int *v10; // [esp+4h] [ebp-18h]

  for ( i = a2; a2; a2 = (int *)a2[1] )
  {
    *(_DWORD *)(*a2 + 4) = a1;
    ++*(_DWORD *)(a1 + 64);
  }
  v10 = i;
  v9 = 0;
  result = Mem_SmallBlockAlloc(44 * *(_DWORD *)(a1 + 64));
  v5 = *(_DWORD *)(a1 + 64);
  *(_DWORD *)(a1 + 52) = result;
  if ( v5 )
  {
    v6 = 0;
    do
    {
      v7 = v10;
      v8 = (const void *)*v10;
      v10 = (int *)v10[1];
      qmemcpy((void *)(v6 + *(_DWORD *)(a1 + 52)), v8, 0x2Cu);
      *(_DWORD *)(v6 + *(_DWORD *)(a1 + 52) + 32) = v6 + *(_DWORD *)(a1 + 52);
      *(_DWORD *)(v6 + *(_DWORD *)(a1 + 52) + 40) = 0;
      g_ClipsMemFreeListTemp = *v7;
      *(_DWORD *)g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 176);
      *(_DWORD *)(g_ClipsMemoryTable + 176) = g_ClipsMemFreeListTemp;
      g_ClipsMemFreeListTemp = (int)v7;
      *v7 = *(_DWORD *)(g_ClipsMemoryTable + 32);
      result = (_DWORD *)((char *)v9 + 1);
      *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
      v6 += 44;
      v9 = result;
    }
    while ( (unsigned int)result < *(_DWORD *)(a1 + 64) );
  }
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004D4170) --------------------------------------------------------
signed int  Class_BuildModuleScopeBitmap(_DWORD *a1)
{
  int v1; // eax
  int i; // edi
  int v3; // esi
  _DWORD *v4; // ecx
  _BYTE *v5; // ebx
  int v6; // eax
  int v8; // [esp+4h] [ebp-28h]
  _BYTE *v10; // [esp+Ch] [ebp-20h]
  _BYTE *v11; // [esp+10h] [ebp-1Ch]

  v10 = *(_BYTE **)(*a1 + 16);
  v1 = Module_GetModuleCount();
  v8 = ((v1 - (__CFSHL__(v1 >> 31, 3) + 8 * (v1 >> 31))) >> 3) + 1;
  v11 = Mem_SmallBlockAlloc(v8);
  Mem_AllocArray(v11, v8);
  Module_BeginEnum();
  for ( i = Module_NextEnum(0); i; i = Module_NextEnum(i) )
  {
    Module_SetCurrent(i);
    v3 = *(_DWORD *)(i + 24);
    if ( Rules_FindImportExportConstruct(aDefclass_4, v4, v10, 1, 0) )
    {
      v5 = &v11[(v3 - (__CFSHL__(v3 >> 31, 3) + 8 * (v3 >> 31))) >> 3];
      *v5 |= 1 << (v3 % 8);
    }
  }
  Module_EndEnum();
  v6 = Rules_AddBitmapValue(v11, v8);
  a1[26] = v6;
  ++*(_DWORD *)(v6 + 4);
  return Mem_SmallBlockFree(v11, v8);
}
// 4D41E6: variable 'v4' is possibly undefined

//----- (004D4260) --------------------------------------------------------
_DWORD * Class_GenerateDefaultSlotHandlersAndFlag(_DWORD *result)
{
  _DWORD *v1; // edx
  int v2; // ebx
  unsigned int v3; // ecx
  unsigned int v4; // ebx
  int v5; // ecx

  v1 = result;
  if ( result[16] )
  {
    v2 = 0;
    do
    {
      result = (_DWORD *)Class_GeneratePublicSlotHandlers(v2 + v1[13]);
      v2 += 44;
    }
    while ( v3 < v1[16] );
  }
  v4 = 0;
  if ( v1[24] )
  {
    v5 = 0;
    do
    {
      result = (_DWORD *)v1[22];
      LOBYTE(result[v5]) |= 1u;
      ++v4;
      v5 += 9;
    }
    while ( v4 < v1[24] );
  }
  return result;
}
// 4D4273: variable 'v1' is possibly undefined
// 4D4286: variable 'v3' is possibly undefined

//----- (004D42C0) --------------------------------------------------------
int  Class_BrowseClassesCommand(int a1, double a2)
{
  int *v2; // eax
  int result; // eax
  int v4; // ecx
  int v5; // [esp-8h] [ebp-24h] BYREF
  int v6; // [esp+0h] [ebp-1Ch]
  int v7; // [esp+14h] [ebp-8h]

  v7 = a1;
  if ( !Rules_RtnArgCount() )
  {
    v2 = Class_LookupByQualifiedName(aObject_1);
    return Class_PrintClassBrowse((int)g_IO_LogicalName_WDisplay, (int)v2, 0);
  }
  result = Lexer_ParseValueList(1, &v5, 2, a2);
  if ( result )
  {
    v2 = Class_LookupByQualifiedName(*(_BYTE **)(v6 + 16));
    if ( !v2 )
      return Class_ReportLookupError(v4, *(_DWORD *)(v6 + 16));
    return Class_PrintClassBrowse((int)g_IO_LogicalName_WDisplay, (int)v2, 0);
  }
  return result;
}
// 4D4327: variable 'v4' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (004D4350) --------------------------------------------------------
int * Class_DescribeClassCommand(int a1, double a2)
{
  int *result; // eax
  int v3; // ecx

  result = (int *)Class_ParseClassNameArg(a1, a2);
  if ( result )
  {
    result = Class_LookupClassOrReportError(v3, result);
    if ( result )
      return (int *)Class_PrintClassDescription((int)g_IO_LogicalName_WDisplay, (int)result);
  }
  return result;
}
// 4D4368: variable 'v3' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (004D4390) --------------------------------------------------------
signed int  Class_PrintClassDescription(int a1, int a2)
{
  int v4; // ecx
  char *v5; // edx
  int v6; // ebp
  int v7; // edi
  unsigned int v8; // ebx
  int v9; // edx
  unsigned int v10; // kr04_4
  int v11; // ecx
  unsigned int v12; // kr08_4
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v17; // ecx
  int v18; // edx
  char v19[84]; // [esp+0h] [ebp-88h] BYREF
  char v20[12]; // [esp+54h] [ebp-34h] BYREF
  char v21[12]; // [esp+60h] [ebp-28h] BYREF
  int v22; // [esp+6Ch] [ebp-1Ch]
  int v23; // [esp+70h] [ebp-18h]

  v22 = a1;
  Class_PrintSeparatorLine(a1, (int)v19, 61, 82);
  Class_PrintSeparatorLine(v22, (int)v19, 42, 82);
  if ( (*(_BYTE *)(a2 + 20) & 4) != 0 )
  {
    v5 = aAbstractDirect;
  }
  else
  {
    Output_Write(v22, (int)aConcreteDirect, v4);
    if ( (*(_BYTE *)(a2 + 20) & 8) != 0 )
      v5 = aReactiveDirect;
    else
      v5 = aNonReactiveDir;
  }
  Output_Write(v22, (int)v5, v4);
  Class_PrintNameList(v22, (int)aDirectSupercla, (unsigned __int16 *)(a2 + 34));
  Class_PrintNameList(v22, (int)aInheritancePre, (unsigned __int16 *)(a2 + 46));
  Class_PrintNameList(v22, (int)aDirectSubclass, (unsigned __int16 *)(a2 + 40));
  if ( *(_DWORD *)(a2 + 56) )
  {
    v6 = 8;
    Class_PrintSeparatorLine(v22, (int)v19, 45, 82);
    v7 = *(_DWORD *)(a2 + 72);
    v8 = 0;
    v23 = 5;
    if ( v7 )
    {
      v9 = 0;
      do
      {
        v10 = strlen(*(const char **)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(a2 + 56) + v9) + 8) + 12) + 16))
            + 1;
        if ( (int)(v10 - 1) > v23 )
          v23 = v10 - 1;
        v11 = *(_DWORD *)(*(_DWORD *)(a2 + 56) + v9);
        if ( (*(_BYTE *)v11 & 0x10) == 0 )
        {
          v12 = strlen(*(const char **)(*(_DWORD *)(v11 + 12) + 16)) + 1;
          if ( (int)(v12 - 1) > v6 )
            v6 = v12 - 1;
        }
        ++v8;
        v9 += 4;
      }
      while ( v8 < *(_DWORD *)(a2 + 72) );
    }
    if ( v23 > 16 )
      v23 = 16;
    if ( v6 > 12 )
      v6 = 12;
    sprintf_(v20, "%%-%d.%ds : ", v23, v23);
    sprintf_(v21, "%%-%d.%ds ", v6, v6);
    Class_PrintSlotBasicInfoTable(v22, v20, v19, v21, a2);
    Output_Write(v22, (int)aConstraintInfo, 82);
    Class_PrintSlotConstraintTable(v22, v20, v13, v19, a2);
  }
  if ( *(_DWORD *)(a2 + 96) )
  {
LABEL_19:
    Class_PrintSeparatorLine(v22, (int)v19, 45, 82);
    Output_Write(v22, (int)aRecognizedMess, v14);
    MessageHandler_CountAndPrintHandlers(v22, (unsigned __int16 *)(a2 + 46), v15, 0);
  }
  else
  {
    v17 = 1;
    v18 = 4;
    while ( v17 < *(unsigned __int16 *)(a2 + 46) )
    {
      if ( *(_DWORD *)(*(_DWORD *)(v18 + *(_DWORD *)(a2 + 48)) + 96) )
        goto LABEL_19;
      v18 += 4;
      ++v17;
    }
  }
  Class_PrintSeparatorLine(v22, (int)v19, 42, 82);
  return Class_PrintSeparatorLine(v22, (int)v19, 61, 82);
}
// 4D43D9: variable 'v4' is possibly undefined
// 4D4527: variable 'v13' is possibly undefined
// 4D4550: variable 'v14' is possibly undefined
// 4D455E: variable 'v15' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (004D45E0) --------------------------------------------------------
char * Class_SlotAccessModeString(int a1)
{
  char v1; // bl
  char v2; // cl

  v1 = *(_BYTE *)(a1 + 1);
  if ( (v1 & 8) != 0 && (v1 & 0x10) != 0 )
    return aRw_0;
  v2 = *(_BYTE *)(a1 + 1);
  if ( (v2 & 8) == 0 && (v2 & 0x10) == 0 )
    return aNil_6;
  if ( (*(_BYTE *)(a1 + 1) & 8) != 0 )
    return aR_6;
  return aW_6;
}

//----- (004D4630) --------------------------------------------------------
int __thiscall Class_DefclassModuleCommand(void *this)
{
  return Rules_GetConstructModuleCommand((int)this, (const char **)g_ClipsDefclassConstructType);
}
// 54E6B8: using guessed type int dword_54E6B8;

//----- (004D4650) --------------------------------------------------------
signed int  Class_SuperclassPCommand(double a1)
{
  signed int result; // eax
  int *v2; // [esp+0h] [ebp-10h] BYREF
  int *v3; // [esp+4h] [ebp-Ch] BYREF

  result = Class_ParseTwoClassNameArgs(&v2, &v3, a1);
  if ( result )
    return Class_HasSuperclass((int)v3, (int)v2);
  return result;
}

//----- (004D46A0) --------------------------------------------------------
signed int  Class_SubclassPCommand(double a1)
{
  signed int result; // eax
  int *v2; // [esp+0h] [ebp-10h] BYREF
  int *v3; // [esp+4h] [ebp-Ch] BYREF

  result = Class_ParseTwoClassNameArgs(&v2, &v3, a1);
  if ( result )
    return Class_HasSuperclass((int)v2, (int)v3);
  return result;
}

//----- (004D46F0) --------------------------------------------------------
signed int  Class_SlotExistPCommand(int *a1, double a2)
{
  signed int result; // eax
  int v3; // esi
  signed int v4; // edi
  int v5; // ecx
  int v6; // [esp-8h] [ebp-30h] BYREF
  int *v7[6]; // [esp+10h] [ebp-18h] BYREF

  v7[4] = a1;
  result = Class_CheckSlotExists((int)aSlotExistp_0, v7, 1, 0, a2);
  v3 = 0;
  v4 = result;
  if ( result )
  {
    if ( Rules_RtnArgCount() == 3 )
    {
      result = Lexer_ParseValueList(3, &v6, 2, a2);
      if ( !result )
        return result;
      if ( strcmp_(v5, aInherit_0) )
      {
        Parser_ReportError(3, (int)aKeywordInher_0);
        Lexer_ErrorRecover(1);
        return 0;
      }
      v3 = 1;
    }
    if ( v7[0] == *(int **)(v4 + 4) )
      return 1;
    else
      return v3;
  }
  return result;
}
// 4D4762: variable 'v5' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004D47C0) --------------------------------------------------------
signed int  Class_MessageHandlerExistPCommand(double a1)
{
  signed int v1; // esi
  signed int result; // eax
  int v3; // ecx
  int *v4; // edi
  int v5; // ebp
  _DWORD v6[2]; // [esp+0h] [ebp-30h] BYREF
  int v7; // [esp+8h] [ebp-28h]

  v1 = 2;
  result = Lexer_ParseValueList(1, v6, 2, a1);
  if ( result )
  {
    v4 = Class_LookupByQualifiedName(*(_BYTE **)(v7 + 16));
    if ( !v4 )
    {
      Class_ReportLookupError(v3, *(_DWORD *)(v7 + 16));
      return 0;
    }
    result = Lexer_ParseValueList(2, v6, 2, a1);
    if ( result )
    {
      v5 = v7;
      if ( Rules_RtnArgCount() == 3 )
      {
        result = Lexer_ParseValueList(3, v6, 2, a1);
        if ( !result )
          return result;
        v1 = MessageHandler_TypeIndexFromKeyword((int)aMessageHandl_8);
        if ( v1 == 4 )
        {
          Lexer_ErrorRecover(1);
          return 0;
        }
      }
      result = (signed int)Class_FindMessageHandler(v4, v5, v1);
      if ( result )
        return 1;
    }
  }
  return result;
}
// 4D482B: variable 'v3' is possibly undefined

//----- (004D48B0) --------------------------------------------------------
_BYTE * Class_SlotWritablePCommand(int *a1, double a2)
{
  _BYTE *result; // eax
  int *v3[4]; // [esp-Ch] [ebp-10h] BYREF

  v3[2] = a1;
  result = (_BYTE *)Class_CheckSlotExists((int)aSlotWritable_0, v3, 1, 1, a2);
  if ( result )
    return (_BYTE *)((*result & 0x10) == 0);
  return result;
}

//----- (004D4910) --------------------------------------------------------
_BYTE * Class_SlotInitablePCommand(int *a1, double a2)
{
  _BYTE *result; // eax
  int *v3[4]; // [esp-Ch] [ebp-10h] BYREF

  v3[2] = a1;
  result = (_BYTE *)Class_CheckSlotExists((int)aSlotInitable_0, v3, 1, 1, a2);
  if ( result )
    return (_BYTE *)((*result & 0x10) == 0 || (*result & 0x20) != 0);
  return result;
}

//----- (004D4980) --------------------------------------------------------
signed int  Class_SlotPublicPCommand(int *a1, double a2)
{
  signed int result; // eax
  int *v3[4]; // [esp-Ch] [ebp-10h] BYREF

  v3[2] = a1;
  result = Class_CheckSlotExists((int)aSlotPublicp_0, v3, 0, 1, a2);
  if ( result )
    return (*(_BYTE *)(result + 1) & 4) != 0;
  return result;
}

//----- (004D49E0) --------------------------------------------------------
signed int  Class_SlotDirectAccessPCommand(int *a1, double a2)
{
  signed int result; // eax
  int *v3[4]; // [esp+0h] [ebp-10h] BYREF

  v3[2] = a1;
  result = Class_CheckSlotExists((int)aSlotDirectAc_0, v3, 1, 1, a2);
  if ( result )
    return (*(_BYTE *)(result + 1) & 4) != 0 || v3[0] == *(int **)(result + 4);
  return result;
}

//----- (004D4A50) --------------------------------------------------------
signed int  Class_ClassExistPCommand(int a1, double a2)
{
  signed int result; // eax
  _DWORD v3[9]; // [esp-8h] [ebp-24h] BYREF

  v3[7] = a1;
  result = Lexer_ParseValueList(1, v3, 2, a2);
  if ( result )
    return Class_LookupByQualifiedName(*(_BYTE **)(v3[2] + 16)) != 0;
  return result;
}

//----- (004D4AA0) --------------------------------------------------------
signed int  Class_ParseTwoClassNameArgs(int **a1, int **a2, double a3)
{
  signed int result; // eax
  int *v5; // eax
  int v6; // ecx
  int *v7; // eax
  _DWORD v8[2]; // [esp+0h] [ebp-28h] BYREF
  int v9; // [esp+8h] [ebp-20h]

  result = Lexer_ParseValueList(1, v8, 2, a3);
  if ( result )
  {
    v5 = Class_LookupByQualifiedName(*(_BYTE **)(v9 + 16));
    *a1 = v5;
    if ( v5 )
    {
      result = Lexer_ParseValueList(2, v8, 2, a3);
      if ( !result )
        return result;
      v7 = Class_LookupByQualifiedName(*(_BYTE **)(v9 + 16));
      *a2 = v7;
      if ( v7 )
        return 1;
    }
    Class_ReportLookupError(v6, *(_DWORD *)(v9 + 16));
    return 0;
  }
  return result;
}
// 4D4B02: variable 'v6' is possibly undefined

//----- (004D4B30) --------------------------------------------------------
signed int  Class_CheckSlotExists(int a1, int **a2, int a3, int a4, double a5)
{
  signed int result; // eax
  unsigned int v10; // eax
  int v11; // ecx
  int *v12; // edx
  int v13; // edi
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx

  result = Class_ParseClassReference(a2, a3, a5);
  if ( result )
  {
    v10 = Instance_ResolveSlotIndex(result, result);
    if ( v10 == -1 )
    {
      if ( a4 )
      {
        Instance_ReportNoSuchSlotError(v11, a1);
        Lexer_ErrorRecover(1);
      }
      return 0;
    }
    else
    {
      v12 = *a2;
      v13 = *(_DWORD *)((*a2)[14] + 4 * v10);
      if ( v12 == *(int **)(v13 + 4) || a3 )
      {
        return v13;
      }
      else
      {
        Rules_PrintErrorID((int)aClassexm, 1, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInheritedSlot, v14);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(v15 + 16), v15);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFromClass, v16);
        Class_PrintName(*(_DWORD *)(v13 + 4), 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIsNotValidForF, v17);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], a1, v18);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_50CE14, v19);
        Lexer_ErrorRecover(1);
        return 0;
      }
    }
  }
  return result;
}
// 4D4B61: variable 'v11' is possibly undefined
// 4D4BA6: variable 'v14' is possibly undefined
// 4D4BB0: variable 'v15' is possibly undefined
// 4D4BC4: variable 'v16' is possibly undefined
// 4D4BE0: variable 'v17' is possibly undefined
// 4D4BEC: variable 'v18' is possibly undefined
// 4D4BFB: variable 'v19' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004D4C10) --------------------------------------------------------
int * Class_ResolveSlotBySymbolName(_BYTE *a1, int a2)
{
  int *result; // eax
  int v3; // ecx
  unsigned int v4; // eax
  int v5; // ecx

  result = Rules_FindSymbolEntry(a1);
  if ( result )
  {
    v4 = Instance_ResolveSlotIndex(v3, (int)result);
    if ( v4 == -1 )
      return 0;
    result = *(int **)(*(_DWORD *)(v5 + 56) + 4 * v4);
    if ( v5 != result[1] && !a2 )
      return 0;
  }
  return result;
}
// 4D4C24: variable 'v3' is possibly undefined
// 4D4C2E: variable 'v5' is possibly undefined

//----- (004D4C50) --------------------------------------------------------
int *__fastcall Class_LookupClassOrReportError(int a1, _BYTE *a2)
{
  int *result; // eax
  int v3; // ecx

  result = Class_LookupByQualifiedName(a2);
  if ( !result )
  {
    Class_ReportLookupError(v3, (int)a2);
    return 0;
  }
  return result;
}
// 4D4C68: variable 'v3' is possibly undefined

//----- (004D4C80) --------------------------------------------------------
signed int  Class_ParseClassNameArg(int a1, double a2)
{
  signed int result; // eax
  _DWORD v3[9]; // [esp-8h] [ebp-24h] BYREF

  v3[7] = a1;
  result = Lexer_ParseValueList(1, v3, 2, a2);
  if ( result )
    return *(_DWORD *)(v3[2] + 16);
  return result;
}

//----- (004D4CB0) --------------------------------------------------------
signed int  Class_PrintClassBrowse(int a1, int a2, unsigned int a3)
{
  int v3; // ecx
  unsigned int i; // esi
  int v6; // eax
  int v7; // ecx
  int v8; // ecx
  signed int result; // eax
  int v10; // ecx
  unsigned int v11; // edi
  int v12; // esi

  v3 = a1;
  for ( i = 0; i < a3; ++i )
    Output_Write(v3, (int)asc_50CE18, v3);
  v6 = Rules_GetConstructNameString(a2);
  Output_Write(v7, v6, v7);
  if ( *(_WORD *)(a2 + 34) > 1u )
    Output_Write(v8, (int)asc_50CE1C, v8);
  result = Output_Write(v8, (int)asc_50CE14, v8);
  v11 = 0;
  v12 = 0;
  while ( v11 < *(unsigned __int16 *)(a2 + 40) )
  {
    v12 += 4;
    ++v11;
    result = Class_PrintClassBrowse(v10, *(_DWORD *)(*(_DWORD *)(a2 + 42) + v12 - 4), a3 + 1);
  }
  return result;
}
// 4D4CCB: variable 'v3' is possibly undefined
// 4D4CEB: variable 'v7' is possibly undefined
// 4D4D24: variable 'v8' is possibly undefined
// 4D4D3B: variable 'v10' is possibly undefined

//----- (004D4D50) --------------------------------------------------------
signed int  Class_PrintSeparatorLine(int a1, int a2, char a3, int a4)
{
  int v5; // esi
  int v6; // ecx
  int i; // eax

  v5 = a2;
  v6 = a4 - 2;
  for ( i = 0; i < v6; *(_BYTE *)(a2 - 1) = a3 )
  {
    ++a2;
    ++i;
  }
  *(_BYTE *)(i + v5) = 10;
  *(_BYTE *)(v5 + i + 1) = 0;
  return Output_Write(a1, v5, v6);
}

//----- (004D4DA0) --------------------------------------------------------
int  Class_PrintSlotBasicInfoTable(
        int a1,
        const char *a2,
        const char *a3,
        const char *a4,
        int a5)
{
  char *v6; // esi
  const char *v7; // ecx
  const char *v8; // edi
  unsigned int v9; // kr04_4
  char *v10; // edi
  char v11; // al
  char v12; // al
  int v13; // ecx
  int v14; // ecx
  int result; // eax
  int v16; // ebx
  char *v17; // esi
  char *v18; // edi
  char v19; // al
  char v20; // al
  const char *v21; // edi
  char *v22; // esi
  char *v23; // edi
  char v24; // al
  char v25; // al
  char *v26; // esi
  char *v27; // edi
  char v28; // al
  char v29; // al
  char *v30; // esi
  char *v31; // edi
  char v32; // al
  char v33; // al
  char *v34; // esi
  char *v35; // edi
  char v36; // al
  char v37; // al
  char *v38; // esi
  char *v39; // edi
  char v40; // al
  char v41; // al
  char *v42; // esi
  char *v43; // edi
  char v44; // al
  char v45; // al
  char *v46; // esi
  char *v47; // edi
  char v48; // al
  char v49; // al
  char *v50; // edx
  char *v51; // esi
  char *v52; // edi
  char v53; // al
  char v54; // al
  char *v55; // esi
  char *v56; // edi
  char v57; // al
  char v58; // al
  char *v59; // esi
  char *v60; // edi
  char v61; // al
  char v62; // al
  char *v63; // esi
  unsigned int v64; // kr34_4
  char *v65; // edi
  char v66; // al
  char v67; // al
  char *v68; // esi
  int v69; // ecx
  int v70; // ecx
  int v73; // [esp+8h] [ebp-18h]
  unsigned int v74; // [esp+Ch] [ebp-14h]

  v6 = aFldDefPrpAccSt;
  sprintf_(a3, a2, aSlots_0);
  v8 = v7;
  v9 = strlen(v7) + 1;
  v10 = (char *)&v8[v9 - 1];
  do
  {
    v11 = *v6;
    *v10 = *v6;
    if ( !v11 )
      break;
    v12 = v6[1];
    v6 += 2;
    v10[1] = v12;
    v10 += 2;
  }
  while ( v12 );
  Output_Write(a1, (int)a3, ~v9);
  sprintf_(a3, a4, aOvrdMsg);
  Output_Write(a1, (int)a3, v13);
  Output_Write(a1, (int)aSourceS, v14);
  result = a5;
  v74 = 0;
  if ( *(_DWORD *)(a5 + 72) )
  {
    v73 = 0;
    do
    {
      v16 = *(_DWORD *)(v73 + *(_DWORD *)(a5 + 56));
      sprintf_(a3, a2, *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v16 + 8) + 12) + 16));
      if ( (*(_BYTE *)v16 & 2) != 0 )
        v17 = aMlt;
      else
        v17 = aSgl;
      v18 = (char *)&a3[strlen(a3)];
      do
      {
        v19 = *v17;
        *v18 = *v17;
        if ( !v19 )
          break;
        v20 = v17[1];
        v17 += 2;
        v18[1] = v20;
        v18 += 2;
      }
      while ( v20 );
      v21 = a3;
      if ( (*(_BYTE *)(v16 + 1) & 1) != 0 )
      {
        v22 = aNil_5;
      }
      else
      {
        if ( (*(_BYTE *)v16 & 0x40) != 0 )
          v22 = aDyn;
        else
          v22 = aStc;
        v21 = a3;
      }
      v23 = (char *)&v21[strlen(v21)];
      do
      {
        v24 = *v22;
        *v23 = *v22;
        if ( !v24 )
          break;
        v25 = v22[1];
        v22 += 2;
        v23[1] = v25;
        v23 += 2;
      }
      while ( v25 );
      if ( (*(_BYTE *)v16 & 8) != 0 )
        v26 = aNil_5;
      else
        v26 = aInh;
      v27 = (char *)&a3[strlen(a3)];
      do
      {
        v28 = *v26;
        *v27 = *v26;
        if ( !v28 )
          break;
        v29 = v26[1];
        v26 += 2;
        v27[1] = v29;
        v27 += 2;
      }
      while ( v29 );
      if ( (*(_BYTE *)v16 & 0x20) != 0 )
      {
        v30 = aInt_0;
      }
      else if ( (*(_BYTE *)v16 & 0x10) != 0 )
      {
        v30 = aR_5;
      }
      else
      {
        v30 = aRw;
      }
      v31 = (char *)&a3[strlen(a3)];
      do
      {
        v32 = *v30;
        *v31 = *v30;
        if ( !v32 )
          break;
        v33 = v30[1];
        v30 += 2;
        v31[1] = v33;
        v31 += 2;
      }
      while ( v33 );
      if ( (*(_BYTE *)v16 & 1) != 0 )
        v34 = aShr;
      else
        v34 = aLcl;
      v35 = (char *)&a3[strlen(a3)];
      do
      {
        v36 = *v34;
        *v35 = *v34;
        if ( !v36 )
          break;
        v37 = v34[1];
        v34 += 2;
        v35[1] = v37;
        v35 += 2;
      }
      while ( v37 );
      if ( (*(_BYTE *)(v16 + 1) & 2) != 0 )
        v38 = aRct;
      else
        v38 = aNil_5;
      v39 = (char *)&a3[strlen(a3)];
      do
      {
        v40 = *v38;
        *v39 = *v38;
        if ( !v40 )
          break;
        v41 = v38[1];
        v38 += 2;
        v39[1] = v41;
        v39 += 2;
      }
      while ( v41 );
      if ( (*(_BYTE *)v16 & 4) != 0 )
        v42 = aCmp;
      else
        v42 = aExc;
      v43 = (char *)&a3[strlen(a3)];
      do
      {
        v44 = *v42;
        *v43 = *v42;
        if ( !v44 )
          break;
        v45 = v42[1];
        v42 += 2;
        v43[1] = v45;
        v43 += 2;
      }
      while ( v45 );
      if ( (*(_BYTE *)(v16 + 1) & 4) != 0 )
        v46 = aPub;
      else
        v46 = aPrv;
      v47 = (char *)&a3[strlen(a3)];
      do
      {
        v48 = *v46;
        *v47 = *v46;
        if ( !v48 )
          break;
        v49 = v46[1];
        v46 += 2;
        v47[1] = v49;
        v47 += 2;
      }
      while ( v49 );
      v50 = Class_SlotAccessModeString(v16);
      if ( !v50[1] )
      {
        v51 = asc_50CEE8;
        v52 = (char *)&a3[strlen(a3)];
        do
        {
          v53 = *v51;
          *v52 = *v51;
          if ( !v53 )
            break;
          v54 = v51[1];
          v51 += 2;
          v52[1] = v54;
          v52 += 2;
        }
        while ( v54 );
      }
      v55 = v50;
      v56 = (char *)&a3[strlen(a3)];
      do
      {
        v57 = *v55;
        *v56 = *v55;
        if ( !v57 )
          break;
        v58 = v55[1];
        v55 += 2;
        v56[1] = v58;
        v56 += 2;
      }
      while ( v58 );
      if ( !v50[1] || !v50[2] )
      {
        v59 = asc_50CEE8;
        v60 = (char *)&a3[strlen(a3)];
        do
        {
          v61 = *v59;
          *v60 = *v59;
          if ( !v61 )
            break;
          v62 = v59[1];
          v59 += 2;
          v60[1] = v62;
          v60 += 2;
        }
        while ( v62 );
      }
      v63 = asc_50CEE8;
      v64 = strlen(a3) + 1;
      v65 = (char *)&a3[v64 - 1];
      do
      {
        v66 = *v63;
        *v65 = *v63;
        if ( !v66 )
          break;
        v67 = v63[1];
        v63 += 2;
        v65[1] = v67;
        v65 += 2;
      }
      while ( v67 );
      Output_Write(a1, (int)a3, ~v64);
      if ( (*(_BYTE *)v16 & 0x10) != 0 )
        v68 = aNil_6;
      else
        v68 = *(char **)(*(_DWORD *)(v16 + 12) + 16);
      sprintf_(a3, a4, v68);
      Output_Write(a1, (int)a3, 0);
      Class_PrintSlotSourceClasses(a1, *(_DWORD *)(*(_DWORD *)(v16 + 8) + 12), v69, (unsigned __int16 *)(*(_DWORD *)(v16 + 4) + 46), 1);
      Output_Write(a1, (int)asc_50CE14, v70);
      v73 += 4;
      result = ++v74;
    }
    while ( v74 < *(_DWORD *)(a5 + 72) );
  }
  return result;
}
// 4D4DC7: variable 'v7' is possibly undefined
// 4D4E0B: variable 'v13' is possibly undefined
// 4D4E19: variable 'v14' is possibly undefined
// 4D50F3: variable 'v69' is possibly undefined
// 4D5101: variable 'v70' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (004D51D0) --------------------------------------------------------
signed int  Class_PrintSlotSourceClasses(int a1, int a2, int a3, unsigned __int16 *a4, int a5)
{
  _BYTE *v8; // eax
  int v9; // ecx
  _BYTE *v10; // edx
  int v12; // ecx

  while ( 1 )
  {
    if ( a3 == *a4 )
      return 0;
    v8 = (_BYTE *)Class_FindSlotBySymbol(*(_DWORD *)(*(_DWORD *)(a4 + 1) + 4 * a3), a2);
    v10 = v8;
    if ( v8 )
    {
      if ( (*v8 & 8) == 0 || v9 )
        break;
    }
    ++a3;
  }
  if ( (*v10 & 4) != 0 )
  {
    if ( Class_PrintSlotSourceClasses(a1, a2, a3 + 1, (int)a4, 0) )
      Output_Write(a1, (int)asc_50CEE8, v12);
  }
  Class_PrintName(*(_DWORD *)(*(_DWORD *)(a4 + 1) + 4 * a3), 0);
  return 1;
}
// 4D5240: variable 'v12' is possibly undefined
// 4D5265: variable 'v9' is possibly undefined

//----- (004D5270) --------------------------------------------------------
signed int  Class_PrintSlotConstraintTable(
        int a1,
        const char *a2,
        int a3,
        const char *a4,
        signed int a5)
{
  char *v5; // esi
  unsigned int v6; // kr04_4
  char *v7; // edi
  char v8; // al
  char v9; // al
  signed int result; // eax
  int v11; // eax
  char *v12; // ebp
  int v13; // edx
  int v14; // ecx
  int v15; // ecx
  char *v16; // edx
  int v17; // edx
  int v18; // ecx
  char *v19; // esi
  char *v20; // edi
  char v21; // al
  char v22; // al
  char *v23; // esi
  char *v24; // edi
  char v25; // al
  char v26; // al
  char *v27; // esi
  char *v28; // edi
  char v29; // al
  char v30; // al
  char *v31; // esi
  char *v32; // edi
  char v33; // al
  char v34; // al
  char *v35; // esi
  char *v36; // edi
  char v37; // al
  char v38; // al
  char *v39; // esi
  char *v40; // edi
  char v41; // al
  char v42; // al
  char *v43; // esi
  char *v44; // edi
  char v45; // al
  char v46; // al
  char *v47; // esi
  char *v48; // edi
  char v49; // al
  char v50; // al
  char v51; // dh
  int v52; // ecx
  int v53; // ecx
  int v54; // ecx
  int v58; // [esp+Ch] [ebp-18h]
  int i; // [esp+10h] [ebp-14h]

  v5 = aSymStrInnInaEx;
  sprintf_(a4, a2, aSlots_0);
  v6 = strlen(a4) + 1;
  v7 = (char *)&a4[v6 - 1];
  do
  {
    v8 = *v5;
    *v7 = *v5;
    if ( !v8 )
      break;
    v9 = v5[1];
    v5 += 2;
    v7[1] = v9;
    v7 += 2;
  }
  while ( v9 );
  Output_Write(a1, (int)a4, ~v6);
  result = a5;
  v58 = 0;
  if ( *(_DWORD *)(a5 + 72) )
  {
    for ( i = 0; ; i += 4 )
    {
      v11 = *(_DWORD *)(i + *(_DWORD *)(a5 + 56));
      v12 = *(char **)(v11 + 20);
      sprintf_(a4, a2, *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v11 + 8) + 12) + 16));
      if ( v12 )
        break;
      IO_OpenStringDestination((int)aDescribeClas_1, (const void *)v13, a3);
      Output_Write((int)aDescribeClas_1, (int)aRngOo__Oo, v14);
      if ( (**(_BYTE **)(i + *(_DWORD *)(a5 + 56)) & 2) != 0 )
      {
        v16 = aCrd0__Oo;
LABEL_9:
        Output_Write((int)aDescribeClas_1, (int)v16, v15);
      }
LABEL_10:
      Output_Write((int)aDescribeClas_1, (int)asc_50CE14, v15);
      IO_CloseStringRouter((int)aDescribeClas_1);
      result = Output_Write(a1, v17, v18);
      if ( (unsigned int)++v58 >= *(_DWORD *)(a5 + 72) )
        return result;
    }
    v19 = Class_ConstraintTypeMarker(v12, *(_DWORD *)v12 << 30 >> 31, *(_DWORD *)v12 << 21 >> 31);
    v20 = (char *)&a4[strlen(a4)];
    do
    {
      v21 = *v19;
      *v20 = *v19;
      if ( !v21 )
        break;
      v22 = v19[1];
      v19 += 2;
      v20[1] = v22;
      v20 += 2;
    }
    while ( v22 );
    v23 = Class_ConstraintTypeMarker(v12, *(_DWORD *)v12 << 29 >> 31, *(_DWORD *)v12 << 20 >> 31);
    v24 = (char *)&a4[strlen(a4)];
    do
    {
      v25 = *v23;
      *v24 = *v23;
      if ( !v25 )
        break;
      v26 = v23[1];
      v23 += 2;
      v24[1] = v26;
      v24 += 2;
    }
    while ( v26 );
    v27 = Class_ConstraintTypeMarker(v12, *(_DWORD *)v12 << 26 >> 31, *(_DWORD *)v12 << 17 >> 31);
    v28 = (char *)&a4[strlen(a4)];
    do
    {
      v29 = *v27;
      *v28 = *v27;
      if ( !v29 )
        break;
      v30 = v27[1];
      v27 += 2;
      v28[1] = v30;
      v28 += 2;
    }
    while ( v30 );
    v31 = Class_ConstraintTypeMarker(v12, *(_DWORD *)v12 << 25 >> 31, 0);
    v32 = (char *)&a4[strlen(a4)];
    do
    {
      v33 = *v31;
      *v32 = *v31;
      if ( !v33 )
        break;
      v34 = v31[1];
      v31 += 2;
      v32[1] = v34;
      v32 += 2;
    }
    while ( v34 );
    v35 = Class_ConstraintTypeMarker(v12, *(_DWORD *)v12 << 24 >> 31, 0);
    v36 = (char *)&a4[strlen(a4)];
    do
    {
      v37 = *v35;
      *v36 = *v35;
      if ( !v37 )
        break;
      v38 = v35[1];
      v35 += 2;
      v36[1] = v38;
      v36 += 2;
    }
    while ( v38 );
    v39 = Class_ConstraintTypeMarker(v12, *(_DWORD *)v12 << 23 >> 31, 0);
    v40 = (char *)&a4[strlen(a4)];
    do
    {
      v41 = *v39;
      *v40 = *v39;
      if ( !v41 )
        break;
      v42 = v39[1];
      v39 += 2;
      v40[1] = v42;
      v40 += 2;
    }
    while ( v42 );
    v43 = Class_ConstraintTypeMarker(v12, *(_DWORD *)v12 << 27 >> 31, *(_DWORD *)v12 << 18 >> 31);
    v44 = (char *)&a4[strlen(a4)];
    do
    {
      v45 = *v43;
      *v44 = *v43;
      if ( !v45 )
        break;
      v46 = v43[1];
      v43 += 2;
      v44[1] = v46;
      v44 += 2;
    }
    while ( v46 );
    v47 = Class_ConstraintTypeMarker(v12, *(_DWORD *)v12 << 28 >> 31, *(_DWORD *)v12 << 19 >> 31);
    v48 = (char *)&a4[strlen(a4)];
    do
    {
      v49 = *v47;
      *v48 = *v47;
      if ( !v49 )
        break;
      v50 = v47[1];
      v47 += 2;
      v48[1] = v50;
      v48 += 2;
    }
    while ( v50 );
    IO_OpenStringDestination((int)aDescribeClas_1, &a4[strlen(a4)], a3 - (strlen(a4) + 1));
    v51 = *v12;
    if ( (*v12 & 0x10) != 0 || (v51 & 8) != 0 || (v51 & 1) != 0 )
    {
      Output_Write((int)aDescribeClas_1, (int)aRng, v15);
      Rules_PrintFieldExprList((signed int)aDescribeClas_1, *(__int16 **)(v12 + 10));
      Output_Write((int)aDescribeClas_1, (int)a___0, v52);
      Rules_PrintFieldExprList((signed int)aDescribeClas_1, *(__int16 **)(v12 + 14));
      Output_Write((int)aDescribeClas_1, (int)asc_50CF34, v53);
    }
    if ( (**(_BYTE **)(i + *(_DWORD *)(a5 + 56)) & 2) == 0 )
      goto LABEL_10;
    Output_Write((int)aDescribeClas_1, (int)aCrd, v15);
    Rules_PrintFieldExprList((signed int)aDescribeClas_1, *(__int16 **)(v12 + 18));
    Output_Write((int)aDescribeClas_1, (int)a___0, v54);
    Rules_PrintFieldExprList((signed int)aDescribeClas_1, *(__int16 **)(v12 + 22));
    v16 = asc_50CF40;
    goto LABEL_9;
  }
  return result;
}
// 4D5320: variable 'v13' is possibly undefined
// 4D532F: variable 'v14' is possibly undefined
// 4D534E: variable 'v15' is possibly undefined
// 4D537F: variable 'v17' is possibly undefined
// 4D537F: variable 'v18' is possibly undefined
// 4D55DD: variable 'v52' is possibly undefined
// 4D55F9: variable 'v53' is possibly undefined
// 4D563C: variable 'v54' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (004D5670) --------------------------------------------------------
char * Class_ConstraintTypeMarker(_BYTE *a1, int a2, int a3)
{
  if ( !a2 && (*a1 & 1) == 0 )
    return asc_50CF94;
  if ( a3 || (a1[1] & 2) != 0 )
    return asc_50CF84;
  return asc_50CF8C;
}

//----- (004D56A0) --------------------------------------------------------
unsigned int  Class_ClassAbstractPCommand(int a1, double a2)
{
  unsigned int result; // eax
  int *v3; // eax
  int v4; // ecx
  int v5; // [esp-8h] [ebp-24h] BYREF
  int v6; // [esp+0h] [ebp-1Ch]
  int v7; // [esp+14h] [ebp-8h]

  v7 = a1;
  result = Lexer_ParseValueList(1, &v5, 2, a2);
  if ( result )
  {
    v3 = Class_LookupByQualifiedName(*(_BYTE **)(v6 + 16));
    if ( v3 )
    {
      return (unsigned int)(v3[5] << 29) >> 31;
    }
    else
    {
      Class_ReportLookupError(v4, *(_DWORD *)(v6 + 16));
      return 0;
    }
  }
  return result;
}
// 4D56F3: variable 'v4' is possibly undefined

//----- (004D5710) --------------------------------------------------------
unsigned int  Class_ClassReactivePCommand(int a1, double a2)
{
  unsigned int result; // eax
  int *v3; // eax
  int v4; // ecx
  int v5; // [esp-8h] [ebp-24h] BYREF
  int v6; // [esp+0h] [ebp-1Ch]
  int v7; // [esp+14h] [ebp-8h]

  v7 = a1;
  result = Lexer_ParseValueList(1, &v5, 2, a2);
  if ( result )
  {
    v3 = Class_LookupByQualifiedName(*(_BYTE **)(v6 + 16));
    if ( v3 )
    {
      return (unsigned int)(v3[5] << 28) >> 31;
    }
    else
    {
      Class_ReportLookupError(v4, *(_DWORD *)(v6 + 16));
      return 0;
    }
  }
  return result;
}
// 4D5763: variable 'v4' is possibly undefined

//----- (004D5780) --------------------------------------------------------
int * Class_ParseClassNameAndInheritFlag(int a1, _DWORD *a2, double a3)
{
  int *result; // eax
  int v6; // ecx
  int *v7; // ebp
  int v8; // ecx
  _DWORD v9[2]; // [esp+0h] [ebp-2Ch] BYREF
  int v10; // [esp+8h] [ebp-24h]

  *a2 = 0;
  if ( Rules_RtnArgCount() )
  {
    result = (int *)Lexer_ParseValueList(1, v9, 2, a3);
    if ( result )
    {
      v7 = Class_LookupByQualifiedName(*(_BYTE **)(v10 + 16));
      if ( v7 )
      {
        if ( Rules_RtnArgCount() == 2 )
        {
          result = (int *)Lexer_ParseValueList(2, v9, 2, a3);
          if ( result )
          {
            if ( !strcmp_(v8, aInherit_1) )
            {
              *a2 = 1;
              return v7;
            }
            else
            {
              Parser_ReportSyntaxError();
              Lexer_ErrorRecover(1);
              return 0;
            }
          }
        }
        else
        {
          return v7;
        }
      }
      else
      {
        Class_ReportLookupError(v6, *(_DWORD *)(v10 + 16));
        return 0;
      }
    }
  }
  else
  {
    Rules_ExpectedCountError(a1, 1);
    Lexer_ErrorRecover(1);
    return 0;
  }
  return result;
}
// 4D5807: variable 'v6' is possibly undefined
// 4D5834: variable 'v8' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004D5870) --------------------------------------------------------
_DWORD * Class_ClassSlotsCommand(unsigned int a1, double a2)
{
  int *v2; // eax
  _DWORD *v3; // ecx
  unsigned int v5[3]; // [esp+0h] [ebp-Ch] BYREF

  v5[2] = a1;
  v2 = Class_ParseClassNameAndInheritFlag((int)aClassSlots_0, v5, a2);
  if ( v2 )
    return Class_SlotsFunction((int)v2, v3, v5[0]);
  else
    return Rules_SetMultifieldErrorValue((int)v3);
}
// 4D5889: variable 'v3' is possibly undefined

//----- (004D58B0) --------------------------------------------------------
__int16  Class_ClassSuperclassesCommand(int a1, double a2)
{
  int *v2; // eax
  _DWORD *v3; // ecx
  int v5[3]; // [esp+0h] [ebp-Ch] BYREF

  v5[2] = a1;
  v2 = Class_ParseClassNameAndInheritFlag((int)aClassSupercl_0, v5, a2);
  if ( v2 )
    return Class_SuperclassesFunction((int)v2, v3, v5[0]);
  else
    return (unsigned __int16)Rules_SetMultifieldErrorValue((int)v3);
}
// 4D58C9: variable 'v3' is possibly undefined

//----- (004D58F0) --------------------------------------------------------
void  Class_ClassSubclassesCommand(int a1, double a2)
{
  int *v2; // eax
  int v3; // ecx
  int v4[3]; // [esp+0h] [ebp-Ch] BYREF

  v4[2] = a1;
  v2 = Class_ParseClassNameAndInheritFlag((int)aClassSubclas_0, v4, a2);
  if ( v2 )
    Class_SubclassesFunction((int)v2, v4[0]);
  else
    Rules_SetMultifieldErrorValue(v3);
}
// 4D5909: variable 'v3' is possibly undefined

//----- (004D5930) --------------------------------------------------------
_DWORD * Class_GetDefmessageHandlerListCommand(int a1, double a2)
{
  int *v3; // eax
  int v4; // ecx
  int v6[4]; // [esp+0h] [ebp-10h] BYREF

  v6[2] = a1;
  if ( !Rules_RtnArgCount() )
    return (_DWORD *)Class_MessageHandlerListFunction(0, 0);
  v3 = Class_ParseClassNameAndInheritFlag((int)aGetDefmessag_0, v6, a2);
  if ( v3 )
    return (_DWORD *)Class_MessageHandlerListFunction((int)v3, v6[0]);
  else
    return Rules_SetMultifieldErrorValue(v4);
}
// 4D5953: variable 'v4' is possibly undefined

//----- (004D5980) --------------------------------------------------------
_DWORD * Class_SlotFacetsCommand(int a1, int *a2, double a3)
{
  return Class_DispatchSlotQuery(a1, a2, (int (*)(void))Class_SlotFacetsQuery, a3);
}

//----- (004D59A0) --------------------------------------------------------
_DWORD * Class_SlotSourcesCommand(int a1, int *a2, double a3)
{
  return Class_DispatchSlotQuery(a1, a2, (int (*)(void))Class_SlotSourcesQuery, a3);
}

//----- (004D59C0) --------------------------------------------------------
_DWORD * Class_SlotTypesCommand(int a1, int *a2, double a3)
{
  return Class_DispatchSlotQuery(a1, a2, (int (*)(void))Class_SlotTypesQuery, a3);
}

//----- (004D59E0) --------------------------------------------------------
_DWORD * Class_SlotAllowedValuesFunction(int a1, int *a2, double a3)
{
  return Class_DispatchSlotQuery(a1, a2, (int (*)(void))Class_SlotAllowedValuesQuery, a3);
}

//----- (004D5A00) --------------------------------------------------------
_DWORD * Class_SlotRangeFunction(int a1, int *a2, double a3)
{
  return Class_DispatchSlotQuery(a1, a2, (int (*)(void))Class_SlotRangeQuery, a3);
}

//----- (004D5A20) --------------------------------------------------------
_DWORD * Class_SlotCardinalityFunction(int a1, int *a2, double a3)
{
  return Class_DispatchSlotQuery(a1, a2, (int (*)(void))Class_SlotCardinalityQuery, a3);
}

//----- (004D5A40) --------------------------------------------------------
int  Class_IsAbstract(int a1)
{
  return *(_DWORD *)(a1 + 20) << 29 >> 31;
}

//----- (004D5A60) --------------------------------------------------------
_DWORD * Class_SlotsFunction(int a1, _DWORD *a2, unsigned int a3)
{
  unsigned int v3; // esi
  signed int v4; // ebx
  _DWORD *result; // eax
  int v6; // edx
  _DWORD *v7; // ecx
  unsigned int v8; // ebx
  int v9; // esi
  int v10; // edi
  int v11; // ebx
  int v12; // [esp+0h] [ebp-18h]

  v3 = a3;
  if ( a3 )
    v4 = *(_DWORD *)(a1 + 72);
  else
    v4 = *(_DWORD *)(a1 + 64);
  a2[1] = 4;
  a2[4] = v4 - 1;
  a2[3] = 0;
  result = Rules_CreateEphemeralMultifield(v4);
  *(_DWORD *)(v6 + 8) = result;
  if ( v4 )
  {
    if ( v3 )
    {
      v8 = 0;
      if ( v7[18] )
      {
        v9 = 0;
        result = 0;
        do
        {
          *(_WORD *)((char *)result + *(_DWORD *)(v6 + 8) + 14) = 2;
          v10 = *(_DWORD *)(v7[14] + v9);
          v9 += 4;
          ++v8;
          *(_DWORD *)((char *)result + *(_DWORD *)(v6 + 8) + 16) = *(_DWORD *)(*(_DWORD *)(v10 + 8) + 12);
          result = (_DWORD *)((char *)result + 6);
        }
        while ( v8 < v7[18] );
      }
    }
    else if ( v7[16] )
    {
      v11 = 0;
      result = 0;
      do
      {
        *(_WORD *)((char *)result + *(_DWORD *)(v6 + 8) + 14) = 2;
        v12 = *(_DWORD *)(v7[13] + v11 + 8);
        v11 += 44;
        *(_DWORD *)((char *)result + *(_DWORD *)(v6 + 8) + 16) = *(_DWORD *)(v12 + 12);
        ++v3;
        result = (_DWORD *)((char *)result + 6);
      }
      while ( v3 < v7[16] );
    }
  }
  return result;
}
// 4D5A91: variable 'v6' is possibly undefined
// 4D5A9C: variable 'v7' is possibly undefined

//----- (004D5B40) --------------------------------------------------------
int  Class_MessageHandlerListFunction(int a1, int a2)
{
  int v3; // ebp
  _DWORD *v4; // ecx
  int i; // ebx
  int v6; // edx
  int v7; // edi
  int v8; // eax
  int *v9; // edx
  int v10; // esi
  _DWORD *v11; // eax
  int v12; // ecx
  int result; // eax
  int v14; // eax
  int v15; // ebx
  int v16; // edx
  int v17; // edx
  unsigned int v18; // edi
  int v19; // esi
  int v20; // eax
  int v21; // ecx
  int v22; // edx
  signed int *v23; // eax
  int v24; // edx
  int v26; // [esp+4h] [ebp-38h]
  int v27; // [esp+10h] [ebp-2Ch]
  int v28; // [esp+14h] [ebp-28h]
  int v29; // [esp+18h] [ebp-24h]
  int v30; // [esp+1Ch] [ebp-20h]
  int j; // [esp+20h] [ebp-1Ch]
  int v32; // [esp+24h] [ebp-18h]
  int v33; // [esp+28h] [ebp-14h]

  if ( a1 )
  {
    v3 = a1;
    v27 = Class_GetNextRecord(a1);
    Rules_SetConstructNextInModule(a1, 0);
  }
  else
  {
    a2 = 0;
    v3 = Class_GetNextRecord(0);
    v27 = Class_GetNextRecord(v3);
  }
  v28 = v3;
  for ( i = 0; v3; v3 = Class_GetNextRecord(v3) )
  {
    if ( a2 )
      v6 = *(unsigned __int16 *)(v3 + 46);
    else
      v6 = 1;
    v7 = v6;
    v8 = 0;
    if ( v6 > 0 )
    {
      v9 = *(int **)(v3 + 48);
      do
      {
        v10 = *v9++;
        ++v8;
        i += *(_DWORD *)(v10 + 96);
      }
      while ( v8 < v7 );
    }
  }
  v4[1] = 4;
  v4[3] = 0;
  v29 = 3 * i;
  v4[4] = 3 * i - 1;
  v11 = Rules_CreateEphemeralMultifield(3 * i);
  *(_DWORD *)(v12 + 8) = v11;
  result = v28;
  v32 = 0;
  for ( j = v28; result; j = result )
  {
    if ( a2 )
      v14 = *(unsigned __int16 *)(j + 46);
    else
      v14 = 1;
    if ( v14 > 0 )
    {
      v33 = 0;
      v30 = 4 * v14;
      do
      {
        v15 = *(_DWORD *)(v33 + *(_DWORD *)(j + 48));
        if ( a2 )
          v16 = v29 - 3 * *(_DWORD *)(v15 + 96) - v32;
        else
          v16 = v32;
        v17 = v16 + 1;
        v18 = 0;
        if ( *(_DWORD *)(v15 + 96) )
        {
          v19 = 0;
          do
          {
            v26 = 6 * (v17 - 1);
            *(_WORD *)(*(_DWORD *)(v12 + 8) + v26 + 14) = 2;
            v20 = Rules_GetConstructNameSymbol(v15);
            *(_DWORD *)(v26 + *(_DWORD *)(v21 + 8) + 16) = v20;
            *(_WORD *)(*(_DWORD *)(v21 + 8) + 6 * v22 + 14) = 2;
            *(_DWORD *)(6 * v22 + *(_DWORD *)(v21 + 8) + 16) = *(_DWORD *)(v19 + *(_DWORD *)(v15 + 88) + 8);
            *(_WORD *)(6 * (v22 + 1) + *(_DWORD *)(v21 + 8) + 14) = 2;
            v23 = Str_Intern(g_MessageHandlerTypeNames[*(_DWORD *)(v19 + *(_DWORD *)(v15 + 88)) << 29 >> 30], v21);
            ++v18;
            v19 += 36;
            *(_DWORD *)(6 * (v24 - 1) + *(_DWORD *)(v12 + 8) + 16) = v23;
            v17 = v24 + 1;
          }
          while ( v18 < *(_DWORD *)(v15 + 96) );
        }
        v32 += 3 * *(_DWORD *)(v15 + 96);
        v33 += 4;
      }
      while ( v33 < v30 );
    }
    result = Class_GetNextRecord(j);
  }
  if ( v28 )
    return Rules_SetConstructNextInModule(v28, v27);
  return result;
}
// 4D5BB0: variable 'v4' is possibly undefined
// 4D5BD3: variable 'v12' is possibly undefined
// 4D5C61: variable 'v21' is possibly undefined
// 4D5C6F: variable 'v22' is possibly undefined
// 4D5CF4: variable 'v24' is possibly undefined
// 51AD3C: using guessed type char *off_51AD3C[4];

//----- (004D5DC0) --------------------------------------------------------
__int16  Class_SuperclassesFunction(int a1, _DWORD *a2, int a3)
{
  int v4; // edx
  unsigned __int16 *v5; // edi
  signed int v6; // eax
  _DWORD *v7; // eax
  unsigned int v8; // edx
  int v9; // ecx
  unsigned int v10; // ecx
  int v11; // ebx
  int v12; // edx
  int v13; // edx
  int v14; // ebp
  int v15; // ecx

  if ( a3 )
  {
    v4 = 1;
    v5 = (unsigned __int16 *)(a1 + 46);
  }
  else
  {
    v5 = (unsigned __int16 *)(a1 + 34);
    v4 = 0;
  }
  a2[1] = 4;
  a2[3] = 0;
  v6 = *v5 - v4;
  a2[4] = v6 - 1;
  v7 = Rules_CreateEphemeralMultifield(v6);
  v9 = a2[4];
  a2[2] = v7;
  if ( v9 != -1 )
  {
    v10 = v8;
    v11 = 4 * v8;
    v12 = 0;
    LOWORD(v7) = *v5;
    if ( v10 < *v5 )
    {
      do
      {
        *(_WORD *)(v12 + a2[2] + 14) = 2;
        v7 = (_DWORD *)Rules_GetConstructNameSymbol(*(_DWORD *)(v11 + *(_DWORD *)(v5 + 1)));
        v11 += 4;
        v14 = v13 + a2[2];
        v12 = v13 + 6;
        *(_DWORD *)(v14 + 16) = v7;
        LOWORD(v7) = *v5;
      }
      while ( v15 + 1 < (unsigned int)*v5 );
    }
  }
  return (__int16)v7;
}
// 4D5DFD: variable 'v8' is possibly undefined
// 4D5E39: variable 'v13' is possibly undefined
// 4D5E3B: variable 'v15' is possibly undefined

//----- (004D5E50) --------------------------------------------------------
void  Class_SubclassesFunction(int a1, int a2)
{
  signed int v3; // eax
  _DWORD *v4; // ecx
  signed int v5; // edx
  _DWORD *v6; // eax
  int v7; // ecx
  int v8; // edx
  signed int v9; // eax
  int v10; // ecx

  v3 = Class_NewTraversalID();
  if ( v3 != -1 )
  {
    Class_CountSubclasses(a1, a2, v3);
    Class_ReleaseTraversalID();
    v4[1] = 4;
    v4[4] = v5 - 1;
    v4[3] = 0;
    v6 = Rules_CreateEphemeralMultifield(v5);
    *(_DWORD *)(v7 + 8) = v6;
    if ( v8 )
    {
      v9 = Class_NewTraversalID();
      if ( v9 != -1 )
      {
        Class_CollectSubclassNames(*(_DWORD *)(v10 + 8), 1, a2, a1, v9);
        Class_ReleaseTraversalID();
      }
    }
  }
}
// 4D5E7B: variable 'v4' is possibly undefined
// 4D5E82: variable 'v5' is possibly undefined
// 4D5E94: variable 'v7' is possibly undefined
// 4D5E99: variable 'v8' is possibly undefined
// 4D5EAD: variable 'v10' is possibly undefined

//----- (004D5EC0) --------------------------------------------------------
signed int * Class_SlotFacetsQuery(int a1, _BYTE *a2, int a3)
{
  signed int *result; // eax
  _BYTE *v4; // ecx
  int i; // eax
  char *v6; // eax
  _BYTE *v7; // ecx
  char *v8; // eax
  _BYTE *v9; // ecx
  char *v10; // eax
  _BYTE *v11; // ecx
  char *v12; // eax
  _BYTE *v13; // ecx
  char *v14; // eax
  int v15; // ecx
  char *v16; // eax
  _BYTE *v17; // ecx
  char *v18; // eax
  int v19; // ecx
  char *v20; // eax
  int v21; // ecx
  char *v22; // eax
  int v23; // ecx
  int v24; // ecx

  result = (signed int *)Class_ResolveNamedSlot(a3, a1, a2);
  if ( result )
  {
    *(_DWORD *)(a3 + 16) = 9;
    *(_DWORD *)(a3 + 8) = Rules_CreateEphemeralMultifield(10);
    for ( i = 0; i != 60; *(_WORD *)(*(_DWORD *)(a3 + 8) + i + 8) = 2 )
      i += 6;
    if ( (*v4 & 2) != 0 )
      v6 = aMlt_0;
    else
      v6 = aSgl_0;
    *(_DWORD *)(*(_DWORD *)(a3 + 8) + 16) = Str_Intern(v6, (int)v4);
    if ( (v7[1] & 1) != 0 )
    {
      v8 = aNil_7;
    }
    else if ( (*v7 & 0x40) != 0 )
    {
      v8 = aDyn_0;
    }
    else
    {
      v8 = aStc_0;
    }
    *(_DWORD *)(*(_DWORD *)(a3 + 8) + 22) = Str_Intern(v8, (int)v7);
    if ( (*v9 & 8) != 0 )
      v10 = aNil_7;
    else
      v10 = aInh_0;
    *(_DWORD *)(*(_DWORD *)(a3 + 8) + 28) = Str_Intern(v10, (int)v9);
    if ( (*v11 & 0x20) != 0 )
    {
      v12 = aInt_1;
    }
    else if ( (*v11 & 0x10) != 0 )
    {
      v12 = aR_9;
    }
    else
    {
      v12 = aRw_1;
    }
    *(_DWORD *)(*(_DWORD *)(a3 + 8) + 34) = Str_Intern(v12, (int)v11);
    if ( (*v13 & 1) != 0 )
      v14 = aShr_0;
    else
      v14 = aLcl_0;
    *(_DWORD *)(*(_DWORD *)(a3 + 8) + 40) = Str_Intern(v14, (int)v13);
    if ( (*(_BYTE *)(v15 + 1) & 2) != 0 )
      v16 = aRct_0;
    else
      v16 = aNil_7;
    *(_DWORD *)(*(_DWORD *)(a3 + 8) + 46) = Str_Intern(v16, v15);
    if ( (*v17 & 4) != 0 )
      v18 = aCmpFacet;
    else
      v18 = aExcFacet;
    *(_DWORD *)(*(_DWORD *)(a3 + 8) + 52) = Str_Intern(v18, (int)v17);
    if ( (*(_BYTE *)(v19 + 1) & 4) != 0 )
      v20 = aPubFacet;
    else
      v20 = aPrvFacet;
    *(_DWORD *)(*(_DWORD *)(a3 + 8) + 58) = Str_Intern(v20, v19);
    v22 = Class_SlotAccessModeString(v21);
    *(_DWORD *)(*(_DWORD *)(a3 + 8) + 64) = Str_Intern(v22, v23);
    if ( (*(_BYTE *)v24 & 0x10) != 0 )
      result = Str_Intern(aNil_7, v24);
    else
      result = *(signed int **)(v24 + 12);
    *(_DWORD *)(*(_DWORD *)(a3 + 8) + 70) = result;
  }
  return result;
}
// 4D5F12: variable 'v4' is possibly undefined
// 4D5F2B: variable 'v7' is possibly undefined
// 4D5F45: variable 'v9' is possibly undefined
// 4D5F5E: variable 'v11' is possibly undefined
// 4D5F79: variable 'v13' is possibly undefined
// 4D5F92: variable 'v15' is possibly undefined
// 4D5FAC: variable 'v17' is possibly undefined
// 4D5FC5: variable 'v19' is possibly undefined
// 4D5FE1: variable 'v21' is possibly undefined
// 4D5FE6: variable 'v23' is possibly undefined
// 4D5FF1: variable 'v24' is possibly undefined
// 50D0A0: using guessed type _UNKNOWN *off_50D0A0;

//----- (004D6090) --------------------------------------------------------
_DWORD * Class_SlotSourcesQuery(int a1, _BYTE *a2, int a3)
{
  _DWORD *result; // eax
  _DWORD *v4; // edx
  signed int v5; // ecx
  int *v6; // eax
  int v7; // edx
  int v8; // esi
  int i; // edi
  int v10; // eax
  int v11; // ebx
  _BYTE *v12; // eax
  _BYTE *v13; // ebp
  _DWORD *v14; // edx
  int *v15; // eax
  int *v16; // ebx
  _DWORD *v17; // eax
  int v18; // edx
  int v19; // edx
  int v20; // eax
  int v21; // edx
  _DWORD *v23; // [esp+4h] [ebp-10h]
  int *v24; // [esp+8h] [ebp-Ch]

  result = (_DWORD *)Class_ResolveNamedSlot(a3, a1, a2);
  v23 = result;
  if ( result )
  {
    v4 = *(_DWORD **)(g_ClipsMemoryTable + 32);
    v5 = 1;
    if ( v4 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
      *(_DWORD *)(g_ClipsMemoryTable + 32) = *v4;
      v6 = (int *)g_ClipsMemFreeListTemp;
    }
    else
    {
      v6 = (int *)Mem_HeapAllocWithRetry((_DWORD *)8);
    }
    v7 = v23[1];
    v6[1] = 0;
    v24 = v6;
    *v6 = v7;
    if ( (*(_BYTE *)v23 & 4) != 0 )
    {
      v8 = 1;
      for ( i = 4; ; i += 4 )
      {
        v10 = v23[1];
        if ( v8 >= *(unsigned __int16 *)(v10 + 46) )
          break;
        v11 = *(_DWORD *)(i + *(_DWORD *)(v10 + 48));
        v12 = (_BYTE *)Class_FindSlotBySymbol(v11, *(_DWORD *)(v23[2] + 12));
        v13 = v12;
        if ( v12 )
        {
          if ( (*v12 & 8) == 0 )
          {
            v14 = *(_DWORD **)(g_ClipsMemoryTable + 32);
            if ( v14 )
            {
              g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
              *(_DWORD *)(g_ClipsMemoryTable + 32) = *v14;
              v15 = (int *)g_ClipsMemFreeListTemp;
            }
            else
            {
              v15 = (int *)Mem_HeapAllocWithRetry((_DWORD *)8);
            }
            *v15 = v11;
            v15[1] = (int)v24;
            ++v5;
            v24 = v15;
            if ( (*v13 & 4) == 0 )
              break;
          }
        }
        ++v8;
      }
    }
    *(_DWORD *)(a3 + 16) = v5 - 1;
    v16 = v24;
    v17 = Rules_CreateEphemeralMultifield(v5);
    *(_DWORD *)(v18 + 8) = v17;
    if ( v24 )
    {
      v19 = 0;
      do
      {
        *(_WORD *)(v19 + *(_DWORD *)(a3 + 8) + 14) = 2;
        v20 = Rules_GetConstructNameSymbol(*v16);
        *(_DWORD *)(v21 + *(_DWORD *)(a3 + 8) + 16) = v20;
        v19 = v21 + 6;
        v16 = (int *)v16[1];
      }
      while ( v16 );
    }
    return Mem_ReturnListToFreePool(v24);
  }
  return result;
}
// 4D6177: variable 'v5' is possibly undefined
// 4D619E: variable 'v18' is possibly undefined
// 4D61C3: variable 'v21' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004D6210) --------------------------------------------------------
_DWORD * Class_SlotTypesQuery(int a1, _BYTE *a2, int a3)
{
  _DWORD *result; // eax
  _DWORD *v5; // edx
  signed int v6; // edx
  int v7; // ebx
  int v8; // edx
  int v9; // edi
  int v10; // esi
  int v11; // [esp+0h] [ebp-18h]
  char v12; // [esp+4h] [ebp-14h]
  char v13; // [esp+5h] [ebp-13h]

  result = (_DWORD *)Class_ResolveNamedSlot(a3, a1, a2);
  if ( result )
  {
    v5 = (_DWORD *)result[5];
    if ( v5 && (*v5 & 1) == 0 )
    {
      v13 = 0;
      v12 = 0;
      v6 = 0;
      if ( (*(_BYTE *)result[5] & 2) != 0 )
      {
        v6 = 1;
        v12 = 4;
      }
      if ( (*(_BYTE *)result[5] & 4) != 0 )
      {
        ++v6;
        v12 |= 8u;
      }
      if ( (*(_BYTE *)result[5] & 8) != 0 )
      {
        ++v6;
        v12 |= 1u;
      }
      if ( (*(_BYTE *)result[5] & 0x10) != 0 )
      {
        ++v6;
        v12 |= 2u;
      }
      if ( (*(_BYTE *)result[5] & 0x20) != 0 )
      {
        ++v6;
        v13 |= 1u;
      }
      if ( (*(_BYTE *)result[5] & 0x40) != 0 )
      {
        ++v6;
        v12 |= 0x80u;
      }
      if ( *(char *)result[5] < 0 )
      {
        ++v6;
        v12 |= 0x20u;
      }
      if ( (*(_BYTE *)(result[5] + 1) & 1) != 0 )
      {
        ++v6;
        v12 |= 0x40u;
      }
    }
    else
    {
      v13 = -1;
      v6 = 8;
      v12 = -17;
    }
    *(_DWORD *)(a3 + 16) = v6 - 1;
    v7 = 0;
    result = Rules_CreateEphemeralMultifield(v6);
    *(_DWORD *)(a3 + 8) = result;
    if ( v8 >= 1 )
    {
      v9 = 0;
      v10 = 0;
      v11 = 6 * v8 - 6;
      do
      {
        result = (_DWORD *)(unsigned __int8)*(&v12 + ((v7 - (__CFSHL__(v7 >> 31, 3) + 8 * (v7 >> 31))) >> 3));
        if ( ((unsigned __int8)(1 << (v7 % 8)) & (unsigned __int8)result) != 0 )
        {
          *(_WORD *)(v10 + *(_DWORD *)(a3 + 8) + 14) = 2;
          v10 += 6;
          result = (_DWORD *)Rules_GetConstructNameSymbol(g_ClipsPrimitiveTypeClassMap[v9]);
          *(_DWORD *)(*(_DWORD *)(a3 + 8) + v10 + 10) = result;
        }
        ++v9;
        ++v7;
      }
      while ( v10 <= v11 );
    }
  }
  return result;
}
// 4D626A: variable 'v8' is possibly undefined
// 51AD7C: using guessed type int dword_51AD7C[];

//----- (004D63B0) --------------------------------------------------------
int  Class_SlotAllowedValuesQuery(int a1, _BYTE *a2, _DWORD *a3)
{
  int result; // eax
  int v4; // ecx
  int v5; // eax
  signed int v6; // eax
  int v7; // edx
  int v8; // edx

  result = Class_ResolveNamedSlot((int)a3, a1, a2);
  if ( result )
  {
    v4 = *(_DWORD *)(result + 20);
    if ( v4 && (v5 = *(_DWORD *)(result + 20), *(_DWORD *)(v4 + 6)) )
    {
      v6 = AST_CountTreeNodes(*(_DWORD *)(v5 + 6));
      a3[4] = v6 - 1;
      a3[2] = Rules_CreateEphemeralMultifield(v6);
      result = *(_DWORD *)(*(_DWORD *)(v7 + 20) + 6);
      if ( result )
      {
        v8 = 0;
        do
        {
          *(_WORD *)(v8 + a3[2] + 14) = *(_WORD *)result;
          *(_DWORD *)(a3[2] + v8 + 16) = *(_DWORD *)(result + 2);
          result = *(_DWORD *)(result + 10);
          v8 += 6;
        }
        while ( result );
      }
    }
    else
    {
      a3[1] = 2;
      result = g_ClipsFalseSymbol;
      a3[2] = g_ClipsFalseSymbol;
    }
  }
  return result;
}
// 4D641A: variable 'v7' is possibly undefined
// 54DD70: using guessed type int dword_54DD70;

//----- (004D6450) --------------------------------------------------------
int  Class_SlotRangeQuery(int a1, _BYTE *a2, _DWORD *a3)
{
  int result; // eax
  char *v5; // ecx
  char v6; // bl
  int v7; // eax
  int v8; // edx

  result = Class_ResolveNamedSlot((int)a3, a1, a2);
  if ( result )
  {
    v5 = *(char **)(result + 20);
    if ( v5 && ((v6 = *v5, (*v5 & 1) != 0) || (v6 & 8) != 0 || (v6 & 0x10) != 0 ? (v7 = 1) : (v7 = 0), v7) )
    {
      a3[4] = 1;
      a3[2] = Rules_CreateEphemeralMultifield(2);
      *(_WORD *)(a3[2] + 14) = **(_WORD **)(*(_DWORD *)(v8 + 20) + 10);
      *(_DWORD *)(a3[2] + 16) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v8 + 20) + 10) + 2);
      *(_WORD *)(a3[2] + 20) = **(_WORD **)(*(_DWORD *)(v8 + 20) + 14);
      result = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v8 + 20) + 14) + 2);
      *(_DWORD *)(a3[2] + 22) = result;
    }
    else
    {
      a3[1] = 2;
      result = g_ClipsFalseSymbol;
      a3[2] = g_ClipsFalseSymbol;
    }
  }
  return result;
}
// 4D64B7: variable 'v8' is possibly undefined
// 54DD70: using guessed type int dword_54DD70;

//----- (004D6500) --------------------------------------------------------
_DWORD * Class_SlotCardinalityQuery(int a1, _BYTE *a2, int a3)
{
  _DWORD *result; // eax
  _DWORD *v4; // eax
  int v5; // edx
  int v6; // ecx

  result = (_DWORD *)Class_ResolveNamedSlot(a3, a1, a2);
  if ( result )
  {
    if ( (*(_BYTE *)result & 2) != 0 )
    {
      *(_DWORD *)(a3 + 16) = 1;
      v4 = Rules_CreateEphemeralMultifield(2);
      *(_DWORD *)(a3 + 8) = v4;
      v6 = *(_DWORD *)(v5 + 20);
      if ( v6 )
      {
        *(_WORD *)(*(_DWORD *)(a3 + 8) + 14) = **(_WORD **)(v6 + 18);
        *(_DWORD *)(*(_DWORD *)(a3 + 8) + 16) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v5 + 20) + 18) + 2);
        *(_WORD *)(*(_DWORD *)(a3 + 8) + 20) = **(_WORD **)(*(_DWORD *)(v5 + 20) + 22);
        result = *(_DWORD **)(*(_DWORD *)(*(_DWORD *)(v5 + 20) + 22) + 2);
        *(_DWORD *)(*(_DWORD *)(a3 + 8) + 22) = result;
      }
      else
      {
        *((_WORD *)v4 + 7) = 1;
        *(_DWORD *)(*(_DWORD *)(a3 + 8) + 16) = g_CLIPS_IntegerZeroValueNode;
        *(_WORD *)(*(_DWORD *)(a3 + 8) + 20) = 2;
        result = (_DWORD *)g_ClipsPositiveInfinitySymbol;
        *(_DWORD *)(*(_DWORD *)(a3 + 8) + 22) = g_ClipsPositiveInfinitySymbol;
      }
    }
    else
    {
      return Rules_SetMultifieldErrorValue(a3);
    }
  }
  return result;
}
// 4D6533: variable 'v5' is possibly undefined
// 54DD68: using guessed type int dword_54DD68;
// 54DD6C: using guessed type int dword_54DD6C;

//----- (004D65B0) --------------------------------------------------------
_DWORD * Class_DispatchSlotQuery(int a1, int *a2, int (*a3)(void), double a4)
{
  int v4; // ecx
  int *v6[3]; // [esp+0h] [ebp-Ch] BYREF

  v6[2] = a2;
  if ( Class_ParseClassReference(v6, a1, a4) )
    return (_DWORD *)a3();
  else
    return Rules_SetMultifieldErrorValue(v4);
}
// 4D65C8: variable 'v4' is possibly undefined

//----- (004D65F0) --------------------------------------------------------
int  Class_CountSubclasses(int a1, int a2, signed int a3)
{
  int v4; // esi
  int v5; // ebp
  int v6; // eax
  int v8; // [esp+8h] [ebp-24h]
  int v9; // [esp+Ch] [ebp-20h]
  unsigned int v11; // [esp+18h] [ebp-14h]

  v9 = (a3 - (__CFSHL__(a3 >> 31, 3) + 8 * (a3 >> 31))) >> 3;
  v4 = 0;
  v5 = 0;
  v11 = 0;
  v8 = a3 % 8;
  while ( *(unsigned __int16 *)(a1 + 40) > v11 )
  {
    v6 = *(_DWORD *)(*(_DWORD *)(a1 + 42) + v5);
    if ( (*(_BYTE *)(v6 + v9 + 108) & (unsigned __int8)(1 << v8)) == 0 )
    {
      ++v4;
      *(_BYTE *)(v6 + v9 + 108) |= 1 << v8;
      if ( a2 )
      {
        if ( *(_WORD *)(v6 + 40) )
          v4 += Class_CountSubclasses(v6, a2, a3);
      }
    }
    v5 += 4;
    ++v11;
  }
  return v4;
}

//----- (004D66B0) --------------------------------------------------------
int  Class_CollectSubclassNames(int a1, int a2, int a3, int a4, signed int a5)
{
  int v7; // esi
  int v8; // ebx
  int v9; // eax
  int v10; // edx
  int v14; // [esp+10h] [ebp-1Ch]
  int v15; // [esp+14h] [ebp-18h]
  unsigned int v16; // [esp+18h] [ebp-14h]
  int v17; // [esp+1Ch] [ebp-10h]

  v7 = a2;
  v16 = 0;
  v15 = (a5 - (__CFSHL__(a5 >> 31, 3) + 8 * (a5 >> 31))) >> 3;
  v14 = a5 % 8;
  v17 = 0;
  while ( *(unsigned __int16 *)(a4 + 40) > v16 )
  {
    v8 = *(_DWORD *)(v17 + *(_DWORD *)(a4 + 42));
    if ( (*(_BYTE *)(v8 + v15 + 108) & (unsigned __int8)(1 << v14)) == 0 )
    {
      *(_BYTE *)(v8 + v15 + 108) |= 1 << v14;
      *(_WORD *)(a1 + 6 * (v7++ - 1) + 14) = 2;
      v9 = Rules_GetConstructNameSymbol(v8);
      *(_DWORD *)(v10 + a1 + 16) = v9;
      if ( a3 )
      {
        if ( *(_WORD *)(v8 + 40) )
          v7 += Class_CollectSubclassNames(a1, v7, a3, v8, a5);
      }
    }
    v17 += 4;
    ++v16;
  }
  return v7 - a2;
}
// 4D66B0: could not find valid save-restore pair for ebx
// 4D6778: variable 'v10' is possibly undefined

//----- (004D67B0) --------------------------------------------------------
int  Class_ResolveNamedSlot(int a1, int a2, _BYTE *a3)
{
  int *v5; // eax
  int v6; // ecx
  unsigned int v7; // eax
  int v8; // ecx

  v5 = Rules_FindSymbolEntry(a3);
  if ( v5 )
  {
    v7 = Instance_ResolveSlotIndex(v6, (int)v5);
    if ( v7 == -1 )
    {
      Instance_ReportNoSuchSlotError(v8, v8);
      Lexer_ErrorRecover(1);
      Rules_SetMultifieldErrorValue(a1);
      return 0;
    }
    else
    {
      *(_DWORD *)(a1 + 4) = 4;
      *(_DWORD *)(a1 + 12) = 0;
      return *(_DWORD *)(*(_DWORD *)(a2 + 56) + 4 * v7);
    }
  }
  else
  {
    Lexer_ErrorRecover(1);
    Rules_SetMultifieldErrorValue(a1);
    return 0;
  }
}
// 4D67C5: variable 'v6' is possibly undefined
// 4D6800: variable 'v8' is possibly undefined

//----- (004D6971) --------------------------------------------------------
void Math_CompareAbsToEpsilon()
{
  return;
}
// 4D6971: inconsistent fpu stack

//----- (004D6B60) --------------------------------------------------------
int  Compiler_GenerateConstructTables(DWORD a1)
{
  const char *v1; // ecx
  int v2; // edx
  const char *v3; // ecx
  int v4; // eax
  const char *v5; // ecx
  int v6; // eax
  const char *v7; // ecx
  int v8; // eax
  const char *v9; // ecx
  int v10; // eax
  const char *v11; // ecx

  Rules_SetAtomicValueIndices(1);
  Compiler_WriteConstantsReferenceFile(v1, a1);
  v4 = Compiler_WriteSymbolTableFile(v3, v2);
  v6 = Compiler_WriteFloatTableFile(v5, v4);
  v8 = Compiler_WriteIntegerTableFile(v7, v6);
  v10 = Compiler_WriteBitMapTableFile(v9, v8);
  return Compiler_WriteBitMapValuesFile(v11, v10);
}
// 4D6B75: variable 'v1' is possibly undefined
// 4D6B7C: variable 'v3' is possibly undefined
// 4D6B7C: variable 'v2' is possibly undefined
// 4D6B85: variable 'v5' is possibly undefined
// 4D6B8E: variable 'v7' is possibly undefined
// 4D6B97: variable 'v9' is possibly undefined
// 4D6BA0: variable 'v11' is possibly undefined

//----- (004D6BB0) --------------------------------------------------------
int  Compiler_WriteSymbolTableFile(const char *a1, int a2)
{
  int v2; // esi
  DWORD v3; // ebp
  _DWORD **v4; // edx
  _DWORD *i; // eax
  int j; // ecx
  int result; // eax
  int v8; // edx
  int v9; // ecx
  int v10; // edi
  _DWORD *v11; // esi
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  _DWORD *v16; // [esp+0h] [ebp-30h]
  int k; // [esp+8h] [ebp-28h]
  int v19; // [esp+Ch] [ebp-24h]
  int v21; // [esp+14h] [ebp-1Ch]
  int v22; // [esp+18h] [ebp-18h]

  v2 = Rules_GetSymbolTable();
  v19 = 1;
  v3 = 1;
  v22 = 0;
  v21 = 0;
  v4 = (_DWORD **)v2;
  do
  {
    for ( i = *v4; i; ++v22 )
      i = (_DWORD *)*i;
    ++v4;
  }
  while ( v4 != (_DWORD **)(v2 + 4052) );
  if ( !v22 )
    return a2;
  for ( j = 1;
        j <= v22 / g_ClipsCodeMaxIndicesPerArray + 1;
        Output_WriteFormatted(j + 1, g_ConstructsToCImageId, g_ClipsCodeHeaderFile, (int)aExternStructSy, g_ConstructsToCImageId) )
  {
    ;
  }
  v9 = Rules_OpenConstructCodeFile(a1, 1, a2, 1u);
  if ( !v9 )
    return -1;
  v10 = 0;
  v16 = (_DWORD *)v2;
  for ( k = 0; k < 1013; ++k )
  {
    v11 = (_DWORD *)*v16;
    if ( *v16 )
    {
      do
      {
        if ( v19 )
        {
          Output_WriteFormatted(v9, 0, v9, (int)aStructSymbolha, g_ConstructsToCImageId);
          v19 = v8;
        }
        if ( *v11 )
          Output_WriteFormatted(v9, g_ClipsCodeMaxIndicesPerArray, v9, (int)aSD_DD_2, g_ConstructsToCImageId);
        else
          Output_WriteFormatted(v9, v8, v9, (int)aNull_8, (char)v16);
        ++v10;
        Output_WriteFormatted(v12, k, v12, (int)aLd000D, v11[1] + 1);
        Compiler_WriteEscapedStringLiteral(v13, v11[4], v13, v10);
        if ( ++v21 == v22 || v10 >= g_ClipsCodeMaxIndicesPerArray )
        {
          Output_WriteFormatted(v14, v22, v14, (int)asc_50D12C, (char)v16);
          fclose_(v15);
          ++v3;
          v8 = v22;
          ++a2;
          v10 = 0;
          if ( v21 < v22 )
          {
            result = Rules_OpenConstructCodeFile(a1, 1, a2, v3);
            v9 = result;
            if ( !result )
              return result;
            v19 = 1;
          }
        }
        else
        {
          Output_WriteFormatted(v14, v22, v14, (int)asc_50D134, (char)v16);
        }
        v11 = (_DWORD *)*v11;
      }
      while ( v11 );
    }
    ++v16;
  }
  return a2;
}
// 4D6C2C: variable 'j' is possibly undefined
// 4D6CA4: variable 'v9' is possibly undefined
// 4D6CAC: variable 'v8' is possibly undefined
// 4D6CBF: variable 'v16' is possibly undefined
// 4D6CD8: variable 'v12' is possibly undefined
// 4D6CE9: variable 'v13' is possibly undefined
// 4D6D05: variable 'v14' is possibly undefined
// 4D6D0F: variable 'v15' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51ACF0: using guessed type int dword_51ACF0;
// 54E6D0: using guessed type int dword_54E6D0;
// 54E6E8: using guessed type int dword_54E6E8;

//----- (004D6E00) --------------------------------------------------------
int  Compiler_WriteBitMapTableFile(const char *a1, int a2)
{
  int v2; // esi
  int v3; // edi
  _DWORD **v4; // edx
  _DWORD *i; // eax
  signed int j; // ebp
  int result; // eax
  int v8; // edx
  int v9; // ecx
  int v10; // ebp
  int *m; // esi
  int v12; // edx
  int v13; // edx
  unsigned __int16 v14; // ax
  int v15; // ecx
  int **v16; // [esp+0h] [ebp-38h]
  int k; // [esp+8h] [ebp-30h]
  int v19; // [esp+Ch] [ebp-2Ch]
  int v20; // [esp+10h] [ebp-28h]
  int v22; // [esp+18h] [ebp-20h]
  int v23; // [esp+1Ch] [ebp-1Ch]
  int v24; // [esp+20h] [ebp-18h]

  v2 = Rules_GetBitmapTable();
  v3 = 0;
  v20 = 1;
  v24 = 1;
  v19 = 1;
  v23 = 0;
  v22 = 0;
  v4 = (_DWORD **)v2;
  do
  {
    for ( i = *v4; i; ++v23 )
      i = (_DWORD *)*i;
    ++v4;
  }
  while ( v4 != (_DWORD **)(v2 + 668) );
  if ( !v23 )
    return a2;
  for ( j = 1; j <= v23 / g_ClipsCodeMaxIndicesPerArray + 1; ++j )
    Output_WriteFormatted(g_ClipsCodeMaxIndicesPerArray, g_ClipsCodeHeaderFile, g_ClipsCodeHeaderFile, (int)aExternStructBi, g_ConstructsToCImageId);
  v8 = Rules_OpenConstructCodeFile(a1, 1, a2, j);
  if ( !v8 )
    return -1;
  v10 = 0;
  v16 = (int **)v2;
  for ( k = 0; k < 167; ++k )
  {
    for ( m = *v16; m; m = (int *)*m )
    {
      if ( v20 )
      {
        Output_WriteFormatted(v24, v8, v8, (int)aStructBitmapha, g_ConstructsToCImageId);
        v20 = 0;
      }
      if ( *m )
      {
        if ( v10 + 1 < g_ClipsCodeMaxIndicesPerArray )
          Output_WriteFormatted(g_ConstructsToCImageId, v8, v8, (int)aBD_DD, g_ConstructsToCImageId);
        else
          Output_WriteFormatted(v9, v8, v8, (int)aBD_DD, g_ConstructsToCImageId);
      }
      else
      {
        Output_WriteFormatted(v9, v8, v8, (int)aNull_8, (char)v16);
      }
      Output_WriteFormatted(g_ConstructsToCImageId, v12, v12, (int)aLd000DCharLD_D, m[1] + 1);
      v14 = *((_WORD *)m + 10);
      v3 += v14 >> 2;
      if ( (v14 & 3) != 0 )
        ++v3;
      if ( v3 >= g_ClipsCodeMaxIndicesPerArray )
      {
        v3 = 0;
        ++v19;
      }
      ++v10;
      if ( ++v22 == v23 || v10 >= g_ClipsCodeMaxIndicesPerArray )
      {
        Output_WriteFormatted(v23, v13, v13, (int)asc_50D12C, (char)v16);
        v10 = 0;
        fclose_(v15);
        v9 = a2 + 1;
        ++v24;
        ++a2;
        if ( v22 < v23 )
        {
          result = Rules_OpenConstructCodeFile(a1, 1, a2, 0);
          v8 = result;
          if ( !result )
            return result;
          v20 = 1;
        }
      }
      else
      {
        Output_WriteFormatted(v23, v13, v13, (int)asc_50D134, (char)v16);
      }
    }
    v9 = (int)++v16;
  }
  return a2;
}
// 4D6EF6: variable 'v8' is possibly undefined
// 4D6F13: variable 'v9' is possibly undefined
// 4D6F13: variable 'v16' is possibly undefined
// 4D6F3F: variable 'v12' is possibly undefined
// 4D6F88: variable 'v13' is possibly undefined
// 4D6F94: variable 'v15' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51ACF0: using guessed type int dword_51ACF0;
// 54E6D0: using guessed type int dword_54E6D0;
// 54E6E8: using guessed type int dword_54E6E8;

//----- (004D7090) --------------------------------------------------------
int  Compiler_WriteBitMapValuesFile(const char *a1, int a2)
{
  DWORD v2; // ebp
  int **v3; // esi
  int *i; // eax
  unsigned __int16 v5; // dx
  int v6; // ebx
  int j; // ecx
  int result; // eax
  int v9; // ecx
  int *m; // esi
  unsigned __int16 v11; // ax
  int v12; // edx
  int v13; // edi
  unsigned int v14; // ebp
  unsigned int v15; // edx
  unsigned int v16; // eax
  int v17; // ecx
  char v18; // bl
  int v19; // edi
  int v20; // ecx
  DWORD v21; // ebp
  char v22; // [esp+1h] [ebp-45h]
  int v23; // [esp+2h] [ebp-44h]
  int **v24; // [esp+6h] [ebp-40h]
  int k; // [esp+Ah] [ebp-3Ch]
  const char *v26; // [esp+Eh] [ebp-38h]
  int v27; // [esp+12h] [ebp-34h]
  int v28; // [esp+16h] [ebp-30h]
  int v29; // [esp+1Ah] [ebp-2Ch]
  int v30; // [esp+1Eh] [ebp-28h]
  int v31; // [esp+22h] [ebp-24h]
  int v32; // [esp+26h] [ebp-20h]
  int v33; // [esp+2Ah] [ebp-1Ch]
  int v34; // [esp+2Eh] [ebp-18h]

  v26 = a1;
  v29 = a2;
  v2 = Rules_GetBitmapTable();
  v3 = (int **)v2;
  v27 = 1;
  v28 = 1;
  v32 = 0;
  v31 = 0;
  do
  {
    for ( i = *v3; i; i = (int *)*i )
    {
      v5 = *((_WORD *)i + 10);
      v6 = (v5 >> 2) + v32;
      v32 = v6;
      if ( (v5 & 3) != 0 )
        v32 = v6 + 1;
    }
    ++v3;
  }
  while ( v3 != (int **)(v2 + 668) );
  if ( !v32 )
    return v29;
  for ( j = 1;
        j <= v32 / g_ClipsCodeMaxIndicesPerArray + 1;
        Output_WriteFormatted(j + 1, g_ClipsCodeHeaderFile, g_ClipsCodeHeaderFile, (int)aExternUnsigned, g_ConstructsToCImageId) )
  {
    v22 = HIBYTE(j);
  }
  v34 = Rules_OpenConstructCodeFile(v26, 1, v29, v2);
  if ( !v34 )
    return -1;
  v24 = (int **)v2;
  v30 = 0;
  for ( k = 0; k < 167; ++k )
  {
    for ( m = *v24; m; m = (int *)*m )
    {
      if ( v27 )
      {
        v22 = HIBYTE(v28);
        Output_WriteFormatted(0, v34, v34, (int)aUnsignedLongLD, g_ConstructsToCImageId);
        v27 = v9;
      }
      v11 = *((_WORD *)m + 10);
      v12 = v11 >> 2;
      v33 = v12;
      if ( (v11 & 3) != 0 )
        v33 = v12 + 1;
      v13 = 0;
      if ( v33 > 0 )
      {
        v14 = 0;
        do
        {
          if ( v13 > 0 )
            Output_WriteFormatted(v9, v12, v34, (int)asc_50D1F8, v23);
          v15 = 0;
          v23 = 0;
          v16 = v14;
          do
          {
            v17 = *((unsigned __int16 *)m + 10);
            if ( v16 >= (unsigned __int16)v17 )
              break;
            v17 = m[4];
            ++v15;
            v18 = *(_BYTE *)(v17 + v16++);
            *(&v22 + v15) = v18;
          }
          while ( v15 < 4 );
          Output_WriteFormatted(v17, v34, v34, (int)a0xLxl, v23);
          ++v13;
          v9 = v33;
          v14 += 4;
        }
        while ( v13 < v33 );
      }
      v19 = v33 + v30;
      v31 += v33;
      v30 += v33;
      if ( v31 == v32 || v19 >= g_ClipsCodeMaxIndicesPerArray )
      {
        Output_WriteFormatted(v9, v12, v34, (int)asc_50D204, v23);
        fclose_(v20);
        v30 = 0;
        v21 = v28 + 1;
        ++v29;
        ++v28;
        if ( v31 < v32 )
        {
          result = Rules_OpenConstructCodeFile(v26, 1, v29, v21);
          v34 = result;
          if ( !result )
            return result;
          v27 = 1;
        }
      }
      else
      {
        Output_WriteFormatted(v34, v12, v34, (int)asc_50D208, v23);
      }
    }
    v9 = (int)++v24;
  }
  return v29;
}
// 4D7124: variable 'j' is possibly undefined
// 4D71B3: variable 'v9' is possibly undefined
// 4D71EB: variable 'v12' is possibly undefined
// 4D7273: variable 'v20' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51ACF0: using guessed type int dword_51ACF0;
// 54E6D0: using guessed type int dword_54E6D0;
// 54E6E8: using guessed type int dword_54E6E8;

//----- (004D7330) --------------------------------------------------------
int  Compiler_WriteFloatTableFile(const char *a1, int a2)
{
  DWORD v2; // ebp
  _DWORD **v3; // edx
  _DWORD *i; // eax
  int j; // edi
  int result; // eax
  int v7; // edx
  int v8; // ecx
  int v9; // edi
  double *k; // esi
  int v11; // edx
  int v12; // ecx
  char v13; // al
  int v14; // edx
  int v15; // ecx
  int v16; // edx
  int v17; // ecx
  int v18; // ecx
  int v19; // [esp+0h] [ebp-34h]
  double **v20; // [esp+4h] [ebp-30h]
  int v22; // [esp+Ch] [ebp-28h]
  int v23; // [esp+10h] [ebp-24h]
  int v25; // [esp+18h] [ebp-1Ch]
  int v26; // [esp+1Ch] [ebp-18h]

  v19 = Rules_GetFloatTable();
  v23 = 1;
  v2 = 1;
  v26 = 0;
  v25 = 0;
  v3 = (_DWORD **)v19;
  do
  {
    for ( i = *v3; i; ++v26 )
      i = (_DWORD *)*i;
    ++v3;
  }
  while ( v3 != (_DWORD **)(v19 + 2012) );
  if ( !v26 )
    return a2;
  for ( j = 1; j <= v26 / g_ClipsCodeMaxIndicesPerArray + 1; ++j )
    Output_WriteFormatted(g_ClipsCodeMaxIndicesPerArray, v26 % g_ClipsCodeMaxIndicesPerArray, g_ClipsCodeHeaderFile, (int)aExternStructFl, g_ConstructsToCImageId);
  v7 = Rules_OpenConstructCodeFile(a1, 1, a2, 1u);
  if ( !v7 )
    return -1;
  v9 = 0;
  v22 = 0;
  v20 = (double **)v19;
  do
  {
    for ( k = *v20; k; k = *(double **)k )
    {
      if ( v23 )
      {
        Output_WriteFormatted(g_ConstructsToCImageId, v7, v7, (int)aStructFloathas, g_ConstructsToCImageId);
        v23 = 0;
      }
      if ( *(_DWORD *)k )
        Output_WriteFormatted(g_ClipsCodeMaxIndicesPerArray, v7, v7, (int)aFD_DD, g_ConstructsToCImageId);
      else
        Output_WriteFormatted(v8, v7, v7, (int)aNull_8, v19);
      Output_WriteFormatted(v22, v11, v11, (int)aLd000D, *((_DWORD *)k + 1) + 1);
      v13 = Rules_FloatToSymbol(v12, k[2]);
      Output_WriteFormatted(v15, v14, v14, (int)aS_11, v13);
      ++v9;
      v17 = v25 + 1;
      v25 = v17;
      if ( v17 == v26 || v9 >= g_ClipsCodeMaxIndicesPerArray )
      {
        ++v2;
        Output_WriteFormatted(v17, v16, v16, (int)asc_50D12C, v19);
        v9 = 0;
        fclose_(v18);
        v8 = ++a2;
        if ( v25 < v26 )
        {
          result = Rules_OpenConstructCodeFile(a1, 1, a2, v2);
          v7 = result;
          if ( !result )
            return result;
          v23 = 1;
        }
      }
      else
      {
        Output_WriteFormatted(v17, v16, v16, (int)asc_50D134, v19);
      }
    }
    v8 = (int)++v20;
    ++v22;
  }
  while ( v22 < 503 );
  return a2;
}
// 4D7429: variable 'v7' is possibly undefined
// 4D7444: variable 'v8' is possibly undefined
// 4D7444: variable 'v19' is possibly undefined
// 4D745C: variable 'v11' is possibly undefined
// 4D746C: variable 'v12' is possibly undefined
// 4D7478: variable 'v15' is possibly undefined
// 4D7478: variable 'v14' is possibly undefined
// 4D749D: variable 'v16' is possibly undefined
// 4D74A9: variable 'v18' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51ACF0: using guessed type int dword_51ACF0;
// 54E6D0: using guessed type int dword_54E6D0;
// 54E6E8: using guessed type int dword_54E6E8;

//----- (004D75A0) --------------------------------------------------------
int  Compiler_WriteIntegerTableFile(const char *a1, int a2)
{
  DWORD v2; // ebp
  _DWORD **v3; // edx
  _DWORD *i; // eax
  int j; // edi
  int result; // eax
  int v7; // edx
  int v8; // ecx
  int v9; // edi
  _DWORD *v10; // esi
  int v11; // edx
  int v12; // edx
  int v13; // ecx
  int v14; // edx
  int v15; // ecx
  int v16; // [esp+0h] [ebp-34h]
  _DWORD *v17; // [esp+4h] [ebp-30h]
  int v19; // [esp+Ch] [ebp-28h]
  int v20; // [esp+10h] [ebp-24h]
  int v22; // [esp+18h] [ebp-1Ch]
  int v23; // [esp+1Ch] [ebp-18h]

  v16 = Rules_GetIntegerTable();
  v20 = 1;
  v2 = 1;
  v23 = 0;
  v22 = 0;
  v3 = (_DWORD **)v16;
  do
  {
    for ( i = *v3; i; ++v23 )
      i = (_DWORD *)*i;
    ++v3;
  }
  while ( v3 != (_DWORD **)(v16 + 668) );
  if ( !v23 )
    return a2;
  for ( j = 1; j <= v23 / g_ClipsCodeMaxIndicesPerArray + 1; ++j )
    Output_WriteFormatted(g_ClipsCodeMaxIndicesPerArray, v23 % g_ClipsCodeMaxIndicesPerArray, g_ClipsCodeHeaderFile, (int)aExternStructIn, g_ConstructsToCImageId);
  v7 = Rules_OpenConstructCodeFile(a1, 1, a2, 1u);
  if ( !v7 )
    return -1;
  v9 = 0;
  v19 = 0;
  v17 = (_DWORD *)v16;
  do
  {
    v10 = (_DWORD *)*v17;
    if ( *v17 )
    {
      do
      {
        if ( v20 )
        {
          Output_WriteFormatted(g_ConstructsToCImageId, v7, v7, (int)aStructIntegerh, g_ConstructsToCImageId);
          v20 = 0;
        }
        if ( *v10 )
          Output_WriteFormatted(g_ClipsCodeMaxIndicesPerArray, v7, v7, (int)aID_DD, g_ConstructsToCImageId);
        else
          Output_WriteFormatted(v8, v7, v7, (int)aNull_8, v16);
        Output_WriteFormatted(v19, v11, v11, (int)aLd000D, v10[1] + 1);
        Output_WriteFormatted(v13, v12, v12, (int)aLd, v10[4]);
        ++v9;
        if ( ++v22 == v23 || v9 >= g_ClipsCodeMaxIndicesPerArray )
        {
          Output_WriteFormatted(v23, v14, v14, (int)asc_50D12C, v16);
          fclose_(v15);
          ++v2;
          v8 = v23;
          ++a2;
          v9 = 0;
          if ( v22 < v23 )
          {
            result = Rules_OpenConstructCodeFile(a1, 1, a2, v2);
            v7 = result;
            if ( !result )
              return result;
            v20 = 1;
          }
        }
        else
        {
          Output_WriteFormatted(v23, v14, v14, (int)asc_50D134, v16);
        }
        v10 = (_DWORD *)*v10;
      }
      while ( v10 );
    }
    v8 = (int)++v17;
    ++v19;
  }
  while ( v19 < 167 );
  return a2;
}
// 4D7699: variable 'v7' is possibly undefined
// 4D76B4: variable 'v8' is possibly undefined
// 4D76B4: variable 'v16' is possibly undefined
// 4D76CC: variable 'v11' is possibly undefined
// 4D76DE: variable 'v13' is possibly undefined
// 4D76DE: variable 'v12' is possibly undefined
// 4D7702: variable 'v14' is possibly undefined
// 4D770C: variable 'v15' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51ACF0: using guessed type int dword_51ACF0;
// 54E6D0: using guessed type int dword_54E6D0;
// 54E6E8: using guessed type int dword_54E6E8;

//----- (004D7800) --------------------------------------------------------
signed int  Compiler_WriteConstantsReferenceFile(const char *a1, DWORD a2)
{
  int *v3; // esi
  signed int result; // eax
  int v5; // ebx
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  int *v9; // esi
  int v10; // edx
  int v11; // ecx
  int v12; // ebx
  int v13; // edx
  int v14; // edx
  int v15; // ecx
  int v16; // ecx
  int v17; // ebp
  int v18; // edx
  int v19; // ebx
  int v20; // esi
  int v21; // edx
  int *v22; // ecx
  int v23; // ecx
  int *v24; // esi
  int v25; // edx
  int v26; // ebx
  int v27; // edx
  int v28; // ecx
  int v29; // ecx
  int v30; // edx
  int v31; // ecx
  char v32; // [esp+0h] [ebp-18h]
  char v33; // [esp+0h] [ebp-18h]
  char v34; // [esp+0h] [ebp-18h]
  char v35; // [esp+0h] [ebp-18h]

  v3 = (int *)Rules_GetSymbolTable();
  result = Rules_OpenConstructCodeFile(a1, 1, 1, a2);
  v5 = result;
  if ( result )
  {
    Output_WriteFormatted(g_ConstructsToCImageId, result, g_ClipsCodeHeaderFile, (int)aExternStruct_0, g_ConstructsToCImageId);
    Output_WriteFormatted(0, v6, v6, (int)aStructSymbol_0, g_ConstructsToCImageId);
    do
    {
      Compiler_WriteSymbolReference(v5, *v3, v7);
      if ( v8 != 1012 )
        Output_WriteFormatted(v8, v8 + 1, v5, (int)asc_50D208, v32);
      v7 = v8 + 1;
      ++v3;
    }
    while ( v7 < 1013 );
    Output_WriteFormatted(v7, 1, v5, (int)asc_50D204, v32);
    fclose_(0);
    v9 = (int *)Rules_GetFloatTable();
    result = Rules_OpenConstructCodeFile(a1, v10, 2, a2);
    v12 = result;
    if ( result )
    {
      Output_WriteFormatted(v11, result, g_ClipsCodeHeaderFile, (int)aExternStruct_1, g_ConstructsToCImageId);
      Output_WriteFormatted(0, v13, v13, (int)aStructFloath_0, g_ConstructsToCImageId);
      do
      {
        if ( *v9 )
          Compiler_WriteFloatReference(v12, *v9);
        else
          Output_WriteFormatted(v15, v14, v12, (int)aNull_9, v33);
        v14 = v16 + 1;
        if ( v16 != 502 )
          Output_WriteFormatted(v16, v14, v12, (int)asc_50D208, v33);
        v15 = v16 + 1;
        ++v9;
      }
      while ( v15 < 503 );
      Output_WriteFormatted(v15, 1, v12, (int)asc_50D204, v33);
      fclose_(0);
      v17 = Rules_GetIntegerTable();
      result = Rules_OpenConstructCodeFile(a1, v18, 3, v17);
      v19 = result;
      if ( result )
      {
        Output_WriteFormatted(g_ConstructsToCImageId, result, g_ClipsCodeHeaderFile, (int)aExternStruct_2, g_ConstructsToCImageId);
        v20 = 0;
        Output_WriteFormatted(v17, v21, v21, (int)aStructIntege_0, g_ConstructsToCImageId);
        do
        {
          if ( *v22 )
            Compiler_WriteIntegerReference(v19, *v22);
          else
            Output_WriteFormatted((int)v22, 0, v19, (int)aNull_9, v34);
          if ( v20 != 166 )
            Output_WriteFormatted(v23, v20 + 1, v19, (int)asc_50D208, v34);
          ++v20;
          v22 = (int *)(v23 + 4);
        }
        while ( v20 < 167 );
        Output_WriteFormatted((int)v22, 1, v19, (int)asc_50D204, v34);
        fclose_(0);
        v24 = (int *)Rules_GetBitmapTable();
        result = Rules_OpenConstructCodeFile(a1, v25, 4, v17);
        v26 = result;
        if ( result )
        {
          Output_WriteFormatted(g_ConstructsToCImageId, result, g_ClipsCodeHeaderFile, (int)aExternStruct_3, g_ConstructsToCImageId);
          Output_WriteFormatted(0, v27, v27, (int)aStructBitmap_0, g_ConstructsToCImageId);
          do
          {
            Compiler_WriteBitMapReference(v26, *v24, v28);
            v30 = v29 + 1;
            if ( v29 != 166 )
              Output_WriteFormatted(v29, v30, v26, (int)asc_50D208, v35);
            v28 = v29 + 1;
            ++v24;
          }
          while ( v28 < 167 );
          Output_WriteFormatted(v28, v30, v26, (int)asc_50D204, v35);
          fclose_(v31);
          return 1;
        }
      }
    }
  }
  return result;
}
// 4D785C: variable 'v6' is possibly undefined
// 4D7874: variable 'v7' is possibly undefined
// 4D7882: variable 'v8' is possibly undefined
// 4D788A: variable 'v32' is possibly undefined
// 4D78C8: variable 'v10' is possibly undefined
// 4D78EB: variable 'v11' is possibly undefined
// 4D7907: variable 'v13' is possibly undefined
// 4D7920: variable 'v15' is possibly undefined
// 4D7920: variable 'v14' is possibly undefined
// 4D7920: variable 'v33' is possibly undefined
// 4D7928: variable 'v16' is possibly undefined
// 4D7977: variable 'v18' is possibly undefined
// 4D79B8: variable 'v21' is possibly undefined
// 4D79C0: variable 'v22' is possibly undefined
// 4D79D0: variable 'v34' is possibly undefined
// 4D79E9: variable 'v23' is possibly undefined
// 4D7A27: variable 'v25' is possibly undefined
// 4D7A66: variable 'v27' is possibly undefined
// 4D7A74: variable 'v28' is possibly undefined
// 4D7A79: variable 'v29' is possibly undefined
// 4D7A8A: variable 'v35' is possibly undefined
// 4D7AA4: variable 'v30' is possibly undefined
// 4D7AAE: variable 'v31' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 54E6D0: using guessed type int dword_54E6D0;
// 54E6E8: using guessed type int dword_54E6E8;

//----- (004D7AE0) --------------------------------------------------------
int  Compiler_WriteSymbolReference(int a1, int a2, int a3)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( a2 )
    return Output_WriteFormatted(
             *(_DWORD *)(a2 + 12) << 16 >> 18,
             (*(_DWORD *)(a2 + 12) << 16 >> 18) % (unsigned int)g_ClipsCodeMaxIndicesPerArray,
             a1,
             (int)aSD_DD_3,
             g_ConstructsToCImageId);
  else
    return Output_WriteFormatted(a3, 0, a1, (int)aNull_9, v4);
}
// 4D7AEE: variable 'v4' is possibly undefined
// 51ACF0: using guessed type int dword_51ACF0;
// 54E6D0: using guessed type int dword_54E6D0;

//----- (004D7B40) --------------------------------------------------------
int  Compiler_WriteFloatReference(int a1, int a2)
{
  return Output_WriteFormatted(
           *(_DWORD *)(a2 + 12) << 16 >> 18,
           (*(_DWORD *)(a2 + 12) << 16 >> 18) % (unsigned int)g_ClipsCodeMaxIndicesPerArray,
           a1,
           (int)aFD_DD_0,
           g_ConstructsToCImageId);
}
// 51ACF0: using guessed type int dword_51ACF0;
// 54E6D0: using guessed type int dword_54E6D0;

//----- (004D7B90) --------------------------------------------------------
int  Compiler_WriteIntegerReference(int a1, int a2)
{
  return Output_WriteFormatted(
           *(_DWORD *)(a2 + 12) << 16 >> 18,
           (*(_DWORD *)(a2 + 12) << 16 >> 18) % (unsigned int)g_ClipsCodeMaxIndicesPerArray,
           a1,
           (int)aID_DD_0,
           g_ConstructsToCImageId);
}
// 51ACF0: using guessed type int dword_51ACF0;
// 54E6D0: using guessed type int dword_54E6D0;

//----- (004D7BE0) --------------------------------------------------------
int  Compiler_WriteBitMapReference(int a1, int a2, int a3)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( a2 )
    return Output_WriteFormatted(
             *(_DWORD *)(a2 + 12) << 16 >> 18,
             (*(_DWORD *)(a2 + 12) << 16 >> 18) % (unsigned int)g_ClipsCodeMaxIndicesPerArray,
             a1,
             (int)aBD_DD_0,
             g_ConstructsToCImageId);
  else
    return Output_WriteFormatted(a3, 0, a1, (int)aNull_9, v4);
}
// 4D7BEE: variable 'v4' is possibly undefined
// 51ACF0: using guessed type int dword_51ACF0;
// 54E6D0: using guessed type int dword_54E6D0;

//----- (004D7C40) --------------------------------------------------------
int  Compiler_WriteEscapedStringLiteral(int a1, int a2, int a3, char a4)
{
  const char *v5; // edx
  signed int v6; // esi
  unsigned int v7; // kr04_4
  const char *v8; // ecx
  char v9; // ah
  int v10; // edx
  int v11; // ecx
  char v13; // [esp-Ch] [ebp-10h]

  Output_WriteFormatted(a3, a2, a1, (int)asc_50D454, a4);
  v6 = 0;
  v7 = strlen(v5) + 1;
  v8 = (const char *)(v7 - 1);
  if ( (int)(v7 - 1) > 0 )
  {
    v8 = v5;
    do
    {
      v9 = *v8;
      if ( *v8 == 34 || v9 == 92 )
      {
        CRT_PutcToStream(v8, a1);
      }
      else if ( v9 == 10 )
      {
        CRT_PutcToStream(v8, a1);
        v10 = a1;
        goto LABEL_6;
      }
      v10 = a1;
LABEL_6:
      CRT_PutcToStream(v8, v10);
      ++v6;
      v8 = (const char *)(v11 + 1);
    }
    while ( v6 < (int)(v7 - 1) );
  }
  return Output_WriteFormatted((int)v8, (int)v5, a1, (int)asc_50D454, v13);
}
// 4D7C5A: variable 'v5' is possibly undefined
// 4D7C83: variable 'v8' is possibly undefined
// 4D7C89: variable 'v11' is possibly undefined
// 4D7C94: variable 'v13' is possibly undefined
// 488A97: using guessed type int __fastcall sub_488A97(_DWORD, _DWORD);

//----- (004D7CC0) --------------------------------------------------------
int  Compiler_WriteConstraintTableFile(const char *a1, int a2, DWORD a3, int a4, int a5)
{
  int v6; // eax
  int i; // esi
  int v8; // ecx
  int v9; // ecx
  int result; // eax
  int v11; // edi
  int j; // ecx
  int v13; // ecx
  int v14; // edi
  int v15; // edx
  int k; // esi
  int v17; // edx
  int v18; // ecx
  int v19; // edx
  int v20; // ecx
  int v21; // edx
  int v22; // ecx
  int v23; // edx
  int v24; // ecx
  int v25; // edx
  int v26; // ecx
  int v27; // edx
  int v28; // ecx
  int v29; // edx
  int v30; // ecx
  int v31; // edx
  int v32; // ecx
  int v33; // edx
  int v34; // ecx
  int v35; // ecx
  int v36; // ebx
  int v37; // [esp+0h] [ebp-30h]
  char v38; // [esp+0h] [ebp-30h]
  char v39; // [esp+0h] [ebp-30h]
  char v40; // [esp+0h] [ebp-30h]
  char v41; // [esp+0h] [ebp-30h]
  char v42; // [esp+0h] [ebp-30h]
  char v43; // [esp+0h] [ebp-30h]
  int v44; // [esp+4h] [ebp-2Ch]
  int v46; // [esp+Ch] [ebp-24h]
  int v47; // [esp+10h] [ebp-20h]
  int v48; // [esp+14h] [ebp-1Ch]
  int v49; // [esp+18h] [ebp-18h]
  int v50; // [esp+1Ch] [ebp-14h]
  unsigned __int16 v51; // [esp+20h] [ebp-10h]

  v37 = a2;
  v46 = 1;
  v47 = 1;
  v50 = 1;
  v6 = 0;
  v51 = 0;
  do
  {
    for ( i = *(_DWORD *)(g_ConstraintHashTable + v6); i; ++v51 )
    {
      *(_WORD *)(i + 4) = v51;
      i = *(_DWORD *)(i + 30);
    }
    v6 += 4;
  }
  while ( v6 != 668 );
  if ( !Rules_DynamicConstraintCheckingEnabled() && v51 )
  {
    Rules_PrintWarningID((int)aCstrncmp, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aConstraintsA_0, v8);
    Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aWhenDynamicC_0, v9);
    return -1;
  }
  if ( !v51 )
    return -1;
  v11 = 1;
  for ( j = a5; v11 <= v51 / j + 1; Output_WriteFormatted(j, v51 % j, a4, (int)aExternConstrai, a3) )
    ++v11;
  v14 = Rules_OpenConstructCodeFile(a1, v37, 1, a3);
  if ( !v14 )
    return -1;
  v49 = 0;
  v48 = 0;
  v44 = 0;
  do
  {
    v15 = v44;
    for ( k = *(_DWORD *)(v44 + g_ConstraintHashTable); k; k = *(_DWORD *)(k + 30) )
    {
      if ( v46 )
      {
        Output_WriteFormatted(0, v50, v14, (int)aConstraint_rec, a3);
        v46 = v13;
      }
      Output_WriteFormatted(v13, v15, v14, (int)aDDDDDDDDDDDDDD, *(_BYTE *)k & 1);
      Output_WriteFormatted(v18, v17, v14, (int)a0, v37);
      Rules_WriteExpressionRefToCode(v14, *(__int16 **)(k + 6), a5, a3);
      Output_WriteFormatted(v20, v19, v14, (int)asc_50D54C, v38);
      Rules_WriteExpressionRefToCode(v14, *(__int16 **)(k + 10), a5, a3);
      Output_WriteFormatted(v22, v21, v14, (int)asc_50D54C, v39);
      Rules_WriteExpressionRefToCode(v14, *(__int16 **)(k + 14), a5, a3);
      Output_WriteFormatted(v24, v23, v14, (int)asc_50D54C, v40);
      Rules_WriteExpressionRefToCode(v14, *(__int16 **)(k + 18), a5, a3);
      Output_WriteFormatted(v26, v25, v14, (int)asc_50D54C, v41);
      Rules_WriteExpressionRefToCode(v14, *(__int16 **)(k + 22), a5, a3);
      Output_WriteFormatted(v28, v27, v14, (int)aNull_10, v42);
      if ( *(_DWORD *)(k + 30) )
      {
        if ( v49 + 1 < a5 )
          Output_WriteFormatted(v50, a5, v14, (int)aCD_DD, a3);
        else
          Output_WriteFormatted(v30, a5, v14, (int)aCD_DD, a3);
      }
      else
      {
        Output_WriteFormatted(v30, v29, v14, (int)aNull_11, v43);
      }
      Output_WriteFormatted(v32, v31, v14, (int)aDD_1, *(_DWORD *)(k + 34));
      v33 = v48 + 1;
      v34 = v49 + 1;
      v48 = v33;
      ++v49;
      if ( v51 == v33 || v34 >= a5 )
      {
        Output_WriteFormatted(v34, v33, v14, (int)asc_50D578, v43);
        fclose_(0);
        v49 = v35;
        v13 = v48;
        v36 = v47 + 1;
        v15 = v50 + 1;
        ++v47;
        ++v50;
        if ( v51 > v48 )
        {
          result = Rules_OpenConstructCodeFile(a1, 1, v36, a3);
          v14 = result;
          if ( !result )
            return result;
          v46 = 1;
        }
      }
      else
      {
        Output_WriteFormatted(v34, v33, v14, (int)asc_50D580, v43);
      }
    }
    v13 = v44 + 4;
    v44 = v13;
  }
  while ( v13 < 668 );
  return v47;
}
// 4D7D49: variable 'v8' is possibly undefined
// 4D7D58: variable 'v9' is possibly undefined
// 4D7D88: variable 'j' is possibly undefined
// 4D7DFA: variable 'v13' is possibly undefined
// 4D7E9A: variable 'v15' is possibly undefined
// 4D7EAA: variable 'v18' is possibly undefined
// 4D7EAA: variable 'v17' is possibly undefined
// 4D7EAA: variable 'v37' is possibly undefined
// 4D7EC8: variable 'v20' is possibly undefined
// 4D7EC8: variable 'v19' is possibly undefined
// 4D7EC8: variable 'v38' is possibly undefined
// 4D7EE6: variable 'v22' is possibly undefined
// 4D7EE6: variable 'v21' is possibly undefined
// 4D7EE6: variable 'v39' is possibly undefined
// 4D7F04: variable 'v24' is possibly undefined
// 4D7F04: variable 'v23' is possibly undefined
// 4D7F04: variable 'v40' is possibly undefined
// 4D7F22: variable 'v26' is possibly undefined
// 4D7F22: variable 'v25' is possibly undefined
// 4D7F22: variable 'v41' is possibly undefined
// 4D7F3E: variable 'v28' is possibly undefined
// 4D7F3E: variable 'v27' is possibly undefined
// 4D7F3E: variable 'v42' is possibly undefined
// 4D7F57: variable 'v30' is possibly undefined
// 4D7F57: variable 'v29' is possibly undefined
// 4D7F57: variable 'v43' is possibly undefined
// 4D7F6E: variable 'v32' is possibly undefined
// 4D7F6E: variable 'v31' is possibly undefined
// 4D7FB8: variable 'v35' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51A610: using guessed type char *off_51A610[6];
// 54E694: using guessed type int dword_54E694;

//----- (004D8090) --------------------------------------------------------
int  Compiler_WriteConstraintReference(int a1, int a2, int a3, char a4)
{
  char v8; // [esp+0h] [ebp-8h]

  if ( a2 && Rules_DynamicConstraintCheckingEnabled() )
    return Output_WriteFormatted(*(unsigned __int16 *)(a2 + 4), *(unsigned __int16 *)(a2 + 4) % a3, a1, (int)aCD_DD_0, a4);
  else
    return Output_WriteFormatted(a3, a2, a1, (int)aNull_21, v8);
}
// 4D80AB: variable 'a3' is possibly undefined
// 4D80AB: variable 'a2' is possibly undefined
// 4D80AB: variable 'v8' is possibly undefined

//----- (004D80F0) --------------------------------------------------------
int Compiler_RegisterModuleCodeItem()
{
  int result; // eax

  result = Rules_AddCodeGeneratorItem((int)aDefmodule_2, 200, (int)Compiler_WriteModuleListSetupCode, (int)Compiler_AssignModuleIndices, (int)Compiler_WriteModuleTableFile, 3);
  g_ClipsDefmoduleCompilerItem = result;
  return result;
}
// 4D8120: using guessed type int sub_4D8120();
// 54E908: using guessed type int dword_54E908;

//----- (004D8120) --------------------------------------------------------
int Compiler_AssignModuleIndices()
{
  int result; // eax
  int i; // ecx
  int v2; // ecx

  result = Module_NextEnum(0);
  for ( i = 0; result; i = v2 + 1 )
  {
    *(_DWORD *)(result + 24) = i;
    result = Module_NextEnum(result);
  }
  return result;
}
// 4D8136: variable 'v2' is possibly undefined
// 4D8120: using guessed type int sub_4D8120();

//----- (004D8150) --------------------------------------------------------
int  Compiler_WriteModuleReference(int a1, int a2)
{
  char v3; // [esp+0h] [ebp-Ch]

  if ( a2 )
    return Output_WriteFormatted(
             a2,
             *(_DWORD *)(g_ClipsDefmoduleCompilerItem + 20),
             a1,
             (int)aSD_LdLd_5,
             *(_DWORD *)(*(_DWORD *)(g_ClipsDefmoduleCompilerItem + 20) + 4));
  else
    return Output_WriteFormatted(0, 0, a1, (int)aNull_18, v3);
}
// 4D8161: variable 'v3' is possibly undefined
// 51ACF0: using guessed type int dword_51ACF0;
// 54E6D0: using guessed type int dword_54E6D0;
// 54E908: using guessed type int dword_54E908;

//----- (004D81C0) --------------------------------------------------------
int __fastcall Compiler_WriteModuleListSetupCode(char a1)
{
  int v1; // edx
  int v2; // ecx
  int v3; // edx
  int v4; // ecx
  char v6; // [esp-4h] [ebp-4h]

  v6 = a1;
  if ( Module_NextEnum(0) )
    Output_WriteFormatted(
      v2,
      *(_DWORD *)(*(_DWORD *)(g_ClipsDefmoduleCompilerItem + 20) + 4),
      v2,
      (int)aSetlistofdefmo,
      *(_DWORD *)(*(_DWORD *)(g_ClipsDefmoduleCompilerItem + 20) + 4));
  else
    Output_WriteFormatted(v2, v1, v2, (int)aSetlistofdef_0, v6);
  return Output_WriteFormatted(v4, v3, v4, (int)aSetcurrentmo_0, v6);
}
// 4D81E1: variable 'v2' is possibly undefined
// 4D81EF: variable 'v4' is possibly undefined
// 4D81EF: variable 'v3' is possibly undefined
// 4D81EF: variable 'v6' is possibly undefined
// 4D81FF: variable 'v1' is possibly undefined
// 54E908: using guessed type int dword_54E908;

//----- (004D8220) --------------------------------------------------------
signed int  Compiler_WriteModuleTableFile(const char *a1, const char *a2, int a3, int a4, int a5)
{
  int v5; // ebp
  signed int result; // eax
  int v7; // edi
  int v8; // edx
  int v9; // ecx
  int v10; // eax
  int v11; // edx
  int v12; // ecx
  int v13; // esi
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // eax
  int v18; // esi
  int v19; // eax
  int v20; // edx
  int v21; // ecx
  int v22; // edx
  int v23; // eax
  int v24; // edx
  int v25; // ecx
  int v26; // ecx
  int v27; // edx
  int v28; // ecx
  int v29; // edx
  int v30; // ecx
  int v31; // ecx
  int v32; // edx
  int v33; // ecx
  int v34; // ecx
  int i; // eax
  int j; // eax
  int v37; // [esp+0h] [ebp-38h] BYREF
  int v38; // [esp+4h] [ebp-34h] BYREF
  int v39; // [esp+8h] [ebp-30h] BYREF
  const char *v40; // [esp+Ch] [ebp-2Ch]
  const char *v41; // [esp+10h] [ebp-28h]
  int v42; // [esp+14h] [ebp-24h]
  int v43; // [esp+18h] [ebp-20h]
  int v44; // [esp+1Ch] [ebp-1Ch]
  int v45; // [esp+20h] [ebp-18h]
  int *Enum; // [esp+24h] [ebp-14h]
  int v47; // [esp+28h] [ebp-10h]

  v41 = a1;
  v40 = a2;
  v42 = a4;
  v44 = a3;
  v43 = 0;
  v45 = 0;
  v38 = 1;
  v39 = 2;
  Output_WriteFormatted(0, 0, a4, (int)aIncludeModulde, 0);
  v5 = 0;
  result = Rules_OpenConstructCodeFile(v41, (int)v40, 1, 0);
  v7 = result;
  if ( result )
  {
    Output_WriteFormatted(
      **(_DWORD **)(g_ClipsDefmoduleCompilerItem + 20),
      *(_DWORD *)(g_ClipsDefmoduleCompilerItem + 20),
      result,
      (int)aStructDefmodul,
      **(_DWORD **)(g_ClipsDefmoduleCompilerItem + 20));
    Output_WriteFormatted(v9, v8, v42, (int)aExternStructDe, **(_DWORD **)(g_ClipsDefmoduleCompilerItem + 20));
    Enum = (int *)Module_NextEnum(0);
    if ( Enum )
    {
      while ( 1 )
      {
        v10 = Rules_ConstructCodeFileOpen(
                v43,
                v41,
                v44,
                v40,
                &v39,
                v38,
                v42,
                (char)aStructDefmod_0,
                *(const char **)(*(_DWORD *)(g_ClipsDefmoduleCompilerItem + 20) + 4),
                0,
                0);
        v13 = v10;
        v43 = v10;
        if ( !v10 )
          break;
        Output_WriteFormatted(v12, v11, v10, (int)asc_50D6C8, v37);
        Compiler_WriteSymbolReference(v13, *Enum, v14);
        Output_WriteFormatted(v16, v15, v13, (int)aNull_30, v37);
        Output_WriteFormatted(v44, v45, v13, (int)aSD_1D, **(_DWORD **)(g_ClipsDefmoduleCompilerItem + 20));
        v17 = Module_GetItemList();
        v47 = 0;
        v18 = v17;
        while ( 1 )
        {
          v19 = Module_GetItemCount();
          if ( v19 <= v20 || !v18 )
            break;
          v22 = *(_DWORD *)(v18 + 20);
          ++v45;
          if ( v22 )
            (*(void (__fastcall **)(int, int))(v18 + 20))(a5, Enum[6]);
          else
            Output_WriteFormatted(v21, 0, v7, (int)aNull_18, v37);
          v23 = Module_GetItemCount();
          if ( v24 >= v23 )
          {
            if ( Enum[7] )
              Output_WriteFormatted(v25, v24, v7, (int)asc_50D6E8, v37);
          }
          else
          {
            Output_WriteFormatted(v25, v24, v7, (int)asc_50D6E4, v37);
          }
          v18 = *(_DWORD *)(v18 + 28);
          ++v47;
        }
        if ( Enum[3] )
        {
          Output_WriteFormatted(
            v43,
            *(_DWORD *)(*(_DWORD *)(g_ClipsDefmoduleCompilerItem + 20) + 8),
            v43,
            (int)aSD_DD_9,
            *(_DWORD *)(*(_DWORD *)(g_ClipsDefmoduleCompilerItem + 20) + 8));
          for ( i = Enum[3]; i; ++v5 )
            i = *(_DWORD *)(i + 12);
        }
        else
        {
          Output_WriteFormatted(v21, v20, v43, (int)aNull_31, v37);
        }
        if ( Enum[4] )
        {
          Output_WriteFormatted(
            v43,
            *(_DWORD *)(*(_DWORD *)(g_ClipsDefmoduleCompilerItem + 20) + 8),
            v43,
            (int)aSD_DD_9,
            *(_DWORD *)(*(_DWORD *)(g_ClipsDefmoduleCompilerItem + 20) + 8));
          for ( j = Enum[4]; j; ++v5 )
            j = *(_DWORD *)(j + 12);
        }
        else
        {
          Output_WriteFormatted(v28, v27, v43, (int)aNull_31, v37);
        }
        Output_WriteFormatted(v30, v29, v43, (int)a0Ld, Enum[6]);
        if ( Enum[7] )
          Output_WriteFormatted(
            v43,
            *(_DWORD *)(*(_DWORD *)(g_ClipsDefmoduleCompilerItem + 20) + 4),
            v43,
            (int)aSD_DD_10,
            *(_DWORD *)(*(_DWORD *)(g_ClipsDefmoduleCompilerItem + 20) + 4));
        else
          Output_WriteFormatted(v31, 0, v43, (int)aNull_32, v37);
        ++v37;
        v43 = Rules_ConstructCodeFileClose(v43, &v37, a5, &v38, 0, 0);
        Enum = (int *)Module_NextEnum((int)Enum);
        if ( !Enum )
          goto LABEL_23;
      }
      v37 = a5;
      Rules_ConstructCodeFileClose(0, &v37, a5, &v38, 0, 0);
      fclose_(v26);
      return 0;
    }
    else
    {
LABEL_23:
      v37 = a5;
      Rules_ConstructCodeFileClose(v43, &v37, a5, &v38, 0, 0);
      Output_WriteFormatted(v33, v32, v7, (int)Lexer_ArrayClose, v37);
      fclose_(v34);
      if ( v5 )
        return Compiler_WritePortItemTableFile(v41, v40, v44, v42, a5, &v39);
      else
        return 1;
    }
  }
  return result;
}
// 4D82C1: variable 'v9' is possibly undefined
// 4D82C1: variable 'v8' is possibly undefined
// 4D8329: variable 'v12' is possibly undefined
// 4D8329: variable 'v11' is possibly undefined
// 4D8339: variable 'v14' is possibly undefined
// 4D8344: variable 'v16' is possibly undefined
// 4D8344: variable 'v15' is possibly undefined
// 4D8387: variable 'v20' is possibly undefined
// 4D83AB: variable 'v21' is possibly undefined
// 4D83BF: variable 'v24' is possibly undefined
// 4D83C7: variable 'v25' is possibly undefined
// 4D83FA: variable 'v26' is possibly undefined
// 4D8469: variable 'v28' is possibly undefined
// 4D8469: variable 'v27' is possibly undefined
// 4D8483: variable 'v30' is possibly undefined
// 4D8483: variable 'v29' is possibly undefined
// 4D84A4: variable 'v31' is possibly undefined
// 4D850C: variable 'v33' is possibly undefined
// 4D850C: variable 'v32' is possibly undefined
// 4D8516: variable 'v34' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 54E908: using guessed type int dword_54E908;

//----- (004D8650) --------------------------------------------------------
signed int  Compiler_WritePortItemTableFile(
        const char *a1,
        const char *a2,
        int a3,
        int a4,
        int a5,
        int *a6)
{
  int v6; // edi
  int v7; // eax
  int v8; // edx
  int v9; // ecx
  int v10; // esi
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int v18; // edx
  int v19; // ecx
  int v20; // edx
  int v21; // ecx
  int v23; // [esp+0h] [ebp-34h] BYREF
  int *v24; // [esp+4h] [ebp-30h] BYREF
  int v25; // [esp+8h] [ebp-2Ch] BYREF
  int v26; // [esp+Ch] [ebp-28h] BYREF
  int v27; // [esp+10h] [ebp-24h] BYREF
  int v28; // [esp+14h] [ebp-20h] BYREF
  const char *v29; // [esp+18h] [ebp-1Ch]
  const char *v30; // [esp+1Ch] [ebp-18h]
  int v31; // [esp+20h] [ebp-14h]
  int v32; // [esp+24h] [ebp-10h]

  v30 = a1;
  v29 = a2;
  v31 = a4;
  v32 = a3;
  v23 = 0;
  v24 = 0;
  v25 = 0;
  v26 = 0;
  v27 = 0;
  v28 = 1;
  v6 = 0;
  v24 = (int *)Module_NextPortItemEnum(&v23, (int *)&v24, &v27, &v26);
  if ( v24 )
  {
    while ( 1 )
    {
      v7 = Rules_ConstructCodeFileOpen(
             v6,
             v30,
             v32,
             v29,
             a6,
             v28,
             v31,
             (char)aStructPortitem,
             *(const char **)(*(_DWORD *)(g_ClipsDefmoduleCompilerItem + 20) + 8),
             0,
             0);
      v10 = v7;
      v6 = v7;
      if ( !v7 )
        break;
      Output_WriteFormatted(v9, v8, v7, (int)asc_50D6C8, v23);
      Compiler_WriteSymbolReference(v10, *v24, v11);
      Output_WriteFormatted(v13, v12, v10, (int)asc_50D6E4, v23);
      Compiler_WriteSymbolReference(v10, v24[1], v14);
      Output_WriteFormatted(v16, v15, v10, (int)asc_50D6E4, v23);
      Compiler_WriteSymbolReference(v10, v24[2], v17);
      Output_WriteFormatted(v19, v18, v10, (int)asc_50D6E4, v23);
      if ( v24[3] )
        Output_WriteFormatted(v32, (v25 + 1) % a5, v10, (int)aSD_DD_10, *(_DWORD *)(*(_DWORD *)(g_ClipsDefmoduleCompilerItem + 20) + 8));
      else
        Output_WriteFormatted(v21, v20, v10, (int)aNull_32, v23);
      ++v25;
      Rules_ConstructCodeFileClose(v6, &v25, a5, &v28, 0, 0);
      v24 = (int *)Module_NextPortItemEnum(&v23, (int *)&v24, &v27, &v26);
      if ( !v24 )
        goto LABEL_6;
    }
    v25 = a5;
    Rules_ConstructCodeFileClose(0, &v25, a5, &v28, 0, 0);
    return 0;
  }
  else
  {
LABEL_6:
    v25 = a5;
    Rules_ConstructCodeFileClose(v6, &v25, a5, &v28, 0, 0);
    return 1;
  }
}
// 4D86F2: variable 'v9' is possibly undefined
// 4D86F2: variable 'v8' is possibly undefined
// 4D8702: variable 'v11' is possibly undefined
// 4D870D: variable 'v13' is possibly undefined
// 4D870D: variable 'v12' is possibly undefined
// 4D871E: variable 'v14' is possibly undefined
// 4D8729: variable 'v16' is possibly undefined
// 4D8729: variable 'v15' is possibly undefined
// 4D873A: variable 'v17' is possibly undefined
// 4D8745: variable 'v19' is possibly undefined
// 4D8745: variable 'v18' is possibly undefined
// 4D8761: variable 'v21' is possibly undefined
// 4D8761: variable 'v20' is possibly undefined
// 54E908: using guessed type int dword_54E908;

//----- (004D8830) --------------------------------------------------------
int  Module_NextPortItemEnum(int *a1, int *a2, _DWORD *a3, _DWORD *a4)
{
  int v5; // ebp

  if ( !*a1 )
  {
    *a1 = Module_NextEnum(0);
    *a2 = 0;
    *a4 = 0;
    *a3 = 0;
  }
  while ( *a1 )
  {
    if ( *a2 )
      *a2 = *(_DWORD *)(*a2 + 12);
    v5 = *a2;
    if ( *a2 )
      return v5;
    if ( !*a4 )
    {
      *a2 = *(_DWORD *)(*a1 + 12);
      *a4 = 1;
      if ( !*a2 )
      {
        *a2 = *(_DWORD *)(*a1 + 16);
        *a3 = 1;
      }
LABEL_10:
      v5 = *a2;
      if ( *a2 )
        return v5;
      goto LABEL_15;
    }
    if ( *a3 )
      goto LABEL_10;
    *a3 = 1;
    *a2 = *(_DWORD *)(*a1 + 16);
    v5 = *a2;
    if ( *a2 )
      return *a2;
LABEL_15:
    *a1 = Module_NextEnum(*a1);
    *a4 = v5;
    *a3 = v5;
  }
  return 0;
}
// 4D8888: variable 'a2' is possibly undefined
// 4D888C: variable 'a3' is possibly undefined

//----- (004D88F0) --------------------------------------------------------
int __cdecl Rules_RegisterObjectPatternConstraintEvaluators(void)
{
  Runtime_InitCompactEvalDescriptor(g_EvalNodeDescFetchJoinObjectSlotFieldRecord, (uintptr_t)Rules_FetchJoinObjectSlotFieldRecord);
  Runtime_InitCompactEvalDescriptor(g_EvalNodeDescFetchJoinObjectSlotFieldSimple, (uintptr_t)Rules_FetchJoinObjectSlotFieldSimple);
  Runtime_InitCompactEvalDescriptor(g_EvalNodeDescFetchObjectSlotFieldRecord, (uintptr_t)Rules_FetchObjectSlotFieldRecord);
  Runtime_InitCompactEvalDescriptor(g_EvalNodeDescFetchObjectSlotFieldSimple, (uintptr_t)Rules_FetchObjectSlotFieldSimple);
  Runtime_InitCompactEvalDescriptor(g_EvalNodeDescObjectSlotBoundVariableEqual, (uintptr_t)Rules_EvalObjectSlotBoundVariableEqual);
  Runtime_InitCompactEvalDescriptor(g_EvalNodeDescObjectSlotIndexInRange, (uintptr_t)Rules_EvalObjectSlotIndexInRange);
  Runtime_InitCompactEvalDescriptor(g_EvalNodeDescObjectSlotFieldsEqual, (uintptr_t)Rules_EvalObjectSlotFieldsEqual);
  Runtime_InitCompactEvalDescriptor(g_EvalNodeDescObjectSlotElementFieldEqual, (uintptr_t)Rules_EvalObjectSlotElementFieldEqual);
  Runtime_InitCompactEvalDescriptor(g_EvalNodeDescObjectSlotElementsEqual, (uintptr_t)Rules_EvalObjectSlotElementsEqual);
  Runtime_InitCompactEvalDescriptor(g_EvalDescriptor_JoinObjectSlotFieldsEqual, (uintptr_t)Rules_EvalJoinObjectSlotFieldsEqual);
  Runtime_InitCompactEvalDescriptor(g_EvalDescriptor_JoinObjectSlotElementFieldEqual, (uintptr_t)Rules_EvalJoinObjectSlotElementFieldEqual);
  Runtime_InitCompactEvalDescriptor(g_EvalDescriptor_JoinObjectSlotElementsEqual, (uintptr_t)Rules_EvalJoinObjectSlotElementsEqual);
  Rules_RegisterEvaluationHandler((int)&g_EvalNodeDescFetchJoinObjectSlotFieldRecord, 47);
  Rules_RegisterEvaluationHandler((int)&g_EvalNodeDescFetchJoinObjectSlotFieldSimple, 48);
  Rules_RegisterEvaluationHandler((int)&g_EvalNodeDescFetchObjectSlotFieldRecord, 45);
  Rules_RegisterEvaluationHandler((int)&g_EvalNodeDescFetchObjectSlotFieldSimple, 46);
  Rules_RegisterEvaluationHandler((int)&g_EvalNodeDescObjectSlotBoundVariableEqual, 50);
  Rules_RegisterEvaluationHandler((int)&g_EvalNodeDescObjectSlotIndexInRange, 49);
  Rules_RegisterEvaluationHandler((int)&g_EvalNodeDescObjectSlotFieldsEqual, 51);
  Rules_RegisterEvaluationHandler((int)&g_EvalNodeDescObjectSlotElementFieldEqual, 53);
  Rules_RegisterEvaluationHandler((int)&g_EvalNodeDescObjectSlotElementsEqual, 55);
  Rules_RegisterEvaluationHandler((int)&g_EvalDescriptor_JoinObjectSlotFieldsEqual, 52);
  Rules_RegisterEvaluationHandler((int)&g_EvalDescriptor_JoinObjectSlotElementFieldEqual, 54);
  return Rules_RegisterEvaluationHandler((int)&g_EvalDescriptor_JoinObjectSlotElementsEqual, 56);
}

//----- (004D89B0) --------------------------------------------------------
unsigned int  Rules_EvalObjectSlotBoundVariableEqual(int a1, int a2, int a3, double a4)
{
  int v5; // ecx
  __int16 *v6; // esi
  int v7; // edx
  int v8; // edi
  int v9; // eax
  unsigned int v10; // eax
  unsigned int result; // eax
  int v12; // [esp-4h] [ebp-28h] BYREF
  int v13; // [esp+0h] [ebp-24h]
  int v14; // [esp+4h] [ebp-20h]
  int v15; // [esp+1Ch] [ebp-8h]

  v15 = a3;
  v5 = *(_DWORD *)(a1 + 16);
  if ( (*(_BYTE *)(v5 + 1) & 2) != 0 )
  {
    Parser_ParseForm(*(__int16 **)(g_ClipsCurrentExpression + 6), &v12, v5, a4);
    v6 = *(__int16 **)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10);
  }
  else
  {
    v6 = *(__int16 **)(g_ClipsCurrentExpression + 6);
    if ( (*(_DWORD *)(g_ObjectPatternActiveClassNode + 4) & 0xFC) == 0x10 )
    {
      v7 = *(_DWORD *)(g_ObjectPatternActiveClassNode + 8);
      if ( (*(_BYTE *)(v5 + 1) & 4) != 0 )
      {
        v13 = *(__int16 *)(v7 + 6 * (*(_DWORD *)v5 & 0x7F) + 14);
        v8 = *(_DWORD *)v5 & 0x7F;
      }
      else
      {
        v13 = *(__int16 *)(v7 + 6 * (*(_DWORD *)(v7 + 6) - ((*(_DWORD *)v5 & 0x7F) + 1)) + 14);
        v8 = *(_DWORD *)(v7 + 6) - ((*(_DWORD *)v5 & 0x7F) + 1);
      }
      v9 = *(_DWORD *)(v7 + 6 * v8 + 16);
    }
    else
    {
      v13 = *(_DWORD *)(g_ObjectPatternActiveClassNode + 4) << 24 >> 26;
      v9 = *(_DWORD *)(g_ObjectPatternActiveClassNode + 8);
    }
    v14 = v9;
  }
  if ( *v6 == v13 && v14 == *(_DWORD *)(v6 + 1) )
    v10 = *(_DWORD *)v5 << 24;
  else
    v10 = *(_DWORD *)v5 << 23;
  result = v10 >> 31;
  *(_DWORD *)(a2 + 4) = 2;
  if ( result )
    *(_DWORD *)(a2 + 8) = g_ClipsTrueSymbol;
  else
    *(_DWORD *)(a2 + 8) = g_ClipsFalseSymbol;
  return result;
}
// 4D8A2F: variable 'v5' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51B47C: using guessed type int dword_51B47C;
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (004D8AF0) --------------------------------------------------------
signed int  Rules_FetchJoinObjectSlotFieldRecord(int a1, _DWORD *a2, _DWORD *a3)
{
  uintptr_t payload; // ecx
  int module; // [esp+0h] [ebp-14h] BYREF
  int slot_constraints; // [esp+4h] [ebp-10h] BYREF

  (void)a3;
  payload = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)a1 + 16);
  if ( !payload )
    return 1;
  Rules_ResolveJoinBindingRecord(((*(_DWORD *)payload << 9) >> 24) - 1, (_DWORD *)&module, (_DWORD *)&slot_constraints);
  Rules_FetchObjectSlotFieldRecordCore(a2, (_DWORD *)(uintptr_t)(unsigned int)module, (int)payload, (_DWORD *)(uintptr_t)(unsigned int)slot_constraints);
  return 1;
}

//----- (004D8B40) --------------------------------------------------------
signed int  Rules_FetchJoinObjectSlotFieldSimple(int a1, int a2)
{
  int v2; // esi
  _DWORD *v3; // ecx
  _DWORD *v5; // [esp+0h] [ebp-14h] BYREF
  _DWORD v6[4]; // [esp+4h] [ebp-10h] BYREF

  v6[2] = a2;
  v2 = *(_DWORD *)(a1 + 16);
  Rules_ResolveJoinBindingRecord((unsigned __int8)*(_DWORD *)(v2 + 4) - 1, &v5, v6);
  Rules_FetchObjectSlotFieldSimpleCore(v3, v5, (int)v3, v2);
  return 1;
}
// 4D8B66: variable 'v3' is possibly undefined

//----- (004D8B90) --------------------------------------------------------
signed int  Rules_FetchObjectSlotFieldRecord(int a1, _DWORD *a2)
{
  Rules_FetchObjectSlotFieldRecordCore(a2, (_DWORD *)g_ClipsObjectReteCurrentInstance, *(_DWORD *)(a1 + 16), (_DWORD *)g_ObjectPatternMarkerListHead);
  return 1;
}
// 51B478: using guessed type int dword_51B478;
// 51B484: using guessed type int dword_51B484;

//----- (004D8BD0) --------------------------------------------------------
signed int  Rules_FetchObjectSlotFieldSimple(int a1, _DWORD *a2, int a3)
{
  Rules_FetchObjectSlotFieldSimpleCore(a2, (_DWORD *)g_ClipsObjectReteCurrentInstance, a3, *(_DWORD *)(a1 + 16));
  return 1;
}
// 51B478: using guessed type int dword_51B478;

//----- (004D8C00) --------------------------------------------------------
signed int  Rules_EvalObjectSlotIndexInRange(int a1, int a2)
{
  int v2; // ecx
  unsigned int v3; // eax

  *(_DWORD *)(a2 + 4) = 2;
  *(_DWORD *)(a2 + 8) = g_ClipsFalseSymbol;
  v2 = *(_DWORD *)(a1 + 16);
  v3 = *(_DWORD *)v2 & 0x7FFF;
  if ( v3 > g_ObjectPatternMatchFieldCount || *(char *)(v2 + 1) < 0 && v3 < g_ObjectPatternMatchFieldCount )
    return 0;
  *(_DWORD *)(a2 + 8) = g_ClipsTrueSymbol;
  return 1;
}
// 51B480: using guessed type int dword_51B480;
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (004D8C60) --------------------------------------------------------
unsigned int  Rules_EvalObjectSlotFieldsEqual(int a1, int a2)
{
  unsigned int *v2; // eax
  int v3; // esi
  int v4; // ecx
  int v5; // ebx
  int v6; // ecx
  unsigned int v7; // eax
  unsigned int result; // eax

  v2 = *(unsigned int **)(a1 + 16);
  v3 = *(_DWORD *)(*(_DWORD *)(g_ClipsObjectReteCurrentInstance + 44) + 60);
  v4 = *(_DWORD *)(g_ClipsObjectReteCurrentInstance + 72);
  v5 = *(_DWORD *)(v4 + 4 * *(_DWORD *)(v3 + 4 * (*v2 & 0x7FFF)) - 4);
  v6 = *(_DWORD *)(v4 + 4 * *(_DWORD *)(v3 + 4 * ((2 * *v2) >> 17)) - 4);
  if ( *(_DWORD *)(v5 + 4) << 24 >> 26 == *(_DWORD *)(v6 + 4) << 24 >> 26 && *(_DWORD *)(v5 + 8) == *(_DWORD *)(v6 + 8) )
    v7 = *v2 << 16;
  else
    v7 = *v2;
  result = v7 >> 31;
  *(_DWORD *)(a2 + 4) = 2;
  if ( result )
    *(_DWORD *)(a2 + 8) = g_ClipsTrueSymbol;
  else
    *(_DWORD *)(a2 + 8) = g_ClipsFalseSymbol;
  return result;
}
// 51B478: using guessed type int dword_51B478;
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (004D8CF0) --------------------------------------------------------
unsigned int  Rules_EvalObjectSlotElementFieldEqual(int a1, int a2)
{
  unsigned int *v3; // esi
  int v4; // eax
  int v5; // edx
  unsigned int v6; // eax
  unsigned int result; // eax

  v3 = *(unsigned int **)(a1 + 16);
  v4 = Rules_ResolveObjectSlotFieldPointer(g_ClipsObjectReteCurrentInstance, *v3 & 0x7FFF, v3[1] & 0x7F, v3[1] << 24 >> 31);
  v5 = *(_DWORD *)(*(_DWORD *)(g_ClipsObjectReteCurrentInstance + 72)
                 + 4 * *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsObjectReteCurrentInstance + 44) + 60) + 4 * ((2 * *v3) >> 17))
                 - 4);
  if ( *(_WORD *)v4 == *(_DWORD *)(v5 + 4) << 24 >> 26 && *(_DWORD *)(v4 + 2) == *(_DWORD *)(v5 + 8) )
    v6 = *v3 << 16;
  else
    v6 = *v3;
  result = v6 >> 31;
  *(_DWORD *)(a2 + 4) = 2;
  if ( result )
    *(_DWORD *)(a2 + 8) = g_ClipsTrueSymbol;
  else
    *(_DWORD *)(a2 + 8) = g_ClipsFalseSymbol;
  return result;
}
// 51B478: using guessed type int dword_51B478;
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (004D8D90) --------------------------------------------------------
unsigned int  Rules_EvalObjectSlotElementsEqual(int a1, int a2)
{
  unsigned int *v3; // esi
  __int16 *v4; // ebp
  __int16 *v5; // eax
  unsigned int v6; // eax
  unsigned int result; // eax

  v3 = *(unsigned int **)(a1 + 16);
  v4 = (__int16 *)Rules_ResolveObjectSlotFieldPointer(g_ClipsObjectReteCurrentInstance, *v3 & 0x7FFF, v3[1] & 0x7F, v3[1] << 24 >> 31);
  v5 = (__int16 *)Rules_ResolveObjectSlotFieldPointer(g_ClipsObjectReteCurrentInstance, (2 * *v3) >> 17, v3[1] << 17 >> 25, v3[1] << 16 >> 31);
  if ( *v4 == *v5 && *(_DWORD *)(v4 + 1) == *(_DWORD *)(v5 + 1) )
    v6 = *v3 << 16;
  else
    v6 = *v3;
  result = v6 >> 31;
  *(_DWORD *)(a2 + 4) = 2;
  if ( result )
    *(_DWORD *)(a2 + 8) = g_ClipsTrueSymbol;
  else
    *(_DWORD *)(a2 + 8) = g_ClipsFalseSymbol;
  return result;
}
// 51B478: using guessed type int dword_51B478;
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (004D8E30) --------------------------------------------------------
unsigned int  Rules_EvalJoinObjectSlotFieldsEqual(int a1, int a2, int a3)
{
  _DWORD *v4; // ecx
  int v5; // edi
  unsigned int *v6; // ecx
  int v7; // eax
  unsigned int v8; // eax
  unsigned int result; // eax
  int v10; // [esp+0h] [ebp-1Ch] BYREF
  int v11; // [esp+4h] [ebp-18h] BYREF
  _DWORD v12[5]; // [esp+8h] [ebp-14h] BYREF

  v12[3] = a3;
  Rules_ResolveJoinBindingRecord((unsigned __int8)*(_DWORD *)(*(_DWORD *)(a1 + 16) + 4) - 1, &v10, v12);
  v5 = *(_DWORD *)(4 * *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v10 + 44) + 60) + 4 * (*v4 & 0x7FFF))
                 + *(_DWORD *)(v10 + 72)
                 - 4);
  Rules_ResolveJoinBindingRecord((v4[1] << 16 >> 24) - 1, &v11, v12);
  v7 = *(_DWORD *)(*(_DWORD *)(v11 + 72)
                 + 4 * *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v11 + 44) + 60) + 4 * ((2 * *v6) >> 17))
                 - 4);
  if ( *(_DWORD *)(v5 + 4) << 24 >> 26 == *(_DWORD *)(v7 + 4) << 24 >> 26 && *(_DWORD *)(v5 + 8) == *(_DWORD *)(v7 + 8) )
    v8 = *v6 << 16;
  else
    v8 = *v6;
  result = v8 >> 31;
  *(_DWORD *)(a2 + 4) = 2;
  if ( result )
    *(_DWORD *)(a2 + 8) = g_ClipsTrueSymbol;
  else
    *(_DWORD *)(a2 + 8) = g_ClipsFalseSymbol;
  return result;
}
// 4D8E53: variable 'v4' is possibly undefined
// 4D8E8B: variable 'v6' is possibly undefined
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (004D8F10) --------------------------------------------------------
unsigned int  Rules_EvalJoinObjectSlotElementFieldEqual(int a1, int a2, int a3)
{
  _DWORD *v4; // esi
  int v5; // ecx
  int v6; // eax
  unsigned int v7; // eax
  unsigned int result; // eax
  int v9; // [esp+0h] [ebp-1Ch] BYREF
  int v10; // [esp+4h] [ebp-18h] BYREF
  _DWORD v11[5]; // [esp+8h] [ebp-14h] BYREF

  v11[3] = a3;
  v4 = *(_DWORD **)(a1 + 16);
  Rules_ResolveJoinBindingRecord((unsigned __int8)v4[1] - 1, &v9, v11);
  Rules_ResolveObjectSlotFieldPointer(v9, *v4 & 0x7FFF, v4[1] << 9 >> 25, *v4 >> 31);
  Rules_ResolveJoinBindingRecord((v4[1] << 16 >> 24) - 1, &v10, v11);
  v6 = *(_DWORD *)(4 * *(_DWORD *)(4 * ((unsigned int)(2 * *v4) >> 17) + *(_DWORD *)(*(_DWORD *)(v10 + 44) + 60))
                 + *(_DWORD *)(v10 + 72)
                 - 4);
  if ( *(_WORD *)v5 == *(_DWORD *)(v6 + 4) << 24 >> 26 && *(_DWORD *)(v5 + 2) == *(_DWORD *)(v6 + 8) )
    v7 = *v4 << 16;
  else
    v7 = v4[1] << 8;
  result = v7 >> 31;
  *(_DWORD *)(a2 + 4) = 2;
  if ( result )
    *(_DWORD *)(a2 + 8) = g_ClipsTrueSymbol;
  else
    *(_DWORD *)(a2 + 8) = g_ClipsFalseSymbol;
  return result;
}
// 4D8F9C: variable 'v5' is possibly undefined
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (004D9000) --------------------------------------------------------
unsigned int  Rules_EvalJoinObjectSlotElementsEqual(int a1, int a2)
{
  unsigned int *v3; // esi
  __int16 *v4; // ebp
  __int16 *v5; // eax
  unsigned int v6; // eax
  unsigned int result; // eax
  int v8; // [esp+0h] [ebp-20h] BYREF
  int v9; // [esp+4h] [ebp-1Ch] BYREF
  _DWORD v10[6]; // [esp+8h] [ebp-18h] BYREF

  v3 = *(unsigned int **)(a1 + 16);
  Rules_ResolveJoinBindingRecord((unsigned __int8)v3[1] - 1, &v8, v10);
  v4 = (__int16 *)Rules_ResolveObjectSlotFieldPointer(v8, *v3 & 0x7FFF, v3[1] << 9 >> 25, v3[1] << 8 >> 31);
  Rules_ResolveJoinBindingRecord((v3[1] << 16 >> 24) - 1, &v9, v10);
  v5 = (__int16 *)Rules_ResolveObjectSlotFieldPointer(v8, (2 * *v3) >> 17, (2 * v3[1]) >> 25, (unsigned __int64)v3[1] >> 31);
  if ( *v4 == *v5 && *(_DWORD *)(v4 + 1) == *(_DWORD *)(v5 + 1) )
    v6 = *v3 << 16;
  else
    v6 = *v3;
  result = v6 >> 31;
  *(_DWORD *)(a2 + 4) = 2;
  if ( result )
    *(_DWORD *)(a2 + 8) = g_ClipsTrueSymbol;
  else
    *(_DWORD *)(a2 + 8) = g_ClipsFalseSymbol;
  return result;
}
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (004D90D0) --------------------------------------------------------
int  Rules_ResolveJoinBindingRecord(int a1, _DWORD *a2, _DWORD *a3)
{
  uintptr_t active_cell; // eax
  uintptr_t fact_list; // ecx
  int offset; // eax

  offset = 4 * a1;
  if ( g_Rules_GlobalRHSBinds && (((unsigned int)*(_DWORD *)(uintptr_t)(unsigned int)g_CurrentPatternEntityPtr << 16) >> 25) - 1 == a1 )
  {
    active_cell = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_Rules_GlobalRHSBinds + 8);
    *a2 = (int)(uintptr_t)(unsigned int)*(_DWORD *)active_cell;
    *a3 = *(_DWORD *)(active_cell + 4);
    return *a3;
  }
  fact_list = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_Clips_CurrentPartialMatch + offset + 8);
  *a2 = (int)(uintptr_t)(unsigned int)*(_DWORD *)fact_list;
  *a3 = *(_DWORD *)(fact_list + 4);
  return *a3;
}
// 51ACFC: using guessed type int dword_51ACFC;
// 51AD00: using guessed type int dword_51AD00;
// 51AD04: using guessed type int dword_51AD04;

//----- (004D9140) --------------------------------------------------------
_DWORD * Rules_FetchObjectSlotFieldRecordCore(_DWORD *a1, _DWORD *a2, int a3, _DWORD *a4)
{
  _DWORD *result; // eax
  int v6; // edx
  int v7; // edi
  int v8; // edx
  int *v9; // edi
  int v10; // ebp
  int v11; // eax
  int v12; // edx
  int v13; // eax
  int v14; // [esp+0h] [ebp-18h] BYREF
  int v15; // [esp+4h] [ebp-14h] BYREF
  int v16; // [esp+8h] [ebp-10h]

  result = a2;
  if ( *(char *)(a3 + 3) < 0 )
  {
    a1[1] = 7;
    a1[2] = a2;
  }
  else if ( (*(_WORD *)a3 & 0x7FFF) != 0 )
  {
    v6 = *(_DWORD *)a3 & 0x7FFF;
    if ( v6 == 1 )
    {
      a1[1] = 8;
      result = (_DWORD *)result[7];
      a1[2] = result;
    }
    else
    {
      v7 = 4 * (*(_DWORD *)(*(_DWORD *)(result[11] + 60) + 4 * v6) - 1);
      v8 = result[18];
      v9 = (int *)(v8 + v7);
      if ( result[5] )
      {
        if ( !g_Rules_JoinOperationInProgress )
        {
          v16 = ((int)v9 - v8) >> 2;
          v15 = 12 * v16 + result[5];
          if ( *(_DWORD *)(v15 + 8) )
            v9 = &v15;
        }
      }
      if ( (*(_BYTE *)(a3 + 4) & 1) != 0 )
      {
        a1[1] = *(_DWORD *)(*v9 + 4) << 24 >> 26;
        result = *(_DWORD **)(*v9 + 8);
        v10 = a1[1];
        a1[2] = result;
        if ( v10 == 4 )
        {
          a1[3] = 0;
          result = (_DWORD *)(*(_DWORD *)(*(_DWORD *)(*v9 + 8) + 6) - 1);
          a1[4] = result;
        }
      }
      else
      {
        v11 = Rules_ComputeObjectMultifieldSegmentOffset(a4, *v9, &v14, (unsigned int)(2 * *(_DWORD *)a3) >> 24);
        v12 = v11 - 1;
        if ( v14 == -1 )
        {
          v13 = *v9;
          if ( (**(_BYTE **)*v9 & 2) != 0 )
          {
            a1[1] = *(__int16 *)(*(_DWORD *)(v13 + 8) + 6 * v12 + 14);
            result = *(_DWORD **)(*(_DWORD *)(*v9 + 8) + 6 * v12 + 16);
          }
          else
          {
            a1[1] = *(_DWORD *)(v13 + 4) << 24 >> 26;
            result = *(_DWORD **)(*v9 + 8);
          }
          a1[2] = result;
        }
        else
        {
          a1[1] = 4;
          a1[2] = *(_DWORD *)(*v9 + 8);
          a1[3] = v12;
          result = (_DWORD *)(v14 + v11 - 2);
          a1[4] = result;
        }
      }
    }
  }
  else
  {
    a1[1] = 2;
    result = (_DWORD *)Rules_GetConstructNameSymbol(a2[11]);
    a1[2] = result;
  }
  return result;
}
// 51A954: using guessed type int dword_51A954;

//----- (004D92D0) --------------------------------------------------------
_DWORD * Rules_FetchObjectSlotFieldSimpleCore(_DWORD *result, _DWORD *a2, int a3, int a4)
{
  int v5; // esi
  int v6; // edx
  _DWORD *v7; // esi
  int v8; // edx
  int v9; // ecx
  int v10; // edx
  unsigned int v11; // ebx
  _DWORD v12[4]; // [esp+0h] [ebp-10h] BYREF

  v12[3] = a3;
  v5 = 4 * (*(_DWORD *)(*(_DWORD *)(a2[11] + 60) + 4 * (*(_DWORD *)a4 & 0x7FFF)) - 1);
  v6 = a2[18];
  v7 = (_DWORD *)(v6 + v5);
  if ( a2[5] )
  {
    if ( !g_Rules_JoinOperationInProgress )
    {
      v12[0] = 12 * (((int)v7 - v6) >> 2) + a2[5];
      if ( *(_DWORD *)(v12[0] + 8) )
        v7 = v12;
    }
  }
  v8 = *(_DWORD *)(*v7 + 8);
  v9 = v8 + 14;
  if ( *(char *)(a4 + 1) >= 0 )
  {
    v11 = 3 * (*(_DWORD *)(v8 + 6) - (((unsigned int)(2 * *(_DWORD *)a4) >> 25) + 1));
    result[1] = *(__int16 *)(v9 + 2 * v11);
    result[2] = *(_DWORD *)(v9 + 2 * v11 + 2);
  }
  else if ( *(char *)(a4 + 2) >= 0 )
  {
    v10 = *(_DWORD *)a4 << 9 >> 25;
    result[1] = *(__int16 *)(v9 + 6 * v10);
    result[2] = *(_DWORD *)(v9 + 6 * v10 + 2);
  }
  else
  {
    result[1] = 4;
    result[2] = v8;
    result[3] = *(_DWORD *)a4 << 9 >> 25;
    result[4] = *(_DWORD *)(v8 + 6) - (((unsigned int)(2 * *(_DWORD *)a4) >> 25) + 1);
  }
  return result;
}
// 51A954: using guessed type int dword_51A954;

//----- (004D93C0) --------------------------------------------------------
int  Rules_ComputeObjectMultifieldSegmentOffset(_DWORD *a1, int a2, int *a3, int a4)
{
  int v5; // ecx
  int i; // esi
  int v7; // edx
  int result; // eax
  int v9; // edx

  v5 = a4;
  *a3 = -1;
  if ( !a2 )
    return a4;
  for ( i = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)a2 + 8) + 12); a1; a1 = (_DWORD *)a1[4] )
  {
    if ( i == a1[1] )
      break;
  }
  while ( a1 && i == a1[1] )
  {
    if ( a4 == *a1 )
    {
      v9 = a1[3] - a1[2] + 1;
      result = v5;
      *a3 = v9;
      return result;
    }
    if ( a4 < *a1 )
      break;
    v7 = a1[3] - a1[2];
    a1 = (_DWORD *)a1[4];
    v5 += v7;
  }
  return v5;
}

//----- (004D9430) --------------------------------------------------------
int  Rules_ResolveObjectSlotFieldPointer(int a1, int a2, int a3, int a4)
{
  int v4; // eax
  int v5; // edx

  v4 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(a1 + 72)
                             + 4 * *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(a1 + 44) + 60) + 4 * a2)
                             - 4)
                 + 8);
  v5 = v4 + 14;
  if ( a4 )
    return v5 + 6 * a3;
  else
    return v5 + 6 * (*(_DWORD *)(v4 + 6) - a3 - 1);
}

//----- (004D9471) --------------------------------------------------------
unsigned int  Str_DecodeMultibyteChar(_WORD *a1, unsigned __int8 *a2, unsigned int a3)
{
  unsigned int v5; // eax
  const CHAR *v6; // edx
  unsigned int v7; // edi
  WCHAR WideCharStr[2]; // [esp+0h] [ebp-4h] BYREF

  if ( !a2 )
    return 0;
  if ( !a3 )
    return -1;
  if ( !*a2 )
  {
    if ( a1 )
      *a1 = 0;
    return 0;
  }
  if ( g_CRT_MbcsCodePageActive && (g_Clips_DbcsLeadByteTable[*a2] & 1) != 0 && !a2[1] )
    return -1;
  v5 = mbclen_();
  v7 = v5;
  if ( a3 < v5 )
    v5 = a3;
  if ( !MultiByteToWideChar(CodePage, 8u, v6, v5, WideCharStr, 1) )
    return -1;
  if ( a1 )
    *a1 = WideCharStr[0];
  return v7;
}
// 4D94E0: variable 'v6' is possibly undefined
// 4E4C37: using guessed type int mbclen_(void);
// 54E718: using guessed type int dword_54E718;

//----- (004D977B) --------------------------------------------------------
void Fpu_ClearExceptions()
{
  return;
}

//----- (004D97D5) --------------------------------------------------------
signed int  Str_ConfigureCodePage(UINT a1, int a2)
{
  UINT v2; // esi
  UINT ACP; // eax
  signed int result; // eax
  int i; // eax
  int j; // eax
  UINT OEMCP; // eax
  int v8; // ecx
  int k; // edx
  int m; // eax
  int v11; // [esp+0h] [ebp-28h] BYREF
  _BYTE v12[34]; // [esp+6h] [ebp-22h]

  v2 = a1;
  switch ( a1 )
  {
    case 0xFFFFFFFF:
      ACP = GetACP();
LABEL_3:
      v2 = ACP;
      break;
    case 0xFFFFFFFE:
      ACP = GetOEMCP();
      goto LABEL_3;
    case 0xFFFFFFFD:
      memset_(a2, 0);
      result = 0;
      g_CRT_MbcsCodePageActive = 0;
      CodePage = 0;
      return result;
    case 0xFFFFFFFC:
      memset_(a2, 0);
      for ( i = 129; i <= 159; g_CRT_MbcsLeadByteTable[i] = 1 )
        ++i;
      for ( j = 224; j <= 252; g_CRT_MbcsLeadByteTable[j] = 1 )
        ++j;
      OEMCP = 932;
      g_CRT_MbcsCodePageActive = 1;
      goto LABEL_27;
  }
  if ( !v2 )
    v2 = 1;
  if ( !GetCPInfo(v2, (LPCPINFO)&v11) )
    return 1;
  memset_(v8, 0);
  g_CRT_MbcsCodePageActive = v12[0] != 0;
  for ( k = 0; v12[k] || v12[k + 1]; k += 2 )
  {
    for ( m = (unsigned __int8)v12[k]; m <= (unsigned __int8)v12[k + 1]; g_CRT_MbcsLeadByteTable[m] = 1 )
      ++m;
  }
  if ( v2 != 1 )
  {
    CodePage = v2;
    return 0;
  }
  OEMCP = GetOEMCP();
LABEL_27:
  CodePage = OEMCP;
  return 0;
}
// 4D98AE: variable 'v8' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 54E718: using guessed type int dword_54E718;

//----- (004D9AED) --------------------------------------------------------
int __fastcall CRT_GetThreadMbcinfoPtr(int a1, int a2)
{
  return g_CrtThreadDataAccessor(a1, a2) + 198;
}
// 51A568: using guessed type int (__fastcall *g_CrtThreadDataAccessor)(_DWORD, _DWORD);

//----- (004D9B90) --------------------------------------------------------
int  Rules_ParseDeftemplateFactPattern(int a1, _DWORD *a2)
{
  signed int v4; // eax
  int v5; // esi
  _DWORD *v6; // eax
  int v7; // eax
  int v9[3]; // [esp+0h] [ebp-24h] BYREF
  _DWORD v10[6]; // [esp+Ch] [ebp-18h] BYREF

  Parser_NextToken(a1, (int)v9);
  if ( v9[0] == 92 || v9[0] == 91 )
  {
    Parser_ReportSyntaxError();
    return 0;
  }
  else
  {
    v4 = AST_AllocNode();
    *(_DWORD *)v4 = 17;
    v5 = v4;
    BYTE1(v4) = *(_BYTE *)(v4 + 8);
    *(_DWORD *)(v5 + 32) = 0;
    *(_DWORD *)(v5 + 40) = 1;
    *(_BYTE *)(v5 + 8) = BYTE1(v4) & 0xFE;
    v6 = (_DWORD *)AST_AllocNode();
    *(_DWORD *)(v5 + 68) = v6;
    *v6 = 2;
    *(_BYTE *)(*(_DWORD *)(v5 + 68) + 8) &= ~1u;
    *(_DWORD *)(*(_DWORD *)(v5 + 68) + 4) = *a2;
    v10[0] = 0;
    v7 = Lexer_ParseRuleRHS(a1, v9, v10, (int)a2);
    if ( v10[0] )
    {
      AST_FreeNode(v7);
      AST_FreeNode(v5);
      return 0;
    }
    else
    {
      *(_DWORD *)(v5 + 64) = v7;
      return v5;
    }
  }
}

//----- (004D9C40) --------------------------------------------------------
int  Lexer_ParseRuleRHS(int a1, int *a2, _DWORD *a3, int a4)
{
  int v6; // ebp
  int v7; // ecx
  int v8; // ecx
  _DWORD *v9; // ebx
  unsigned int *v10; // eax
  int v11; // eax
  int v13; // edx
  int v14; // edx
  int v15; // [esp+0h] [ebp-1Ch] BYREF
  int v16; // [esp+4h] [ebp-18h]
  _DWORD *v17; // [esp+8h] [ebp-14h]
  unsigned int *v18; // [esp+Ch] [ebp-10h]

  v16 = a4;
  v17 = a3;
  v6 = 0;
  v7 = *a2;
  v18 = 0;
  if ( v7 == 101 )
    return v6;
  while ( 1 )
  {
    IO_OutNewline();
    IO_OutWriteToken(asc_50D750);
    IO_OutWriteToken((char *)a2[2]);
    if ( *a2 != 100 || (Parser_NextToken(a1, (int)a2), *a2 != 2) )
    {
      *v17 = 1;
      Parser_ReportSyntaxError();
LABEL_12:
      v11 = v6;
      goto LABEL_13;
    }
    v9 = Lexer_FindTemplateSlot(v16, a2[1], &v15);
    if ( !v9 )
    {
      v13 = v16;
      *v17 = 1;
      Rules_ReportInvalidSlotError(v8, *(_DWORD *)(*(_DWORD *)v13 + 16));
      goto LABEL_12;
    }
    if ( Lexer_CheckDuplicateSlotName(v6, a2[1]) == 1 )
    {
      *v17 = 1;
      goto LABEL_12;
    }
    v10 = Lexer_ParseSlotValueList(a1, (int)a2, v17, (int)v9, v15 + 1);
    if ( *v17 )
      break;
    if ( v18 )
      v18[16] = (unsigned int)v10;
    else
      v6 = (int)v10;
    while ( v10[16] )
      v10 = (unsigned int *)v10[16];
    v18 = v10;
    Parser_NextToken(a1, (int)a2);
    if ( *a2 == 101 )
      return v6;
  }
  AST_FreeNode(v6);
  v11 = v14;
LABEL_13:
  AST_FreeNode(v11);
  return 0;
}
// 4D9D28: variable 'v8' is possibly undefined
// 4D9D42: variable 'v14' is possibly undefined

//----- (004D9D70) --------------------------------------------------------
unsigned int * Lexer_ParseSlotValueList(int a1, int a2, _DWORD *a3, int a4, int a5)
{
  int v7; // edx
  int v8; // ecx
  unsigned int *v9; // eax
  unsigned int *v10; // edx
  int v12; // edx
  int v13; // edx

  IO_OutWriteToken(asc_50D750);
  Parser_NextToken(a1, v7);
  if ( (*(_BYTE *)(a4 + 4) & 1) != 0 )
  {
    v10 = Rules_ParsePatternFieldList(a1, (int *)a2, v8, 1, a5 - 1, *(int **)(a4 + 8), 1);
    if ( !v10 )
    {
      *a3 = 1;
      return 0;
    }
  }
  else
  {
    v9 = Rules_ParsePatternFieldList(a1, (int *)a2, *(_DWORD *)a4, 0, a5 - 1, *(int **)(a4 + 8), 0);
    v10 = v9;
    if ( !v9 )
    {
      *a3 = 1;
      return 0;
    }
    if ( *v9 == 16 || *v9 == 4 )
    {
      Rules_ReportSingleFieldSlotCardError();
      *a3 = 1;
      AST_FreeNode(v12);
      return 0;
    }
  }
  if ( *(_DWORD *)a2 == 101 )
  {
    if ( !v10[17] && (*(_BYTE *)(a4 + 4) & 1) != 0 )
    {
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(asc_50D754);
    }
    return v10;
  }
  else
  {
    IO_OutNewline();
    IO_OutWriteToken(asc_50D750);
    IO_OutWriteToken(*(char **)(a2 + 8));
    Parser_ReportSyntaxError();
    *a3 = 1;
    AST_FreeNode(v13);
    return 0;
  }
}
// 4D9D8E: variable 'v7' is possibly undefined
// 4D9DF3: variable 'v10' is possibly undefined
// 4D9E21: variable 'v12' is possibly undefined
// 4D9E41: variable 'v8' is possibly undefined
// 4D9E90: variable 'v13' is possibly undefined

//----- (004D9EA0) --------------------------------------------------------
signed int  Lexer_CheckDuplicateSlotName(int a1, int a2)
{
  int v2; // ecx

  if ( !a1 )
    return 0;
  while ( 1 )
  {
    v2 = *(_DWORD *)(a1 + 36);
    if ( a2 == v2 )
      break;
    a1 = *(_DWORD *)(a1 + 64);
    if ( !a1 )
      return 0;
  }
  Rules_ReportAlreadyParsed(v2, *(_DWORD *)(v2 + 16));
  return 1;
}

//----- (004D9ED0) --------------------------------------------------------
int * Lexer_ParseRuleLHS(int a1, int a2, int a3, double a4)
{
  _DWORD *v5; // edx
  _DWORD *v6; // eax
  int v8[3]; // [esp+0h] [ebp-Ch] BYREF

  v8[2] = a2;
  v8[0] = 0;
  g_CLIPS_CurrentRuleSalience = 0;
  g_Rules_DeclaredAutoFocusFlag = 0;
  g_ClipsParsedFormAst = 0;
  Rules_SetIndentDepth(3);
  v6 = Lexer_ParseRuleLHSPatterns(a1, v5, v8, a3, a4);
  if ( v8[0] )
    return 0;
  else
    return Rules_BuildConjunctionFromPatternList((int)v6);
}
// 4D9EFF: variable 'v5' is possibly undefined
// 51C6F4: using guessed type int dword_51C6F4;
// 54E90C: using guessed type int dword_54E90C;
// 54E910: using guessed type int dword_54E910;

//----- (004D9F20) --------------------------------------------------------
_DWORD * Lexer_ParseRuleLHSPatterns(int a1, _DWORD *a2, int *a3, int a4, double a5)
{
  _DWORD *v8; // eax
  int v9; // edx
  int v10; // edi
  _DWORD *result; // eax
  _DWORD *v12; // [esp+0h] [ebp-10h]

  *a3 = 0;
  if ( *a2 == 2 && !strcmp_(a3, Lexer_Token_Arrow) )
    return 0;
  v8 = Lexer_ParsePatternCE(a1, 2, (int)Lexer_Token_Arrow, a5, 1, (int)a2, a4);
  v10 = (int)v8;
  v12 = v8;
  if ( *a3 == 1 )
  {
    AST_FreeNode((int)v8);
    return 0;
  }
  else
  {
    AST_Append(*a3, v9);
    result = (_DWORD *)Lexer_ParsePatternCEList(2, a3, Lexer_Token_Arrow, a1, a5);
    if ( *a3 == 1 )
    {
      AST_FreeNode(v10);
      return 0;
    }
    else if ( v10 )
    {
      *(_DWORD *)(v10 + 68) = result;
      return v12;
    }
  }
  return result;
}
// 4D9F76: variable 'v9' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004D9FD0) --------------------------------------------------------
int  Lexer_ParseDeclareOptions(_DWORD *a1, double a2)
{
  int v3; // ebx
  int v4; // edx
  int v5; // ecx
  int v6; // ecx
  int v7; // ebp
  int v8; // ecx
  int result; // eax
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // edx
  _DWORD v15[7]; // [esp+0h] [ebp-1Ch] BYREF

  IO_OutWriteToken(asc_50D764);
  v3 = 0;
  Parser_NextToken(v5, v4);
  v7 = 0;
  if ( v15[0] == 100 )
  {
    while ( 1 )
    {
      Parser_NextToken(v6, (int)v15);
      if ( v15[0] != 2 )
      {
LABEL_3:
        Parser_ReportSyntaxError();
LABEL_4:
        *a1 = 1;
LABEL_5:
        result = AST_Free(g_ClipsParsedFormAst);
        g_ClipsParsedFormAst = 0;
        return result;
      }
      if ( !strcmp_(v8, aSalience) )
      {
        if ( v3 )
          goto LABEL_18;
        Lexer_ParseSalienceOption(a1, a2);
        v3 = 1;
      }
      else
      {
        if ( strcmp_(v10, aAutoFocus) )
          goto LABEL_3;
        if ( v7 )
        {
LABEL_18:
          Rules_ReportAlreadyParsed(v10, 0);
          goto LABEL_4;
        }
        v7 = 1;
        Lexer_ParseAutoFocusOption(v10);
      }
      if ( *a1 )
        goto LABEL_5;
      Parser_NextToken(v11, (int)v15);
      if ( v15[0] != 101 )
      {
        IO_OutNewline();
        IO_OutWriteToken(asc_50D764);
        IO_OutWriteToken((char *)v15[2]);
        AST_Free(g_ClipsParsedFormAst);
        g_ClipsParsedFormAst = v13;
        result = Parser_ReportSyntaxError();
        *a1 = 1;
        return result;
      }
      Parser_NextToken(v12, (int)v15);
      if ( v15[0] == 101 )
        break;
      if ( v15[0] != 100 )
      {
        AST_Free(g_ClipsParsedFormAst);
        g_ClipsParsedFormAst = 0;
        result = Parser_ReportSyntaxError();
        *a1 = 1;
        return result;
      }
      IO_OutNewline();
      IO_OutWriteToken(Lexer_Token_OpenParenSpace);
    }
    AST_PackNodeChain((_DWORD *)g_ClipsParsedFormAst);
    result = AST_Free(g_ClipsParsedFormAst);
    g_ClipsParsedFormAst = v14;
  }
  else
  {
    result = Parser_ReportSyntaxError();
    *a1 = 1;
  }
  return result;
}
// 4D9FED: variable 'v5' is possibly undefined
// 4D9FED: variable 'v4' is possibly undefined
// 4DA000: variable 'v6' is possibly undefined
// 4DA053: variable 'v8' is possibly undefined
// 4DA079: variable 'v11' is possibly undefined
// 4DA08C: variable 'v12' is possibly undefined
// 4DA0D7: variable 'v10' is possibly undefined
// 4DA135: variable 'v13' is possibly undefined
// 4DA18E: variable 'v14' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51C6F4: using guessed type int dword_51C6F4;

//----- (004DA1A0) --------------------------------------------------------
int  Lexer_ParseSalienceOption(_DWORD *a1, double a2)
{
  int v2; // ecx
  int result; // eax
  _DWORD *v4; // edx
  int v5; // ecx
  int v6; // ecx
  int v7; // [esp+0h] [ebp-1Ch]
  int v8; // [esp+4h] [ebp-18h]

  IO_OutWriteToken(asc_50D764);
  result = Parser_ParseSingleExpression(v2, 0, v2);
  g_ClipsParsedFormAst = result;
  if ( result )
  {
    Lexer_ErrorRecover(0);
    if ( Parser_ParseForm((__int16 *)g_ClipsParsedFormAst, v4, v5, a2) )
    {
      result = Rules_SalienceInformationError();
      *a1 = 1;
    }
    else if ( v7 == 1 )
    {
      v6 = *(_DWORD *)(v8 + 16);
      if ( v6 > 10000 || v6 < -10000 )
      {
        result = Rules_SalienceRangeError();
        *a1 = 1;
      }
      else
      {
        result = g_ClipsParsedFormAst;
        if ( *(_WORD *)g_ClipsParsedFormAst == 1 )
        {
          result = AST_Free(g_ClipsParsedFormAst);
          g_ClipsParsedFormAst = 0;
        }
        g_CLIPS_CurrentRuleSalience = v6;
      }
    }
    else
    {
      result = Rules_SalienceNonIntegerError();
      *a1 = 1;
    }
  }
  else
  {
    *a1 = 1;
  }
  return result;
}
// 4DA1B7: variable 'v2' is possibly undefined
// 4DA1DF: variable 'v4' is possibly undefined
// 4DA1DF: variable 'v5' is possibly undefined
// 4DA1ED: variable 'v7' is possibly undefined
// 4DA1F3: variable 'v8' is possibly undefined
// 4DA21E: variable 'v6' is possibly undefined
// 51C6F4: using guessed type int dword_51C6F4;
// 54E910: using guessed type int dword_54E910;

//----- (004DA260) --------------------------------------------------------
int  Lexer_ParseAutoFocusOption(int a1)
{
  int v2; // edx
  int v3; // ecx
  int result; // eax
  int v5; // ecx
  _DWORD *v6; // ecx
  int v7; // [esp+0h] [ebp-14h]

  IO_OutWriteToken(asc_50D764);
  Parser_NextToken(a1, v2);
  if ( v7 != 2 )
    goto LABEL_5;
  result = strcmp_(v3, aTrue_0);
  if ( result )
  {
    result = strcmp_(v5, aFalse_0);
    if ( !result )
    {
      g_Rules_DeclaredAutoFocusFlag = 0;
      return result;
    }
LABEL_5:
    result = Parser_ReportSyntaxError();
    *v6 = 1;
    return result;
  }
  g_Rules_DeclaredAutoFocusFlag = 1;
  return result;
}
// 4DA277: variable 'v2' is possibly undefined
// 4DA280: variable 'v7' is possibly undefined
// 4DA28E: variable 'v3' is possibly undefined
// 4DA2B1: variable 'v6' is possibly undefined
// 4DA2C5: variable 'v5' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 54E90C: using guessed type int dword_54E90C;

//----- (004DA2E0) --------------------------------------------------------
_DWORD * Lexer_ParsePatternCE(int a1, int a2, int a3, double a4, int a5, int a6, int a7)
{
  _DWORD *v9; // ecx
  _DWORD *result; // eax
  _DWORD *v11; // ecx
  _DWORD *v12; // ecx
  _DWORD *v13; // ecx
  _DWORD *v14; // ecx
  _DWORD *v15; // ecx
  _DWORD *v16; // ecx
  _DWORD *v17; // ecx
  _DWORD *v18; // ecx
  _DWORD *v19; // ecx
  int v20; // [esp+0h] [ebp-18h] BYREF

  if ( a6 )
    qmemcpy(&v20, (const void *)a6, 12);
  else
    Parser_NextToken(a1, (int)&v20);
  if ( v20 != 100 )
  {
    if ( v20 == 15 )
    {
      result = (_DWORD *)Lexer_ParsePatternBinding((int)v9, v9);
      if ( *v11 != 1 )
        return result;
LABEL_33:
      AST_FreeNode((int)result);
      return 0;
    }
    if ( a2 == v20 && !strcmp_(v9, a3) )
      return 0;
LABEL_15:
    Parser_ReportSyntaxError();
    *v14 = 1;
    return 0;
  }
  Parser_NextToken(a1, (int)&v20);
  if ( v20 != 2 )
    goto LABEL_15;
  if ( a5 && !strcmp_(v12, aDeclare) )
  {
    if ( !a7 )
      Rules_ReportSystemError((int)v12, 1);
    Lexer_ParseDeclareOptions(v12, a4);
    result = 0;
    if ( *v13 == 1 )
      goto LABEL_33;
  }
  else if ( !strcmp_(v12, aTest_0) )
  {
    result = (_DWORD *)Lexer_ParseTestCE(a1, v15, (int)v15);
    if ( *v16 == 1 )
      goto LABEL_33;
  }
  else if ( !strcmp_(v15, aAnd_1)
         || !strcmp_(v17, aLogical_0)
         || !strcmp_(v17, aNot_1)
         || !strcmp_(v17, aExists_0)
         || !strcmp_(v17, aForall_0)
         || !strcmp_(v17, aOr_1) )
  {
    result = (_DWORD *)Lexer_ParseConnectiveCE(v17, a1, a4);
    if ( *v18 == 1 )
      goto LABEL_33;
  }
  else
  {
    result = Rules_DispatchPatternTypeParser(&v20, (int)v17, v17);
    if ( *v19 == 1 )
      goto LABEL_33;
  }
  return result;
}
// 4DA316: variable 'v9' is possibly undefined
// 4DA31B: variable 'v11' is possibly undefined
// 4DA358: variable 'v12' is possibly undefined
// 4DA381: variable 'v13' is possibly undefined
// 4DA39D: variable 'v14' is possibly undefined
// 4DA3C7: variable 'v15' is possibly undefined
// 4DA3CC: variable 'v16' is possibly undefined
// 4DA3FF: variable 'v17' is possibly undefined
// 4DA467: variable 'v18' is possibly undefined
// 4DA480: variable 'v19' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 494140: using guessed type int COleDateTimeSpan::operator=(void);

//----- (004DA4E0) --------------------------------------------------------
signed int  Lexer_ParseConnectiveCE(_DWORD *a1, int a2, double a3)
{
  int v3; // esi
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  char *v7; // eax
  int v8; // edx
  signed int v9; // ecx
  signed int v10; // edx
  int v11; // ecx
  signed int v12; // ebp
  int v13; // edi
  signed int result; // eax
  int v15; // ecx
  int v16; // edx
  int v17; // ecx
  int v18; // edx
  int v19; // ecx
  int v20; // edx
  int v21; // ecx
  int v22; // ecx
  int v23; // ecx
  int v24; // esi
  _DWORD *v25; // eax
  int v26; // edx
  int v27; // eax
  int v28; // ecx
  signed int v29; // eax
  int v30; // ecx
  int v31; // edx
  int v32; // eax
  int v33; // eax
  int v34; // esi
  _DWORD *v35; // eax
  int v36; // edx
  int v37; // ecx
  int v38; // eax
  signed int v39; // eax
  int v40; // edx
  int v41; // eax
  int v42; // ecx
  _DWORD *v43; // eax
  int v44; // eax
  int v45; // ecx
  int v47; // [esp+4h] [ebp-18h]
  int v48; // [esp+8h] [ebp-14h]

  Rules_IncrementIndentDepth(5);
  v3 = 0;
  v48 = 0;
  if ( !strcmp_(v4, aOr_1) )
  {
    v3 = 82;
    v7 = asc_50D870;
    goto LABEL_4;
  }
  if ( !strcmp_(v5, aAnd_1) )
  {
    v3 = 81;
    v7 = asc_50D764;
LABEL_4:
    IO_OutWriteToken(v7);
    goto LABEL_5;
  }
  if ( !strcmp_(v6, aNot_1) )
  {
    v3 = 83;
    v7 = asc_50D764;
    goto LABEL_4;
  }
  if ( !strcmp_(v15, aExists_0) )
  {
    AST_Append(v17, v16);
    v3 = 86;
  }
  else if ( !strcmp_(v17, aForall_0) )
  {
    AST_Append(v19, v18);
    v3 = 87;
  }
  else if ( !strcmp_(v19, aLogical_0) )
  {
    AST_Append(v21, v20);
    v3 = 81;
    v48 = 1;
  }
LABEL_5:
  if ( g_Parser_InsideNegatedCEFlag && v48 )
  {
    Rules_PrintErrorID((int)aRulelhs, 1, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aTheLogicalCeCa, v22);
    *a1 = 1;
    return 0;
  }
  v47 = g_Parser_InsideNegatedCEFlag;
  if ( v3 == 83 || v3 == 86 || v3 == 87 )
    g_Parser_InsideNegatedCEFlag = 1;
  Lexer_ParsePatternCEList(101, a1, asc_50D94C, a2, a3);
  g_Parser_InsideNegatedCEFlag = v47;
  Rules_DecrementIndentDepth(5);
  if ( *a1 == 1 )
  {
    AST_FreeNode(v8);
    return 0;
  }
  if ( v48 )
    AST_MarkLogicalCEChain(v8);
  if ( !v9 )
  {
    Parser_ReportSyntaxError();
    *a1 = 1;
    return 0;
  }
  if ( v3 == 83 && *(_DWORD *)(v9 + 68) || v3 == 87 && !*(_DWORD *)(v9 + 68) )
  {
    Parser_ReportSyntaxError();
    AST_FreeNode(v23);
    *a1 = 1;
    return 0;
  }
  if ( (v3 == 81 || v3 == 82) && !*(_DWORD *)(v9 + 68) )
  {
    *(_BYTE *)(v9 + 8) &= ~2u;
    result = v9;
    *(_DWORD *)(v9 + 8) |= 2 * (v48 & 1);
    return result;
  }
  v10 = AST_AllocNode();
  v12 = v10;
  *(_BYTE *)(v10 + 8) &= ~2u;
  v13 = 2 * (v48 & 1);
  *(_DWORD *)(v10 + 8) |= v13;
  if ( v3 == 81 || v3 == 82 || v3 == 83 )
  {
    *(_DWORD *)v10 = v3;
    *(_DWORD *)(v10 + 64) = v11;
    return v10;
  }
  if ( v3 != 86 )
  {
    if ( v3 == 87 )
    {
      *(_DWORD *)v10 = 83;
      v24 = *(_DWORD *)(v11 + 68);
      *(_DWORD *)(v11 + 68) = 0;
      v25 = (_DWORD *)AST_AllocNode();
      *(_DWORD *)(v26 + 64) = v25;
      *v25 = 81;
      v27 = *(_DWORD *)(v26 + 64);
      *(_BYTE *)(v27 + 8) &= ~2u;
      *(_DWORD *)(v27 + 8) |= v13;
      *(_DWORD *)(*(_DWORD *)(v26 + 64) + 64) = v28;
      v29 = AST_AllocNode();
      v30 = v24;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v31 + 64) + 64) + 68) = v29;
      **(_DWORD **)(*(_DWORD *)(*(_DWORD *)(v31 + 64) + 64) + 68) = 83;
      v32 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v31 + 64) + 64) + 68);
      *(_BYTE *)(v32 + 8) &= ~2u;
      *(_DWORD *)(v32 + 8) |= v13;
      v33 = *(_DWORD *)(v24 + 68);
      v34 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v31 + 64) + 64) + 68);
      if ( v33 )
      {
        v43 = (_DWORD *)AST_AllocNode();
        *(_DWORD *)(v34 + 64) = v43;
        *v43 = 81;
        v44 = *(_DWORD *)(v34 + 64);
        *(_BYTE *)(v44 + 8) &= ~2u;
        *(_DWORD *)(v44 + 8) |= v13;
        *(_DWORD *)(*(_DWORD *)(v34 + 64) + 64) = v45;
      }
      else
      {
        *(_DWORD *)(v34 + 64) = v30;
      }
      return v12;
    }
    return v10;
  }
  *(_DWORD *)v10 = 83;
  v35 = (_DWORD *)AST_AllocNode();
  *(_DWORD *)(v36 + 64) = v35;
  *v35 = 83;
  v38 = *(_DWORD *)(v36 + 64);
  *(_BYTE *)(v38 + 8) &= ~2u;
  *(_DWORD *)(v38 + 8) |= v13;
  if ( *(_DWORD *)(v37 + 68) )
  {
    v39 = AST_AllocNode();
    *(_DWORD *)(*(_DWORD *)(v40 + 64) + 64) = v39;
    **(_DWORD **)(*(_DWORD *)(v40 + 64) + 64) = 81;
    v41 = *(_DWORD *)(*(_DWORD *)(v40 + 64) + 64);
    *(_BYTE *)(v41 + 8) &= ~2u;
    *(_DWORD *)(v41 + 8) |= v13;
    *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v40 + 64) + 64) + 64) = v42;
  }
  else
  {
    *(_DWORD *)(*(_DWORD *)(v36 + 64) + 64) = v37;
  }
  return v12;
}
// 4DA509: variable 'v4' is possibly undefined
// 4DA521: variable 'v5' is possibly undefined
// 4DA5B0: variable 'v8' is possibly undefined
// 4DA5B7: variable 'v9' is possibly undefined
// 4DA618: variable 'v11' is possibly undefined
// 4DA644: variable 'v6' is possibly undefined
// 4DA658: variable 'v15' is possibly undefined
// 4DA66C: variable 'v17' is possibly undefined
// 4DA675: variable 'v19' is possibly undefined
// 4DA675: variable 'v18' is possibly undefined
// 4DA69D: variable 'v16' is possibly undefined
// 4DA6C9: variable 'v21' is possibly undefined
// 4DA6C9: variable 'v20' is possibly undefined
// 4DA701: variable 'v22' is possibly undefined
// 4DA760: variable 'v23' is possibly undefined
// 4DA7E1: variable 'v26' is possibly undefined
// 4DA7F7: variable 'v28' is possibly undefined
// 4DA801: variable 'v31' is possibly undefined
// 4DA851: variable 'v36' is possibly undefined
// 4DA864: variable 'v37' is possibly undefined
// 4DA87F: variable 'v40' is possibly undefined
// 4DA8A4: variable 'v42' is possibly undefined
// 4DA8CC: variable 'v45' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 51C6F0: using guessed type int dword_51C6F0;

//----- (004DA8E0) --------------------------------------------------------
int  Lexer_ParsePatternCEList(int a1, _DWORD *a2, char *a3, int a4, double a5)
{
  int v6; // edi
  int v7; // eax
  int v8; // edx
  int v10; // edx
  int v11; // ecx
  int v14; // [esp+8h] [ebp-10h]

  v6 = 0;
  v14 = 0;
  while ( 1 )
  {
    v7 = Lexer_ParsePatternCE(a4, a1, (int)a3, a5, 0, 0, 0);
    if ( *a2 )
    {
      AST_FreeNode(v14);
      return 0;
    }
    if ( !v7 )
      break;
    if ( v6 )
      *(_DWORD *)(v6 + 68) = v7;
    else
      v14 = v7;
    AST_Append(0, v7);
    v6 = v8;
  }
  IO_OutNewline();
  IO_OutNewline();
  if ( a1 != 101 )
    AST_Append(v11, v10);
  IO_OutWriteToken(a3);
  return v14;
}
// 4DA929: variable 'v8' is possibly undefined
// 4DA95F: variable 'v11' is possibly undefined
// 4DA95F: variable 'v10' is possibly undefined

//----- (004DA980) --------------------------------------------------------
int  Lexer_ParseTestCE(int a1, _DWORD *a2, int a3)
{
  _DWORD *v5; // eax
  __int16 *v6; // eax
  __int16 *v7; // eax
  int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v13; // ecx
  _DWORD v14[6]; // [esp+0h] [ebp-18h] BYREF

  v14[4] = a3;
  IO_OutWriteToken(asc_50D764);
  v5 = (_DWORD *)AST_AllocNode();
  *v5 = 84;
  v6 = (__int16 *)Parser_ParseRequiredFunctionCall(a1, (int)v5);
  v7 = Rules_CECloneRestrictionExpr(v6);
  *(_DWORD *)(v8 + 56) = v7;
  AST_Free(v9);
  if ( *(_DWORD *)(v10 + 56) )
  {
    Parser_NextToken(a1, (int)v14);
    if ( v14[0] == 101 )
    {
      return v11;
    }
    else
    {
      Parser_ReportSyntaxError();
      *a2 = 1;
      AST_FreeNode(v13);
      return 0;
    }
  }
  else
  {
    *a2 = 1;
    AST_FreeNode(v10);
    return 0;
  }
}
// 4DA9AF: variable 'v8' is possibly undefined
// 4DA9B4: variable 'v9' is possibly undefined
// 4DA9B9: variable 'v10' is possibly undefined
// 4DA9CE: variable 'v11' is possibly undefined
// 4DA9FA: variable 'v13' is possibly undefined

//----- (004DAA10) --------------------------------------------------------
int  Lexer_ParsePatternBinding(int a1, _DWORD *a2)
{
  int v3; // edx
  int v4; // ecx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  int v10; // [esp+0h] [ebp-18h]
  int v11; // [esp+14h] [ebp-4h]

  v11 = a1;
  if ( g_Parser_InsideNegatedCEFlag )
  {
    Rules_PrintErrorID((int)aRulelhs, 2, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAPatternCeCann, v8);
    *a2 = 1;
    return 0;
  }
  else
  {
    IO_OutWriteToken(asc_50D764);
    Parser_NextToken(v4, v3);
    if ( v10 == 2 && !strcmp_(v5, asc_50D9B0) )
    {
      IO_OutWriteToken(asc_50D764);
      Parser_NextToken(v7, v6);
    }
    Parser_ReportSyntaxError();
    *a2 = 1;
    return 0;
  }
}
// 4DAA7A: conditional instruction was optimized away because %var_18.4==2
// 4DAA37: variable 'v4' is possibly undefined
// 4DAA37: variable 'v3' is possibly undefined
// 4DAA52: variable 'v5' is possibly undefined
// 4DAA71: variable 'v7' is possibly undefined
// 4DAA71: variable 'v6' is possibly undefined
// 4DAABD: variable 'v8' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 51C6F0: using guessed type int dword_51C6F0;

//----- (004DAAF0) --------------------------------------------------------
int  AST_MarkLogicalCEChain(int result)
{
  int i; // edx
  int v2; // ecx
  int v3; // edx

  for ( i = result; i; i = *(_DWORD *)(i + 68) )
  {
    while ( 1 )
    {
      BYTE1(result) = *(_BYTE *)(i + 8) | 2;
      v2 = *(_DWORD *)i;
      *(_BYTE *)(i + 8) = BYTE1(result);
      if ( v2 != 81 && v2 != 82 && v2 != 83 )
        break;
      result = AST_MarkLogicalCEChain(*(_DWORD *)(i + 64));
      i = *(_DWORD *)(v3 + 68);
      if ( !i )
        return result;
    }
  }
  return result;
}
// 4DAB15: variable 'v3' is possibly undefined

//----- (004DAB30) --------------------------------------------------------
_DWORD * Rules_DispatchPatternTypeParser(_DWORD *a1, int a2, _DWORD *a3)
{
  int v5; // ecx
  signed int v6; // eax
  char v7; // dl
  int v8; // ecx
  _DWORD *v9; // ebx
  int v10; // ecx
  int v12; // eax
  int v13; // ecx

  if ( *a1 != 2 || !strcmp_(a2, asc_50D9C8) || !strcmp_(v5, asc_50D9CC) )
  {
    Parser_ReportSyntaxError();
    *a3 = 1;
    return 0;
  }
  v6 = AST_AllocNode();
  v7 = *(_BYTE *)(v6 + 8);
  *(_DWORD *)v6 = 80;
  *(_BYTE *)(v6 + 8) = v7 & 0xFE;
  v8 = g_PatternParserListHead;
  v9 = (_DWORD *)v6;
  if ( !g_PatternParserListHead )
  {
LABEL_7:
    *a3 = 1;
    Parser_ReportSyntaxError();
    AST_FreeNode((int)v9);
    return 0;
  }
  while ( !(*(int (**)(void))(v8 + 12))() )
  {
    v8 = *(_DWORD *)(v10 + 92);
    if ( !v8 )
      goto LABEL_7;
  }
  v9[6] = v10;
  v12 = (*(int (__fastcall **)(int, _DWORD *))(v10 + 16))(v10, a1);
  v9[16] = v12;
  if ( v12 )
  {
    AST_PropagateDepthTag(v9, v13);
    return v9;
  }
  else
  {
    *a3 = 1;
    AST_FreeNode((int)v9);
    return 0;
  }
}
// 4DAB66: variable 'v5' is possibly undefined
// 4DAB99: variable 'v10' is possibly undefined
// 4DAC0B: variable 'v13' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51B348: using guessed type int dword_51B348;

//----- (004DAC20) --------------------------------------------------------
_DWORD * AST_PropagateDepthTag(_DWORD *result, int a2)
{
  _DWORD *i; // ecx
  int v4; // edx

  for ( i = result; i; i = (_DWORD *)i[17] )
  {
    v4 = i[16];
    i[6] = a2;
    if ( v4 )
      result = (_DWORD *)AST_PropagateDepthTag(v4, a2);
    if ( i[14] )
      result = (_DWORD *)AST_PropagateDepthTag(i[14], a2);
  }
  return result;
}
// 4DAC35: variable 'i' is possibly undefined

//----- (004DAC60) --------------------------------------------------------
_DWORD * AST_MarkNodeFieldBound(_DWORD *result, int a2)
{
  *(_BYTE *)(*result + 12) |= 2u;
  result[3] = a2;
  return result;
}

//----- (004DAC70) --------------------------------------------------------
_DWORD * AST_ExtractPatternBindingInfo(_DWORD *result, int a2)
{
  int v2; // ecx

  *result = *(_DWORD *)(*(_DWORD *)a2 + 12) << 16 >> 18;
  result[1] = *(_DWORD *)(**(_DWORD **)(a2 + 8) + 24);
  v2 = *(_DWORD *)(a2 + 16);
  if ( v2 )
    result[2] = *(_DWORD *)(v2 + 12);
  else
    result[2] = -1;
  return result;
}

//----- (004DACB0) --------------------------------------------------------
int  Rules_BuildIndexedSlotDescriptor(int result, _DWORD *a2, int a3, int a4, int a5, int a6)
{
  int v6; // ecx
  int v7; // ebp

  a2[2] = *(_DWORD *)(result + 4) * a4 + a3;
  v6 = *(_DWORD *)(g_ClipsBloadSymbolPointerArray + 4 * *(_DWORD *)result);
  *a2 = v6;
  ++*(_DWORD *)(v6 + 4);
  v7 = *(_DWORD *)(result + 8);
  if ( v7 == -1 )
  {
    a2[4] = 0;
  }
  else
  {
    result = v7 * a5;
    a2[4] = v7 * a5 + a6;
  }
  a2[1] = 0;
  a2[3] = 0;
  return result;
}
// 54E674: using guessed type int dword_54E674;

//----- (004DAD10) --------------------------------------------------------
int  Rules_ReleaseSymbolReference(int *a1, int a2)
{
  return Rules_DecrementSymbolCount(*a1, a2);
}

//----- (004DAD20) --------------------------------------------------------
_DWORD *Module_RegisterBsaveBloadHandlers()
{
  Rules_AddBeforeBloadFunction((int)aDefmodule_3, (int)Module_RemoveAllModules, 2000);
  Rules_RegisterBinaryItem(
    (int)aDefmodule_3,
    0,
    0,
    (int)Module_BsaveCountModulesAndItems,
    (int)Module_BsaveWriteHeaderCounts,
    (int)Module_BsaveWriteModuleRecords,
    (int)Module_BloadReadHeaderCounts,
    (int)Module_BloadRefreshModules,
    (int)Module_ClearBloadData);
  return Rules_AddAbortBloadFunction((int)aDefmodule_3, (int)Module_CreateMainModule, 0);
}

//----- (004DAD80) --------------------------------------------------------
_DWORD * Module_UpdateItemHeader(_DWORD *result, _DWORD *a2, int a3, int a4)
{
  int v4; // esi
  int v5; // esi
  int v6; // ebx

  *a2 = 32 * *result + g_ClipsModuleArrayBase;
  v4 = result[1];
  if ( v4 == -1 )
  {
    a2[1] = 0;
    a2[2] = 0;
  }
  else
  {
    v5 = a4 * v4;
    v6 = result[2] * a4;
    result = (_DWORD *)(a3 + v5);
    a2[1] = a3 + v5;
    a2[2] = v6 + a3;
  }
  return result;
}
// 51C704: using guessed type int dword_51C704;

//----- (004DADC0) --------------------------------------------------------
_DWORD * Module_AssignBsaveItemHeaderIndices(_DWORD *result, _DWORD *a2)
{
  int v2; // ecx

  *result = *(_DWORD *)(*a2 + 24);
  v2 = a2[1];
  if ( v2 )
  {
    result[1] = *(_DWORD *)(v2 + 12);
    result[2] = *(_DWORD *)(a2[2] + 12);
  }
  else
  {
    result[1] = -1;
    result[2] = -1;
  }
  return result;
}

//----- (004DADF0) --------------------------------------------------------
_DWORD *Module_BsaveCountModulesAndItems()
{
  _DWORD *result; // eax
  _DWORD *i; // ecx
  _DWORD *j; // eax
  int v3; // edx
  int v4; // ebp
  _DWORD *k; // eax
  int v6; // ebp
  int v7; // ebp

  if ( Rules_IsBloaded() )
  {
    Rules_ConstructQueuePush(g_ClipsBsaveModuleCount);
    Rules_ConstructQueuePush(g_ClipsBloadPortItemCount);
  }
  g_ClipsBsaveModuleCount = 0;
  g_ClipsBloadPortItemCount = 0;
  result = (_DWORD *)Module_NextEnum(0);
  for ( i = result; result; i = result )
  {
    ++g_ClipsBsaveModuleCount;
    *(_DWORD *)(*i + 12) |= 2u;
    for ( j = (_DWORD *)i[3]; j; j = (_DWORD *)j[3] )
    {
      ++g_ClipsBloadPortItemCount;
      if ( *j )
        *(_DWORD *)(*j + 12) |= 2u;
      v3 = j[1];
      if ( v3 )
        *(_DWORD *)(v3 + 12) |= 2u;
      v4 = j[2];
      if ( v4 )
        *(_DWORD *)(v4 + 12) |= 2u;
    }
    for ( k = (_DWORD *)i[4]; k; k = (_DWORD *)k[3] )
    {
      ++g_ClipsBloadPortItemCount;
      if ( *k )
        *(_DWORD *)(*k + 12) |= 2u;
      v6 = k[1];
      if ( v6 )
        *(_DWORD *)(v6 + 12) |= 2u;
      v7 = k[2];
      if ( v7 )
        *(_DWORD *)(v7 + 12) |= 2u;
    }
    result = (_DWORD *)Module_NextEnum((int)i);
  }
  return result;
}
// 51C6F8: using guessed type int dword_51C6F8;
// 51C6FC: using guessed type int dword_51C6FC;

//----- (004DAEC0) --------------------------------------------------------
const void * Module_BsaveWriteHeaderCounts(int a1, int a2)
{
  int v2; // ecx
  int v3; // ecx
  _DWORD v5[4]; // [esp+0h] [ebp-10h] BYREF

  v5[2] = a2;
  v5[0] = 8;
  Rules_BsaveWriteBlock(4, a1, v5);
  Rules_BsaveWriteBlock(4, v2, &g_ClipsBsaveModuleCount);
  return Rules_BsaveWriteBlock(4, v3, &g_ClipsBloadPortItemCount);
}
// 4DAEEA: variable 'v2' is possibly undefined
// 4DAEFB: variable 'v3' is possibly undefined
// 51C6F8: using guessed type int dword_51C6F8;
// 51C6FC: using guessed type int dword_51C6FC;

//----- (004DAF10) --------------------------------------------------------
int  Module_BsaveWriteModuleRecords(int a1)
{
  int v2; // ecx
  _DWORD *i; // ecx
  int v4; // ebp
  int v5; // eax
  int v6; // ecx
  int m; // edi
  _DWORD *n; // ecx
  int v9; // eax
  int v10; // ebx
  int v11; // ecx
  _DWORD *ii; // ecx
  int v13; // eax
  int v14; // ebx
  int v15; // ecx
  int result; // eax
  int j; // eax
  int k; // eax
  int v19; // [esp+0h] [ebp-40h] BYREF
  int v20; // [esp+4h] [ebp-3Ch]
  int v21; // [esp+8h] [ebp-38h]
  int v22; // [esp+Ch] [ebp-34h]
  int v23; // [esp+10h] [ebp-30h]
  int v24; // [esp+14h] [ebp-2Ch] BYREF
  int v25; // [esp+18h] [ebp-28h]
  int v26; // [esp+1Ch] [ebp-24h]
  int v27; // [esp+20h] [ebp-20h]
  int v28[7]; // [esp+24h] [ebp-1Ch] BYREF

  v28[0] = 16 * g_ClipsBloadPortItemCount + 20 * g_ClipsBsaveModuleCount;
  Rules_BsaveWriteBlock(4, a1, v28);
  g_ClipsBsaveModuleCount = v2;
  g_ClipsBloadPortItemCount = v2;
  for ( i = (_DWORD *)Module_NextEnum(0); i; i = (_DWORD *)Module_NextEnum(v6) )
  {
    v4 = g_ClipsBsaveModuleCount + 1;
    v5 = *(_DWORD *)(*i + 12) << 16 >> 18;
    ++g_ClipsBsaveModuleCount;
    v19 = v5;
    if ( i[7] )
      v22 = v4;
    else
      v22 = -1;
    if ( i[3] )
    {
      v20 = g_ClipsBloadPortItemCount;
      for ( j = i[3]; j; j = *(_DWORD *)(j + 12) )
        ++g_ClipsBloadPortItemCount;
    }
    else
    {
      v20 = -1;
    }
    if ( i[4] )
    {
      v21 = g_ClipsBloadPortItemCount;
      for ( k = i[4]; k; k = *(_DWORD *)(k + 12) )
        ++g_ClipsBloadPortItemCount;
    }
    else
    {
      v21 = -1;
    }
    v23 = i[6];
    Rules_BsaveWriteBlock(20, a1, &v19);
  }
  g_ClipsBloadPortItemCount = 0;
  for ( m = Module_NextEnum(0); m; m = Module_NextEnum(m) )
  {
    for ( n = *(_DWORD **)(m + 12); n; n = *(_DWORD **)(v11 + 12) )
    {
      ++g_ClipsBloadPortItemCount;
      if ( *n )
        v24 = *(_DWORD *)(*n + 12) << 16 >> 18;
      else
        v24 = -1;
      v9 = n[1];
      if ( v9 )
        v25 = *(_DWORD *)(v9 + 12) << 16 >> 18;
      else
        v25 = -1;
      v10 = n[2];
      if ( v10 )
        v26 = *(_DWORD *)(v10 + 12) << 16 >> 18;
      else
        v26 = -1;
      if ( n[3] )
        v27 = g_ClipsBloadPortItemCount;
      else
        v27 = -1;
      Rules_BsaveWriteBlock(16, a1, &v24);
    }
    for ( ii = *(_DWORD **)(m + 16); ii; ii = *(_DWORD **)(v15 + 12) )
    {
      ++g_ClipsBloadPortItemCount;
      if ( *ii )
        v24 = *(_DWORD *)(*ii + 12) << 16 >> 18;
      else
        v24 = -1;
      v13 = ii[1];
      if ( v13 )
        v25 = *(_DWORD *)(v13 + 12) << 16 >> 18;
      else
        v25 = -1;
      v14 = ii[2];
      if ( v14 )
        v26 = *(_DWORD *)(v14 + 12) << 16 >> 18;
      else
        v26 = -1;
      if ( ii[3] )
        v27 = g_ClipsBloadPortItemCount;
      else
        v27 = -1;
      Rules_BsaveWriteBlock(16, a1, &v24);
    }
  }
  result = Rules_IsBloaded();
  if ( result )
  {
    Rules_ConstructQueuePop(&g_ClipsBsaveModuleCount);
    return Rules_ConstructQueuePop(&g_ClipsBloadPortItemCount);
  }
  return result;
}
// 4DAF59: variable 'v2' is possibly undefined
// 4DAFD7: variable 'v6' is possibly undefined
// 4DB063: variable 'v11' is possibly undefined
// 4DB0D0: variable 'v15' is possibly undefined
// 51C6F8: using guessed type int dword_51C6F8;
// 51C6FC: using guessed type int dword_51C6FC;

//----- (004DB200) --------------------------------------------------------
int __fastcall Module_BloadReadHeaderCounts(int a1)
{
  int result; // eax
  _DWORD v2[3]; // [esp+0h] [ebp-Ch] BYREF

  v2[2] = a1;
  Rules_BloadReadBlock((uintptr_t)v2, 4u);
  Rules_BloadReadBlock((uintptr_t)&g_ClipsBsaveModuleCount, 4u);
  result = Rules_BloadReadBlock((uintptr_t)&g_ClipsBloadPortItemCount, 4u);
  if ( g_ClipsBsaveModuleCount )
  {
    v2[0] = 32 * g_ClipsBsaveModuleCount;
    result = Mem_HeapAllocWithRetry((_DWORD *)(32 * g_ClipsBsaveModuleCount));
    g_ClipsModuleArrayBase = result;
    if ( g_ClipsBloadPortItemCount )
    {
      v2[0] = 16 * g_ClipsBloadPortItemCount;
      result = Mem_HeapAllocWithRetry((_DWORD *)(16 * g_ClipsBloadPortItemCount));
      g_Defmodule_PortItemArrayPtr = result;
    }
    else
    {
      g_Defmodule_PortItemArrayPtr = 0;
    }
  }
  else
  {
    g_ClipsModuleArrayBase = 0;
  }
  return result;
}
// 51C6F8: using guessed type int dword_51C6F8;
// 51C6FC: using guessed type int dword_51C6FC;
// 51C700: using guessed type int dword_51C700;
// 51C704: using guessed type int dword_51C704;

//----- (004DB290) --------------------------------------------------------
int Module_BloadRefreshModules()
{
  int result; // eax
  int Enum; // eax
  int v2; // [esp-8h] [ebp-8h] BYREF

  result = Rules_BloadReadBlock((uintptr_t)&v2, 4u);
  if ( g_ClipsBsaveModuleCount )
  {
    Rules_BloadAndRefresh(g_ClipsBsaveModuleCount, 20, (void (__fastcall *)(signed int, signed int))Module_BloadFixupModuleRecord);
    Rules_BloadAndRefresh(g_ClipsBloadPortItemCount, 16, (void (__fastcall *)(signed int, signed int))Module_BloadFixupPortItemRecord);
    Module_SetModuleListHead(g_ClipsModuleArrayBase);
    Enum = Module_NextEnum(0);
    return Module_SetCurrent(Enum);
  }
  return result;
}
// 51C6F8: using guessed type int dword_51C6F8;
// 51C6FC: using guessed type int dword_51C6FC;
// 51C704: using guessed type int dword_51C704;

//----- (004DB300) --------------------------------------------------------
int  Module_BloadFixupModuleRecord(_DWORD *a1, int a2)
{
  int module_offset; // edx
  int module; // ebx
  int parent_index; // edi
  int constraint; // edx
  int constraint_index; // ebx
  int constraint_offset; // ecx
  int value; // eax
  int import_index; // edx
  int export_index; // ecx
  int result; // eax

  module_offset = 32 * a2;
  module = g_ClipsModuleArrayBase + module_offset;
  *(_DWORD *)module = *(_DWORD *)(4 * *a1 + g_ClipsBloadSymbolPointerArray);
  ++*(_DWORD *)(*(_DWORD *)module + 4);
  parent_index = a1[3];
  if ( parent_index == -1 )
    *(_DWORD *)(module + 28) = 0;
  else
    *(_DWORD *)(module + 28) = g_ClipsModuleArrayBase + 32 * parent_index;
  *(_DWORD *)(module + 8) = Mem_SmallBlockAlloc(4 * Module_GetItemCount());
  constraint = Module_GetItemList();
  constraint_index = 0;
  constraint_offset = 0;
  while ( constraint_index < Module_GetItemCount() && constraint )
  {
    if ( *(_DWORD *)(constraint + 16) )
      value = ((int (*)(int))(uintptr_t)(unsigned int)*(_DWORD *)(constraint + 16))(a2);
    else
      value = 0;
    *(_DWORD *)(constraint_offset + *(_DWORD *)(module + 8)) = value;
    constraint_offset += 4;
    ++constraint_index;
    constraint = *(_DWORD *)(constraint + 28);
  }
  *(_DWORD *)(module + 4) = 0;
  import_index = a1[1];
  if ( import_index == -1 )
    *(_DWORD *)(module + 12) = 0;
  else
    *(_DWORD *)(module + 12) = 16 * import_index + g_Defmodule_PortItemArrayPtr;
  export_index = a1[2];
  if ( export_index == -1 )
    *(_DWORD *)(module + 16) = 0;
  else
    *(_DWORD *)(module + 16) = 16 * export_index + g_Defmodule_PortItemArrayPtr;
  result = a1[4];
  *(_DWORD *)(module + 24) = result;
  return result;
}
// 51C700: using guessed type int dword_51C700;
// 51C704: using guessed type int dword_51C704;
// 54E674: using guessed type int dword_54E674;

//----- (004DB470) --------------------------------------------------------
int  Module_BloadFixupPortItemRecord(_DWORD *a1, int a2)
{
  int v2; // ebp
  int v3; // ecx
  int v4; // esi
  int v5; // ecx
  int v6; // ebp
  int v7; // edx
  int result; // eax

  if ( *a1 == -1 )
  {
    *(_DWORD *)(g_Defmodule_PortItemArrayPtr + 16 * a2) = 0;
  }
  else
  {
    *(_DWORD *)(g_Defmodule_PortItemArrayPtr + 16 * a2) = *(_DWORD *)(4 * *a1 + g_ClipsBloadSymbolPointerArray);
    ++*(_DWORD *)(*(_DWORD *)(g_Defmodule_PortItemArrayPtr + 16 * a2) + 4);
  }
  v2 = a1[1];
  v3 = 16 * a2;
  if ( v2 == -1 )
  {
    *(_DWORD *)(v3 + g_Defmodule_PortItemArrayPtr + 4) = 0;
  }
  else
  {
    *(_DWORD *)(v3 + g_Defmodule_PortItemArrayPtr + 4) = *(_DWORD *)(g_ClipsBloadSymbolPointerArray + 4 * v2);
    ++*(_DWORD *)(*(_DWORD *)(v3 + g_Defmodule_PortItemArrayPtr + 4) + 4);
  }
  v4 = a1[2];
  v5 = 16 * a2;
  if ( v4 == -1 )
  {
    *(_DWORD *)(v5 + g_Defmodule_PortItemArrayPtr + 8) = 0;
  }
  else
  {
    *(_DWORD *)(g_Defmodule_PortItemArrayPtr + v5 + 8) = *(_DWORD *)(g_ClipsBloadSymbolPointerArray + 4 * v4);
    ++*(_DWORD *)(*(_DWORD *)(v5 + g_Defmodule_PortItemArrayPtr + 8) + 4);
  }
  v6 = a1[3];
  v7 = 16 * a2;
  result = g_Defmodule_PortItemArrayPtr;
  if ( v6 == -1 )
    *(_DWORD *)(v7 + g_Defmodule_PortItemArrayPtr + 12) = 0;
  else
    *(_DWORD *)(v7 + g_Defmodule_PortItemArrayPtr + 12) = g_Defmodule_PortItemArrayPtr + 16 * v6;
  return result;
}
// 51C700: using guessed type int dword_51C700;
// 54E674: using guessed type int dword_54E674;

//----- (004DB590) --------------------------------------------------------
int Module_ClearBloadData()
{
  int v0; // ebx
  int v1; // ecx
  int v2; // ecx
  int *i; // edx
  int v4; // eax
  int *j; // edx
  int v6; // eax
  int v7; // eax
  int v8; // ecx
  int v9; // ecx
  int result; // eax

  v0 = 0;
  if ( g_ClipsBsaveModuleCount > 0 )
  {
    v1 = 0;
    do
    {
      Rules_DecrementSymbolCount(*(_DWORD *)(v1 + g_ClipsModuleArrayBase), v1);
      for ( i = *(int **)(v2 + g_ClipsModuleArrayBase + 12); i; i = (int *)i[3] )
      {
        if ( *i )
          Rules_DecrementSymbolCount(*i, v2);
        v4 = i[1];
        if ( v4 )
          Rules_DecrementSymbolCount(v4, v2);
        if ( i[2] )
          Rules_DecrementSymbolCount(i[2], v2);
      }
      for ( j = *(int **)(v2 + g_ClipsModuleArrayBase + 16); j; j = (int *)j[3] )
      {
        if ( *j )
          Rules_DecrementSymbolCount(*j, v2);
        v6 = j[1];
        if ( v6 )
          Rules_DecrementSymbolCount(v6, v2);
        if ( j[2] )
          Rules_DecrementSymbolCount(j[2], v2);
      }
      v7 = Module_GetItemCount();
      ++v0;
      Mem_SmallBlockFree(*(_DWORD **)(v8 + g_ClipsModuleArrayBase + 8), 4 * v7);
      v1 = v9 + 32;
    }
    while ( v0 < g_ClipsBsaveModuleCount );
  }
  if ( 32 * g_ClipsBsaveModuleCount )
    Mem_ReleasePoolBlock(g_ClipsModuleArrayBase, 32 * g_ClipsBsaveModuleCount);
  if ( 16 * g_ClipsBloadPortItemCount )
    Mem_ReleasePoolBlock(g_Defmodule_PortItemArrayPtr, 16 * g_ClipsBloadPortItemCount);
  Module_SetModuleListHead(0);
  result = Module_CreateMainModule();
  g_Module_MainRedefinable = 1;
  return result;
}
// 4DB5BD: variable 'v2' is possibly undefined
// 4DB5D2: variable 'i' is possibly undefined
// 4DB60D: variable 'j' is possibly undefined
// 4DB63F: variable 'v8' is possibly undefined
// 4DB64F: variable 'v9' is possibly undefined
// 51A9C4: using guessed type int dword_51A9C4;
// 51C6F8: using guessed type int dword_51C6F8;
// 51C6FC: using guessed type int dword_51C6FC;
// 51C700: using guessed type int dword_51C700;
// 51C704: using guessed type int dword_51C704;

//----- (004DB6B0) --------------------------------------------------------
signed int  Rules_CheckConstraintParseConflicts(int a1, __int16 *a2)
{
  _WORD *v3; // edx
  int v5; // ecx

  if ( (*(_DWORD *)a1 & 1) == 1 )
    goto LABEL_2;
  if ( (*(_BYTE *)(a1 + 1) & 4) != 0 && (*(_BYTE *)a1 & 2) == 0 )
  {
    Rules_ReportAttributeConflict((int)a2, (int)aAllowedSymbols);
    return 0;
  }
  if ( (*(_BYTE *)(a1 + 1) & 8) != 0 && (*(_BYTE *)a1 & 4) == 0 )
  {
    Rules_ReportAttributeConflict((int)a2, (int)aAllowedStrings);
    return 0;
  }
  if ( (*(_BYTE *)(a1 + 1) & 0x20) != 0 && (*(_BYTE *)a1 & 0x10) == 0 )
  {
    Rules_ReportAttributeConflict((int)a2, (int)aAllowedInteger);
    return 0;
  }
  if ( (*(_BYTE *)(a1 + 1) & 0x10) != 0 && (*(_BYTE *)a1 & 8) == 0 )
  {
    Rules_ReportAttributeConflict((int)a2, (int)aAllowedFloatsN);
    return 0;
  }
  if ( (*(_BYTE *)(a1 + 1) & 0x40) != 0 && (*(_BYTE *)a1 & 0x20) == 0 )
  {
    Rules_ReportAttributeConflict((int)a2, (int)aAllowedInstanc);
    return 0;
  }
  if ( (*(_BYTE *)(a1 + 1) & 2) != 0 && (a2 = *(__int16 **)(a1 + 6)) != 0 )
  {
    while ( !Rules_CheckValueAgainstConstraint(*a2, *(_DWORD *)(a2 + 1), a1) )
    {
      a2 = *(__int16 **)(v5 + 10);
      if ( !a2 )
        goto LABEL_2;
    }
    Rules_ReportAttributeConflict(v5, (int)aAllowedValues);
    return 0;
  }
  else
  {
LABEL_2:
    v3 = *(_WORD **)(a1 + 14);
    if ( (!v3
       || (*(_BYTE *)a1 & 1) != 0
       || (*v3 != 1 || (*(_BYTE *)a1 & 0x10) != 0) && (**(_WORD **)(a1 + 14) || (*(_BYTE *)a1 & 8) != 0))
      && (!*(_DWORD *)(a1 + 10)
       || (*(_BYTE *)a1 & 1) != 0
       || (**(_WORD **)(a1 + 10) != 1 || (*(_BYTE *)a1 & 0x10) != 0)
       && (**(_WORD **)(a1 + 10) || (*(_BYTE *)a1 & 8) != 0)) )
    {
      return 1;
    }
    else
    {
      Rules_ReportAttributeConflict((int)a2, (int)aRange_0);
      return 0;
    }
  }
}
// 4DB7A1: variable 'v5' is possibly undefined

//----- (004DB850) --------------------------------------------------------
signed int __fastcall Rules_ReportAttributeConflict(int a1, int a2)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx

  Rules_PrintErrorID((int)aCstrnpsr, 1, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aThe_2, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v4, v4);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAttributeConfl, v5);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], a2, v6);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAttribute_, v7);
}
// 4DB872: variable 'v3' is possibly undefined
// 4DB87E: variable 'v4' is possibly undefined
// 4DB88D: variable 'v5' is possibly undefined
// 4DB899: variable 'v6' is possibly undefined
// 4DB8A8: variable 'v7' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004DB8C0) --------------------------------------------------------
_WORD * Rules_ResetConstraintParsedFlags(_WORD *result)
{
  *result &= 0xF800u;
  return result;
}

//----- (004DB8D0) --------------------------------------------------------
BOOL  Rules_IsConstraintAttributeKeyword(int a1)
{
  int v1; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx

  return !strcmp_(a1, aType_0)
      || !strcmp_(v1, aRange_0)
      || !strcmp_(v3, aCardinality)
      || !strcmp_(v4, aAllowedSymbols)
      || !strcmp_(v5, aAllowedStrings)
      || !strcmp_(v6, aAllowedLexemes)
      || !strcmp_(v7, aAllowedInteg_0)
      || !strcmp_(v8, aAllowedFloats)
      || !strcmp_(v9, aAllowedNumbers)
      || !strcmp_(v10, aAllowedInstanc)
      || !strcmp_(v11, aAllowedValues);
}
// 4DB8F1: variable 'v1' is possibly undefined
// 4DB901: variable 'v3' is possibly undefined
// 4DB911: variable 'v4' is possibly undefined
// 4DB921: variable 'v5' is possibly undefined
// 4DB931: variable 'v6' is possibly undefined
// 4DB941: variable 'v7' is possibly undefined
// 4DB951: variable 'v8' is possibly undefined
// 4DB961: variable 'v9' is possibly undefined
// 4DB975: variable 'v10' is possibly undefined
// 4DB989: variable 'v11' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004DB9A0) --------------------------------------------------------
int  Rules_ParseStandardConstraintAttribute(char *a1, const char *a2, _BYTE *a3, int a4, int a5)
{
  int v8; // ecx
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

  if ( Rules_TestConstraintAttributeParsedFlag((int)a2, a3) )
  {
    Rules_ReportAlreadyParsed(0, (int)aAttribute);
    return 0;
  }
  else
  {
    if ( !strcmp_(0, aRange_0) || !strcmp_(v8, aCardinality) )
    {
      Rules_ParseRangeOrCardinalityAttribute((int)a1, a4, a2, a3, a1, a5);
    }
    else if ( !strcmp_(v10, aType_0) )
    {
      Rules_ParseTypeAttribute((int)a1, v11);
    }
    else if ( !strcmp_(v11, aAllowedSymbols)
           || !strcmp_(v12, aAllowedStrings)
           || !strcmp_(v13, aAllowedLexemes)
           || !strcmp_(v14, aAllowedInteg_0)
           || !strcmp_(v15, aAllowedFloats)
           || !strcmp_(v16, aAllowedNumbers)
           || !strcmp_(v17, aAllowedInstanc)
           || !strcmp_(v18, aAllowedValues) )
    {
      Rules_ParseAllowedValuesAttribute((int)a1, a2, (int)a3, a4);
    }
    Rules_MarkConstraintAttributeParsed(a3, (int)a2);
    return v19;
  }
}
// 4DBA0E: variable 'v8' is possibly undefined
// 4DBA1E: variable 'v10' is possibly undefined
// 4DBA2C: variable 'v11' is possibly undefined
// 4DBA4A: variable 'v12' is possibly undefined
// 4DBA5A: variable 'v13' is possibly undefined
// 4DBA6A: variable 'v14' is possibly undefined
// 4DBA7A: variable 'v15' is possibly undefined
// 4DBA8A: variable 'v16' is possibly undefined
// 4DBA9A: variable 'v17' is possibly undefined
// 4DBABD: variable 'v18' is possibly undefined
// 4DBACF: variable 'v19' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004DBAE0) --------------------------------------------------------
int  Rules_OverlayConstraint(int result, int a2, int *a3)
{
  char *v3; // edi
  int v4; // ecx
  int v6; // ecx
  signed int v7; // eax
  int v8; // ecx
  char v9; // bl
  char v10; // bh
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // ecx
  char v27; // bh
  int v28; // ecx
  int v29; // ecx
  signed int v30; // eax
  int v31; // ecx
  int v32; // ecx

  v3 = (char *)result;
  v4 = a2;
  if ( (*(_BYTE *)result & 1) == 0 )
  {
    v17 = *a3;
    *(_BYTE *)a2 &= ~1u;
    *(_DWORD *)a2 |= v17 & 1;
    v18 = *a3;
    *(_BYTE *)a2 &= ~2u;
    *(_DWORD *)a2 |= v18 & 2;
    v19 = *a3;
    *(_BYTE *)a2 &= ~4u;
    *(_DWORD *)a2 |= v19 & 4;
    v20 = *a3;
    *(_BYTE *)a2 &= ~8u;
    *(_DWORD *)a2 |= v20 & 8;
    v21 = *a3;
    *(_BYTE *)a2 &= ~0x10u;
    *(_DWORD *)a2 |= v21 & 0x10;
    v22 = *a3;
    *(_BYTE *)a2 &= ~0x20u;
    *(_DWORD *)a2 |= v22 & 0x20;
    v23 = *a3;
    *(_BYTE *)a2 &= ~0x40u;
    *(_DWORD *)a2 |= v23 & 0x40;
    v24 = *a3;
    *(_BYTE *)a2 &= ~0x80u;
    *(_DWORD *)a2 |= v24 & 0x80;
    v25 = *a3;
    *(_BYTE *)(a2 + 1) &= ~1u;
    result = v25 & 0x100;
    *(_DWORD *)a2 |= result;
  }
  if ( (*v3 & 2) == 0 )
  {
    AST_Free(*(_DWORD *)(a2 + 10));
    AST_Free(*(_DWORD *)(v6 + 14));
    v7 = AST_CloneNodeList(*(int *)((char *)a3 + 10));
    *(_DWORD *)(v8 + 10) = v7;
    result = AST_CloneNodeList(*(int *)((char *)a3 + 14));
    *(_DWORD *)(v4 + 14) = result;
  }
  v9 = v3[1];
  if ( (v9 & 1) == 0 )
  {
    v10 = *v3;
    if ( (*v3 & 4) != 0
      || (v10 & 8) != 0
      || (v10 & 0x10) != 0
      || (v10 & 0x40) != 0
      || (v10 & 0x20) != 0
      || v10 < 0
      || (v9 & 2) != 0 )
    {
      if ( (*v3 & 4) == 0 && (*((_BYTE *)a3 + 1) & 4) != 0 )
      {
        *(_BYTE *)(v4 + 1) |= 4u;
        result = Rules_MergeConstraintValueList(2, v4, (int)a3);
      }
      if ( (*v3 & 8) == 0 && (*((_BYTE *)a3 + 1) & 8) != 0 )
      {
        *(_BYTE *)(v4 + 1) |= 8u;
        result = Rules_MergeConstraintValueList(3, v4, (int)a3);
      }
      if ( (*v3 & 0x10) == 0 )
      {
        BYTE1(result) = *((_BYTE *)a3 + 1);
        if ( (result & 0x400) != 0 && (result & 0x800) != 0 )
        {
          *(_BYTE *)(v4 + 1) |= 0xCu;
          Rules_MergeConstraintValueList(2, v4, (int)a3);
          result = Rules_MergeConstraintValueList(3, v26, (int)a3);
        }
      }
      if ( (*v3 & 0x40) == 0 && (*((_BYTE *)a3 + 1) & 0x20) != 0 )
      {
        *(_BYTE *)(v4 + 1) |= 0x20u;
        result = Rules_MergeConstraintValueList(1, v4, (int)a3);
      }
      if ( (*v3 & 0x20) == 0 && (*((_BYTE *)a3 + 1) & 0x10) != 0 )
      {
        *(_BYTE *)(v4 + 1) |= 0x10u;
        result = Rules_MergeConstraintValueList(0, v4, (int)a3);
      }
      if ( *v3 >= 0 )
      {
        v27 = *((_BYTE *)a3 + 1);
        if ( (v27 & 0x20) != 0 && (v27 & 0x10) != 0 )
        {
          *(_BYTE *)(v4 + 1) |= 0x30u;
          Rules_MergeConstraintValueList(1, v4, (int)a3);
          result = Rules_MergeConstraintValueList(0, v28, (int)a3);
        }
      }
      if ( (v3[1] & 2) == 0 && (*((_BYTE *)a3 + 1) & 0x40) != 0 )
      {
        *(_BYTE *)(v4 + 1) |= 0x40u;
        result = Rules_MergeConstraintValueList(8, v4, (int)a3);
        if ( (v3[1] & 4) != 0 )
          return result;
        goto LABEL_39;
      }
    }
    else
    {
      v11 = *a3;
      *(_BYTE *)(v4 + 1) &= ~2u;
      *(_DWORD *)v4 |= v11 & 0x200;
      v12 = *a3;
      *(_BYTE *)(v4 + 1) &= ~4u;
      *(_DWORD *)v4 |= v12 & 0x400;
      v13 = *a3;
      *(_BYTE *)(v4 + 1) &= ~8u;
      *(_DWORD *)v4 |= v13 & 0x800;
      v14 = *a3;
      *(_BYTE *)(v4 + 1) &= ~0x10u;
      *(_DWORD *)v4 |= v14 & 0x1000;
      v15 = *a3;
      *(_BYTE *)(v4 + 1) &= ~0x20u;
      *(_DWORD *)v4 |= v15 & 0x2000;
      v16 = *a3;
      *(_BYTE *)(v4 + 1) &= ~0x40u;
      *(_DWORD *)v4 |= v16 & 0x4000;
      result = AST_CloneNodeList(*(int *)((char *)a3 + 6));
      *(_DWORD *)(v4 + 6) = result;
    }
  }
  if ( (v3[1] & 4) == 0 )
  {
LABEL_39:
    AST_Free(*(_DWORD *)(v4 + 18));
    AST_Free(*(_DWORD *)(v29 + 22));
    v30 = AST_CloneNodeList(*(int *)((char *)a3 + 18));
    *(_DWORD *)(v31 + 18) = v30;
    result = AST_CloneNodeList(*(int *)((char *)a3 + 22));
    *(_DWORD *)(v32 + 22) = result;
  }
  return result;
}
// 4DBAFF: variable 'v6' is possibly undefined
// 4DBB0F: variable 'v8' is possibly undefined
// 4DBB1A: variable 'v4' is possibly undefined
// 4DBCEE: variable 'v26' is possibly undefined
// 4DBD62: variable 'v28' is possibly undefined
// 4DBDA4: variable 'v29' is possibly undefined
// 4DBDB4: variable 'v31' is possibly undefined
// 4DBDBF: variable 'v32' is possibly undefined

//----- (004DBE40) --------------------------------------------------------
signed int  Rules_MergeConstraintValueList(signed int result, int a2, int a3)
{
  signed int v3; // edi
  __int16 *i; // ecx
  int v6; // ecx

  v3 = result;
  for ( i = *(__int16 **)(a3 + 6); i; i = *(__int16 **)(v6 + 10) )
  {
    while ( 1 )
    {
      result = *i;
      if ( result == v3 )
        break;
      i = *(__int16 **)(i + 5);
      if ( !i )
        return result;
    }
    result = AST_NewNode(result, *(_DWORD *)(i + 1));
    *(_DWORD *)(result + 10) = *(_DWORD *)(a2 + 6);
    *(_DWORD *)(a2 + 6) = result;
  }
  return result;
}
// 4DBE71: variable 'v6' is possibly undefined

//----- (004DBE80) --------------------------------------------------------
signed int  Rules_ParseAllowedValuesAttribute(int a1, const char *a2, int a3, int a4)
{
  char *v5; // ecx
  int v6; // edi
  int v7; // esi
  char v8; // ah
  char v9; // al
  _BYTE *v11; // ecx
  int v12; // ecx
  _BYTE *v13; // ecx
  char *v14; // edx
  char *v15; // ecx
  _BYTE *v16; // ecx
  unsigned int v17; // eax
  signed int v18; // ebx
  int v19; // edx
  unsigned int v20; // ecx
  int v21; // ecx
  bool v22; // zf
  bool v23; // zf
  signed int v24; // eax
  int v25; // ecx
  int v26; // ecx
  int v27; // ecx
  char v28[120]; // [esp+0h] [ebp-20Ch] BYREF
  char v29[120]; // [esp+78h] [ebp-194h] BYREF
  char v30[120]; // [esp+F0h] [ebp-11Ch] BYREF
  char v31[120]; // [esp+168h] [ebp-A4h] BYREF
  _DWORD v32[2]; // [esp+1E0h] [ebp-2Ch] BYREF
  char *v33; // [esp+1ECh] [ebp-20h]
  const char *v34; // [esp+1F0h] [ebp-1Ch]
  int v35; // [esp+1F4h] [ebp-18h]
  signed int v36; // [esp+1F8h] [ebp-14h]
  int v37; // [esp+1FCh] [ebp-10h]

  v34 = a2;
  v35 = a4;
  v6 = 0;
  v7 = 0;
  v37 = 0;
  if ( !strcmp_(a3, aAllowedValues) )
  {
    v8 = *v5;
    if ( (*v5 & 4) != 0
      || (v8 & 8) != 0
      || (v8 & 0x10) != 0
      || (v8 & 0x40) != 0
      || (v8 & 0x20) != 0
      || v8 < 0
      || (v5[1] & 2) != 0 )
    {
      v9 = *v5;
      if ( (*v5 & 4) != 0 )
      {
        v33 = aAllowedSymbols;
      }
      else if ( (v9 & 8) != 0 )
      {
        v33 = aAllowedStrings;
      }
      else if ( (v9 & 0x10) != 0 )
      {
        v33 = aAllowedLexemes;
      }
      else if ( (v9 & 0x40) != 0 )
      {
        v33 = aAllowedInteg_0;
      }
      else if ( (v9 & 0x20) != 0 )
      {
        v33 = aAllowedFloats;
      }
      else if ( v9 >= 0 )
      {
        if ( (v5[1] & 2) != 0 )
          v33 = aAllowedInstanc;
      }
      else
      {
        v33 = aAllowedNumbers;
      }
      Rules_ReportAttributeCannotCombine((int)v5, (int)v33);
      return 0;
    }
  }
  if ( (!strcmp_(v5, aAllowedValues)
     || !strcmp_(v11, aAllowedNumbers)
     || !strcmp_(v11, aAllowedInteg_0)
     || !strcmp_(v11, aAllowedFloats))
    && (*v11 & 2) != 0 )
  {
    Rules_ReportAttributeCannotCombine((int)v11, (int)aRange_0);
    return 0;
  }
  if ( strcmp_(v11, aAllowedValues) && (*(_BYTE *)(v12 + 1) & 1) != 0 )
  {
    Rules_ReportAttributeCannotCombine(v12, (int)aAllowedValues);
    return 0;
  }
  if ( !strcmp_(v12, aAllowedNumbers) && ((*v13 & 0x20) != 0 || (*v13 & 0x40) != 0) )
  {
    if ( (*v13 & 0x20) != 0 )
      v14 = aAllowedFloats;
    else
      v14 = aAllowedInteg_0;
LABEL_20:
    Rules_ReportAttributeCannotCombine((int)v13, (int)v14);
    return 0;
  }
  if ( (!strcmp_(v13, aAllowedInteg_0) || !strcmp_(v15, aAllowedFloats)) && *v15 < 0 )
  {
    Rules_ReportAttributeCannotCombine((int)v15, (int)aAllowedNumber);
    return 0;
  }
  if ( !strcmp_(v15, aAllowedLexemes) && ((*v13 & 4) != 0 || (*v13 & 8) != 0) )
  {
    if ( (*v13 & 4) != 0 )
      v14 = aAllowedSymbols;
    else
      v14 = aAllowedStrings;
    goto LABEL_20;
  }
  if ( (!strcmp_(v13, aAllowedSymbols) || !strcmp_(v16, aAllowedStrings)) && (*v16 & 0x10) != 0 )
  {
    Rules_ReportAttributeCannotCombine((int)v16, (int)aAllowedLexemes);
    return 0;
  }
  v17 = Rules_GetAllowedAttributeTokenCode((int)v34);
  Rules_SetConstraintAllowedTypeFlag(v17, v35, 1);
  v18 = *(_DWORD *)(v35 + 6);
  if ( v18 )
  {
    while ( *(_DWORD *)(v18 + 10) )
      v18 = *(_DWORD *)(v18 + 10);
  }
  IO_OutWriteToken(asc_50DB38);
  Parser_NextToken(a1, v19);
  if ( v32[0] != 101 )
  {
    while ( 1 )
    {
      IO_OutWriteToken(asc_50DB38);
      if ( v32[0] < 2u )
        break;
      if ( v32[0] <= 2u )
      {
        if ( v21 == 103 || v21 == 2 )
          goto LABEL_69;
        v23 = v21 == 111;
        goto LABEL_67;
      }
      if ( v32[0] < 8u )
      {
        if ( v32[0] != 3 )
          goto LABEL_101;
        if ( v21 == 103 || v21 == v32[0] )
          goto LABEL_69;
        v23 = v21 == 111;
        goto LABEL_67;
      }
      if ( v32[0] <= 8u )
      {
        if ( v21 != 103 )
        {
          v23 = v21 == 8;
          goto LABEL_67;
        }
LABEL_69:
        v7 = 1;
        goto LABEL_70;
      }
      if ( v32[0] != 15 )
      {
LABEL_101:
        sprintf_(v30, "%s attribute", v34);
        Parser_ReportSyntaxError();
        return 0;
      }
      if ( strcmp_(v21, a_variable) )
      {
        sprintf_(v31, "%s attribute", v34);
        Parser_ReportSyntaxError();
        return 0;
      }
      v37 = 1;
LABEL_70:
      if ( v6 )
      {
        Rules_PrintErrorID((int)aCstrnpsr, 4, 1);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aValueDoesNotMa, v25);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)v34, v26);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAttribute_0, v27);
        return 0;
      }
      if ( v7 && v37 )
      {
        sprintf_(v28, "%s attribute", v34);
        Parser_ReportSyntaxError();
        return 0;
      }
      v24 = AST_NewNode(v32[0], v32[1]);
      v36 = v24;
      if ( v18 )
        *(_DWORD *)(v18 + 10) = v24;
      else
        *(_DWORD *)(v35 + 6) = v24;
      Parser_NextToken(a1, (int)v32);
      v18 = v36;
      if ( v32[0] == 101 )
        goto LABEL_76;
    }
    if ( v32[0] )
    {
      if ( v21 == 103 )
        goto LABEL_69;
      v22 = v21 == 1;
    }
    else
    {
      if ( v21 == 103 )
        goto LABEL_69;
      v22 = v21 == 0;
    }
    if ( v22 )
      goto LABEL_69;
    v23 = v21 == 110;
LABEL_67:
    if ( !v23 )
      v6 = 1;
    goto LABEL_69;
  }
LABEL_76:
  if ( v7 || v37 )
  {
    if ( v37 )
    {
      if ( v20 >= 3 )
      {
        if ( v20 > 3 )
        {
          if ( v20 >= 0x67 )
          {
            if ( v20 > 0x67 )
            {
              if ( v20 >= 0x6E )
              {
                if ( v20 > 0x6E )
                {
                  if ( v20 == 111 )
                    *(_BYTE *)(v35 + 1) &= 0xF3u;
                }
                else
                {
                  *(_BYTE *)(v35 + 1) &= 0xCFu;
                }
              }
            }
            else
            {
              *(_BYTE *)(v35 + 1) &= ~2u;
            }
          }
          else if ( v20 == 8 )
          {
            *(_BYTE *)(v35 + 1) &= ~0x40u;
          }
        }
        else
        {
          *(_BYTE *)(v35 + 1) &= ~8u;
        }
      }
      else if ( v20 )
      {
        if ( v20 > 1 )
          *(_BYTE *)(v35 + 1) &= ~4u;
        else
          *(_BYTE *)(v35 + 1) &= ~0x20u;
      }
      else
      {
        *(_BYTE *)(v35 + 1) &= ~0x10u;
      }
    }
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken(asc_50DB94);
    return 1;
  }
  else
  {
    sprintf_(v29, "%s attribute", v34);
    Parser_ReportSyntaxError();
    return 0;
  }
}
// 4DBEB9: variable 'v5' is possibly undefined
// 4DBF2A: variable 'v11' is possibly undefined
// 4DBF48: variable 'v12' is possibly undefined
// 4DBF6B: variable 'v13' is possibly undefined
// 4DC0C0: variable 'v15' is possibly undefined
// 4DC15D: variable 'v16' is possibly undefined
// 4DC1EB: variable 'v19' is possibly undefined
// 4DC223: variable 'v21' is possibly undefined
// 4DC2C3: variable 'v20' is possibly undefined
// 4DC41C: variable 'v25' is possibly undefined
// 4DC42D: variable 'v26' is possibly undefined
// 4DC43C: variable 'v27' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];

//----- (004DC550) --------------------------------------------------------
signed int __fastcall Rules_ReportAttributeCannotCombine(int a1, int a2)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx

  Rules_PrintErrorID((int)aCstrnpsr, 3, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aThe_2, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v4, v4);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAttributeCanno, v5);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInConjunctionW, v6);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], a2, v7);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAttribute_, v8);
}
// 4DC575: variable 'v3' is possibly undefined
// 4DC581: variable 'v4' is possibly undefined
// 4DC590: variable 'v5' is possibly undefined
// 4DC59F: variable 'v6' is possibly undefined
// 4DC5AB: variable 'v7' is possibly undefined
// 4DC5BA: variable 'v8' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004DC5D0) --------------------------------------------------------
signed int  Rules_ParseTypeAttribute(int a1, int a2)
{
  int v3; // edi
  int v4; // edx
  int v5; // ebx
  int v6; // ecx
  signed int v7; // eax
  int v8; // ecx
  _BYTE *v9; // ecx
  _DWORD v11[7]; // [esp+0h] [ebp-1Ch] BYREF

  v11[5] = a2;
  IO_OutWriteToken(asc_50DB38);
  v3 = 0;
  Parser_NextToken(a1, v4);
  v5 = 0;
  while ( v11[0] != 101 )
  {
    IO_OutWriteToken(asc_50DB38);
    if ( v11[0] == 2 )
    {
      if ( v5 == 1 )
        goto LABEL_11;
      v7 = Rules_GetTypeNameTokenCode(*(_DWORD *)(v11[1] + 16));
      if ( v7 < 0 || Rules_UpdateCETypeFlag(v7, v8) )
        goto LABEL_11;
      v3 = 1;
      *v9 &= ~1u;
    }
    else
    {
      if ( v11[0] != 15 || strcmp_(v6, a_variable) || v3 || v5 )
        goto LABEL_11;
      v5 = 1;
    }
    Parser_NextToken(a1, (int)v11);
  }
  IO_OutNewline();
  IO_OutNewline();
  IO_OutWriteToken(asc_50DB94);
  if ( v3 || v5 )
    return 1;
LABEL_11:
  Parser_ReportSyntaxError();
  return 0;
}
// 4DC5EB: variable 'v4' is possibly undefined
// 4DC627: variable 'v8' is possibly undefined
// 4DC630: variable 'v9' is possibly undefined
// 4DC696: variable 'v6' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004DC6B0) --------------------------------------------------------
signed int  Rules_ParseRangeOrCardinalityAttribute(
        int a1,
        int a2,
        const char *a3,
        _BYTE *a4,
        char *a5,
        int a6)
{
  int v8; // ecx
  int v10; // edx
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  char v17; // al
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  _BYTE v22[120]; // [esp+0h] [ebp-10Ch] BYREF
  _BYTE v23[120]; // [esp+78h] [ebp-94h] BYREF
  int v24; // [esp+F0h] [ebp-1Ch] BYREF
  int v25; // [esp+F4h] [ebp-18h]
  const char *v26; // [esp+FCh] [ebp-10h]

  v26 = a3;
  if ( !strcmp_(a3, aRange_0) )
  {
    v8 = 1;
    *a4 |= 2u;
    if ( (a4[1] & 1) != 0 || (v17 = *a4, (char)*a4 < 0) || (v17 & 0x40) != 0 || (v17 & 0x20) != 0 )
    {
      if ( (a4[1] & 1) != 0 )
      {
        a5 = aAllowedValues;
      }
      else
      {
        LOBYTE(v8) = *a4;
        if ( (*a4 & 0x40) != 0 )
        {
          a5 = aAllowedInteg_0;
        }
        else if ( (v8 & 0x20) != 0 )
        {
          a5 = aAllowedFloats;
        }
        else if ( (v8 & 0x80u) != 0 )
        {
          a5 = aAllowedNumbers;
        }
      }
      Rules_ReportAttributeCannotCombine(v8, (int)a5);
      return 0;
    }
  }
  else
  {
    a4[1] |= 4u;
    if ( !a6 )
    {
      Rules_PrintErrorID((int)aCstrnpsr, 5, 1);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aTheCardinality, v15);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCanOnlyBeUsedW, v16);
      return 0;
    }
  }
  IO_OutWriteToken(asc_50DB38);
  Parser_NextToken(a1, v10);
  if ( v24 == 1 || !v24 && v11 )
  {
    if ( v11 )
    {
      AST_Free(*(_DWORD *)(a2 + 10));
      *(_DWORD *)(a2 + 10) = AST_NewNode(v24, v25);
    }
    else
    {
      AST_Free(*(_DWORD *)(a2 + 18));
      *(_DWORD *)(a2 + 18) = AST_NewNode(v24, v25);
    }
  }
  else if ( v24 != 15 || strcmp_(v11, a_variable) )
  {
    sprintf_(v22, "%s attribute", v26);
    Parser_ReportSyntaxError();
    return 0;
  }
  IO_OutWriteToken(asc_50DB38);
  Parser_NextToken(a1, v12);
  if ( v24 == 1 || !v24 && v13 )
  {
    if ( v13 )
    {
      AST_Free(*(_DWORD *)(a2 + 14));
      *(_DWORD *)(a2 + 14) = AST_NewNode(v24, v25);
    }
    else
    {
      AST_Free(*(_DWORD *)(a2 + 22));
      *(_DWORD *)(a2 + 22) = AST_NewNode(v24, v25);
    }
  }
  else if ( v24 != 15 || strcmp_(v13, a_variable) )
  {
    sprintf_(v23, "%s attribute", v26);
    Parser_ReportSyntaxError();
    return 0;
  }
  Parser_NextToken(a1, (int)&v24);
  if ( v24 == 101 )
  {
    if ( v14 )
    {
      if ( Rules_CompareBoundedCEValues(
             **(__int16 **)(a2 + 10),
             *(_DWORD *)(*(_DWORD *)(a2 + 10) + 2),
             *(_DWORD *)(*(_DWORD *)(a2 + 14) + 2),
             **(__int16 **)(a2 + 14)) != 1 )
        return 1;
      Rules_PrintErrorID((int)aCstrnpsr, 2, 1);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aMinimumRangeVa, v18);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOrEqualToTheMa, v19);
      return 0;
    }
    else
    {
      if ( Rules_CompareBoundedCEValues(
             **(__int16 **)(a2 + 18),
             *(_DWORD *)(*(_DWORD *)(a2 + 18) + 2),
             *(_DWORD *)(*(_DWORD *)(a2 + 22) + 2),
             **(__int16 **)(a2 + 22)) != 1 )
        return 1;
      Rules_PrintErrorID((int)aCstrnpsr, 2, 1);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aMinimumCardina, v20);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOrEqualToThe_0, v21);
      return 0;
    }
  }
  else
  {
    Parser_ReportSyntaxError();
    return 0;
  }
}
// 4DC745: variable 'v10' is possibly undefined
// 4DC75C: variable 'v11' is possibly undefined
// 4DC793: variable 'v12' is possibly undefined
// 4DC7AA: variable 'v13' is possibly undefined
// 4DC7EC: variable 'v14' is possibly undefined
// 4DC841: variable 'v15' is possibly undefined
// 4DC850: variable 'v16' is possibly undefined
// 4DC9EF: variable 'v18' is possibly undefined
// 4DC9FE: variable 'v19' is possibly undefined
// 4DCA4C: variable 'v20' is possibly undefined
// 4DCA5B: variable 'v21' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];

//----- (004DCA70) --------------------------------------------------------
int  Rules_GetAllowedAttributeTokenCode(int a1)
{
  int v1; // ecx
  int result; // eax
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx

  if ( !strcmp_(a1, aAllowedValues) )
    return 103;
  if ( !strcmp_(v1, aAllowedSymbols) )
    return 2;
  if ( !strcmp_(v3, aAllowedStrings) )
    return 3;
  if ( !strcmp_(v4, aAllowedLexemes) )
    return 111;
  if ( !strcmp_(v5, aAllowedInteg_0) )
    return 1;
  if ( !strcmp_(v6, aAllowedNumbers) )
    return 110;
  if ( !strcmp_(v7, aAllowedInstanc) )
    return 8;
  result = strcmp_(v8, aAllowedFloats);
  if ( result )
    return -1;
  return result;
}
// 4DCA91: variable 'v1' is possibly undefined
// 4DCAA9: variable 'v3' is possibly undefined
// 4DCAC1: variable 'v4' is possibly undefined
// 4DCAD9: variable 'v5' is possibly undefined
// 4DCAF1: variable 'v6' is possibly undefined
// 4DCB09: variable 'v7' is possibly undefined
// 4DCB21: variable 'v8' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004DCB40) --------------------------------------------------------
int  Rules_GetTypeNameTokenCode(int a1)
{
  int v1; // ecx
  int result; // eax
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx

  if ( !strcmp_(a1, aSymbol_7) )
    return 2;
  if ( !strcmp_(v1, aString_3) )
    return 3;
  if ( !strcmp_(v3, aLexeme_1) )
    return 111;
  if ( !strcmp_(v4, aInteger_4) )
    return 1;
  result = strcmp_(v5, aFloat_4);
  if ( result )
  {
    if ( !strcmp_(v6, aNumber_2) )
    {
      return 110;
    }
    else if ( !strcmp_(v7, aInstanceName_4) )
    {
      return 8;
    }
    else if ( !strcmp_(v8, aInstanceAddr_8) )
    {
      return 7;
    }
    else if ( !strcmp_(v9, aInstance_6) )
    {
      return 112;
    }
    else if ( !strcmp_(v10, aExternalAddr_1) )
    {
      return 5;
    }
    else if ( !strcmp_(v11, aFactAddress_2) )
    {
      return 6;
    }
    else
    {
      return -1;
    }
  }
  return result;
}
// 4DCB61: variable 'v1' is possibly undefined
// 4DCB79: variable 'v3' is possibly undefined
// 4DCB91: variable 'v4' is possibly undefined
// 4DCBA9: variable 'v5' is possibly undefined
// 4DCBB9: variable 'v6' is possibly undefined
// 4DCBD1: variable 'v7' is possibly undefined
// 4DCBE9: variable 'v8' is possibly undefined
// 4DCC01: variable 'v9' is possibly undefined
// 4DCC19: variable 'v10' is possibly undefined
// 4DCC31: variable 'v11' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004DCC50) --------------------------------------------------------
int  Rules_TestConstraintAttributeParsedFlag(int a1, _DWORD *a2)
{
  int v3; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx

  if ( !strcmp_(a1, aType_0) )
    return *a2 & 1;
  if ( !strcmp_(v3, aRange_0) )
    return *a2 << 30 >> 31;
  if ( !strcmp_(v5, aCardinality) )
    return *a2 << 21 >> 31;
  if ( !strcmp_(v6, aAllowedValues) )
    return *a2 << 23 >> 31;
  if ( !strcmp_(v7, aAllowedSymbols) )
    return *a2 << 29 >> 31;
  if ( !strcmp_(v8, aAllowedStrings) )
    return *a2 << 28 >> 31;
  if ( !strcmp_(v9, aAllowedLexemes) )
    return *a2 << 27 >> 31;
  if ( !strcmp_(v10, aAllowedInstanc) )
    return *a2 << 22 >> 31;
  if ( !strcmp_(v11, aAllowedInteg_0) )
    return *a2 << 25 >> 31;
  if ( !strcmp_(v12, aAllowedFloats) )
    return *a2 << 26 >> 31;
  if ( !strcmp_(v13, aAllowedNumbers) )
    return *a2 << 24 >> 31;
  return 1;
}
// 4DCC73: variable 'v3' is possibly undefined
// 4DCC8E: variable 'v5' is possibly undefined
// 4DCCA9: variable 'v6' is possibly undefined
// 4DCCC4: variable 'v7' is possibly undefined
// 4DCCDF: variable 'v8' is possibly undefined
// 4DCCFA: variable 'v9' is possibly undefined
// 4DCD15: variable 'v10' is possibly undefined
// 4DCD30: variable 'v11' is possibly undefined
// 4DCD4B: variable 'v12' is possibly undefined
// 4DCD66: variable 'v13' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004DCD90) --------------------------------------------------------
unsigned int  Rules_SetConstraintAllowedTypeFlag(unsigned int result, int a2, char a3)
{
  int v3; // ecx
  int v4; // ebp
  int v5; // esi
  int v6; // ebx

  v3 = a3 & 1;
  v4 = v3 << 12;
  v5 = v3 << 13;
  v6 = v3 << 10;
  if ( result < 3 )
  {
    if ( result )
    {
      if ( result > 1 )
      {
        *(_BYTE *)(a2 + 1) &= ~4u;
        *(_DWORD *)a2 |= v6;
      }
      else
      {
        *(_BYTE *)(a2 + 1) &= ~0x20u;
        *(_DWORD *)a2 |= v5;
      }
    }
    else
    {
      *(_BYTE *)(a2 + 1) &= ~0x10u;
      *(_DWORD *)a2 |= v4;
    }
    return result;
  }
  if ( result <= 3 )
  {
LABEL_14:
    *(_BYTE *)(a2 + 1) &= ~8u;
    *(_DWORD *)a2 |= v3 << 11;
    return result;
  }
  if ( result < 0x67 )
  {
    if ( result == 8 )
    {
      *(_BYTE *)(a2 + 1) &= ~0x40u;
      *(_DWORD *)a2 |= v3 << 14;
    }
    return result;
  }
  if ( result <= 0x67 )
  {
    *(_BYTE *)(a2 + 1) &= ~2u;
    *(_DWORD *)a2 |= v3 << 9;
    return result;
  }
  if ( result >= 0x6E )
  {
    if ( result <= 0x6E )
    {
      *(_BYTE *)(a2 + 1) &= ~0x20u;
      *(_DWORD *)a2 |= v5;
      *(_BYTE *)(a2 + 1) &= ~0x10u;
      *(_DWORD *)a2 |= v4;
      return result;
    }
    if ( result == 111 )
    {
      *(_BYTE *)(a2 + 1) &= ~4u;
      *(_DWORD *)a2 |= v6;
      goto LABEL_14;
    }
  }
  return result;
}

//----- (004DCE50) --------------------------------------------------------
int  Rules_MarkConstraintAttributeParsed(_BYTE *a1, int a2)
{
  int result; // eax
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx

  result = strcmp_(a2, aRange_0);
  if ( result )
  {
    result = strcmp_(v4, aType_0);
    if ( result )
    {
      result = strcmp_(v5, aCardinality);
      if ( result )
      {
        result = strcmp_(v6, aAllowedSymbols);
        if ( result )
        {
          result = strcmp_(v7, aAllowedStrings);
          if ( result )
          {
            result = strcmp_(v8, aAllowedLexemes);
            if ( result )
            {
              result = strcmp_(v9, aAllowedInteg_0);
              if ( result )
              {
                result = strcmp_(v10, aAllowedFloats);
                if ( result )
                {
                  result = strcmp_(v11, aAllowedNumbers);
                  if ( result )
                  {
                    result = strcmp_(v12, aAllowedValues);
                    if ( !result )
                      a1[1] |= 1u;
                  }
                  else
                  {
                    *a1 |= 0x80u;
                  }
                }
                else
                {
                  *a1 |= 0x20u;
                }
              }
              else
              {
                *a1 |= 0x40u;
              }
            }
            else
            {
              *a1 |= 0x10u;
            }
          }
          else
          {
            *a1 |= 8u;
          }
        }
        else
        {
          *a1 |= 4u;
        }
      }
      else
      {
        a1[1] |= 4u;
      }
    }
    else
    {
      *a1 |= 1u;
    }
  }
  else
  {
    *a1 |= 2u;
  }
  return result;
}
// 4DCE73: variable 'v4' is possibly undefined
// 4DCE89: variable 'v5' is possibly undefined
// 4DCEA0: variable 'v6' is possibly undefined
// 4DCEB6: variable 'v7' is possibly undefined
// 4DCECC: variable 'v8' is possibly undefined
// 4DCEE2: variable 'v9' is possibly undefined
// 4DCEF8: variable 'v10' is possibly undefined
// 4DCF0E: variable 'v11' is possibly undefined
// 4DCF24: variable 'v12' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004DCF40) --------------------------------------------------------
signed int  Rules_CEDetectDuplicatePatternBinding(_DWORD *a1)
{
  _DWORD *v1; // edi
  int v2; // ebp
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  char *v8; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int *v14; // ebp
  int *v15; // esi
  int v16; // ecx
  int v17; // [esp+4h] [ebp-1Ch]

  v1 = a1;
  v17 = 0;
  if ( !a1 )
    return v17;
  while ( *v1 == 80 )
  {
    if ( v1[1] )
    {
      v2 = v1[5];
      if ( v2 )
      {
        v17 = 1;
        if ( *(_DWORD *)(v2 + 32) == -1 )
        {
          Rules_PrintErrorID((int)aAnalysis, 1, 1);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDuplicatePatte, v3);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(v1[1] + 16), v4);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFoundInCe_0, v5);
          Rules_PrintLongInteger(v6, v1[2] << 19 >> 25);
          v8 = a__26;
        }
        else
        {
          Rules_PrintErrorID((int)aAnalysis, 2, 1);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aPatternAddress, v10);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(v1[1] + 16), v11);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUsedInCe, v12);
          Rules_PrintLongInteger(v13, v1[2] << 19 >> 25);
          v8 = aWasPreviouslyB;
        }
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)v8, v7);
      }
    }
    if ( Rules_CEPropagateVariableBindingCheck((int)v1) )
      return 1;
LABEL_9:
    v1 = (_DWORD *)v1[17];
    if ( !v1 )
      return v17;
  }
  if ( *v1 != 84 )
    goto LABEL_9;
  Rules_CEFindUnboundVariableReference(v1[14], 0, 0, v1[2] << 19 >> 25, 0);
  v14 = Rules_ClonePatternPositionConstraintList((int *)v1[14]);
  v15 = v14;
  if ( !v14 )
  {
LABEL_17:
    AST_FreeNode((int)v14);
    if ( v16 )
      v17 = 1;
    else
      v1[13] = AST_CloneFieldAccessSubtreePN(v1[14]);
    goto LABEL_9;
  }
  while ( !Rules_CEScanBranchesForVariableMatch((int)v1, (int)v1, 15, 0, v15[1], v15, 0) )
  {
    v15 = (int *)v15[16];
    if ( !v15 )
      goto LABEL_17;
  }
  AST_FreeNode((int)v14);
  return 1;
}
// 4DCFA2: variable 'v3' is possibly undefined
// 4DCFB2: variable 'v4' is possibly undefined
// 4DCFC1: variable 'v5' is possibly undefined
// 4DCFD4: variable 'v6' is possibly undefined
// 4DCFE3: variable 'v7' is possibly undefined
// 4DD027: variable 'v10' is possibly undefined
// 4DD037: variable 'v11' is possibly undefined
// 4DD046: variable 'v12' is possibly undefined
// 4DD059: variable 'v13' is possibly undefined
// 4DD0D8: variable 'v16' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004DD110) --------------------------------------------------------
signed int  Rules_CEPropagateVariableBindingCheck(int a1)
{
  int v1; // ecx
  int *v3; // esi
  int v4; // edx
  int *v6; // ecx

  v1 = a1;
  v3 = 0;
  if ( !a1 )
    return 0;
  do
  {
    while ( 1 )
    {
      if ( (*(_BYTE *)(v1 + 8) & 4) != 0 )
      {
        v3 = (int *)v1;
        v1 = *(_DWORD *)(v1 + 68);
      }
      if ( v1 )
      {
        v4 = *(_DWORD *)v1;
        if ( *(_DWORD *)v1 == 15 || v4 == 16 || v4 == 80 && *(_DWORD *)(v1 + 4) )
        {
          if ( Rules_CEBindPatternAddressVariable(v1, v3, a1) )
            return 1;
        }
        else if ( Rules_CEValidateFieldConstraintUsage((_DWORD *)v1, v3, a1) )
        {
          return 1;
        }
      }
      if ( v1 )
        break;
      v1 = (int)v3;
LABEL_10:
      v1 = *(_DWORD *)(v1 + 64);
      if ( !v1 )
        return 0;
    }
    if ( *(_DWORD *)(v1 + 64) || !v3 )
      goto LABEL_10;
    v6 = v3;
    v3 = 0;
    v1 = v6[16];
  }
  while ( v1 );
  return 0;
}
// 4DD14B: variable 'v1' is possibly undefined

//----- (004DD1A0) --------------------------------------------------------
signed int  Rules_CEBindPatternAddressVariable(int a1, int *a2, int a3)
{
  _BYTE *v6; // eax
  int v7; // [esp+0h] [ebp-18h]
  int v8; // [esp+4h] [ebp-14h]

  if ( *(_DWORD *)a1 == 80 )
  {
    v8 = *(_DWORD *)(a1 + 4);
    v7 = 15;
    if ( (*(_BYTE *)(a1 + 8) & 0x10) != 0 )
      AST_DecrementNodeRefCount(*(_DWORD **)(a1 + 16));
    v6 = (_BYTE *)Rules_CreateLHSParseNode();
    *(_DWORD *)(a1 + 16) = v6;
    *v6 &= ~1u;
    **(_BYTE **)(a1 + 16) |= 0x40u;
    *(_BYTE *)(*(_DWORD *)(a1 + 16) + 1) |= 1u;
    *(_BYTE *)(a1 + 8) |= 0x10u;
  }
  else
  {
    v7 = *(_DWORD *)a1;
    v8 = *(_DWORD *)(a1 + 4);
  }
  if ( *(_DWORD *)a1 == 80 )
    return Rules_CEScanBranchesForVariableMatch(a3, a1, v7, (int)a2, v8, (int *)a1, 1);
  Rules_CEFindBoundVariableOccurrence(*(_DWORD *)(a1 + 68), v7, (int *)a1, v8, *(_DWORD *)(a3 + 44), 1, 0);
  if ( !Rules_CEValidateFieldConstraintUsage((_DWORD *)a1, a2, a3) )
    return Rules_CEScanBranchesForVariableMatch(a3, a1, v7, (int)a2, v8, (int *)a1, 1);
  else
    return 1;
}

//----- (004DD260) --------------------------------------------------------
signed int  Rules_CEScanBranchesForVariableMatch(
        int a1,
        int a2,
        int a3,
        int a4,
        int a5,
        int *a6,
        signed int a7)
{
  if ( a4 && Rules_CEFindBoundVariableOccurrence(*(_DWORD *)(a4 + 64), a3, a6, a5, *(_DWORD *)(a1 + 44), a7, 0)
    || Rules_CEFindBoundVariableOccurrence(*(_DWORD *)(a2 + 64), a3, a6, a5, *(_DWORD *)(a1 + 44), a7, 0) )
  {
LABEL_9:
    Rules_ReportVariableFieldTypeConflict();
    return 1;
  }
  if ( *(_DWORD *)a1 == 80 || *(_DWORD *)a1 == 84 )
  {
    if ( (*(_BYTE *)(a1 + 8) & 1) != 0
      || *(_DWORD *)(a1 + 44) > *(_DWORD *)(a1 + 48)
      || !Rules_CEFindBoundVariableOccurrence(*(_DWORD *)(a1 + 68), a3, a6, a5, *(_DWORD *)(a1 + 44), a7, *(_DWORD *)a1 == 84) )
    {
      return 0;
    }
    goto LABEL_9;
  }
  return 0;
}

//----- (004DD330) --------------------------------------------------------
signed int  Rules_CEValidateFieldConstraintUsage(_DWORD *a1, int *a2, int a3)
{
  int *v5; // esi
  int v6; // ecx
  signed int v7; // [esp+0h] [ebp-18h]

  if ( *a1 == 80 )
    return 0;
  v7 = Rules_IntersectConnectedCEConstraints((int)a1);
  v5 = (int *)v7;
  if ( v7 )
  {
    while ( !Rules_CEScanBranchesForVariableMatch(a3, (int)a1, *v5, (int)a2, v5[1], v5, 0) )
    {
      v5 = (int *)v5[16];
      if ( !v5 )
        goto LABEL_6;
    }
    AST_FreeNode(v7);
    return 1;
  }
  else
  {
LABEL_6:
    AST_FreeNode(v7);
    if ( Rules_CEValidateLiteralAgainstConstraints((int)a1, *(_DWORD *)(a3 + 8) << 19 >> 25, v6) )
    {
      return 1;
    }
    else if ( Rules_ComputeConnectedCEConstraintGroup((int)a1, a2, a3) )
    {
      return 1;
    }
    else
    {
      AST_BuildClassHierarchyFieldAccessTest(a1, a3);
      return 0;
    }
  }
}
// 4DD390: variable 'v6' is possibly undefined

//----- (004DD3F0) --------------------------------------------------------
signed int  Rules_CEFindBoundVariableOccurrence(
        int a1,
        int a2,
        int *a3,
        int a4,
        int a5,
        signed int a6,
        int a7)
{
  int v7; // esi
  int v10; // edx
  _BYTE *v11; // eax
  _DWORD *v12; // ecx
  char v13; // dl
  int v14; // eax
  signed int result; // eax

  v7 = a1;
  if ( a1 )
  {
    while ( 1 )
    {
      v10 = *(_DWORD *)(v7 + 56);
      if ( v10 )
      {
        Rules_CEFindBoundVariableOccurrence(v10, a2, (int)a3, a4, a5, a6, 1);
      }
      else
      {
        if ( (*(_DWORD *)v7 == 15 || *(_DWORD *)v7 == 16) && a4 == *(_DWORD *)(v7 + 4) )
        {
          if ( !a7 && (a2 == 15 && *(_DWORD *)v7 == 16 || a2 == 16 && *(_DWORD *)v7 == 15) )
            return 1;
          if ( a3[4] && (*(_BYTE *)(v7 + 8) & 1) == 0 )
          {
            v11 = Rules_IntersectConstraints(a3[4], *(_DWORD *)(v7 + 16));
            v13 = *(_BYTE *)(v7 + 8);
            *(_DWORD *)(v7 + 16) = v11;
            if ( (v13 & 0x10) != 0 )
              AST_DecrementNodeRefCount(v12);
            *(_BYTE *)(v7 + 8) |= 0x10u;
          }
          if ( !a6 || *(_DWORD *)(v7 + 20) && a3[7] != *(_DWORD *)(v7 + 28) && a3[6] != *(_DWORD *)(v7 + 24) )
            goto LABEL_18;
        }
        else
        {
          if ( *(_DWORD *)v7 != 80 )
            goto LABEL_18;
          if ( a4 != *(_DWORD *)(v7 + 4) )
            goto LABEL_18;
          result = a6;
          if ( a6 != 1 )
            goto LABEL_18;
          if ( a2 == 16 )
            return result;
        }
        *(_DWORD *)(v7 + 20) = a3;
      }
LABEL_18:
      v14 = *(_DWORD *)(v7 + 64);
      if ( v14 && Rules_CEFindBoundVariableOccurrence(v14, a2, (int)a3, a4, a5, a6, a7) )
        return 1;
      if ( (*(_DWORD *)v7 == 80 || *(_DWORD *)v7 == 84) && a5 > *(_DWORD *)(v7 + 48) )
        return 0;
      v7 = *(_DWORD *)(v7 + 68);
      if ( !v7 )
        return 0;
    }
  }
  return 0;
}
// 4DD3F0: could not find valid save-restore pair for ebx
// 4DD472: variable 'v12' is possibly undefined

//----- (004DD580) --------------------------------------------------------
signed int  Rules_CEValidateLiteralAgainstConstraints(int a1, int a2, int a3)
{
  int v4; // esi
  int v6; // ebp
  unsigned int *v7; // esi
  unsigned int v8; // ebx
  signed int v9; // eax
  unsigned int *v10; // [esp+0h] [ebp-20h]
  int v11; // [esp+4h] [ebp-1Ch]
  int v12; // [esp+8h] [ebp-18h]

  if ( (*(_BYTE *)(a1 + 8) & 4) != 0 )
  {
    v4 = *(_DWORD *)(a1 + 68);
    if ( v4 )
    {
      while ( !Rules_CEValidateLiteralAgainstConstraints(v4, a2, a3) )
      {
        v4 = *(_DWORD *)(v4 + 64);
        if ( !v4 )
          return 0;
      }
      return 1;
    }
    return 0;
  }
  v12 = *(_DWORD *)(a1 + 32);
  v11 = *(_DWORD *)(a1 + 16);
  v6 = *(_DWORD *)(a1 + 36);
  v10 = *(unsigned int **)(a1 + 68);
  if ( !v10 )
    return 0;
  while ( 2 )
  {
    v7 = v10;
    do
    {
      if ( (*v7 == 15 || *v7 == 16) && !v7[5] )
      {
        Rules_ReportUnboundVariableUsage(v7[1], 0, v6, a2, v12);
        return 1;
      }
      v8 = *v7;
      if ( *v7 == 93 || v8 == 94 )
      {
        if ( Rules_CEFindUnboundVariableReference(v7[14], 0, v6, a2, v12) )
          return 1;
      }
      else if ( v8 < 4 || v8 == 8 )
      {
        if ( Rules_StaticConstraintCheckingEnabled() )
        {
          v9 = Rules_CheckValueAgainstConstraint(*v7, v7[1], v11);
          if ( v9 )
          {
            Rules_PrintConstraintViolationMessage((int)aALiteralRestri, 0, a2, 0, v6, v12, v9, v11, 1);
            return 1;
          }
        }
      }
      v7 = (unsigned int *)v7[16];
    }
    while ( v7 );
    v10 = (unsigned int *)v10[17];
    if ( v10 )
      continue;
    break;
  }
  return 0;
}
// 4DD5DF: conditional instruction was optimized away because %var_20.4!=0
// 4DD65B: simplified comparisons for 'ebx.4': ==1 || ==0 became <2u
// 4DD65B: simplified comparisons for 'ebx.4': <2u || ==2 became <3u
// 4DD65B: simplified comparisons for 'ebx.4': <3u || ==3 became <4u
// 4DD59D: variable 'a3' is possibly undefined

//----- (004DD6C0) --------------------------------------------------------
int  Rules_CEFindUnboundVariableReference(int a1, int a2, int a3, int a4, int a5)
{
  int v5; // esi
  int result; // eax
  int v8; // ecx
  int v9; // [esp+0h] [ebp-18h] BYREF
  int v10; // [esp+4h] [ebp-14h]
  int v11; // [esp+8h] [ebp-10h]

  v5 = a1;
  v10 = a2;
  v11 = 1;
  if ( !a1 )
    return 0;
  while ( 1 )
  {
    if ( *(_DWORD *)v5 == 15 )
    {
      if ( !*(_DWORD *)(v5 + 20) )
        break;
      if ( Rules_ConstraintIsUnmatchable(*(char **)(v5 + 16)) && Rules_StaticConstraintCheckingEnabled() )
      {
        Rules_PrintVariableBindingConstraintViolation(*(_DWORD *)(v5 + 4), v10, a4, v11, a3, a5);
        return v5;
      }
      goto LABEL_6;
    }
    if ( *(_DWORD *)v5 == 16 && !*(_DWORD *)(v5 + 20) )
      break;
    v8 = *(_DWORD *)v5;
    if ( *(_DWORD *)v5 == 13 )
    {
      if ( !Rules_FindImportExportConstruct(aDefglobal_6, &v9, *(_BYTE **)(*(_DWORD *)(v5 + 4) + 16), 1, 0) )
        break;
    }
    else if ( v8 == 10 || v8 == 11 || v8 == 12 )
    {
      if ( *(_DWORD *)(v5 + 68) )
      {
        result = Rules_CEFindUnboundVariableReference(*(_DWORD *)(v5 + 68), v5, a3, a4, a5);
        if ( result )
          return result;
      }
    }
LABEL_6:
    v5 = *(_DWORD *)(v5 + 64);
    ++v11;
    if ( !v5 )
      return 0;
  }
  Rules_ReportUnboundVariableUsage(*(_DWORD *)(v5 + 4), v10, a3, a4, a5);
  return v5;
}

//----- (004DD820) --------------------------------------------------------
signed int  Rules_ReportUnboundVariableUsage(int a1, int a2, int a3, int a4, int a5)
{
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // eax
  int v12; // ecx
  __int16 *v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v19; // ecx
  int v20; // ecx

  Rules_PrintErrorID((int)aAnalysis, 4, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aVariable_, v7);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(a1 + 16), v8);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_50DE28, v9);
  if ( a2 )
  {
    v11 = Rules_CECloneBindingList(a2);
    AST_Free(*(_DWORD *)(v11 + 10));
    *(_DWORD *)(v12 + 10) = 0;
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFoundInTheExpr, v12);
    Rules_PrintFieldExprList((signed int)g_IO_LogicalNameTable_WError[0], v13);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_50DE48, v14);
    AST_Free(v15);
  }
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aWasReferencedI, v10);
  Rules_PrintLongInteger(v16, a4);
  if ( a3 )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSlot_8, v17);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(a3 + 16), v20);
  }
  else if ( a5 > 0 )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aField_1, v17);
    Rules_PrintLongInteger(v19, a5);
  }
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aBeforeBeingDef, v17);
}
// 4DD84D: variable 'v7' is possibly undefined
// 4DD85D: variable 'v8' is possibly undefined
// 4DD86C: variable 'v9' is possibly undefined
// 4DD886: variable 'v12' is possibly undefined
// 4DD8A3: variable 'v13' is possibly undefined
// 4DD8B2: variable 'v14' is possibly undefined
// 4DD8B9: variable 'v15' is possibly undefined
// 4DD8C8: variable 'v10' is possibly undefined
// 4DD8D4: variable 'v16' is possibly undefined
// 4DD906: variable 'v17' is possibly undefined
// 4DD914: variable 'v19' is possibly undefined
// 4DD932: variable 'v20' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004DD940) --------------------------------------------------------
signed int Rules_ReportVariableFieldTypeConflict()
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)aAnalysis, 3, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aVariable_, v0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(v1 + 16), v1);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIsUsedAsBothAS, v2);
}
// 4DD963: variable 'v0' is possibly undefined
// 4DD96D: variable 'v1' is possibly undefined
// 4DD97F: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004DD990) --------------------------------------------------------
int Rules_CheckAndReportUnmatchableFieldConstraint()
{
  int result; // eax
  int v1; // ecx
  int v2; // edx
  int v3; // ecx

  result = Rules_StaticConstraintCheckingEnabled();
  if ( result )
  {
    result = (int)Rules_ConstraintIsUnmatchable(*(char **)(v1 + 16));
    if ( result )
    {
      Rules_ReportConstraintReferenceConflict(*(_DWORD *)(v3 + 4), v2, *(_DWORD *)(v3 + 32));
      return 1;
    }
  }
  return result;
}
// 4DD99E: variable 'v1' is possibly undefined
// 4DD9B2: variable 'v3' is possibly undefined
// 4DD9B9: variable 'v2' is possibly undefined

//----- (004DD9D0) --------------------------------------------------------
signed int  Rules_ReportConstraintReferenceConflict(int a1, int a2, int a3)
{
  int v5; // ecx
  char *v6; // edx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v12; // ecx
  int v13; // ecx

  Rules_PrintErrorID((int)aRulecstr, 1, 1);
  if ( a1 )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aVariable__0, v5);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(a1 + 16), v12);
    v6 = aInCe;
  }
  else
  {
    v6 = aPattern_0;
  }
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)v6, v5);
  Rules_PrintLongInteger(v7, a2);
  if ( v8 )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSlot_9, v8);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(v13 + 16), v13);
  }
  else
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aField_2, 0);
    Rules_PrintLongInteger(v9, a3);
  }
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aHasConstraintC, v10);
}
// 4DD9F8: variable 'v5' is possibly undefined
// 4DDA04: variable 'v7' is possibly undefined
// 4DDA0B: variable 'v8' is possibly undefined
// 4DDA23: variable 'v9' is possibly undefined
// 4DDA32: variable 'v10' is possibly undefined
// 4DDA52: variable 'v12' is possibly undefined
// 4DDA72: variable 'v13' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004DDA90) --------------------------------------------------------
int  Rules_DeriveCEFieldCardinalityConstraint(int a1)
{
  int v2; // ecx
  signed int v3; // ebx
  int v4; // esi
  _DWORD *i; // edx
  int v6; // eax
  _DWORD *v7; // edi
  signed int v8; // ecx
  int *v9; // eax
  __int16 v10; // ax
  int *v11; // edx
  char v12; // bh
  int v13; // edx
  int result; // eax
  char *v15; // edx
  int v16; // edi
  int v17; // edi
  int j; // eax
  int v19; // edi

  v2 = 0;
  v3 = 0;
  v4 = 0;
  if ( (*(_BYTE *)(a1 + 8) & 4) == 0 )
    return 0;
  for ( i = *(_DWORD **)(a1 + 68); i; i = (_DWORD *)i[16] )
  {
    if ( *i == 15 || *i == 17 )
    {
      ++v2;
      ++v3;
    }
    else
    {
      v16 = i[4];
      if ( !v16 )
        goto LABEL_22;
      v17 = *(_DWORD *)(*(_DWORD *)(v16 + 18) + 2);
      if ( v17 != g_Clips_NegativeInfinitySymbol )
        v2 += *(_DWORD *)(v17 + 16);
      for ( j = *(_DWORD *)(i[4] + 22); *(_DWORD *)(j + 10); j = *(_DWORD *)(j + 10) )
        ;
      v19 = *(_DWORD *)(j + 2);
      if ( v19 != g_ClipsPositiveInfinitySymbol )
        v3 += *(_DWORD *)(v19 + 16);
      else
LABEL_22:
        v4 = 1;
    }
  }
  if ( *(_DWORD *)(a1 + 16) )
    v6 = Rules_CloneLHSParseNode(*(int **)(a1 + 16));
  else
    v6 = Rules_CreateLHSParseNode();
  v7 = (_DWORD *)v6;
  AST_Free(*(_DWORD *)(v6 + 18));
  AST_Free(*(_DWORD *)((char *)v7 + 22));
  v9 = Rules_AddIntegerValue(v8);
  *(_DWORD *)((char *)v7 + 18) = AST_NewNode(1, (int)v9);
  if ( v4 )
  {
    v10 = 2;
    v11 = (int *)g_ClipsPositiveInfinitySymbol;
  }
  else
  {
    v11 = Rules_AddIntegerValue(v3);
    v10 = 1;
  }
  *(_DWORD *)((char *)v7 + 22) = AST_NewNode(v10, (int)v11);
  Rules_IntersectConstraints(*(_DWORD *)(a1 + 16), (int)v7);
  if ( (*(_BYTE *)(a1 + 8) & 0x10) != 0 )
    AST_DecrementNodeRefCount(*(_DWORD **)(a1 + 16));
  AST_DecrementNodeRefCount(v7);
  v12 = *(_BYTE *)(a1 + 8);
  *(_DWORD *)(a1 + 16) = v13;
  *(_BYTE *)(a1 + 8) = v12 | 0x10;
  result = Rules_StaticConstraintCheckingEnabled();
  if ( result )
  {
    result = (int)Rules_ConstraintIsUnmatchable(v15);
    if ( result )
      return 1;
  }
  return result;
}
// 4DDAE9: variable 'v8' is possibly undefined
// 4DDB3E: variable 'v13' is possibly undefined
// 4DDBD8: variable 'v15' is possibly undefined
// 54DD60: using guessed type int dword_54DD60;
// 54DD68: using guessed type int dword_54DD68;

//----- (004DDC00) --------------------------------------------------------
signed int  Rules_ComputeConnectedCEConstraintGroup(int a1, int *a2, int a3)
{
  int v3; // ebx
  int v4; // ecx
  _BYTE *v5; // esi
  int v6; // ecx
  _DWORD *v7; // edi
  _DWORD *v8; // ebx
  int v9; // esi
  int v10; // ecx
  _DWORD *v11; // ebx
  _DWORD *v12; // ecx
  __int16 *v14; // esi
  _BYTE *v15; // edi
  int v16; // ecx
  _DWORD *v17; // ebp
  int v21; // [esp+Ch] [ebp-18h]
  int v22; // [esp+10h] [ebp-14h]

  v21 = 0;
  v22 = *(_DWORD *)(a1 + 68);
  if ( !v22 )
    goto LABEL_15;
  do
  {
    v3 = v22;
    v4 = 0;
    do
    {
      if ( (*(_BYTE *)(v3 + 8) & 1) != 0 )
        goto LABEL_8;
      if ( *(_DWORD *)v3 == 94 )
      {
        if ( **(_DWORD **)(v3 + 56) != 10 )
          goto LABEL_8;
        v5 = Rules_ApplyCEKeywordFlags();
        v7 = (_DWORD *)v6;
        Rules_IntersectConstraints(v6, (int)v5);
        AST_DecrementNodeRefCount(v7);
        goto LABEL_7;
      }
      if ( Rules_TagIsConstantType(*(_DWORD *)v3) )
      {
        v14 = (__int16 *)AST_NewNode(*(_DWORD *)v3, *(_DWORD *)(v3 + 4));
        v15 = Rules_BuildLHSNodeFromToken(v14);
        v17 = (_DWORD *)v16;
        Rules_IntersectConstraints(v16, (int)v15);
        AST_DecrementNodeRefCount(v17);
        AST_DecrementNodeRefCount(v15);
        AST_Free((int)v14);
      }
      else if ( *(_DWORD *)(v3 + 16) )
      {
        v5 = (_BYTE *)v4;
        Rules_IntersectConstraints(v4, *(_DWORD *)(v3 + 16));
LABEL_7:
        AST_DecrementNodeRefCount(v5);
      }
LABEL_8:
      v3 = *(_DWORD *)(v3 + 64);
    }
    while ( v3 );
    v8 = (_DWORD *)v4;
    Rules_IntersectConstraints(v4, *(_DWORD *)(a1 + 16));
    v9 = v22;
    AST_DecrementNodeRefCount(v8);
    do
    {
      if ( (*(_BYTE *)(v9 + 8) & 1) != 0 && Rules_TagIsConstantType(*(_DWORD *)v9) )
        Rules_RemoveConstantFromConstraint(*(_DWORD *)v9, *(_DWORD *)(v9 + 4), v10);
      v9 = *(_DWORD *)(v9 + 64);
    }
    while ( v9 );
    v11 = (_DWORD *)v21;
    v21 = Rules_UnionConstraints(v21, v10);
    AST_DecrementNodeRefCount(v11);
    AST_DecrementNodeRefCount(v12);
    v22 = *(_DWORD *)(v22 + 68);
  }
  while ( v22 );
LABEL_15:
  if ( v21 )
  {
    if ( (*(_BYTE *)(a1 + 8) & 0x10) != 0 )
      AST_DecrementNodeRefCount(*(_DWORD **)(a1 + 16));
    *(_DWORD *)(a1 + 16) = v21;
    *(_BYTE *)(a1 + 8) |= 0x10u;
  }
  if ( Rules_CheckAndReportUnmatchableFieldConstraint() )
    return 1;
  if ( !a2 || *(_DWORD *)(a1 + 64) || !Rules_DeriveCEFieldCardinalityConstraint((int)a2) )
    return 0;
  Rules_PrintConstraintViolationMessage((int)aTheGroupOfRest, 0, *(_DWORD *)(a3 + 8) << 19 >> 25, 0, a2[9], a2[8], 5, a2[4], 1);
  return 1;
}
// 4DDC2F: conditional instruction was optimized away because %var_14.4!=0
// 4DDC95: conditional instruction was optimized away because esi.4!=0
// 4DDC58: variable 'v6' is possibly undefined
// 4DDC7F: variable 'v4' is possibly undefined
// 4DDCAF: variable 'v10' is possibly undefined
// 4DDCD5: variable 'v12' is possibly undefined
// 4DDD94: variable 'v16' is possibly undefined

//----- (004DDE10) --------------------------------------------------------
signed int  Rules_PrintVariableBindingConstraintViolation(int a1, int a2, int a3, int a4, int a5, int a6)
{
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // eax
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // edx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v24; // ecx
  int v25; // ecx

  Rules_PrintErrorID((int)aRulecstr, 2, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aPreviousVariab, v8);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(a1 + 16), v9);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCausedTheTypeR, v10);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aForArgument_0, v11);
  Rules_PrintLongInteger(v12, a4);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOfTheExpressio, v13);
  v14 = Rules_CECloneBindingList(a2);
  AST_Free(*(_DWORD *)(v14 + 10));
  *(_DWORD *)(v15 + 10) = 0;
  Rules_PrintFieldExprList((signed int)g_IO_LogicalNameTable_WError[0], (__int16 *)v15);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_50DFD4, v16);
  AST_Free(v17);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v18, v19);
  Rules_PrintLongInteger(v20, a3);
  if ( a5 )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSlot_9, v21);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(a5 + 16), v25);
  }
  else
  {
    v22 = a6;
    if ( a6 > 0 )
    {
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aField_2, a6);
      Rules_PrintLongInteger(v24, v24);
    }
  }
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aToBeViolated_, v22);
}
// 4DDE3D: variable 'v8' is possibly undefined
// 4DDE4D: variable 'v9' is possibly undefined
// 4DDE5C: variable 'v10' is possibly undefined
// 4DDE6B: variable 'v11' is possibly undefined
// 4DDE77: variable 'v12' is possibly undefined
// 4DDE86: variable 'v13' is possibly undefined
// 4DDE9C: variable 'v15' is possibly undefined
// 4DDEB9: variable 'v16' is possibly undefined
// 4DDEC5: variable 'v17' is possibly undefined
// 4DDECF: variable 'v18' is possibly undefined
// 4DDECF: variable 'v19' is possibly undefined
// 4DDEDB: variable 'v20' is possibly undefined
// 4DDF1D: variable 'v24' is possibly undefined
// 4DDEF9: variable 'v22' is possibly undefined
// 4DDF2E: variable 'v21' is possibly undefined
// 4DDF3F: variable 'v25' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004DDF50) --------------------------------------------------------
_DWORD * Rules_MergeConstraintListsByFieldIndex(_DWORD *a1, _DWORD *a2)
{
  _DWORD *v3; // ebx
  _DWORD *v4; // ecx
  _DWORD *v5; // edi
  int v6; // ecx
  int v7; // edx
  int v8; // ecx

  v3 = a2;
  if ( a2 )
  {
    do
    {
      v4 = a1;
      v5 = (_DWORD *)v3[16];
      v3[16] = 0;
      if ( a1 )
      {
        while ( v4[1] != v3[1] )
        {
          v4 = (_DWORD *)v4[16];
          if ( !v4 )
            goto LABEL_5;
        }
        Rules_IntersectConstraints(v4[4], v3[4]);
        AST_DecrementNodeRefCount(*(_DWORD **)(v6 + 16));
        *(_DWORD *)(v8 + 16) = v7;
        AST_FreeNode((int)v3);
      }
LABEL_5:
      if ( !v4 )
      {
        v3[16] = a1;
        a1 = v3;
      }
      v3 = v5;
    }
    while ( v5 );
  }
  return a1;
}
// 4DDF81: variable 'v6' is possibly undefined
// 4DDF8B: variable 'v7' is possibly undefined
// 4DDF8B: variable 'v8' is possibly undefined
// 4DDF95: variable 'v4' is possibly undefined

//----- (004DDFC0) --------------------------------------------------------
signed int  Rules_IntersectConstraintListsByFieldIndex(int a1, int a2)
{
  int v2; // ecx
  signed int v4; // edi
  int v5; // edx
  signed int v6; // ebx
  int v7; // ecx
  int v8; // edx
  int v9; // edx

  v2 = a1;
  v4 = 0;
  if ( a1 )
  {
    do
    {
      v5 = a2;
      if ( a2 )
      {
        while ( *(_DWORD *)(v2 + 4) != *(_DWORD *)(v5 + 4) )
        {
          v5 = *(_DWORD *)(v5 + 64);
          if ( !v5 )
            goto LABEL_5;
        }
        v6 = AST_AllocNode();
        *(_BYTE *)(v6 + 8) |= 0x10u;
        *(_DWORD *)(v6 + 4) = *(_DWORD *)(v7 + 4);
        *(_DWORD *)(v6 + 16) = Rules_UnionConstraints(*(_DWORD *)(v7 + 16), *(_DWORD *)(v8 + 16));
        *(_DWORD *)(v6 + 64) = v4;
        v4 = v6;
      }
LABEL_5:
      *(_DWORD *)(v2 + 64) = 0;
      AST_FreeNode(v2);
      v2 = v9;
    }
    while ( v9 );
  }
  AST_FreeNode(a2);
  return v4;
}
// 4DDFEC: variable 'v7' is possibly undefined
// 4DDFF2: variable 'v8' is possibly undefined
// 4DE00A: variable 'v2' is possibly undefined
// 4DE016: variable 'v9' is possibly undefined

//----- (004DE040) --------------------------------------------------------
_DWORD * Rules_ClonePatternPositionConstraintList(int *a1)
{
  int *v1; // ecx
  _DWORD *i; // edx
  int v3; // esi
  signed int v4; // eax
  int v5; // ecx
  int *v6; // edi
  _DWORD *v7; // ebx
  _DWORD *v8; // edx
  _DWORD *v10; // eax
  _DWORD *v11; // edx

  v1 = a1;
  for ( i = 0; v1; v1 = (int *)v1[17] )
  {
    if ( v1[16] )
    {
      v10 = (_DWORD *)Rules_ClonePatternPositionConstraintList(v1[16]);
      i = Rules_MergeConstraintListsByFieldIndex(v10, v11);
    }
    v3 = *v1;
    if ( *v1 == 15 )
    {
      v4 = AST_AllocNode();
      v6 = *(int **)(v5 + 20);
      v7 = (_DWORD *)v4;
      if ( v6 )
        v3 = *v6;
      *(_DWORD *)v4 = v3;
      *(_DWORD *)(v4 + 4) = *(_DWORD *)(v5 + 4);
      *(_BYTE *)(v4 + 8) |= 0x10u;
      *(_DWORD *)(v4 + 16) = Rules_CloneLHSParseNode(*(int **)(v5 + 16));
      i = Rules_MergeConstraintListsByFieldIndex(v7, v8);
    }
  }
  return i;
}
// 4DE0A1: variable 'v11' is possibly undefined
// 4DE054: variable 'v1' is possibly undefined
// 4DE060: variable 'v5' is possibly undefined
// 4DE084: variable 'v8' is possibly undefined

//----- (004DE0B0) --------------------------------------------------------
signed int  Rules_IntersectConnectedCEConstraints(int a1)
{
  int v1; // ebp
  int v2; // esi
  int v3; // edi
  int v4; // ecx
  _DWORD *v5; // ebx
  _DWORD *v6; // eax
  signed int result; // eax

  v1 = 1;
  v2 = *(_DWORD *)(a1 + 68);
  v3 = 0;
  if ( !v2 )
    return v3;
  do
  {
    while ( 1 )
    {
      v4 = v2;
      v5 = 0;
      do
      {
        if ( *(_DWORD *)v4 == 94 || *(_DWORD *)v4 == 93 )
        {
          v6 = Rules_ClonePatternPositionConstraintList(*(int **)(v4 + 56));
          v5 = Rules_MergeConstraintListsByFieldIndex(v5, v6);
        }
        v4 = *(_DWORD *)(v4 + 64);
      }
      while ( v4 );
      if ( !v1 )
        break;
      v3 = (int)v5;
      v1 = 0;
      v2 = *(_DWORD *)(v2 + 68);
      if ( !v2 )
        return v3;
    }
    result = Rules_IntersectConstraintListsByFieldIndex(v3, (int)v5);
    v3 = result;
    v2 = *(_DWORD *)(v2 + 68);
  }
  while ( v2 );
  return result;
}
// 4DE0CA: conditional instruction was optimized away because esi.4!=0
// 4DE0E6: variable 'v4' is possibly undefined

//----- (004DE130) --------------------------------------------------------
signed int  Rules_CheckRHSActionsAgainstCEConstraints(signed int result, int a2)
{
  int v3; // edi
  int v4; // esi
  int v5; // ecx
  signed int v6; // [esp+0h] [ebp-20h]
  int v7; // [esp+4h] [ebp-1Ch]
  int v8; // [esp+8h] [ebp-18h]

  if ( result )
  {
    v6 = result;
    while ( 2 )
    {
      v3 = 1;
      v4 = *(_DWORD *)(v6 + 6);
      if ( *(_WORD *)v6 == 10 )
      {
        v7 = v6;
        v8 = *(_DWORD *)(v6 + 2);
      }
      else
      {
        v8 = 0;
      }
      while ( v4 )
      {
        if ( Rules_CheckFieldRestrictionAgainstRHSAction(v4, v7, v8, v3, a2) )
          return 1;
        *(_DWORD *)(v4 + 10) = 0;
        ++v3;
        if ( Rules_CheckRHSActionsAgainstCEConstraints(v4, a2) )
          return 1;
        *(_DWORD *)(v4 + 10) = v5;
        v4 = v5;
      }
      v6 = *(_DWORD *)(v6 + 10);
      if ( v6 )
        continue;
      break;
    }
    return 0;
  }
  return result;
}
// 4DE141: conditional instruction was optimized away because eax.4!=0
// 4DE196: variable 'v7' is possibly undefined
// 4DE1B3: variable 'v5' is possibly undefined

//----- (004DE1D0) --------------------------------------------------------
signed int  Rules_CheckFieldRestrictionAgainstRHSAction(int a1, int a2, int a3, int a4, int a5)
{
  int v8; // ebx
  _DWORD *v10; // ecx
  _DWORD *v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // edx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // ebx
  int v22; // ecx
  _DWORD *v23; // ecx
  char *v24; // [esp+0h] [ebp-18h]
  _DWORD *v25; // [esp+4h] [ebp-14h]
  _BYTE *v26; // [esp+8h] [ebp-10h]

  v8 = 0;
  if ( *(_WORD *)a1 != 15 || !a3 )
    return 0;
  Rules_GetArgRestrictionType(a3, a4);
  v26 = Rules_ApplyPatternKeywordFlags();
  v11 = Rules_FindCEByIndex(*(_DWORD *)(a1 + 2), v10);
  if ( v11 )
  {
    if ( *v11 == 16 )
    {
      v12 = Rules_CreateLHSParseNode();
      Rules_UpdateCETypeFlag(4u, v12);
    }
    else if ( v11[4] )
    {
      Rules_CloneLHSParseNode((int *)v11[4]);
    }
    else
    {
      Rules_CreateLHSParseNode();
    }
  }
  v13 = Rules_GetNamedContextValue(*(_DWORD *)(a1 + 2));
  v25 = (_DWORD *)Rules_UnionConstraints(v13, v14);
  v24 = Rules_IntersectConstraints((int)v25, (int)v26);
  if ( Rules_ConstraintIsUnmatchable(v24) )
  {
    if ( Rules_StaticConstraintCheckingEnabled() )
    {
      Rules_PrintErrorID((int)aRulecstr, 3, 1);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aPreviousVariab, v15);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(*(_DWORD *)(a1 + 2) + 16), v16);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCausedTheTypeR, v17);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aForArgument_0, v18);
      Rules_PrintLongInteger(v19, a4);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOfTheExpressio, v20);
      v21 = *(_DWORD *)(a2 + 10);
      *(_DWORD *)(a2 + 10) = 0;
      Rules_PrintFieldExprList((signed int)g_IO_LogicalNameTable_WError[0], (__int16 *)a2);
      *(_DWORD *)(a2 + 10) = v21;
      v8 = 1;
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFoundInTheRule, v22);
    }
  }
  AST_DecrementNodeRefCount(v26);
  AST_DecrementNodeRefCount(v23);
  AST_DecrementNodeRefCount(v25);
  AST_DecrementNodeRefCount(v24);
  return v8;
}
// 4DE212: variable 'v10' is possibly undefined
// 4DE245: variable 'v14' is possibly undefined
// 4DE292: variable 'v15' is possibly undefined
// 4DE2A2: variable 'v16' is possibly undefined
// 4DE2B1: variable 'v17' is possibly undefined
// 4DE2C0: variable 'v18' is possibly undefined
// 4DE2CC: variable 'v19' is possibly undefined
// 4DE2DB: variable 'v20' is possibly undefined
// 4DE308: variable 'v22' is possibly undefined
// 4DE318: variable 'v23' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004DE370) --------------------------------------------------------
_DWORD * Rules_BuildJoinTestExpressionChain(int a1, _DWORD *a2, _DWORD *a3)
{
  _DWORD *v3; // esi
  int v4; // edx
  int v5; // edi
  _DWORD *v6; // ecx
  int v7; // eax
  int v8; // eax
  int v9; // ebx
  __int64 v10; // rax
  int v11; // ebp
  int v12; // ecx
  int v13; // ebp
  _WORD *v14; // eax
  int v15; // edx
  int v16; // ecx
  int v18; // ecx
  int v20[33]; // [esp+4h] [ebp-BCh] BYREF
  int v21; // [esp+88h] [ebp-38h]
  BOOL v22; // [esp+8Ch] [ebp-34h]
  int v23; // [esp+90h] [ebp-30h]
  int i; // [esp+94h] [ebp-2Ch]
  int v25; // [esp+98h] [ebp-28h]
  int v26; // [esp+9Ch] [ebp-24h]
  int v27; // [esp+A0h] [ebp-20h]
  _DWORD *v28; // [esp+A4h] [ebp-1Ch]
  int v29; // [esp+A8h] [ebp-18h]

  v21 = a1;
  v28 = a2;
  Rules_MergeRedundantFieldAccessNodes(a2, a3);
  v3 = 0;
  v29 = v4;
  v26 = v4;
  v5 = v4;
  for ( i = 0; v28; ++v26 )
  {
    if ( !v28[17] )
      i = 1;
    v6 = v28;
    v7 = v5;
    while ( v5 < v6[11] )
    {
      ++v7;
      ++v5;
      v20[v7 - 1] = (int)v3;
    }
    v8 = v6[6];
    v23 = *(_DWORD *)(v8 + 8);
    v9 = v21;
    v10 = ((__int64 (*)(void))*(_DWORD *)(v8 + 24))();
    v11 = v10;
    v22 = v26 == v9;
    if ( HIDWORD(v10) == 1 )
      LODWORD(v10) = *(_DWORD *)(v10 + 8);
    else
      LODWORD(v10) = v3[5];
    v25 = v28[12];
    if ( v29 == 1
      && Rules_FindExistingJoinTestNode((_DWORD *)v10, v11, v28[2] & 1, SHIDWORD(v10), v22, (__int16 *)v28[13], v25, v5, i, (int)&v20[1]) )
    {
      if ( Rules_GetWatchItemState((int)aCompilations) == 1 && Rules_GetLoadInProgress() )
        Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aJ, v12);
      v3 = (_DWORD *)v12;
    }
    else
    {
      v20[0] = v28[2] & 1;
      v29 = 0;
      v14 = (_WORD *)Rules_InternJoinTestNode(v28[13], v3, 0, v11, v20[0]);
      v15 = v23 & 7;
      *v14 &= 0xFE3Fu;
      v3 = v14;
      *(_DWORD *)v14 |= v15 << 6;
    }
    v13 = 4 * v5;
    v27 = 4 * v25;
    while ( v13 > v27 )
    {
      v13 -= 4;
      --v5;
      if ( !v3[5] )
      {
        v29 = 0;
        goto LABEL_19;
      }
      if ( v29 )
      {
        if ( Rules_GetWatchItemState((int)aCompilations) == 1 && Rules_GetLoadInProgress() )
        {
          Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aJ, v16);
          v3 = (_DWORD *)v3[5];
        }
        else
        {
          v3 = (_DWORD *)v3[5];
        }
      }
      else
      {
LABEL_19:
        v3 = (_DWORD *)Rules_InternJoinTestNode(0, (_DWORD *)v20[v13 / 4u], 1, (int)v3, 0);
      }
    }
    v28 = (_DWORD *)v28[17];
  }
  if ( Rules_GetWatchItemState((int)aCompilations) != 1 || !Rules_GetLoadInProgress() )
    return v3;
  Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)asc_50E03C, v18);
  return v3;
}
// 4DE3A3: variable 'v4' is possibly undefined
// 4DE4C8: variable 'v12' is possibly undefined
// 4DE5AF: variable 'v16' is possibly undefined
// 4DE616: variable 'v18' is possibly undefined
// 51A61C: using guessed type char *off_51A61C[3];

//----- (004DE630) --------------------------------------------------------
_DWORD * Rules_MergeRedundantFieldAccessNodes(_DWORD *result, _DWORD *a2)
{
  _DWORD *i; // ebx
  int v3; // ecx
  _DWORD *v4; // ecx
  int v5; // edx
  int v6; // edx

  for ( i = result; i; i = (_DWORD *)i[17] )
  {
    if ( (i[2] & 1) != 0 )
    {
      v3 = 0;
    }
    else
    {
      a2 = i;
      v3 = i[17];
    }
    while ( v3 )
    {
      result = *(_DWORD **)(v3 + 44);
      if ( result != (_DWORD *)i[11] || (*(_DWORD *)(v3 + 8) & 1) != 0 )
      {
        a2 = (_DWORD *)v3;
        v3 = *(_DWORD *)(v3 + 68);
      }
      else
      {
        if ( *(_DWORD *)v3 == 80 )
          break;
        if ( *(_DWORD *)v3 == 84 )
        {
          i[13] = AST_MergeFieldAccessNodes((_DWORD *)i[13], *(_DWORD **)(v3 + 52));
          v4[13] = 0;
          v5 = v4[17];
          v4[17] = 0;
          a2[17] = v5;
          a2[12] = v4[12];
          result = (_DWORD *)AST_FreeNode((int)v4);
          v3 = v6;
        }
        else
        {
          Rules_ReportSystemError(v3, 1);
          result = (_DWORD *)IO_RunRouterExitCallbacks();
        }
      }
    }
  }
  return result;
}
// 4DE64C: variable 'v3' is possibly undefined
// 4DE691: variable 'v4' is possibly undefined
// 4DE6AA: variable 'v6' is possibly undefined

//----- (004DE6D0) --------------------------------------------------------
_DWORD * Rules_FindExistingJoinTestNode(
        _DWORD *a1,
        int a2,
        int a3,
        int a4,
        int a5,
        __int16 *a6,
        int a7,
        int a8,
        int a9,
        int a10)
{
  _DWORD *v10; // esi

  v10 = a1;
  if ( !a1 )
    return 0;
  do
  {
    while ( 1 )
    {
      if ( a2 == v10[4] && Rules_JoinTestNodeMatches((int)v10, a4, a5, a3, a6, a7, a8, a9, a10) )
        return v10;
      if ( !a4 )
        break;
      v10 = (_DWORD *)v10[8];
      if ( !v10 )
        return 0;
    }
    v10 = (_DWORD *)v10[7];
  }
  while ( v10 );
  return 0;
}

//----- (004DE750) --------------------------------------------------------
BOOL  Rules_JoinTestNodeMatches(
        int a1,
        int a2,
        int a3,
        int a4,
        __int16 *a5,
        int a6,
        int a7,
        int a8,
        int a9)
{
  int v9; // esi
  int v10; // ecx
  int v11; // eax
  int v13; // eax

  v9 = a1;
  if ( a2 != (*(_DWORD *)a1 & 1)
    || *(_DWORD *)a1 << 28 >> 31 != a4
    || a3 == 1 && (*(_BYTE *)a1 & 2) == 0 && *(_DWORD *)(a1 + 8)
    || AST_NodeListsEqual(*(__int16 **)(a1 + 12), a5) != 1 )
  {
    return 0;
  }
  v11 = a9 + 4 * v10;
  while ( a6 < v10 )
  {
    v9 = *(_DWORD *)(v9 + 20);
    if ( !v9 || (*(_BYTE *)v9 & 4) == 0 || *(_DWORD *)(v11 - 8) != *(_DWORD *)(v9 + 24) )
      return 0;
    v11 -= 4;
    --v10;
  }
  if ( a8 && (*(_DWORD *)(v9 + 36) || *(_DWORD *)(v9 + 8)) )
    return 0;
  return a8 || (v13 = *(_DWORD *)(v9 + 20)) == 0 || (*(_BYTE *)v13 & 4) == 0 || v9 != *(_DWORD *)(v13 + 16);
}
// 4DE79F: variable 'v10' is possibly undefined

//----- (004DE810) --------------------------------------------------------
int  Rules_InternJoinTestNode(int a1, _DWORD *a2, int a3, int a4, char a5)
{
  _DWORD *v8; // ecx
  signed int v9; // edx
  int v10; // edx
  int v11; // ecx
  int v12; // eax
  int v13; // edx
  __int16 v14; // si
  int v16; // ecx
  char v17; // al
  int v18; // [esp+0h] [ebp-10h]

  if ( Rules_GetWatchItemState((int)aCompilations) == 1 && Rules_GetLoadInProgress() )
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aJ_0, v16);
  v8 = *(_DWORD **)(g_ClipsMemoryTable + 160);
  if ( v8 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 160);
    *(_DWORD *)(g_ClipsMemoryTable + 160) = *v8;
    v9 = g_ClipsMemFreeListTemp;
  }
  else
  {
    v9 = Mem_HeapAllocWithRetry(40);
  }
  *(_BYTE *)v9 &= ~4u;
  *(_DWORD *)v9 |= 4 * (a3 & 1);
  *(_BYTE *)v9 &= ~8u;
  *(_DWORD *)(v9 + 8) = 0;
  *(_DWORD *)(v9 + 20) = 0;
  *(_DWORD *)v9 |= 8 * (a5 & 1);
  v18 = Rules_GetIncrementalReset() & 1;
  *(_BYTE *)v10 &= ~0x10u;
  *(_DWORD *)v10 |= 16 * v18;
  *(_BYTE *)v10 &= ~2u;
  *(_DWORD *)(v10 + 36) = 0;
  v12 = AST_AddHashedNodeChain(a1, v10, v11);
  *(_DWORD *)(v13 + 12) = v12;
  *(_DWORD *)(v13 + 24) = a2;
  if ( a2 )
  {
    *(_BYTE *)v13 &= ~1u;
    v17 = (*a2 << 16 >> 25) + 1;
    *(_BYTE *)(v13 + 1) &= 1u;
    *(_DWORD *)v13 |= (v17 & 0x7F) << 9;
    *(_DWORD *)(v13 + 28) = a2[5];
    a2[5] = v13;
  }
  else
  {
    v14 = *(_WORD *)v13 & 0x1FE;
    *(_DWORD *)(v13 + 28) = 0;
    *(_WORD *)v13 = v14;
    *(_WORD *)v13 = v14 | 0x201;
  }
  *(_DWORD *)(v13 + 16) = a4;
  if ( a3 )
  {
    *(_DWORD *)(v13 + 32) = 0;
    *(_DWORD *)(a4 + 20) = v13;
  }
  else
  {
    *(_DWORD *)(v13 + 32) = *(_DWORD *)(a4 + 8);
    *(_DWORD *)(a4 + 8) = v13;
  }
  return v13;
}
// 4DE898: variable 'v10' is possibly undefined
// 4DE8AF: variable 'v11' is possibly undefined
// 4DE8B4: variable 'v13' is possibly undefined
// 4DE911: variable 'v16' is possibly undefined
// 51A61C: using guessed type char *off_51A61C[3];
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004DE9B0) --------------------------------------------------------
int ** Defgeneric_InitializeFromRestrictionString(int a1, int a2)
{
  int **result; // eax
  _DWORD *v3; // ecx
  __int16 v4; // [esp+0h] [ebp-14h] BYREF
  int **v5; // [esp+2h] [ebp-12h]
  int v6; // [esp+6h] [ebp-Eh]
  int v7; // [esp+Ah] [ebp-Ah]
  int v8; // [esp+10h] [ebp-4h]

  v8 = a2;
  result = Rules_MakeSymbol(*(_BYTE **)(*(_DWORD *)a1 + 16));
  if ( result )
  {
    v4 = 10;
    v5 = result;
    v7 = 0;
    v6 = 0;
    return (int **)Method_ParseWildcardRestrictionString(v3, *(char **)((char *)result + 17), (int)v3, &v4);
  }
  return result;
}
// 4DE9E9: variable 'v3' is possibly undefined

//----- (004DEA00) --------------------------------------------------------
int  Method_ParseWildcardRestrictionString(_DWORD *a1, char *a2, int a3, _DWORD *a4)
{
  _DWORD *v4; // edx
  signed int v5; // eax
  int v6; // esi
  _DWORD *v7; // ecx
  _DWORD *v8; // ecx
  int v9; // ecx
  _DWORD *v10; // eax
  __int16 *v11; // eax
  unsigned int *v12; // eax
  int v14; // ecx
  int v15; // esi
  int v16; // edi
  char *v17; // ebp
  char *v18; // eax
  char v19; // al
  _DWORD *v20; // ecx
  _DWORD *v21; // ebx
  signed int v22; // eax
  int v23; // ebp
  char *v24; // edi
  int v25; // ebx
  _DWORD *v26; // edi
  int **Symbol; // eax
  signed int v28; // eax
  int v29; // ecx
  int **v30; // eax
  signed int v31; // eax
  int v32; // ecx
  int v33; // ebp
  signed int v34; // eax
  int v35; // ecx
  int *v36; // eax
  signed int v37; // eax
  int v38; // ecx
  _DWORD *v39; // ebp
  signed int v40; // eax
  int v41; // edi
  __int16 *v42; // eax
  unsigned int *v43; // eax
  int v44; // eax
  __int16 *v45; // eax
  unsigned int *v46; // eax
  _DWORD *v47; // ecx
  _DWORD *v48; // ebx
  signed int v49; // eax
  char v50; // dh
  __int16 *v51; // eax
  unsigned int *v52; // eax
  signed int v53; // [esp+0h] [ebp-44h]
  int v54; // [esp+4h] [ebp-40h] BYREF
  int v55; // [esp+8h] [ebp-3Ch]
  _DWORD *v56; // [esp+Ch] [ebp-38h]
  char *v57; // [esp+10h] [ebp-34h]
  int v58; // [esp+14h] [ebp-30h]
  int v59; // [esp+18h] [ebp-2Ch]
  int v60; // [esp+1Ch] [ebp-28h]
  _DWORD *v61; // [esp+20h] [ebp-24h]
  int v62; // [esp+24h] [ebp-20h]
  signed int v63; // [esp+28h] [ebp-1Ch]
  int v64; // [esp+2Ch] [ebp-18h]
  char v65; // [esp+30h] [ebp-14h]
  char v66; // [esp+31h] [ebp-13h]
  char v67; // [esp+34h] [ebp-10h]

  v61 = a1;
  v57 = a2;
  v56 = a4;
  if ( a2 )
  {
    v66 = 0;
    if ( *a2 == 42 )
    {
      v14 = 0;
      v58 = 0;
    }
    else
    {
      v65 = *v57;
      v58 = unknown_libname_2(a3);
    }
    if ( v57[1] == 42 )
    {
      v59 = -1;
    }
    else
    {
      v65 = v57[1];
      v59 = unknown_libname_2(v14);
    }
    if ( v57[2] )
    {
      v67 = v57[2];
      v64 = 3;
    }
    else
    {
      v67 = 117;
      v64 = 2;
    }
    v15 = 0;
    v16 = 0;
    v63 = 0;
    if ( v58 > 0 )
    {
      v17 = &v57[v64];
      do
      {
        if ( *v17 )
        {
          v18 = &v57[v64];
          ++v17;
          ++v64;
          v19 = *v18;
        }
        else
        {
          v19 = v67;
        }
        v65 = v19;
        v20 = Method_BuildTypeRestrictionRecordFromFlags();
        v21 = *(_DWORD **)(g_ClipsMemoryTable + 56);
        if ( v21 )
        {
          g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 56);
          *(_DWORD *)(g_ClipsMemoryTable + 56) = *v21;
          v22 = g_ClipsMemFreeListTemp;
        }
        else
        {
          v22 = Mem_HeapAllocWithRetry((_DWORD *)0xE);
        }
        *(_DWORD *)(v22 + 10) = 0;
        *(_DWORD *)(v22 + 6) = v20;
        if ( v15 )
          *(_DWORD *)(v63 + 10) = v22;
        else
          v15 = v22;
        ++v16;
        v63 = v22;
      }
      while ( v16 < v58 );
    }
    v53 = v63;
    v23 = v58;
    v62 = v58 + 1;
    v55 = 1;
    v60 = 0;
    v24 = &v57[v64];
    if ( v57[v64] )
    {
      while ( v24[1] || v62 != v59 )
      {
        v47 = Method_BuildTypeRestrictionRecordFromFlags();
        v48 = *(_DWORD **)(g_ClipsMemoryTable + 56);
        if ( v48 )
        {
          g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 56);
          *(_DWORD *)(g_ClipsMemoryTable + 56) = *v48;
          v49 = g_ClipsMemFreeListTemp;
        }
        else
        {
          v49 = Mem_HeapAllocWithRetry((_DWORD *)0xE);
        }
        *(_DWORD *)(v49 + 10) = 0;
        *(_DWORD *)(v49 + 6) = v47;
        if ( v15 )
          *(_DWORD *)(v63 + 10) = v49;
        else
          v15 = v49;
        v63 = v49;
        ++v23;
        ++v24;
        ++v62;
        ++v60;
        v50 = *v24;
        ++v64;
        if ( v50 || v23 == v59 )
        {
          Method_FindInsertionIndex((int)v61, v15, 0, v23, (unsigned int *)&v54);
          v51 = (__int16 *)AST_PackNodeChain(v56);
          v52 = Defgeneric_AddMethod(v61, 0, 0, v54, v15, v23, 0, 0, v51, 0, 1);
          *((_BYTE *)v52 + 24) |= 1u;
          if ( !*v24 )
            goto LABEL_28;
        }
        else if ( !*v24 )
        {
          goto LABEL_28;
        }
      }
      v67 = *v24;
    }
LABEL_28:
    if ( v60 + v58 != v59 )
    {
      if ( !v60 )
        v55 = 0;
      v25 = v59;
      v26 = Method_BuildTypeRestrictionRecordFromFlags();
      if ( v25 != -1 )
      {
        Symbol = Rules_MakeSymbol(asc_50E04C);
        v28 = AST_NewNode(10, (int)Symbol);
        *(_DWORD *)(v29 + 4) = v28;
        v30 = Rules_MakeSymbol(aLength_1);
        v31 = AST_NewNode(10, (int)v30);
        v33 = v60;
        *(_DWORD *)(*(_DWORD *)(v32 + 4) + 6) = v31;
        v34 = AST_NewProcParamNode(v33 + v58 + 1);
        *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v35 + 4) + 6) + 6) = v34;
        v36 = Rules_AddIntegerValue(v25 - v58 - v33);
        v37 = AST_NewNode(1, (int)v36);
        *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v38 + 4) + 6) + 10) = v37;
      }
      v39 = *(_DWORD **)(g_ClipsMemoryTable + 56);
      if ( v39 )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 56);
        *(_DWORD *)(g_ClipsMemoryTable + 56) = *v39;
        v40 = g_ClipsMemFreeListTemp;
      }
      else
      {
        v40 = Mem_HeapAllocWithRetry((_DWORD *)0xE);
      }
      *(_DWORD *)(v40 + 10) = 0;
      *(_DWORD *)(v40 + 6) = v26;
      if ( v15 )
        *(_DWORD *)(v63 + 10) = v40;
      else
        v15 = v40;
      v41 = v60 + v58 + 1;
      Method_FindInsertionIndex((int)v61, v15, g_ClipsTrueSymbol, v41, (unsigned int *)&v54);
      v42 = (__int16 *)AST_PackNodeChain(v56);
      v43 = Defgeneric_AddMethod(v61, 0, 0, v54, v15, v41, 0, g_ClipsTrueSymbol, v42, 0, 0);
      *((_BYTE *)v43 + 24) |= 1u;
    }
    if ( v55 )
    {
      if ( v53 )
      {
        v44 = *(_DWORD *)(v53 + 10);
        *(_DWORD *)(v53 + 10) = 0;
        Method_FreeRestrictionChain(v44);
      }
      Method_FindInsertionIndex((int)v61, v15, 0, v58, (unsigned int *)&v54);
      v45 = (__int16 *)AST_PackNodeChain(v56);
      v46 = Defgeneric_AddMethod(v61, 0, 0, v54, v15, v58, 0, 0, v45, 0, 1);
      *((_BYTE *)v46 + 24) |= 1u;
    }
    return Method_FreeRestrictionChain(v15);
  }
  else
  {
    v4 = *(_DWORD **)(g_ClipsMemoryTable + 56);
    if ( v4 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 56);
      *(_DWORD *)(g_ClipsMemoryTable + 56) = *v4;
      v5 = g_ClipsMemFreeListTemp;
    }
    else
    {
      v5 = Mem_HeapAllocWithRetry((_DWORD *)0xE);
    }
    v6 = v5;
    v7 = *(_DWORD **)(g_ClipsMemoryTable + 48);
    if ( v7 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
      *(_DWORD *)(g_ClipsMemoryTable + 48) = *v7;
      v8 = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      v8 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0xC);
    }
    Method_PackRestrictionTypes(v8, 0);
    *(_DWORD *)(v9 + 4) = 0;
    *(_DWORD *)(v6 + 10) = 0;
    v10 = v56;
    *(_DWORD *)(v6 + 6) = v9;
    v11 = (__int16 *)AST_PackNodeChain(v10);
    v12 = Defgeneric_AddMethod(v61, 0, 0, 0, v6, 1, 0, g_ClipsTrueSymbol, v11, 0, 0);
    *((_BYTE *)v12 + 24) |= 1u;
    return Method_FreeRestrictionChain(v6);
  }
}
// 4DEA55: variable 'v9' is possibly undefined
// 4DEB7C: variable 'v20' is possibly undefined
// 4DEC37: variable 'v29' is possibly undefined
// 4DEC50: variable 'v32' is possibly undefined
// 4DEC66: variable 'v35' is possibly undefined
// 4DEC8A: variable 'v38' is possibly undefined
// 4DEDA6: variable 'v14' is possibly undefined
// 4DEE20: variable 'v47' is possibly undefined
// 48523F: using guessed type int __thiscall unknown_libname_2(_DWORD);
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD64: using guessed type int dword_54DD64;

//----- (004DEF00) --------------------------------------------------------
_DWORD *Method_BuildTypeRestrictionRecordFromFlags()
{
  _DWORD *v0; // edx
  signed int v1; // esi
  signed int v2; // eax
  _DWORD *v3; // ebp
  char *v4; // eax
  char v5; // dl
  char *v6; // edi
  char *v7; // ecx
  int v8; // ebx
  char *v9; // ecx
  int v10; // ebx
  int v11; // eax
  char *v12; // ecx
  int v13; // ebx
  int v14; // eax
  char *v15; // ecx
  int v16; // ebx
  int v17; // eax

  v0 = *(_DWORD **)(g_ClipsMemoryTable + 48);
  v1 = 0;
  if ( v0 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
    *(_DWORD *)(g_ClipsMemoryTable + 48) = *v0;
    v2 = g_ClipsMemFreeListTemp;
  }
  else
  {
    v2 = Mem_HeapAllocWithRetry((_DWORD *)0xC);
  }
  v3 = (_DWORD *)v2;
  *(_DWORD *)(v2 + 4) = 0;
  v4 = Rules_ApplyPatternKeywordFlags();
  v5 = *v4;
  v6 = v4;
  if ( (*v4 & 1) != 0 )
    goto LABEL_23;
  if ( (v5 & 2) != 0 && (v5 & 4) != 0 )
  {
    v7 = aLexeme;
    v8 = -1;
  }
  else if ( (*v4 & 2) != 0 )
  {
    v8 = 2;
    v7 = 0;
  }
  else
  {
    if ( (*v4 & 4) == 0 )
      goto LABEL_8;
    v8 = 3;
    v7 = 0;
  }
  v1 = Method_AddTypeRestrictionNode(0, v7, v8);
LABEL_8:
  if ( (*v6 & 8) != 0 && (*v6 & 0x10) != 0 )
  {
    v9 = aNumber_0;
    v10 = -1;
    v11 = v1;
  }
  else if ( (*v6 & 0x10) != 0 )
  {
    v10 = 1;
    v11 = v1;
    v9 = 0;
  }
  else
  {
    if ( (*v6 & 8) == 0 )
      goto LABEL_12;
    v11 = v1;
    v9 = 0;
    v10 = 0;
  }
  v1 = Method_AddTypeRestrictionNode(v11, v9, v10);
LABEL_12:
  if ( (*v6 & 0x20) != 0 && (*v6 & 0x40) != 0 )
  {
    v12 = aInstance_0;
    v13 = -1;
    v14 = v1;
  }
  else if ( (*v6 & 0x20) != 0 )
  {
    v13 = 8;
    v14 = v1;
    v12 = 0;
  }
  else
  {
    if ( (*v6 & 0x40) == 0 )
      goto LABEL_16;
    v13 = 7;
    v14 = v1;
    v12 = 0;
  }
  v1 = Method_AddTypeRestrictionNode(v14, v12, v13);
LABEL_16:
  if ( *v6 < 0 && (*v6 & 0x40) != 0 && (v6[1] & 1) != 0 )
  {
    v15 = aAddress;
    v16 = -1;
    v17 = v1;
  }
  else
  {
    if ( *v6 < 0 )
      v1 = Method_AddTypeRestrictionNode(v1, 0, 5);
    if ( (*v6 & 0x40) != 0 && (*v6 & 0x20) == 0 )
      v1 = Method_AddTypeRestrictionNode(v1, 0, 7);
    if ( (v6[1] & 1) == 0 )
      goto LABEL_21;
    v16 = 6;
    v17 = v1;
    v15 = 0;
  }
  v1 = Method_AddTypeRestrictionNode(v17, v15, v16);
LABEL_21:
  if ( v6[1] < 0 )
    v1 = Method_AddTypeRestrictionNode(v1, 0, 4);
LABEL_23:
  AST_DecrementNodeRefCount(v6);
  Method_PackRestrictionTypes(v3, v1);
  return v3;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004DF120) --------------------------------------------------------
signed int  Method_AddTypeRestrictionNode(int a1, _BYTE *a2, int a3)
{
  signed int result; // eax
  int *v5; // eax

  if ( a3 == -1 )
  {
    v5 = Class_LookupByQualifiedName(a2);
    result = AST_NewNode(0, (int)v5);
  }
  else
  {
    result = AST_NewNode(0, g_ClipsPrimitiveTypeClassMap[a3]);
  }
  *(_DWORD *)(result + 10) = a1;
  return result;
}
// 51AD7C: using guessed type int dword_51AD7C[];

//----- (004DF160) --------------------------------------------------------
signed int  MessageHandler_ParseDefinition(int a1)
{
  int v2; // edx
  int v3; // eax
  int *v5; // eax
  int v6; // edx
  int v7; // edx
  int v8; // ecx
  int v9; // edx
  _DWORD *v10; // ebp
  _DWORD *v11; // esi
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  char *v17; // edx
  signed int v18; // eax
  int v19; // edx
  int v20; // ebp
  int v21; // ecx
  int v22; // ecx
  int v23; // eax
  int v24; // ecx
  int v25; // ecx
  int v26; // ecx
  int v27; // ecx
  int v28; // ecx
  int v29; // ecx
  __int16 *v30; // eax
  int v31; // edx
  int v32; // [esp+0h] [ebp-40h] BYREF
  int v33; // [esp+4h] [ebp-3Ch] BYREF
  int v34; // [esp+8h] [ebp-38h] BYREF
  int v35; // [esp+Ch] [ebp-34h] BYREF
  int v36; // [esp+10h] [ebp-30h] BYREF
  __int16 *v37; // [esp+14h] [ebp-2Ch]
  int v38; // [esp+18h] [ebp-28h]
  int v39; // [esp+1Ch] [ebp-24h]
  int *v40; // [esp+20h] [ebp-20h]
  int v41; // [esp+24h] [ebp-1Ch]

  Rules_SetPPBufferStatus(1);
  Rules_FlushPPBuffer();
  Rules_SetIndentDepth(3);
  v41 = v2;
  IO_OutWriteToken(aDefmessageHa_1);
  if ( Rules_IsBloaded() )
  {
    Rules_ReportCannotLoadWithBload();
    return 1;
  }
  v3 = Rules_GetConstructNameAndComment(a1, (int)&g_ParserCurrentTokenType, 0, aDefmessageHa_2, 0, asc_50E0A8, 1, 0, 1);
  if ( !v3 )
    return 1;
  v5 = Class_LookupByQualifiedName(*(_BYTE **)(v3 + 16));
  v40 = v5;
  if ( !v5 )
  {
    Rules_PrintErrorID((int)aMsgpsr, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAClassMustBeDe, v21);
    return 1;
  }
  if ( v5 == (int *)g_Class_InstanceName || v5 == (int *)g_Class_InstanceAddress || v5 == **(int ***)(g_Class_InstanceName + 36) )
  {
    Rules_PrintErrorID((int)aMsgpsr, 8, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aMessageHandl_1, v22);
    v23 = Rules_GetConstructNameString((int)v40);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], v23, v24);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__13, v25);
    return 1;
  }
  if ( MessageHandler_AnyHandlerBusy((int)v5) )
  {
    Rules_PrintErrorID((int)aMsgpsr, 2, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotReDefine, v26);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOtherMessageHa, v27);
    return 1;
  }
  if ( g_ParserCurrentTokenType != 2 )
    goto LABEL_29;
  IO_OutNewline();
  IO_OutNewline();
  IO_OutWriteToken(asc_50E190);
  IO_OutWriteToken((char *)g_ClipsScanTokenPrintForm);
  IO_OutWriteToken(asc_50E190);
  v39 = g_ClipsParserTokenValue;
  Parser_NextToken(a1, (int)&g_ParserCurrentTokenType);
  if ( g_ParserCurrentTokenType == 100 )
    goto LABEL_17;
  IO_OutWriteToken(asc_50E190);
  if ( g_ParserCurrentTokenType != 3 )
  {
    if ( g_ParserCurrentTokenType == 2 )
    {
      v41 = MessageHandler_TypeIndexFromKeyword((int)aDefmessageHa_2);
      if ( v41 == 4 )
        return 1;
      Parser_NextToken(a1, (int)&g_ParserCurrentTokenType);
      if ( g_ParserCurrentTokenType != 3 )
        goto LABEL_17;
      goto LABEL_16;
    }
LABEL_29:
    Parser_ReportSyntaxError();
    return 1;
  }
LABEL_16:
  IO_OutWriteToken(asc_50E190);
  Parser_NextToken(a1, v6);
LABEL_17:
  IO_OutNewline();
  IO_OutNewline();
  AST_Append(v8, v7);
  IO_OutWriteToken((char *)g_ClipsScanTokenPrintForm);
  v10 = Class_FindMessageHandler(v40, v9, v41);
  v11 = v10;
  if ( Rules_GetLoadInProgress() && Rules_GetWatchCompilations() )
  {
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aHandler, v12);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], *(_DWORD *)(v39 + 16), v13);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)asc_50E190, v14);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)g_MessageHandlerTypeNames[v41], v15);
    if ( v10 )
      v17 = aRedefined__0;
    else
      v17 = aDefined__0;
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)v17, v16);
  }
  if ( v10 && (*v10 & 1) != 0 )
  {
    Rules_PrintErrorID((int)aMsgpsr, 3, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSystemMessageH, v28);
    return 1;
  }
  else
  {
    v18 = AST_NewNode(2, g_MessageHandler_SelfSymbol);
    v20 = Parser_ParseProcParameters(a1, &g_ParserCurrentTokenType, &v32, v18, &v33, &v34, &v35, (int (*)(void))MessageHandler_CheckParamNotSelfReference);
    v38 = v20;
    if ( v35 )
    {
      return 1;
    }
    else
    {
      AST_Append((int)v40, v19);
      g_ClipsParseReturnContext = 1;
      v37 = (__int16 *)Parser_ParseProcActions(
                         (int)aMessageHandl_2,
                         a1,
                         v20,
                         v32,
                         (int (*)(void))MessageHandler_ResolveSelfSlotGetRef,
                         (int (*)(void))MessageHandler_ResolveSelfSlotBindRef,
                         &v36,
                         v29);
      if ( v37 )
      {
        if ( g_ParserCurrentTokenType == 101 )
        {
          IO_OutNewline();
          IO_OutNewline();
          IO_OutWriteToken((char *)g_ClipsScanTokenPrintForm);
          IO_OutWriteToken(asc_50E1FC);
          if ( v11 )
          {
            AST_DeinstallNodeChain((__int16 *)v11[7]);
            AST_FreePackedNodeChain(v11[7]);
            if ( v11[8] )
              Mem_SmallBlockFree((_DWORD *)v11[8], strlen((const char *)v11[8]) + 1);
          }
          else
          {
            v11 = Class_InsertMessageHandlerRecord(v40, v39, v41);
            ++*(_DWORD *)(v11[2] + 4);
          }
          AST_Free(v38);
          v11[4] = v33;
          v11[5] = v34;
          v11[6] = v36;
          v30 = v37;
          v11[7] = v37;
          AST_InstallNodeChain(v30);
          if ( Mem_GetAllocFlag() )
            v11[8] = 0;
          else
            v11[8] = Rules_CopyPPBuffer();
          return 0;
        }
        else
        {
          Parser_ReportSyntaxError();
          AST_Free(v20);
          AST_FreePackedNodeChain(v31);
          return 1;
        }
      }
      else
      {
        AST_Free(v20);
        return 1;
      }
    }
  }
}
// 4DF18E: variable 'v2' is possibly undefined
// 4DF2DB: variable 'v6' is possibly undefined
// 4DF2EA: variable 'v8' is possibly undefined
// 4DF2EA: variable 'v7' is possibly undefined
// 4DF305: variable 'v9' is possibly undefined
// 4DF32A: variable 'v12' is possibly undefined
// 4DF33B: variable 'v13' is possibly undefined
// 4DF34A: variable 'v14' is possibly undefined
// 4DF35F: variable 'v15' is possibly undefined
// 4DF376: variable 'v16' is possibly undefined
// 4DF3FB: variable 'v21' is possibly undefined
// 4DF42A: variable 'v22' is possibly undefined
// 4DF442: variable 'v24' is possibly undefined
// 4DF451: variable 'v25' is possibly undefined
// 4DF480: variable 'v26' is possibly undefined
// 4DF48F: variable 'v27' is possibly undefined
// 4DF4E1: variable 'v28' is possibly undefined
// 4DF4F9: variable 'v19' is possibly undefined
// 4DF52C: variable 'v29' is possibly undefined
// 4DF610: variable 'v31' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A61C: using guessed type char *off_51A61C[3];
// 51AD3C: using guessed type char *off_51AD3C[4];
// 51AD98: using guessed type int dword_51AD98;
// 51AD9C: using guessed type int dword_51AD9C;
// 51C708: using guessed type int dword_51C708;
// 54E87C: using guessed type int dword_54E87C;
// 54E8FC: using guessed type int dword_54E8FC;
// 54E900: using guessed type int dword_54E900;
// 54E904: using guessed type int dword_54E904;

//----- (004DF660) --------------------------------------------------------
signed int  Class_GeneratePublicSlotHandlers(signed int result)
{
  char v1; // dl
  unsigned int v2; // edi
  int v3; // edx
  int v4; // ecx
  int v5; // edx
  int v6; // ecx
  const char *v7; // edx
  const char *v8; // eax
  const char *v9; // edx
  int v10; // ecx
  int v11; // edx
  _DWORD *v12; // ecx
  int v13; // [esp+0h] [ebp-14h]
  const char *v14; // [esp+8h] [ebp-Ch]
  const char *v15; // [esp+Ch] [ebp-8h]
  _BYTE *v16; // [esp+10h] [ebp-4h]

  v16 = (_BYTE *)result;
  v1 = *(_BYTE *)(result + 1);
  if ( (v1 & 8) != 0 || (v1 & 0x10) != 0 )
  {
    v14 = *(const char **)(**(_DWORD **)(result + 4) + 16);
    v15 = *(const char **)(*(_DWORD *)(*(_DWORD *)(result + 8) + 12) + 16);
    v2 = strlen(v14) + 2 * strlen(v15) + 80;
    Mem_SmallBlockAlloc(v2);
    v13 = Rules_GetLoadInProgress();
    Rules_SetLoadInProgress(0);
    unknown_libname_5(v4, v3);
    if ( (v16[1] & 8) != 0 )
    {
      sprintf_(v5, "%s get-%s () ?self:%s)", v14, v15, v15);
      if ( IO_OpenStringSource((int)aDefaultPublicH, v7, 0) )
      {
        MessageHandler_ParseDefinition((int)aDefaultPublicH);
        Rules_DestroyPPBuffer();
        IO_CloseStringRouter((int)aDefaultPublicH);
      }
    }
    if ( (v16[1] & 0x10) != 0 )
    {
      if ( (*v16 & 2) != 0 )
        v8 = aAccessorSetterMultifieldParamPrefix;
      else
        v8 = aAccessorSetterSinglefieldParamPrefix;
      sprintf_(v6, "%s put-%s (%svalue) (bind ?self:%s ?value))", v14, v15, v8, v15);
      if ( IO_OpenStringSource((int)aDefaultPublicH, v9, 0) )
      {
        MessageHandler_ParseDefinition((int)aDefaultPublicH);
        Rules_DestroyPPBuffer();
        IO_CloseStringRouter((int)aDefaultPublicH);
      }
    }
    Rules_SetLoadInProgress(v13);
    unknown_libname_5(v10, v2);
    return Mem_SmallBlockFree(v12, v11);
  }
  return result;
}
// 4DF6E5: variable 'v4' is possibly undefined
// 4DF6E5: variable 'v3' is possibly undefined
// 4DF705: variable 'v5' is possibly undefined
// 4DF711: variable 'v7' is possibly undefined
// 4DF758: variable 'v6' is possibly undefined
// 4DF764: variable 'v9' is possibly undefined
// 4DF78D: variable 'v10' is possibly undefined
// 4DF794: variable 'v12' is possibly undefined
// 4DF794: variable 'v11' is possibly undefined
// 472B00: using guessed type int __fastcall unknown_libname_5(_DWORD, _DWORD);
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (004DF7B0) --------------------------------------------------------
signed int  MessageHandler_CheckParamNotSelfReference(int a1)
{
  int v1; // ecx
  int v3; // ecx

  if ( strncmp_(a1, aSelf_0) || *(_BYTE *)(v1 + 4) != 58 )
    return 0;
  Rules_PrintErrorID((int)aMsgpsr, 4, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIllegalSlotRef, v3);
  return 1;
}
// 4DF7C8: variable 'v1' is possibly undefined
// 4DF7F7: variable 'v3' is possibly undefined
// 48A1ED: using guessed type int __fastcall strncmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];

//----- (004DF810) --------------------------------------------------------
signed int  MessageHandler_ResolveSelfSlotGetRef(int a1, int a2, int a3)
{
  int v6; // edx
  int v7; // ecx
  int v8; // eax
  int v9; // ecx
  int v10; // [esp+0h] [ebp-1Ch]
  int v11; // [esp+4h] [ebp-18h]

  if ( *(_WORD *)a1 != 15 && *(_WORD *)a1 != 16 )
    return 0;
  if ( strncmp_(a3, aSelf_0) )
    return 0;
  if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(a1 + 2) + 16) + 4) != 58 )
    return 0;
  IO_OpenStringSource((int)aHndVar, (const char *)(*(_DWORD *)(*(_DWORD *)(a1 + 2) + 16) + 5), 0);
  Rules_GetPPBufferStatus();
  Rules_SetPPBufferStatus(0);
  Parser_NextToken((int)aHndVar, v6);
  Rules_SetPPBufferStatus(v7);
  IO_CloseStringRouter((int)aHndVar);
  if ( v10 == 102 )
    return 0;
  v8 = MessageHandler_BuildSlotAccessNode(a2, v10, 0, v11, 0);
  if ( !v8 )
    return -1;
  AST_NewSlotReferenceNode(58, v9, v8);
  return 1;
}
// 4DF88B: variable 'v6' is possibly undefined
// 4DF892: variable 'v7' is possibly undefined
// 4DF8A7: variable 'v10' is possibly undefined
// 4DF8B3: variable 'v11' is possibly undefined
// 4DF8D2: variable 'v9' is possibly undefined
// 48A1ED: using guessed type int __fastcall strncmp_(_DWORD, _DWORD);

//----- (004DF8F0) --------------------------------------------------------
signed int  MessageHandler_ResolveSelfSlotBindRef(int a1, int a2)
{
  int v4; // ecx
  int v5; // ecx
  signed int result; // eax
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int *v10; // ebp
  int v11; // eax
  int v12; // ecx
  int v13; // [esp+0h] [ebp-20h]
  int v14; // [esp+4h] [ebp-1Ch]

  if ( !strcmp_(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(a1 + 6) + 2) + 16), aSelf_0) )
  {
    Rules_PrintErrorID((int)aMsgpsr, 5, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aActiveInstance, v7);
    return -1;
  }
  else if ( !strncmp_(v4, aSelf_0)
         && *(_BYTE *)(v5 + 4) == 58
         && (IO_OpenStringSource((int)aHndVar, (const char *)(v5 + 5), 0),
             Rules_GetPPBufferStatus(),
             Rules_SetPPBufferStatus(0),
             Parser_NextToken((int)aHndVar, v8),
             Rules_SetPPBufferStatus(v9),
             IO_CloseStringRouter((int)aHndVar),
             v13 != 102) )
  {
    v10 = *(int **)(*(_DWORD *)(a1 + 6) + 10);
    v11 = MessageHandler_BuildSlotAccessNode(a2, v13, 1, v14, v10);
    if ( v11 )
    {
      AST_NewSlotReferenceNode(59, v12, v11);
      *(_DWORD *)(*(_DWORD *)(a1 + 6) + 10) = 0;
      AST_Free(*(_DWORD *)(a1 + 6));
      result = 1;
      *(_DWORD *)(a1 + 6) = v10;
    }
    else
    {
      return -1;
    }
  }
  else
  {
    return 0;
  }
  return result;
}
// 4DF921: variable 'v4' is possibly undefined
// 4DF92A: variable 'v5' is possibly undefined
// 4DF95E: variable 'v7' is possibly undefined
// 4DF98E: variable 'v8' is possibly undefined
// 4DF995: variable 'v9' is possibly undefined
// 4DF9AA: variable 'v13' is possibly undefined
// 4DF9BE: variable 'v14' is possibly undefined
// 4DF9DE: variable 'v12' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 48A1ED: using guessed type int __fastcall strncmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];

//----- (004DFA10) --------------------------------------------------------
int  MessageHandler_BuildSlotAccessNode(int a1, int a2, int a3, int a4, int *a5)
{
  unsigned int v6; // eax
  int v7; // ecx
  int v8; // esi
  signed int v9; // edi
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // eax
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx

  if ( a2 == 2 )
  {
    v6 = Instance_ResolveSlotIndex(a3, a4);
    if ( v6 == -1 )
    {
      Rules_PrintErrorID((int)aMsgpsr, 6, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoSuchSlot_0, v12);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(a4 + 16), v13);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInClass_1, v14);
      v15 = Rules_GetConstructNameString(a1);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], v15, v16);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFor_selfRefere, v17);
      return 0;
    }
    else
    {
      v8 = *(_DWORD *)(4 * v6 + *(_DWORD *)(a1 + 56));
      if ( (*(_BYTE *)(v8 + 1) & 4) != 0 || a1 == *(_DWORD *)(v8 + 4) )
      {
        if ( !v7 )
          return v8;
        if ( (*(_BYTE *)v8 & 0x10) != 0 && (*(_BYTE *)v8 & 0x20) == 0 )
        {
          MessageHandler_ReportSlotWriteAccessDenied(*(_DWORD *)(a4 + 16), 0);
          return 0;
        }
        else
        {
          if ( !Rules_StaticConstraintCheckingEnabled() )
            return v8;
          v9 = Rules_CheckFieldExprListAgainstConstraint(a5, *(_DWORD *)(v8 + 20));
          if ( !v9 )
            return v8;
          Rules_PrintErrorID((int)aCstrnchk_2, 1, 0);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpressionFor, (int)aDirectSlotWrit);
          Instance_PrintSlotErrorContext((int)g_IO_LogicalNameTable_WError[0], v8, v18, 0);
          Rules_PrintConstraintViolationMessage(0, 0, 0, 0, 0, 0, v9, *(_DWORD *)(v8 + 20), 0);
          return 0;
        }
      }
      else
      {
        MessageHandler_ReportPrivateSlotAccessDenied(v8);
        return 0;
      }
    }
  }
  else
  {
    Rules_PrintErrorID((int)aMsgpsr, 7, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIllegalValueFo, v11);
    return 0;
  }
}
// 4DFA4E: variable 'v7' is possibly undefined
// 4DFAA0: variable 'v11' is possibly undefined
// 4DFAC8: variable 'v12' is possibly undefined
// 4DFAD5: variable 'v13' is possibly undefined
// 4DFAE4: variable 'v14' is possibly undefined
// 4DFAFA: variable 'v16' is possibly undefined
// 4DFB09: variable 'v17' is possibly undefined
// 4DFB69: variable 'v18' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004DFB90) --------------------------------------------------------
int  AST_NewSlotReferenceNode(__int16 a1, int a2, int a3)
{
  _WORD *v4; // ecx
  int result; // eax
  int v6; // ecx
  __int16 v7; // [esp+0h] [ebp-10h] BYREF
  int v8; // [esp+2h] [ebp-Eh]
  int v9; // [esp+Ch] [ebp-4h]

  v9 = a2;
  Mem_AllocArray(&v7, 6);
  v7 = *(_WORD *)(*(_DWORD *)(a3 + 4) + 24);
  v8 = *(_DWORD *)(*(_DWORD *)(a3 + 8) + 8);
  *v4 = a1;
  result = Rules_AddBitmapValue(&v7, 6);
  *(_DWORD *)(v6 + 2) = result;
  return result;
}
// 4DFBC1: variable 'v4' is possibly undefined
// 4DFBC9: variable 'v6' is possibly undefined

//----- (004DFBE0) --------------------------------------------------------
signed int Rules_SetupDefinstancesBsaveBload()
{
  return Rules_RegisterBinaryItem(
           (int)aDefinstances_0,
           0,
           (int)Rules_FindDefinstancesBsaveExpressions,
           (int)Rules_CountDefinstancesBsaveExpressions,
           (int)Rules_BsaveWriteDefinstancesCounts,
           (int)Rules_BsaveWriteDefinstancesData,
           (int)Rules_BloadAllocateDefinstancesArrays,
           (int)Rules_BloadRefreshDefinstances,
           (int)Rules_ClearDefinstancesBloadData);
}

//----- (004DFC20) --------------------------------------------------------
int  Rules_DefinstancesBloadModuleReference(int a1)
{
  return 12 * a1 + g_DefinstancesBloadModuleRefArray;
}
// 54E914: using guessed type int dword_54E914;

//----- (004DFC40) --------------------------------------------------------
signed int Rules_CountDefinstancesBsaveExpressions()
{
  signed int result; // eax

  if ( Rules_IsBloaded() )
  {
    Rules_ConstructQueuePush(g_Clips_DefinstancesCount);
    Rules_ConstructQueuePush(g_Definstances_Count);
  }
  g_Definstances_Count = 0;
  result = Rules_DoForAllConstructs((void (*)(void))Rules_MarkDefinstancesExpressionUsage, 0);
  g_Clips_DefinstancesCount = result;
  return result;
}
// 51C710: using guessed type int dword_51C710;
// 51C714: using guessed type int dword_51C714;
// 54E8F0: using guessed type int dword_54E8F0;

//----- (004DFC90) --------------------------------------------------------
__int16  Rules_MarkDefinstancesExpressionUsage(_DWORD *a1)
{
  int v1; // edx
  int v2; // ecx
  int v3; // ecx

  v1 = g_Definstances_Count++;
  AST_MarkNodeFieldBound(a1, v1);
  g_ClipsExpressionNodeIndex += AST_CountTreeNodes(*(_DWORD *)(v2 + 24));
  return Rules_MarkReferencedFunctions(*(__int16 **)(v3 + 24));
}
// 4DFCA8: variable 'v2' is possibly undefined
// 4DFCB6: variable 'v3' is possibly undefined
// 51C710: using guessed type int dword_51C710;
// 54E680: using guessed type int dword_54E680;

//----- (004DFCC0) --------------------------------------------------------
signed int Rules_FindDefinstancesBsaveExpressions()
{
  return Rules_DoForAllConstructs((void (*)(void))Rules_BsaveWriteDefinstancesExpression, 0);
}
// 54E8F0: using guessed type int dword_54E8F0;

//----- (004DFCE0) --------------------------------------------------------
__int16 * Rules_BsaveWriteDefinstancesExpression(int a1, int a2)
{
  return Rules_BsaveWriteExpression(*(__int16 **)(a1 + 24), a2);
}

//----- (004DFCF0) --------------------------------------------------------
const void * Rules_BsaveWriteDefinstancesCounts(int a1, int a2)
{
  int v2; // ecx
  int v3; // ecx
  _DWORD v5[4]; // [esp+0h] [ebp-10h] BYREF

  v5[2] = a2;
  v5[0] = 8;
  Rules_BsaveWriteBlock(4, a1, v5);
  Rules_BsaveWriteBlock(4, v2, &g_Clips_DefinstancesCount);
  return Rules_BsaveWriteBlock(4, v3, &g_Definstances_Count);
}
// 4DFD1A: variable 'v2' is possibly undefined
// 4DFD2B: variable 'v3' is possibly undefined
// 51C710: using guessed type int dword_51C710;
// 51C714: using guessed type int dword_51C714;

//----- (004DFD40) --------------------------------------------------------
int  Rules_BsaveWriteDefinstancesData(int a1, int a2)
{
  int v3; // eax
  int v4; // ecx
  _DWORD *v5; // eax
  int v6; // ecx
  int result; // eax
  _DWORD v8[3]; // [esp-Ch] [ebp-20h] BYREF
  _DWORD v9[5]; // [esp+0h] [ebp-14h] BYREF

  v9[3] = a2;
  v9[0] = 16 * g_Definstances_Count + 12 * g_Clips_DefinstancesCount;
  Rules_BsaveWriteBlock(4, a1, v9);
  g_Definstances_Count = 0;
  if ( Module_NextEnum(0) )
  {
    do
    {
      v3 = Module_FindItemByName((int)aDefinstances_0);
      v5 = (_DWORD *)Module_GetItem(v4, *(_DWORD *)(v3 + 4));
      Module_AssignBsaveItemHeaderIndices(v8, v5);
      Rules_BsaveWriteBlock(12, a1, v8);
    }
    while ( Module_NextEnum(v6) );
  }
  Rules_DoForAllConstructs((void (*)(void))Rules_BsaveWriteDefinstancesRecord, 0);
  result = Rules_IsBloaded();
  if ( result )
  {
    Rules_ConstructQueuePop(&g_Clips_DefinstancesCount);
    return Rules_ConstructQueuePop(&g_Definstances_Count);
  }
  return result;
}
// 4DFDA2: variable 'v4' is possibly undefined
// 4DFDC0: variable 'v6' is possibly undefined
// 51C710: using guessed type int dword_51C710;
// 51C714: using guessed type int dword_51C714;
// 54E8F0: using guessed type int dword_54E8F0;

//----- (004DFE20) --------------------------------------------------------
const void * Rules_BsaveWriteDefinstancesRecord(int a1, int a2, int a3)
{
  int v4; // ecx
  _DWORD v6[3]; // [esp-Ch] [ebp-18h] BYREF
  int v7; // [esp+0h] [ebp-Ch]
  int v8; // [esp+4h] [ebp-8h]

  v8 = a3;
  AST_ExtractPatternBindingInfo(v6, a1);
  if ( *(_DWORD *)(v4 + 24) )
  {
    v7 = g_ClipsExpressionNodeIndex;
    g_ClipsExpressionNodeIndex += AST_CountTreeNodes(*(_DWORD *)(v4 + 24));
  }
  else
  {
    v7 = -1;
  }
  return Rules_BsaveWriteBlock(16, a2, v6);
}
// 4DFE32: variable 'v4' is possibly undefined
// 54E680: using guessed type int dword_54E680;

//----- (004DFE80) --------------------------------------------------------
int __thiscall Rules_BloadAllocateDefinstancesArrays(void *this)
{
  int result; // eax
  _DWORD v2[4]; // [esp+0h] [ebp-10h] BYREF

  v2[2] = this;
  result = Rules_BloadReadBlock((uintptr_t)v2, 4u);
  if ( v2[0] )
  {
    Rules_BloadReadBlock((uintptr_t)&g_Clips_DefinstancesCount, 4u);
    result = Rules_BloadReadBlock((uintptr_t)&g_Definstances_Count, 4u);
    if ( g_Clips_DefinstancesCount )
    {
      v2[0] = 12 * g_Clips_DefinstancesCount;
      result = Mem_HeapAllocWithRetry((_DWORD *)(12 * g_Clips_DefinstancesCount));
      g_DefinstancesBloadModuleRefArray = result;
      if ( g_Definstances_Count )
      {
        v2[0] = 28 * g_Definstances_Count;
        result = Mem_HeapAllocWithRetry((_DWORD *)(28 * g_Definstances_Count));
        g_ClipsDefinstancesBloadArray = result;
      }
      else
      {
        g_ClipsDefinstancesBloadArray = 0;
      }
    }
    else
    {
      g_DefinstancesBloadModuleRefArray = 0;
      g_ClipsDefinstancesBloadArray = 0;
    }
  }
  return result;
}
// 51C70C: using guessed type int dword_51C70C;
// 51C710: using guessed type int dword_51C710;
// 51C714: using guessed type int dword_51C714;
// 54E914: using guessed type int dword_54E914;

//----- (004DFF40) --------------------------------------------------------
signed int Rules_BloadRefreshDefinstances()
{
  int v3; // [esp-8h] [ebp-Ch] BYREF

  Rules_BloadReadBlock((uintptr_t)&v3, 4u);
  Rules_BloadAndRefresh(g_Clips_DefinstancesCount, 12, (void (__fastcall *)(signed int, signed int))Rules_BloadRefreshDefinstancesRecord);
  return Rules_BloadAndRefresh(g_Definstances_Count, 16, (void (__fastcall *)(signed int, signed int))Rules_BloadRefreshDefinstancesExpression);
}
// 51C710: using guessed type int dword_51C710;
// 51C714: using guessed type int dword_51C714;

//----- (004DFF80) --------------------------------------------------------
_DWORD * Rules_BloadRefreshDefinstancesRecord(_DWORD *a1, int a2)
{
  return Module_UpdateItemHeader(a1, (_DWORD *)(12 * a2 + g_DefinstancesBloadModuleRefArray), g_ClipsDefinstancesBloadArray, 28);
}
// 51C70C: using guessed type int dword_51C70C;
// 54E914: using guessed type int dword_54E914;

//----- (004DFFC0) --------------------------------------------------------
int  Rules_BloadRefreshDefinstancesExpression(int a1, int a2)
{
  _DWORD *v3; // edi
  int result; // eax

  v3 = (_DWORD *)(g_ClipsDefinstancesBloadArray + 28 * a2);
  Rules_BuildIndexedSlotDescriptor(a1, v3, g_DefinstancesBloadModuleRefArray, 12, 28, g_ClipsDefinstancesBloadArray);
  if ( *(_DWORD *)(a1 + 12) == -1 )
  {
    result = 0;
    v3[5] = 0;
    v3[6] = 0;
  }
  else
  {
    result = g_ClipsPackedExpressionArray + 14 * *(_DWORD *)(a1 + 12);
    v3[5] = 0;
    v3[6] = result;
  }
  return result;
}
// 51C70C: using guessed type int dword_51C70C;
// 54E688: using guessed type int dword_54E688;
// 54E914: using guessed type int dword_54E914;

//----- (004E0040) --------------------------------------------------------
signed int Rules_ClearDefinstancesBloadData()
{
  signed int result; // eax
  int v1; // ecx
  int v2; // ecx
  int v3; // edx

  result = 12 * g_Clips_DefinstancesCount;
  if ( 12 * g_Clips_DefinstancesCount )
  {
    Mem_ReleasePoolBlock(g_DefinstancesBloadModuleRefArray, 12 * g_Clips_DefinstancesCount);
    g_DefinstancesBloadModuleRefArray = 0;
    g_Clips_DefinstancesCount = 0;
    if ( g_Definstances_Count > 0 )
    {
      v1 = 0;
      do
      {
        Rules_ReleaseSymbolReference((int *)(v1 + g_ClipsDefinstancesBloadArray), v1);
        v1 = v2 + 28;
      }
      while ( v3 < g_Definstances_Count );
    }
    result = 28 * g_Definstances_Count;
    if ( 28 * g_Definstances_Count )
    {
      result = Mem_ReleasePoolBlock(g_ClipsDefinstancesBloadArray, 28 * g_Definstances_Count);
      g_ClipsDefinstancesBloadArray = 0;
      g_Definstances_Count = 0;
    }
  }
  return result;
}
// 4E009F: variable 'v2' is possibly undefined
// 4E00A4: variable 'v3' is possibly undefined
// 51C70C: using guessed type int dword_51C70C;
// 51C710: using guessed type int dword_51C710;
// 51C714: using guessed type int dword_51C714;
// 54E914: using guessed type int dword_54E914;

//----- (004E00F0) --------------------------------------------------------
int Rules_RegisterDefinstancesCodeGenerator()
{
  int result; // eax

  result = Rules_AddCodeGeneratorItem((int)aDefinstances_1, 0, 0, (int)Compiler_RegisterDefinstancesModuleAssigner, (int)Compiler_WriteDefinstancesToCode, 2);
  g_DefinstancesCodeGenItem = result;
  return result;
}
// 54E918: using guessed type int dword_54E918;

//----- (004E0120) --------------------------------------------------------
int  Rules_WriteDefinstancesModuleReference(int a1, int a2)
{
  return Output_WriteFormatted(a2, **(_DWORD **)(g_DefinstancesCodeGenItem + 20), a1, (int)aMihsSD_DD_7, **(_DWORD **)(g_DefinstancesCodeGenItem + 20));
}
// 54E918: using guessed type int dword_54E918;

//----- (004E0160) --------------------------------------------------------
signed int Compiler_RegisterDefinstancesModuleAssigner()
{
  return Rules_RegisterModuleItemIdAssigner();
}
// 54E8F0: using guessed type int dword_54E8F0;

//----- (004E0170) --------------------------------------------------------
int  Compiler_WriteDefinstancesToCode(const char *a1, const char *a2, int a3, int a4, int a5)
{
  int v5; // esi
  int v6; // ecx
  int v7; // eax
  int v8; // ecx
  int v9; // edi
  int v10; // edi
  int v11; // eax
  int v12; // ecx
  int v13; // esi
  int v14; // ebx
  int v16; // [esp+0h] [ebp-3Ch] BYREF
  int v17; // [esp+4h] [ebp-38h] BYREF
  int v18; // [esp+8h] [ebp-34h] BYREF
  int v19; // [esp+Ch] [ebp-30h] BYREF
  int v20; // [esp+10h] [ebp-2Ch] BYREF
  int v21; // [esp+14h] [ebp-28h]
  int Enum; // [esp+18h] [ebp-24h]
  const char *v23; // [esp+1Ch] [ebp-20h]
  const char *v24; // [esp+20h] [ebp-1Ch]
  int v25; // [esp+24h] [ebp-18h]
  int v26; // [esp+28h] [ebp-14h]
  int v27; // [esp+2Ch] [ebp-10h]

  v23 = a1;
  v24 = a2;
  v25 = a4;
  v27 = a3;
  v26 = 0;
  v17 = 0;
  v18 = 1;
  v19 = 0;
  v20 = 1;
  v21 = 0;
  Output_WriteFormatted(0, 1, a4, (int)aIncludeDefins_, 1);
  v5 = 0;
  Enum = Module_NextEnum(0);
  if ( Enum )
  {
    while ( 1 )
    {
      Module_SetCurrent(Enum);
      v7 = Rules_ConstructCodeFileOpen(
             v21,
             v23,
             v27,
             v24,
             &v16,
             v18,
             v25,
             (char)aDefinstances_m,
             **(const char ***)(g_DefinstancesCodeGenItem + 20),
             0,
             0);
      v9 = v7;
      if ( !v7 )
      {
        Compiler_CloseDefinstancesCodeFiles(0, v5, v8, a5);
        return 0;
      }
      Compiler_WriteDefinstancesModuleHeaderToCode(v7, Enum, a5);
      v21 = Rules_ConstructCodeFileClose(v9, &v17, a5, &v18, 0, 0);
      v10 = Definstances_GetNextRecord(0);
      if ( v10 )
        break;
LABEL_6:
      v14 = v26;
      Enum = Module_NextEnum(Enum);
      v26 = v14 + 1;
      ++v17;
      if ( !Enum )
        goto LABEL_7;
    }
    while ( 1 )
    {
      v11 = Rules_ConstructCodeFileOpen(
              v5,
              v23,
              v27,
              v24,
              &v16,
              v20,
              v25,
              (char)aDefinstances_3,
              *(const char **)(*(_DWORD *)(g_DefinstancesCodeGenItem + 20) + 4),
              0,
              0);
      v13 = v11;
      if ( !v11 )
        break;
      Compiler_WriteDefinstancesConstructToCode(v11, v10, a5, v26);
      ++v19;
      v5 = Rules_ConstructCodeFileClose(v13, &v19, a5, &v20, 0, 0);
      v10 = Definstances_GetNextRecord(v10);
      if ( !v10 )
        goto LABEL_6;
    }
    Compiler_CloseDefinstancesCodeFiles(v21, 0, v12, a5);
    return 0;
  }
  else
  {
LABEL_7:
    Compiler_CloseDefinstancesCodeFiles(v21, v5, v6, a5);
    return 1;
  }
}
// 4E0309: variable 'v6' is possibly undefined
// 4E0320: variable 'v8' is possibly undefined
// 4E0338: variable 'v12' is possibly undefined
// 54E918: using guessed type int dword_54E918;

//----- (004E0350) --------------------------------------------------------
int  Compiler_CloseDefinstancesCodeFiles(int a1, int a2, int a3, int a4)
{
  int result; // eax
  int v6; // [esp+0h] [ebp-14h] BYREF
  _DWORD v7[4]; // [esp+4h] [ebp-10h] BYREF

  v7[3] = a3;
  result = a2;
  v6 = a4;
  v7[0] = 0;
  if ( a2 )
  {
    result = Rules_ConstructCodeFileClose(a2, &v6, a4, v7, 0, 0);
    if ( !a1 )
      return result;
    goto LABEL_5;
  }
  if ( a1 )
  {
LABEL_5:
    v6 = a4;
    return Rules_ConstructCodeFileClose(a1, &v6, a4, v7, 0, 0);
  }
  return result;
}

//----- (004E03B0) --------------------------------------------------------
int  Compiler_WriteDefinstancesModuleHeaderToCode(int a1, int a2, int a3)
{
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  char v9; // [esp+0h] [ebp-Ch]
  char v10; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(a3, a2, a1, (int)asc_50E3D0, v9);
  Rules_WriteConstructModuleItemHeaderToCode(a1, v4, v5, g_Clips_DefinstancesModuleItemIndex, *(_DWORD *)(*(_DWORD *)(g_DefinstancesCodeGenItem + 20) + 4));
  return Output_WriteFormatted(v7, v6, a1, (int)asc_50E3D4, v10);
}
// 4E03BB: variable 'v9' is possibly undefined
// 4E03D8: variable 'v4' is possibly undefined
// 4E03D8: variable 'v5' is possibly undefined
// 4E03E3: variable 'v7' is possibly undefined
// 4E03E3: variable 'v6' is possibly undefined
// 4E03E3: variable 'v10' is possibly undefined
// 54E8F0: using guessed type int dword_54E8F0;
// 54E918: using guessed type int dword_54E918;

//----- (004E03F0) --------------------------------------------------------
int  Compiler_WriteDefinstancesConstructToCode(int a1, int a2, int a3, int a4)
{
  int *v6; // eax
  DWORD v7; // ebp
  signed int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  char v15; // [esp+0h] [ebp-Ch]
  char v16; // [esp+0h] [ebp-Ch]
  char v17; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(a3, a2, a1, (int)asc_50E3D0, v15);
  v6 = *(int **)(g_DefinstancesCodeGenItem + 20);
  v7 = *v6;
  Rules_WriteConstructHeaderToCode(a1, a2, v8, a4, *v6, v6[1]);
  Output_WriteFormatted(v10, v9, a1, (int)a0_2, v16);
  Rules_ExpressionToCode(a1, *(__int16 **)(a2 + 24), v11, v7);
  return Output_WriteFormatted(v13, v12, a1, (int)asc_50E3D4, v17);
}
// 4E03FD: variable 'v15' is possibly undefined
// 4E041D: variable 'v8' is possibly undefined
// 4E0428: variable 'v10' is possibly undefined
// 4E0428: variable 'v9' is possibly undefined
// 4E0428: variable 'v16' is possibly undefined
// 4E0435: variable 'v11' is possibly undefined
// 4E0440: variable 'v13' is possibly undefined
// 4E0440: variable 'v12' is possibly undefined
// 4E0440: variable 'v17' is possibly undefined
// 54E918: using guessed type int dword_54E918;

//----- (004E0450) --------------------------------------------------------
char * Parser_ParseInstanceQueryNoAction(int a1, int a2)
{
  char *result; // eax
  char *v4; // esi
  int v5; // edx
  int v6; // ecx
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int v10[7]; // [esp+0h] [ebp-1Ch] BYREF

  v10[5] = a2;
  result = (char *)Parser_ParseInstanceQueryRestrictions(a1, v10);
  v4 = result;
  if ( result )
  {
    Rules_IncrementIndentDepth(3);
    AST_Append(v6, v5);
    if ( Parser_ParseInstanceQueryTestExpression(v7, v7) )
    {
      Rules_DecrementIndentDepth(3);
      Parser_NextToken(v9, v8);
      if ( v10[0] == 101 )
      {
        Parser_ReplaceInstanceQuerySlotReferences(v4, *(_DWORD *)(a1 + 6), 0, 1);
        AST_Free((int)v4);
        return (char *)a1;
      }
      else
      {
        Parser_ReportSyntaxError();
        AST_Free(a1);
        AST_Free((int)v4);
        return 0;
      }
    }
    else
    {
      Rules_DecrementIndentDepth(3);
      AST_Free((int)v4);
      return 0;
    }
  }
  return result;
}
// 4E047A: variable 'v6' is possibly undefined
// 4E047A: variable 'v5' is possibly undefined
// 4E0483: variable 'v7' is possibly undefined
// 4E049A: variable 'v9' is possibly undefined
// 4E049A: variable 'v8' is possibly undefined

//----- (004E0510) --------------------------------------------------------
char * Parser_ParseInstanceQueryAction(int a1, int a2)
{
  char *result; // eax
  char *v4; // esi
  int v5; // edx
  int v6; // ecx
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int v10; // ecx
  int v11; // edx
  int v12; // ecx
  int v13[7]; // [esp+0h] [ebp-1Ch] BYREF

  v13[5] = a2;
  result = (char *)Parser_ParseInstanceQueryRestrictions(a1, v13);
  v4 = result;
  if ( result )
  {
    Rules_IncrementIndentDepth(3);
    AST_Append(v6, v5);
    if ( Parser_ParseInstanceQueryTestExpression(v7, v7) && (AST_Append(v9, v8), Parser_ParseInstanceQueryActionExpression(a1, v10, (int)v4)) )
    {
      Rules_DecrementIndentDepth(3);
      Parser_NextToken(v12, v11);
      if ( v13[0] == 101 )
      {
        Parser_ReplaceInstanceQuerySlotReferences(v4, *(_DWORD *)(a1 + 6), 0, 1);
        Parser_ReplaceInstanceQuerySlotReferences(v4, *(_DWORD *)(*(_DWORD *)(a1 + 6) + 10), 0, 0);
        AST_Free((int)v4);
        return (char *)a1;
      }
      else
      {
        Parser_ReportSyntaxError();
        AST_Free(a1);
        AST_Free((int)v4);
        return 0;
      }
    }
    else
    {
      Rules_DecrementIndentDepth(3);
      AST_Free((int)v4);
      return 0;
    }
  }
  return result;
}
// 4E053A: variable 'v6' is possibly undefined
// 4E053A: variable 'v5' is possibly undefined
// 4E0543: variable 'v7' is possibly undefined
// 4E054C: variable 'v9' is possibly undefined
// 4E054C: variable 'v8' is possibly undefined
// 4E0557: variable 'v10' is possibly undefined
// 4E056E: variable 'v12' is possibly undefined
// 4E056E: variable 'v11' is possibly undefined

//----- (004E05F0) --------------------------------------------------------
int  Parser_ParseInstanceQueryRestrictions(int a1, int *a2)
{
  int v4; // edi
  int v5; // edx
  int v6; // ecx
  int v7; // ecx
  int v8; // ebx
  int v10; // ecx
  int v11; // eax
  signed int v12; // eax
  int v13; // ecx
  signed int v14; // eax
  signed int v15; // ebx
  int v16; // ecx
  signed int v17; // eax
  signed int v18; // eax
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // edx
  signed int v24; // edx
  int v25; // [esp+0h] [ebp-20h] BYREF
  signed int v26; // [esp+4h] [ebp-1Ch]
  signed int v27; // [esp+8h] [ebp-18h]
  int v28; // [esp+Ch] [ebp-14h]

  v4 = 0;
  v27 = 0;
  v25 = 0;
  IO_OutWriteToken(asc_50E3F8);
  v28 = 0;
  Parser_NextToken(v6, v5);
  v8 = *a2;
  v26 = 0;
  if ( v8 == 100 && (Parser_NextToken(v7, (int)a2), *a2 == 100) )
  {
    while ( *a2 == 100 )
    {
      Parser_NextToken(v10, (int)a2);
      if ( *a2 != 15 )
        goto LABEL_2;
      v11 = v4;
      if ( v4 )
      {
        while ( *(_DWORD *)(v11 + 2) != a2[1] )
        {
          v11 = *(_DWORD *)(v11 + 10);
          if ( !v11 )
            goto LABEL_12;
        }
        Rules_PrintErrorID((int)aInsqypsr, 1, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDuplicateIns_0, v20);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(**(_DWORD **)(a1 + 2) + 16), v21);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__27, v22);
        goto LABEL_3;
      }
LABEL_12:
      v12 = AST_NewNode(15, a2[1]);
      if ( v4 )
        *(_DWORD *)(v27 + 10) = v12;
      else
        v4 = v12;
      v27 = v12;
      IO_OutWriteToken(asc_50E3F8);
      v14 = Parser_ParseArgument(v13, &v25, v13);
      v15 = v14;
      v28 = v14;
      if ( v25 )
        goto LABEL_3;
      if ( !v14 )
        goto LABEL_2;
      if ( !Rules_ReplaceClassNameWithClassReference(v14) )
        goto LABEL_3;
      IO_OutWriteToken(asc_50E3F8);
      while ( 1 )
      {
        v17 = Parser_ParseArgument(v16, &v25, v16);
        if ( !v17 )
          break;
        if ( !Rules_ReplaceClassNameWithClassReference(v17) )
          goto LABEL_3;
        *(_DWORD *)(v15 + 10) = v23;
        IO_OutWriteToken(asc_50E3F8);
        v15 = v24;
      }
      if ( v25 )
        goto LABEL_3;
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(asc_50E444);
      v18 = AST_NewNode(2, g_InternedSym_Qds);
      *(_DWORD *)(v15 + 10) = v18;
      if ( *(_DWORD *)(a1 + 6) )
        *(_DWORD *)(v26 + 10) = v28;
      else
        *(_DWORD *)(a1 + 6) = v28;
      v26 = v18;
      IO_OutWriteToken(asc_50E3F8);
      Parser_NextToken(v19, (int)a2);
      v28 = 0;
    }
    if ( *a2 != 101 )
      goto LABEL_2;
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken(asc_50E444);
    return v4;
  }
  else
  {
LABEL_2:
    Parser_ReportSyntaxError();
LABEL_3:
    AST_Free(v28);
    AST_Free(a1);
    AST_Free(v4);
    return 0;
  }
}
// 4E0618: variable 'v6' is possibly undefined
// 4E0618: variable 'v5' is possibly undefined
// 4E0657: variable 'v7' is possibly undefined
// 4E068E: variable 'v10' is possibly undefined
// 4E06DC: variable 'v13' is possibly undefined
// 4E0716: variable 'v16' is possibly undefined
// 4E077E: variable 'v19' is possibly undefined
// 4E07A7: variable 'v20' is possibly undefined
// 4E07B9: variable 'v21' is possibly undefined
// 4E07C8: variable 'v22' is possibly undefined
// 4E07F0: variable 'v23' is possibly undefined
// 4E07F8: variable 'v24' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51B454: using guessed type int dword_51B454;

//----- (004E0810) --------------------------------------------------------
signed int  Rules_ReplaceClassNameWithClassReference(int a1)
{
  int *v3; // eax
  int v4; // ecx

  if ( *(_WORD *)a1 != 2 )
    return 1;
  v3 = Class_LookupByQualifiedName(*(_BYTE **)(*(_DWORD *)(a1 + 2) + 16));
  if ( v3 )
  {
    *(_WORD *)a1 = 57;
    *(_DWORD *)(a1 + 2) = v3;
    return 1;
  }
  else
  {
    Rules_ReportCantFindItem(v4, v4);
    return 0;
  }
}
// 4E084A: variable 'v4' is possibly undefined

//----- (004E0860) --------------------------------------------------------
signed int __fastcall Parser_ParseInstanceQueryTestExpression(int a1, int a2)
{
  int v3; // ebx
  _DWORD *v4; // edx
  int v5; // ecx
  signed int v6; // eax
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v14; // ecx

  v3 = Parser_GetLoopContextStack();
  Parser_SetLoopContextStack(0);
  v6 = Parser_ParseArgument(a2, v4, v5);
  if ( v6 )
  {
    *(_DWORD *)(v6 + 10) = *(_DWORD *)(v7 + 6);
    *(_DWORD *)(v7 + 6) = v6;
    if ( Parser_LoopContextStackIsEmpty() )
    {
      Parser_SetLoopContextStack(v3);
      return 1;
    }
    else
    {
      Parser_FreeLoopContextStack();
      Parser_SetLoopContextStack(v3);
      Rules_PrintErrorID((int)aInsqypsr, v8, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aBindsAreNotA_0, v9);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(**(_DWORD **)(v10 + 2) + 16), v10);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__27, v11);
      AST_Free(v12);
      return 0;
    }
  }
  else
  {
    Parser_SetLoopContextStack(v3);
    Parser_ReportSyntaxError();
    AST_Free(v14);
    return 0;
  }
}
// 4E088A: conditional instruction was optimized away because %var_10.4==0
// 4E0881: variable 'v4' is possibly undefined
// 4E0881: variable 'v5' is possibly undefined
// 4E0894: variable 'v7' is possibly undefined
// 4E08C2: variable 'v8' is possibly undefined
// 4E08D1: variable 'v9' is possibly undefined
// 4E08D6: variable 'v10' is possibly undefined
// 4E08F2: variable 'v11' is possibly undefined
// 4E08F9: variable 'v12' is possibly undefined
// 4E0931: variable 'v14' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004E0960) --------------------------------------------------------
signed int  Parser_ParseInstanceQueryActionExpression(int a1, int a2, int a3)
{
  int v5; // edi
  int v6; // ecx
  signed int v7; // eax
  int v8; // ecx
  _DWORD *v9; // edx
  _DWORD *v10; // eax
  int v11; // ecx
  int v13; // edx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  _DWORD v19[5]; // [esp+0h] [ebp-14h] BYREF

  v19[0] = 0;
  v5 = Parser_GetLoopContextStack();
  Parser_SetLoopContextStack(0);
  g_ParserBreakContextFlag = 1;
  g_ClipsParseReturnContext = *(_DWORD *)g_ClipsParseContextSaveStack;
  v7 = Parser_ParseArgument(a2, v19, v6);
  g_ParserBreakContextFlag = 0;
  if ( v19[0] == 1 )
  {
    Parser_SetLoopContextStack(v8);
    AST_Free(a1);
    return 0;
  }
  else if ( v7 )
  {
    *(_DWORD *)(v7 + 10) = *(_DWORD *)(*(_DWORD *)(a1 + 6) + 10);
    *(_DWORD *)(*(_DWORD *)(a1 + 6) + 10) = v7;
    v9 = (_DWORD *)Parser_GetLoopContextStack();
    v10 = 0;
    if ( v9 )
    {
      while ( 1 )
      {
        v11 = a3;
        if ( a3 )
          break;
LABEL_7:
        v10 = v9;
        v9 = (_DWORD *)v9[2];
        if ( !v9 )
          goto LABEL_8;
      }
      while ( *(_DWORD *)(v11 + 2) != *v9 )
      {
        v11 = *(_DWORD *)(v11 + 10);
        if ( !v11 )
          goto LABEL_7;
      }
      Parser_FreeLoopContextStack();
      Parser_SetLoopContextStack(v5);
      Rules_PrintErrorID((int)aInsqypsr, v13, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotRebindIn, v14);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(*(_DWORD *)(v15 + 2) + 16), v15);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInFunction_3, v16);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(**(_DWORD **)(a1 + 2) + 16), v17);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__27, v18);
      AST_Free(a1);
      return 0;
    }
    else
    {
LABEL_8:
      if ( v10 )
        v10[2] = v5;
      else
        Parser_SetLoopContextStack(v5);
      return 1;
    }
  }
  else
  {
    Parser_SetLoopContextStack(v8);
    Parser_ReportSyntaxError();
    AST_Free(a1);
    return 0;
  }
}
// 4E099A: variable 'v6' is possibly undefined
// 4E0A10: variable 'v8' is possibly undefined
// 4E0A54: variable 'v13' is possibly undefined
// 4E0A63: variable 'v14' is possibly undefined
// 4E0A68: variable 'v15' is possibly undefined
// 4E0A82: variable 'v16' is possibly undefined
// 4E0A94: variable 'v17' is possibly undefined
// 4E0AA3: variable 'v18' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51B35C: using guessed type int dword_51B35C;
// 54E878: using guessed type int dword_54E878;
// 54E87C: using guessed type int dword_54E87C;

//----- (004E0AD0) --------------------------------------------------------
char * Parser_ReplaceInstanceQuerySlotReferences(char *a1, int a2, signed int a3, int a4)
{
  char *result; // eax
  int v8; // ecx
  int v9; // edx
  int i; // ecx
  int *v11; // eax
  signed int v12; // ebx
  signed int v13; // ecx
  int *v14; // eax
  signed int v15; // ecx
  int v16; // ebx
  signed int v17; // [esp+0h] [ebp-1Ch]
  int **Symbol; // [esp+4h] [ebp-18h]
  int v19; // [esp+8h] [ebp-14h]

  Symbol = Rules_MakeSymbol(aQueryInstanc_0);
  result = (char *)Rules_MakeSymbol(aQueryInstanc_1);
  v19 = (int)result;
  if ( v9 )
  {
    result = (char *)(v8 + 1);
    v17 = v8 + 1;
    do
    {
      if ( *(_WORD *)a2 == 15 )
      {
        result = a1;
        for ( i = 0; result; ++i )
        {
          if ( *(_DWORD *)(result + 2) == *(_DWORD *)(a2 + 2) )
            break;
          result = *(char **)(result + 10);
        }
        if ( result )
        {
          *(_DWORD *)(a2 + 2) = Symbol;
          *(_WORD *)a2 = 10;
          v11 = Rules_AddIntegerValue(a3);
          v12 = AST_NewNode(1, (int)v11);
          v14 = Rules_AddIntegerValue(v13);
          result = (char *)AST_NewNode(1, (int)v14);
          *(_DWORD *)(v12 + 10) = result;
          *(_DWORD *)(a2 + 6) = v12;
        }
        else if ( a4 == 1 )
        {
          result = (char *)Parser_ResolveInstanceQuerySlotReference((int)a1, a2, a3, v19);
        }
      }
      if ( *(_DWORD *)(a2 + 6) )
      {
        if ( Rules_IsInstanceSetQueryFunctionCall(a2) )
        {
          v15 = v17;
          v16 = a4;
        }
        else
        {
          v16 = a4;
          v15 = a3;
        }
        result = (char *)Parser_ReplaceInstanceQuerySlotReferences((int)a1, *(_DWORD *)(a2 + 6), v15, v16);
      }
      a2 = *(_DWORD *)(a2 + 10);
    }
    while ( a2 );
  }
  return result;
}
// 4E0AFE: variable 'v9' is possibly undefined
// 4E0B04: variable 'v8' is possibly undefined
// 4E0B58: variable 'v13' is possibly undefined

//----- (004E0BD0) --------------------------------------------------------
const char * Parser_ResolveInstanceQuerySlotReference(int a1, int a2, signed int a3, int a4)
{
  const char *v4; // ebp
  const char *result; // eax
  unsigned int v6; // kr04_4
  int v7; // esi
  int v8; // ecx
  signed int j; // edi
  int v10; // edx
  int v11; // ecx
  int *v12; // eax
  int *v13; // eax
  __int16 v14; // [esp+0h] [ebp-2Ch]
  int v15; // [esp+4h] [ebp-28h]
  const char *i; // [esp+1Ch] [ebp-10h]

  v4 = *(const char **)(*(_DWORD *)(a2 + 2) + 16);
  result = 0;
  v6 = strlen(v4) + 1;
  if ( (int)(v6 - 1) >= 3 )
  {
    v7 = v6 - 3;
    if ( (int)(v6 - 3) >= 1 )
    {
      for ( i = &v4[v7]; ; --i )
      {
        result = i;
        if ( *i == 58 )
        {
          result = (const char *)(v7 >= 1);
          if ( v7 >= 1 )
          {
            v8 = a1;
            for ( j = 0; v8; ++j )
            {
              result = (const char *)(strncmp_(v8, v4) != 0);
              if ( !result )
                break;
              v8 = *(_DWORD *)(v8 + 10);
            }
            if ( v8 )
              break;
          }
        }
        if ( --v7 < 1 )
          return result;
      }
      IO_OpenStringSource((int)aQueryVar, &v4[v7 + 1], 0);
      Rules_GetPPBufferStatus();
      Rules_SetPPBufferStatus(0);
      Parser_NextToken((int)aQueryVar, v10);
      Rules_SetPPBufferStatus(v11);
      IO_CloseStringRouter((int)aQueryVar);
      *(_WORD *)a2 = 10;
      *(_DWORD *)(a2 + 2) = a4;
      v12 = Rules_AddIntegerValue(a3);
      *(_DWORD *)(a2 + 6) = AST_NewNode(1, (int)v12);
      v13 = Rules_AddIntegerValue(j);
      *(_DWORD *)(*(_DWORD *)(a2 + 6) + 10) = AST_NewNode(1, (int)v13);
      result = (const char *)AST_NewNode(v14, v15);
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(a2 + 6) + 10) + 10) = result;
    }
  }
  return result;
}
// 4E0C4B: variable 'v8' is possibly undefined
// 4E0C92: variable 'v10' is possibly undefined
// 4E0C99: variable 'v11' is possibly undefined
// 4E0CFC: variable 'v14' is possibly undefined
// 4E0CFC: variable 'v15' is possibly undefined
// 48A1ED: using guessed type int __fastcall strncmp_(_DWORD, _DWORD);

//----- (004E0D20) --------------------------------------------------------
BOOL  Rules_IsInstanceSetQueryFunctionCall(int a1)
{
  int *( *v1)(int, double); // eax
  BOOL result; // eax

  result = 0;
  if ( *(_WORD *)a1 == 10 )
  {
    v1 = *(int *( **)(int, double))(*(_DWORD *)(a1 + 2) + 9);
    if ( v1 == InstanceQuery_AnyInstancep
      || (char *)v1 == (char *)InstanceQuery_FindInstance
      || (char *)v1 == (char *)InstanceQuery_FindAllInstances
      || (char *)v1 == (char *)InstanceQuery_DoForInstance
      || (char *)v1 == (char *)InstanceQuery_DoForAllInstances
      || (char *)v1 == (char *)InstanceQuery_DelayedDoForAllInstances )
    {
      return 1;
    }
  }
  return result;
}

//----- (004E0D60) --------------------------------------------------------
int Compiler_RegisterObjectPatternNetworkCodeGenerator()
{
  int result; // eax

  result = Rules_AddCodeGeneratorItem((int)aObjectPatterns, 0, (int)Compiler_WriteObjectPatternNetworkSetupCode, (int)Compiler_AssignObjectPatternAndRuleCodeIndices, (int)Compiler_WriteObjectPatternsAndRulesToCode, 2);
  g_ObjectPatternNetworkCodeGenItem = result;
  return result;
}
// 4E0DF0: using guessed type int sub_4E0DF0();
// 54E91C: using guessed type int dword_54E91C;

//----- (004E0D90) --------------------------------------------------------
int  Compiler_WriteObjectPatternSecondaryIndexRef(int a1, int a2, int a3)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( a1 )
    return Output_WriteFormatted(
             a3,
             *(_DWORD *)(*(_DWORD *)(g_ObjectPatternNetworkCodeGenItem + 20) + 4),
             a2,
             (int)aSD_DD_11,
             *(_DWORD *)(*(_DWORD *)(g_ObjectPatternNetworkCodeGenItem + 20) + 4));
  else
    return Output_WriteFormatted(a3, a2, a2, (int)aNull_33, v4);
}
// 4E0DA0: variable 'v4' is possibly undefined
// 54E91C: using guessed type int dword_54E91C;

//----- (004E0DF0) --------------------------------------------------------
int Compiler_AssignObjectPatternAndRuleCodeIndices()
{
  _DWORD *v0; // eax
  int i; // ecx
  int v2; // ecx
  int result; // eax
  int j; // edx

  v0 = (_DWORD *)Rules_GetObjectPatternNetworkRoot();
  for ( i = 0; v0; i = v2 + 1 )
  {
    v0[9] = i;
    v0 = Rules_GetNextObjectPatternNode(v0);
  }
  result = Rules_GetReactiveRuleList();
  for ( j = 0; result; ++j )
  {
    *(_DWORD *)(result + 40) = j;
    result = *(_DWORD *)(result + 36);
  }
  return result;
}
// 4E0E05: variable 'v2' is possibly undefined
// 4E0DF0: using guessed type int sub_4E0DF0();

//----- (004E0E40) --------------------------------------------------------
_DWORD * Rules_GetNextObjectPatternNode(_DWORD *result)
{
  if ( result[4] )
    return (_DWORD *)result[4];
  while ( !result[7] )
  {
    result = (_DWORD *)result[5];
    if ( !result )
      return result;
  }
  return (_DWORD *)result[7];
}

//----- (004E0E70) --------------------------------------------------------
int  Compiler_WriteObjectPatternNetworkSetupCode(int a1, int a2)
{
  int v3; // edx
  int v4; // ecx
  int v5; // eax
  int v6; // ecx
  int v8; // edx
  int v9; // ecx
  char v10; // [esp+0h] [ebp-Ch]
  char v11; // [esp+0h] [ebp-Ch]

  if ( Rules_GetObjectPatternNetworkRoot() )
  {
    Rules_GetObjectPatternNetworkRoot();
    v5 = Rules_GetReactiveRuleList();
    Output_WriteFormatted(*(_DWORD *)(v5 + 40), *(_DWORD *)(v5 + 40), a1, (int)aSetobjectnetwo, **(_DWORD **)(g_ObjectPatternNetworkCodeGenItem + 20));
    return Output_WriteFormatted(
             *(_DWORD *)(*(_DWORD *)(g_ObjectPatternNetworkCodeGenItem + 20) + 4),
             v6 % a2,
             a1,
             (int)aSetobjectnet_0,
             *(_DWORD *)(*(_DWORD *)(g_ObjectPatternNetworkCodeGenItem + 20) + 4));
  }
  else
  {
    Output_WriteFormatted(v4, v3, a1, (int)aSetobjectnet_1, v10);
    return Output_WriteFormatted(v9, v8, a1, (int)aSetobjectnet_2, v11);
  }
}
// 4E0ED3: variable 'v6' is possibly undefined
// 4E0EFD: variable 'v4' is possibly undefined
// 4E0EFD: variable 'v3' is possibly undefined
// 4E0EFD: variable 'v10' is possibly undefined
// 4E0F0B: variable 'v9' is possibly undefined
// 4E0F0B: variable 'v8' is possibly undefined
// 4E0F0B: variable 'v11' is possibly undefined
// 54E91C: using guessed type int dword_54E91C;

//----- (004E0F20) --------------------------------------------------------
int  Compiler_WriteObjectPatternsAndRulesToCode(const char *a1, int a2, DWORD a3, int a4, int a5)
{
  int result; // eax

  result = Compiler_WriteObjectPatternNodesToCode(a1, a2, a3, a4, a5, 1);
  if ( result )
  {
    result = Compiler_WriteReactiveRulesToCode(a1, a2, a3, a4, a5, result);
    if ( result )
      return 1;
  }
  return result;
}

//----- (004E0F80) --------------------------------------------------------
int  Compiler_WriteObjectPatternValueIndexRef(int a1, int a2, int a3)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( a1 )
    return Output_WriteFormatted(a3, **(_DWORD **)(g_ObjectPatternNetworkCodeGenItem + 20), a2, (int)aSD_DD_11, **(_DWORD **)(g_ObjectPatternNetworkCodeGenItem + 20));
  else
    return Output_WriteFormatted(a3, a2, a2, (int)aNull_33, v4);
}
// 4E0F90: variable 'v4' is possibly undefined
// 54E91C: using guessed type int dword_54E91C;

//----- (004E0FD0) --------------------------------------------------------
int  Compiler_WriteObjectPatternNodesToCode(const char *a1, char a2, DWORD a3, int a4, int a5, int a6)
{
  int v7; // edx
  int v8; // ecx
  int result; // eax
  int v10; // edx
  int v11; // esi
  int v12; // eax
  int v13; // edx
  int v14; // ecx
  _DWORD *v15; // edi
  int v16; // ecx
  int v17; // edx
  int v18; // ecx
  int v19; // edx
  int v20; // ecx
  int v21; // edx
  int v22; // ecx
  int v23; // edx
  int v24; // ecx
  int v25; // edx
  int v26; // edx
  int v27; // ecx
  _DWORD *v28; // eax
  int v29; // edx
  int v30; // ecx
  int v31; // eax
  int v33; // [esp+0h] [ebp-24h]
  char v34; // [esp+0h] [ebp-24h]
  char v35; // [esp+0h] [ebp-24h]
  char v36; // [esp+0h] [ebp-24h]
  char v37; // [esp+0h] [ebp-24h]
  char v38; // [esp+0h] [ebp-24h]
  char v39; // [esp+0h] [ebp-24h]
  int v41; // [esp+Ch] [ebp-18h]
  int v42; // [esp+10h] [ebp-14h]
  int v43; // [esp+14h] [ebp-10h]

  if ( !Rules_GetObjectPatternNetworkRoot() )
    return 1;
  Output_WriteFormatted(v8, v7, a4, (int)aIncludeObjrt_0, a2);
  result = Rules_OpenConstructCodeFile(a1, v10, a6, a3);
  v11 = result;
  if ( result )
  {
    v12 = Rules_GetObjectPatternNetworkRoot();
    v14 = 1;
    v15 = (_DWORD *)v12;
    v41 = 1;
    v43 = 1;
    v42 = 1;
    if ( v12 )
    {
      do
      {
        if ( v41 )
        {
          Output_WriteFormatted(**(_DWORD **)(g_ObjectPatternNetworkCodeGenItem + 20), v43, v11, (int)aObject_pattern, **(_DWORD **)(g_ObjectPatternNetworkCodeGenItem + 20));
          Output_WriteFormatted(a4, **(_DWORD **)(g_ObjectPatternNetworkCodeGenItem + 20), a4, (int)aExternObject_p, **(_DWORD **)(g_ObjectPatternNetworkCodeGenItem + 20));
          v41 = 0;
        }
        Output_WriteFormatted(v14, v13, v11, (int)a0UUUU0lU, (*v15 & 2) != 0);
        Rules_WriteExpressionRefToCode(v11, (__int16 *)v15[3], a5, a3);
        Output_WriteFormatted(v16, v11, v11, (int)asc_50E654, v33);
        Compiler_WriteObjectPatternValueIndexRef(v15[4], v17, a5);
        Output_WriteFormatted(v18, v11, v11, (int)asc_50E654, v34);
        Compiler_WriteObjectPatternValueIndexRef(v15[5], v19, a5);
        Output_WriteFormatted(v20, v11, v11, (int)asc_50E654, v35);
        Compiler_WriteObjectPatternValueIndexRef(v15[6], v21, a5);
        Output_WriteFormatted(v22, v11, v11, (int)asc_50E654, v36);
        Compiler_WriteObjectPatternValueIndexRef(v15[7], v23, a5);
        Output_WriteFormatted(v24, v11, v11, (int)asc_50E654, v37);
        Compiler_WriteObjectPatternSecondaryIndexRef(v15[8], v25, a5);
        Output_WriteFormatted(v27, v26, v11, (int)a0l_0, v38);
        v28 = Rules_GetNextObjectPatternNode(v15);
        v29 = v42 + 1;
        v15 = v28;
        v42 = v29;
        if ( v29 <= a5 && v28 )
        {
          Output_WriteFormatted(a5, v29, v11, (int)asc_50E664, v39);
        }
        else
        {
          Output_WriteFormatted(a5, v29, v11, (int)asc_50E660, v39);
          fclose_(v30);
          v42 = 1;
          v31 = a6 + 1;
          v13 = v43 + 1;
          ++a6;
          ++v43;
          if ( v15 )
          {
            result = Rules_OpenConstructCodeFile(a1, v33, v31, a3);
            v11 = result;
            if ( !result )
              return result;
            v41 = 1;
          }
        }
      }
      while ( v15 );
    }
    return a6;
  }
  return result;
}
// 4E11FD: conditional instruction was optimized away because eax.4!=0
// 4E1000: variable 'v8' is possibly undefined
// 4E1000: variable 'v7' is possibly undefined
// 4E1012: variable 'v10' is possibly undefined
// 4E10B8: variable 'v14' is possibly undefined
// 4E10B8: variable 'v13' is possibly undefined
// 4E10D8: variable 'v16' is possibly undefined
// 4E10D8: variable 'v33' is possibly undefined
// 4E10E7: variable 'v17' is possibly undefined
// 4E10F6: variable 'v18' is possibly undefined
// 4E10F6: variable 'v34' is possibly undefined
// 4E1105: variable 'v19' is possibly undefined
// 4E1114: variable 'v20' is possibly undefined
// 4E1114: variable 'v35' is possibly undefined
// 4E1123: variable 'v21' is possibly undefined
// 4E1132: variable 'v22' is possibly undefined
// 4E1132: variable 'v36' is possibly undefined
// 4E1141: variable 'v23' is possibly undefined
// 4E1150: variable 'v24' is possibly undefined
// 4E1150: variable 'v37' is possibly undefined
// 4E115F: variable 'v25' is possibly undefined
// 4E116A: variable 'v27' is possibly undefined
// 4E116A: variable 'v26' is possibly undefined
// 4E116A: variable 'v38' is possibly undefined
// 4E1192: variable 'v39' is possibly undefined
// 4E11A1: variable 'v30' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 54E91C: using guessed type int dword_54E91C;

//----- (004E1210) --------------------------------------------------------
int  Compiler_WriteReactiveRulesToCode(const char *a1, int a2, DWORD a3, int a4, int a5, int a6)
{
  int v7; // edx
  int result; // eax
  int v9; // esi
  int v10; // ecx
  int *v11; // edi
  int v12; // edx
  int v13; // edx
  int v14; // ecx
  int v15; // ecx
  int v16; // edx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // edx
  int v21; // ecx
  int v22; // edx
  int v23; // ecx
  int v24; // edx
  int v25; // edx
  int v26; // ecx
  int v27; // ecx
  int v28; // ebx
  int v29; // [esp+0h] [ebp-24h]
  char v30; // [esp+0h] [ebp-24h]
  char v31; // [esp+0h] [ebp-24h]
  char v32; // [esp+0h] [ebp-24h]
  char v33; // [esp+0h] [ebp-24h]
  char v34; // [esp+0h] [ebp-24h]
  char v35; // [esp+0h] [ebp-24h]
  char v36; // [esp+0h] [ebp-24h]
  int v39; // [esp+Ch] [ebp-18h]
  int v40; // [esp+10h] [ebp-14h]
  int v41; // [esp+14h] [ebp-10h]

  v29 = a4;
  if ( !Rules_GetReactiveRuleList() )
    return a6;
  result = Rules_OpenConstructCodeFile(a1, v7, a6, a3);
  v9 = result;
  if ( result )
  {
    v11 = (int *)Rules_GetReactiveRuleList();
    v39 = 1;
    v40 = 1;
    v41 = 1;
    if ( !v11 )
      return a6;
    do
    {
      if ( v39 )
      {
        Output_WriteFormatted(
          *(_DWORD *)(*(_DWORD *)(g_ObjectPatternNetworkCodeGenItem + 20) + 4),
          v40,
          v9,
          (int)aObject_alpha_n,
          *(_DWORD *)(*(_DWORD *)(g_ObjectPatternNetworkCodeGenItem + 20) + 4));
        Output_WriteFormatted(
          v29,
          *(_DWORD *)(*(_DWORD *)(g_ObjectPatternNetworkCodeGenItem + 20) + 4),
          v29,
          (int)aExternObject_a,
          *(_DWORD *)(*(_DWORD *)(g_ObjectPatternNetworkCodeGenItem + 20) + 4));
        v39 = 0;
      }
      Output_WriteFormatted(v10, (int)v11, v9, (int)asc_50E6B4, v29);
      Rules_PrintPatternNetworkNodeTrace(v9, v12, a5);
      Output_WriteFormatted(v14, v13, v9, (int)a0l_1, v30);
      Compiler_WriteBitMapReference(v9, v11[5], v15);
      Output_WriteFormatted(v17, v16, v9, (int)asc_50E654, v31);
      Compiler_WriteBitMapReference(v9, v11[6], v18);
      Output_WriteFormatted(v19, v9, v9, (int)asc_50E654, v32);
      Compiler_WriteObjectPatternValueIndexRef(v11[7], v20, a5);
      Output_WriteFormatted(v21, v9, v9, (int)asc_50E654, v33);
      Compiler_WriteObjectPatternSecondaryIndexRef(v11[8], v22, a5);
      Output_WriteFormatted(v23, v9, v9, (int)asc_50E654, v34);
      Compiler_WriteObjectPatternSecondaryIndexRef(v11[9], v24, a5);
      Output_WriteFormatted(v26, v25, v9, (int)a0l_0, v35);
      v11 = (int *)v11[9];
      if ( ++v41 <= a5 && v11 )
      {
        Output_WriteFormatted(v27, a5, v9, (int)asc_50E664, v36);
      }
      else
      {
        Output_WriteFormatted(v27, a5, v9, (int)asc_50E660, v36);
        fclose_(1);
        v41 = v10;
        v28 = v10 + a6;
        a6 += v10;
        v40 += v10;
        if ( v11 )
        {
          result = Rules_OpenConstructCodeFile(a1, a2, v28, a3);
          v9 = result;
          if ( !result )
            return result;
          v39 = 1;
        }
      }
    }
    while ( v11 );
    return a6;
  }
  return result;
}
// 4E13F0: conditional instruction was optimized away because edi.4!=0
// 4E1243: variable 'v7' is possibly undefined
// 4E12AB: variable 'v29' is possibly undefined
// 4E12C1: variable 'v10' is possibly undefined
// 4E12CF: variable 'v12' is possibly undefined
// 4E12DA: variable 'v14' is possibly undefined
// 4E12DA: variable 'v13' is possibly undefined
// 4E12DA: variable 'v30' is possibly undefined
// 4E12E7: variable 'v15' is possibly undefined
// 4E12F2: variable 'v17' is possibly undefined
// 4E12F2: variable 'v16' is possibly undefined
// 4E12F2: variable 'v31' is possibly undefined
// 4E12FF: variable 'v18' is possibly undefined
// 4E130E: variable 'v19' is possibly undefined
// 4E130E: variable 'v32' is possibly undefined
// 4E131D: variable 'v20' is possibly undefined
// 4E132C: variable 'v21' is possibly undefined
// 4E132C: variable 'v33' is possibly undefined
// 4E133B: variable 'v22' is possibly undefined
// 4E134A: variable 'v23' is possibly undefined
// 4E134A: variable 'v34' is possibly undefined
// 4E1359: variable 'v24' is possibly undefined
// 4E1364: variable 'v26' is possibly undefined
// 4E1364: variable 'v25' is possibly undefined
// 4E1364: variable 'v35' is possibly undefined
// 4E1386: variable 'v27' is possibly undefined
// 4E1386: variable 'v36' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 54E91C: using guessed type int dword_54E91C;

//----- (004E1410) --------------------------------------------------------
int __fastcall Rules_BuildSlotBoundTestNode(int a1, int a2)
{
  return Rules_BuildSlotConstraintBitmapTestNode(1, a2);
}

//----- (004E1430) --------------------------------------------------------
int  Rules_BuildSlotBoundTestExpression(int a1)
{
  int v2; // ecx

  AST_NewNode(0, 0);
  Rules_BuildSlotConstraintBitmapTestNode(1, a1);
  return v2;
}
// 4E144C: variable 'v2' is possibly undefined

//----- (004E1460) --------------------------------------------------------
signed int  Rules_BuildSlotRangeTestNode(int a1, int a2)
{
  return Rules_BuildDualSlotConstraintBitmapTestNode(1, a1, a2);
}

//----- (004E1480) --------------------------------------------------------
signed int Rules_BuildMultifieldIndexTestNode()
{
  int v0; // ecx
  int v1; // esi
  int v2; // eax
  signed int v3; // edi
  _DWORD *v4; // ecx
  int v6; // eax
  signed int v7; // edi
  int *v8; // ecx
  int v9; // ebp
  _DWORD *v10; // ecx
  int v11; // edx
  unsigned int v12; // eax
  _DWORD v13[7]; // [esp+0h] [ebp-1Ch] BYREF

  Mem_AllocArray(v13, 4);
  if ( (*(_BYTE *)(v0 + 8) & 1) != 0 )
    BYTE1(v13[0]) |= 1u;
  else
    LOBYTE(v13[0]) |= 0x80u;
  if ( (*(_BYTE *)(v0 + 9) & 0x40) != 0 && (*(_WORD *)(v0 + 10) & 0x1FC0) != 0 && (*(_DWORD *)(v0 + 8) & 0x3F8000) != 0
    || *(_DWORD *)(v0 + 40) < 2u )
  {
    BYTE1(v13[0]) |= 2u;
    v6 = Rules_AddBitmapValue(v13, 4);
    v7 = AST_NewNode(50, v6);
    *(_DWORD *)(v7 + 6) = AST_NewNode(0, 0);
    v9 = *v8;
    *v8 = 15;
    Rules_BuildSlotConstraintBitmapTestNode(0, (int)v8);
    v11 = v10[1];
    *v10 = v9;
    *(_DWORD *)(*(_DWORD *)(v7 + 6) + 10) = AST_NewNode(v9, v11);
    return v7;
  }
  else
  {
    v1 = v13[0] | 0x400;
    if ( (*(_BYTE *)(v0 + 9) & 0x40) != 0 )
    {
      if ( (*(_DWORD *)(v0 + 8) & 0x3F8000) != 0 )
      {
        v12 = *(_DWORD *)(v0 + 12) << 18;
        LOBYTE(v13[0]) &= 0x80u;
        v13[0] |= v12 >> 25;
      }
      else
      {
        v13[0] |= 0x400u;
        LOWORD(v1) = v1 & 0xFF80;
        v13[0] = *(_DWORD *)(v0 + 12) & 0x7F | v1;
      }
    }
    else
    {
      v13[0] |= 0x400u;
    }
    v2 = Rules_AddBitmapValue(v13, 4);
    v3 = AST_NewNode(50, v2);
    *(_DWORD *)(v3 + 6) = AST_NewNode(*v4, v4[1]);
    return v3;
  }
}
// 4E14AC: simplified comparisons for 'ebx.4': ==0 || ==1 became <2u
// 4E1497: variable 'v0' is possibly undefined
// 4E14E8: variable 'v4' is possibly undefined
// 4E154B: variable 'v8' is possibly undefined
// 4E155F: variable 'v10' is possibly undefined

//----- (004E15D0) --------------------------------------------------------
int __fastcall mblen_(int a1, int a2)
{
  (void)a2;
  return Rules_BuildSlotConstraintBitmapTestNode(0, a1);
}

//----- (004E15E0) --------------------------------------------------------
int  Rules_BuildSlotUnboundTestExpression(int a1)
{
  int v2; // ecx

  AST_NewNode(0, 0);
  Rules_BuildSlotConstraintBitmapTestNode(0, a1);
  return v2;
}
// 4E15F9: variable 'v2' is possibly undefined

//----- (004E1600) --------------------------------------------------------
int __fastcall mblen__0(int a1, int a2)
{
  return Rules_BuildDualSlotConstraintBitmapTestNode(0, a1, a2);
}

//----- (004E1610) --------------------------------------------------------
_DWORD * Rules_AppendFieldCardinalityBitmapTest(_DWORD *result)
{
  int v1; // ecx
  int v2; // eax
  int v3; // eax
  _DWORD *v4; // eax
  int v5; // ecx
  int v6; // ecx
  unsigned int v7; // eax
  _DWORD v8[4]; // [esp+0h] [ebp-10h] BYREF

  if ( (result[3] & 0x3F80) != 0 || *result == 15 || *result == 17 )
  {
    Mem_AllocArray(v8, 4);
    if ( *(_DWORD *)v1 == 16 || *(_DWORD *)v1 == 18 || (*(_WORD *)(v1 + 10) & 0x1FC0) != 0 )
      BYTE1(v8[0]) &= ~0x80u;
    else
      BYTE1(v8[0]) |= 0x80u;
    if ( *(_DWORD *)v1 == 15 || *(_DWORD *)v1 == 17 )
    {
      v2 = *(_DWORD *)(v1 + 12) << 18 >> 25;
      LOWORD(v8[0]) &= 0x8000u;
      v8[0] |= ((_WORD)v2 + 1) & 0x7FFF;
    }
    else
    {
      v7 = *(_DWORD *)(v1 + 12) << 18;
      LOWORD(v8[0]) &= 0x8000u;
      v8[0] |= (v7 >> 25) & 0x7FFF;
    }
    v3 = Rules_AddBitmapValue(v8, 4);
    v4 = (_DWORD *)AST_NewNode(49, v3);
    result = AST_MergeFieldAccessNodes(v4, *(_DWORD **)(v5 + 52));
    *(_DWORD *)(v6 + 52) = result;
  }
  return result;
}
// 4E163F: variable 'v1' is possibly undefined
// 4E16A9: variable 'v5' is possibly undefined
// 4E16B1: variable 'v6' is possibly undefined

//----- (004E1700) --------------------------------------------------------
_DWORD *__fastcall Rules_AppendMultifieldWildcardBitmapTest(int a1, int a2)
{
  int v2; // eax
  _DWORD *v3; // eax
  int v4; // ecx
  _DWORD *result; // eax
  int v6; // ecx
  _WORD v7[4]; // [esp+0h] [ebp-Ch] BYREF
  int v8; // [esp+8h] [ebp-4h]

  v8 = a1;
  Mem_AllocArray(v7, 4);
  HIBYTE(v7[0]) |= 0x80u;
  v7[0] &= 0x8000u;
  v2 = Rules_AddBitmapValue(v7, 4);
  v3 = (_DWORD *)AST_NewNode(49, v2);
  result = AST_MergeFieldAccessNodes(v3, *(_DWORD **)(v4 + 52));
  *(_DWORD *)(v6 + 52) = result;
  return result;
}
// 4E173C: variable 'v4' is possibly undefined
// 4E1744: variable 'v6' is possibly undefined

//----- (004E1750) --------------------------------------------------------
int  Rules_BuildSlotConstraintBitmapTestNode(int a1, int a2)
{
  __int16 *v3; // ecx
  int v4; // eax
  __int16 v5; // ax
  int result; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  __int16 v12; // ax
  int v13; // ecx
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  unsigned int v20; // [esp+0h] [ebp-20h] BYREF
  char v21; // [esp+4h] [ebp-1Ch]
  int v22; // [esp+8h] [ebp-18h] BYREF
  int v23; // [esp+Ch] [ebp-14h]

  Mem_AllocArray(&v20, 8);
  Mem_AllocArray(&v22, 8);
  if ( a1 )
  {
    v20 = ((unsigned __int8)*(_DWORD *)(a2 + 28) << 15) | v20 & 0xFF807FFF;
    v8 = *(_DWORD *)(a2 + 28);
    LOBYTE(v23) = 0;
    v23 |= (unsigned __int8)v8;
  }
  if ( *(int *)(a2 + 40) < 0 )
  {
    HIBYTE(v20) |= 0x80u;
    if ( !a1 )
      goto LABEL_13;
    goto LABEL_10;
  }
  if ( (*(_BYTE *)(a2 + 12) & 0x7F) == 0
    && (*(_WORD *)(a2 + 12) & 0x3F80) == 0
    && (*(_DWORD *)(a2 + 8) & 0x3F8000) == 0
    && (*(_WORD *)(a2 + 10) & 0x1FC0) == 0
    && ((*(_BYTE *)(a2 + 9) & 0x40) == 0 || *(_DWORD *)a2 == 16 || *(_DWORD *)a2 == 18) )
  {
    v21 |= 1u;
    v4 = *(_DWORD *)(a2 + 40);
    LOWORD(v20) = v20 & 0x8000;
    v20 |= v4 & 0x7FFF;
    if ( !a1 )
      goto LABEL_13;
LABEL_10:
    v5 = 47;
LABEL_11:
    *v3 = v5;
    result = Rules_AddBitmapValue(&v20, 8);
    *(_DWORD *)(v7 + 2) = result;
    return result;
  }
  if ( (*(_DWORD *)a2 == 17 || *(_DWORD *)a2 == 15)
    && ((*(_DWORD *)(a2 + 8) & 0x3F8000) == 0 || (*(_WORD *)(a2 + 10) & 0x1FC0) == 0) )
  {
    v9 = *(_DWORD *)(a2 + 40);
    LOWORD(v22) = v22 & 0x8000;
    v22 |= v9 & 0x7FFF;
    if ( (*(_DWORD *)(a2 + 8) & 0x3F8000) != 0 )
    {
      BYTE2(v22) |= 0x80u;
      v17 = *(_DWORD *)(a2 + 12) << 18 >> 25;
      HIBYTE(v22) &= 0x80u;
      v11 = (v17 & 0x7F) << 24;
    }
    else
    {
      BYTE1(v22) |= 0x80u;
      v10 = *(_DWORD *)(a2 + 12);
      BYTE2(v22) &= 0x80u;
      v11 = (v10 & 0x7F) << 16;
    }
    v22 |= v11;
    if ( a1 )
      v12 = 48;
    else
      v12 = 46;
    goto LABEL_22;
  }
  if ( *(_DWORD *)a2 != 18 && *(_DWORD *)a2 != 16
    || (*(_DWORD *)(a2 + 8) & 0x3F8000) != 0
    || (*(_WORD *)(a2 + 10) & 0x1FC0) != 0 )
  {
    v18 = *(_DWORD *)(a2 + 40);
    LOWORD(v20) = v20 & 0x8000;
    v20 |= v18 & 0x7FFF;
    v19 = (unsigned __int8)*(_DWORD *)(a2 + 32);
    HIWORD(v20) &= 0x807Fu;
    v20 |= v19 << 23;
    if ( a1 )
      goto LABEL_10;
LABEL_13:
    v5 = 45;
    goto LABEL_11;
  }
  v14 = *(_DWORD *)(a2 + 40);
  LOWORD(v22) = v22 & 0x8000;
  v22 |= v14 & 0x7FFF | 0x808000;
  v15 = *(_DWORD *)(a2 + 12) & 0x7F;
  BYTE2(v22) &= 0x80u;
  v22 |= v15 << 16;
  v16 = *(_DWORD *)(a2 + 12) << 18 >> 25;
  HIBYTE(v22) &= 0x80u;
  v22 |= (v16 & 0x7F) << 24;
  if ( a1 )
    v12 = 48;
  else
    v12 = 46;
LABEL_22:
  *v3 = v12;
  result = Rules_AddBitmapValue(&v22, 8);
  *(_DWORD *)(v13 + 2) = result;
  return result;
}
// 4E17EA: variable 'v3' is possibly undefined
// 4E17F4: variable 'v7' is possibly undefined
// 4E18CE: variable 'v13' is possibly undefined

//----- (004E1A40) --------------------------------------------------------
BOOL  Rules_IsMultiplyConstrainedSlot(int a1)
{
  return *(_DWORD *)a1 != 18
      && *(_DWORD *)a1 != 16
      && *(int *)(a1 + 40) >= 2
      && ((*(_BYTE *)(a1 + 9) & 0x40) == 0
       || (*(_BYTE *)(a1 + 8) & 4) == 0
       && ((*(_DWORD *)(a1 + 8) & 0x3F8000) == 0 || (*(_WORD *)(a1 + 10) & 0x1FC0) == 0));
}
// 4E1A53: simplified comparisons for 'ebx.4': <0 || ==0 became <1
// 4E1A53: simplified comparisons for 'ebx.4': <1 || ==1 became <2

//----- (004E1A90) --------------------------------------------------------
signed int  Rules_BuildDualSlotConstraintBitmapTestNode(int a1, int a2, int a3)
{
  int v5; // ecx
  int v6; // edx
  signed int v7; // ebp
  int v8; // ecx
  int v10; // edx
  int v11; // ecx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // ecx
  unsigned int v21; // ebp
  int v22; // eax
  unsigned int v23; // edx
  int v24; // edx
  int v25; // edx
  int v26; // eax
  unsigned int v27; // edx
  int v28; // eax
  int v29; // eax
  int v30; // eax
  int v31; // eax
  int v32; // edx
  int v33; // edx
  int v34; // eax
  int v35; // eax
  int v36; // eax
  int v37; // ecx
  int v38; // eax
  int v39; // eax
  int v40; // eax
  int v41; // eax
  int v42; // eax
  int v43; // ebx
  int v44; // eax
  int v45; // eax
  int v46; // eax
  int v47; // eax
  int v48; // eax
  int v49; // eax
  int v50; // eax
  int v51; // [esp+0h] [ebp-3Ch] BYREF
  int v52; // [esp+4h] [ebp-38h]
  int v53; // [esp+8h] [ebp-34h] BYREF
  int v54; // [esp+Ch] [ebp-30h]
  int v55; // [esp+10h] [ebp-2Ch] BYREF
  int v56; // [esp+14h] [ebp-28h]
  int v57; // [esp+18h] [ebp-24h] BYREF
  int v58; // [esp+1Ch] [ebp-20h]
  int v59; // [esp+20h] [ebp-1Ch] BYREF
  int v60; // [esp+24h] [ebp-18h]
  _DWORD v61[5]; // [esp+28h] [ebp-14h] BYREF

  if ( Rules_IsMultiplyConstrainedSlot(a2) && Rules_IsMultiplyConstrainedSlot(a3) )
  {
    if ( (*(_BYTE *)(v10 + 9) & 0x40) == 0 && (*(_BYTE *)(a3 + 9) & 0x40) == 0 )
    {
      Mem_AllocArray(v61, 4);
      Mem_AllocArray(&v51, 8);
      if ( (*(_BYTE *)(v11 + 8) & 1) != 0 )
      {
        HIBYTE(v51) |= 0x80u;
        HIBYTE(v61[0]) = HIBYTE(v61[0]) & 0x7F | 0x80;
      }
      else
      {
        BYTE1(v51) |= 0x80u;
        BYTE1(v61[0]) = BYTE1(v61[0]) & 0x7F | 0x80;
      }
      v12 = *(_DWORD *)(v11 + 40);
      LOWORD(v51) = v51 & 0x8000;
      v51 |= v12 & 0x7FFF;
      v13 = *(_DWORD *)(v11 + 40);
      LOWORD(v61[0]) &= 0x8000u;
      v61[0] |= v13 & 0x7FFF;
      v14 = *(_DWORD *)(a3 + 40);
      HIWORD(v51) &= 0x8000u;
      v51 |= (v14 & 0x7FFF) << 16;
      v15 = *(_DWORD *)(a3 + 40);
      HIWORD(v61[0]) &= 0x8000u;
      v61[0] |= (v15 & 0x7FFF) << 16;
      if ( a1 )
      {
        v16 = *(_DWORD *)(v11 + 28);
        LOBYTE(v52) = 0;
        v52 |= (unsigned __int8)v16;
        v17 = *(_DWORD *)(a3 + 28);
        BYTE1(v52) = 0;
        v52 |= (unsigned __int8)v17 << 8;
        v18 = Rules_AddBitmapValue(&v51, 8);
        return AST_NewNode(52, v18);
      }
      else
      {
        v19 = Rules_AddBitmapValue(v61, 4);
        return AST_NewNode(51, v19);
      }
    }
    if ( (*(_BYTE *)(v5 + 9) & 0x40) == 0 || (*(_BYTE *)(a3 + 9) & 0x40) == 0 )
    {
      Mem_AllocArray(&v53, 8);
      Mem_AllocArray(&v57, 8);
      if ( (*(_BYTE *)(v20 + 8) & 1) != 0 )
      {
        BYTE2(v58) |= 0x80u;
        HIBYTE(v53) = HIBYTE(v53) & 0x7F | 0x80;
      }
      else
      {
        BYTE1(v57) |= 0x80u;
        BYTE1(v53) = BYTE1(v53) & 0x7F | 0x80;
      }
      v22 = v58;
      v21 = v57 & 0xFFFF8000;
      v23 = v53 & 0xFFFF8000;
      LOBYTE(v22) = 0;
      if ( (*(_BYTE *)(v20 + 9) & 0x40) != 0 )
      {
        v57 = v21 | *(_DWORD *)(v20 + 40) & 0x7FFF;
        v53 = *(_DWORD *)(v20 + 40) & 0x7FFF | v23;
        v24 = *(_DWORD *)(a3 + 40);
        HIWORD(v57) &= 0x8000u;
        v57 |= (v24 & 0x7FFF) << 16;
        v25 = *(_DWORD *)(a3 + 40);
        HIWORD(v53) &= 0x8000u;
        v53 |= (v25 & 0x7FFF) << 16;
        if ( a1 )
        {
          v58 = (unsigned __int8)*(_DWORD *)(v20 + 28) | v22;
          v26 = *(_DWORD *)(a3 + 28);
          BYTE1(v58) = 0;
          v58 |= (unsigned __int8)v26 << 8;
        }
        v27 = v58 & 0xFF80FFFF;
        if ( (*(_DWORD *)(v20 + 8) & 0x3F8000) != 0 )
        {
          v30 = (unsigned __int8)(*(_DWORD *)(v20 + 12) << 18 >> 24) >> 1;
          LOBYTE(v54) = v54 & 0x80;
          v58 = (v30 << 16) | v27;
          goto LABEL_24;
        }
        HIBYTE(v57) |= 0x80u;
        LOBYTE(v54) = v54 & 0x7F | 0x80;
        v28 = *(_DWORD *)(v20 + 12);
      }
      else
      {
        v57 = v21 | *(_DWORD *)(a3 + 40) & 0x7FFF;
        v53 = *(_DWORD *)(a3 + 40) & 0x7FFF | v23;
        v32 = *(_DWORD *)(v20 + 40);
        HIWORD(v57) &= 0x8000u;
        v57 |= (v32 & 0x7FFF) << 16;
        v33 = *(_DWORD *)(v20 + 40) & 0x7FFF;
        HIWORD(v53) &= 0x8000u;
        v53 |= v33 << 16;
        if ( a1 )
        {
          v58 = (unsigned __int8)*(_DWORD *)(a3 + 28) | v22;
          v34 = *(_DWORD *)(v20 + 28);
          BYTE1(v58) = 0;
          v58 |= (unsigned __int8)v34 << 8;
        }
        v27 = v58 & 0xFF80FFFF;
        if ( (*(_DWORD *)(a3 + 8) & 0x3F8000) != 0 )
        {
          v35 = (unsigned __int8)(*(_DWORD *)(a3 + 12) << 18 >> 24) >> 1;
          LOBYTE(v54) = v54 & 0x80;
          v58 = (v35 << 16) | v27;
          v54 |= v35;
LABEL_25:
          if ( a1 )
          {
            v31 = Rules_AddBitmapValue(&v57, 8);
            return AST_NewNode(54, v31);
          }
          else
          {
            v36 = Rules_AddBitmapValue(&v53, 8);
            return AST_NewNode(53, v36);
          }
        }
        HIBYTE(v57) |= 0x80u;
        LOBYTE(v54) = v54 & 0x7F | 0x80;
        v28 = *(_DWORD *)(a3 + 12);
      }
      v29 = v28 & 0x7F;
      v58 = (v29 << 16) | v27;
      LOBYTE(v54) = v54 & 0x80;
      v30 = v29 & 0x7F;
LABEL_24:
      v54 |= v30;
      goto LABEL_25;
    }
    Mem_AllocArray(&v55, 8);
    Mem_AllocArray(&v59, 8);
    if ( (*(_BYTE *)(v37 + 8) & 1) != 0 )
    {
      HIBYTE(v59) |= 0x80u;
      HIBYTE(v55) = HIBYTE(v55) & 0x7F | 0x80;
    }
    else
    {
      BYTE1(v59) |= 0x80u;
      BYTE1(v55) = BYTE1(v55) & 0x7F | 0x80;
    }
    v38 = *(_DWORD *)(v37 + 40);
    LOWORD(v59) = v59 & 0x8000;
    v59 |= v38 & 0x7FFF;
    v39 = *(_DWORD *)(v37 + 40);
    LOWORD(v55) = v55 & 0x8000;
    v55 |= v39 & 0x7FFF;
    v40 = *(_DWORD *)(a3 + 40);
    HIWORD(v59) &= 0x8000u;
    v59 |= (v40 & 0x7FFF) << 16;
    v41 = *(_DWORD *)(a3 + 40);
    HIWORD(v55) &= 0x8000u;
    v55 |= (v41 & 0x7FFF) << 16;
    if ( (*(_DWORD *)(v37 + 8) & 0x3F8000) != 0 )
    {
      v44 = (unsigned __int8)(*(_DWORD *)(v37 + 12) << 18 >> 24) >> 1;
      BYTE2(v60) &= 0x80u;
      LOBYTE(v56) = v56 & 0x80;
      v60 |= v44 << 16;
    }
    else
    {
      BYTE2(v60) |= 0x80u;
      LOBYTE(v56) = v56 & 0x7F | 0x80;
      v42 = *(_DWORD *)(v37 + 12) & 0x7F;
      BYTE2(v60) &= 0x80u;
      v43 = (v42 << 16) | v60;
      LOBYTE(v56) = v56 & 0x80;
      v44 = v42 & 0x7F;
      v60 = v43;
    }
    v56 |= v44;
    if ( (*(_DWORD *)(a3 + 8) & 0x3F8000) != 0 )
    {
      v46 = (unsigned __int8)(*(_DWORD *)(a3 + 12) << 18 >> 24) >> 1;
      HIBYTE(v60) &= 0x80u;
      v60 |= v46 << 24;
    }
    else
    {
      HIBYTE(v60) |= 0x80u;
      BYTE1(v56) = BYTE1(v56) & 0x7F | 0x80;
      v45 = *(_DWORD *)(a3 + 12) & 0x7F;
      HIBYTE(v60) &= 0x80u;
      v60 |= v45 << 24;
      v46 = v45 & 0x7F;
    }
    BYTE1(v56) &= 0x80u;
    v56 |= v46 << 8;
    if ( a1 )
    {
      v47 = *(_DWORD *)(v37 + 28);
      LOBYTE(v60) = 0;
      v60 |= (unsigned __int8)v47;
      v48 = *(_DWORD *)(a3 + 28);
      BYTE1(v60) = 0;
      v60 |= (unsigned __int8)v48 << 8;
      v49 = Rules_AddBitmapValue(&v59, 8);
      return AST_NewNode(56, v49);
    }
    else
    {
      v50 = Rules_AddBitmapValue(&v55, 8);
      return AST_NewNode(55, v50);
    }
  }
  else
  {
    if ( (*(_BYTE *)(v5 + 8) & 1) != 0 )
      v6 = g_ClipsSymbolNeq;
    else
      v6 = g_ClipsSymbolEq;
    v7 = AST_NewNode(10, v6);
    *(_DWORD *)(v7 + 6) = AST_NewNode(0, 0);
    Rules_BuildSlotConstraintBitmapTestNode(a1, v8);
    *(_DWORD *)(*(_DWORD *)(v7 + 6) + 10) = AST_NewNode(0, 0);
    Rules_BuildSlotConstraintBitmapTestNode(a1, a3);
    return v7;
  }
}
// 4E1AA8: variable 'v5' is possibly undefined
// 4E1AD8: variable 'v8' is possibly undefined
// 4E1B14: variable 'v10' is possibly undefined
// 4E1B42: variable 'v11' is possibly undefined
// 4E1CA8: variable 'v20' is possibly undefined
// 4E1F83: variable 'v37' is possibly undefined
// 54E658: using guessed type int dword_54E658;
// 54E668: using guessed type int dword_54E668;

//----- (004E2200) --------------------------------------------------------
signed int Rules_RegisterObjectPatternNetworkBinaryItem()
{
  return Rules_RegisterBinaryItem(
           (int)aObjectPatter_0,
           0,
           0,
           (int)Rules_AssignObjectPatternNetworkBsaveIndices,
           (int)Rules_BsaveObjectPatternNetworkCounts,
           (int)Rules_BsaveObjectPatternNetworkRecords,
           (int)Rules_BloadObjectPatternNetworkCounts,
           (int)Rules_BloadObjectPatternNetworkRecords,
           (int)Class_ClearClassIDTable);
}

//----- (004E2240) --------------------------------------------------------
_DWORD *Rules_AssignObjectPatternNetworkBsaveIndices()
{
  _DWORD *i; // eax
  int v1; // ebx
  int v2; // edx
  _DWORD *result; // eax
  int v4; // edx
  _DWORD *v5; // esi

  if ( Rules_IsBloaded() )
  {
    Rules_ConstructQueuePush(g_ReactiveRuleBloadCount);
    Rules_ConstructQueuePush(g_ObjectPatternNetworkBloadCount);
  }
  g_ReactiveRuleBloadCount = 0;
  for ( i = (_DWORD *)Rules_GetReactiveRuleList(); i; i = (_DWORD *)i[9] )
  {
    *(_BYTE *)(i[5] + 12) |= 2u;
    v1 = i[6];
    if ( v1 )
      *(_BYTE *)(i[6] + 12) = *(_BYTE *)(v1 + 12) | 2;
    v2 = g_ReactiveRuleBloadCount++;
    i[10] = v2;
  }
  g_ObjectPatternNetworkBloadCount = 0;
  result = (_DWORD *)Rules_GetObjectPatternNetworkRoot();
  if ( result )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        v4 = g_ObjectPatternNetworkBloadCount++;
        v5 = (_DWORD *)result[4];
        result[9] = v4;
        if ( !v5 )
          break;
        result = v5;
      }
      while ( !result[7] )
      {
        result = (_DWORD *)result[5];
        if ( !result )
          return result;
      }
      result = (_DWORD *)result[7];
    }
  }
  return result;
}
// 51C718: using guessed type int dword_51C718;
// 51C71C: using guessed type int dword_51C71C;

//----- (004E2300) --------------------------------------------------------
const void * Rules_BsaveObjectPatternNetworkCounts(int a1, int a2)
{
  int v2; // ecx
  int v3; // ecx
  _DWORD v5[4]; // [esp+0h] [ebp-10h] BYREF

  v5[2] = a2;
  v5[0] = 8;
  Rules_BsaveWriteBlock(4, a1, v5);
  Rules_BsaveWriteBlock(4, v2, &g_ReactiveRuleBloadCount);
  return Rules_BsaveWriteBlock(4, v3, &g_ObjectPatternNetworkBloadCount);
}
// 4E232A: variable 'v2' is possibly undefined
// 4E233B: variable 'v3' is possibly undefined
// 51C718: using guessed type int dword_51C718;
// 51C71C: using guessed type int dword_51C71C;

//----- (004E2350) --------------------------------------------------------
const void * Rules_BsaveObjectPatternNetworkRecords(int a1)
{
  int i; // ecx
  _DWORD *v3; // ecx
  int v4; // edx
  int v5; // edi
  int v6; // eax
  int v7; // ebp
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // ecx
  unsigned int v13; // eax
  int v14; // eax
  int v15; // eax
  _DWORD *v16; // ecx
  int v17; // ebx
  int v18; // eax
  int v19; // edi
  int v20; // eax
  int v21; // ebp
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // edx
  int v26; // eax
  const void *result; // eax
  _DWORD *v28; // ecx
  _DWORD v29[8]; // [esp+0h] [ebp-58h] BYREF
  _BYTE v30[8]; // [esp+20h] [ebp-38h] BYREF
  int v31; // [esp+28h] [ebp-30h]
  int v32; // [esp+2Ch] [ebp-2Ch]
  int v33; // [esp+30h] [ebp-28h]
  int v34; // [esp+34h] [ebp-24h]
  int v35; // [esp+38h] [ebp-20h]
  int v36[7]; // [esp+3Ch] [ebp-1Ch] BYREF

  v36[0] = 32 * g_ObjectPatternNetworkBloadCount + 28 * g_ReactiveRuleBloadCount;
  Rules_BsaveWriteBlock(4, a1, v36);
  for ( i = Rules_GetReactiveRuleList(); i; i = *(_DWORD *)(v11 + 36) )
  {
    Rules_BsavePackSharedRecordHeader((int)v30, i);
    v31 = *(_DWORD *)(v3[5] + 12) << 16 >> 18;
    v4 = v3[6];
    if ( v4 )
      v32 = *(_DWORD *)(v4 + 12) << 16 >> 18;
    else
      v32 = -1;
    v5 = v3[7];
    if ( v5 )
      v6 = *(_DWORD *)(v5 + 36);
    else
      v6 = -1;
    v33 = v6;
    v7 = v3[8];
    if ( v7 )
      v8 = *(_DWORD *)(v7 + 40);
    else
      v8 = -1;
    v34 = v8;
    v9 = v3[9];
    if ( v9 )
      v10 = *(_DWORD *)(v9 + 40);
    else
      v10 = -1;
    v35 = v10;
    Rules_BsaveWriteBlock(28, a1, v30);
  }
  v12 = Rules_GetObjectPatternNetworkRoot();
  while ( v12 )
  {
    v13 = *(_DWORD *)v12 << 30;
    LOBYTE(v29[0]) &= ~1u;
    v29[0] |= v13 >> 31;
    v14 = *(_DWORD *)v12 << 21 >> 24;
    LOWORD(v29[0]) &= 0xFC03u;
    v29[0] |= 4 * (unsigned __int8)v14;
    v29[0] = ((unsigned __int8)(*(_DWORD *)v12 << 13 >> 24) << 10) | v29[0] & 0xFFFC03FF;
    v15 = *(_DWORD *)v12 << 29 >> 31;
    LOBYTE(v29[0]) &= ~2u;
    v29[0] |= 2 * (v15 & 1);
    v29[1] = *(_DWORD *)(v12 + 8);
    v29[2] = AST_GetHashedNodeIndex(*(__int16 **)(v12 + 12));
    v17 = v16[4];
    if ( v17 )
      v18 = *(_DWORD *)(v17 + 36);
    else
      v18 = -1;
    v29[3] = v18;
    v19 = v16[5];
    if ( v19 )
      v20 = *(_DWORD *)(v19 + 36);
    else
      v20 = -1;
    v29[4] = v20;
    v21 = v16[6];
    if ( v21 )
      v22 = *(_DWORD *)(v21 + 36);
    else
      v22 = -1;
    v29[5] = v22;
    v23 = v16[7];
    if ( v23 )
      v24 = *(_DWORD *)(v23 + 36);
    else
      v24 = -1;
    v29[6] = v24;
    v25 = v16[8];
    if ( v25 )
      v26 = *(_DWORD *)(v25 + 40);
    else
      v26 = -1;
    v29[7] = v26;
    result = Rules_BsaveWriteBlock(32, a1, v29);
    if ( v28[4] )
    {
      v12 = v28[4];
    }
    else
    {
      while ( !v28[7] )
      {
        v28 = (_DWORD *)v28[5];
        if ( !v28 )
          return result;
      }
      v12 = v28[7];
    }
  }
  result = (const void *)Rules_IsBloaded();
  if ( result )
  {
    Rules_ConstructQueuePop(&g_ReactiveRuleBloadCount);
    return (const void *)Rules_ConstructQueuePop(&g_ObjectPatternNetworkBloadCount);
  }
  return result;
}
// 4E23AB: variable 'v3' is possibly undefined
// 4E2419: variable 'v11' is possibly undefined
// 4E24C7: variable 'v16' is possibly undefined
// 4E252F: variable 'v28' is possibly undefined
// 51C718: using guessed type int dword_51C718;
// 51C71C: using guessed type int dword_51C71C;

//----- (004E25F0) --------------------------------------------------------
signed int Rules_BloadObjectPatternNetworkCounts()
{
  signed int result; // eax
  unsigned int count_bytes; // [esp+8h] [ebp-Ch] BYREF
  int counts[2]; // [esp+0h] [ebp-14h] BYREF

  Rules_BloadReadBlock((uintptr_t)&count_bytes, 4u);
  Rules_BloadReadBlock((uintptr_t)counts, count_bytes);
  g_ReactiveRuleBloadCount = counts[0];
  result = counts[1];
  g_ObjectPatternNetworkBloadCount = counts[1];
  if ( counts[0] )
  {
    count_bytes = 44 * counts[0];
    result = Mem_HeapAllocWithRetry((_DWORD *)(44 * counts[0]));
    g_ReactiveRuleArrayPtr = result;
  }
  else
  {
    g_ReactiveRuleArrayPtr = 0;
  }
  if ( g_ObjectPatternNetworkBloadCount )
  {
    count_bytes = 40 * g_ObjectPatternNetworkBloadCount;
    result = Mem_HeapAllocWithRetry((_DWORD *)(40 * g_ObjectPatternNetworkBloadCount));
    g_ObjectPatternNetworkArrayPtr = result;
  }
  else
  {
    g_ObjectPatternNetworkArrayPtr = 0;
  }
  return result;
}
// 51C718: using guessed type int dword_51C718;
// 51C71C: using guessed type int dword_51C71C;
// 51C720: using guessed type int dword_51C720;
// 51C724: using guessed type int dword_51C724;

//----- (004E2680) --------------------------------------------------------
int Rules_BloadObjectPatternNetworkRecords()
{
  int result; // eax
  int v1; // [esp+0h] [ebp-8h] BYREF

  result = Rules_BloadReadBlock((uintptr_t)&v1, 4u);
  if ( v1 )
  {
    Rules_BloadAndRefresh(g_ReactiveRuleBloadCount, 28, (void (__fastcall *)(signed int, signed int))Rules_RefreshBloadedReactiveRuleRecord);
    Rules_BloadAndRefresh(g_ObjectPatternNetworkBloadCount, 32, (void (__fastcall *)(signed int, signed int))Class_ResolveSystemSlotTemplate);
    Rules_SetReactiveRuleList(g_ReactiveRuleArrayPtr);
    return Rules_SetObjectPatternNetworkRoot(g_ObjectPatternNetworkArrayPtr);
  }
  return result;
}
// 51C718: using guessed type int dword_51C718;
// 51C71C: using guessed type int dword_51C71C;
// 51C720: using guessed type int dword_51C720;
// 51C724: using guessed type int dword_51C724;

//----- (004E26E0) --------------------------------------------------------
int  Rules_RefreshBloadedReactiveRuleRecord(int *a1, int a2)
{
  int record; // ecx
  int reactive_slots_index; // ebp
  int reactive_slots; // eax
  int direct_super_index; // eax
  int result; // eax
  int superclass_index; // ebx
  int role_symbol; // eax
  int superclass; // ebx

  record = 44 * a2 + g_ReactiveRuleArrayPtr;
  Rules_BloadUnpackSharedRecordHeader(record, a1);
  *(_DWORD *)(record + 16) = 0;
  *(_DWORD *)(record + 20) = *(_DWORD *)(g_ClipsBloadBitmapPointerTable + 4 * a1[2]);
  if ( a1[3] == -1 )
  {
    *(_DWORD *)(record + 24) = 0;
  }
  else
  {
    role_symbol = *(_DWORD *)(g_ClipsBloadBitmapPointerTable + 4 * a1[3]);
    *(_DWORD *)(record + 24) = role_symbol;
    ++*(_DWORD *)(role_symbol + 4);
  }
  ++*(_DWORD *)(*(_DWORD *)(record + 20) + 4);
  reactive_slots_index = a1[4];
  if ( reactive_slots_index == -1 )
    reactive_slots = 0;
  else
    reactive_slots = 40 * reactive_slots_index + g_ObjectPatternNetworkArrayPtr;
  *(_DWORD *)(record + 28) = reactive_slots;
  direct_super_index = a1[5];
  if ( direct_super_index == -1 )
    result = 0;
  else
    result = g_ReactiveRuleArrayPtr + 44 * direct_super_index;
  *(_DWORD *)(record + 32) = result;
  superclass_index = a1[6];
  if ( superclass_index == -1 )
  {
    *(_DWORD *)(record + 40) = 0;
    *(_DWORD *)(record + 36) = 0;
  }
  else
  {
    result = 44 * superclass_index;
    superclass = 44 * superclass_index + g_ReactiveRuleArrayPtr;
    *(_DWORD *)(record + 40) = 0;
    *(_DWORD *)(record + 36) = superclass;
  }
  return result;
}
// 51C720: using guessed type int dword_51C720;
// 51C724: using guessed type int dword_51C724;
// 54E67C: using guessed type int dword_54E67C;

//----- (004E27B0) --------------------------------------------------------
int * Class_ResolveSystemSlotTemplate(_DWORD *a1, int a2)
{
  int *result; // eax
  int v4; // ebx
  int v5; // ebx
  int v6; // edi
  int v7; // ebx
  int v8; // ebx
  int v9; // edi
  int v10; // ebp
  _DWORD *v11; // edx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ebx
  int v16; // ecx
  int v17; // esi
  int v18; // ecx
  int v19; // edi
  int v20; // ecx
  int v21; // ebp
  int v22; // edx

  result = (int *)(40 * a2 + g_ObjectPatternNetworkArrayPtr);
  *(_BYTE *)result &= ~1u;
  v4 = *a1;
  *(_BYTE *)result &= ~2u;
  *result |= 2 * (v4 & 1);
  v5 = *a1 << 22 >> 24;
  *(_WORD *)result &= 0xF807u;
  v6 = (8 * (unsigned __int8)v5) | *result;
  *result = v6;
  v7 = (unsigned __int8)(*a1 << 14 >> 24) << 11;
  *result = v6 & 0xFFF807FF;
  *result = v7 | v6 & 0xFFF807FF;
  v8 = *a1 << 30 >> 31;
  *(_BYTE *)result &= ~4u;
  v9 = *result;
  result[1] = 0;
  *result = (4 * (v8 & 1)) | v9;
  result[2] = a1[1];
  v10 = a1[2];
  v11 = a1;
  if ( v10 == -1 )
    v12 = 0;
  else
    v12 = g_ClipsPackedExpressionArray + 14 * v10;
  result[3] = v12;
  v13 = v11[3];
  if ( v13 == -1 )
    v14 = 0;
  else
    v14 = g_ObjectPatternNetworkArrayPtr + 40 * v13;
  result[4] = v14;
  v15 = v11[4];
  if ( v15 == -1 )
    v16 = 0;
  else
    v16 = g_ObjectPatternNetworkArrayPtr + 40 * v15;
  result[5] = v16;
  v17 = v11[5];
  if ( v17 == -1 )
    v18 = 0;
  else
    v18 = g_ObjectPatternNetworkArrayPtr + 40 * v17;
  result[6] = v18;
  v19 = v11[6];
  if ( v19 == -1 )
    v20 = 0;
  else
    v20 = g_ObjectPatternNetworkArrayPtr + 40 * v19;
  result[7] = v20;
  v21 = v11[7];
  if ( v21 == -1 )
  {
    result[9] = 0;
    result[8] = 0;
  }
  else
  {
    v22 = g_ReactiveRuleArrayPtr + 44 * v21;
    result[9] = 0;
    result[8] = v22;
  }
  return result;
}
// 51C720: using guessed type int dword_51C720;
// 51C724: using guessed type int dword_51C724;
// 54E688: using guessed type int dword_54E688;

//----- (004E2970) --------------------------------------------------------
int Class_ClearClassIDTable()
{
  int v0; // ecx
  int v1; // edx
  int v2; // edx
  int v3; // ecx

  v0 = 0;
  if ( g_ReactiveRuleBloadCount > 0 )
  {
    v1 = 0;
    do
    {
      Rules_DecrementBitmapCount(*(_DWORD *)(v1 + g_ReactiveRuleArrayPtr + 20), v0);
      if ( *(_DWORD *)(v2 + g_ReactiveRuleArrayPtr + 24) )
        Rules_DecrementBitmapCount(*(_DWORD *)(v2 + g_ReactiveRuleArrayPtr + 24), v3);
      v0 = v3 + 1;
      v1 = v2 + 44;
    }
    while ( v0 < g_ReactiveRuleBloadCount );
  }
  if ( g_ReactiveRuleBloadCount )
  {
    Mem_ReleasePoolBlock(g_ReactiveRuleArrayPtr, 44 * g_ReactiveRuleBloadCount);
    g_ReactiveRuleArrayPtr = 0;
    Mem_ReleasePoolBlock(g_ObjectPatternNetworkArrayPtr, 40 * g_ObjectPatternNetworkBloadCount);
    g_ObjectPatternNetworkArrayPtr = 0;
  }
  Rules_SetReactiveRuleList(0);
  return Rules_SetObjectPatternNetworkRoot(0);
}
// 4E2996: variable 'v2' is possibly undefined
// 4E29CD: variable 'v3' is possibly undefined
// 51C718: using guessed type int dword_51C718;
// 51C71C: using guessed type int dword_51C71C;
// 51C720: using guessed type int dword_51C720;
// 51C724: using guessed type int dword_51C724;

//----- (004E2A30) --------------------------------------------------------
int  Class_ParseSuperclasses(int a1, int a2)
{
  int **v4; // esi
  int **v5; // ebp
  int v6; // edx
  int **v8; // eax
  int *v9; // eax
  int *v10; // ecx
  _DWORD *v11; // edx
  int **v12; // eax
  _DWORD *v13; // edx
  signed int v14; // eax
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // eax
  int v22; // ecx
  int v23; // ecx

  v4 = 0;
  v5 = 0;
  if ( g_ParserCurrentTokenType == 100
    && (Parser_NextToken(a1, (int)&g_ParserCurrentTokenType), g_ParserCurrentTokenType == 2)
    && g_ClipsParserTokenValue == g_Symbol_IsA )
  {
    IO_OutWriteToken(asc_50E6E8);
    Parser_NextToken(a1, v6);
    if ( g_ParserCurrentTokenType == 101 )
    {
LABEL_23:
      if ( v4 )
      {
        IO_OutNewline();
        IO_OutNewline();
        IO_OutWriteToken(asc_50E7F8);
        v13 = *(_DWORD **)(g_ClipsMemoryTable + 24);
        if ( v13 )
        {
          g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 24);
          *(_DWORD *)(g_ClipsMemoryTable + 24) = *v13;
          Class_PackClassLinkList(g_ClipsMemFreeListTemp, v4);
        }
        else
        {
          v14 = Mem_HeapAllocWithRetry((_DWORD *)6);
          Class_PackClassLinkList(v14, v4);
        }
        return v15;
      }
      else
      {
        Rules_PrintErrorID((int)aInherpsr, 4, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aMustHaveAtLeas, v23);
        return 0;
      }
    }
    else
    {
      while ( 1 )
      {
        if ( g_ParserCurrentTokenType != 2 )
        {
          Parser_ReportSyntaxError();
          Mem_ReturnListToFreePool(v4);
          return 0;
        }
        if ( Rules_FindModuleSeparator(*(_BYTE **)(a2 + 16)) )
        {
          Module_ReportIllegalSpecifierError();
          Mem_ReturnListToFreePool(v4);
          return 0;
        }
        if ( a2 == g_ClipsParserTokenValue )
        {
          Rules_PrintErrorID((int)aInherpsr, 1, 0);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAClassMayNotHa, v16);
          Mem_ReturnListToFreePool(v4);
          return 0;
        }
        v8 = v4;
        if ( v4 )
          break;
LABEL_14:
        v9 = Class_LookupInScope(*(_BYTE **)(g_ClipsParserTokenValue + 16));
        v10 = v9;
        if ( !v9 )
        {
          Rules_PrintErrorID((int)aInherpsr, 3, 0);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAClassMustBe_0, v18);
          Mem_ReturnListToFreePool(v4);
          return 0;
        }
        if ( v9 == (int *)g_Class_InstanceName || v9 == (int *)g_Class_InstanceAddress || v9 == **(int ***)(g_Class_InstanceName + 36) )
        {
          Rules_PrintErrorID((int)aInherpsr, 6, 0);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAUserDefinedCl, v19);
          v21 = Rules_GetConstructNameString(v20);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], v21, (int)g_IO_LogicalNameTable_WError[0]);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__28, v22);
          Mem_ReturnListToFreePool(v4);
          return 0;
        }
        v11 = *(_DWORD **)(g_ClipsMemoryTable + 32);
        if ( v11 )
        {
          g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
          *(_DWORD *)(g_ClipsMemoryTable + 32) = *v11;
          v12 = (int **)g_ClipsMemFreeListTemp;
        }
        else
        {
          v12 = (int **)Mem_HeapAllocWithRetry((_DWORD *)8);
        }
        *v12 = v10;
        if ( v4 )
          v5[1] = (int *)v12;
        else
          v4 = v12;
        v5 = v12;
        v12[1] = 0;
        IO_OutWriteToken(asc_50E6E8);
        Parser_NextToken(a1, (int)&g_ParserCurrentTokenType);
        if ( g_ParserCurrentTokenType == 101 )
          goto LABEL_23;
      }
      while ( g_ClipsParserTokenValue != **v8 )
      {
        v8 = (int **)v8[1];
        if ( !v8 )
          goto LABEL_14;
      }
      Rules_PrintErrorID((int)aInherpsr, 2, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAClassMayInher, v17);
      Mem_ReturnListToFreePool(v4);
      return 0;
    }
  }
  else
  {
    Parser_ReportSyntaxError();
    return 0;
  }
}
// 4E2A81: variable 'v6' is possibly undefined
// 4E2B56: variable 'v10' is possibly undefined
// 4E2BCF: variable 'v15' is possibly undefined
// 4E2C06: variable 'v16' is possibly undefined
// 4E2C35: variable 'v17' is possibly undefined
// 4E2C64: variable 'v18' is possibly undefined
// 4E2C93: variable 'v19' is possibly undefined
// 4E2C9A: variable 'v20' is possibly undefined
// 4E2CB8: variable 'v22' is possibly undefined
// 4E2D04: variable 'v23' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51AD98: using guessed type int dword_51AD98;
// 51AD9C: using guessed type int dword_51AD9C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E6FC: using guessed type int dword_54E6FC;
// 54E8FC: using guessed type int dword_54E8FC;
// 54E900: using guessed type int dword_54E900;

//----- (004E2D40) --------------------------------------------------------
int  Class_BuildPrecedenceList(int a1, unsigned __int16 *a2)
{
  _DWORD *v2; // eax
  _DWORD *v3; // esi
  _DWORD *v4; // ecx
  _DWORD *v5; // eax
  int v6; // ebp
  unsigned int i; // edx
  int v8; // eax
  unsigned int v9; // edi
  unsigned int v10; // ecx
  int v11; // edx
  unsigned int v12; // edx
  int v13; // ebp
  unsigned int v14; // edi
  unsigned int v15; // ecx
  int v16; // edx
  _DWORD *v17; // edx
  _DWORD *v18; // ebx
  _DWORD *v19; // ecx
  _DWORD *v20; // ebp
  int *v21; // ebp
  _DWORD *v22; // edi
  int *v23; // eax
  int v24; // edi
  _DWORD *v25; // edx
  signed int v26; // eax
  int *v27; // edx
  _DWORD *v28; // ecx
  signed int v29; // ecx
  int v30; // ecx
  _DWORD *v32; // ebp
  _DWORD *v33; // eax
  int *v35; // [esp+8h] [ebp-24h]
  int *v36; // [esp+Ch] [ebp-20h]
  int *v38; // [esp+14h] [ebp-18h]

  v2 = Class_CollectAllSuperclasses(0, a2);
  v3 = v2;
  if ( a1 )
  {
    v4 = *(_DWORD **)(g_ClipsMemoryTable + 64);
    if ( v4 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
      *(_DWORD *)(g_ClipsMemoryTable + 64) = *v4;
      v5 = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      v5 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x10);
    }
    v5[1] = 0;
    v5[2] = 0;
    v5[3] = v3;
    *v5 = a1;
    v38 = (int *)v5[3];
    v3 = v5;
    Class_AddPrecedenceDependency(v5, a1, 0, a2);
  }
  else
  {
    v38 = v2;
  }
  while ( v38 )
  {
    v6 = 0;
    Class_AddPrecedenceDependency(v3, *v38, 0, (unsigned __int16 *)(*v38 + 34));
    for ( i = 0; ; i = v9 )
    {
      v8 = *v38;
      if ( i >= *(unsigned __int16 *)(*v38 + 34) )
        break;
      v9 = i + 1;
      v10 = i + 1;
      v11 = *(_DWORD *)(*(_DWORD *)(v8 + 36) + v6);
      v6 += 4;
      Class_AddPrecedenceDependency(v3, v11, v10, (unsigned __int16 *)(v8 + 34));
    }
    v38 = (int *)v38[3];
  }
  v12 = 0;
  v13 = 0;
  while ( v12 < *a2 )
  {
    v14 = v12 + 1;
    v15 = v12 + 1;
    v16 = *(_DWORD *)(*(_DWORD *)(a2 + 1) + v13);
    v13 += 4;
    Class_AddPrecedenceDependency(v3, v16, v15, a2);
    v12 = v14;
  }
  v17 = v3;
  v18 = 0;
  v19 = 0;
  v35 = 0;
  v36 = 0;
  if ( v3 )
  {
    do
    {
      if ( !v17 )
      {
        v17 = v3;
        v18 = (_DWORD *)v18[3];
        v19 = 0;
      }
      if ( v17[1] )
      {
        v19 = v17;
        v17 = (_DWORD *)v17[3];
      }
      else
      {
        while ( 1 )
        {
          v20 = (_DWORD *)v17[2];
          if ( !v20 )
            break;
          v17[2] = v20[1];
          --*(_DWORD *)(*v20 + 4);
          g_ClipsMemFreeListTemp = (int)v20;
          *v20 = *(_DWORD *)(g_ClipsMemoryTable + 32);
          *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
        }
        v21 = v17;
        if ( v19 )
          v19[3] = v17[3];
        else
          v3 = (_DWORD *)v17[3];
        v18 = v19;
        v22 = *(_DWORD **)(g_ClipsMemoryTable + 32);
        v17 = (_DWORD *)v17[3];
        if ( v22 )
        {
          g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
          *(_DWORD *)(g_ClipsMemoryTable + 32) = *v22;
          v23 = (int *)g_ClipsMemFreeListTemp;
        }
        else
        {
          v23 = (int *)Mem_HeapAllocWithRetry((_DWORD *)8);
        }
        v24 = *v21;
        v23[1] = 0;
        *v23 = v24;
        g_ClipsMemFreeListTemp = (int)v21;
        *v21 = *(_DWORD *)(g_ClipsMemoryTable + 64);
        *(_DWORD *)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
        if ( v36 )
          v35[1] = (int)v23;
        else
          v36 = v23;
        v35 = v23;
      }
    }
    while ( v17 != v18 );
  }
  if ( v3 )
  {
    Rules_PrintErrorID((int)aInherpsr, 5, 0);
    Class_PrintClassNameList((int)g_IO_LogicalNameTable_WError[0], (int)aPartialPrecede, v36);
    Class_ReportPrecedenceLoop(v3);
    do
    {
      while ( 1 )
      {
        v32 = (_DWORD *)v3[2];
        if ( !v32 )
          break;
        v3[2] = v32[1];
        g_ClipsMemFreeListTemp = (int)v32;
        *v32 = *(_DWORD *)(g_ClipsMemoryTable + 32);
        *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
      }
      v33 = v3;
      v3 = (_DWORD *)v3[3];
      g_ClipsMemFreeListTemp = (int)v33;
      *v33 = *(_DWORD *)(g_ClipsMemoryTable + 64);
      *(_DWORD *)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
    }
    while ( v3 );
    Mem_ReturnListToFreePool(v36);
    return 0;
  }
  else
  {
    if ( !a1 )
    {
      v25 = *(_DWORD **)(g_ClipsMemoryTable + 32);
      if ( v25 )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
        *(_DWORD *)(g_ClipsMemoryTable + 32) = *v25;
        v26 = g_ClipsMemFreeListTemp;
      }
      else
      {
        v26 = Mem_HeapAllocWithRetry((_DWORD *)8);
      }
      v27 = v36;
      v36 = (int *)v26;
      *(_DWORD *)(v26 + 4) = v27;
    }
    *v36 = 0;
    v28 = *(_DWORD **)(g_ClipsMemoryTable + 24);
    if ( v28 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 24);
      *(_DWORD *)(g_ClipsMemoryTable + 24) = *v28;
      v29 = g_ClipsMemFreeListTemp;
    }
    else
    {
      v29 = Mem_HeapAllocWithRetry((_DWORD *)6);
    }
    Class_PackClassLinkList(v29, v36);
    return v30;
  }
}
// 4E2FF5: conditional instruction was optimized away because esi.4!=0
// 4E2EAA: variable 'v19' is possibly undefined
// 4E2F87: variable 'v30' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004E3090) --------------------------------------------------------
_DWORD * Class_PackClassLinkList(int a1, _DWORD *a2)
{
  _DWORD *v4; // eax
  int i; // edx
  _DWORD *v6; // eax
  int v7; // edx
  int v8; // ecx
  _DWORD *result; // eax
  __int16 v10; // dx

  v4 = a2;
  for ( i = 0; v4; ++i )
    v4 = (_DWORD *)v4[1];
  if ( i )
    *(_DWORD *)(a1 + 2) = Mem_SmallBlockAlloc(4 * i);
  else
    *(_DWORD *)(a1 + 2) = 0;
  v6 = a2;
  v7 = 0;
  if ( a2 )
  {
    v8 = 0;
    do
    {
      *(_DWORD *)(*(_DWORD *)(a1 + 2) + v8) = *v6;
      ++v7;
      v6 = (_DWORD *)v6[1];
      v8 += 4;
    }
    while ( v6 );
  }
  result = Mem_ReturnListToFreePool(a2);
  *(_WORD *)a1 = v10;
  return result;
}
// 4E30F7: variable 'v10' is possibly undefined

//----- (004E3110) --------------------------------------------------------
_DWORD * Class_CollectAllSuperclasses(_DWORD *a1, unsigned __int16 *a2)
{
  int v4; // edi
  _DWORD *v5; // eax
  _DWORD *i; // ecx
  _DWORD *v7; // ebx
  _DWORD *v8; // eax
  int v9; // edx
  unsigned int v11; // [esp+0h] [ebp-18h]

  v4 = 0;
  v11 = 0;
  while ( *a2 > v11 )
  {
    v5 = a1;
    for ( i = 0; v5; v5 = (_DWORD *)v5[3] )
    {
      if ( *v5 == *(_DWORD *)(v4 + *(_DWORD *)(a2 + 1)) )
        break;
      i = v5;
    }
    if ( v5 )
    {
      v4 += 4;
      ++v11;
    }
    else
    {
      v7 = *(_DWORD **)(g_ClipsMemoryTable + 64);
      if ( v7 )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
        *(_DWORD *)(g_ClipsMemoryTable + 64) = *v7;
        v8 = (_DWORD *)g_ClipsMemFreeListTemp;
      }
      else
      {
        v8 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x10);
      }
      v9 = *(_DWORD *)(*(_DWORD *)(a2 + 1) + v4);
      v8[3] = 0;
      v8[2] = 0;
      v8[1] = 0;
      *v8 = v9;
      if ( i )
        i[3] = v8;
      else
        a1 = v8;
      a1 = (_DWORD *)Class_CollectAllSuperclasses((int)a1, *(_DWORD *)(v4 + *(_DWORD *)(a2 + 1)) + 34);
      v4 += 4;
      ++v11;
    }
  }
  return a1;
}
// 4E3197: variable 'i' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004E31E0) --------------------------------------------------------
__int16  Class_AddPrecedenceDependency(_DWORD *a1, int a2, unsigned int a3, unsigned __int16 *a4)
{
  int v7; // ecx
  int i; // esi
  __int16 result; // ax
  _DWORD *v10; // edx
  _DWORD *v11; // eax
  _DWORD *v12; // ecx
  _DWORD *v13; // [esp+0h] [ebp-10h]

  v13 = Class_FindClassLinkNode(a1, a2);
  for ( i = 4 * v7; ; i += 4 )
  {
    result = *a4;
    if ( a3 >= *a4 )
      break;
    v10 = *(_DWORD **)(g_ClipsMemoryTable + 32);
    if ( v10 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
      *(_DWORD *)(g_ClipsMemoryTable + 32) = *v10;
    }
    else
    {
      Mem_HeapAllocWithRetry((_DWORD *)8);
    }
    v11 = Class_FindClassLinkNode(a1, *(_DWORD *)(*(_DWORD *)(a4 + 1) + i));
    *v12 = v11;
    v12[1] = v13[2];
    v13[2] = v12;
    ++a3;
    ++*(_DWORD *)(*v12 + 4);
  }
  return result;
}
// 4E31F4: variable 'v7' is possibly undefined
// 4E3230: variable 'v12' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004E3270) --------------------------------------------------------
_DWORD * Class_FindClassLinkNode(_DWORD *result, int a2)
{
  for ( ; result; result = (_DWORD *)result[3] )
  {
    if ( a2 == *result )
      break;
  }
  return result;
}

//----- (004E3280) --------------------------------------------------------
signed int  Class_ReportPrecedenceLoop(_DWORD *a1)
{
  _DWORD *i; // ecx
  _DWORD *j; // edi
  int v3; // ebx
  _DWORD *v4; // edx
  _DWORD *v5; // eax
  int v6; // eax
  _DWORD *v7; // esi
  _DWORD *v8; // eax
  _DWORD *k; // ebx
  int *m; // esi
  int v11; // ecx
  int v12; // ecx

  for ( i = a1; a1; a1 = (_DWORD *)a1[3] )
    a1[1] = 0;
  for ( j = i; j; j = (_DWORD *)j[3] )
  {
    if ( j[1] )
    {
      v6 = j[2];
      v3 = *(_DWORD *)(v6 + 4);
      *(_DWORD *)(v6 + 4) = 0;
    }
    else
    {
      v3 = j[2];
      j[2] = 0;
    }
    while ( v3 )
    {
      v4 = Class_FindClassLinkNode(i, **(_DWORD **)v3);
      if ( !v4[1] )
      {
        v7 = *(_DWORD **)(g_ClipsMemoryTable + 32);
        if ( v7 )
        {
          g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
          *(_DWORD *)(g_ClipsMemoryTable + 32) = *v7;
          v8 = (_DWORD *)g_ClipsMemFreeListTemp;
        }
        else
        {
          v8 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)8);
        }
        *v8 = j;
        v8[1] = v4[2];
        v4[1] = 1;
        v4[2] = v8;
      }
      v5 = (_DWORD *)v3;
      v3 = *(_DWORD *)(v3 + 4);
      g_ClipsMemFreeListTemp = (int)v5;
      *v5 = *(_DWORD *)(g_ClipsMemoryTable + 32);
      *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
    }
  }
  for ( k = i; k; k = (_DWORD *)k[3] )
    k[1] = 0;
  for ( m = i; !m[1]; m = *(int **)m[2] )
    m[1] = 1;
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aPrecedenceLoop, (int)i);
  if ( m[1] == 1 )
  {
    v11 = 0;
    do
    {
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_50E6E8, v11);
      Class_PrintName(*m, v12);
      m[1] = v11;
      m = *(int **)m[2];
    }
    while ( m[1] == 1 );
  }
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_50E6E8, v11);
  return Class_PrintName(*m, 1);
}
// 4E32C7: variable 'i' is possibly undefined
// 4E33A3: variable 'v11' is possibly undefined
// 4E33B1: variable 'v12' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004E3400) --------------------------------------------------------
signed int  Class_PrintClassNameList(int a1, int a2, int *a3)
{
  int v3; // ecx

  v3 = a1;
  if ( a2 )
    Output_Write(a1, a2, a1);
  while ( a3 )
  {
    Output_Write(v3, (int)asc_50E6E8, v3);
    Class_PrintName(*a3, 0);
    a3 = (int *)a3[1];
  }
  return Output_Write(v3, (int)asc_50E840, v3);
}
// 4E3415: variable 'v3' is possibly undefined

//----- (004E3440) --------------------------------------------------------
int * Class_ParseSlot(
        char *a1,
        _DWORD *a2,
        int a3,
        unsigned __int16 *a4,
        double a5,
        int a6)
{
  int v9; // esi
  int *result; // eax
  _BYTE *v11; // ecx
  int v12; // ebp
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int v18; // ebx
  char *v19; // eax
  int v20; // eax
  __int16 *v21; // ecx
  char v22; // cl
  int v23; // ecx
  signed int v24; // eax
  int v25; // ecx
  signed int v26; // eax
  int v27; // ecx
  signed int v28; // eax
  int v29; // ecx
  signed int v30; // eax
  int v31; // ecx
  signed int v32; // eax
  int v33; // ecx
  signed int v34; // eax
  int v35; // ecx
  signed int v36; // eax
  signed int v37; // eax
  int v38; // ecx
  int v39; // eax
  __int16 v40; // [esp+0h] [ebp-1Ch] BYREF
  int v41; // [esp+4h] [ebp-18h] BYREF
  unsigned __int16 *v42; // [esp+8h] [ebp-14h]
  char v43[16]; // [esp+Ch] [ebp-10h] BYREF

  v42 = a4;
  IO_OutWriteToken(asc_50E844);
  v43[1] = 0;
  v43[0] = 0;
  Parser_NextToken((int)a1, (int)&g_ParserCurrentTokenType);
  if ( g_ParserCurrentTokenType != 2 || g_ClipsParserTokenValue == g_Symbol_IsA || g_ClipsParserTokenValue == g_Clips_NameSymbol )
  {
    Class_DeleteSlotList((int)a2);
    Parser_ReportSyntaxError();
    return 0;
  }
  v9 = Class_NewSlot((_DWORD *)g_ClipsParserTokenValue);
  result = Class_InsertSlot(a2, v9);
  v12 = (int)result;
  if ( !result )
    return result;
  if ( a3 )
    *v11 |= 2u;
  if ( a6 )
    v43[0] |= 2u;
  Parser_NextToken((int)a1, (int)&g_ParserCurrentTokenType);
  Rules_IncrementIndentDepth(3);
  Rules_ResetConstraintParsedFlags(&v40);
  if ( g_ParserCurrentTokenType == 100 )
  {
    while ( 1 )
    {
      IO_OutNewline();
      AST_Append(v14, v13);
      IO_OutWriteToken(asc_50E858);
      Parser_NextToken((int)a1, v15);
      if ( g_ParserCurrentTokenType != 2 )
        goto LABEL_11;
      if ( !strcmp_(v16, aDefault_2) )
        break;
      if ( !strcmp_(v17, aDefaultDynam_1) )
      {
        v18 = v9;
        BYTE1(v17) = v43[0] | 0x80;
        v19 = a1;
        v43[0] |= 0x80u;
        goto LABEL_18;
      }
      if ( !strcmp_(v17, aAccess) )
      {
        v24 = Class_ParseSimpleFacet(
                (int)a1,
                (int)v43,
                2,
                (int)aAccess,
                (int)aReadWrite,
                (int)aReadOnly,
                (int)aInitializeOnly,
                0,
                0);
        switch ( v24 )
        {
          case -1:
            goto LABEL_12;
          case 1:
            *(_BYTE *)v9 |= 0x10u;
            break;
          case 2:
            *(_BYTE *)v9 |= 0x20u;
            break;
        }
      }
      else if ( !strcmp_(v23, aStorage) )
      {
        v26 = Class_ParseSimpleFacet((int)a1, (int)v43, 0, (int)aStorage, (int)aLocal_0, (int)aShared, 0, 0, 0);
        if ( v26 == -1 )
          goto LABEL_12;
        *(_BYTE *)v9 &= ~1u;
        *(_DWORD *)v9 |= v26 & 1;
      }
      else if ( !strcmp_(v25, aPropagation) )
      {
        v28 = Class_ParseSimpleFacet((int)a1, (int)v43, 3, (int)aPropagation, (int)aInherit_2, (int)aNoInherit, 0, 0, 0);
        if ( v28 == -1 )
          goto LABEL_12;
        *(_BYTE *)v9 &= ~8u;
        *(_DWORD *)v9 |= 8 * (v28 & 1);
      }
      else if ( !strcmp_(v27, aSource) )
      {
        v30 = Class_ParseSimpleFacet((int)a1, (int)v43, 4, (int)aSource, (int)aExclusive, (int)aComposite, 0, 0, 0);
        if ( v30 == -1 )
          goto LABEL_12;
        *(_BYTE *)v9 &= ~4u;
        *(_DWORD *)v9 |= 4 * (v30 & 1);
      }
      else if ( !strcmp_(v29, aPatternMatch_1) )
      {
        v32 = Class_ParseSimpleFacet((int)a1, (int)v43, 5, (int)aPatternMatch_1, (int)aNonReactive_0, (int)aReactive_0, 0, 0, 0);
        if ( v32 == -1 )
          goto LABEL_12;
        *(_BYTE *)(v9 + 1) &= ~2u;
        *(_DWORD *)v9 |= (v32 & 1) << 9;
      }
      else if ( !strcmp_(v31, aVisibility) )
      {
        v34 = Class_ParseSimpleFacet((int)a1, (int)v43, 8, (int)aVisibility, (int)aPrivate, (int)aPublic, 0, 0, 0);
        if ( v34 == -1 )
          goto LABEL_12;
        *(_BYTE *)(v9 + 1) &= ~4u;
        *(_DWORD *)v9 |= (v34 & 1) << 10;
      }
      else if ( !strcmp_(v33, aCreateAccessor) )
      {
        v36 = Class_ParseSimpleFacet(
                (int)a1,
                (int)v43,
                9,
                (int)aCreateAccessor,
                (int)aRead_0,
                (int)aWrite,
                (int)aReadWrite,
                (int)aNone_2,
                0);
        if ( v36 == -1 )
          goto LABEL_12;
        if ( !v36 || v36 == 2 )
          *(_BYTE *)(v9 + 1) |= 8u;
        if ( v36 == 1 || v36 == 2 )
          *(_BYTE *)(v9 + 1) |= 0x10u;
      }
      else
      {
        if ( strcmp_(v35, aOverrideMessag) )
        {
          if ( !Rules_IsConstraintAttributeKeyword(*(_DWORD *)(g_ClipsParserTokenValue + 16)) )
            goto LABEL_11;
          v20 = Rules_ParseStandardConstraintAttribute(a1, *(const char **)(g_ClipsParserTokenValue + 16), &v40, *(_DWORD *)(v9 + 20), 1);
          goto LABEL_19;
        }
        v37 = Class_ParseSimpleFacet((int)a1, (int)v43, 10, (int)aOverrideMessag, 0, 0, 0, (int)aDefault_3, &v41);
        if ( v37 == -1 )
          goto LABEL_12;
        if ( v37 == 4 )
        {
          Rules_DecrementSymbolCount(*(_DWORD *)(v9 + 12), v38);
          v39 = v41;
          *(_DWORD *)(v9 + 12) = v41;
          ++*(_DWORD *)(v39 + 4);
        }
        *(_BYTE *)(v9 + 1) |= 0x20u;
      }
LABEL_20:
      Parser_NextToken((int)a1, (int)&g_ParserCurrentTokenType);
      if ( g_ParserCurrentTokenType != 100 )
        goto LABEL_21;
    }
    v18 = v9;
    v19 = a1;
LABEL_18:
    v20 = Class_ParseDefaultFacet((int)v19, v43, v17, v18, a5);
LABEL_19:
    if ( !v20 )
      goto LABEL_12;
    goto LABEL_20;
  }
LABEL_21:
  if ( g_ParserCurrentTokenType != 101 )
  {
LABEL_11:
    Parser_ReportSyntaxError();
LABEL_12:
    Rules_DecrementIndentDepth(3);
    Class_DeleteSlotList(v12);
    return 0;
  }
  if ( (*(_BYTE *)v9 & 4) != 0 )
    Class_BuildCompositeFacets(v9, v42, (int)&v40, v43);
  if ( !Class_CheckForFacetConflicts(v9, (int)&v40) || !Rules_CheckConstraintParseConflicts(*(_DWORD *)(v9 + 20), v21) || !Class_EvaluateSlotDefaultValue((int *)v9, v43, a5) )
    goto LABEL_12;
  v22 = *(_BYTE *)v9;
  if ( (*(_BYTE *)v9 & 0x40) == 0 && (v22 & 0x10) != 0 && (v22 & 0x20) == 0 )
    *(_BYTE *)v9 = v22 | 1;
  *(_DWORD *)(v9 + 20) = AST_InternNode(*(_DWORD **)(v9 + 20));
  Rules_DecrementIndentDepth(3);
  return (int *)v12;
}
// 4E34BA: variable 'v11' is possibly undefined
// 4E34F8: variable 'v14' is possibly undefined
// 4E34F8: variable 'v13' is possibly undefined
// 4E350E: variable 'v15' is possibly undefined
// 4E3562: variable 'v16' is possibly undefined
// 4E3577: variable 'v17' is possibly undefined
// 4E35D0: variable 'v21' is possibly undefined
// 4E36C8: variable 'v23' is possibly undefined
// 4E3713: variable 'v25' is possibly undefined
// 4E376C: variable 'v27' is possibly undefined
// 4E37C5: variable 'v29' is possibly undefined
// 4E381C: variable 'v31' is possibly undefined
// 4E3873: variable 'v33' is possibly undefined
// 4E38E5: variable 'v35' is possibly undefined
// 4E3924: variable 'v38' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 54E6F8: using guessed type int dword_54E6F8;
// 54E6FC: using guessed type int dword_54E6FC;
// 54E8FC: using guessed type int dword_54E8FC;
// 54E900: using guessed type int dword_54E900;

//----- (004E3970) --------------------------------------------------------
int  Class_DeleteSlotList(int result)
{
  int i; // ecx
  int v2; // edx
  int v3; // ecx
  int v4; // edx
  int v5; // edx
  int v6; // eax
  int v7; // edx

  for ( i = result; i; *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp )
  {
    Class_ReleaseSlotName(*(_DWORD **)(*(_DWORD *)i + 8));
    Rules_DecrementSymbolCount(*(_DWORD *)(*(_DWORD *)v2 + 12), v3);
    AST_DecrementNodeRefCount(*(_DWORD **)(*(_DWORD *)v4 + 20));
    v6 = *(_DWORD *)v5;
    if ( (**(_BYTE **)v5 & 0x40) != 0 )
    {
      AST_DeinstallNodeChain(*(__int16 **)(v6 + 16));
      AST_FreePackedNodeChain(*(_DWORD *)(*(_DWORD *)v7 + 16));
    }
    else if ( *(_DWORD *)(v6 + 16) )
    {
      Rules_ValueDeinstall(*(_DWORD *)(v6 + 16), i);
      g_ClipsMemFreeListTemp = *(_DWORD *)(*(_DWORD *)v5 + 16);
      *(_DWORD *)g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 96);
      *(_DWORD *)(g_ClipsMemoryTable + 96) = g_ClipsMemFreeListTemp;
    }
    g_ClipsMemFreeListTemp = *(_DWORD *)v5;
    *(_DWORD *)g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 176);
    *(_DWORD *)(g_ClipsMemoryTable + 176) = g_ClipsMemFreeListTemp;
    g_ClipsMemFreeListTemp = v5;
    *(_DWORD *)v5 = *(_DWORD *)(g_ClipsMemoryTable + 32);
    result = g_ClipsMemFreeListTemp;
  }
  return result;
}
// 4E397F: variable 'i' is possibly undefined
// 4E398C: variable 'v2' is possibly undefined
// 4E3991: variable 'v3' is possibly undefined
// 4E3996: variable 'v4' is possibly undefined
// 4E39A0: variable 'v5' is possibly undefined
// 4E3A3E: variable 'v7' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004E3A50) --------------------------------------------------------
int  Class_NewSlot(_DWORD *a1)
{
  _DWORD *v2; // edx
  signed int v3; // ecx
  __int16 v4; // dx
  int v5; // eax
  int v6; // ecx
  int v7; // edx
  unsigned int *v8; // eax
  int v9; // ecx
  unsigned int v10; // eax

  v2 = *(_DWORD **)(g_ClipsMemoryTable + 176);
  if ( v2 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 176);
    *(_DWORD *)(g_ClipsMemoryTable + 176) = *v2;
    v3 = g_ClipsMemFreeListTemp;
  }
  else
  {
    v3 = Mem_HeapAllocWithRetry((_DWORD *)0x2C);
  }
  *(_DWORD *)(v3 + 24) = 0;
  v4 = *(_WORD *)v3;
  *(_DWORD *)(v3 + 4) = 0;
  *(_DWORD *)(v3 + 16) = 0;
  *(_WORD *)v3 = v4 | 0x240;
  *(_WORD *)v3 = v4 & 0xC000 | 0x240;
  v5 = Rules_CreateLHSParseNode();
  *(_DWORD *)(v6 + 20) = v5;
  v8 = Class_InternSlotName(a1, v7, 0);
  *(_DWORD *)(v9 + 8) = v8;
  v10 = v8[4];
  *(_DWORD *)(v9 + 12) = v10;
  ++*(_DWORD *)(v10 + 4);
  return v9;
}
// 4E3AAF: variable 'v6' is possibly undefined
// 4E3AB4: variable 'v7' is possibly undefined
// 4E3AB9: variable 'v9' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004E3AE0) --------------------------------------------------------
int * Class_InsertSlot(_DWORD *a1, int a2)
{
  int v3; // ecx
  _DWORD *v4; // edx
  int *result; // eax
  int v6; // esi
  _DWORD *v7; // eax
  _DWORD *v8; // edx
  int v9; // edx
  int v10; // ecx

  v3 = a2;
  v4 = *(_DWORD **)(g_ClipsMemoryTable + 32);
  if ( v4 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
    *(_DWORD *)(g_ClipsMemoryTable + 32) = *v4;
    result = (int *)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = (int *)Mem_HeapAllocWithRetry((_DWORD *)8);
  }
  result[1] = 0;
  v6 = (int)result;
  *result = v3;
  if ( a1 )
  {
    v7 = a1;
    while ( *(_DWORD *)(v3 + 8) != *(_DWORD *)(*v7 + 8) )
    {
      v8 = v7;
      v7 = (_DWORD *)v7[1];
      if ( !v7 )
      {
        v8[1] = v6;
        return a1;
      }
    }
    *(_DWORD *)(v6 + 4) = a1;
    Class_DeleteSlotList(v6);
    Rules_PrintErrorID((int)aClsltpsr, v9, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDuplicateSlots, v10);
    return 0;
  }
  return result;
}
// 4E3B0D: variable 'v3' is possibly undefined
// 4E3B63: variable 'v9' is possibly undefined
// 4E3B72: variable 'v10' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004E3B80) --------------------------------------------------------
signed int  Class_ParseSimpleFacet(
        int a1,
        int a2,
        signed int a3,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        _DWORD *a9)
{
  _BYTE *v11; // ebx
  int v12; // eax
  int v13; // edx
  int v14; // ecx
  int v15; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx

  v11 = (_BYTE *)(((a3 - (__CFSHL__(a3 >> 31, 3) + 8 * (a3 >> 31))) >> 3) + a2);
  v12 = 1 << (a3 % 8);
  if ( (*v11 & (unsigned __int8)v12) != 0 )
  {
    Rules_PrintErrorID((int)aClsltpsr, 2, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], a4, v17);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFacetAlreadySp, v18);
    return -1;
  }
  *v11 |= v12;
  IO_OutWriteToken(asc_50E844);
  Parser_NextToken(a1, v13);
  if ( g_ParserCurrentTokenType == 15 )
  {
    if ( a8 && !strcmp_(v14, a8) )
      goto LABEL_5;
  }
  else if ( g_ParserCurrentTokenType == 2 )
  {
    if ( a9 )
    {
      *a9 = g_ClipsParserTokenValue;
      goto LABEL_5;
    }
    if ( !strcmp_(v14, a5) || !strcmp_(v19, a6) || a7 && !strcmp_(v20, a7) )
    {
LABEL_5:
      Parser_NextToken(a1, (int)&g_ParserCurrentTokenType);
      if ( g_ParserCurrentTokenType == 101 )
        return v15;
    }
  }
  Parser_ReportSyntaxError();
  return -1;
}
// 4E3BDA: variable 'v13' is possibly undefined
// 4E3C02: variable 'v14' is possibly undefined
// 4E3C35: variable 'v15' is possibly undefined
// 4E3C58: variable 'v17' is possibly undefined
// 4E3C67: variable 'v18' is possibly undefined
// 4E3CC2: variable 'v19' is possibly undefined
// 4E3CE8: variable 'v20' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 54E8FC: using guessed type int dword_54E8FC;
// 54E900: using guessed type int dword_54E900;

//----- (004E3D20) --------------------------------------------------------
signed int  Class_ParseDefaultFacet(int a1, _BYTE *a2, int a3, int a4, double a5)
{
  _DWORD *v6; // eax
  int v8; // ecx
  int v9; // edx
  int v10; // [esp+0h] [ebp-18h] BYREF
  int v11; // [esp+4h] [ebp-14h] BYREF
  _DWORD v12[4]; // [esp+8h] [ebp-10h] BYREF

  v12[3] = a3;
  if ( (*a2 & 0x40) != 0 )
  {
    Rules_PrintErrorID((int)aClsltpsr, 2, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDefaultFacetAl, v8);
    return 0;
  }
  *a2 |= 0x40u;
  v10 = 0;
  v6 = (_DWORD *)Rules_ParseDefaultAttribute(a1, 1, 0, *a2 & 0x80, a5, &v11, v12, &v10);
  if ( v10 == 1 )
    return 0;
  if ( v11 || v12[0] )
  {
    if ( !v11 )
    {
      *a2 &= ~0x40u;
      return 1;
    }
    *(_WORD *)a4 |= 0x180u;
  }
  else
  {
    *(_DWORD *)(a4 + 16) = AST_PackNodeChain(v6);
    AST_Free(v9);
    AST_InstallNodeChain(*(__int16 **)(a4 + 16));
    *(_BYTE *)a4 |= 0x80u;
  }
  return 1;
}
// 4E3D9D: variable 'v8' is possibly undefined
// 4E3DB7: variable 'v9' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004E3DE0) --------------------------------------------------------
__int16  Class_BuildCompositeFacets(int a1, unsigned __int16 *a2, int a3, _BYTE *a4)
{
  unsigned int v6; // ecx
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  __int16 *v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  _BYTE *v21; // eax
  _DWORD *v22; // edi
  void *v23; // eax
  _BYTE *v27; // [esp+8h] [ebp-Ch]

  v6 = 1;
  v7 = 4;
  while ( 1 )
  {
    LOWORD(v8) = *a2;
    if ( v6 >= *a2 )
      break;
    v21 = (_BYTE *)Class_FindSlotBySymbol(*(_DWORD *)(v7 + *(_DWORD *)(a2 + 1)), *(_DWORD *)(*(_DWORD *)(a1 + 8) + 12));
    v27 = v21;
    if ( v21 )
    {
      v8 = (*v21 & 8) == 0;
      if ( v8 )
        break;
      v7 += 4;
      ++v6;
    }
    else
    {
      v7 += 4;
      ++v6;
    }
  }
  if ( v27 )
  {
    if ( *(char *)a1 >= 0 && (char)*v27 < 0 )
    {
      v9 = *(_DWORD *)v27;
      *(_BYTE *)a1 &= ~0x40u;
      *(_DWORD *)a1 |= v9 & 0x40;
      LOBYTE(v6) = *(_BYTE *)(a1 + 1) & 0xFE;
      v10 = *(_DWORD *)v27;
      *(_BYTE *)(a1 + 1) = v6;
      *(_DWORD *)a1 |= v10 & 0x100;
      BYTE1(v6) = *(_BYTE *)a1 | 0x80;
      *(_BYTE *)a1 = BYTE1(v6);
      if ( *((_DWORD *)v27 + 4) )
      {
        if ( (v6 & 0x4000) != 0 )
        {
          v11 = (__int16 *)AST_PackNodeChain(*((_DWORD **)v27 + 4));
          *(_DWORD *)(a1 + 16) = v11;
          AST_InstallNodeChain(v11);
        }
        else
        {
          v22 = *(_DWORD **)(g_ClipsMemoryTable + 96);
          if ( v22 )
          {
            g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 96);
            *(_DWORD *)(g_ClipsMemoryTable + 96) = *v22;
            v23 = (void *)g_ClipsMemFreeListTemp;
          }
          else
          {
            v23 = (void *)Mem_HeapAllocWithRetry((_DWORD *)0x18);
          }
          *(_DWORD *)(a1 + 16) = v23;
          qmemcpy(v23, *((const void **)v27 + 4), 0x18u);
          Rules_ValueInstall(*(_DWORD *)(a1 + 16), 0);
        }
      }
    }
    if ( (*a4 & 2) == 0 )
    {
      v12 = *(_DWORD *)v27;
      *(_BYTE *)a1 &= ~2u;
      *(_DWORD *)a1 |= v12 & 2;
    }
    if ( (*a4 & 1) == 0 )
    {
      v13 = *(_DWORD *)v27;
      *(_BYTE *)a1 &= ~1u;
      *(_DWORD *)a1 |= v13 & 1;
    }
    if ( (*a4 & 4) == 0 )
    {
      BYTE1(v6) = *(_BYTE *)a1 & 0xEF;
      v14 = *(_DWORD *)v27;
      *(_BYTE *)a1 = BYTE1(v6);
      *(_DWORD *)a1 |= v14 & 0x10;
      v15 = *(_DWORD *)v27;
      *(_BYTE *)a1 &= ~0x20u;
      *(_DWORD *)a1 |= v15 & 0x20;
    }
    if ( (*a4 & 0x20) == 0 )
    {
      v16 = *(_DWORD *)v27;
      *(_BYTE *)(a1 + 1) &= ~2u;
      *(_DWORD *)a1 |= v16 & 0x200;
    }
    if ( (a4[1] & 1) == 0 )
    {
      LOBYTE(v6) = *(_BYTE *)(a1 + 1) & 0xFB;
      v17 = *(_DWORD *)v27;
      *(_BYTE *)(a1 + 1) = v6;
      *(_DWORD *)a1 |= v17 & 0x400;
    }
    if ( (a4[1] & 2) == 0 )
    {
      v18 = *(_DWORD *)v27;
      *(_BYTE *)(a1 + 1) &= ~8u;
      *(_DWORD *)a1 |= v18 & 0x800;
      v19 = *(_DWORD *)v27;
      *(_BYTE *)(a1 + 1) &= ~0x10u;
      *(_DWORD *)a1 |= v19 & 0x1000;
    }
    if ( (a4[1] & 4) == 0 && (v27[1] & 0x20) != 0 )
    {
      Rules_DecrementSymbolCount(*(_DWORD *)(a1 + 12), v6);
      v20 = *((_DWORD *)v27 + 3);
      *(_DWORD *)(a1 + 12) = v20;
      ++*(_DWORD *)(v20 + 4);
      *(_BYTE *)(a1 + 1) |= 0x20u;
    }
    LOWORD(v8) = Rules_OverlayConstraint(a3, *(_DWORD *)(a1 + 20), *((int **)v27 + 5));
  }
  return v8;
}
// 4E3E0C: variable 'v27' is possibly undefined
// 4E3F75: variable 'v6' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004E4040) --------------------------------------------------------
signed int  Class_CheckForFacetConflicts(int a1, int a2)
{
  int v2; // ecx
  int v3; // ecx
  int *v4; // eax
  signed int v5; // eax
  int v6; // ecx
  int *v7; // eax
  signed int v8; // eax
  char v9; // dl
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx

  v2 = a1;
  if ( (*(_BYTE *)a1 & 2) == 0 )
  {
    if ( (*(_BYTE *)(a2 + 1) & 4) != 0 )
    {
      Rules_PrintErrorID((int)aClsltpsr, 3, 1);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCardinalityFac, v11);
      return 0;
    }
    AST_Free(*(_DWORD *)(*(_DWORD *)(a1 + 20) + 18));
    AST_Free(*(_DWORD *)(*(_DWORD *)(v3 + 20) + 22));
    v4 = Rules_AddIntegerValue(1);
    v5 = AST_NewNode(1, (int)v4);
    *(_DWORD *)(*(_DWORD *)(v6 + 20) + 18) = v5;
    v7 = Rules_AddIntegerValue(1);
    v8 = AST_NewNode(1, (int)v7);
    *(_DWORD *)(*(_DWORD *)(v2 + 20) + 22) = v8;
  }
  if ( (*(_BYTE *)(v2 + 1) & 1) != 0 && (*(_BYTE *)v2 & 0x10) != 0 )
  {
    Rules_PrintErrorID((int)aClsltpsr, 4, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aReadOnlySlotsM, v12);
    return 0;
  }
  else if ( (*(_BYTE *)v2 & 0x10) != 0 && ((v9 = *(_BYTE *)(v2 + 1), (v9 & 0x10) != 0) || (v9 & 0x20) != 0) )
  {
    Rules_PrintErrorID((int)aClsltpsr, 5, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aReadOnlySlotsC, v13);
    return 0;
  }
  else if ( (*(_BYTE *)v2 & 8) != 0 && (*(_BYTE *)(v2 + 1) & 4) != 0 )
  {
    Rules_PrintErrorID((int)aClsltpsr, 6, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoInheritSlots, v14);
    return 0;
  }
  else
  {
    return 1;
  }
}
// 4E405E: variable 'v3' is possibly undefined
// 4E407F: variable 'v6' is possibly undefined
// 4E409B: variable 'v2' is possibly undefined
// 4E40F3: variable 'v11' is possibly undefined
// 4E411B: variable 'v12' is possibly undefined
// 4E4143: variable 'v13' is possibly undefined
// 4E416B: variable 'v14' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004E4180) --------------------------------------------------------
signed int  Class_EvaluateSlotDefaultValue(int *a1, char *a2, double a3)
{
  _DWORD *v4; // ecx
  _DWORD *v5; // eax
  int v6; // ebx
  int v7; // ecx
  int v9; // edi
  int v10; // edx
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  int v14; // edx
  _DWORD *v15; // ebx
  void *v16; // eax
  signed int v17; // esi
  int v18; // ecx
  _DWORD v19[11]; // [esp+0h] [ebp-2Ch] BYREF

  if ( *a2 >= 0 )
    *(_BYTE *)a1 &= ~0x40u;
  if ( (*((_BYTE *)a1 + 1) & 1) != 0 )
    return 1;
  if ( (*(_BYTE *)a1 & 0x40) != 0 )
  {
    if ( !Rules_StaticConstraintCheckingEnabled() )
      return 1;
    v17 = Rules_CheckFieldExprListAgainstConstraint((int *)a1[4], a1[5]);
    if ( !v17 )
      return 1;
    Rules_PrintErrorID((int)aCstrnchk_3, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpressionFo_0, (int)aDynamicDefault);
    Instance_PrintSlotErrorContext((int)g_IO_LogicalNameTable_WError[0], (int)a1, v18, 0);
    Rules_PrintConstraintViolationMessage(0, 0, 0, 0, 0, 0, v17, a1[5], 0);
    return 0;
  }
  else
  {
    if ( (*a2 & 0x40) == 0 )
    {
      if ( *(char *)a1 < 0 )
        return 1;
      v4 = *(_DWORD **)(g_ClipsMemoryTable + 96);
      if ( v4 )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 96);
        *(_DWORD *)(g_ClipsMemoryTable + 96) = *v4;
        v5 = (_DWORD *)g_ClipsMemFreeListTemp;
      }
      else
      {
        v5 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x18);
      }
      v6 = *a1;
      a1[4] = (int)v5;
      Rules_DeriveDefaultFromConstraints((char *)a1[5], v5, (unsigned int)(v6 << 30) >> 31);
LABEL_10:
      Rules_ValueInstall(a1[4], v7);
      return 1;
    }
    v9 = Rules_GetReentryGuardFlag();
    Rules_SetReentryGuardFlag(1);
    Rules_StaticConstraintCheckingEnabled();
    unknown_libname_10(v11, v10);
    v12 = Parser_ParseSlotDefaultOrRestriction((unsigned int)(*a1 << 30) >> 31, a1[4], v19, a3);
    if ( v12 )
      v12 = Instance_ValidateSlotValueConstraints(v19, (int)a1, 0);
    unknown_libname_10(v13, v12);
    Rules_SetReentryGuardFlag(v9);
    if ( v14 )
    {
      AST_DeinstallNodeChain((__int16 *)a1[4]);
      AST_FreePackedNodeChain(a1[4]);
      v15 = *(_DWORD **)(g_ClipsMemoryTable + 96);
      if ( v15 )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 96);
        *(_DWORD *)(g_ClipsMemoryTable + 96) = *v15;
        v16 = (void *)g_ClipsMemFreeListTemp;
      }
      else
      {
        v16 = (void *)Mem_HeapAllocWithRetry((_DWORD *)0x18);
      }
      a1[4] = (int)v16;
      qmemcpy(v16, v19, 0x18u);
      v7 = 0;
      goto LABEL_10;
    }
    *(_BYTE *)a1 |= 0x40u;
    return 0;
  }
}
// 4E41E0: variable 'v7' is possibly undefined
// 4E420F: variable 'v11' is possibly undefined
// 4E420F: variable 'v10' is possibly undefined
// 4E4243: variable 'v13' is possibly undefined
// 4E4251: variable 'v14' is possibly undefined
// 4E4320: variable 'v18' is possibly undefined
// 4971A0: using guessed type int __fastcall unknown_libname_10(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004E4C6D) --------------------------------------------------------
_DWORD * CRT_ResizeHeapBlockLocked(_DWORD *a1, unsigned int a2, unsigned int a3)
{
  unsigned int v6[4]; // [esp-Ch] [ebp-10h] BYREF

  v6[2] = a3;
  g_CRT_StaticLock2AcquireHook();
  if ( CRT_ResizeHeapBlockInPlace(__DS__, a1, v6, a2, a1) )
  {
    g_CRT_StaticLock2ReleaseHook();
    return 0;
  }
  else
  {
    g_CRT_StaticLock2ReleaseHook();
    return a1;
  }
}
// 485379: using guessed type _DWORD nullsub_8();
// 51A584: using guessed type _DWORD (*off_51A584)();
// 51A58C: using guessed type _DWORD (*off_51A58C)();

//----- (004E4CA7) --------------------------------------------------------
signed int  CRT_ResizeHeapBlockInPlace(
        __int16 a1,
        _DWORD *a2,
        unsigned int *a3,
        unsigned int a4,
        _DWORD *i)
{
  unsigned int v6; // eax
  unsigned int v7; // edx
  unsigned int v8; // eax
  unsigned int *j; // ebx
  unsigned int v10; // ebp
  int v11; // ebp
  unsigned int *v12; // edx
  unsigned int v13; // eax
  unsigned int *v14; // ebx
  unsigned int v15; // edx
  unsigned int v16; // ebx
  unsigned int *v19; // [esp+4h] [ebp-18h]
  unsigned int v20; // [esp+8h] [ebp-14h]
  unsigned int v21; // [esp+Ch] [ebp-10h]

  v6 = a4 + 11;
  LOBYTE(v6) = (a4 + 11) & 0xF8;
  if ( v6 >= a4 )
  {
    if ( v6 < 0x10 )
      v6 = 16;
  }
  else
  {
    v6 = -1;
  }
  v19 = a2 - 1;
  v7 = *(a2 - 1);
  LOBYTE(v7) = v7 & 0xFE;
  if ( v6 <= v7 )
  {
    v15 = v7 - v6;
    if ( v15 >= 0x10 )
    {
      v16 = v6;
      LOBYTE(v16) = v6 | 1;
      LOBYTE(v15) = v15 | 1;
      *v19 = v16;
      *(unsigned int *)((char *)v19 + v6) = v15;
      if ( __DS__ == a1 )
      {
        for ( i = (_DWORD *)g_CRT_HeapSegmentListHead; i[2] && (i > a2 || (_DWORD *)((char *)i + *i) <= a2); i = (_DWORD *)i[2] )
          ;
      }
      ++i[6];
      nfree_(v19);
    }
    return 0;
  }
  else
  {
    v8 = v6 - v7;
    for ( j = (unsigned int *)((char *)v19 + v7); ; j = (unsigned int *)((char *)j + v10) )
    {
      *a3 = v8;
      v10 = *j;
      if ( *j == -1 )
        return 2;
      if ( (v10 & 1) != 0 )
        break;
      v21 = j[2];
      v20 = j[1];
      if ( __DS__ == a1 )
      {
        for ( i = (_DWORD *)g_CRT_HeapSegmentListHead; i[2] && (i > a2 || (_DWORD *)((char *)i + *i) <= a2); i = (_DWORD *)i[2] )
          ;
      }
      v12 = (unsigned int *)i[3];
      if ( j == v12 )
        i[3] = v12[1];
      if ( v10 >= *a3 )
      {
        v13 = v10 - *a3;
        if ( v13 >= 0x10 )
        {
          v14 = (unsigned int *)((char *)j + *a3);
          *v14 = v13;
          v14[1] = v20;
          v14[2] = v21;
          *(_DWORD *)(v20 + 8) = v14;
          *(_DWORD *)(v21 + 4) = v14;
          v11 = 0;
          *v19 += *a3;
          g_CRT_HeapCoalesceStateByte = 0;
          return v11;
        }
      }
      *(_DWORD *)(v20 + 8) = v21;
      *(_DWORD *)(v21 + 4) = v20;
      *v19 += v10;
      --i[7];
      g_CRT_HeapCoalesceStateByte = 0;
      if ( v10 >= *a3 )
        return 0;
      v8 = *a3 - v10;
    }
    return 1;
  }
}
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 519F14: using guessed type int dword_519F14;
// 54E511: using guessed type char byte_54E511;

//----- (004E4F71) --------------------------------------------------------
BOOL __cdecl CRT_ThreadStartTrampoline(LPVOID lpThreadParameter)
{
  int v1; // ecx
  int v2; // edx
  int v3; // eax
  void *v4; // esp
  int v5; // ecx
  HANDLE v7; // ebx
  int v8; // ecx
  _BYTE v9[8]; // [esp+0h] [ebp-10h] BYREF
  void (*v10)(void); // [esp+8h] [ebp-8h]
  HANDLE hObject; // [esp+Ch] [ebp-4h]

  v10 = *(void (**)(void))lpThreadParameter;
  v2 = g_CrtThreadDataMgmtDisabledFlag;
  hObject = (HANDLE)**((_DWORD **)lpThreadParameter + 4);
  if ( g_CrtThreadDataMgmtDisabledFlag
    || (v3 = g_CRT_ThreadDataBlockSize + 3,
        LOBYTE(v3) = (g_CRT_ThreadDataBlockSize + 3) & 0xFC,
        v4 = alloca(v3),
        memset_(v9, 0),
        *(_DWORD *)(v5 + 240) = g_CRT_ThreadDataBlockSize,
        CRT_CreateAndAttachThreadData(v5, v5)) )
  {
    v7 = hObject;
    *(_DWORD *)(g_CrtThreadDataAccessor(v1, v2) + 222) = v7;
    SetEvent(*((HANDLE *)lpThreadParameter + 3));
    CRT_InstallUnhandledExceptionFilter((int)v9, v8);
    g_CRT_ThreadStartupHook();
    v10();
    endthread_();
  }
  return CloseHandle(hObject);
}
// 4E4FBC: variable 'v5' is possibly undefined
// 4E4FDD: variable 'v1' is possibly undefined
// 4E4FDD: variable 'v2' is possibly undefined
// 4E4FF7: variable 'v8' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 485379: using guessed type _DWORD nullsub_8();
// 4D9788: using guessed type void __noreturn endthread_(void);
// 51A568: using guessed type __int64 (__fastcall *g_CrtThreadDataAccessor)(_DWORD, _DWORD);
// 51A5A8: using guessed type _DWORD (*off_51A5A8)();
// 51AF00: using guessed type int dword_51AF00;

//----- (004E5018) --------------------------------------------------------
HANDLE  CRT_BeginThread(int a1, int a2, int a3)
{
  int v3; // ecx
  HANDLE result; // eax
  DWORD CurrentThreadId; // eax
  CHAR v7[32]; // [esp+0h] [ebp-50h] BYREF
  _DWORD Parameter[3]; // [esp+20h] [ebp-30h] BYREF
  HANDLE hHandle; // [esp+2Ch] [ebp-24h]
  HANDLE *v10; // [esp+30h] [ebp-20h]
  HANDLE Thread; // [esp+34h] [ebp-1Ch] BYREF
  DWORD ThreadId[6]; // [esp+38h] [ebp-18h] BYREF

  v3 = a1;
  if ( dwTlsIndex == -1 )
  {
    result = (HANDLE)CRT_AllocateTlsIndex();
    if ( !result )
      return result;
    CRT_InitializeThreadAndFileHandleHooks();
  }
  Parameter[0] = v3;
  Parameter[1] = a3;
  Parameter[2] = GetCurrentThread();
  strcpy(v7, "__bgnthd");
  CurrentThreadId = GetCurrentThreadId();
  Str_FormatSignedRadixDigits(CurrentThreadId, &v7[8], 0x10u);
  hHandle = CreateEventA(0, 0, 0, v7);
  v10 = &Thread;
  Thread = CreateThread(0, (a2 + 4095) & 0xFFFFF000, (LPTHREAD_START_ROUTINE)CRT_ThreadStartTrampoline, Parameter, 0, ThreadId);
  if ( Thread )
    WaitForSingleObject(hHandle, 0xFFFFFFFF);
  else
    ThreadId[0] = -1;
  CloseHandle(hHandle);
  return Thread;
}
// 4E503F: variable 'v3' is possibly undefined

//----- (004E50F1) --------------------------------------------------------
void __fastcall __noreturn CRT_EndThread(int a1, int a2)
{
  int v2; // edx
  int v3; // ecx

  g_CRT_ThreadEndHook(a2, a1);
  CRT_RemoveUnhandledExceptionFilter(v3, v2);
  if ( !g_CrtThreadDataMgmtDisabledFlag )
    CRT_DetachThreadDataAndMaybeCloseHandle((char *)1);
  ExitThread(0);
}
// 4E50F9: variable 'v3' is possibly undefined
// 4E50F9: variable 'v2' is possibly undefined
// 51A5AC: using guessed type int (__cdecl *off_51A5AC)(_DWORD, _DWORD);

//----- (004E51E0) --------------------------------------------------------
_DWORD * AST_BuildClassHierarchyFieldAccessTest(_DWORD *a1, int a2)
{
  int v2; // edi
  _DWORD *v3; // ebp
  _DWORD *v4; // edi
  _DWORD *v5; // esi
  int v6; // ecx
  _DWORD *v7; // esi
  int v8; // ecx
  int v9; // edx
  _DWORD *v10; // eax
  _DWORD *result; // eax
  _DWORD *v12; // eax
  _DWORD *v13; // [esp+0h] [ebp-30h] BYREF
  _DWORD *v14; // [esp+4h] [ebp-2Ch] BYREF
  int v15; // [esp+8h] [ebp-28h]
  _DWORD *v16; // [esp+Ch] [ebp-24h]
  int v17; // [esp+10h] [ebp-20h]
  _DWORD *v18; // [esp+14h] [ebp-1Ch]
  _DWORD *i; // [esp+18h] [ebp-18h]

  v16 = a1;
  v15 = a2;
  v17 = 1;
  v13 = 0;
  v14 = 0;
  if ( !a1 )
  {
    Rules_ReportSystemError(0, 3);
    IO_RunRouterExitCallbacks();
  }
  v2 = v16[17];
  if ( v2 && *(_DWORD *)(v2 + 68) )
    v17 = AST_IsFieldAccessHomogeneousAcrossHierarchy(v16[17], v16[7]);
  v3 = 0;
  v4 = 0;
  v18 = 0;
  v5 = (_DWORD *)v16[17];
  for ( i = 0; v5; v5 = (_DWORD *)v5[17] )
  {
    AST_AccumulateFieldAccessTestChain(v5, v17, (signed int *)&v14, (signed int *)&v13);
    if ( v13 )
    {
      if ( v3 )
        *(_DWORD *)((char *)v3 + 10) = v13;
      else
        v18 = v13;
      v3 = v13;
    }
    if ( v14 )
    {
      if ( v4 )
        *(_DWORD *)((char *)v4 + 10) = v14;
      else
        i = v14;
      v4 = v14;
    }
  }
  if ( v18 && *(_DWORD *)((char *)v18 + 10) )
  {
    v18 = (_DWORD *)AST_NewNode(10, g_ClipsSymbolOr);
    *(_DWORD *)((char *)v18 + 6) = v6;
  }
  v7 = i;
  if ( i && *(_DWORD *)((char *)i + 10) )
  {
    i = (_DWORD *)AST_NewNode(10, g_ClipsSymbolOr);
    *(_DWORD *)((char *)i + 6) = v7;
  }
  if ( *v16 == 16 || *v16 == 15 )
  {
    v8 = v16[5];
    if ( v8 )
    {
      v9 = v16[5];
      if ( *(_DWORD *)(v8 + 28) == v16[7] )
      {
        v12 = (_DWORD *)AST_InvokeFieldAccessValidator((int)v16, (int)v16);
        v18 = AST_MergeFieldAccessNodes(v12, v18);
      }
      else if ( *(int *)(v9 + 28) > 0 )
      {
        v10 = (_DWORD *)AST_BuildCrossClassFieldAccessTest((int)v16, v9);
        i = AST_MergeFieldAccessNodes(v10, i);
      }
    }
  }
  v16[13] = v18;
  result = AST_MergeFieldAccessNodes(*(_DWORD **)(v15 + 52), i);
  *(_DWORD *)(v15 + 52) = result;
  return result;
}
// 4E52B5: variable 'v6' is possibly undefined
// 54E664: using guessed type int dword_54E664;

//----- (004E53B0) --------------------------------------------------------
_DWORD * AST_AccumulateFieldAccessTestChain(_DWORD *result, int a2, signed int *a3, signed int *a4)
{
  int v4; // esi
  _DWORD *v6; // [esp+0h] [ebp-18h] BYREF
  _DWORD *v7; // [esp+4h] [ebp-14h] BYREF
  int v8; // [esp+8h] [ebp-10h]

  v4 = (int)result;
  v8 = a2;
  *a4 = 0;
  *a3 = 0;
  if ( result )
  {
    do
    {
      AST_DispatchFieldAccessNodeBuild(v4, v8, &v7, &v6);
      *a4 = (signed int)AST_MergeFieldAccessNodes((_DWORD *)*a4, v6);
      result = AST_MergeFieldAccessNodes((_DWORD *)*a3, v7);
      *a3 = (signed int)result;
      v4 = *(_DWORD *)(v4 + 64);
    }
    while ( v4 );
  }
  return result;
}

//----- (004E5420) --------------------------------------------------------
int  AST_DispatchFieldAccessNodeBuild(int a1, int a2, _DWORD *a3, _DWORD *a4)
{
  int result; // eax
  unsigned int v6; // edx
  _DWORD *v7; // ecx
  _DWORD *v8; // ecx
  _DWORD *v9; // ecx
  int v10; // eax
  _DWORD *v11; // ecx

  result = a2;
  *a4 = 0;
  *a3 = 0;
  v6 = *(_DWORD *)a1;
  if ( *(_DWORD *)a1 == 3 || v6 == 2 || v6 == 8 || v6 < 2 )
  {
    if ( result == 1 )
    {
      result = AST_BuildFieldAccessNodePN(a1);
      *a4 = result;
    }
    else
    {
      result = AST_BuildFieldAccessNodeJN(a1);
      *v7 = result;
    }
  }
  else
  {
    switch ( v6 )
    {
      case 0x5Du:
        if ( result == 1 && AST_IsFieldPositionConsistent(*(_DWORD **)(a1 + 56), *(_DWORD *)(a1 + 28)) == 1 )
        {
          result = AST_BuildNegatedFieldAccessNodeJN(a1);
          *a4 = result;
        }
        else
        {
          result = AST_BuildNegatedFieldAccessNodePN(a1);
          *v8 = result;
        }
        break;
      case 0x5Eu:
        if ( result == 1 && AST_IsFieldPositionConsistent(*(_DWORD **)(a1 + 56), *(_DWORD *)(a1 + 28)) == 1 )
        {
          result = AST_BuildFieldAccessComparisonNodeJN(a1);
          *a4 = result;
        }
        else
        {
          result = AST_BuildFieldAccessComparisonNodePN(a1);
          *v9 = result;
        }
        break;
      case 0xFu:
      case 0x10u:
        if ( result == 1 && (v10 = *(_DWORD *)(a1 + 20)) != 0 && *(_DWORD *)(v10 + 28) == *(_DWORD *)(a1 + 28) )
        {
          result = AST_InvokeFieldAccessValidator(a1, (int)a3);
          *a4 = result;
        }
        else
        {
          result = AST_BuildCrossClassFieldAccessTest(a1, *(_DWORD *)(a1 + 20));
          *v11 = result;
        }
        break;
    }
  }
  return result;
}
// 4E5454: simplified comparisons for 'edx.4': ==0 || ==1 became <2u
// 4E5487: variable 'v7' is possibly undefined
// 4E5492: variable 'v8' is possibly undefined
// 4E54C2: variable 'v9' is possibly undefined
// 4E5506: variable 'v11' is possibly undefined

//----- (004E5510) --------------------------------------------------------
int  AST_BuildFieldAccessNodePN(int a1)
{
  int v2; // eax
  int v3; // edx
  signed int v4; // ebx
  int v5; // ecx
  _DWORD *v6; // ecx

  v2 = *(_DWORD *)(a1 + 24);
  if ( *(_DWORD *)(v2 + 48) )
    return (*(int (**)(void))(v2 + 48))();
  if ( (*(_BYTE *)(a1 + 8) & 1) != 0 )
    v3 = g_ClipsSymbolNeq;
  else
    v3 = g_ClipsSymbolEq;
  v4 = AST_NewNode(10, v3);
  *(_DWORD *)(v4 + 6) = (*(int (**)(void))(*(_DWORD *)(v5 + 24) + 56))();
  *(_DWORD *)(*(_DWORD *)(v4 + 6) + 10) = AST_NewNode(*v6, v6[1]);
  return v4;
}
// 4E5536: variable 'v5' is possibly undefined
// 4E5544: variable 'v6' is possibly undefined
// 54E658: using guessed type int dword_54E658;
// 54E668: using guessed type int dword_54E668;

//----- (004E5570) --------------------------------------------------------
int  AST_BuildFieldAccessNodeJN(int a1)
{
  int v2; // eax
  int v3; // edx
  signed int v4; // ebx
  int v5; // ecx
  _DWORD *v6; // ecx

  v2 = *(_DWORD *)(a1 + 24);
  if ( *(_DWORD *)(v2 + 32) )
    return (*(int (**)(void))(v2 + 32))();
  if ( (*(_BYTE *)(a1 + 8) & 1) != 0 )
    v3 = g_ClipsSymbolNeq;
  else
    v3 = g_ClipsSymbolEq;
  v4 = AST_NewNode(10, v3);
  *(_DWORD *)(v4 + 6) = (*(int (**)(void))(*(_DWORD *)(v5 + 24) + 40))();
  *(_DWORD *)(*(_DWORD *)(v4 + 6) + 10) = AST_NewNode(*v6, v6[1]);
  return v4;
}
// 4E5596: variable 'v5' is possibly undefined
// 4E55A4: variable 'v6' is possibly undefined
// 54E658: using guessed type int dword_54E658;
// 54E668: using guessed type int dword_54E668;

//----- (004E55D0) --------------------------------------------------------
int  AST_BuildNegatedFieldAccessNodePN(int a1)
{
  int result; // eax
  int v2; // edx
  int v3; // ecx

  result = AST_CloneFieldAccessSubtreePN(*(_DWORD *)(a1 + 56));
  if ( (*(_BYTE *)(v2 + 8) & 1) != 0 )
  {
    result = AST_NewNode(10, g_ClipsNotSymbol);
    *(_DWORD *)(result + 6) = v3;
  }
  return result;
}
// 4E55DE: variable 'v2' is possibly undefined
// 4E55F9: variable 'v3' is possibly undefined
// 54E660: using guessed type int dword_54E660;

//----- (004E5600) --------------------------------------------------------
int  AST_BuildNegatedFieldAccessNodeJN(int a1)
{
  int result; // eax
  int v2; // edx
  int v3; // ecx

  result = AST_CloneFieldAccessSubtreeJN(*(_DWORD *)(a1 + 56));
  if ( (*(_BYTE *)(v2 + 8) & 1) != 0 )
  {
    result = AST_NewNode(10, g_ClipsNotSymbol);
    *(_DWORD *)(result + 6) = v3;
  }
  return result;
}
// 4E560E: variable 'v2' is possibly undefined
// 4E5629: variable 'v3' is possibly undefined
// 54E660: using guessed type int dword_54E660;

//----- (004E5630) --------------------------------------------------------
int  AST_BuildFieldAccessComparisonNodePN(int a1)
{
  int v1; // esi
  int v2; // ecx
  int v3; // edx
  int v4; // ecx
  __int64 v5; // rax

  v1 = AST_CloneFieldAccessSubtreePN(*(_DWORD *)(a1 + 56));
  if ( (*(_BYTE *)(v2 + 8) & 1) != 0 )
    v3 = g_ClipsSymbolNeq;
  else
    v3 = g_ClipsSymbolEq;
  AST_NewNode(10, v3);
  v5 = ((__int64 (*)(void))*(_DWORD *)(*(_DWORD *)(v4 + 24) + 40))();
  *(_DWORD *)(HIDWORD(v5) + 6) = v5;
  *(_DWORD *)(v5 + 10) = v1;
  return HIDWORD(v5);
}
// 4E5640: variable 'v2' is possibly undefined
// 4E5658: variable 'v4' is possibly undefined
// 54E658: using guessed type int dword_54E658;
// 54E668: using guessed type int dword_54E668;

//----- (004E5680) --------------------------------------------------------
int  AST_BuildFieldAccessComparisonNodeJN(int a1)
{
  int v1; // esi
  int v2; // ecx
  int v3; // edx
  int v4; // ecx
  __int64 v5; // rax

  v1 = AST_CloneFieldAccessSubtreeJN(*(_DWORD *)(a1 + 56));
  if ( (*(_BYTE *)(v2 + 8) & 1) != 0 )
    v3 = g_ClipsSymbolNeq;
  else
    v3 = g_ClipsSymbolEq;
  AST_NewNode(10, v3);
  v5 = ((__int64 (*)(void))*(_DWORD *)(*(_DWORD *)(v4 + 24) + 56))();
  *(_DWORD *)(HIDWORD(v5) + 6) = v5;
  *(_DWORD *)(v5 + 10) = v1;
  return HIDWORD(v5);
}
// 4E5690: variable 'v2' is possibly undefined
// 4E56A8: variable 'v4' is possibly undefined
// 54E658: using guessed type int dword_54E658;
// 54E668: using guessed type int dword_54E668;

//----- (004E56D0) --------------------------------------------------------
int  AST_CloneFieldAccessSubtreePN(int result)
{
  int v1; // edx
  _DWORD *v2; // ebx
  signed int v3; // ecx
  int v4; // eax
  int v5; // ecx
  int v6; // edx
  int v7; // eax
  _DWORD *v8; // edx
  int v9; // ecx
  int v10; // ebx

  v1 = result;
  if ( result )
  {
    v2 = *(_DWORD **)(g_ClipsMemoryTable + 56);
    if ( v2 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 56);
      *(_DWORD *)(g_ClipsMemoryTable + 56) = *v2;
      v3 = g_ClipsMemFreeListTemp;
    }
    else
    {
      v3 = Mem_HeapAllocWithRetry((_DWORD *)0xE);
    }
    *(_WORD *)v3 = *(_WORD *)v1;
    *(_DWORD *)(v3 + 2) = *(_DWORD *)(v1 + 4);
    v4 = AST_CloneFieldAccessSubtreePN(*(_DWORD *)(v1 + 64));
    *(_DWORD *)(v5 + 10) = v4;
    v7 = AST_CloneFieldAccessSubtreePN(*(_DWORD *)(v6 + 68));
    *(_DWORD *)(v9 + 6) = v7;
    v10 = v9;
    if ( *v8 == 15 || *v8 == 16 )
    {
      (*(void (**)(void))(*(_DWORD *)(v8[5] + 24) + 36))();
    }
    else if ( *(_WORD *)v9 == 13 )
    {
      Defglobal_ResolveGlobalVariableReference(v9, v9);
      return v10;
    }
    return v10;
  }
  return result;
}
// 4E570C: variable 'v5' is possibly undefined
// 4E570F: variable 'v6' is possibly undefined
// 4E5717: variable 'v9' is possibly undefined
// 4E571A: variable 'v8' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004E5760) --------------------------------------------------------
int  AST_CloneFieldAccessSubtreeJN(int result)
{
  int v1; // edx
  _DWORD *v2; // ebx
  signed int v3; // ecx
  int v4; // eax
  int v5; // ecx
  int v6; // edx
  int v7; // eax
  _DWORD *v8; // edx
  int v9; // ecx
  int v10; // ebx

  v1 = result;
  if ( result )
  {
    v2 = *(_DWORD **)(g_ClipsMemoryTable + 56);
    if ( v2 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 56);
      *(_DWORD *)(g_ClipsMemoryTable + 56) = *v2;
      v3 = g_ClipsMemFreeListTemp;
    }
    else
    {
      v3 = Mem_HeapAllocWithRetry((_DWORD *)0xE);
    }
    *(_WORD *)v3 = *(_WORD *)v1;
    *(_DWORD *)(v3 + 2) = *(_DWORD *)(v1 + 4);
    v4 = AST_CloneFieldAccessSubtreeJN(*(_DWORD *)(v1 + 64));
    *(_DWORD *)(v5 + 10) = v4;
    v7 = AST_CloneFieldAccessSubtreeJN(*(_DWORD *)(v6 + 68));
    *(_DWORD *)(v9 + 6) = v7;
    v10 = v9;
    if ( *v8 == 15 || *v8 == 16 )
    {
      (*(void (**)(void))(*(_DWORD *)(v8[5] + 24) + 52))();
    }
    else if ( *(_WORD *)v9 == 13 )
    {
      Defglobal_ResolveGlobalVariableReference(v9, v9);
      return v10;
    }
    return v10;
  }
  return result;
}
// 4E579C: variable 'v5' is possibly undefined
// 4E579F: variable 'v6' is possibly undefined
// 4E57A7: variable 'v9' is possibly undefined
// 4E57AA: variable 'v8' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004E57F0) --------------------------------------------------------
int  AST_BuildCrossClassFieldAccessTest(int a1, int a2)
{
  int v4; // eax
  int v5; // edx
  int v6; // edx
  int v7; // ecx
  __int64 v8; // rax
  __int64 v9; // rax

  v4 = *(_DWORD *)(a1 + 24);
  if ( !*(_DWORD *)(v4 + 44) )
    return 0;
  v5 = *(_DWORD *)(a2 + 24);
  if ( !*(_DWORD *)(v5 + 44) )
    return 0;
  if ( *(_DWORD *)(v4 + 44) == *(_DWORD *)(v5 + 44) )
    return (*(int (**)(void))(v4 + 44))();
  if ( (*(_BYTE *)(a1 + 8) & 1) != 0 )
    v6 = g_ClipsSymbolNeq;
  else
    v6 = g_ClipsSymbolEq;
  AST_NewNode(10, v6);
  v8 = ((__int64 (*)(void))*(_DWORD *)(*(_DWORD *)(v7 + 24) + 40))();
  *(_DWORD *)(HIDWORD(v8) + 6) = v8;
  v9 = ((__int64 (*)(void))*(_DWORD *)(*(_DWORD *)(a2 + 24) + 40))();
  *(_DWORD *)(*(_DWORD *)(HIDWORD(v9) + 6) + 10) = v9;
  return HIDWORD(v9);
}
// 4E5829: variable 'v7' is possibly undefined
// 54E658: using guessed type int dword_54E658;
// 54E668: using guessed type int dword_54E668;

//----- (004E5870) --------------------------------------------------------
int  AST_InvokeFieldAccessValidator(int a1, int a2)
{
  int v2; // ecx

  v2 = *(_DWORD *)(a1 + 24);
  if ( *(_DWORD *)(v2 + 60) )
    return (*(int (__cdecl **)(int))(v2 + 60))(a2);
  else
    return 0;
}

//----- (004E5890) --------------------------------------------------------
int  AST_IsFieldAccessHomogeneousAcrossHierarchy(int a1, int a2)
{
  int v2; // esi
  int v4; // ecx
  int v5; // edx
  int result; // eax

  v2 = a1;
  if ( !a1 )
    return 1;
  while ( 1 )
  {
    v4 = v2;
    if ( v2 )
      break;
LABEL_6:
    v2 = *(_DWORD *)(v2 + 68);
    if ( !v2 )
      return 1;
  }
  while ( 1 )
  {
    v5 = *(_DWORD *)v4;
    if ( *(_DWORD *)v4 == 15 || v5 == 16 )
      break;
    if ( v5 == 93 || v5 == 94 )
    {
      result = AST_IsFieldPositionConsistent(*(_DWORD **)(v4 + 56), a2);
      if ( !result )
        return result;
    }
LABEL_5:
    v4 = *(_DWORD *)(v4 + 64);
    if ( !v4 )
      goto LABEL_6;
  }
  if ( a2 == *(_DWORD *)(*(_DWORD *)(v4 + 20) + 28) )
    goto LABEL_5;
  return 0;
}
// 4E58B0: variable 'v4' is possibly undefined

//----- (004E58F0) --------------------------------------------------------
int  AST_IsFieldPositionConsistent(_DWORD *a1, int a2)
{
  _DWORD *v2; // ecx
  int result; // eax
  int v5; // ecx

  v2 = a1;
  if ( !a1 )
    return 1;
  while ( *v2 != 15 && *v2 != 16 || a2 == *(_DWORD *)(v2[5] + 28) )
  {
    result = AST_IsFieldPositionConsistent(v2[17], a2);
    if ( !result )
      return result;
    v2 = *(_DWORD **)(v5 + 64);
    if ( !v2 )
      return 1;
  }
  return 0;
}
// 4E5921: variable 'v5' is possibly undefined

//----- (004E5C90) --------------------------------------------------------
unsigned int  CRT_StrToXLong(unsigned __int8 *a1, int *a2, int a3, signed int a4)
{
  signed int v5; // esi
  unsigned __int8 *i; // edx
  unsigned __int8 v7; // cl
  unsigned __int8 v9; // bh
  unsigned int v10; // ebx
  int v11; // edx
  unsigned int v12; // eax
  char v13; // ch
  unsigned __int8 *v15; // [esp+4h] [ebp-18h]
  int v16; // [esp+8h] [ebp-14h]
  int v17; // [esp+Ch] [ebp-10h]

  v5 = a4;
  v17 = a3;
  if ( a2 )
    *a2 = (int)a1;
  for ( i = a1; (IsTable[(unsigned __int8)(*i + 1)] & 2) != 0; ++i )
    ;
  BYTE1(a3) = *i;
  if ( *i == 43 || BYTE1(a3) == 45 )
    ++i;
  if ( a4 )
  {
    if ( a4 < 2 || a4 > 36 )
    {
      _set_errno_((int)a1);
      return 0;
    }
    if ( a4 == 16 )
      goto LABEL_21;
  }
  else
  {
    if ( *i == 48 )
    {
      v7 = i[1];
      if ( v7 == 120 || v7 == 88 )
      {
        v5 = 16;
LABEL_21:
        if ( *i == 48 )
        {
          v9 = i[1];
          if ( v9 == 120 || v9 == 88 )
            i += 2;
        }
        goto LABEL_25;
      }
    }
    if ( *i == 48 )
      v5 = 8;
    else
      v5 = 10;
  }
LABEL_25:
  v15 = i;
  LOBYTE(a3) = 0;
  v10 = 0;
  while ( 1 )
  {
    v16 = CRT_DigitCharToValue(*i, (int)i, a3);
    if ( v16 >= v5 )
      break;
    if ( v10 > (unsigned int)g_StrToLongOverflowLimitTable[v5] )
      LOBYTE(a3) = 1;
    v12 = v10;
    v10 = v16 + v5 * v10;
    if ( v10 < v12 )
      LOBYTE(a3) = 1;
    i = (unsigned __int8 *)(v11 + 1);
  }
  if ( (unsigned __int8 *)v11 == v15 )
    v11 = (int)a1;
  if ( a2 )
    *a2 = v11;
  if ( (v17 != 1 || v10 < 0x80000000 || v10 == 0x80000000 && BYTE1(a3) == 45) && !(_BYTE)a3 )
  {
    if ( BYTE1(a3) == 45 )
      return -v10;
    return v10;
  }
  else
  {
    _set_errno_((int)a1);
    if ( v17 )
    {
      if ( v13 == 45 )
        return 0x80000000;
      else
        return 0x7FFFFFFF;
    }
    else
    {
      return -1;
    }
  }
}
// 4E5D40: variable 'a3' is possibly undefined
// 4E5D66: variable 'v11' is possibly undefined
// 4E5DAF: variable 'v13' is possibly undefined
// 51C790: using guessed type char *off_51C790[2];

//----- (004E5DD9) --------------------------------------------------------
unsigned int  CRT_StrToULongRadix(unsigned __int8 *a1, int *a2, signed int a3)
{
  return CRT_StrToXLong(a1, a2, 1, a3);
}

//----- (004E5DE1) --------------------------------------------------------
int  CRT_DigitCharToValue(unsigned __int8 a1, int a2, int a3)
{
  unsigned __int8 v4; // al

  if ( a1 >= 0x30u && a1 <= 0x39u )
    return a1 - 48;
  v4 = tolower_(a3, a2);
  if ( v4 >= 0x61u && v4 <= 0x69u )
    return v4 - 87;
  if ( v4 >= 0x6Au && v4 <= 0x72u || v4 >= 0x73u && v4 <= 0x7Au )
    return v4 - 87;
  return 37;
}
// 4852ED: using guessed type int __fastcall tolower_(_DWORD, _DWORD);

//----- (004E5F8A) --------------------------------------------------------
void  CRT_PutEnvEntryA(_BYTE *a1, _BYTE *i, int a3)
{
  int v3; // ebp
  _DWORD *v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // edx
  int v8; // ecx
  int v9; // eax
  void *v10; // eax
  unsigned int v11; // ecx
  int v12; // eax
  int v13; // ecx
  int v15; // [esp+4h] [ebp-20h]
  int v16; // [esp+8h] [ebp-1Ch]

  if ( a1 )
  {
    if ( *a1 )
    {
      for ( i = a1 + 1; *i && *i != 61; ++i )
        ;
    }
    if ( *i )
    {
      v3 = i[1] == 0;
      v16 = g_CRT_EnvVarPointerArray;
      if ( g_CRT_EnvVarPointerArray )
      {
        v6 = CRT_FindEnvVarIndexA(a1, v3, a3);
        if ( v3 )
          goto LABEL_23;
        if ( v6 > 0 )
        {
          v3 = v6 - 1;
          goto LABEL_22;
        }
        v3 = -v6;
        v8 = -4 * v6;
        v15 = -4 * v6 + 8;
        v9 = 1 - v6 + v15;
        if ( g_RuntimeGrowableByteFlagArrayPtr )
        {
          v12 = nrealloc_(v8, v9);
          v16 = v12;
          if ( !v12 )
            goto LABEL_23;
          memmove_((void *)(uintptr_t)(v12 + v15), (const void *)(uintptr_t)g_RuntimeGrowableByteFlagArrayPtr, (size_t)v3);
          g_RuntimeGrowableByteFlagArrayPtr = v13;
        }
        else
        {
          v10 = (void *)nmalloc_(v8, v7);
          v16 = (int)v10;
          if ( !v10 )
            goto LABEL_23;
          qmemcpy(v10, (const void *)g_CRT_EnvVarPointerArray, v11);
          g_RuntimeGrowableByteFlagArrayPtr = (int)v10 + v15;
          memset_(0, 0);
        }
        g_CRT_EnvVarPointerArray = v16;
        *(_DWORD *)(v16 + 4 * v3 + 4) = 0;
        goto LABEL_22;
      }
      if ( i[1] )
      {
        v4 = (_DWORD *)nmalloc_(a3, i);
        v16 = (int)v4;
        if ( v4 )
        {
          g_CRT_EnvVarPointerArray = (int)v4;
          *v4 = 0;
          v5 = (int)(v4 + 2);
          *(_DWORD *)(v5 - 4) = 0;
          g_RuntimeGrowableByteFlagArrayPtr = v5;
LABEL_22:
          *(_DWORD *)(v16 + 4 * v3) = a1;
          *(_BYTE *)(g_RuntimeGrowableByteFlagArrayPtr + v3) = 0;
        }
      }
    }
  }
LABEL_23:
  // 4E60F0: jumps to the shared register-restore epilogue at 4E5F83 (in putenv_);
  // in C this is the function return.
  return;
}
// 4E60F0: control flows out of bounds to 4E5F83
// 4E603E: variable 'v7' is possibly undefined
// 4E6064: variable 'v11' is possibly undefined
// 4E60AF: variable 'v13' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 47BB96: using guessed type int __fastcall memmove_(_DWORD, _DWORD);
// 4D9607: using guessed type int __fastcall nrealloc_(_DWORD, _DWORD);
// 54E700: using guessed type int dword_54E700;
// 54E704: using guessed type int dword_54E704;

//----- (004E60F5) --------------------------------------------------------
int  CRT_FindEnvVarIndexA(_BYTE *a1, int a2, int a3)
{
  _DWORD *v5; // esi
  _BYTE *i; // ebx
  int v7; // eax
  int v8; // eax
  _BYTE *v9; // edx
  int v10; // edi
  _DWORD *j; // ecx
  int v12; // esi
  int v13; // ecx
  unsigned __int8 *v14; // eax

  v5 = (_DWORD *)g_CRT_EnvVarPointerArray;
LABEL_20:
  if ( !*v5 )
    return (g_CRT_EnvVarPointerArray - (int)v5) >> 2;
  for ( i = a1; ; ++i )
  {
    if ( !*i || (v7 = toupper_(a3), v8 = toupper_(v7), a3 != v8) )
    {
      ++v5;
      goto LABEL_20;
    }
    if ( *v9 == 61 )
      break;
  }
  v10 = ((int)v5 - g_CRT_EnvVarPointerArray) >> 2;
  if ( !a2 )
    return v10 + 1;
  for ( j = v5; *j; ++j )
    *j = j[1];
  if ( g_RuntimeGrowableByteFlagArrayPtr )
  {
    if ( *(_BYTE *)(v10 + g_RuntimeGrowableByteFlagArrayPtr) )
      nfree_(j);
    v12 = ((int)j - g_CRT_EnvVarPointerArray) >> 2;
    memmove_(j, (const void *)(uintptr_t)g_RuntimeGrowableByteFlagArrayPtr, (size_t)v12);
    g_RuntimeGrowableByteFlagArrayPtr = v13;
    if ( v10 < v12 )
    {
      v14 = (unsigned __int8 *)(v10 + g_RuntimeGrowableByteFlagArrayPtr);
      do
      {
        *v14 = v14[1];
        ++v14;
        ++v10;
      }
      while ( v10 < v12 );
    }
  }
  return 0;
}
// 4E6114: variable 'a3' is possibly undefined
// 4E612C: variable 'v9' is possibly undefined
// 4E617A: variable 'j' is possibly undefined
// 4E618E: variable 'v13' is possibly undefined
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 476271: using guessed type int __thiscall toupper_(_DWORD);
// 47BB96: using guessed type int __fastcall memmove_(_DWORD, _DWORD);
// 54E700: using guessed type int dword_54E700;
// 54E704: using guessed type int dword_54E704;

//----- (004E70ED) --------------------------------------------------------
signed int  CRT_PutEnvEntryW(_WORD *a1, _WORD *i)
{
  bool v4; // al
  BOOL v5; // ebx
  _DWORD *v6; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // esi
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // ebp
  int v14; // ecx
  int v15; // eax
  int v16; // ebp
  int v17; // [esp+0h] [ebp-20h]

  if ( !a1 )
    return -1;
  if ( *a1 )
  {
    for ( i = a1 + 1; *i && *i != 61; ++i )
      ;
  }
  if ( !*i )
    return -1;
  v4 = i[1] == 0;
  v5 = v4;
  if ( g_CrtWideEnvironTable )
  {
    v10 = CRT_FindEnvVarIndexW(a1, v4, g_CrtWideEnvironTable);
    if ( !v5 )
    {
      if ( v10 > 0 )
      {
        v9 = v10 - 1;
        goto LABEL_22;
      }
      v9 = -v10;
      v11 = 1 - v10;
      v17 = -4 * v10 + 8;
      v12 = 1 - v10 + v17;
      if ( g_RuntimeGrowableByteFlagArrayPtr )
      {
        v15 = nrealloc_(v7, v12);
        if ( !v15 )
          return -1;
        v16 = v15 + v17;
        memmove_((void *)(uintptr_t)v15, (const void *)(uintptr_t)g_RuntimeGrowableByteFlagArrayPtr, (size_t)v9);
        g_RuntimeGrowableByteFlagArrayPtr = v16;
      }
      else
      {
        v13 = nmalloc_(v7, v11);
        if ( !v13 )
          return -1;
        memcpy_(v13, g_CrtWideEnvironTable);
        g_RuntimeGrowableByteFlagArrayPtr = v13 + v17;
        memset_(v14, 0);
      }
      g_CrtWideEnvironTable = v7;
      *(_DWORD *)(v7 + 4 * v9 + 4) = 0;
      goto LABEL_22;
    }
  }
  else if ( i[1] )
  {
    v6 = (_DWORD *)nmalloc_(0, i);
    v7 = (int)v6;
    if ( v6 )
    {
      g_CrtWideEnvironTable = (int)v6;
      *v6 = 0;
      v8 = (int)(v6 + 2);
      v9 = 0;
      *(_DWORD *)(v8 - 4) = 0;
      g_RuntimeGrowableByteFlagArrayPtr = v8;
LABEL_22:
      *(_DWORD *)(v7 + 4 * v9) = a1;
      *(_BYTE *)(v9 + g_RuntimeGrowableByteFlagArrayPtr) = 0;
      return 0;
    }
    return -1;
  }
  return 0;
}
// 4E71AC: variable 'v7' is possibly undefined
// 4E71D8: variable 'v14' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 47BB96: using guessed type int __fastcall memmove_(_DWORD, _DWORD);
// 4D9607: using guessed type int __fastcall nrealloc_(_DWORD, _DWORD);
// 4D9756: using guessed type int __fastcall memcpy_(_DWORD, _DWORD);
// 54E700: using guessed type int dword_54E700;
// 54E708: using guessed type int dword_54E708;

//----- (004E7239) --------------------------------------------------------
int  CRT_FindEnvVarIndexW(_WORD *a1, int a2, int a3)
{
  _DWORD *v5; // esi
  _WORD *i; // ebx
  int v7; // eax
  __int16 v8; // ax
  _WORD *v9; // edx
  int v10; // edi
  _DWORD *j; // ecx
  int v12; // esi
  int v13; // ecx
  _BYTE *v14; // eax

  v5 = (_DWORD *)g_CrtWideEnvironTable;
LABEL_20:
  if ( !*v5 )
    return (g_CrtWideEnvironTable - (int)v5) >> 2;
  for ( i = a1; ; ++i )
  {
    if ( !*i || (v7 = towupper_(a3), v8 = towupper_(v7), (_WORD)a3 != v8) )
    {
      ++v5;
      goto LABEL_20;
    }
    if ( *v9 == 61 )
      break;
  }
  v10 = ((int)v5 - g_CrtWideEnvironTable) >> 2;
  if ( !a2 )
    return v10 + 1;
  for ( j = v5; *j; ++j )
    *j = j[1];
  if ( g_RuntimeGrowableByteFlagArrayPtr )
  {
    if ( *(_BYTE *)(v10 + g_RuntimeGrowableByteFlagArrayPtr) )
      nfree_(j);
    v12 = ((int)j - g_CrtWideEnvironTable) >> 2;
    memmove_(j, (const void *)(uintptr_t)g_RuntimeGrowableByteFlagArrayPtr, (size_t)v12);
    g_RuntimeGrowableByteFlagArrayPtr = v13;
    v14 = (_BYTE *)(v10 + v13);
    while ( v10 < v12 )
    {
      ++v10;
      *v14 = v14[1];
      ++v14;
    }
  }
  return 0;
}
// 4E7259: variable 'a3' is possibly undefined
// 4E7273: variable 'v9' is possibly undefined
// 4E72C2: variable 'j' is possibly undefined
// 4E72D6: variable 'v13' is possibly undefined
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 47BB96: using guessed type int __fastcall memmove_(_DWORD, _DWORD);
// 4E7DBB: using guessed type int __thiscall towupper_(_DWORD);
// 54E700: using guessed type int dword_54E700;
// 54E708: using guessed type int dword_54E708;

//----- (004E7AAE) --------------------------------------------------------
DWORD __cdecl CRT_SpawnveLaunchProcess(int a1, int a2, LPSTR lpCommandLine, LPVOID lpEnvironment, int a5)
{
  int v5; // ecx
  DWORD dwProcessId; // eax
  HANDLE v8; // eax
  HANDLE hProcess; // [esp-18h] [ebp-88h]
  HANDLE CurrentProcess; // [esp-14h] [ebp-84h]
  struct _STARTUPINFOA StartupInfo; // [esp+0h] [ebp-70h] BYREF
  struct _PROCESS_INFORMATION ProcessInformation; // [esp+44h] [ebp-2Ch] BYREF
  DWORD ExitCode; // [esp+54h] [ebp-1Ch] BYREF
  HANDLE TargetHandle; // [esp+58h] [ebp-18h] BYREF

  _ccmdline_(0, a5);
  memset_(v5, 0);
  StartupInfo.wShowWindow = 1;
  if ( !CreateProcessA(0, lpCommandLine, 0, 0, 1, 0, lpEnvironment, 0, &StartupInfo, &ProcessInformation) )
  {
    GetLastError();
    return _set_errno_dos_(StartupInfo.cb);
  }
  if ( a1 )
  {
    if ( a1 == 3 )
    {
      CloseHandle(ProcessInformation.hProcess);
      dwProcessId = ProcessInformation.dwProcessId;
    }
    else
    {
      CurrentProcess = GetCurrentProcess();
      hProcess = ProcessInformation.hProcess;
      v8 = GetCurrentProcess();
      if ( !DuplicateHandle(v8, hProcess, CurrentProcess, &TargetHandle, 0, 0, 2u) )
        TargetHandle = ProcessInformation.hProcess;
      dwProcessId = (DWORD)TargetHandle;
    }
    ExitCode = dwProcessId;
LABEL_20:
    CloseHandle(ProcessInformation.hThread);
    return ExitCode;
  }
  if ( HIWORD(g_WindowsVersionDword) < 0x8000u || (unsigned __int8)g_WindowsVersionDword >= 4u )
  {
    if ( WaitForSingleObject(ProcessInformation.hProcess, 0xFFFFFFFF) )
      ExitCode = _set_errno_nt_(StartupInfo.cb);
    else
      GetExitCodeProcess(ProcessInformation.hProcess, &ExitCode);
LABEL_13:
    CloseHandle(ProcessInformation.hProcess);
    goto LABEL_20;
  }
  Sleep(0x3E8u);
  ExitCode = 259;
  while ( 1 )
  {
    Sleep(0x64u);
    if ( !GetExitCodeProcess(ProcessInformation.hProcess, &ExitCode) )
      return _set_errno_nt_(StartupInfo.cb);
    if ( ExitCode != 259 )
      goto LABEL_13;
  }
}
// 4E7AD5: variable 'v5' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 485306: using guessed type int __cdecl _set_errno_dos_(_DWORD);
// 485357: using guessed type int __cdecl _set_errno_nt_(_DWORD);
// 4E77CE: using guessed type int __fastcall _ccmdline_(_DWORD, _DWORD);
// 51A8A7: using guessed type int dword_51A8A7;

//----- (004E7CA5) --------------------------------------------------------
const CHAR * CRT_SetEnvironmentVariableCompat(const WCHAR *a1, const WCHAR *a2, int a3)
{
  const CHAR *result; // eax
  int v5; // eax
  int v6; // edx
  int v7; // ecx
  const CHAR *v8; // ebp
  const CHAR *v9; // esi
  int v10; // eax
  int v11; // edx
  int v12; // ecx
  int v13; // ecx
  int v14; // edx
  int v15; // ecx

  if ( HIWORD(g_WindowsVersionDword) < 0x8000u )
    return (const CHAR *)SetEnvironmentVariableW(a1, a2);
  v5 = wcslen_(a3, a2);
  result = (const CHAR *)nmalloc_(2 * v5 + 1, v6);
  v8 = result;
  if ( result )
  {
    if ( a2 )
    {
      v10 = wcslen_(v7, result);
      v9 = (const CHAR *)nmalloc_(2 * v10 + 1, v11);
      if ( !v9 )
        goto LABEL_9;
    }
    else
    {
      v9 = 0;
    }
    if ( wcstombs_(v7, a1) == -1 )
    {
      nfree_(v12);
      if ( !v9 )
        return 0;
LABEL_9:
      nfree_(v7);
      return 0;
    }
    if ( v9 && wcstombs_(v12, a2) == -1 )
      goto LABEL_9;
    SetEnvironmentVariableA(v8, v9);
    nfree_(v13);
    if ( v9 )
      nfree_(v15);
    return (const CHAR *)v14;
  }
  return result;
}
// 4E7CD2: variable 'v6' is possibly undefined
// 4E7CED: variable 'v7' is possibly undefined
// 4E7CF9: variable 'v11' is possibly undefined
// 4E7D1B: variable 'v12' is possibly undefined
// 4E7D50: variable 'v13' is possibly undefined
// 4E7D5B: variable 'v15' is possibly undefined
// 4E7D60: variable 'v14' is possibly undefined
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 4D9743: using guessed type int __fastcall wcslen_(_DWORD, _DWORD);
// 4D9993: using guessed type int __fastcall wcstombs_(_DWORD, _DWORD);
// 51A8A7: using guessed type int dword_51A8A7;

//----- (004E7DDE) --------------------------------------------------------
// attributes: thunk
int CRT_InvokeIoInitHook()
{
  return g_CRT_InitHookPtr();
}
// 51A8BB: using guessed type int (*off_51A8BB)();

//----- (004E7DE5) --------------------------------------------------------
int CRT_DefaultZeroStub()
{
  return 0;
}

//----- (004E7DE8) --------------------------------------------------------
signed int  CRT_GetOsHandleFromFd(int a1, int a2)
{
  if ( a1 >= 0 && a1 <= (unsigned int)g_CRT_MaxFileDescriptor )
    return *(_DWORD *)(4 * a1 + g_CRT_OsHandleTable);
  _set_errno_(a2);
  return -1;
}
// 51A768: using guessed type int dword_51A768;
// 51AED0: using guessed type int dword_51AED0;

//----- (004E7EB8) --------------------------------------------------------
unsigned int  CRT_MbcsBackUpOverLeadByte(unsigned int a1, unsigned int a2)
{
  unsigned __int8 *v4; // eax

  if ( a1 >= a2 )
    return 0;
  v4 = (unsigned __int8 *)(a2 - 1);
  if ( g_CRT_MbcsCodePageActive && (g_Clips_DbcsLeadByteTable[*v4] & 1) != 0 )
    return a2 - 2;
  do
    --v4;
  while ( a1 <= (unsigned int)v4 && g_CRT_MbcsCodePageActive && (g_Clips_DbcsLeadByteTable[*v4] & 1) != 0 );
  return a2 - 1 - (int)(a2 - (_DWORD)v4) % 2;
}
// 54E718: using guessed type int dword_54E718;

//----- (004E7F2D) --------------------------------------------------------
int  CRT_IsExtendedMbcsLeadByte(int a1, int a2)
{
  unsigned int v2; // edx

  if ( !ismbclegal_(a2, a1) )
    return IsTable[(unsigned __int8)(v2 + 1)] & 0x80;
  return v2 >= 0x8281 && v2 <= 0x829A;
}
// 4E7F3F: variable 'v2' is possibly undefined
// 4E800B: using guessed type int __fastcall ismbclegal_(_DWORD, _DWORD);

//----- (004E7F70) --------------------------------------------------------
char * CRT_StrNCpyMbcsSafe(char *a1, const char *a2, unsigned int a3)
{
  const char *v4; // esi
  unsigned int v5; // kr04_4
  unsigned int v6; // ecx
  char *v7; // edi
  char v8; // al
  char v9; // al

  v4 = a2;
  v5 = strlen(a2) + 1;
  v6 = v5 - 1;
  if ( g_CRT_MbcsCodePageActive && (g_Clips_DbcsLeadByteTable[(unsigned __int8)a2[a3]] & 1) != 0 && a3 < v6 )
    --a3;
  if ( v5 > a3 )
  {
    qmemcpy(a1, a2, a3);
  }
  else
  {
    v7 = a1;
    do
    {
      v8 = *v4;
      *v7 = *v4;
      if ( !v8 )
        break;
      v9 = v4[1];
      v4 += 2;
      v7[1] = v9;
      v7 += 2;
    }
    while ( v9 );
    if ( v6 != a3 )
      memset_(v6, 0);
  }
  return a1;
}
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 54E718: using guessed type int dword_54E718;

// nfuncs=4362 queued=3899 decompiled=3899 lumina nreq=0 worse=0 better=0
// Remaining decompiler scars are tracked in docs/archive/COMPILATION_PROGRESS.md and are no longer fatal to parsing.
