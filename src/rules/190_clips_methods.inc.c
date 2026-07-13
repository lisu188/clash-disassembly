/* CLIPS method lookup, dispatch, and late object-runtime support.
 * Original function-marker range: 0x004C82D0..0x004CFFC0.
 * Included by clash95.c; not a standalone translation unit. */

//----- (004C82D0) --------------------------------------------------------
signed int  Method_FindByIndex(int a1, int a2)
{
  int v4; // edx
  signed int result; // eax
  _DWORD *i; // edx

  v4 = *(_DWORD *)(a1 + 32);
  result = 0;
  if ( !v4 )
    return -1;
  for ( i = *(_DWORD **)(a1 + 28); a2 != *i; i += 10 )
  {
    if ( (unsigned int)++result >= *(_DWORD *)(a1 + 32) )
      return -1;
  }
  return result;
}

//----- (004C8300) --------------------------------------------------------
signed int  Defgeneric_PreviewGenericCommand(double a1)
{
  signed int result; // eax
  int v2; // esi
  int v3; // edi
  int v4; // ebx
  int v5; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // [esp+0h] [ebp-34h] BYREF
  int v10; // [esp+8h] [ebp-2Ch]
  int v11; // [esp+18h] [ebp-1Ch]

  g_ClipsEvaluationError = 0;
  result = Lexer_ParseValueList(1, &v9, 2, a1);
  if ( result )
  {
    v2 = Defgeneric_LookupWithImports(*(_BYTE **)(v10 + 16));
    if ( v2 )
    {
      v3 = Rules_GetReentryGuardFlag();
      Rules_SetReentryGuardFlag(1);
      v11 = g_ClipsCurrentGeneric;
      g_ClipsCurrentGeneric = v2;
      ++g_ClipsCurrentEvaluationDepth;
      v4 = Rules_GetConstructNameString(v2);
      v5 = AST_CountListNodes(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10));
      ProcParam_PushEvaluatedArgumentFrame(
        *(_DWORD **)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10),
        v5,
        (int)aGenericFunct_1,
        v4,
        a1,
        (int (*)(void))Method_PrintCallErrorBanner);
      if ( !g_ClipsEvaluationError )
      {
        ++*(_DWORD *)(v2 + 20);
        Defgeneric_PrintApplicableMethods(v2, a1);
        --*(_DWORD *)(v2 + 20);
      }
      ProcParam_PopFrame();
      g_ClipsCurrentGeneric = v11;
      --g_ClipsCurrentEvaluationDepth;
      return Rules_SetReentryGuardFlag(v3);
    }
    else
    {
      Rules_PrintErrorID((int)aGenrcfun, 3, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnableToFindGe, v6);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(v10 + 16), v7);
      return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInFunctionPrev, v8);
    }
  }
  return result;
}
// 4C8400: variable 'v6' is possibly undefined
// 4C8411: variable 'v7' is possibly undefined
// 4C8420: variable 'v8' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A960: using guessed type int dword_51A960;
// 51A964: using guessed type int dword_51A964;
// 51A96C: using guessed type int dword_51A96C;
// 51B3D4: using guessed type int dword_51B3D4;

//----- (004C8470) --------------------------------------------------------
_DWORD * Defgeneric_AppendMethodSignatureText(char *a1, int a2, int a3, int a4)
{
  _DWORD *result; // eax
  int v6; // ebx
  _DWORD *v7; // edx
  int v8; // eax
  const char *v9; // edi
  unsigned int v10; // ebp
  unsigned int v11; // edx
  int v12; // ecx
  char v13[16]; // [esp+0h] [ebp-38h] BYREF
  int v14; // [esp+10h] [ebp-28h]
  _DWORD *v15; // [esp+14h] [ebp-24h]
  _DWORD *v16; // [esp+18h] [ebp-20h]
  int v17; // [esp+1Ch] [ebp-1Ch]
  int v18; // [esp+20h] [ebp-18h]
  _DWORD *v19; // [esp+24h] [ebp-14h]

  v17 = a2;
  v16 = (_DWORD *)a4;
  *a1 = 0;
  if ( (*(_BYTE *)(a4 + 24) & 1) != 0 )
    strncpy_(a3, aSys);
  sprintf_(v13, "%-2d ", *v16);
  ((void (*)(void))strncat_)();
  result = v16;
  v6 = v16[2];
  v15 = 0;
  if ( v6 > 0 )
  {
    v14 = 0;
    do
    {
      v7 = (_DWORD *)(v16[7] + v14);
      v8 = v16[2] - 1;
      v19 = v7;
      if ( (_DWORD *)v8 == v15 && v16[4] == -1 )
      {
        if ( !v7[2] && !v19[1] )
        {
          strlen(a1);
          return (_DWORD *)((int (*)(void))strncat_)();
        }
        v9 = a1;
      }
      else
      {
        v9 = a1;
      }
      strlen(v9);
      ((void (*)(void))strncat_)();
      v10 = 0;
      if ( v19[2] )
      {
        v18 = 0;
        do
        {
          strlen(a1);
          Rules_GetConstructNameString(*(_DWORD *)(v18 + *v19));
          ((void (*)(void))strncat_)();
          if ( v10 < v19[2] - 1 )
          {
            strlen(a1);
            ((void (*)(void))strncat_)();
          }
          ++v10;
          v11 = v19[2];
          v18 += 4;
        }
        while ( v10 < v11 );
      }
      if ( v19[1] )
      {
        if ( v19[2] )
        {
          strlen(a1);
          ((void (*)(void))strncat_)();
        }
        strlen(a1);
        ((void (*)(void))strncat_)();
      }
      strlen(a1);
      ((void (*)(void))strncat_)();
      result = (_DWORD *)(v16[2] - 1);
      if ( result != v15 )
      {
        strlen(a1);
        result = (_DWORD *)((int (*)(void))strncat_)();
      }
      v12 = v16[2];
      v14 += 12;
      v15 = (_DWORD *)((char *)v15 + 1);
    }
    while ( (int)v15 < v12 );
  }
  return result;
}
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 48521A: using guessed type int __fastcall strncpy_(_DWORD, _DWORD);

//----- (004C86C0) --------------------------------------------------------
int  Defgeneric_CheckGenericExists(int a1, _BYTE *a2)
{
  int result; // eax
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx

  result = Defgeneric_LookupWithImports(a2);
  if ( !result )
  {
    Rules_PrintErrorID((int)aGenrcfun, 3, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnableToFindGe, v4);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], v5, v5);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInFunction_2, v6);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], a1, v7);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__23, v8);
    Lexer_ErrorRecover(1);
    return 0;
  }
  return result;
}
// 4C86F6: variable 'v4' is possibly undefined
// 4C8702: variable 'v5' is possibly undefined
// 4C8711: variable 'v6' is possibly undefined
// 4C871D: variable 'v7' is possibly undefined
// 4C872C: variable 'v8' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004C8750) --------------------------------------------------------
signed int  Defgeneric_CheckMethodExists(int a1, int a2, int a3)
{
  signed int result; // eax
  int v6; // ecx
  int v7; // eax
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx

  result = Method_FindByIndex(a2, a3);
  if ( result == -1 )
  {
    Rules_PrintErrorID((int)aGenrcfun, 2, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnableToFindMe, v6);
    v7 = Rules_GetConstructNameString(a2);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], v7, v8);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_50B158, v9);
    Rules_PrintLongInteger(v10, v10);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInFunction_2, v11);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], a1, v12);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__23, v13);
    Lexer_ErrorRecover(1);
    return -1;
  }
  return result;
}
// 4C878C: variable 'v6' is possibly undefined
// 4C87A2: variable 'v8' is possibly undefined
// 4C87B1: variable 'v9' is possibly undefined
// 4C87BD: variable 'v10' is possibly undefined
// 4C87CC: variable 'v11' is possibly undefined
// 4C87D8: variable 'v12' is possibly undefined
// 4C87E7: variable 'v13' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004C8850) --------------------------------------------------------
unsigned int  Defgeneric_PrintApplicableMethods(unsigned int result, double a2)
{
  int v2; // ecx
  int v3; // ebp
  unsigned int v4; // edi
  int v5; // esi
  int v6; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // eax
  int v14; // ecx
  char v15[280]; // [esp+0h] [ebp-118h] BYREF

  v2 = result;
  v3 = 0;
  v4 = 0;
  if ( *(_DWORD *)(result + 32) )
  {
    v5 = 0;
    do
    {
      ++*(_DWORD *)(v5 + *(_DWORD *)(v2 + 28) + 4);
      if ( Method_RestrictionsSatisfiedByArgs(v5 + *(_DWORD *)(v2 + 28), a2) )
      {
        v6 = Rules_GetConstructNameString(v2);
        Output_Write((int)g_IO_LogicalName_WDisplay, v6, v7);
        Output_Write((int)g_IO_LogicalName_WDisplay, (int)asc_50B158, v8);
        Defgeneric_AppendMethodSignatureText(v15, 255, v9, v5 + *(_DWORD *)(v9 + 28));
        Output_Write((int)g_IO_LogicalName_WDisplay, (int)v15, v10);
        v3 = 1;
        Output_Write((int)g_IO_LogicalName_WDisplay, (int)asc_50B160, v11);
      }
      --*(_DWORD *)(v5 + *(_DWORD *)(v2 + 28) + 4);
      ++v4;
      result = *(_DWORD *)(v2 + 32);
      v5 += 40;
    }
    while ( v4 < result );
  }
  if ( !v3 )
  {
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aNoApplicableMe, v2);
    v13 = Rules_GetConstructNameString(v12);
    Output_Write((int)g_IO_LogicalName_WDisplay, v13, (int)g_IO_LogicalName_WDisplay);
    return Output_Write((int)g_IO_LogicalName_WDisplay, (int)a__23, v14);
  }
  return result;
}
// 4C886B: variable 'v2' is possibly undefined
// 4C88B4: variable 'v7' is possibly undefined
// 4C88C3: variable 'v8' is possibly undefined
// 4C88D4: variable 'v9' is possibly undefined
// 4C88E0: variable 'v10' is possibly undefined
// 4C88F4: variable 'v11' is possibly undefined
// 4C890C: variable 'v12' is possibly undefined
// 4C892A: variable 'v14' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (004C8940) --------------------------------------------------------
int Defgeneric_CompilerSetup()
{
  int result; // eax

  result = Rules_AddCodeGeneratorItem((int)aGenerics, 0, 0, (int)Defgeneric_BeforeCode, (int)Defgeneric_DefgenericsToCode, 5);
  g_DefgenericCodeGenItem = result;
  return result;
}
// 54E8CC: using guessed type int dword_54E8CC;

//----- (004C8970) --------------------------------------------------------
int  Defgeneric_PrintModuleIndexOrNull(int a1, int a2, int a3)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( a2 )
    return Output_WriteFormatted(
             a3,
             *(_DWORD *)(*(_DWORD *)(g_DefgenericCodeGenItem + 20) + 4),
             a1,
             (int)aSD_DD,
             *(_DWORD *)(*(_DWORD *)(g_DefgenericCodeGenItem + 20) + 4));
  else
    return Output_WriteFormatted(a3, 0, a1, (int)aNull_4, v4);
}
// 4C8980: variable 'v4' is possibly undefined
// 54E8CC: using guessed type int dword_54E8CC;

//----- (004C89C0) --------------------------------------------------------
int  Defgeneric_PrintModuleReference(int a1, int a2)
{
  return Output_WriteFormatted(a2, **(_DWORD **)(g_DefgenericCodeGenItem + 20), a1, (int)aMihsSD_DD, **(_DWORD **)(g_DefgenericCodeGenItem + 20));
}
// 54E8CC: using guessed type int dword_54E8CC;

//----- (004C8A00) --------------------------------------------------------
signed int Defgeneric_BeforeCode()
{
  return Rules_RegisterModuleItemIdAssigner();
}
// 54E6A4: using guessed type int dword_54E6A4;

//----- (004C8A10) --------------------------------------------------------
int  Defgeneric_DefgenericsToCode(const char *a1, const char *a2, int a3, int a4, int a5)
{
  int v5; // eax
  int v6; // edx
  const char **v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // edx
  int v13; // eax
  int v14; // ecx
  _DWORD *v15; // ebp
  int v16; // edx
  unsigned int v17; // esi
  int v18; // edi
  unsigned int v19; // edi
  unsigned int v20; // esi
  int v21; // ebp
  int v23; // [esp+0h] [ebp-D8h]
  int v24; // [esp+4h] [ebp-D4h]
  const char **v25; // [esp+8h] [ebp-D0h]
  const char *v26[3]; // [esp+Ch] [ebp-CCh] BYREF
  const char *v27[3]; // [esp+18h] [ebp-C0h] BYREF
  const char *v28[3]; // [esp+24h] [ebp-B4h] BYREF
  const char *v29[3]; // [esp+30h] [ebp-A8h] BYREF
  const char *v30[3]; // [esp+3Ch] [ebp-9Ch] BYREF
  int v31; // [esp+48h] [ebp-90h] BYREF
  int v32; // [esp+4Ch] [ebp-8Ch] BYREF
  int v33; // [esp+50h] [ebp-88h] BYREF
  int v34; // [esp+54h] [ebp-84h] BYREF
  DWORD v35; // [esp+58h] [ebp-80h] BYREF
  int v36; // [esp+5Ch] [ebp-7Ch] BYREF
  int v37; // [esp+60h] [ebp-78h] BYREF
  int v38; // [esp+64h] [ebp-74h] BYREF
  int v39; // [esp+68h] [ebp-70h] BYREF
  int v40; // [esp+6Ch] [ebp-6Ch] BYREF
  int v41; // [esp+70h] [ebp-68h] BYREF
  int v42; // [esp+74h] [ebp-64h] BYREF
  int v43; // [esp+78h] [ebp-60h] BYREF
  int v44; // [esp+7Ch] [ebp-5Ch] BYREF
  int v45; // [esp+80h] [ebp-58h] BYREF
  int v46; // [esp+84h] [ebp-54h] BYREF
  int v47; // [esp+88h] [ebp-50h]
  int v48; // [esp+8Ch] [ebp-4Ch]
  int v49; // [esp+90h] [ebp-48h]
  int v50; // [esp+94h] [ebp-44h]
  int v51; // [esp+98h] [ebp-40h] BYREF
  int v52; // [esp+9Ch] [ebp-3Ch]
  int Enum; // [esp+A0h] [ebp-38h]
  int v54; // [esp+A4h] [ebp-34h]
  int i; // [esp+A8h] [ebp-30h]
  int v56; // [esp+ACh] [ebp-2Ch]
  unsigned int v57; // [esp+B0h] [ebp-28h]
  const char *v58; // [esp+B4h] [ebp-24h]
  const char *v59; // [esp+B8h] [ebp-20h]
  int v60; // [esp+BCh] [ebp-1Ch]
  int v61; // [esp+C0h] [ebp-18h]
  int v62; // [esp+C4h] [ebp-14h]
  unsigned int v63; // [esp+C8h] [ebp-10h]

  v59 = a1;
  v58 = a2;
  v60 = a4;
  v52 = a3;
  v5 = 0;
  v51 = 1;
  v54 = 0;
  v6 = 0;
  do
  {
    ++v5;
    v6 += 12;
    v30[v5 + 2] = 0;
    *(int *)((char *)&v40 + v5 * 4) = 1;
    *(int *)((char *)&v45 + v5 * 4) = 0;
    *(DWORD *)((char *)&v35 + v5 * 4) = 0;
    *(int *)((char *)&v23 + v6) = 0;
  }
  while ( v5 != 5 );
  Output_WriteFormatted(0, v6, v60, (int)aIncludeGenrcfu, (char)v26[0]);
  Enum = Module_NextEnum(0);
  if ( Enum )
  {
    while ( 1 )
    {
      Module_SetCurrent(Enum);
      v25 = v26;
      v7 = *(const char ***)(g_DefgenericCodeGenItem + 20);
      v24 = v36;
      v8 = Rules_ConstructCodeFileOpen(v46, v59, v52, v58, &v51, v41, v60, (char)aDefgeneric_mod, *v7, v36, v26);
      v46 = v8;
      if ( !v8 )
        break;
      Defgeneric_ModuleToCode(v8, Enum, a5);
      v46 = Rules_ConstructCodeFileClose(v46, &v31, a5, &v41, &v36, (int)v26);
      for ( i = Defgeneric_GetNextInModule(0); i; i = Defgeneric_GetNextInModule(i) )
      {
        v25 = v27;
        v9 = Rules_ConstructCodeFileOpen(
               v47,
               v59,
               v52,
               v58,
               &v51,
               v42,
               v60,
               (char)aDefgeneric_5,
               *(const char **)(*(_DWORD *)(g_DefgenericCodeGenItem + 20) + 4),
               v37,
               v27);
        v47 = v9;
        if ( !v9 )
          goto LABEL_34;
        Defgeneric_SingleToCode(v9, v52, i, a5, v54, v43, v33);
        ++v32;
        v47 = Rules_ConstructCodeFileClose(v47, &v32, a5, &v42, &v37, (int)v27);
        if ( *(_DWORD *)(i + 32) )
        {
          v25 = v28;
          v10 = *(_DWORD *)(g_DefgenericCodeGenItem + 20);
          v24 = v38;
          v48 = Rules_ConstructCodeFileOpen(v48, v59, v52, v58, &v51, v43, v60, (char)aDefmethod_2, *(const char **)(v10 + 8), v38, v28);
          if ( !v48 )
            goto LABEL_34;
          v12 = *(_DWORD *)(i + 32);
          v57 = 0;
          if ( v12 )
          {
            v56 = 0;
            do
            {
              v61 = *(_DWORD *)(i + 28) + v56;
              if ( v57 )
                Output_WriteFormatted(v11, v48, v48, (int)asc_50B1FC, (char)v26[0]);
              Defgeneric_MethodToCode(v48, v52, v44, v61, v34);
              if ( *(int *)(v61 + 8) > 0 )
              {
                v25 = v29;
                v13 = *(_DWORD *)(g_DefgenericCodeGenItem + 20);
                v24 = v39;
                v49 = Rules_ConstructCodeFileOpen(
                        v49,
                        v59,
                        v52,
                        v58,
                        &v51,
                        v44,
                        v60,
                        (char)aRestriction,
                        *(const char **)(v13 + 12),
                        v39,
                        v29);
                if ( !v49 )
                  goto LABEL_34;
                v14 = *(_DWORD *)(v61 + 8);
                v63 = 0;
                if ( v14 )
                {
                  v62 = 0;
                  do
                  {
                    v15 = (_DWORD *)(v62 + *(_DWORD *)(v61 + 28));
                    if ( v63 )
                      Output_WriteFormatted(v63, v62, v49, (int)asc_50B1FC, (char)v26[0]);
                    Defgeneric_RestrictionToCode(v49, v52, v45, (int)v15, (DWORD)v15, v35);
                    if ( v15[2] )
                    {
                      v50 = Rules_ConstructCodeFileOpen(
                              v50,
                              v59,
                              v52,
                              v58,
                              &v51,
                              v45,
                              v60,
                              (char)aVoid_1,
                              *(const char **)(*(_DWORD *)(g_DefgenericCodeGenItem + 20) + 16),
                              v40,
                              v30);
                      if ( !v50 )
                        goto LABEL_34;
                      v17 = 0;
                      if ( v15[2] )
                      {
                        v18 = 0;
                        do
                        {
                          if ( v17 )
                            Output_WriteFormatted(v50, v16, v50, (int)asc_50B1FC, (char)v26[0]);
                          ++v17;
                          Defgeneric_RestrictionTypeToCode(v50, a5, *(_DWORD *)(v18 + *v15));
                          v18 += 4;
                        }
                        while ( v17 < v15[2] );
                      }
                      v35 += v15[2];
                      v50 = Rules_ConstructCodeFileClose(v50, (int *)&v35, a5, &v45, &v40, (int)v30);
                    }
                    v19 = *(_DWORD *)(v61 + 8);
                    v62 += 12;
                    ++v63;
                  }
                  while ( v63 < v19 );
                }
                v34 += *(_DWORD *)(v61 + 8);
                v49 = Rules_ConstructCodeFileClose(v49, &v34, a5, &v44, &v39, (int)v29);
              }
              v11 = v56 + 40;
              v20 = *(_DWORD *)(i + 32);
              v56 += 40;
              ++v57;
            }
            while ( v57 < v20 );
          }
          v33 += *(_DWORD *)(i + 32);
          v48 = Rules_ConstructCodeFileClose(v48, &v33, a5, &v43, &v38, (int)v28);
        }
      }
      v21 = v54;
      Enum = Module_NextEnum(Enum);
      v54 = v21 + 1;
      ++v31;
      if ( !Enum )
        goto LABEL_33;
    }
LABEL_34:
    Defgeneric_CloseCodeFiles(&v46, &v36, a5, (int)v26);
    return 0;
  }
  else
  {
LABEL_33:
    Defgeneric_CloseCodeFiles(&v46, &v36, a5, (int)v26);
    return 1;
  }
}
// 4C8CDF: variable 'v11' is possibly undefined
// 4C8E7A: variable 'v16' is possibly undefined
// 54E8CC: using guessed type int dword_54E8CC;

//----- (004C9070) --------------------------------------------------------
int  Defgeneric_CloseCodeFiles(int *a1, _DWORD *a2, int a3, int a4)
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
  v11 = a2 + 5;
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

//----- (004C90D0) --------------------------------------------------------
int  Defgeneric_ModuleToCode(int a1, int a2, int a3)
{
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  char v9; // [esp+0h] [ebp-Ch]
  char v10; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(a3, a2, a1, (int)asc_50B214, v9);
  Rules_WriteConstructModuleItemHeaderToCode(a1, v4, v5, g_DefgenericModuleItemIndex, *(_DWORD *)(*(_DWORD *)(g_DefgenericCodeGenItem + 20) + 4));
  return Output_WriteFormatted(v7, v6, a1, (int)asc_50B218, v10);
}
// 4C90DB: variable 'v9' is possibly undefined
// 4C90F8: variable 'v4' is possibly undefined
// 4C90F8: variable 'v5' is possibly undefined
// 4C9103: variable 'v7' is possibly undefined
// 4C9103: variable 'v6' is possibly undefined
// 4C9103: variable 'v10' is possibly undefined
// 54E6A4: using guessed type int dword_54E6A4;
// 54E8CC: using guessed type int dword_54E8CC;

//----- (004C9110) --------------------------------------------------------
int  Defgeneric_SingleToCode(int a1, int a2, int a3, signed int a4, int a5, int a6, int a7)
{
  int v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // edx
  int v13; // edx
  int v14; // ecx
  char v16; // [esp+0h] [ebp-Ch]
  char v17; // [esp+0h] [ebp-Ch]
  char v18; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(a3, a2, a1, (int)asc_50B214, v16);
  Rules_WriteConstructHeaderToCode(a1, a3, a4, a5, **(_DWORD **)(g_DefgenericCodeGenItem + 20), *(_DWORD *)(*(_DWORD *)(g_DefgenericCodeGenItem + 20) + 4));
  Output_WriteFormatted(v10, v9, a1, (int)a00_15, v17);
  v12 = *(_DWORD *)(a3 + 28);
  if ( v12 )
    Output_WriteFormatted(a7, v12, a1, (int)aSD_DD, *(_DWORD *)(*(_DWORD *)(g_DefgenericCodeGenItem + 20) + 8));
  else
    Output_WriteFormatted(v11, 0, a1, (int)aNull_4, v18);
  return Output_WriteFormatted(v14, v13, a1, (int)aU0, *(_DWORD *)(a3 + 32));
}
// 4C911F: variable 'v16' is possibly undefined
// 4C914E: variable 'v10' is possibly undefined
// 4C914E: variable 'v9' is possibly undefined
// 4C914E: variable 'v17' is possibly undefined
// 4C9163: variable 'v11' is possibly undefined
// 4C9163: variable 'v18' is possibly undefined
// 4C9175: variable 'v14' is possibly undefined
// 4C9175: variable 'v13' is possibly undefined
// 54E8CC: using guessed type int dword_54E8CC;

//----- (004C91B0) --------------------------------------------------------
int  Defgeneric_MethodToCode(int a1, int a2, int a3, int a4, int a5)
{
  DWORD v6; // ebp
  int v7; // edx
  int v8; // ecx
  int v9; // ecx
  int v10; // edx
  int v11; // ecx
  int v13; // edx
  char v14; // [esp+0h] [ebp-Ch]

  v6 = *(_DWORD *)a4;
  Output_WriteFormatted(a3, a2, a1, (int)aU0DDDDU0, *(_DWORD *)a4);
  if ( *(_DWORD *)(a4 + 28) )
  {
    v13 = *(_DWORD *)(g_DefgenericCodeGenItem + 20);
    v6 = *(_DWORD *)(v13 + 12);
    Output_WriteFormatted(v8, v13, a1, (int)aSD_DD_7, v6);
  }
  else
  {
    Output_WriteFormatted(v8, v7, a1, (int)aNull_25, v14);
  }
  Rules_ExpressionToCode(a1, *(__int16 **)(a4 + 32), v9, v6);
  return Output_WriteFormatted(v11, v10, a1, (int)aNull_26, v14);
}
// 4C91EA: variable 'v8' is possibly undefined
// 4C91EA: variable 'v7' is possibly undefined
// 4C91EA: variable 'v14' is possibly undefined
// 4C91F7: variable 'v9' is possibly undefined
// 4C9202: variable 'v11' is possibly undefined
// 4C9202: variable 'v10' is possibly undefined
// 54E8CC: using guessed type int dword_54E8CC;

//----- (004C9240) --------------------------------------------------------
int  Defgeneric_RestrictionToCode(int a1, int a2, int a3, int a4, DWORD a5, DWORD a6)
{
  int v7; // edx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  char v12; // [esp+0h] [ebp-Ch]
  char v13; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(a3, a2, a1, (int)asc_50B214, v12);
  if ( *(_DWORD *)a4 )
  {
    a5 = a6;
    Output_WriteFormatted(v8, *(_DWORD *)(g_DefgenericCodeGenItem + 20), a1, (int)aSD_DD_7, *(_DWORD *)(*(_DWORD *)(g_DefgenericCodeGenItem + 20) + 16));
  }
  else
  {
    Output_WriteFormatted(v8, v7, a1, (int)aNull_25, v13);
  }
  Rules_ExpressionToCode(a1, *(__int16 **)(a4 + 4), v9, a5);
  return Output_WriteFormatted(v10, *(_DWORD *)(a4 + 8), a1, (int)aU, *(_DWORD *)(a4 + 8));
}
// 4C924B: variable 'v12' is possibly undefined
// 4C925F: variable 'v8' is possibly undefined
// 4C925F: variable 'v7' is possibly undefined
// 4C925F: variable 'v13' is possibly undefined
// 4C926C: variable 'v9' is possibly undefined
// 4C927B: variable 'v10' is possibly undefined
// 54E8CC: using guessed type int dword_54E8CC;

//----- (004C92B0) --------------------------------------------------------
int  Defgeneric_RestrictionTypeToCode(int a1, int a2, int a3)
{
  int v4; // edx
  int v5; // ecx
  char v7; // [esp+0h] [ebp-8h]

  Output_WriteFormatted(a2, a3, a1, (int)aVs_1, v7);
  return ObjectsCompiler_WriteDefclassPointerRef(a1, v4, v5);
}
// 4C92BE: variable 'v7' is possibly undefined
// 4C92CA: variable 'v4' is possibly undefined
// 4C92CA: variable 'v5' is possibly undefined

//----- (004C92E0) --------------------------------------------------------
signed int  Defgeneric_ParseDefgeneric(int a1)
{
  _DWORD *v3; // edx
  int v4; // ecx
  signed int v5; // ecx
  int v6; // ecx
  char *v7; // eax
  signed int v8; // ecx

  Rules_SetPPBufferStatus(1);
  Rules_FlushPPBuffer();
  IO_OutWriteToken(aDefgeneric_3);
  Rules_SetIndentDepth(3);
  if ( Rules_IsBloaded() == 1 )
  {
    Rules_ReportCannotLoadWithBload();
    return 1;
  }
  if ( !Rules_GetConstructNameAndComment(a1, (int)&g_ClipsMethodParserToken, (int (*)(void))Defgeneric_ParseConstruct, aDefgeneric_1, 0, asc_50B28C, 1, 1, 1)
    || !Defgeneric_ParseDeclaration() )
  {
    return 1;
  }
  if ( g_ClipsMethodParserToken == 101 )
  {
    IO_OutWriteToken(asc_50B2C4);
    Defgeneric_AddConstruct(v4, v3);
    if ( Mem_GetAllocFlag() )
    {
      Rules_ReplaceConstructPPForm(v5, 0);
    }
    else
    {
      v7 = Rules_CopyPPBuffer();
      Rules_ReplaceConstructPPForm(v8, (int)v7);
    }
    return 0;
  }
  else
  {
    Rules_PrintErrorID((int)aGenrcpsr, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedToComp, v6);
    return 1;
  }
}
// 4C937B: variable 'v4' is possibly undefined
// 4C937B: variable 'v3' is possibly undefined
// 4C938F: variable 'v5' is possibly undefined
// 4C93B9: variable 'v6' is possibly undefined
// 4C93D4: variable 'v8' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 54E8D0: using guessed type int dword_54E8D0;

//----- (004C93F0) --------------------------------------------------------
signed int  Defgeneric_ParseDefmethod(int a1)
{
  int v1; // edx
  int v3; // ecx
  int v4; // eax
  _DWORD *v5; // edi
  signed int *v6; // edx
  int v7; // edx
  int v8; // ecx
  int i; // esi
  int v10; // eax
  int v11; // esi
  int v12; // ecx
  char *v13; // edx
  int *v14; // ecx
  int v15; // edx
  int v16; // ecx
  __int16 *v17; // edx
  char *v18; // eax
  int v19; // ecx
  int v20; // esi
  int *v21; // ecx
  int v22; // ecx
  char *v23; // edx
  int v24; // ecx
  int v25; // ecx
  signed int v26; // eax
  int v27; // ecx
  int v28; // [esp+0h] [ebp-24h] BYREF
  int v29; // [esp+4h] [ebp-20h] BYREF
  unsigned int v30; // [esp+8h] [ebp-1Ch] BYREF
  int v31; // [esp+Ch] [ebp-18h]
  int v32; // [esp+10h] [ebp-14h] BYREF
  unsigned int v33; // [esp+14h] [ebp-10h] BYREF
  int v34; // [esp+18h] [ebp-Ch]
  int v35; // [esp+1Ch] [ebp-8h]
  int v36; // [esp+20h] [ebp-4h]

  v36 = a1;
  Rules_SetPPBufferStatus(1);
  Rules_FlushPPBuffer();
  Rules_SetIndentDepth(3);
  v35 = v1;
  IO_OutWriteToken(aDefmethod_0);
  if ( Rules_IsBloaded() == 1 )
  {
    Rules_ReportCannotLoadWithBload();
    return 1;
  }
  if ( !Method_ParseIndexModifier(v36, &v33) || !Defgeneric_ParseDeclaration() )
    return 1;
  v4 = Defgeneric_AddConstruct(v3, &v29);
  v5 = (_DWORD *)v4;
  if ( v29 )
    Defgeneric_CreateDefaultPPForm(v4);
  Rules_IncrementIndentDepth(1);
  v34 = Method_ParseParameterList(v36, v6, &v32);
  Rules_DecrementIndentDepth(1);
  if ( v7 == -1 )
  {
LABEL_9:
    if ( v29 )
    {
      Rules_UnlinkListNode((int)v5);
      Defgeneric_RemoveDefgeneric((int)v5);
      return 1;
    }
    return 1;
  }
  AST_Append(v8, v7);
  for ( i = v31; i; i = *(_DWORD *)(i + 10) )
  {
    Method_ReplaceCurrentArgumentRefs(*(int ***)(*(_DWORD *)(i + 6) + 4));
    if ( Parser_ReplaceProcVars((int)aMethod, *(_DWORD *)(*(_DWORD *)(i + 6) + 4), v32, v31, 0, 0) )
      goto LABEL_19;
  }
  v10 = Method_FindInsertionIndex((int)v5, v31, v32, v34, (unsigned int *)&v28);
  v11 = v10;
  if ( v10 )
  {
    if ( (*(_BYTE *)(v10 + 24) & 1) != 0 )
    {
      Rules_PrintErrorID((int)aGenrcpsr, 17, 0);
      v13 = aCannotReplaceT;
LABEL_17:
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)v13, v12);
      v15 = *v14;
LABEL_18:
      Rules_PrintLongInteger((int)v14, v15);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__12, v16);
LABEL_19:
      Method_FreeRestrictionChain(v31);
      goto LABEL_9;
    }
    if ( v33 && v33 != *(_DWORD *)v10 )
    {
      Rules_PrintErrorID((int)aGenrcpsr, 2, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNewMethod, v24);
      Rules_PrintLongInteger(v25, v33);
      v13 = aWouldBeIndisti;
      goto LABEL_17;
    }
  }
  else if ( v33 )
  {
    v26 = Method_FindByIndex((int)v5, v33);
    if ( v26 == -1 )
    {
      v35 = 1;
    }
    else if ( (*(_BYTE *)(v5[7] + 40 * v26 + 24) & 1) != 0 )
    {
      Rules_PrintErrorID((int)aGenrcpsr, 17, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotReplaceT, v27);
      v15 = v33;
      goto LABEL_18;
    }
  }
  else
  {
    v35 = 1;
  }
  g_ClipsParseReturnContext = 1;
  if ( !Parser_ParseProcActions((int)aMethod, v36, v31, v32, 0, 0, (int *)&v30, 0) )
    goto LABEL_19;
  IO_OutNewline();
  IO_OutNewline();
  IO_OutWriteToken((char *)g_CLIPS_GenericParseTokenPrintStr);
  IO_OutWriteToken(asc_50B2C4);
  if ( Mem_GetAllocFlag() )
    v18 = 0;
  else
    v18 = Rules_CopyPPBuffer();
  Defgeneric_AddMethod(v5, v11, v33, v28, v31, v34, v30, v32, v17, (unsigned int)v18, 0);
  Method_FreeRestrictionChain(v31);
  if ( Rules_GetLoadInProgress() && Rules_GetWatchCompilations() )
  {
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aMethod_0, v19);
    v20 = v35;
    Rules_PrintLongInteger((int)v21, *v21);
    if ( v20 )
      v23 = aDefined_;
    else
      v23 = aRedefined_;
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)v23, v22);
  }
  return 0;
}
// 4C941E: variable 'v1' is possibly undefined
// 4C946C: variable 'v3' is possibly undefined
// 4C9492: variable 'v6' is possibly undefined
// 4C94A9: variable 'v7' is possibly undefined
// 4C94CD: variable 'v8' is possibly undefined
// 4C954A: variable 'v12' is possibly undefined
// 4C9554: variable 'v14' is possibly undefined
// 4C9565: variable 'v16' is possibly undefined
// 4C9606: variable 'v17' is possibly undefined
// 4C9631: variable 'v19' is possibly undefined
// 4C9640: variable 'v21' is possibly undefined
// 4C9657: variable 'v22' is possibly undefined
// 4C9680: variable 'v24' is possibly undefined
// 4C968D: variable 'v25' is possibly undefined
// 4C96FB: variable 'v27' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A61C: using guessed type char *off_51A61C[3];
// 54E87C: using guessed type int dword_54E87C;
// 54E8D8: using guessed type int dword_54E8D8;

//----- (004C9730) --------------------------------------------------------
unsigned int * Defgeneric_AddMethod(
        _DWORD *a1,
        int a2,
        unsigned int a3,
        int a4,
        int a5,
        int a6,
        unsigned int a7,
        int a8,
        __int16 *a9,
        unsigned int a10,
        int a11)
{
  signed int v11; // eax
  int v12; // ebp
  int v13; // eax
  _DWORD *v14; // eax
  int v15; // edx
  int v16; // ebp
  int v17; // ebx
  _DWORD *v18; // edx
  int v19; // eax
  _DWORD *v20; // edi
  int v21; // ecx
  const void **v22; // edx
  int v23; // ecx
  int v24; // ecx
  unsigned int v25; // edx
  int v27; // ebp
  int v28; // edx
  int v29; // ebx
  int v30; // ebp
  int v31; // ebx
  int v32; // edx
  int v33; // edx
  int v34; // edx
  int v36; // [esp+4h] [ebp-24h]
  unsigned int *v37; // [esp+14h] [ebp-14h]

  v37 = (unsigned int *)a2;
  v36 = a4;
  g_Defgeneric_SavedBusyCount = a1[5];
  if ( a2 )
  {
    AST_DeinstallNodeChain(*(__int16 **)(a2 + 32));
    AST_FreePackedNodeChain(*(_DWORD *)(v33 + 32));
    if ( *(_DWORD *)(v34 + 36) )
      Mem_SmallBlockFree((_DWORD *)v37[9], strlen(*(const char **)(v34 + 36)) + 1);
  }
  else if ( a3 && (v11 = Method_FindByIndex((int)a1, a3), v12 = v11, v11 != -1) )
  {
    Defgeneric_DeleteMethodInfo((int)a1, 40 * v11 + a1[7]);
    if ( v12 >= a4 )
    {
      v30 = v12 - 1;
      if ( v30 >= a4 )
      {
        v31 = 40 * v30 + 40;
        v32 = 40 * v30;
        do
        {
          --v30;
          qmemcpy((void *)(a1[7] + v31), (const void *)(a1[7] + v32), 0x28u);
          v32 -= 40;
          v31 -= 40;
        }
        while ( v32 >= 40 * v36 );
      }
    }
    else
    {
      v27 = v12 + 1;
      v36 = a4 - 1;
      if ( v27 <= a4 - 1 )
      {
        v28 = 40 * v27 - 40;
        v29 = 40 * v27;
        do
        {
          ++v27;
          qmemcpy((void *)(v28 + a1[7]), (const void *)(a1[7] + v29), 0x28u);
          v28 += 40;
          v29 += 40;
        }
        while ( v28 <= 40 * v36 - 40 );
      }
    }
    v37 = (unsigned int *)(40 * v36 + a1[7]);
    *v37 = a3;
  }
  else
  {
    v37 = Defgeneric_InsertMethodSlot(a1, a4, a3);
  }
  *((_BYTE *)v37 + 24) &= ~1u;
  v37[8] = (unsigned int)a9;
  AST_InstallNodeChain(a9);
  v37[9] = a10;
  if ( v36 != -1 )
  {
    v37[5] = a7;
    v37[2] = a6;
    if ( a8 )
    {
      v37[4] = -1;
      v13 = a6 - 1;
    }
    else
    {
      v13 = a6;
      v37[4] = a6;
    }
    v37[3] = v13;
    if ( a6 )
    {
      v14 = Mem_SmallBlockAlloc(12 * a6);
      *(_DWORD *)(v15 + 28) = v14;
    }
    else
    {
      v37[7] = 0;
    }
    if ( a6 > 0 )
    {
      v16 = 0;
      do
      {
        v17 = v16 + v37[7];
        *(_DWORD *)(v17 + 4) = AST_PackNodeChain(*(_DWORD **)(*(_DWORD *)(a5 + 6) + 4));
        v19 = v18[2];
        *(_DWORD *)(v17 + 8) = v19;
        if ( a11 )
        {
          if ( *v18 )
          {
            v20 = Mem_SmallBlockAlloc(4 * v19);
            v21 = *(_DWORD *)(v17 + 8);
            *(_DWORD *)v17 = v20;
            qmemcpy(v20, *v22, 4 * v21);
          }
          else
          {
            *(_DWORD *)v17 = 0;
          }
        }
        else
        {
          *(_DWORD *)v17 = *v18;
          v18[2] = 0;
          *v18 = 0;
        }
        AST_InstallNodeChain(*(__int16 **)(v17 + 4));
        if ( *(_DWORD *)(v17 + 8) )
        {
          v23 = 0;
          do
          {
            Class_AddBusyReference(*(_DWORD *)(v23 + *(_DWORD *)v17));
            v23 = v24 + 4;
          }
          while ( v25 < *(_DWORD *)(v17 + 8) );
        }
        v16 += 12;
        a5 = *(_DWORD *)(a5 + 10);
      }
      while ( v16 < 12 * a6 );
    }
  }
  a1[5] = g_Defgeneric_SavedBusyCount;
  return v37;
}
// 4C9802: variable 'v15' is possibly undefined
// 4C9842: variable 'v18' is possibly undefined
// 4C9878: variable 'v22' is possibly undefined
// 4C98AB: variable 'v24' is possibly undefined
// 4C98B0: variable 'v25' is possibly undefined
// 4C9A1F: variable 'v33' is possibly undefined
// 4C9A27: variable 'v34' is possibly undefined
// 54E8C8: using guessed type int dword_54E8C8;

//----- (004C9A80) --------------------------------------------------------
int  Method_PackRestrictionTypes(_DWORD *a1, int a2)
{
  _DWORD *v2; // ecx
  int i; // eax
  int v5; // ebx
  _DWORD *v6; // eax
  int v7; // ebx
  unsigned int v8; // edx
  int v9; // eax

  v2 = a1;
  a1[2] = 0;
  for ( i = a2; i; i = *(_DWORD *)(i + 10) )
    ++v2[2];
  v5 = v2[2];
  if ( v5 )
  {
    v6 = Mem_SmallBlockAlloc(4 * v5);
    *v2 = v6;
  }
  else
  {
    *v2 = 0;
  }
  v7 = a2;
  v8 = 0;
  if ( v2[2] )
  {
    v9 = 0;
    do
    {
      ++v8;
      *(_DWORD *)(*v2 + v9) = *(_DWORD *)(v7 + 2);
      v9 += 4;
      v7 = *(_DWORD *)(v7 + 10);
    }
    while ( v8 < v2[2] );
  }
  return AST_Free(a2);
}
// 4C9AB3: variable 'v2' is possibly undefined

//----- (004C9B00) --------------------------------------------------------
int  Method_FreeRestrictionChain(int result)
{
  int i; // ebx
  _DWORD *v2; // eax
  int v3; // ecx
  int v4; // ecx
  int v5; // edx

  for ( i = result; i; *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp )
  {
    v2 = (_DWORD *)i;
    i = *(_DWORD *)(i + 10);
    v3 = *(_DWORD *)((char *)v2 + 6);
    g_ClipsMemFreeListTemp = (int)v2;
    *v2 = *(_DWORD *)(g_ClipsMemoryTable + 56);
    *(_DWORD *)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
    AST_Free(*(_DWORD *)(v3 + 4));
    v5 = *(_DWORD *)(v4 + 8);
    if ( v5 )
      Mem_SmallBlockFree(*(_DWORD **)v4, 4 * v5);
    g_ClipsMemFreeListTemp = v4;
    *(_DWORD *)v4 = *(_DWORD *)(g_ClipsMemoryTable + 48);
    result = g_ClipsMemFreeListTemp;
  }
  return result;
}
// 4C9B37: variable 'v4' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004C9B80) --------------------------------------------------------
int  Method_FindInsertionIndex(int a1, int a2, int a3, int a4, unsigned int *a5)
{
  unsigned int v5; // esi
  int v6; // edi
  signed int v7; // eax
  int v10; // [esp+4h] [ebp-18h]
  int v11; // [esp+8h] [ebp-14h]

  if ( a3 )
  {
    v11 = a4 - 1;
    v10 = -1;
  }
  else
  {
    v10 = a4;
    v11 = a4;
  }
  v5 = 0;
  if ( *(_DWORD *)(a1 + 32) )
  {
    v6 = 0;
    while ( 1 )
    {
      v7 = Method_CompareRestrictionOrder(a2, a4, v10, v11, (_DWORD *)(v6 + *(_DWORD *)(a1 + 28)));
      if ( !v7 )
        break;
      if ( v7 != -1 )
      {
        ++v5;
        v6 += 40;
        if ( v5 < *(_DWORD *)(a1 + 32) )
          continue;
      }
      goto LABEL_8;
    }
    *a5 = -1;
    return v6 + *(_DWORD *)(a1 + 28);
  }
  else
  {
LABEL_8:
    *a5 = v5;
    return 0;
  }
}

//----- (004C9C20) --------------------------------------------------------
signed int Defgeneric_ParseDeclaration()
{
  _BYTE *v0; // ecx
  int v1; // eax
  _BYTE *v2; // ecx
  int v3; // esi
  int v4; // eax
  int v5; // ecx
  int v6; // ecx
  int v7; // eax
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int Name; // eax
  int v12; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // eax
  _BYTE *v17; // ecx
  int **Symbol; // eax
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx

  if ( Rules_FindConstructByName() )
  {
    Rules_PrintErrorID((int)aGenrcpsr, 3, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDefgenericsAre, v14);
    return 0;
  }
  else
  {
    v1 = Deffunction_LookupByName(v0);
    v3 = v1;
    if ( v1 )
    {
      Rules_GetConstructOwnerModule(v1);
      v4 = Module_GetCurrent();
      if ( v5 == v4 )
      {
        Rules_PrintErrorID((int)aGenrcpsr, 5, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDefgenericsA_0, v15);
      }
      else
      {
        Rules_PrintErrorID((int)aGenrcpsr, 4, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDeffunction_0, v6);
        v7 = Rules_GetConstructNameString(v3);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], v7, v8);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aImportedFromMo, v9);
        Name = Module_GetName(v10);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], Name, (int)g_IO_LogicalNameTable_WError[0]);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aConflictsWithT, v12);
      }
      return 0;
    }
    else
    {
      v16 = Defgeneric_ParseConstruct(v2, (int)v2);
      if ( v16 && Defgeneric_MethodsExecuting(v16) )
      {
        Defgeneric_PrintCannotModifyError();
        return 0;
      }
      else
      {
        Symbol = Rules_MakeSymbol(v17);
        if ( Symbol && !*(_WORD *)((char *)Symbol + 21) )
        {
          Rules_PrintErrorID((int)aGenrcpsr, 16, 0);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aTheSystemFunct, v19);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], v20, v20);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotBeOverlo, v21);
          return 0;
        }
        else
        {
          return 1;
        }
      }
    }
  }
}
// 4C9C35: variable 'v0' is possibly undefined
// 4C9C52: variable 'v5' is possibly undefined
// 4C9C73: variable 'v6' is possibly undefined
// 4C9C89: variable 'v8' is possibly undefined
// 4C9C98: variable 'v9' is possibly undefined
// 4C9C9F: variable 'v10' is possibly undefined
// 4C9CBD: variable 'v12' is possibly undefined
// 4C9CE4: variable 'v14' is possibly undefined
// 4C9D0B: variable 'v15' is possibly undefined
// 4C9D19: variable 'v2' is possibly undefined
// 4C9D2F: variable 'v17' is possibly undefined
// 4C9D7A: variable 'v19' is possibly undefined
// 4C9D86: variable 'v20' is possibly undefined
// 4C9D95: variable 'v21' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004C9DB0) --------------------------------------------------------
signed int  Defgeneric_CreateDefaultPPForm(int a1)
{
  int v2; // eax
  const char *Name; // esi
  const char *v4; // edx
  _DWORD *v5; // eax
  const char *v6; // edx
  int v7; // ecx

  v2 = Module_GetCurrent();
  Name = (const char *)Module_GetName(v2);
  v4 = (const char *)Rules_GetConstructNameString(a1);
  v5 = Mem_SmallBlockAlloc(strlen(v4) + strlen(Name) + 17);
  sprintf_(v5, "(defgeneric %s::%s)\n", Name, v6);
  return Rules_ReplaceConstructPPForm(a1, v7);
}
// 4C9DFA: variable 'v6' is possibly undefined
// 4C9E06: variable 'v7' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (004C9E20) --------------------------------------------------------
int  Method_ParseIndexModifier(int a1, _DWORD *a2)
{
  int result; // eax
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int v10; // eax
  int v11; // edx
  int v12; // edx
  int v13; // ecx

  *a2 = 0;
  result = Rules_GetConstructNameAndComment(a1, (int)&g_ClipsMethodParserToken, 0, aDefmethod_1, 0, asc_50B47C, 1, 0, 1);
  v5 = result;
  if ( result )
  {
    if ( g_ClipsMethodParserToken == 1 )
    {
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(asc_50B480);
      IO_OutWriteToken((char *)g_CLIPS_GenericParseTokenPrintStr);
      v10 = *(_DWORD *)(g_Clips_CurrentTokenValue + 16);
      if ( v10 < v11 )
      {
        Rules_PrintErrorID((int)aGenrcpsr, 6, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aMethodIndexOut, v13);
        return 0;
      }
      *a2 = v10;
      AST_Append(v9, (int)&g_ClipsMethodParserToken);
      Parser_NextToken(a1, v12);
    }
    if ( g_ClipsMethodParserToken == 3 )
    {
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(asc_50B480);
      IO_OutWriteToken((char *)g_CLIPS_GenericParseTokenPrintStr);
      AST_Append(v7, v6);
      Parser_NextToken(a1, v8);
    }
    return v5;
  }
  return result;
}
// 4C9E89: variable 'v7' is possibly undefined
// 4C9E89: variable 'v6' is possibly undefined
// 4C9E90: variable 'v8' is possibly undefined
// 4C9E95: variable 'v5' is possibly undefined
// 4C9EC4: variable 'v11' is possibly undefined
// 4C9ECD: variable 'v9' is possibly undefined
// 4C9ED4: variable 'v12' is possibly undefined
// 4C9EF6: variable 'v13' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 54E8D0: using guessed type int dword_54E8D0;
// 54E8D4: using guessed type int dword_54E8D4;
// 54E8D8: using guessed type int dword_54E8D8;

//----- (004C9F10) --------------------------------------------------------
int  Method_ParseParameterList(int a1, signed int *a2, int *a3)
{
  signed int v4; // esi
  int v5; // ebp
  _DWORD *v6; // edx
  _DWORD *v7; // ecx
  int v8; // ecx
  signed int v9; // eax
  int v10; // edx
  int v11; // ecx
  int v13; // ecx
  int v14; // edx
  int v15; // ecx
  int v16; // ebp
  int v17; // edx
  int v18; // ecx
  int v19; // edx
  int v20; // ecx
  int v21; // [esp+0h] [ebp-20h] BYREF
  signed int *v22; // [esp+4h] [ebp-1Ch]
  int *v23; // [esp+8h] [ebp-18h]
  int v24; // [esp+Ch] [ebp-14h]

  v22 = a2;
  v23 = a3;
  v4 = 0;
  *a3 = 0;
  *a2 = 0;
  v24 = 0;
  if ( g_ClipsMethodParserToken != 100 )
  {
    Rules_PrintErrorID((int)aGenrcpsr, 7, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedAToBeg, v13);
    return -1;
  }
  Parser_NextToken(a1, (int)&g_ClipsMethodParserToken);
  while ( g_ClipsMethodParserToken != 101 )
  {
    if ( *v23 )
    {
      Method_FreeRestrictionChain(v4);
      Rules_PrintErrorID((int)aPrccode_1, v14, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoParametersAl, v15);
      return -1;
    }
    if ( g_ClipsMethodParserToken == 15 || g_ClipsMethodParserToken == 16 )
    {
      v5 = g_Clips_CurrentTokenValue;
      if ( Method_CheckDuplicateParameterName(v4, &v21, g_Clips_CurrentTokenValue) )
        goto LABEL_18;
      if ( g_ClipsMethodParserToken == 16 )
        *v23 = v5;
      v6 = *(_DWORD **)(g_ClipsMemoryTable + 48);
      if ( v6 )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
        *(_DWORD *)(g_ClipsMemoryTable + 48) = *v6;
        v7 = (_DWORD *)g_ClipsMemFreeListTemp;
      }
      else
      {
        v7 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0xC);
      }
      Method_PackRestrictionTypes(v7, 0);
      *(_DWORD *)(v8 + 4) = 0;
      v9 = Method_AppendParameterNode(v4, v21, v5);
      v11 = v24 + 1;
      v4 = v9;
      ++v24;
    }
    else
    {
      if ( g_ClipsMethodParserToken != 100 )
      {
        Method_FreeRestrictionChain(v4);
        Rules_PrintErrorID((int)aGenrcpsr, v19, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedAVar_0, v20);
        return -1;
      }
      Parser_NextToken(a1, (int)&g_ClipsMethodParserToken);
      if ( g_ClipsMethodParserToken != 15 && g_ClipsMethodParserToken != 16 )
      {
        Method_FreeRestrictionChain(v4);
        Rules_PrintErrorID((int)aGenrcpsr, v17, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedAVaria, v18);
        return -1;
      }
      v16 = g_Clips_CurrentTokenValue;
      if ( Method_CheckDuplicateParameterName(v4, &v21, g_Clips_CurrentTokenValue) )
        goto LABEL_18;
      if ( g_ClipsMethodParserToken == 16 )
        *v23 = v16;
      IO_OutWriteToken(asc_50B480);
      if ( !Method_ParseParameterRestriction(a1) )
      {
LABEL_18:
        Method_FreeRestrictionChain(v4);
        return -1;
      }
      v4 = Method_AppendParameterNode(v4, v21, v16);
      ++v24;
    }
    AST_Append(v11, v10);
    Parser_NextToken(a1, (int)&g_ClipsMethodParserToken);
  }
  if ( v24 )
  {
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken(asc_50B584);
  }
  *v22 = v4;
  return v24;
}
// 4C9FC2: variable 'v8' is possibly undefined
// 4C9FDE: variable 'v11' is possibly undefined
// 4C9FDE: variable 'v10' is possibly undefined
// 4CA044: variable 'v13' is possibly undefined
// 4CA069: variable 'v14' is possibly undefined
// 4CA078: variable 'v15' is possibly undefined
// 4CA146: variable 'v17' is possibly undefined
// 4CA155: variable 'v18' is possibly undefined
// 4CA17A: variable 'v19' is possibly undefined
// 4CA189: variable 'v20' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E8D0: using guessed type int dword_54E8D0;
// 54E8D4: using guessed type int dword_54E8D4;

//----- (004CA1A0) --------------------------------------------------------
int  Method_ParseParameterRestriction(int a1)
{
  int v2; // edi
  int v3; // ecx
  int v4; // edx
  _DWORD *v5; // ebp
  _DWORD *v6; // ecx
  int v7; // ecx
  int v9; // ecx
  signed int v10; // eax
  int v11; // esi
  int v12; // ebx
  int v13; // ecx
  int v14; // eax
  int v15; // edx
  int v16; // ecx
  int v17; // eax
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // [esp+0h] [ebp-1Ch]

  Parser_NextToken(a1, (int)&g_ClipsMethodParserToken);
  v2 = 0;
  v3 = g_ClipsMethodParserToken;
  v23 = 0;
  if ( g_ClipsMethodParserToken == 101 )
  {
LABEL_8:
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken(asc_50B584);
    if ( v2 || v23 )
    {
      v5 = *(_DWORD **)(g_ClipsMemoryTable + 48);
      if ( v5 )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
        *(_DWORD *)(g_ClipsMemoryTable + 48) = *v5;
        v6 = (_DWORD *)g_ClipsMemFreeListTemp;
      }
      else
      {
        v6 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0xC);
      }
      v6[1] = v23;
      Method_PackRestrictionTypes(v6, v2);
      return v7;
    }
    else
    {
      Rules_PrintErrorID((int)aGenrcpsr, 13, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedAValid, v22);
      return 0;
    }
  }
  while ( 1 )
  {
    if ( v23 )
    {
      Rules_PrintErrorID((int)aGenrcpsr, 10, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aQueryMustBeLas, v9);
      AST_Free(v23);
      AST_Free(v2);
      return 0;
    }
    if ( g_ClipsMethodParserToken == 2 )
      break;
    if ( g_ClipsMethodParserToken == 100 )
    {
      v23 = Parser_ParseExpression(a1, v3);
      if ( !v23 )
        goto LABEL_30;
      if ( Parser_GetLoopContextStack() )
      {
        Rules_PrintErrorID((int)aGenrcpsr, 12, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aBindsAreNotAll, v19);
        AST_Free(v20);
LABEL_30:
        AST_Free(v2);
        return 0;
      }
    }
    else
    {
      if ( g_ClipsMethodParserToken != 13 )
      {
        Rules_PrintErrorID((int)aGenrcpsr, 13, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedAValid, v21);
        AST_Free(0);
        AST_Free(v2);
        return 0;
      }
      v23 = AST_NewNode(13, g_Clips_CurrentTokenValue);
    }
LABEL_7:
    IO_OutWriteToken(asc_50B480);
    Parser_NextToken(a1, v4);
    if ( g_ClipsMethodParserToken == 101 )
      goto LABEL_8;
  }
  v10 = Method_ParseParameterClassName(g_Clips_CurrentTokenValue);
  v11 = v10;
  if ( !v10 )
  {
    AST_Free(v2);
    AST_Free(0);
    return 0;
  }
  if ( !v2 )
  {
    v2 = v10;
    goto LABEL_7;
  }
  v12 = v2;
  while ( 1 )
  {
    v13 = v11;
    if ( v11 )
      break;
LABEL_23:
    v17 = v12;
    v12 = *(_DWORD *)(v12 + 10);
    if ( !v12 )
    {
      *(_DWORD *)(v17 + 10) = v11;
      goto LABEL_7;
    }
  }
  while ( 1 )
  {
    v14 = *(_DWORD *)(v12 + 2);
    v15 = *(_DWORD *)(v13 + 2);
    if ( v14 == v15 )
      break;
    if ( Method_CheckRedundantClassPair(v14, v15) )
      goto LABEL_26;
    v13 = *(_DWORD *)(v16 + 10);
    if ( !v13 )
      goto LABEL_23;
  }
  Rules_PrintErrorID((int)aGenrcpsr, 11, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDuplicateClass, v18);
LABEL_26:
  AST_Free(0);
  AST_Free(v2);
  AST_Free(v11);
  return 0;
}
// 4CA2F0: conditional instruction was optimized away because edi.4!=0
// 4CA214: variable 'v4' is possibly undefined
// 4CA26F: variable 'v7' is possibly undefined
// 4CA296: variable 'v9' is possibly undefined
// 4CA30B: variable 'v16' is possibly undefined
// 4CA33E: variable 'v18' is possibly undefined
// 4CA367: variable 'v3' is possibly undefined
// 4CA39D: variable 'v19' is possibly undefined
// 4CA3A4: variable 'v20' is possibly undefined
// 4CA3D7: variable 'v21' is possibly undefined
// 4CA412: variable 'v22' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E8D0: using guessed type int dword_54E8D0;
// 54E8D4: using guessed type int dword_54E8D4;

//----- (004CA440) --------------------------------------------------------
int ** Method_ReplaceCurrentArgumentRefs(int **result)
{
  int v1; // ecx

  v1 = (int)result;
  if ( result )
  {
    do
    {
      if ( *(_WORD *)v1 == 15 )
      {
        result = (int **)(strcmp_(v1, aCurrentArgumen) == 0);
        if ( result )
        {
          *(_WORD *)v1 = 10;
          result = Rules_MakeSymbol(aGnrcCurrentA_0);
          *(_DWORD *)(v1 + 2) = result;
        }
      }
      if ( *(_DWORD *)(v1 + 6) )
        result = (int **)Method_ReplaceCurrentArgumentRefs(*(_DWORD *)(v1 + 6));
      v1 = *(_DWORD *)(v1 + 10);
    }
    while ( v1 );
  }
  return result;
}
// 4CA44E: variable 'v1' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004CA4A0) --------------------------------------------------------
signed int  Method_CheckDuplicateParameterName(int a1, _DWORD *a2, int a3)
{
  int v3; // ecx
  int v5; // ecx

  *a2 = 0;
  if ( !a1 )
    return 0;
  while ( 1 )
  {
    v3 = *(_DWORD *)(a1 + 2);
    if ( a3 == v3 )
      break;
    *a2 = a1;
    a1 = *(_DWORD *)(a1 + 10);
    if ( !a1 )
      return 0;
  }
  Rules_PrintErrorID((int)aPrccode_1, 7, v3 ^ a3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDuplicateParam, v5);
  return 1;
}
// 4CA4DA: variable 'v5' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004CA4F0) --------------------------------------------------------
signed int  Method_AppendParameterNode(signed int a1, int a2, int a3)
{
  signed int result; // eax
  int v6; // ecx
  signed int v7; // edx

  result = AST_NewNode(2, a3);
  v7 = result;
  if ( a1 )
  {
    *(_DWORD *)(a2 + 10) = result;
    result = a1;
    *(_DWORD *)(v7 + 6) = v6;
  }
  else
  {
    *(_DWORD *)(result + 6) = v6;
  }
  return result;
}
// 4CA50C: variable 'v6' is possibly undefined

//----- (004CA520) --------------------------------------------------------
signed int  Method_ParseParameterClassName(int a1)
{
  int v1; // edx
  int *v2; // eax
  int v3; // ecx

  if ( Rules_FindModuleSeparator(*(_BYTE **)(a1 + 16)) )
  {
    Module_ReportIllegalSpecifierError();
    return 0;
  }
  else
  {
    v2 = Class_LookupInScope(*(_BYTE **)(v1 + 16));
    if ( v2 )
    {
      return AST_NewNode(5, (int)v2);
    }
    else
    {
      Rules_PrintErrorID((int)aGenrcpsr, 14, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnknownClassIn, v3);
      return 0;
    }
  }
}
// 4CA52F: variable 'v1' is possibly undefined
// 4CA557: variable 'v3' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004CA580) --------------------------------------------------------
signed int  Method_CheckRedundantClassPair(int a1, int a2)
{
  int v3; // ecx
  int v4; // eax
  int v5; // ecx
  int v6; // ecx
  signed int result; // eax

  if ( Class_HasSuperclass(a1, a2) )
  {
    v4 = v3;
LABEL_3:
    Rules_GetConstructNameString(v4);
    Rules_PrintErrorID((int)aGenrcpsr, 15, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], v5, v5);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aClassIsRedunda, v6);
    return 1;
  }
  result = Class_HasSuperclass(a2, v3);
  if ( result )
  {
    v4 = a2;
    goto LABEL_3;
  }
  return result;
}
// 4CA58F: variable 'v3' is possibly undefined
// 4CA5B0: variable 'v5' is possibly undefined
// 4CA5BF: variable 'v6' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004CA5E0) --------------------------------------------------------
int  Defgeneric_AddConstruct(int a1, _DWORD *a2)
{
  int v3; // eax
  int v4; // ecx
  int v5; // edx
  int v6; // edx
  _DWORD *v8; // eax
  int v9; // ecx

  v3 = Defgeneric_ParseConstruct(*(_BYTE **)(a1 + 16), a1);
  v5 = v3;
  if ( v3 )
  {
    *a2 = 0;
    Rules_UnlinkListNode(v3);
  }
  else
  {
    *a2 = 1;
    v8 = Defgeneric_AllocateRecord(v4);
    ++*(_DWORD *)(v9 + 4);
    Defgeneric_InitializeFromRestrictionString((int)v8, v9);
  }
  Rules_AppendConstructToModuleList(v5);
  return v6;
}
// 4CA601: variable 'v5' is possibly undefined
// 4CA606: variable 'v6' is possibly undefined
// 4CA613: variable 'v4' is possibly undefined
// 4CA618: variable 'v9' is possibly undefined

//----- (004CA640) --------------------------------------------------------
_DWORD * Defgeneric_InsertMethodSlot(_DWORD *a1, int a2, unsigned int a3)
{
  unsigned int v3; // ebx
  int v4; // edx
  int v5; // ebp
  _DWORD *v6; // eax
  int v7; // edx
  _DWORD *v8; // edx
  char v9; // al
  char v10; // bl
  int v11; // ebp
  char v12; // bh
  _DWORD *v16; // [esp+8h] [ebp-18h]

  v16 = Mem_SmallBlockAlloc(40 * (a1[8] + 1));
  v3 = 0;
  v4 = 0;
  if ( a1[8] )
  {
    v5 = 0;
    do
    {
      if ( v3 == a2 )
        ++v4;
      qmemcpy(&v16[10 * v4], (const void *)(v5 + a1[7]), 0x28u);
      ++v3;
      v5 += 40;
      ++v4;
    }
    while ( v3 < a1[8] );
  }
  v6 = &v16[10 * a2];
  if ( a3 )
  {
    *v6 = a3;
    if ( a3 >= a1[9] )
      a1[9] = a3 + 1;
  }
  else
  {
    v7 = a1[9];
    a1[9] = v7 + 1;
    *v6 = v7;
  }
  v8 = &v16[10 * a2];
  v8[1] = 0;
  v9 = g_Rules_WatchMethods;
  v8[3] = 0;
  v8[4] = 0;
  v8[2] = 0;
  v10 = *((_BYTE *)v8 + 24);
  v8[5] = 0;
  v8[7] = 0;
  *((_BYTE *)v8 + 24) = v10 & 0xFD;
  v11 = v8[6];
  v8[8] = 0;
  v8[6] = (2 * (v9 & 1)) | v11;
  v12 = *((_BYTE *)v8 + 24);
  v8[9] = 0;
  *((_BYTE *)v8 + 24) = v12 & 0xFE;
  if ( a1[8] )
    Mem_SmallBlockFree((_DWORD *)a1[7], 40 * a1[8]);
  ++a1[8];
  a1[7] = v16;
  return &v16[10 * a2];
}
// 51B3E4: using guessed type int dword_51B3E4;

//----- (004CA7F0) --------------------------------------------------------
signed int  Method_CompareRestrictionOrder(int a1, int a2, int a3, int a4, _DWORD *a5)
{
  int v6; // ecx
  int v7; // ebx
  int v8; // esi
  signed int result; // eax
  int v10; // ecx
  int v12; // [esp+4h] [ebp-20h]
  int v13; // [esp+8h] [ebp-1Ch]
  int v16; // [esp+14h] [ebp-10h]

  v6 = 0;
  v13 = 0;
  if ( a2 > 0 )
  {
    v16 = 0;
    v12 = a2 - 1;
    while ( v6 < a5[2] )
    {
      if ( v6 == v12 && a3 == -1 && a5[4] != -1 )
        return 1;
      if ( v6 == a5[2] - 1 && a3 != -1 && a5[4] == -1 )
        return -1;
      v7 = v16 + a5[7];
      v8 = *(_DWORD *)(a1 + 6);
      result = Method_CompareTypeArrays((_DWORD *)v8, (_DWORD *)v7);
      if ( result )
        return result;
      if ( !*(_DWORD *)(v8 + 4) && *(_DWORD *)(v7 + 4) )
        return 1;
      if ( *(_DWORD *)(v8 + 4) && !*(_DWORD *)(v7 + 4) )
        return -1;
      if ( !AST_NodeListsEqual(*(__int16 **)(v8 + 4), *(__int16 **)(v7 + 4)) )
        v13 = 1;
      v6 = v10 + 1;
      a1 = *(_DWORD *)(a1 + 10);
      v16 += 12;
      if ( v6 >= a2 )
        break;
    }
  }
  if ( a2 == a5[2] )
    return v13 != 0;
  if ( a4 <= a5[3] && a3 == -1 )
    return 1;
  return -1;
}
// 4CA8B6: variable 'v10' is possibly undefined

//----- (004CA920) --------------------------------------------------------
signed int  Method_CompareTypeArrays(_DWORD *a1, _DWORD *a2)
{
  unsigned int v4; // ebx
  int v5; // ecx
  int *v6; // eax
  int *v7; // edx
  unsigned int v8; // eax
  unsigned int v9; // edx
  int v11; // ecx
  int v12; // [esp+0h] [ebp-18h]

  v12 = 0;
  if ( !a1[2] && !a2[2] )
    return 0;
  if ( !a1[2] )
    return 1;
  if ( a2[2] )
  {
    v4 = 0;
    v5 = 0;
    while ( v4 < a2[2] )
    {
      v6 = (int *)(v5 + *a1);
      v7 = (int *)(v5 + *a2);
      if ( *v6 != *v7 )
      {
        v12 = 1;
        if ( Class_HasSuperclass(*v6, *v7) )
          return -1;
        if ( Class_HasSuperclass(*(_DWORD *)(v11 + *a2), *(_DWORD *)(v11 + *a1)) )
          return 1;
      }
      ++v4;
      v5 += 4;
      if ( v4 >= a1[2] )
        break;
    }
    v8 = a1[2];
    v9 = a2[2];
    if ( v8 < v9 )
      return -1;
    return v8 > v9 || v12;
  }
  return -1;
}
// 4CA94F: conditional instruction was optimized away because ebp.4!=0
// 4CA96A: variable 'v5' is possibly undefined
// 4CA9C6: variable 'v11' is possibly undefined

//----- (004CA9E0) --------------------------------------------------------
_DWORD * Defgeneric_AllocateRecord(int a1)
{
  _DWORD *v2; // edx
  _DWORD *v3; // ecx
  _DWORD *result; // eax

  v2 = *(_DWORD **)(g_ClipsMemoryTable + 160);
  if ( v2 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 160);
    *(_DWORD *)(g_ClipsMemoryTable + 160) = *v2;
  }
  else
  {
    Mem_HeapAllocWithRetry((_DWORD *)0x28);
  }
  Rules_InitConstructModuleRecord((int)aDefgeneric_1, a1);
  v3[5] = 0;
  v3[9] = 1;
  v3[7] = 0;
  v3[8] = 0;
  result = v3;
  v3[6] = g_Rules_WatchGenericFunctions;
  return result;
}
// 4CAA15: variable 'v3' is possibly undefined
// 51B3E0: using guessed type int dword_51B3E0;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004CAA50) --------------------------------------------------------
int  Method_DispatchGenericCall(
        int a1,
        int a2,
        _DWORD *a3,
        int *a4,
        double a5,
        _DWORD *a6)
{
  int result; // eax
  int v9; // ebx
  int v10; // eax
  int v11; // ecx
  int v12; // edx
  int v13; // eax
  int v14; // ecx
  int v15; // edx
  int v16; // eax
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // eax
  int v23; // ecx
  int v24; // ecx
  __int16 v25; // [esp+0h] [ebp-34h] BYREF
  int v26; // [esp+2h] [ebp-32h]
  int v27; // [esp+6h] [ebp-2Eh]
  int v28; // [esp+Ah] [ebp-2Ah]
  int v29; // [esp+10h] [ebp-24h]
  int v30; // [esp+14h] [ebp-20h]
  int v31; // [esp+18h] [ebp-1Ch]
  _DWORD *v32; // [esp+1Ch] [ebp-18h]
  int v33; // [esp+20h] [ebp-14h]
  int v34; // [esp+24h] [ebp-10h]

  v30 = a2;
  v32 = a3;
  a6[1] = 2;
  result = g_ClipsFalseSymbol;
  a6[2] = g_ClipsFalseSymbol;
  g_ClipsEvaluationError = 0;
  if ( !g_ClipsHaltExecution )
  {
    v34 = Rules_GetReentryGuardFlag();
    v29 = v34;
    Rules_SetReentryGuardFlag(1);
    v31 = g_ClipsCurrentGeneric;
    g_ClipsCurrentGeneric = a1;
    ++g_ClipsCurrentEvaluationDepth;
    v33 = g_ClipsCurrentMethod;
    ++*(_DWORD *)(a1 + 20);
    v9 = Rules_GetConstructNameString(a1);
    v10 = AST_CountListNodes((int)v32);
    ProcParam_PushEvaluatedArgumentFrame(v32, v10, v11, v9, a5, (int (*)(void))Method_PrintCallErrorBanner);
    if ( g_ClipsEvaluationError )
    {
      v13 = v31;
      --*(_DWORD *)(a1 + 20);
      g_ClipsCurrentGeneric = v13;
      g_ClipsCurrentMethod = v33;
      --g_ClipsCurrentEvaluationDepth;
      Rules_RunPeriodicCleanup(0, 1);
      return Rules_SetReentryGuardFlag(v34);
    }
    else
    {
      if ( a4 )
      {
        if ( Method_RestrictionsSatisfiedByArgs((int)a4, a5) )
        {
          ++a4[1];
          g_ClipsCurrentMethod = (int)a4;
        }
        else
        {
          Rules_PrintErrorID((int)aGenrcexe, 4, 0);
          Lexer_ErrorRecover(1);
          g_ClipsCurrentMethod = v14;
          Output_Write((int)g_IO_LogicalNameTable_WError[0], v15, v14);
          v16 = Rules_GetConstructNameString(a1);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], v16, v17);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aMethod_2, v18);
          Rules_PrintLongInteger(v19, *a4);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIsNotApplicabl, v20);
        }
      }
      else
      {
        g_ClipsCurrentMethod = Method_FindApplicableMethod(a1, v30, a5);
      }
      if ( g_ClipsCurrentMethod )
      {
        if ( *(_DWORD *)(g_ClipsCurrentGeneric + 24) )
          Method_PrintGenericCallTrace((int)asc_50B73C);
        if ( (*(_BYTE *)(g_ClipsCurrentMethod + 24) & 2) != 0 )
          Method_PrintMethodCallTrace((int)asc_50B73C);
        if ( (*(_BYTE *)(g_ClipsCurrentMethod + 24) & 1) != 0 )
        {
          v25 = 10;
          v26 = *(_DWORD *)(*(_DWORD *)(g_ClipsCurrentMethod + 32) + 2);
          v28 = 0;
          v27 = ProcParam_BuildArgumentExpressionChain();
          Parser_ParseForm(&v25, a6, 0, a5);
        }
        else
        {
          Rules_ExecuteRuleActions(
            **(_DWORD **)(g_ClipsCurrentGeneric + 8),
            *(__int16 **)(g_ClipsCurrentMethod + 32),
            a6,
            *(_DWORD *)(g_ClipsCurrentMethod + 20),
            a5,
            (void (*)(void))Method_PrintCallErrorBanner);
        }
        --*(_DWORD *)(g_ClipsCurrentMethod + 4);
        if ( (*(_BYTE *)(g_ClipsCurrentMethod + 24) & 2) != 0 )
          Method_PrintMethodCallTrace((int)asc_50B740);
        if ( *(_DWORD *)(g_ClipsCurrentGeneric + 24) )
          Method_PrintGenericCallTrace((int)asc_50B740);
      }
      else if ( !g_ClipsEvaluationError )
      {
        Rules_PrintErrorID((int)aGenrcexe, 1, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoApplicable_0, v21);
        v22 = Rules_GetConstructNameString(a1);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], v22, v23);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__24, v24);
        Lexer_ErrorRecover(1);
      }
      --*(_DWORD *)(a1 + 20);
      g_ClipsHaltExecutionFlag = 0;
      ProcParam_PopFrame();
      g_ClipsCurrentGeneric = v31;
      g_ClipsCurrentMethod = v33;
      --g_ClipsCurrentEvaluationDepth;
      Rules_PropagateReturnValueDepth((int)a6);
      Rules_RunPeriodicCleanup(0, v12);
      return Rules_SetReentryGuardFlag(v29);
    }
  }
  return result;
}
// 4CAAF5: variable 'v11' is possibly undefined
// 4CAC08: variable 'v12' is possibly undefined
// 4CAC8A: variable 'v14' is possibly undefined
// 4CAC90: variable 'v15' is possibly undefined
// 4CACA6: variable 'v17' is possibly undefined
// 4CACB5: variable 'v18' is possibly undefined
// 4CACC1: variable 'v19' is possibly undefined
// 4CACD0: variable 'v20' is possibly undefined
// 4CAD38: variable 'v21' is possibly undefined
// 4CAD4E: variable 'v23' is possibly undefined
// 4CAD5D: variable 'v24' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A964: using guessed type int dword_51A964;
// 51A968: using guessed type int dword_51A968;
// 51A96C: using guessed type int dword_51A96C;
// 51ACC0: using guessed type int dword_51ACC0;
// 51B3D4: using guessed type int dword_51B3D4;
// 51B3D8: using guessed type int dword_51B3D8;
// 54DD70: using guessed type int dword_54DD70;

//----- (004CAD80) --------------------------------------------------------
signed int __thiscall Method_PrintCallErrorBanner(void *this)
{
  int v1; // eax
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx

  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aGenericFunct_5, (int)this);
  v1 = Rules_GetConstructNameString(g_ClipsCurrentGeneric);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v1, (int)g_IO_LogicalNameTable_WError[0]);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aMethod_2, v2);
  Rules_PrintLongInteger(v3, *(_DWORD *)g_ClipsCurrentMethod);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__24, v4);
}
// 4CADB4: variable 'v2' is possibly undefined
// 4CADC6: variable 'v3' is possibly undefined
// 4CADD5: variable 'v4' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51B3D4: using guessed type int dword_51B3D4;
// 51B3D8: using guessed type int dword_51B3D8;

//----- (004CADE0) --------------------------------------------------------
int  Method_RestrictionsSatisfiedByArgs(int a1, double a2)
{
  int v2; // ecx
  int i; // ebp
  int v4; // ebx
  int result; // eax
  unsigned int v6; // esi
  int *v7; // eax
  _DWORD *v8; // eax
  bool v9; // zf
  int v10; // edx
  int v11; // [esp+0h] [ebp-44h] BYREF
  __int64 v12; // [esp+4h] [ebp-40h]
  int v13; // [esp+18h] [ebp-2Ch]
  int v14; // [esp+1Ch] [ebp-28h]
  int v15; // [esp+20h] [ebp-24h]
  int v16; // [esp+24h] [ebp-20h]
  int v17; // [esp+28h] [ebp-1Ch]

  v13 = a1;
  v2 = *(_DWORD *)(a1 + 12);
  if ( g_ClipsProcParamCount < v2 || g_ClipsProcParamCount > v2 && *(_DWORD *)(a1 + 16) != -1 )
    return 0;
  v16 = 0;
  v14 = 0;
  if ( g_ClipsProcParamCount > 0 )
  {
    v15 = 0;
    for ( i = 0; ; i += 24 )
    {
      v4 = v15 + *(_DWORD *)(v13 + 28);
      if ( !*(_DWORD *)(v4 + 8) )
        goto LABEL_7;
      result = Method_GetArgumentClass(i + g_ClipsProcParamArray);
      v17 = result;
      if ( !result )
        return result;
      v6 = 0;
      if ( *(_DWORD *)(v4 + 8) )
        break;
LABEL_19:
      if ( v6 == *(_DWORD *)(v4 + 8) )
        return 0;
LABEL_7:
      if ( *(_DWORD *)(v4 + 4) )
      {
        g_Method_CurrentArgParamPtr = i + g_ClipsProcParamArray;
        Parser_ParseForm(*(__int16 **)(v4 + 4), &v11, v2, a2);
        if ( v12 == __PAIR64__(g_ClipsFalseSymbol, 2) )
          return 0;
      }
      if ( *(_DWORD *)(v13 + 8) - 1 != v14 )
      {
        ++v14;
        v15 += 12;
      }
      v2 = g_ClipsProcParamCount;
      if ( ++v16 >= g_ClipsProcParamCount )
        return 1;
    }
    v2 = 0;
    while ( 1 )
    {
      v7 = (int *)(v2 + *(_DWORD *)v4);
      if ( v17 == *v7 || Class_HasSuperclass(v17, *v7) )
        goto LABEL_19;
      v8 = (_DWORD *)(v2 + *(_DWORD *)v4);
      if ( *v8 == g_Class_InstanceAddress )
        break;
      if ( *v8 == g_Class_InstanceName )
      {
        v9 = *(_DWORD *)(i + g_ClipsProcParamArray + 4) == 8;
LABEL_24:
        if ( v9 )
          goto LABEL_19;
        goto LABEL_25;
      }
      if ( *v8 == **(_DWORD **)(g_Class_InstanceName + 36) )
      {
        v10 = *(_DWORD *)(i + g_ClipsProcParamArray + 4);
        if ( v10 == 8 )
          goto LABEL_19;
        v9 = v10 == 7;
        goto LABEL_24;
      }
LABEL_25:
      ++v6;
      v2 += 4;
      if ( v6 >= *(_DWORD *)(v4 + 8) )
        goto LABEL_19;
    }
    v9 = *(_DWORD *)(i + g_ClipsProcParamArray + 4) == 7;
    goto LABEL_24;
  }
  return 1;
}
// 4CAE58: variable 'v2' is possibly undefined
// 51ABB8: using guessed type int dword_51ABB8;
// 51ABBC: using guessed type int dword_51ABBC;
// 51AD98: using guessed type int dword_51AD98;
// 51AD9C: using guessed type int dword_51AD9C;
// 51B3DC: using guessed type int dword_51B3DC;
// 54DD70: using guessed type int dword_54DD70;

//----- (004CAF90) --------------------------------------------------------
int  Method_HasNextApplicableMethod(double a1)
{
  int result; // eax
  int v2; // edx

  if ( !g_ClipsCurrentMethod )
    return 0;
  result = Method_FindApplicableMethod(g_ClipsCurrentGeneric, g_ClipsCurrentMethod, a1);
  v2 = result;
  if ( result )
  {
    result = 1;
    --*(_DWORD *)(v2 + 4);
  }
  return result;
}
// 51B3D4: using guessed type int dword_51B3D4;
// 51B3D8: using guessed type int dword_51B3D8;

//----- (004CAFC0) --------------------------------------------------------
int  Method_OverrideNextMethod(_DWORD *a1, int a2, double a3)
{
  _DWORD *v3; // ecx
  int result; // eax
  int v5; // esi
  int v6; // ecx
  __int16 v7; // [esp+0h] [ebp-20h] BYREF
  int v8; // [esp+2h] [ebp-1Eh]
  int v9; // [esp+6h] [ebp-1Ah]
  int v10; // [esp+Ah] [ebp-16h]
  int v11; // [esp+18h] [ebp-8h]

  v11 = a2;
  v3 = a1;
  a1[1] = 2;
  result = g_ClipsFalseSymbol;
  v3[2] = g_ClipsFalseSymbol;
  if ( !g_ClipsHaltExecution )
  {
    v5 = g_ClipsCurrentMethod;
    if ( g_ClipsCurrentMethod )
      g_ClipsCurrentMethod = Method_FindApplicableMethod(g_ClipsCurrentGeneric, g_ClipsCurrentMethod, a3);
    if ( g_ClipsCurrentMethod )
    {
      if ( (*(_BYTE *)(g_ClipsCurrentMethod + 24) & 2) != 0 )
        Method_PrintMethodCallTrace((int)asc_50B73C);
      if ( (*(_BYTE *)(g_ClipsCurrentMethod + 24) & 1) != 0 )
      {
        v7 = 10;
        v8 = *(_DWORD *)(*(_DWORD *)(g_ClipsCurrentMethod + 32) + 2);
        v10 = 0;
        v9 = ProcParam_BuildArgumentExpressionChain();
        Parser_ParseForm(&v7, v3, (int)v3, a3);
      }
      else
      {
        Rules_ExecuteRuleActions(
          **(_DWORD **)(g_ClipsCurrentGeneric + 8),
          *(__int16 **)(g_ClipsCurrentMethod + 32),
          v3,
          *(_DWORD *)(g_ClipsCurrentMethod + 20),
          a3,
          (void (*)(void))Method_PrintCallErrorBanner);
      }
      --*(_DWORD *)(g_ClipsCurrentMethod + 4);
      if ( (*(_BYTE *)(g_ClipsCurrentMethod + 24) & 2) != 0 )
        Method_PrintMethodCallTrace((int)asc_50B740);
      result = 0;
      g_ClipsCurrentMethod = v5;
      g_ClipsHaltExecutionFlag = 0;
    }
    else
    {
      g_ClipsCurrentMethod = v5;
      Rules_PrintErrorID((int)aGenrcexe, 2, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aShadowedMethod, v6);
      return Lexer_ErrorRecover(1);
    }
  }
  return result;
}
// 4CB047: variable 'v3' is possibly undefined
// 4CB0B4: variable 'v6' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A968: using guessed type int dword_51A968;
// 51ACC0: using guessed type int dword_51ACC0;
// 51B3D4: using guessed type int dword_51B3D4;
// 51B3D8: using guessed type int dword_51B3D8;
// 54DD70: using guessed type int dword_54DD70;

//----- (004CB0F0) --------------------------------------------------------
signed int  Method_EvaluateCallSpecificMethod(_DWORD *a1, double a2)
{
  signed int result; // eax
  int v4; // esi
  int v5; // ebp
  _DWORD v6[2]; // [esp+0h] [ebp-30h] BYREF
  int v7; // [esp+8h] [ebp-28h]

  a1[1] = 2;
  a1[2] = g_ClipsFalseSymbol;
  result = Lexer_ParseValueList(1, v6, 2, a2);
  if ( result )
  {
    result = Defgeneric_CheckGenericExists((int)aCallSpecific_0, *(_BYTE **)(v7 + 16));
    v4 = result;
    if ( result )
    {
      result = Lexer_ParseValueList(2, v6, 1, a2);
      if ( result )
      {
        result = Defgeneric_CheckMethodExists((int)aCallSpecific_0, v4, *(_DWORD *)(v7 + 16));
        if ( result != -1 )
        {
          v5 = 40 * result;
          ++*(_DWORD *)(*(_DWORD *)(v4 + 28) + 40 * result + 4);
          Method_DispatchGenericCall(
            v4,
            0,
            *(_DWORD **)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10),
            (int *)(40 * result + *(_DWORD *)(v4 + 28)),
            a2,
            a1);
          result = *(_DWORD *)(v4 + 28);
          --*(_DWORD *)(result + v5 + 4);
        }
      }
    }
  }
  return result;
}
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (004CB1C0) --------------------------------------------------------
_DWORD * Method_CallNextMethod(_DWORD *result, double a2)
{
  int v2; // ecx

  result[1] = 2;
  result[2] = g_ClipsFalseSymbol;
  if ( !g_ClipsHaltExecution )
  {
    if ( g_ClipsCurrentMethod )
    {
      return (_DWORD *)Method_DispatchGenericCall(g_ClipsCurrentGeneric, g_ClipsCurrentMethod, *(_DWORD **)(g_ClipsCurrentExpression + 6), 0, a2, result);
    }
    else
    {
      Rules_PrintErrorID((int)aGenrcexe, 2, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aShadowedMethod, v2);
      return (_DWORD *)Lexer_ErrorRecover(1);
    }
  }
  return result;
}
// 4CB1FF: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A960: using guessed type int dword_51A960;
// 51A968: using guessed type int dword_51A968;
// 51B3D4: using guessed type int dword_51B3D4;
// 51B3D8: using guessed type int dword_51B3D8;
// 54DD70: using guessed type int dword_54DD70;

//----- (004CB240) --------------------------------------------------------
_DWORD * Method_SaveCurrentArgContext(_DWORD *result)
{
  result[1] = *(_DWORD *)(g_Method_CurrentArgParamPtr + 4);
  result[2] = *(_DWORD *)(g_Method_CurrentArgParamPtr + 8);
  result[3] = *(_DWORD *)(g_Method_CurrentArgParamPtr + 12);
  result[4] = *(_DWORD *)(g_Method_CurrentArgParamPtr + 16);
  return result;
}
// 51B3DC: using guessed type int dword_51B3DC;

//----- (004CB280) --------------------------------------------------------
int  Method_FindApplicableMethod(int a1, int a2, double a3)
{
  int v3; // ecx
  unsigned int v4; // edx
  int v6; // edx
  int v7; // ebp

  v3 = a1;
  if ( a2 )
    v4 = a2 + 40;
  else
    v4 = *(_DWORD *)(a1 + 28);
  while ( 1 )
  {
    if ( v4 >= 40 * *(_DWORD *)(v3 + 32) + *(_DWORD *)(v3 + 28) )
      return 0;
    ++*(_DWORD *)(v4 + 4);
    if ( Method_RestrictionsSatisfiedByArgs(v4, a3) )
      break;
    v7 = *(_DWORD *)(v6 + 4);
    v4 = v6 + 40;
    *(_DWORD *)(v4 - 36) = v7 - 1;
  }
  return v6;
}
// 4CB28D: variable 'v3' is possibly undefined
// 4CB2B8: variable 'v6' is possibly undefined

//----- (004CB2D0) --------------------------------------------------------
signed int  Method_PrintGenericCallTrace(int a1)
{
  int v1; // ecx
  int v2; // ecx
  int v3; // eax
  int v4; // ecx
  _DWORD *v5; // edx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int Name; // eax
  int v11; // ecx

  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)aGnc, a1);
  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], v1, v1);
  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_50B7D0, v2);
  v3 = Module_GetCurrent();
  if ( v3 != *v5 )
  {
    Name = Module_GetName(**(_DWORD **)(g_ClipsCurrentGeneric + 8));
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], Name, (int)g_IO_LogicalNameTable_WTrace[0]);
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_50B7D4, v11);
  }
  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], *(_DWORD *)(*(_DWORD *)g_ClipsCurrentGeneric + 16), v4);
  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_50B7D0, v6);
  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)aEd_1, v7);
  Rules_PrintLongInteger(v8, g_ClipsCurrentEvaluationDepth);
  return ProcParam_PrintArguments((int)g_IO_LogicalNameTable_WTrace[0]);
}
// 4CB2EA: variable 'v1' is possibly undefined
// 4CB2F9: variable 'v2' is possibly undefined
// 4CB30B: variable 'v5' is possibly undefined
// 4CB387: variable 'v11' is possibly undefined
// 4CB31F: variable 'v4' is possibly undefined
// 4CB32E: variable 'v6' is possibly undefined
// 4CB33D: variable 'v7' is possibly undefined
// 4CB34D: variable 'v8' is possibly undefined
// 51A618: using guessed type char *off_51A618[4];
// 51A96C: using guessed type int dword_51A96C;
// 51B3D4: using guessed type int dword_51B3D4;

//----- (004CB390) --------------------------------------------------------
signed int  Method_PrintMethodCallTrace(int a1)
{
  int v1; // ecx
  int v2; // ecx
  int v3; // eax
  int v4; // ecx
  _DWORD *v5; // edx
  int Name; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx

  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)aMth, a1);
  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], v1, v1);
  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_50B7D0, v2);
  v3 = Module_GetCurrent();
  if ( v3 != *v5 )
  {
    Name = Module_GetName(**(_DWORD **)(g_ClipsCurrentGeneric + 8));
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], Name, (int)g_IO_LogicalNameTable_WTrace[0]);
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_50B7D4, v7);
  }
  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], *(_DWORD *)(*(_DWORD *)g_ClipsCurrentGeneric + 16), v4);
  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_50B7E8, v8);
  if ( (*(_BYTE *)(g_ClipsCurrentMethod + 24) & 1) != 0 )
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)aSys_0, v9);
  Rules_PrintLongInteger(v9, *(_DWORD *)g_ClipsCurrentMethod);
  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_50B7D0, v10);
  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)aEd_1, v11);
  Rules_PrintLongInteger(v12, g_ClipsCurrentEvaluationDepth);
  return ProcParam_PrintArguments((int)g_IO_LogicalNameTable_WTrace[0]);
}
// 4CB3AA: variable 'v1' is possibly undefined
// 4CB3B9: variable 'v2' is possibly undefined
// 4CB3CB: variable 'v5' is possibly undefined
// 4CB3F7: variable 'v7' is possibly undefined
// 4CB40C: variable 'v4' is possibly undefined
// 4CB41B: variable 'v8' is possibly undefined
// 4CB482: variable 'v9' is possibly undefined
// 4CB447: variable 'v10' is possibly undefined
// 4CB456: variable 'v11' is possibly undefined
// 4CB466: variable 'v12' is possibly undefined
// 51A618: using guessed type char *off_51A618[4];
// 51A96C: using guessed type int dword_51A96C;
// 51B3D4: using guessed type int dword_51B3D4;
// 51B3D8: using guessed type int dword_51B3D8;

//----- (004CB490) --------------------------------------------------------
int  Method_GetArgumentClass(int a1)
{
  int v1; // edx
  _DWORD *v2; // eax
  int v3; // esi
  int v4; // edx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // eax
  int v9; // ecx

  v1 = *(_DWORD *)(a1 + 4);
  if ( v1 != 8 )
  {
    if ( v1 != 7 )
      return g_ClipsPrimitiveTypeClassMap[v1];
    v2 = *(_DWORD **)(a1 + 8);
    if ( (v2[6] & 2) == 0 )
      goto LABEL_4;
LABEL_9:
    v3 = 0;
    goto LABEL_5;
  }
  v2 = Instance_FindByName(*(_DWORD *)(a1 + 8));
  if ( !v2 )
    goto LABEL_9;
LABEL_4:
  v3 = v2[11];
LABEL_5:
  if ( !v3 )
  {
    Lexer_ErrorRecover(1);
    Rules_PrintErrorID((int)aGenrcexe, v4, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnableToDeterm, v5);
    Rules_PrintDataObject((int)g_IO_LogicalNameTable_WError[0], v6);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInGenericFunct, v7);
    v8 = Rules_GetConstructNameString(g_ClipsCurrentGeneric);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], v8, (int)g_IO_LogicalNameTable_WError[0]);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__24, v9);
  }
  return v3;
}
// 4CB4D5: variable 'v4' is possibly undefined
// 4CB4E4: variable 'v5' is possibly undefined
// 4CB4F0: variable 'v6' is possibly undefined
// 4CB4FF: variable 'v7' is possibly undefined
// 4CB527: variable 'v9' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51AD7C: using guessed type int dword_51AD7C[];
// 51B3D4: using guessed type int dword_51B3D4;

//----- (004CB560) --------------------------------------------------------
int Deffunction_RegisterCodeGenerator()
{
  int result; // eax

  result = Rules_AddCodeGeneratorItem((int)aDeffunctions_1, 0, 0, (int)Deffunction_RegisterModuleItemAssigner, (int)Deffunction_WriteConstructCodeFiles, 2);
  g_DeffunctionCodeGeneratorItem = result;
  return result;
}
// 54E8DC: using guessed type int dword_54E8DC;

//----- (004CB590) --------------------------------------------------------
int  Deffunction_WriteConstructReference(int a1, int a2, int a3)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( a2 )
    return Output_WriteFormatted(
             a3,
             *(_DWORD *)(*(_DWORD *)(g_DeffunctionCodeGeneratorItem + 20) + 4),
             a1,
             (int)aSD_DD_0,
             *(_DWORD *)(*(_DWORD *)(g_DeffunctionCodeGeneratorItem + 20) + 4));
  else
    return Output_WriteFormatted(a3, 0, a1, (int)aNull_5, v4);
}
// 4CB5A0: variable 'v4' is possibly undefined
// 54E8DC: using guessed type int dword_54E8DC;

//----- (004CB5E0) --------------------------------------------------------
int  Deffunction_WriteModuleItemReference(int a1, int a2)
{
  return Output_WriteFormatted(a2, **(_DWORD **)(g_DeffunctionCodeGeneratorItem + 20), a1, (int)aMihsSD_DD_0, **(_DWORD **)(g_DeffunctionCodeGeneratorItem + 20));
}
// 54E8DC: using guessed type int dword_54E8DC;

//----- (004CB620) --------------------------------------------------------
signed int Deffunction_RegisterModuleItemAssigner()
{
  return Rules_RegisterModuleItemIdAssigner();
}
// 54E6A8: using guessed type int dword_54E6A8;

//----- (004CB630) --------------------------------------------------------
int  Deffunction_WriteConstructCodeFiles(const char *a1, const char *a2, int a3, int a4, int a5)
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
  Output_WriteFormatted(0, 1, a4, (int)aIncludeDffnxfu, 1);
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
             (char)aDeffunction_mo,
             **(const char ***)(g_DeffunctionCodeGeneratorItem + 20),
             0,
             0);
      v9 = v7;
      if ( !v7 )
      {
        Deffunction_CloseCodeFiles(0, v5, v8, a5);
        return 0;
      }
      Deffunction_WriteConstructHeader(v7, Enum, a5);
      v21 = Rules_ConstructCodeFileClose(v9, &v17, a5, &v18, 0, 0);
      v10 = Deffunction_EnumNext(0);
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
              (char)aDeffunction_8,
              *(const char **)(*(_DWORD *)(g_DeffunctionCodeGeneratorItem + 20) + 4),
              0,
              0);
      v13 = v11;
      if ( !v11 )
        break;
      Deffunction_WriteConstructBody(v11, v10, a5, v26);
      ++v19;
      v5 = Rules_ConstructCodeFileClose(v13, &v19, a5, &v20, 0, 0);
      v10 = Deffunction_EnumNext(v10);
      if ( !v10 )
        goto LABEL_6;
    }
    Deffunction_CloseCodeFiles(v21, 0, v12, a5);
    return 0;
  }
  else
  {
LABEL_7:
    Deffunction_CloseCodeFiles(v21, v5, v6, a5);
    return 1;
  }
}
// 4CB7C9: variable 'v6' is possibly undefined
// 4CB7E0: variable 'v8' is possibly undefined
// 4CB7F8: variable 'v12' is possibly undefined
// 54E8DC: using guessed type int dword_54E8DC;

//----- (004CB810) --------------------------------------------------------
int  Deffunction_CloseCodeFiles(int a1, int a2, int a3, int a4)
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

//----- (004CB870) --------------------------------------------------------
int  Deffunction_WriteConstructHeader(int a1, int a2, int a3)
{
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  char v9; // [esp+0h] [ebp-Ch]
  char v10; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(a3, a2, a1, (int)asc_50B89C, v9);
  Rules_WriteConstructModuleItemHeaderToCode(a1, v4, v5, g_Clips_DeffunctionModuleItemIndex, *(_DWORD *)(*(_DWORD *)(g_DeffunctionCodeGeneratorItem + 20) + 4));
  return Output_WriteFormatted(v7, v6, a1, (int)asc_50B8A0, v10);
}
// 4CB87B: variable 'v9' is possibly undefined
// 4CB898: variable 'v4' is possibly undefined
// 4CB898: variable 'v5' is possibly undefined
// 4CB8A3: variable 'v7' is possibly undefined
// 4CB8A3: variable 'v6' is possibly undefined
// 4CB8A3: variable 'v10' is possibly undefined
// 54E6A8: using guessed type int dword_54E6A8;
// 54E8DC: using guessed type int dword_54E8DC;

//----- (004CB8B0) --------------------------------------------------------
int  Deffunction_WriteConstructBody(int a1, int a2, int a3, int a4)
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

  Output_WriteFormatted(a3, a2, a1, (int)asc_50B89C, v15);
  v6 = *(int **)(g_DeffunctionCodeGeneratorItem + 20);
  v7 = *v6;
  Rules_WriteConstructHeaderToCode(a1, a2, v8, a4, *v6, v6[1]);
  Output_WriteFormatted(v10, v9, a1, (int)a000_0, v16);
  Rules_ExpressionToCode(a1, *(__int16 **)(a2 + 30), v11, v7);
  Output_WriteFormatted(*(_DWORD *)(a2 + 38), *(_DWORD *)(a2 + 42), a1, (int)aDDD, *(_DWORD *)(a2 + 34));
  return Output_WriteFormatted(v13, v12, a1, (int)asc_50B8A0, v17);
}
// 4CB8BD: variable 'v15' is possibly undefined
// 4CB8DD: variable 'v8' is possibly undefined
// 4CB8E8: variable 'v10' is possibly undefined
// 4CB8E8: variable 'v9' is possibly undefined
// 4CB8E8: variable 'v16' is possibly undefined
// 4CB8F5: variable 'v11' is possibly undefined
// 4CB91A: variable 'v13' is possibly undefined
// 4CB91A: variable 'v12' is possibly undefined
// 4CB91A: variable 'v17' is possibly undefined
// 54E8DC: using guessed type int dword_54E8DC;

//----- (004CB930) --------------------------------------------------------
int  Deffunction_ParseConstruct(int a1)
{
  int (*v2)(void); // edx
  int v3; // edi
  int v5; // esi
  int v6; // edx
  int v7; // ecx
  __int16 *v8; // edx
  int v9; // [esp+0h] [ebp-30h] BYREF
  int v10; // [esp+4h] [ebp-2Ch] BYREF
  int v11; // [esp+8h] [ebp-28h] BYREF
  int v12; // [esp+Ch] [ebp-24h] BYREF
  int v13; // [esp+10h] [ebp-20h] BYREF
  int v14; // [esp+14h] [ebp-1Ch]

  v13 = 0;
  Rules_SetPPBufferStatus(1);
  Rules_FlushPPBuffer();
  Rules_SetIndentDepth(3);
  IO_OutWriteToken(aDeffunction_3);
  if ( Rules_IsBloaded() == 1 )
  {
    Rules_ReportCannotLoadWithBload();
    return 1;
  }
  v3 = Rules_GetConstructNameAndComment(a1, (int)g_Rules_ParsedConstructNameComment, (int (*)(void))Deffunction_FindByName, aDeffunction_4, v2, asc_50B8D8, 1, 1, 1);
  if ( !v3 )
    return 1;
  if ( !Deffunction_ValidateNewName() )
    return 1;
  v5 = Parser_ParseProcParameters(a1, g_Rules_ParsedConstructNameComment, &v9, 0, &v10, &v11, &v13, 0);
  if ( v13 )
    return 1;
  v14 = Deffunction_AddDeffunction(v3, 0, v11, v10, 0, 1);
  if ( v14 )
  {
    AST_Append(v7, v6);
    g_ClipsParseReturnContext = 1;
    if ( !Parser_ParseProcActions((int)aDeffunction_4, a1, v5, v9, 0, 0, &v12, 0) )
    {
      AST_Free(v5);
      if ( !*(_DWORD *)(v14 + 20) )
      {
        Rules_UnlinkListNode(v14);
        Deffunction_Free(v14);
        return 1;
      }
      return 1;
    }
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken((char *)g_Clips_DeffunctionEchoToken);
    IO_OutWriteToken(asc_50B8E8);
    Deffunction_AddDeffunction(v3, v8, v11, v10, v12, 0);
    AST_Free(v5);
    return v13;
  }
  else
  {
    AST_Free(v5);
    return 1;
  }
}
// 4CB98B: variable 'v2' is possibly undefined
// 4CBA06: variable 'v7' is possibly undefined
// 4CBA06: variable 'v6' is possibly undefined
// 4CBAB5: variable 'v8' is possibly undefined
// 54E87C: using guessed type int dword_54E87C;
// 54E8E0: using guessed type _DWORD dword_54E8E0[2];
// 54E8E8: using guessed type int dword_54E8E8;

//----- (004CBAD0) --------------------------------------------------------
signed int Deffunction_ValidateNewName()
{
  _BYTE *v0; // edx
  _BYTE *v1; // edx
  int v2; // eax
  _BYTE *v3; // edx
  int v4; // esi
  int v5; // ecx
  int v6; // ecx
  int v7; // eax
  int v8; // ecx
  int Name; // eax
  int v10; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // eax
  int v16; // ecx
  int v17; // ecx
  int v18; // eax
  int v19; // ecx

  if ( Rules_FindConstructByName() )
  {
    Rules_PrintErrorID((int)aDffnxpsr, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDeffunctionsAr, v12);
    return 0;
  }
  else if ( Rules_MakeSymbol(v0) )
  {
    Rules_PrintErrorID((int)aDffnxpsr, 2, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDeffunctions_3, v13);
    return 0;
  }
  else
  {
    v2 = Defgeneric_LookupLocalOnly(v1);
    if ( v2 )
    {
      v4 = *(_DWORD *)Rules_GetConstructOwnerModule(v2);
      if ( v4 == Module_GetCurrent() )
      {
        Rules_PrintErrorID((int)aDffnxpsr, 3, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDeffunctions_4, v14);
      }
      else
      {
        Rules_PrintErrorID((int)aDffnxpsr, 5, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDefgeneric_4, v5);
        v7 = Rules_GetConstructNameString(v6);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], v7, (int)g_IO_LogicalNameTable_WError[0]);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aImportedFrom_0, v8);
        Name = Module_GetName(v4);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], Name, (int)g_IO_LogicalNameTable_WError[0]);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aConflictsWit_0, v10);
      }
      return 0;
    }
    else
    {
      v15 = Deffunction_FindByName(v3, 0);
      if ( v15 && *(_DWORD *)(v15 + 24) )
      {
        Rules_PrintErrorID((int)aDfnxpsr, 4, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDeffunction_5, v16);
        v18 = Rules_GetConstructNameString(v17);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], v18, (int)g_IO_LogicalNameTable_WError[0]);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aMayNotBeRedefi, v19);
        return 0;
      }
      else
      {
        return 1;
      }
    }
  }
}
// 4CBAE5: variable 'v0' is possibly undefined
// 4CBAF4: variable 'v1' is possibly undefined
// 4CBB32: variable 'v5' is possibly undefined
// 4CBB39: variable 'v6' is possibly undefined
// 4CBB57: variable 'v8' is possibly undefined
// 4CBB7C: variable 'v10' is possibly undefined
// 4CBBA3: variable 'v12' is possibly undefined
// 4CBBCA: variable 'v13' is possibly undefined
// 4CBBF1: variable 'v14' is possibly undefined
// 4CBBFF: variable 'v3' is possibly undefined
// 4CBC35: variable 'v16' is possibly undefined
// 4CBC3C: variable 'v17' is possibly undefined
// 4CBC5A: variable 'v19' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004CBC70) --------------------------------------------------------
int  Deffunction_AddDeffunction(int a1, __int16 *a2, int a3, int a4, int a5, int a6)
{
  int v8; // eax
  int v9; // edx
  int v10; // esi
  _DWORD *v11; // ebx
  _DWORD *v12; // ecx
  int v13; // edx
  __int16 v14; // ax
  int v16; // ecx
  __int16 *v17; // eax
  int v18; // ecx
  int v19; // eax
  int v20; // edx
  signed int v21; // ecx
  int v22; // ecx
  char *v23; // eax
  int v25; // [esp+4h] [ebp-14h]

  v8 = Deffunction_FindByName(*(_BYTE **)(a1 + 16), a3);
  v25 = v9;
  v10 = v8;
  if ( v8 )
  {
    v25 = Deffunction_GetWatchFlagField(v8);
    *(_DWORD *)(v16 + 38) = a3;
    *(_DWORD *)(v16 + 42) = a5;
    v17 = *(__int16 **)(v16 + 30);
    *(_DWORD *)(v16 + 34) = a4;
    AST_DeinstallNodeChain(v17);
    v19 = *(_DWORD *)(v18 + 30);
    *(_DWORD *)(v18 + 20) = v20;
    AST_FreePackedNodeChain(v19);
    *(_DWORD *)(v21 + 30) = 0;
    Rules_ReplaceConstructPPForm(v21, 0);
    Rules_UnlinkListNode(v22);
  }
  else
  {
    v11 = *(_DWORD **)(g_ClipsMemoryTable + 184);
    if ( v11 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 184);
      *(_DWORD *)(g_ClipsMemoryTable + 184) = *v11;
    }
    else
    {
      Mem_HeapAllocWithRetry((_DWORD *)0x2E);
    }
    Rules_InitConstructModuleRecord((int)aDeffunction_4, a1);
    ++*(_DWORD *)(a1 + 4);
    *(_DWORD *)((char *)v12 + 30) = 0;
    v12[5] = 0;
    v12[6] = 0;
    *(_DWORD *)((char *)v12 + 34) = a4;
    *(_DWORD *)((char *)v12 + 38) = a3;
    v10 = (int)v12;
    *(_DWORD *)((char *)v12 + 42) = a5;
  }
  Rules_AppendConstructToModuleList(v10);
  if ( a2 )
  {
    AST_InstallNodeChain(a2);
    *(_DWORD *)(v10 + 20) = v13;
    *(_DWORD *)(v10 + 30) = a2;
  }
  if ( v25 )
    v14 = 1;
  else
    v14 = g_Rules_WatchDeffunctions;
  Deffunction_SetWatchFlagField(v14, v10);
  if ( Mem_GetAllocFlag() || a6 )
    return v10;
  v23 = Rules_CopyPPBuffer();
  Rules_ReplaceConstructPPForm(v10, (int)v23);
  return v10;
}
// 4CBC8B: variable 'v9' is possibly undefined
// 4CBCCC: variable 'v12' is possibly undefined
// 4CBD0C: variable 'v13' is possibly undefined
// 4CBD6B: variable 'v16' is possibly undefined
// 4CBD83: variable 'v18' is possibly undefined
// 4CBD86: variable 'v20' is possibly undefined
// 4CBD92: variable 'v21' is possibly undefined
// 4CBDA0: variable 'v22' is possibly undefined
// 51AAE8: using guessed type int dword_51AAE8;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004CBDD0) --------------------------------------------------------
int  Deffunction_CallDeffunction(int a1, _DWORD *a2, _DWORD *a3, double a4)
{
  int result; // eax
  int v8; // eax
  int v9; // ebx
  int v10; // eax
  int v11; // ecx
  int v12; // edx
  int v13; // [esp+4h] [ebp-18h]
  int v14; // [esp+8h] [ebp-14h]

  a3[1] = 2;
  result = g_ClipsFalseSymbol;
  a3[2] = g_ClipsFalseSymbol;
  g_ClipsEvaluationError = 0;
  if ( !g_ClipsHaltExecution )
  {
    v14 = Rules_GetReentryGuardFlag();
    Rules_SetReentryGuardFlag(1);
    v8 = g_CurrentDeffunction;
    g_CurrentDeffunction = a1;
    ++g_ClipsCurrentEvaluationDepth;
    v13 = v8;
    ++*(_DWORD *)(a1 + 24);
    v9 = Rules_GetConstructNameString(a1);
    v10 = AST_CountListNodes((int)a2);
    ProcParam_PushEvaluatedArgumentFrame(a2, v10, v11, v9, a4, (int (*)(void))Deffunction_PrintErrorContext);
    if ( g_ClipsEvaluationError )
    {
      --*(_DWORD *)(a1 + 24);
      g_CurrentDeffunction = v13;
      --g_ClipsCurrentEvaluationDepth;
      Rules_RunPeriodicCleanup(0, 1);
      return Rules_SetReentryGuardFlag(v14);
    }
    else
    {
      if ( *(_WORD *)(a1 + 28) )
        Deffunction_PrintCallTrace((int)asc_50BA48);
      Rules_ExecuteRuleActions(
        **(_DWORD **)(a1 + 8),
        *(__int16 **)(a1 + 30),
        a3,
        *(_DWORD *)(a1 + 42),
        a4,
        (void (*)(void))Deffunction_PrintErrorContext);
      if ( *(_WORD *)(a1 + 28) )
        Deffunction_PrintCallTrace((int)asc_50BA4C);
      LODWORD(g_ClipsHaltExecutionFlag) = 0;
      --*(_DWORD *)(a1 + 24);
      ProcParam_PopFrame();
      g_CurrentDeffunction = v13;
      --g_ClipsCurrentEvaluationDepth;
      Rules_PropagateReturnValueDepth((int)a3);
      Rules_RunPeriodicCleanup(0, v12);
      return Rules_SetReentryGuardFlag(v14);
    }
  }
  return result;
}
// 4CBE5D: variable 'v11' is possibly undefined
// 4CBEE0: variable 'v12' is possibly undefined
// 51A964: using guessed type int dword_51A964;
// 51A968: using guessed type int dword_51A968;
// 51A96C: using guessed type int dword_51A96C;
// 51ACC0: using guessed type __int64 qword_51ACC0;
// 51B3E8: using guessed type int dword_51B3E8;
// 54DD70: using guessed type int dword_54DD70;

//----- (004CBF30) --------------------------------------------------------
signed int __thiscall Deffunction_PrintErrorContext(void *this)
{
  int v1; // eax
  int v2; // ecx

  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDeffunction_9, (int)this);
  v1 = Rules_GetConstructNameString(g_CurrentDeffunction);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v1, (int)g_IO_LogicalNameTable_WError[0]);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__33, v2);
}
// 4CBF64: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51B3E8: using guessed type int dword_51B3E8;

//----- (004CBF70) --------------------------------------------------------
signed int  Deffunction_PrintCallTrace(int a1)
{
  int v1; // ecx
  int v2; // eax
  int v3; // ecx
  _DWORD *v4; // edx
  int v5; // ecx
  int v6; // ecx
  int Name; // eax
  int v9; // ecx

  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)aDfn, a1);
  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], v1, v1);
  v2 = Module_GetCurrent();
  if ( v2 != *v4 )
  {
    Name = Module_GetName(**(_DWORD **)(g_CurrentDeffunction + 8));
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], Name, (int)g_IO_LogicalNameTable_WTrace[0]);
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_50BA6C, v9);
  }
  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], *(_DWORD *)(*(_DWORD *)g_CurrentDeffunction + 16), v3);
  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)aEd_2, v5);
  Rules_PrintLongInteger(v6, g_ClipsCurrentEvaluationDepth);
  return ProcParam_PrintArguments((int)g_IO_LogicalNameTable_WTrace[0]);
}
// 4CBF8A: variable 'v1' is possibly undefined
// 4CBF9C: variable 'v4' is possibly undefined
// 4CC008: variable 'v9' is possibly undefined
// 4CBFAF: variable 'v3' is possibly undefined
// 4CBFBE: variable 'v5' is possibly undefined
// 4CBFCE: variable 'v6' is possibly undefined
// 51A618: using guessed type char *off_51A618[4];
// 51A96C: using guessed type int dword_51A96C;
// 51B3E8: using guessed type int dword_51B3E8;

//----- (004CC010) --------------------------------------------------------
int Defglobal_RegisterConstructCommands()
{
  int v0; // ecx

  Rules_AddSaveFunction((int)aDefglobal_0, (int)Defglobal_SaveDefglobals, 40);
  Rules_AddResetFunction((int)aDefglobal_0, (int)Defglobal_ResetAllDefglobals, 50);
  Rules_RegisterHostFunction(aGetDefglobalLi, 109, v0, (int)Defglobal_GetDefglobalListCommand, (int)a01w_7);
  Rules_RegisterHostFunction(aUndefglobal, 118, (int)aUndefglobalcom, (int)Defglobal_UndefglobalCommand, (int)a11w_11);
  Rules_RegisterHostFunction(aDefglobalModul, 119, (int)aDefglobalmodul, (int)Defglobal_DefglobalModuleCommand, (int)a11w_11);
  Rules_RegisterHostFunction(aListDefglobals, 118, (int)aListdefglobals, (int)Defglobal_ListDefglobalsCommand, (int)a01w_7);
  Rules_RegisterHostFunction(aPpdefglobal, 118, (int)aPpdefglobalcom, (int)Defglobal_PpdefglobalCommand, (int)a11w_11);
  Rules_AddWatchItem((int)aGlobals, 0, 0, (int)&g_Rules_WatchGlobals, (int)Defglobal_SetWatchAll, (int)Defglobal_GetWatchAll);
  Rules_RegisterDefglobalBinaryItem();
  return Defglobal_RegisterCodeGeneratorItem();
}
// 4CC054: variable 'v0' is possibly undefined
// 51B3EC: using guessed type int dword_51B3EC;

//----- (004CC100) --------------------------------------------------------
signed int Defglobal_ResetAllDefglobals()
{
  signed int result; // eax

  result = Defglobal_GetResetGlobalsFlag();
  if ( result )
    return sub_4A9430_Impl((int (*)(int, intptr_t))Defglobal_ResetSingleDefglobal, g_ClipsDefglobalModuleItemId, 0, 1);
  return result;
}
// 54E6B0: using guessed type int dword_54E6B0;

//----- (004CC130) --------------------------------------------------------
int  Defglobal_ResetSingleDefglobal(int a1, int a2, double a3)
{
  _DWORD v5[6]; // [esp+0h] [ebp-18h] BYREF

  (void)a2;
  if ( Parser_ParseForm((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(a1 + 52), v5, a1, a3) )
  {
    v5[1] = 2;
    v5[2] = g_ClipsFalseSymbol;
  }
  return Defglobal_SetValue(a1, v5, 0, a3);
}
// 54DD70: using guessed type int dword_54DD70;

//----- (004CC170) --------------------------------------------------------
int  Defglobal_SaveDefglobals(signed int a1)
{
  return Rules_SaveConstruct(a1, g_ClipsDefglobalConstructType);
}
// 54E6B4: using guessed type int dword_54E6B4;

//----- (004CC180) --------------------------------------------------------
int __thiscall Defglobal_UndefglobalCommand(void *this)
{
  return Rules_UndefconstructCommand((int)this, g_ClipsDefglobalConstructType);
}
// 54E6B4: using guessed type int dword_54E6B4;

//----- (004CC1A0) --------------------------------------------------------
int  Defglobal_DeleteConstructOrAll(int a1, int a2)
{
  return Rules_DeleteConstructOrAll(a1, g_ClipsDefglobalConstructType, a2);
}
// 54E6B4: using guessed type int dword_54E6B4;

//----- (004CC1B0) --------------------------------------------------------
_DWORD * Defglobal_GetDefglobalListCommand(int a1, double a2)
{
  return Rules_GetConstructListCommand(a1, g_ClipsDefglobalConstructType, a2);
}
// 54E6B4: using guessed type int dword_54E6B4;

//----- (004CC1F0) --------------------------------------------------------
int __thiscall Defglobal_DefglobalModuleCommand(void *this)
{
  return Rules_GetConstructModuleCommand((int)this, (const char **)g_ClipsDefglobalConstructType);
}
// 54E6B4: using guessed type int dword_54E6B4;

//----- (004CC210) --------------------------------------------------------
int __thiscall Defglobal_PpdefglobalCommand(void *this)
{
  return Rules_PPConstructCommand((int)this, (const char **)g_ClipsDefglobalConstructType);
}
// 54E6B4: using guessed type int dword_54E6B4;

//----- (004CC240) --------------------------------------------------------
int  Defglobal_ListDefglobalsCommand(int a1, double a2)
{
  return Rules_ListConstructsCommand(g_ClipsDefglobalConstructType, a1, a2);
}
// 54E6B4: using guessed type int dword_54E6B4;

//----- (004CC280) --------------------------------------------------------
int  Defglobal_GetWatchFlagField(int a1)
{
  return *(_DWORD *)(a1 + 20) & 1;
}

//----- (004CC290) --------------------------------------------------------
int  Defglobal_SetWatchFlagField(char a1, int a2)
{
  int result; // eax

  *(_BYTE *)(a2 + 20) &= ~1u;
  result = a1 & 1;
  *(_DWORD *)(a2 + 20) |= result;
  return result;
}

//----- (004CC2A0) --------------------------------------------------------
signed int  Defglobal_SetWatchAll(int a1, int a2, double a3)
{
  return Rules_ApplyWatchFlagCommand(g_ClipsDefglobalConstructType, a1, (int)Defglobal_GetWatchFlagField, a2, a3, (void (*)(void))Defglobal_SetWatchFlagField);
}
// 4CC280: using guessed type int sub_4CC280();
// 4CC290: using guessed type int sub_4CC290();
// 54E6B4: using guessed type int dword_54E6B4;

//----- (004CC2C0) --------------------------------------------------------
signed int  Defglobal_GetWatchAll(int a1, int a2, double a3)
{
  return Rules_ListWatchFlagStatus(g_ClipsDefglobalConstructType, a1, (int)Defglobal_GetWatchFlagField, a2, a3, (void (*)(void))Defglobal_SetWatchFlagField);
}
// 4CC280: using guessed type int sub_4CC280();
// 4CC290: using guessed type int sub_4CC290();
// 54E6B4: using guessed type int dword_54E6B4;

//----- (004CC2E0) --------------------------------------------------------
signed int Defglobal_RegisterResetGlobalsCommands()
{
  Rules_RegisterHostFunction(aSetResetGlobal, 98, (int)aSetresetglobal, (int)Defglobal_SetResetGlobalsCommand, (int)a11_5);
  Rules_RegisterHostFunction(aGetResetGlobal, 98, (int)aGetresetglobal, (int)Defglobal_GetResetGlobalsCommand, (int)a00_11);
  return Rules_RegisterHostFunction(aShowDefglobals, 118, (int)aShowdefglobals, (int)Defglobal_ShowDefglobalsCommand, (int)a01w_8);
}

//----- (004CC350) --------------------------------------------------------
int  Defglobal_SetResetGlobalsCommand(int a1, double a2)
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
  g_DefglobalResetGlobalsFlag = v8 != __PAIR64__(g_ClipsFalseSymbol, 2);
  return v5;
}
// 4CC36E: variable 'v4' is possibly undefined
// 51B3F0: using guessed type int dword_51B3F0;
// 54DD70: using guessed type int dword_54DD70;

//----- (004CC3E0) --------------------------------------------------------
int Defglobal_GetResetGlobalsCommand()
{
  int v0; // ecx

  Lexer_TokenExpect(0);
  return v0;
}
// 4CC3FA: variable 'v0' is possibly undefined
// 51B3F0: using guessed type int dword_51B3F0;

//----- (004CC400) --------------------------------------------------------
int Defglobal_GetResetGlobalsFlag()
{
  return g_DefglobalResetGlobalsFlag;
}
// 51B3F0: using guessed type int dword_51B3F0;

//----- (004CC410) --------------------------------------------------------
void  Defglobal_ShowDefglobalsCommand(int a1, double a2, int a3)
{
  int v3; // eax
  int v4; // ecx
  int v5; // eax
  int v6; // ecx
  int *v7; // edx
  _DWORD v8[4]; // [esp+0h] [ebp-10h] BYREF

  v8[2] = a1;
  v8[1] = a3;
  v3 = Lexer_TokenExpect(1);
  if ( v3 != -1 )
  {
    if ( v3 == 1 )
    {
      v7 = Rules_GetModuleNameArg(1, v4, v8, a2);
      if ( !v8[0] )
        Defglobal_ShowDefglobalsForModules(0, (int)v7);
    }
    else
    {
      v5 = Module_GetCurrent();
      Defglobal_ShowDefglobalsForModules(v6, v5);
    }
  }
}
// 4CC440: variable 'v6' is possibly undefined
// 4CC455: variable 'v4' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (004CC480) --------------------------------------------------------
void __fastcall Defglobal_ShowDefglobalsForModules(int a1, int a2)
{
  int Enum; // edi
  int v3; // esi
  int Name; // eax
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ebx
  int v9; // ecx

  Enum = a2;
  v3 = 0;
  if ( !a2 )
  {
    v3 = 1;
    Enum = Module_NextEnum(0);
  }
  while ( Enum )
  {
    if ( v3 )
    {
      Name = Module_GetName(Enum);
      Output_Write(v5, Name, v5);
      Output_Write(v6, (int)asc_50BBE4, v6);
    }
    v8 = *(_DWORD *)(Module_GetItem(Enum, g_ClipsDefglobalModuleItemId) + 4);
    if ( v8 )
    {
      while ( g_ClipsHaltExecution != 1 )
      {
        if ( v3 )
          Output_Write(v7, (int)asc_50BBE8, v7);
        Defglobal_PrintDefglobalValue(v7, v8);
        Output_Write(v9, (int)asc_50BBEC, v9);
        v8 = *(_DWORD *)(v8 + 16);
        if ( !v8 )
          goto LABEL_11;
      }
      return;
    }
LABEL_11:
    if ( !v3 )
      return;
    Enum = Module_NextEnum(Enum);
  }
}
// 4CC4A9: variable 'v5' is possibly undefined
// 4CC4B5: variable 'v6' is possibly undefined
// 4CC4E2: variable 'v7' is possibly undefined
// 4CC4F7: variable 'v9' is possibly undefined
// 51A968: using guessed type int dword_51A968;
// 54E6B0: using guessed type int dword_54E6B0;

//----- (004CC530) --------------------------------------------------------
signed int  Defglobal_PrintDefglobalValue(int a1, int a2)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx

  Output_Write(a1, (int)aDefglobalVariablePrefix, a1);
  Output_Write(v3, *(_DWORD *)(*(_DWORD *)a2 + 16), v3);
  Output_Write(v4, (int)asc_50BBF4, v4);
  return Rules_PrintDataObject(v5, a2 + 28);
}
// 4CC547: variable 'v3' is possibly undefined
// 4CC553: variable 'v4' is possibly undefined
// 4CC55D: variable 'v5' is possibly undefined

//----- (004CC570) --------------------------------------------------------
int  Defglobal_ParseDefglobalConstruct(int a1, double a2)
{
  int v4; // ebx
  int v5; // eax
  char *Name; // eax
  int v7; // eax
  char *v8; // eax
  int v10; // ecx
  int v11; // edx
  int v12; // [esp+0h] [ebp-1Ch] BYREF
  int v13; // [esp+4h] [ebp-18h]
  char *v14; // [esp+8h] [ebp-14h]
  _DWORD v15[4]; // [esp+Ch] [ebp-10h] BYREF

  v4 = 1;
  v15[0] = 0;
  Rules_SetPPBufferStatus(1);
  Rules_FlushPPBuffer();
  Rules_SetIndentDepth(3);
  IO_OutWriteToken(aDefglobal_5);
  if ( Rules_IsBloaded() == 1 )
  {
    Rules_ReportCannotLoadWithBload();
    return 1;
  }
  Parser_NextToken(a1, (int)&v12);
  if ( v12 == 2 )
  {
    v4 = 0;
    if ( Rules_FindModuleSeparator(*(_BYTE **)(v13 + 16)) )
    {
      Parser_ReportSyntaxError();
      return 1;
    }
    if ( !Module_FindByName(*(_BYTE **)(v13 + 16)) )
    {
      Rules_ReportCantFindItem(v10, *(_DWORD *)(v13 + 16));
      return 1;
    }
    IO_OutWriteToken(asc_50BC20);
    Module_SetCurrent(v11);
  }
  else
  {
    IO_OutNewline();
    v5 = Module_GetCurrent();
    Name = (char *)Module_GetName(v5);
    IO_OutWriteToken(Name);
    IO_OutWriteToken(asc_50BC20);
    IO_OutWriteToken(v14);
  }
  while ( Lexer_ParseDefglobal(a1, v15, &v12, v4, a2) )
  {
    Rules_FlushPPBuffer();
    IO_OutWriteToken(aDefglobal_5);
    v7 = Module_GetCurrent();
    v8 = (char *)Module_GetName(v7);
    IO_OutWriteToken(v8);
    v4 = 0;
    IO_OutWriteToken(asc_50BC20);
  }
  return v15[0];
}
// 4CC671: variable 'v11' is possibly undefined
// 4CC69D: variable 'v10' is possibly undefined

//----- (004CC6C0) --------------------------------------------------------
int  Lexer_ParseDefglobal(int a1, _DWORD *a2, _DWORD *a3, int a4, double a5)
{
  int v7; // ebp
  int v8; // ecx
  char *v9; // edx
  int v10; // ecx
  int v11; // ecx
  char *v12; // edx
  _BYTE *v13; // ebx
  int v14; // eax
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int result; // eax
  __int16 *v19; // ebx
  _DWORD *v20; // edx
  int v21; // ecx
  int v22; // edx

  if ( !a4 )
    Parser_NextToken(a1, (int)a3);
  if ( *a3 == 101 )
    return 0;
  if ( *a3 != 13 )
    goto LABEL_16;
  v7 = a3[1];
  IO_OutWriteToken(asc_50BC20);
  if ( Rules_GetWatchItemState((int)aCompilations) == 1 && Rules_GetLoadInProgress() )
  {
    if ( Defglobal_FindNextChanged() )
      v9 = aRedefiningDefg;
    else
      v9 = aDefiningDefglo;
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)v9, v8);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], *(_DWORD *)(v7 + 16), v10);
    v12 = asc_50BC64;
    goto LABEL_10;
  }
  if ( Rules_GetLoadInProgress() )
  {
    v12 = asc_50BC68;
LABEL_10:
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)v12, v11);
  }
  v13 = *(_BYTE **)(v7 + 16);
  v14 = Module_GetCurrent();
  if ( Rules_FindImportExportConflict(aDefglobal_2, v14, v13) )
  {
    Lexer_WarnImpliedTemplate((int)aDefglobal_2, *(_DWORD *)(v7 + 16), 0);
    *a2 = 1;
    return 0;
  }
  Parser_NextToken(a1, v15);
  if ( strcmp_(v16, asc_50BC6C) )
  {
LABEL_16:
    Parser_ReportSyntaxError();
    *a2 = 1;
    return 0;
  }
  IO_OutWriteToken(asc_50BC20);
  result = Parser_ParseSingleExpression(a1, 0, v17);
  v19 = (__int16 *)result;
  if ( result )
  {
    Lexer_ErrorRecover(0);
    if ( Parser_ParseForm(v19, v20, v21, a5) )
    {
      AST_Free((int)v19);
      *a2 = 1;
      return 0;
    }
    else
    {
      IO_OutWriteToken(asc_50BC70);
      Defglobal_AddDefglobal(v7, v22, v19);
      return 1;
    }
  }
  else
  {
    *a2 = 1;
  }
  return result;
}
// 4CC6E0: simplified comparisons for 'edx.4': ==F || !=D became !=D
// 4CC6D2: variable 'a3' is possibly undefined
// 4CC735: variable 'v8' is possibly undefined
// 4CC742: variable 'v10' is possibly undefined
// 4CC751: variable 'v11' is possibly undefined
// 4CC776: variable 'v15' is possibly undefined
// 4CC783: variable 'v16' is possibly undefined
// 4CC79A: variable 'v17' is possibly undefined
// 4CC81D: variable 'v20' is possibly undefined
// 4CC81D: variable 'v21' is possibly undefined
// 4CC84A: variable 'v22' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A61C: using guessed type char *off_51A61C[3];

//----- (004CC860) --------------------------------------------------------
char * Defglobal_AddDefglobal(int a1, int a2, __int16 *a3)
{
  int *v5; // eax
  int *v6; // ebx
  int v7; // ebp
  _DWORD *v8; // ebx
  signed int v9; // eax
  _DWORD *v10; // ecx
  int v11; // ecx
  int v12; // eax
  int v13; // edx
  int v14; // ecx
  __int16 *v15; // eax
  int v16; // ecx
  _BYTE *v17; // edx
  _DWORD *v18; // ecx
  char v19; // al
  char *result; // eax
  int v21; // ecx
  int v22; // eax
  int v23; // eax
  int v24; // ecx
  int v25; // [esp+0h] [ebp-14h]

  v5 = Defglobal_FindNextChanged();
  v6 = v5;
  v7 = 0;
  v25 = 0;
  if ( v5 )
  {
    Rules_FreeConstructHeaderString(v5, (int)v5);
    v25 = v6[5] & 1;
  }
  else
  {
    v8 = *(_DWORD **)(g_ClipsMemoryTable + 224);
    v7 = 1;
    if ( v8 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 224);
      *(_DWORD *)(g_ClipsMemoryTable + 224) = *v8;
      v9 = g_ClipsMemFreeListTemp;
    }
    else
    {
      v9 = Mem_HeapAllocWithRetry((_DWORD *)0x38);
    }
    v10 = (_DWORD *)v9;
  }
  if ( !v7 )
  {
    Rules_ValueDeinstall((int)(v10 + 7), (int)v10);
    if ( *(_DWORD *)(v11 + 32) == 4 )
      Rules_ReturnMultifieldToPool(*(_DWORD **)(v11 + 36));
    AST_RemoveHashedNodeChain(*(__int16 **)(v11 + 52), v11);
  }
  v12 = *(_DWORD *)(a2 + 4);
  v10[8] = v12;
  if ( v12 == 4 )
    Rules_AssignMultifieldRangeCopy(v10 + 7, a2);
  else
    v10[9] = *(_DWORD *)(a2 + 8);
  Rules_ValueInstall((int)(v10 + 7), (int)v10);
  v15 = AST_AddHashedNodeChain(a3, v13, v14);
  *(_DWORD *)(v16 + 52) = v15;
  AST_Free((int)a3);
  g_Defglobal_ChangedFlag = 1;
  if ( v25 )
    v19 = 1;
  else
    v19 = g_Rules_WatchGlobals;
  *v17 &= ~1u;
  *(_DWORD *)v17 |= v19 & 1;
  *v18 = a1;
  ++*(_DWORD *)(a1 + 4);
  IO_OutWriteToken(asc_50BC64);
  result = (char *)Mem_GetAllocFlag();
  if ( result != (char *)1 )
  {
    result = Rules_CopyPPBuffer();
    *(_DWORD *)(v21 + 4) = result;
    *(_BYTE *)(v21 + 20) |= 2u;
    if ( !v7 )
      return result;
    goto LABEL_21;
  }
  *(_DWORD *)(v21 + 4) = 0;
  *(_BYTE *)(v21 + 20) |= 2u;
  if ( v7 )
  {
LABEL_21:
    *(_DWORD *)(v21 + 24) = 0;
    v22 = Module_FindItemByName((int)aDefglobal_2);
    v23 = Module_GetItem(0, *(_DWORD *)(v22 + 4));
    *(_DWORD *)(v24 + 8) = v23;
    return (char *)Rules_AppendConstructToModuleList(v24);
  }
  return result;
}
// 4CC8AA: variable 'v10' is possibly undefined
// 4CC8B2: variable 'v11' is possibly undefined
// 4CC8C8: variable 'a2' is possibly undefined
// 4CC8E7: variable 'v13' is possibly undefined
// 4CC8E7: variable 'v14' is possibly undefined
// 4CC8EC: variable 'v16' is possibly undefined
// 4CC911: variable 'v17' is possibly undefined
// 4CC919: variable 'v18' is possibly undefined
// 4CC936: variable 'v21' is possibly undefined
// 4CC9BF: variable 'v24' is possibly undefined
// 51AB1C: using guessed type int dword_51AB1C;
// 51B3EC: using guessed type int dword_51B3EC;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004CC9E0) --------------------------------------------------------
signed int  Defglobal_ResolveGlobalVariableReference(int a1, int a2)
{
  int v4; // eax
  _DWORD v6[5]; // [esp+0h] [ebp-14h] BYREF

  v6[3] = a2;
  v4 = Rules_FindImportExportConstruct(aDefglobal_2, v6, *(_BYTE **)(*(_DWORD *)(a1 + 2) + 16), 1, 0);
  if ( v4 )
  {
    if ( v6[0] > 1 )
    {
      Rules_ReportAmbiguousReferenceError((int)aDefglobal_2, *(_DWORD *)(*(_DWORD *)(a1 + 2) + 16));
      return 0;
    }
    else
    {
      *(_WORD *)a1 = 60;
      *(_DWORD *)(a1 + 2) = v4;
      return 1;
    }
  }
  else
  {
    Defglobal_PrintUndefinedVariableError();
    return 0;
  }
}

//----- (004CCA50) --------------------------------------------------------
signed int Defglobal_PrintUndefinedVariableError()
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)aGloblpsr, 1, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aGlobalVariable, v0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v1, v1);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aWasReferencedB, v2);
}
// 4CCA70: variable 'v0' is possibly undefined
// 4CCA7C: variable 'v1' is possibly undefined
// 4CCA8B: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004CCAA0) --------------------------------------------------------
int Defglobal_RegisterCodeGeneratorItem()
{
  int result; // eax

  result = Rules_AddCodeGeneratorItem((int)aDefglobal_3, 0, (int)Defglobals_ResetCallback, (int)Defglobal_AssignModuleItemIds, (int)Defglobal_WriteConstructsToCCode, 2);
  g_ClipsDefglobalCodeGenItem = result;
  return result;
}
// 4CCAE0: using guessed type int sub_4CCAE0();
// 54E8EC: using guessed type int dword_54E8EC;

//----- (004CCAD0) --------------------------------------------------------
signed int Defglobal_AssignModuleItemIds()
{
  return Rules_RegisterModuleItemIdAssigner();
}
// 54E6B0: using guessed type int dword_54E6B0;

//----- (004CCAE0) --------------------------------------------------------
int Defglobals_ResetCallback(int a1)
{
  return ((int (__cdecl *)(int, const char *))Output_WriteFormatted)(a1, "   ResetDefglobals();\n");
}

//----- (004CCAF0) --------------------------------------------------------
int  Defglobal_WriteConstructsToCCode(const char *a1, const char *a2, int a3, int a4, int a5)
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
  int v15; // [esp+0h] [ebp-3Ch] BYREF
  int v16; // [esp+4h] [ebp-38h] BYREF
  int v17; // [esp+8h] [ebp-34h] BYREF
  int v18; // [esp+Ch] [ebp-30h] BYREF
  int v19; // [esp+10h] [ebp-2Ch] BYREF
  int v20; // [esp+14h] [ebp-28h]
  int Enum; // [esp+18h] [ebp-24h]
  const char *v22; // [esp+1Ch] [ebp-20h]
  const char *v23; // [esp+20h] [ebp-1Ch]
  int v24; // [esp+24h] [ebp-18h]
  int v25; // [esp+28h] [ebp-14h]
  int v26; // [esp+2Ch] [ebp-10h]

  v22 = a1;
  v23 = a2;
  v24 = a4;
  v26 = a3;
  v25 = 0;
  v16 = 0;
  v17 = 1;
  v18 = 0;
  v19 = 1;
  v20 = 0;
  Output_WriteFormatted(0, 1, a4, (int)aIncludeGloblde, 1);
  v5 = 0;
  Enum = Module_NextEnum(0);
  if ( Enum )
  {
    while ( 1 )
    {
      Module_SetCurrent(Enum);
      v7 = Rules_ConstructCodeFileOpen(
             v20,
             v22,
             v26,
             v23,
             &v15,
             v17,
             v24,
             (char)aStructDefgloba,
             **(const char ***)(g_ClipsDefglobalCodeGenItem + 20),
             0,
             0);
      v9 = v7;
      if ( !v7 )
      {
        Defglobal_CloseConstructCodeFiles(0, v5, v8, a5);
        return 0;
      }
      Defglobal_WriteModuleHeaderToCode(v7, Enum, a5, v25);
      v20 = Rules_ConstructCodeFileClose(v9, &v16, a5, &v17, 0, 0);
      v10 = Defglobal_EnumNext(0);
      if ( v10 )
        break;
LABEL_6:
      ++v25;
      ++v16;
      Enum = Module_NextEnum(Enum);
      if ( !Enum )
        goto LABEL_7;
    }
    while ( 1 )
    {
      v11 = Rules_ConstructCodeFileOpen(
              v5,
              v22,
              v26,
              v23,
              &v15,
              v19,
              v24,
              (char)aStructDefglo_0,
              *(const char **)(*(_DWORD *)(g_ClipsDefglobalCodeGenItem + 20) + 4),
              0,
              0);
      v13 = v11;
      if ( !v11 )
        break;
      Defglobal_WriteDefglobalEntryToCode(v11, v10, a5, v26, v25);
      ++v18;
      v5 = Rules_ConstructCodeFileClose(v13, &v18, a5, &v19, 0, 0);
      v10 = Defglobal_EnumNext(v10);
      if ( !v10 )
        goto LABEL_6;
    }
    Defglobal_CloseConstructCodeFiles(v20, 0, v12, a5);
    return 0;
  }
  else
  {
LABEL_7:
    Defglobal_CloseConstructCodeFiles(v20, v5, v6, a5);
    return 1;
  }
}
// 4CCC90: variable 'v6' is possibly undefined
// 4CCCA7: variable 'v8' is possibly undefined
// 4CCCBF: variable 'v12' is possibly undefined
// 54E8EC: using guessed type int dword_54E8EC;

//----- (004CCCD0) --------------------------------------------------------
int  Defglobal_CloseConstructCodeFiles(int a1, int a2, int a3, int a4)
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

//----- (004CCD30) --------------------------------------------------------
int  Defglobal_WriteModuleHeaderToCode(int a1, int a2, int a3, int a4)
{
  int v5; // edx
  int v6; // ecx
  int v7; // edx
  int v8; // ecx
  char v10; // [esp+0h] [ebp-Ch]
  char v11; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(a3, a2, a1, (int)asc_50BD24, v10);
  Rules_WriteConstructModuleItemHeaderToCode(a1, v5, v6, g_ClipsDefglobalModuleItemId, *(_DWORD *)(*(_DWORD *)(g_ClipsDefglobalCodeGenItem + 20) + 4));
  return Output_WriteFormatted(v8, v7, a1, (int)asc_50BD28, v11);
}
// 4CCD3B: variable 'v10' is possibly undefined
// 4CCD58: variable 'v5' is possibly undefined
// 4CCD58: variable 'v6' is possibly undefined
// 4CCD63: variable 'v8' is possibly undefined
// 4CCD63: variable 'v7' is possibly undefined
// 4CCD63: variable 'v11' is possibly undefined
// 54E6B0: using guessed type int dword_54E6B0;
// 54E8EC: using guessed type int dword_54E8EC;

//----- (004CCD80) --------------------------------------------------------
int  Defglobal_WriteDefglobalEntryToCode(int a1, int a2, int a3, char a4, int a5)
{
  int v8; // edx
  int v9; // ecx
  int v10; // edx
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  int v14; // edx
  int v15; // ecx
  int v16; // edx
  int v17; // ecx
  char v19; // [esp+0h] [ebp-10h]
  char v20; // [esp+0h] [ebp-10h]
  char v21; // [esp+0h] [ebp-10h]
  char v22; // [esp+0h] [ebp-10h]

  Output_WriteFormatted(a3, a2, a1, (int)asc_50BD24, a4);
  Rules_WriteConstructHeaderToCode(a1, a2, a3, a5, **(_DWORD **)(g_ClipsDefglobalCodeGenItem + 20), *(_DWORD *)(*(_DWORD *)(g_ClipsDefglobalCodeGenItem + 20) + 4));
  Output_WriteFormatted(v9, v8, a1, (int)asc_50BD2C, v19);
  Output_WriteFormatted(v11, v10, a1, (int)a00Ld, *(_DWORD *)(a2 + 24));
  Output_WriteFormatted(v13, v12, a1, (int)aNullRvoid, v20);
  Output_WriteFormatted(a3, v14, a1, (int)asc_50BD2C, v21);
  Rules_WriteExpressionRefToCode(a1, *(__int16 **)(a2 + 52), v15, v22);
  return Output_WriteFormatted(v17, v16, a1, (int)asc_50BD28, v22);
}
// 4CCDC6: variable 'v9' is possibly undefined
// 4CCDC6: variable 'v8' is possibly undefined
// 4CCDC6: variable 'v19' is possibly undefined
// 4CCDD8: variable 'v11' is possibly undefined
// 4CCDD8: variable 'v10' is possibly undefined
// 4CCDE6: variable 'v13' is possibly undefined
// 4CCDE6: variable 'v12' is possibly undefined
// 4CCDE6: variable 'v20' is possibly undefined
// 4CCDF6: variable 'v14' is possibly undefined
// 4CCDF6: variable 'v21' is possibly undefined
// 4CCE06: variable 'v15' is possibly undefined
// 4CCE06: variable 'v22' is possibly undefined
// 4CCE11: variable 'v17' is possibly undefined
// 4CCE11: variable 'v16' is possibly undefined
// 54E8EC: using guessed type int dword_54E8EC;

//----- (004CCE30) --------------------------------------------------------
int  Defglobal_WriteModuleItemHeaderReference(int a1, int a2)
{
  return Output_WriteFormatted(a2, **(_DWORD **)(g_ClipsDefglobalCodeGenItem + 20), a1, (int)aMihsSD_DD_6, **(_DWORD **)(g_ClipsDefglobalCodeGenItem + 20));
}
// 54E8EC: using guessed type int dword_54E8EC;

//----- (004CCE70) --------------------------------------------------------
int  Defglobal_WriteDefglobalArrayReference(int a1, int a2, int a3)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( a2 )
    return Output_WriteFormatted(
             a3,
             *(_DWORD *)(*(_DWORD *)(g_ClipsDefglobalCodeGenItem + 20) + 4),
             a1,
             (int)aSD_LdLd_0,
             *(_DWORD *)(*(_DWORD *)(g_ClipsDefglobalCodeGenItem + 20) + 4));
  else
    return Output_WriteFormatted(a3, 0, a1, (int)aNull_6, v4);
}
// 4CCE80: variable 'v4' is possibly undefined
// 54E8EC: using guessed type int dword_54E8EC;

//----- (004CCEC0) --------------------------------------------------------
static int Runtime_ExprDescriptorNoop(int value)
{
  return value;
}

int MessageHandler_RegisterCommands()
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx

  g_EvalDesc_GetSelfSlotDirect[1] = (int)(uintptr_t)Runtime_ExprDescriptorNoop;
  g_EvalDesc_GetSelfSlotDirect[2] = (int)(uintptr_t)Runtime_ExprDescriptorNoop;
  g_EvalDesc_GetSelfSlotDirect[4] = (int)(uintptr_t)MessageHandler_GetSelfSlotDirect;
  g_EvalDesc_PutSelfSlotDirect[1] = (int)(uintptr_t)Runtime_ExprDescriptorNoop;
  g_EvalDesc_PutSelfSlotDirect[2] = (int)(uintptr_t)Runtime_ExprDescriptorNoop;
  g_EvalDesc_PutSelfSlotDirect[4] = (int)(uintptr_t)MessageHandler_PutSelfSlotDirect;
  Rules_RegisterEvaluationHandler((int)&g_EvalDesc_GetSelfSlotDirect, 58);
  Rules_RegisterEvaluationHandler((int)&g_EvalDesc_PutSelfSlotDirect, 59);
  g_MessageHandler_InitSymbol = (int)Str_Intern(aInit, v0);
  ++*(_DWORD *)(g_MessageHandler_InitSymbol + 4);
  g_ClipsDeleteMessageSymbol = (int)Str_Intern(aDelete_0, v1);
  ++*(_DWORD *)(g_ClipsDeleteMessageSymbol + 4);
  Rules_AddClearFunction((int)aDefclass_1, (int)MessageHandler_RegisterSystemHandlers, -100);
  g_MessageHandler_SelfSymbol = (int)Str_Intern(aSelf, v2);
  ++*(_DWORD *)(g_MessageHandler_SelfSymbol + 4);
  Rules_RegisterConstructType((int)aDefmessageHa_0, (int)aDefmessageHand, 0, (int)MessageHandler_ParseDefinition, 0, 0, 0, 0, 0, 0, 0, 0);
  Rules_RegisterHostFunction(aUndefmessageHa, 118, (int)aUndefmessageha, (int)MessageHandler_UndefineCommand, (int)a23w_0);
  Rules_RegisterHostFunction(aSend, 117, (int)aSendcommand, (int)MessageHandler_ParseAndSend, (int)a2Uuw);
  Rules_RegisterHostFunction(aPreviewSend, 118, (int)aPreviewsendcom, (int)MessageHandler_PreviewSendCommand, (int)a22w_0);
  Rules_RegisterHostFunction(aPpdefmessageHa, 118, (int)aPpdefmessageha, (int)MessageHandler_PrettyPrintCommand, (int)a23w_0);
  Rules_RegisterHostFunction(aListDefmessage, 118, (int)aListdefmessage, (int)MessageHandler_ListCommand, (int)a02w_0);
  Rules_RegisterHostFunction(aNextHandlerp, 98, (int)aNexthandlerava, (int)MessageHandler_HasNextHandler, (int)a00_12);
  Rules_SetFunctionSeqOverloadFlags(aNextHandlerp, 0);
  Rules_RegisterHostFunction(aCallNextHandle, 117, v3, (int)MessageHandler_CallNextHandler, (int)a00_12);
  Rules_SetFunctionSeqOverloadFlags(aCallNextHandle, 0);
  Rules_RegisterHostFunction(aOverrideNextHa, 117, v4, (int)MessageHandler_CallNextHandler, 0);
  Rules_SetFunctionSeqOverloadFlags(aOverrideNextHa, 0);
  Rules_RegisterHostFunction(aDynamicGet, 117, v5, (int)MessageHandler_DynamicGetSlot, (int)a11w_12);
  Rules_RegisterHostFunction(aDynamicPut, 117, (int)aDynamichandl_0, (int)MessageHandler_DynamicPutSlot, (int)a1W_2);
  Rules_RegisterHostFunction(aGet, 117, (int)aDynamichandler, (int)MessageHandler_DynamicGetSlot, (int)a11w_12);
  Rules_RegisterHostFunction(aPut, 117, (int)aDynamichandl_0, (int)MessageHandler_DynamicPutSlot, (int)a1W_2);
  Rules_AddWatchItem((int)aMessages, 0, 36, (int)&g_MessageHandler_WatchMessages, 0, 0);
  return Rules_AddWatchItem((int)aMessageHandl_0, 0, 35, (int)&g_Rules_WatchMessageHandlers, (int)MessageHandler_WatchCommand, (int)MessageHandler_ListWatchItemsCommand);
}
// 4CCEE6: variable 'v0' is possibly undefined
// 4CCEF8: variable 'v1' is possibly undefined
// 4CCF22: variable 'v2' is possibly undefined
// 4CD037: variable 'v3' is possibly undefined
// 4CD063: variable 'v4' is possibly undefined
// 4CD092: variable 'v5' is possibly undefined
// 51AD34: using guessed type int dword_51AD34;
// 51AD38: using guessed type int dword_51AD38;
// 51AD4C: using guessed type int dword_51AD4C;
// 51AD50: using guessed type int dword_51AD50;
// 51C708: using guessed type int dword_51C708;

//----- (004CD180) --------------------------------------------------------
int  MessageHandler_EnumNext(int a1, int a2)
{
  if ( !a2 )
    return *(_DWORD *)(a1 + 88) != 0;
  if ( a2 == *(_DWORD *)(a1 + 96) )
    return 0;
  return a2 + 1;
}

//----- (004CD1C0) --------------------------------------------------------
_BYTE * MessageHandler_SetWatchFlagField(char a1, int a2, int a3)
{
  _BYTE *result; // eax

  result = (_BYTE *)(*(_DWORD *)(a2 + 88) + 36 * (a3 - 1));
  *result &= ~0x10u;
  *(_DWORD *)result |= 16 * (a1 & 1);
  return result;
}

//----- (004CD270) --------------------------------------------------------
int  MessageHandler_UndefineCommand(int a1, double a2)
{
  int result; // eax
  int v3; // ecx
  int v4; // ecx
  int *v5; // edi
  int v6; // ecx
  signed int *v7; // esi
  int v8; // ecx
  char *v9; // ebx
  int v10; // ecx
  _DWORD v11[2]; // [esp-8h] [ebp-2Ch] BYREF
  signed int *v12; // [esp+0h] [ebp-24h]
  int v13; // [esp+1Ch] [ebp-8h]

  v13 = a1;
  if ( Rules_IsBloaded() )
  {
    Rules_PrintErrorID((int)aMsgcom, 3, 0);
    return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnableToDele_1, v3);
  }
  result = Lexer_ParseValueList(1, v11, 2, a2);
  if ( result )
  {
    v5 = Class_LookupByQualifiedName((_BYTE *)v12[4]);
    if ( !v5 && strcmp_(v4, asc_50BFD4) )
      return Class_ReportLookupError(v6, v12[4]);
    result = Lexer_ParseValueList(2, v11, 2, a2);
    if ( result )
    {
      v7 = v12;
      if ( Rules_RtnArgCount() != 3 )
      {
        v9 = g_MessageHandler_PrimaryAfterTypeNames[0];
        return MessageHandler_UndefineForClassOrAll(v5, v7, v8, (int)v9);
      }
      result = Lexer_ParseValueList(3, v11, 2, a2);
      if ( result )
      {
        v9 = (char *)v12[4];
        if ( strcmp_(v10, asc_50BFD4) )
          return MessageHandler_UndefineForClassOrAll(v5, v7, v8, (int)v9);
        return MessageHandler_UndefineForClassOrAll(v5, v7, v8, 0);
      }
    }
  }
  return result;
}
// 4CD2BF: variable 'v3' is possibly undefined
// 4CD2E4: variable 'v4' is possibly undefined
// 4CD324: variable 'v8' is possibly undefined
// 4CD33E: variable 'v6' is possibly undefined
// 4CD375: variable 'v10' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 51AD44: using guessed type char *off_51AD44[2];

//----- (004CD450) --------------------------------------------------------
signed int  MessageHandler_PrettyPrintCommand(double a1)
{
  signed int result; // eax
  int *v2; // edi
  int *v3; // ebp
  _DWORD *v4; // ecx
  int *v5; // esi
  signed int v6; // ebx
  _DWORD *v7; // edx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  _DWORD v15[2]; // [esp+0h] [ebp-30h] BYREF
  int v16; // [esp+8h] [ebp-28h]

  result = Lexer_ParseValueList(1, v15, 2, a1);
  v2 = 0;
  if ( result )
  {
    v3 = Rules_FindSymbolEntry(*(_BYTE **)(v16 + 16));
    result = Lexer_ParseValueList(2, v4, 2, a1);
    if ( result )
    {
      v5 = Rules_FindSymbolEntry(*(_BYTE **)(v16 + 16));
      if ( Rules_RtnArgCount() != 3 || (result = Lexer_ParseValueList(3, v15, 2, a1)) != 0 )
      {
        v6 = MessageHandler_TypeIndexFromKeyword((int)aPpdefmessageHa);
        if ( v6 == 4 )
        {
          return Lexer_ErrorRecover(1);
        }
        else
        {
          if ( v3 )
            v2 = Class_LookupByQualifiedName((_BYTE *)v3[4]);
          if ( v2 && v5 && (v7 = Class_FindMessageHandler(v2, (int)v5, v6), result = v7 == 0, v7) )
          {
            if ( v7[8] )
              return Output_WriteLongString((signed int)g_IO_LogicalName_WDisplay, (char *)v7[8]);
          }
          else
          {
            Rules_PrintErrorID((int)aMsgcom, 2, 0);
            Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnableToFind_0, v8);
            Output_Write((int)g_IO_LogicalNameTable_WError[0], v5[4], v9);
            Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_50C030, v10);
            Output_Write((int)g_IO_LogicalNameTable_WError[0], v11, v11);
            Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aForClass, v12);
            Output_Write((int)g_IO_LogicalNameTable_WError[0], v3[4], v13);
            Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInFunctionPpde, v14);
            return Lexer_ErrorRecover(1);
          }
        }
      }
    }
  }
  return result;
}
// 4CD49B: variable 'v4' is possibly undefined
// 4CD581: variable 'v8' is possibly undefined
// 4CD58E: variable 'v9' is possibly undefined
// 4CD59D: variable 'v10' is possibly undefined
// 4CD5A9: variable 'v11' is possibly undefined
// 4CD5B8: variable 'v12' is possibly undefined
// 4CD5C5: variable 'v13' is possibly undefined
// 4CD5D4: variable 'v14' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A624: using guessed type char *off_51A624;
// 51AD44: using guessed type char *off_51AD44[2];

//----- (004CD5F0) --------------------------------------------------------
int * MessageHandler_ListCommand(double a1)
{
  int v1; // ecx
  int *result; // eax
  int v3[3]; // [esp+0h] [ebp-Ch] BYREF

  if ( !Rules_RtnArgCount() )
    return (int *)MessageHandler_PrintHandlerListTally((int)g_IO_LogicalName_WDisplay, 0, v1, 0);
  result = Class_ParseClassNameAndInheritFlag((int)aListDefmessage, v3, a1);
  if ( result )
    return (int *)MessageHandler_PrintHandlerListTally((int)g_IO_LogicalName_WDisplay, (int)result, (int)g_IO_LogicalName_WDisplay, v3[0]);
  return result;
}
// 4CD61D: variable 'v1' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (004CD640) --------------------------------------------------------
int * MessageHandler_PreviewSendCommand(int a1, double a2)
{
  int *result; // eax
  int v3; // ecx
  _DWORD v4[2]; // [esp-8h] [ebp-28h] BYREF
  int v5; // [esp+0h] [ebp-20h]
  int v6; // [esp+18h] [ebp-8h]

  v6 = a1;
  result = (int *)Lexer_ParseValueList(1, v4, 2, a2);
  if ( result )
  {
    if ( Class_LookupByQualifiedName(*(_BYTE **)(v5 + 16)) )
    {
      result = (int *)Lexer_ParseValueList(2, v4, 2, a2);
      if ( result )
        return MessageHandler_PreviewSendForSymbol((int)g_IO_LogicalName_WDisplay, *(_BYTE **)(v5 + 16));
    }
    else
    {
      return (int *)Class_ReportLookupError(v3, *(_DWORD *)(v5 + 16));
    }
  }
  return result;
}
// 4CD6B9: variable 'v3' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (004CD6D0) --------------------------------------------------------
int  MessageHandler_GetRecordPPForm(int a1, int a2)
{
  return *(_DWORD *)(*(_DWORD *)(a1 + 88) + 36 * (a2 - 1) + 32);
}

//----- (004CD6F0) --------------------------------------------------------
int  MessageHandler_PrintHandlerListTally(int a1, int a2, int a3, int a4)
{
  unsigned __int16 *v5; // edx
  int v6; // edi
  int v8; // ecx
  unsigned __int16 v9; // [esp+0h] [ebp-18h] BYREF
  int *v10; // [esp+2h] [ebp-16h]
  int v11[4]; // [esp+8h] [ebp-10h] BYREF

  v11[3] = a3;
  if ( a2 )
  {
    v11[0] = a2;
    if ( a4 )
    {
      v5 = (unsigned __int16 *)(a2 + 46);
    }
    else
    {
      v5 = &v9;
      v9 = 1;
      v10 = v11;
    }
    v6 = MessageHandler_CountAndPrintHandlers(a1, v5, a3, 0);
  }
  else
  {
    v6 = 0;
    v9 = 1;
    for ( v11[0] = Class_GetNextRecord(0); v11[0]; v11[0] = Class_GetNextRecord(v11[0]) )
    {
      v10 = v11;
      v6 += MessageHandler_CountAndPrintHandlers(a1, &v9, v8, 0);
    }
  }
  return Rules_PrintTally(a1, v6, (int)aMessageHandl_0, (int)aMessageHandl_5);
}
// 4CD775: variable 'v8' is possibly undefined

//----- (004CD790) --------------------------------------------------------
int * MessageHandler_PreviewSendForSymbol(int a1, _BYTE *a2)
{
  int *result; // eax
  int v4; // ecx
  int v5; // ecx

  result = Rules_FindSymbolEntry(a2);
  if ( result )
  {
    result = (int *)MessageHandler_BuildPreviewHandlerCore(v4, (int)result);
    if ( result )
    {
      MessageHandler_PrintHandlerPreview(a1, result, 0);
      return (int *)MessageHandler_FreeHandlerCore(v5);
    }
  }
  return result;
}
// 4CD7A8: variable 'v4' is possibly undefined
// 4CD7C0: variable 'v5' is possibly undefined

//----- (004CD7D0) --------------------------------------------------------
int  MessageHandler_CountAndPrintHandlers(int a1, unsigned __int16 *a2, int a3, unsigned int a4)
{
  unsigned int v6; // ecx
  int i; // esi
  int v8; // eax
  int v10; // [esp+0h] [ebp-18h]

  v10 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(a2 + 1) + 4 * a4) + 96);
  if ( a4 < (unsigned int)*a2 - 1 )
    v10 += MessageHandler_CountAndPrintHandlers(a1, (int)a2, a3, a4 + 1);
  v6 = 0;
  for ( i = 0; ; i += 36 )
  {
    v8 = *(_DWORD *)(4 * a4 + *(_DWORD *)(a2 + 1));
    if ( v6 >= *(_DWORD *)(v8 + 96) )
      break;
    MessageHandler_PrintNameTypeAndClass(a1, (_DWORD *)(i + *(_DWORD *)(v8 + 88)), 1);
  }
  return v10;
}
// 4CD811: variable 'v6' is possibly undefined

//----- (004CD850) --------------------------------------------------------
int MessageHandler_RegisterSystemHandlers()
{
  MessageHandler_AddSystemHandler(aUser_0, aInit, 0, aInitSlots_0);
  MessageHandler_AddSystemHandler(aUser_0, aDelete_0, 0, aDeleteInstan_0);
  MessageHandler_AddSystemHandler(aUser_0, aPrint, 0, aPpinstance_0);
  MessageHandler_AddSystemHandler(aUser_0, aDirectModify_2, 1, aDirectModify_1);
  MessageHandler_AddSystemHandler(aUser_0, aMessageModif_3, 1, aMessageModif_2);
  MessageHandler_AddSystemHandler(aUser_0, aDirectDuplic_2, 2, aDirectDuplic_1);
  return MessageHandler_AddSystemHandler(aUser_0, aMessageDupli_3, 2, aMessageDupli_2);
}

//----- (004CD900) --------------------------------------------------------
signed int  MessageHandler_UndefineForClassOrAll(_DWORD *a1, signed int *a2, int a3, int a4)
{
  int v6; // edx
  signed int v7; // ebp
  int v8; // eax
  int v9; // edx
  _DWORD *v10; // esi
  int v12; // [esp+0h] [ebp-14h]

  v6 = a4;
  if ( !a2 )
    a2 = Str_Intern(asc_50BFD4, a3);
  if ( v6 )
  {
    v7 = MessageHandler_TypeIndexFromKeyword((int)aUndefmessageHa);
    if ( v7 == 4 )
      return 0;
  }
  else
  {
    v7 = -1;
  }
  if ( a1 )
    return MessageHandler_RemoveByNameAndType(a1, (int)a2, 1, v7);
  v8 = Class_GetNextRecord(0);
  v12 = v9;
  v10 = (_DWORD *)v8;
  if ( v8 )
  {
    do
    {
      if ( !MessageHandler_RemoveByNameAndType(v10, (int)a2, 0, v7) )
        v12 = 0;
      v10 = (_DWORD *)Class_GetNextRecord((int)v10);
    }
    while ( v10 );
  }
  return v12;
}
// 4CD913: variable 'v6' is possibly undefined
// 4CD92A: variable 'v9' is possibly undefined

//----- (004CD9A0) --------------------------------------------------------
BOOL  MessageHandler_WatchCommand(int a1, int a2, double a3)
{
  if ( a1 )
    return MessageHandler_DispatchWatchCommand((int)aWatch_2, 0, 0, a1, a3, (void (*)(void))MessageHandler_SetWatchFlagField, a2);
  else
    return MessageHandler_DispatchWatchCommand((int)aUnwatch_1, 0, 0, 0, a3, (void (*)(void))MessageHandler_SetWatchFlagField, a2);
}
// 4CD1C0: using guessed type int sub_4CD1C0();

//----- (004CD9D0) --------------------------------------------------------
BOOL  MessageHandler_ListWatchItemsCommand(int a1, int a2, double a3)
{
  return MessageHandler_DispatchWatchCommand((int)aListWatchIte_2, a1, (void (*)(void))MessageHandler_PrintWatchStatusLine, -1, a3, 0, a2);
}

//----- (004CD9F0) --------------------------------------------------------
BOOL  MessageHandler_DispatchWatchCommand(
        int a1,
        int a2,
        void (*a3)(void),
        int a4,
        double a5,
        void (*a6)(void),
        int a7)
{
  int v7; // esi
  BOOL result; // eax
  int v10; // esi
  int Name; // eax
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ebx
  signed int v16; // eax
  __int16 *v17; // eax
  int v18; // ebx
  int v19; // ecx
  int v20; // [esp+0h] [ebp-40h] BYREF
  int v21; // [esp+4h] [ebp-3Ch]
  int v22; // [esp+8h] [ebp-38h]
  int v23; // [esp+18h] [ebp-28h]
  int *v24; // [esp+1Ch] [ebp-24h]
  int v25; // [esp+20h] [ebp-20h]
  int Enum; // [esp+24h] [ebp-1Ch]
  int v27; // [esp+28h] [ebp-18h]
  void (*v28)(void); // [esp+2Ch] [ebp-14h]
  int v29; // [esp+30h] [ebp-10h]

  v7 = a7;
  v23 = a1;
  v29 = a4;
  v28 = a3;
  v27 = 2;
  if ( a7 )
  {
    while ( 1 )
    {
      if ( !v7 )
        return 1;
      if ( Parser_ParseForm((__int16 *)v7, &v20, (int)a3, a5) )
        return 0;
      if ( v21 != 2 || (v24 = Class_LookupByQualifiedName(*(_BYTE **)(v22 + 16))) == 0 )
      {
        Parser_ReportError(v27, (int)aClassName);
        return 0;
      }
      v15 = *(_DWORD *)(v7 + 10);
      if ( v15 )
      {
        v17 = *(__int16 **)(v7 + 10);
        ++v27;
        v7 = v15;
        if ( Parser_ParseForm(v17, &v20, v14, a5) )
          return 0;
        if ( v21 != 2 )
        {
          Parser_ReportError(v27, (int)aHandlerName);
          return 0;
        }
        v18 = *(_DWORD *)(v15 + 10);
        v25 = *(_DWORD *)(v22 + 16);
        if ( v18 )
        {
          v7 = *(_DWORD *)(v7 + 10);
          ++v27;
          if ( Parser_ParseForm((__int16 *)v7, &v20, 2, a5) )
            return 0;
          if ( v19 != v21 )
          {
            Parser_ReportError(v27, (int)aHandlerType);
            return 0;
          }
          v16 = MessageHandler_TypeIndexFromKeyword(v23);
          if ( v16 == 4 )
            return 0;
        }
        else
        {
          v16 = -1;
        }
      }
      else
      {
        v16 = -1;
        v25 = 0;
      }
      if ( !MessageHandler_ForEachMatchingHandler((int)v24, v25, a2, v16, v29, 0, v28, a6) )
        break;
      v7 = *(_DWORD *)(v7 + 10);
      ++v27;
    }
    Parser_ReportError(v27, (int)aHandler_0);
    return 0;
  }
  else
  {
    Module_BeginEnum();
    Enum = Module_NextEnum(0);
    if ( Enum )
    {
      while ( 1 )
      {
        Module_SetCurrent(Enum);
        if ( !a6 )
        {
          Name = Module_GetName(Enum);
          Output_Write(a2, Name, v12);
          Output_Write(a2, (int)asc_50C164, v13);
        }
        v10 = Class_GetNextRecord(0);
        if ( v10 )
          break;
LABEL_11:
        Enum = Module_NextEnum(Enum);
        if ( !Enum )
          goto LABEL_12;
      }
      while ( 1 )
      {
        result = MessageHandler_ForEachMatchingHandler(v10, 0, a2, -1, v29, 1, v28, a6);
        if ( !result )
          break;
        v10 = Class_GetNextRecord(v10);
        if ( !v10 )
          goto LABEL_11;
      }
    }
    else
    {
LABEL_12:
      Module_EndEnum();
      return 1;
    }
  }
  return result;
}
// 4CDABB: variable 'v12' is possibly undefined
// 4CDAC7: variable 'v13' is possibly undefined
// 4CDAD2: variable 'a3' is possibly undefined
// 4CDB74: variable 'v14' is possibly undefined
// 4CDBDC: variable 'v19' is possibly undefined

//----- (004CDC40) --------------------------------------------------------
BOOL  MessageHandler_ForEachMatchingHandler(
        int a1,
        int a2,
        int a3,
        int a4,
        int a5,
        int a6,
        void (*a7)(void),
        void (*a8)(void))
{
  int v11; // ebx
  int i; // ecx

  v11 = 0;
  for ( i = MessageHandler_EnumNext(a1, 0); i; i = MessageHandler_EnumNext(a1, i) )
  {
    if ( (a4 == -1 || *(_DWORD *)(36 * (i - 1) + *(_DWORD *)(a1 + 88)) << 29 >> 30 == a4)
      && (!a2 || !strcmp_(i, *(_DWORD *)(*(_DWORD *)(36 * (i - 1) + *(_DWORD *)(a1 + 88) + 8) + 16))) )
    {
      if ( a8 )
      {
        a8();
      }
      else
      {
        if ( a6 )
          Output_Write(a3, (int)asc_50C19C, i);
        a7();
      }
      v11 = 1;
    }
  }
  return !a2 || a4 == -1 || v11;
}
// 4CDC8C: variable 'i' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004CDD40) --------------------------------------------------------
signed int  MessageHandler_PrintWatchStatusLine(int a1, int a2)
{
  int v3; // eax
  int v4; // ecx
  int v5; // ecx
  int v6; // ebx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx

  v3 = Rules_GetConstructNameString(a1);
  Output_Write(v4, v3, v4);
  Output_Write(v5, (int)asc_50C030, v5);
  v6 = 36 * (a2 - 1);
  Output_Write(v7, *(_DWORD *)(*(_DWORD *)(v6 + *(_DWORD *)(a1 + 88) + 8) + 16), v7);
  Output_Write(v8, (int)asc_50C030, v8);
  Output_Write(v9, (int)g_MessageHandlerTypeNames[*(_DWORD *)(v6 + *(_DWORD *)(a1 + 88)) << 29 >> 30], v9);
  if ( (*(_DWORD *)(v6 + *(_DWORD *)(a1 + 88)) & 0x10) != 0 )
    return Output_Write(v10, (int)aOn_4, v10);
  else
    return Output_Write(v10, (int)aOff_4, v10);
}
// 4CDD51: variable 'v4' is possibly undefined
// 4CDD5D: variable 'v5' is possibly undefined
// 4CDD81: variable 'v7' is possibly undefined
// 4CDD8D: variable 'v8' is possibly undefined
// 4CDDA7: variable 'v9' is possibly undefined
// 4CDDC3: variable 'v10' is possibly undefined
// 51AD3C: using guessed type char *off_51AD3C[4];

//----- (004CDDE0) --------------------------------------------------------
int Definstances_SetupConstruct()
{
  int v0; // ecx
  int v1; // ecx

  g_Clips_DefinstancesModuleItemIndex = Module_RegisterItem(
                   (int)aDefinstances,
                   (int)Definstances_AllocModuleData,
                   (int)Rules_DefinstancesBloadModuleReference,
                   (int)Definstances_FreeModuleData,
                   (int)Rules_WriteDefinstancesModuleReference,
                   (int)Definstances_FindByName);
  g_ClipsDefinstancesConstructType = (int)Rules_RegisterConstructType(
                        (int)aDefinstances,
                        (int)aDefinstances,
                        (int)Definstances_FindByName,
                        (int)Definstances_ParseAndCreate,
                        (int)Rules_GetConstructNameSymbol,
                        (int)Rules_GetModuleConstructListHead,
                        (int)Rules_GetConstructOwnerModule,
                        (int)Definstances_GetNextRecord,
                        (int)Rules_SetConstructNextInModule,
                        (int)Definstances_IsDeletable,
                        (int)Definstances_DeleteRecord,
                        (int)Definstances_FreeRecord);
  Rules_AddClearReadyFunction((int)aDefinstances, (int)Definstances_IsClearReady, 0);
  Rules_RegisterHostFunction(aUndefinstanc_0, 118, v0, (int)Definstances_UndefineCommand, (int)a11w_13);
  Rules_AddSaveFunction((int)aDefinstances, (int)Definstances_SaveConstruct, 0);
  Rules_AddClearFunction((int)aDefinstances, (int)Definstances_CreateDefaultRecord, -1000);
  Rules_RegisterHostFunction(aPpdefinstanc_0, 118, v1, (int)Definstances_PrettyPrintCommand, (int)a11w_13);
  Rules_RegisterHostFunction(aListDefinstanc, 118, (int)aListdefinstanc, (int)Definstances_ListCommand, (int)a01_2);
  Rules_RegisterHostFunction(aGetDefinstance, 109, (int)aGetdefinstance, (int)Definstances_GetListCommand, (int)a01_2);
  Rules_RegisterHostFunction(aDefinstancesMo, 119, (int)aGetdefinstan_0, (int)Definstances_GetModuleCommand, (int)a11w_13);
  Rules_AddResetFunction((int)aDefinstances, (int)Definstances_ResetAll, 0);
  Rules_SetupDefinstancesBsaveBload();
  return Rules_RegisterDefinstancesCodeGenerator();
}
// 4CDE78: variable 'v0' is possibly undefined
// 4CDEBB: variable 'v1' is possibly undefined
// 54E8F0: using guessed type int dword_54E8F0;
// 54E8F4: using guessed type int dword_54E8F4;

//----- (004CDF40) --------------------------------------------------------
int  Definstances_GetNextRecord(int a1)
{
  return Class_Enum(a1, g_Clips_DefinstancesModuleItemIndex);
}
// 54E8F0: using guessed type int dword_54E8F0;

//----- (004CDF50) --------------------------------------------------------
int  Definstances_FindByName(_BYTE *a1, int a2)
{
  return Rules_FindConstructByNameGeneric(a1, a2);
}
// 54E8F4: using guessed type int dword_54E8F4;

//----- (004CDF60) --------------------------------------------------------
BOOL Definstances_IsDeletable()
{
  int v0; // edx

  return !Rules_IsBloaded() && *(_DWORD *)(v0 + 20) == 0;
}
// 4CDF70: variable 'v0' is possibly undefined

//----- (004CDF80) --------------------------------------------------------
int __thiscall Definstances_UndefineCommand(void *this)
{
  return Rules_UndefconstructCommand((int)this, g_ClipsDefinstancesConstructType);
}
// 54E8F4: using guessed type int dword_54E8F4;

//----- (004CDFA0) --------------------------------------------------------
int __thiscall Definstances_GetModuleCommand(void *this)
{
  return Rules_GetConstructModuleCommand((int)this, (const char **)g_ClipsDefinstancesConstructType);
}
// 54E8F4: using guessed type int dword_54E8F4;

//----- (004CDFC0) --------------------------------------------------------
signed int Definstances_DeleteRecord()
{
  int v0; // edx
  signed int result; // eax
  int v2; // edx

  if ( Rules_IsBloaded() )
    return 0;
  if ( !v0 )
    return Definstances_RemoveAll();
  result = Definstances_IsDeletable();
  if ( result )
  {
    Rules_UnlinkListNode(v2);
    Definstances_FreeRecord(v2);
    return 1;
  }
  return result;
}
// 4CDFCE: variable 'v0' is possibly undefined
// 4CDFEA: variable 'v2' is possibly undefined

//----- (004CE000) --------------------------------------------------------
int __thiscall Definstances_PrettyPrintCommand(void *this)
{
  return Rules_PPConstructCommand((int)this, (const char **)g_ClipsDefinstancesConstructType);
}
// 54E8F4: using guessed type int dword_54E8F4;

//----- (004CE020) --------------------------------------------------------
int  Definstances_ListCommand(int a1, double a2)
{
  return Rules_ListConstructsCommand(g_ClipsDefinstancesConstructType, a1, a2);
}
// 54E8F4: using guessed type int dword_54E8F4;

//----- (004CE060) --------------------------------------------------------
_DWORD * Definstances_GetListCommand(int a1, double a2)
{
  return Rules_GetConstructListCommand(a1, g_ClipsDefinstancesConstructType, a2);
}
// 54E8F4: using guessed type int dword_54E8F4;

//----- (004CE0A0) --------------------------------------------------------
signed int  Definstances_ParseAndCreate(int a1)
{
  int v2; // edi
  int v3; // ebx
  _DWORD *v4; // edx
  _DWORD *v5; // ecx
  char *v6; // eax
  int **Symbol; // ebx
  int v8; // ecx
  int v9; // eax
  int v10; // ebp
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  char *v14; // eax
  _DWORD *v15; // eax
  int v16; // edx
  int v17; // ecx
  int v18; // edx
  int v19; // eax
  int v20; // edx
  int v21; // edx
  int v23; // ecx
  int v24; // [esp+0h] [ebp-20h] BYREF
  _DWORD *v25; // [esp+4h] [ebp-1Ch]

  Rules_SetPPBufferStatus(1);
  Rules_FlushPPBuffer();
  Rules_SetIndentDepth(3);
  v2 = 0;
  IO_OutWriteToken(aDefinstances_2);
  if ( Rules_IsBloaded() )
  {
    Rules_ReportCannotLoadWithBload();
    return 1;
  }
  v3 = Definstances_ParseHeaderAndActiveFlag(a1, &v24);
  if ( !v3 )
    return 1;
  v4 = *(_DWORD **)(g_ClipsMemoryTable + 112);
  if ( v4 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 112);
    *(_DWORD *)(g_ClipsMemoryTable + 112) = *v4;
  }
  else
  {
    Mem_HeapAllocWithRetry((_DWORD *)0x1C);
  }
  Rules_InitConstructModuleRecord((int)aDefinstances, v3);
  v5[5] = 0;
  v5[6] = 0;
  v25 = v5;
  if ( v24 )
    v6 = aActiveMakeIn_1;
  else
    v6 = aMakeInstance_2;
  Symbol = Rules_MakeSymbol(v6);
  if ( g_ParserCurrentTokenType == 100 )
  {
    while ( 1 )
    {
      AST_NewNode(103, (int)Symbol);
      v9 = Rules_ParseObjectInstanceFunctionCall(v8, a1);
      v10 = v9;
      if ( !v9 )
      {
        AST_Free(v25[6]);
        g_ClipsMemFreeListTemp = (int)v25;
        *v25 = *(_DWORD *)(g_ClipsMemoryTable + 112);
        *(_DWORD *)(g_ClipsMemoryTable + 112) = g_ClipsMemFreeListTemp;
        return 1;
      }
      if ( AST_TreeContainsSpecialTag(v9, 0) == 1 )
        break;
      if ( v2 )
        *(_DWORD *)(v2 + 10) = v11;
      else
        v25[6] = v11;
      Parser_NextToken(a1, (int)&g_ParserCurrentTokenType);
      IO_OutNewline();
      AST_Append(v13, v12);
      IO_OutWriteToken((char *)g_ClipsScanTokenPrintForm);
      v2 = v10;
      if ( g_ParserCurrentTokenType != 100 )
        goto LABEL_13;
    }
    Rules_ReportLocalVariableError();
    AST_Free(v23);
    AST_Free(v25[6]);
    g_ClipsMemFreeListTemp = (int)v25;
    *v25 = *(_DWORD *)(g_ClipsMemoryTable + 112);
    *(_DWORD *)(g_ClipsMemoryTable + 112) = g_ClipsMemFreeListTemp;
    return 1;
  }
  else
  {
LABEL_13:
    if ( g_ParserCurrentTokenType == 101 )
    {
      if ( !Mem_GetAllocFlag() )
      {
        if ( v25[6] )
          IO_OutNewline();
        IO_OutNewline();
        IO_OutWriteToken(asc_50C2E4);
        v14 = Rules_CopyPPBuffer();
        Rules_ReplaceConstructPPForm((signed int)v25, (int)v14);
      }
      v15 = AST_PackNodeChain((_DWORD *)v25[6]);
      *(_DWORD *)(v16 + 24) = v15;
      AST_Free(v17);
      v19 = Rules_GetConstructNameSymbol(v18);
      ++*(_DWORD *)(v19 + 4);
      AST_InstallNodeChain(*(__int16 **)(v20 + 24));
      Rules_AppendConstructToModuleList(v21);
      return 0;
    }
    else
    {
      AST_Free(v25[6]);
      g_ClipsMemFreeListTemp = (int)v25;
      *v25 = *(_DWORD *)(g_ClipsMemoryTable + 112);
      *(_DWORD *)(g_ClipsMemoryTable + 112) = g_ClipsMemFreeListTemp;
      Parser_ReportSyntaxError();
      return 1;
    }
  }
}
// 4CE118: variable 'v5' is possibly undefined
// 4CE159: variable 'v8' is possibly undefined
// 4CE186: variable 'v11' is possibly undefined
// 4CE19A: variable 'v13' is possibly undefined
// 4CE19A: variable 'v12' is possibly undefined
// 4CE20B: variable 'v16' is possibly undefined
// 4CE210: variable 'v17' is possibly undefined
// 4CE217: variable 'v18' is possibly undefined
// 4CE21F: variable 'v20' is possibly undefined
// 4CE229: variable 'v21' is possibly undefined
// 4CE2BF: variable 'v23' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E8FC: using guessed type int dword_54E8FC;
// 54E904: using guessed type int dword_54E904;

//----- (004CE360) --------------------------------------------------------
int  Definstances_ParseHeaderAndActiveFlag(int a1, _DWORD *a2)
{
  int result; // eax
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  int v8; // edx
  int v9; // edx
  int v10; // ecx
  int v11; // edx

  *a2 = 0;
  result = Rules_GetConstructNameAndComment(
             a1,
             (int)&g_ParserCurrentTokenType,
             (int (*)(void))Definstances_FindByName,
             aDefinstances,
             (int (*)(void))Definstances_DeleteRecord,
             aDefinstancesConstructMarker,
             1,
             0,
             1);
  v5 = result;
  if ( result )
  {
    if ( g_ParserCurrentTokenType == 2 && !strcmp_(result, aActive) )
    {
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(asc_50C2F4);
      IO_OutWriteToken((char *)g_ClipsScanTokenPrintForm);
      AST_Append(v10, v9);
      Parser_NextToken(a1, v11);
      *a2 = 1;
    }
    if ( g_ParserCurrentTokenType == 3 )
    {
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(asc_50C2F4);
      IO_OutWriteToken((char *)g_ClipsScanTokenPrintForm);
      AST_Append(v7, v6);
      Parser_NextToken(a1, v8);
    }
    return v5;
  }
  return result;
}
// 4CE3CD: variable 'v7' is possibly undefined
// 4CE3CD: variable 'v6' is possibly undefined
// 4CE3D4: variable 'v8' is possibly undefined
// 4CE3D9: variable 'v5' is possibly undefined
// 4CE421: variable 'v10' is possibly undefined
// 4CE421: variable 'v9' is possibly undefined
// 4CE428: variable 'v11' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 54E8FC: using guessed type int dword_54E8FC;
// 54E900: using guessed type int dword_54E900;
// 54E904: using guessed type int dword_54E904;

//----- (004CE440) --------------------------------------------------------
int  Definstances_FreeRecord(int a1)
{
  int v1; // eax
  int rhs; // eax
  int result; // eax

  v1 = Rules_GetConstructNameSymbol(a1);
  Rules_DecrementSymbolCount(v1, a1);
  rhs = *(_DWORD *)(a1 + 24);
  AST_DeinstallNodeChain((__int16 *)(uintptr_t)(unsigned int)rhs);
  AST_FreePackedNodeChain(rhs);
  Rules_ReplaceConstructPPForm(a1, 0);
  g_ClipsMemFreeListTemp = a1;
  *(_DWORD *)a1 = *(_DWORD *)(g_ClipsMemoryTable + 112);
  result = g_ClipsMemoryTable;
  *(_DWORD *)(g_ClipsMemoryTable + 112) = g_ClipsMemFreeListTemp;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004CE490) --------------------------------------------------------
int  Definstances_SaveConstruct(signed int a1)
{
  return Rules_SaveConstruct(a1, g_ClipsDefinstancesConstructType);
}
// 54E8F4: using guessed type int dword_54E8F4;

//----- (004CE4A0) --------------------------------------------------------
signed int Definstances_RemoveAll()
{
  int v0; // esi
  int v2; // ebx
  int v3; // ecx
  int v4; // ecx
  int v5; // eax
  int v6; // ecx

  v0 = 1;
  if ( Rules_IsBloaded() )
    return 0;
  v2 = Class_Enum(0, g_Clips_DefinstancesModuleItemIndex);
  if ( !v2 )
    return v0;
  do
  {
    while ( 1 )
    {
      v2 = Class_Enum(v2, g_Clips_DefinstancesModuleItemIndex);
      if ( !Definstances_IsDeletable() )
        break;
      Rules_UnlinkListNode(v3);
      Definstances_FreeRecord(v4);
      if ( !v2 )
        return v0;
    }
    v5 = Rules_GetConstructNameString(v3);
    Definstances_ReportCannotDelete(v5, v6);
    v0 = 0;
  }
  while ( v2 );
  return 0;
}
// 4CE4E5: variable 'v3' is possibly undefined
// 4CE4EC: variable 'v4' is possibly undefined
// 4CE503: variable 'v6' is possibly undefined
// 54E8F0: using guessed type int dword_54E8F0;

//----- (004CE520) --------------------------------------------------------
signed int  Definstances_ReportCannotDelete(int a1, int a2)
{
  return Rules_ReportCantDeleteItem(a2, a1);
}

//----- (004CE530) --------------------------------------------------------
int Definstances_CreateDefaultRecord()
{
  int free_record; // edx
  int definstances_record; // ecx
  int **make_instance_symbol; // eax
  int make_instance_node; // ebx
  int initial_object_node; // eax
  int *initial_object_class; // eax
  _DWORD *rhs_copy; // eax
  int owner_symbol; // eax

  free_record = *(_DWORD *)(g_ClipsMemoryTable + 112);
  if ( free_record )
  {
    g_ClipsMemFreeListTemp = free_record;
    *(_DWORD *)(g_ClipsMemoryTable + 112) = *(_DWORD *)free_record;
    definstances_record = g_ClipsMemFreeListTemp;
  }
  else
  {
    definstances_record = Mem_HeapAllocWithRetry((_DWORD *)0x1C);
  }
  sub_4A94D0_Impl((int)aDefinstances, definstances_record, g_Rules_InitialObjectSymbol);
  *(_DWORD *)(definstances_record + 20) = 0;
  make_instance_symbol = Rules_MakeSymbol(aMakeInstance_2);
  make_instance_node = AST_NewNode(10, (int)make_instance_symbol);
  initial_object_node = AST_NewNode(8, g_Rules_InitialObjectSymbol);
  *(_DWORD *)(make_instance_node + 6) = initial_object_node;
  initial_object_class = Class_LookupInScope(aInitialObjec_1);
  *(_DWORD *)(initial_object_node + 10) = AST_NewNode(57, (int)initial_object_class);
  rhs_copy = AST_PackNodeChain((_DWORD *)make_instance_node);
  *(_DWORD *)(definstances_record + 24) = rhs_copy;
  AST_Free(make_instance_node);
  owner_symbol = Rules_GetConstructNameSymbol(definstances_record);
  ++*(_DWORD *)(owner_symbol + 4);
  AST_InstallNodeChain((__int16 *)rhs_copy);
  return Rules_AppendConstructToModuleList(definstances_record);
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E6F4: using guessed type int dword_54E6F4;

//----- (004CE600) --------------------------------------------------------
signed int Definstances_AllocModuleData()
{
  _DWORD *v0; // edx

  v0 = *(_DWORD **)(g_ClipsMemoryTable + 48);
  if ( !v0 )
    return Mem_HeapAllocWithRetry((_DWORD *)0xC);
  g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
  *(_DWORD *)(g_ClipsMemoryTable + 48) = *v0;
  return g_ClipsMemFreeListTemp;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004CE630) --------------------------------------------------------
int  Definstances_FreeModuleData(int a1)
{
  int result; // eax
  _DWORD *freed_node; // ecx

  result = Rules_ClearModuleConstructList(a1, g_ClipsDefinstancesConstructType, a1);
  freed_node = (_DWORD *)a1;
  g_ClipsMemFreeListTemp = a1;
  *freed_node = *(_DWORD *)(g_ClipsMemoryTable + 48);
  *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E8F4: using guessed type int dword_54E8F4;

//----- (004CE670) --------------------------------------------------------
__int64 __fastcall Definstances_IsClearReady(int a1, int a2)
{
  __int64 v3; // [esp+0h] [ebp-10h]

  HIDWORD(v3) = a2;
  LODWORD(v3) = 1;
  sub_4A9430_Impl((int (*)(int, intptr_t))Definstances_CheckRecordBusy, g_Clips_DefinstancesModuleItemIndex, (intptr_t)&v3, 0);
  return v3;
}
// 54E8F0: using guessed type int dword_54E8F0;

//----- (004CE6A0) --------------------------------------------------------
int  Definstances_CheckRecordBusy(int result, _DWORD *a2)
{
  if ( *(_DWORD *)(result + 20) )
    *a2 = 0;
  return result;
}

//----- (004CE6B0) --------------------------------------------------------
signed int Definstances_ResetAll()
{
  return sub_4A9430_Impl((int (*)(int, intptr_t))Definstances_ExecuteRecordActions, g_Clips_DefinstancesModuleItemIndex, 0, 1);
}
// 54E8F0: using guessed type int dword_54E8F0;

//----- (004CE6D0) --------------------------------------------------------
int  Definstances_ExecuteRecordActions(int a1, int a2, double a3)
{
  int record; // ecx
  __int16 *expression; // ecx
  int result; // eax
  _DWORD v9[6]; // [esp+0h] [ebp-18h] BYREF

  (void)a2;
  record = a1;
  Module_BeginEnum();
  Module_SetCurrent(*(_DWORD *)(*(_DWORD *)(record + 8)));
  ++*(_DWORD *)(record + 20);
  expression = (__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(record + 24);
  if ( expression )
  {
    while ( 1 )
    {
      Parser_ParseForm(expression, v9, (int)(uintptr_t)expression, a3);
      if ( g_ClipsHaltExecution || v9[1] == 2 && v9[2] == g_ClipsFalseSymbol )
        break;
      expression = (__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)(uintptr_t)expression + 10);
      if ( !expression )
        goto LABEL_6;
    }
    result = Module_EndEnum();
    --*(_DWORD *)(record + 20);
  }
  else
  {
LABEL_6:
    --*(_DWORD *)(record + 20);
    return Module_EndEnum();
  }
  return result;
}
// 51A968: using guessed type int dword_51A968;
// 54DD70: using guessed type int dword_54DD70;

//----- (004CE740) --------------------------------------------------------
signed int __thiscall InstanceQuery_SetupFunctions(void *this)
{
  int v1; // ecx
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx

  g_InternedSym_Qds = (int)Str_Intern(aQds, (int)this);
  ++*(_DWORD *)(g_InternedSym_Qds + 4);
  Rules_RegisterHostFunction(aQueryInstance, 111, (int)aGetqueryinstan, (int)InstanceQuery_GetQueryInstance, 0);
  Rules_RegisterHostFunction(aQueryInstanceS, 117, (int)aGetqueryinst_0, (int)InstanceQuery_ResolveBoundSlotValue, 0);
  Rules_RegisterHostFunction(aAnyInstancep, 98, (int)aAnyinstances, (int)InstanceQuery_AnyInstancep, 0);
  Rules_AddFunctionParser(aAnyInstancep);
  Rules_RegisterHostFunction(aFindInstance, 109, v1, (int)InstanceQuery_FindInstance, 0);
  Rules_AddFunctionParser(aFindInstance);
  Rules_RegisterHostFunction(aFindAllInstanc, 109, v2, (int)InstanceQuery_FindAllInstances, 0);
  Rules_AddFunctionParser(aFindAllInstanc);
  Rules_RegisterHostFunction(aDoForInstance, 117, v3, (int)InstanceQuery_DoForInstance, 0);
  Rules_AddFunctionParser(aDoForInstance);
  Rules_RegisterHostFunction(aDoForAllInstan, 117, v4, (int)InstanceQuery_DoForAllInstances, 0);
  Rules_AddFunctionParser(aDoForAllInstan);
  Rules_RegisterHostFunction(aDelayedDoForAl, 117, v5, (int)InstanceQuery_DelayedDoForAllInstances, 0);
  return Rules_AddFunctionParser(aDelayedDoForAl);
}
// 4CE7CF: variable 'v1' is possibly undefined
// 4CE7F9: variable 'v2' is possibly undefined
// 4CE823: variable 'v3' is possibly undefined
// 4CE84D: variable 'v4' is possibly undefined
// 4CE877: variable 'v5' is possibly undefined
// 51B454: using guessed type int dword_51B454;

//----- (004CE890) --------------------------------------------------------
signed int *__thiscall InstanceQuery_GetQueryInstance(void *this)
{
  _DWORD *v1; // eax

  v1 = (_DWORD *)InstanceQuery_GetQueryFrameAtDepth(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 2) + 16));
  return Instance_GetQualifiedName(
           *(_DWORD *)(*v1 + 4 * *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 2) + 16)),
           (int)this);
}
// 51A960: using guessed type int dword_51A960;

//----- (004CE8D0) --------------------------------------------------------
int  InstanceQuery_ResolveBoundSlotValue(int a1, int a2, double a3)
{
  _DWORD *v4; // eax
  int v5; // edx
  int v6; // ebx
  int result; // eax
  _DWORD *v8; // ecx
  _DWORD v9[9]; // [esp-4h] [ebp-24h] BYREF

  v9[7] = a2;
  *(_DWORD *)(a1 + 4) = 2;
  *(_DWORD *)(a1 + 8) = g_ClipsFalseSymbol;
  v4 = (_DWORD *)InstanceQuery_GetQueryFrameAtDepth(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 2) + 16));
  v5 = *(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10);
  v6 = *(_DWORD *)(*v4 + 4 * *(_DWORD *)(*(_DWORD *)(v5 + 2) + 16));
  Parser_ParseForm(*(__int16 **)(v5 + 10), v9, a1, a3);
  if ( v9[1] == 2 )
  {
    result = Instance_GetSlotValueBySymbol(v6, v9[2]);
    if ( result )
    {
      v8[1] = *(_DWORD *)(result + 4) << 24 >> 26;
      v8[2] = *(_DWORD *)(result + 8);
      if ( (*(_DWORD *)(result + 4) & 0xFC) == 0x10 )
      {
        v8[3] = 0;
        result = *(_DWORD *)(*(_DWORD *)(result + 8) + 6) - 1;
        v8[4] = result;
      }
    }
    else
    {
      return Instance_ReportNoSuchSlotError((int)v8, (int)aInstanceSetQ_0);
    }
  }
  else
  {
    Parser_ReportError(1, (int)aSymbol_6);
    return Lexer_ErrorRecover(1);
  }
  return result;
}
// 4CE93A: variable 'v8' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (004CE9B0) --------------------------------------------------------
int * InstanceQuery_AnyInstancep(int a1, double a2)
{
  int *result; // eax
  _DWORD *v3; // edx
  _DWORD *v4; // eax
  int *v5; // ecx
  signed int v6; // ebx
  int *v7; // ecx
  _DWORD v8[4]; // [esp+0h] [ebp-10h] BYREF

  v8[2] = a1;
  result = InstanceQuery_ParseRestrictions(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10), (int)aAnyInstancep, v8, a2);
  if ( result )
  {
    InstanceQuery_PushQueryFrame();
    v3 = *(_DWORD **)(g_ClipsMemoryTable + 128);
    if ( v3 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 128);
      *(_DWORD *)(g_ClipsMemoryTable + 128) = *v3;
      v4 = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      v4 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x20);
    }
    g_ClipsQueryCore = (int)v4;
    *v4 = Mem_SmallBlockAlloc(4 * v8[0]);
    *(_DWORD *)(g_ClipsQueryCore + 4) = *(_DWORD *)(g_ClipsCurrentExpression + 6);
    v6 = InstanceQuery_TestClassRestriction(v5, 0, a2);
    g_InstanceQuery_AbortFlag = 0;
    Mem_SmallBlockFree(*(_DWORD **)g_ClipsQueryCore, 4 * v8[0]);
    g_ClipsMemFreeListTemp = g_ClipsQueryCore;
    *(_DWORD *)g_ClipsQueryCore = *(_DWORD *)(g_ClipsMemoryTable + 128);
    *(_DWORD *)(g_ClipsMemoryTable + 128) = g_ClipsMemFreeListTemp;
    InstanceQuery_PopQueryFrame();
    InstanceQuery_FreeRestrictionClassList(v7);
    return (int *)v6;
  }
  return result;
}
// 4CEA31: variable 'v5' is possibly undefined
// 4CEA8A: variable 'v7' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51B458: using guessed type int dword_51B458;
// 51B460: using guessed type int dword_51B460;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004CEAC0) --------------------------------------------------------
int * InstanceQuery_FindInstance(_DWORD *a1, double a2)
{
  int *v3; // ebp
  _DWORD *v4; // edx
  _DWORD *v5; // eax
  int v6; // ecx
  int v7; // ebx
  int v8; // edx
  signed int *v9; // eax
  int v10; // edx
  int v11; // ecx
  int *result; // eax
  signed int v13[5]; // [esp+0h] [ebp-14h] BYREF

  a1[1] = 4;
  a1[3] = 0;
  a1[4] = -1;
  v3 = InstanceQuery_ParseRestrictions(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10), (int)aFindInstance, v13, a2);
  if ( v3 )
  {
    InstanceQuery_PushQueryFrame();
    v4 = *(_DWORD **)(g_ClipsMemoryTable + 128);
    if ( v4 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 128);
      *(_DWORD *)(g_ClipsMemoryTable + 128) = *v4;
      v5 = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      v5 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x20);
    }
    g_ClipsQueryCore = (int)v5;
    *v5 = Mem_SmallBlockAlloc(4 * v13[0]);
    *(_DWORD *)(g_ClipsQueryCore + 4) = *(_DWORD *)(g_ClipsCurrentExpression + 6);
    if ( InstanceQuery_TestClassRestriction(v3, 0, a2) == 1 )
    {
      a1[2] = Rules_CreateEphemeralMultifield(v13[0]);
      a1[4] = v13[0] - 1;
      v6 = 1;
      if ( v13[0] >= 1 )
      {
        v7 = 4;
        v8 = 0;
        do
        {
          *(_WORD *)(v8 + a1[2] + 14) = 8;
          v9 = Instance_GetQualifiedName(*(_DWORD *)(v7 + *(_DWORD *)g_ClipsQueryCore - 4), v6);
          v7 += 4;
          *(_DWORD *)(v10 + a1[2] + 16) = v9;
          v6 = v11 + 1;
          v8 = v10 + 6;
        }
        while ( v6 <= v13[0] );
      }
    }
    else
    {
      a1[2] = Rules_CreateEphemeralMultifield(0);
    }
    g_InstanceQuery_AbortFlag = 0;
    Mem_SmallBlockFree(*(_DWORD **)g_ClipsQueryCore, 4 * v13[0]);
    g_ClipsMemFreeListTemp = g_ClipsQueryCore;
    *(_DWORD *)g_ClipsQueryCore = *(_DWORD *)(g_ClipsMemoryTable + 128);
    *(_DWORD *)(g_ClipsMemoryTable + 128) = g_ClipsMemFreeListTemp;
    InstanceQuery_PopQueryFrame();
    return InstanceQuery_FreeRestrictionClassList(v3);
  }
  else
  {
    result = Rules_CreateEphemeralMultifield(0);
    a1[2] = result;
  }
  return result;
}
// 4CEBA9: variable 'v10' is possibly undefined
// 4CEBAD: variable 'v11' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51B458: using guessed type int dword_51B458;
// 51B460: using guessed type int dword_51B460;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004CEC60) --------------------------------------------------------
int * InstanceQuery_FindAllInstances(_DWORD *a1, double a2)
{
  _DWORD *v3; // edx
  _DWORD *v4; // eax
  int v5; // ecx
  int v6; // ecx
  int v7; // esi
  int v8; // ebx
  int v9; // edx
  signed int *v10; // eax
  int v11; // edx
  int v12; // ecx
  int *result; // eax
  int v14; // [esp+0h] [ebp-18h] BYREF
  int *v15; // [esp+4h] [ebp-14h]

  a1[1] = 4;
  a1[3] = 0;
  a1[4] = -1;
  v15 = InstanceQuery_ParseRestrictions(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10), (int)aFindAllInstanc, &v14, a2);
  if ( v15 )
  {
    InstanceQuery_PushQueryFrame();
    v3 = *(_DWORD **)(g_ClipsMemoryTable + 128);
    if ( v3 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 128);
      *(_DWORD *)(g_ClipsMemoryTable + 128) = *v3;
      v4 = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      v4 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x20);
    }
    g_ClipsQueryCore = (int)v4;
    *v4 = Mem_SmallBlockAlloc(4 * v14);
    *(_DWORD *)(g_ClipsQueryCore + 4) = *(_DWORD *)(g_ClipsCurrentExpression + 6);
    *(_DWORD *)(g_ClipsQueryCore + 8) = 0;
    *(_DWORD *)(g_ClipsQueryCore + 12) = 0;
    *(_DWORD *)(g_ClipsQueryCore + 20) = v14;
    *(_DWORD *)(g_ClipsQueryCore + 24) = 0;
    InstanceQuery_ForEachClassRestriction(v15, 0, a2);
    g_InstanceQuery_AbortFlag = v5;
    a1[2] = Rules_CreateEphemeralMultifield(v14 * *(_DWORD *)(g_ClipsQueryCore + 24));
    while ( *(_DWORD *)(g_ClipsQueryCore + 12) )
    {
      v6 = 0;
      v7 = a1[4] + 2;
      if ( v14 > 0 )
      {
        v8 = 0;
        v9 = 6 * v7 - 6;
        do
        {
          *(_WORD *)(v9 + a1[2] + 14) = 8;
          v10 = Instance_GetQualifiedName(*(_DWORD *)(v8 + **(_DWORD **)(g_ClipsQueryCore + 12)), v6);
          v8 += 4;
          v6 = v12 + 1;
          ++v7;
          *(_DWORD *)(v11 + a1[2] + 16) = v10;
          v9 = v11 + 6;
        }
        while ( v6 < v14 );
      }
      a1[4] = v7 - 2;
      InstanceQuery_DequeueDelayedBinding();
    }
    Mem_SmallBlockFree(*(_DWORD **)g_ClipsQueryCore, 4 * v14);
    g_ClipsMemFreeListTemp = g_ClipsQueryCore;
    *(_DWORD *)g_ClipsQueryCore = *(_DWORD *)(g_ClipsMemoryTable + 128);
    *(_DWORD *)(g_ClipsMemoryTable + 128) = g_ClipsMemFreeListTemp;
    InstanceQuery_PopQueryFrame();
    return InstanceQuery_FreeRestrictionClassList(v15);
  }
  else
  {
    result = Rules_CreateEphemeralMultifield(0);
    a1[2] = result;
  }
  return result;
}
// 4CED36: variable 'v5' is possibly undefined
// 4CED99: variable 'v12' is possibly undefined
// 4CED97: variable 'v11' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51B458: using guessed type int dword_51B458;
// 51B460: using guessed type int dword_51B460;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004CEE40) --------------------------------------------------------
int * InstanceQuery_DoForInstance(int a1, int a2, double a3)
{
  int *result; // eax
  int *v4; // ebx
  _DWORD *v5; // edx
  _DWORD *v6; // eax
  _DWORD *v7; // ecx
  _DWORD v8[4]; // [esp+0h] [ebp-10h] BYREF

  v8[2] = a2;
  *(_DWORD *)(a1 + 4) = 2;
  *(_DWORD *)(a1 + 8) = g_ClipsFalseSymbol;
  result = InstanceQuery_ParseRestrictions(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10), (int)aDoForInstance, v8, a3);
  v4 = result;
  if ( result )
  {
    InstanceQuery_PushQueryFrame();
    v5 = *(_DWORD **)(g_ClipsMemoryTable + 128);
    if ( v5 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 128);
      *(_DWORD *)(g_ClipsMemoryTable + 128) = *v5;
      v6 = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      v6 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x20);
    }
    g_ClipsQueryCore = (int)v6;
    *v6 = Mem_SmallBlockAlloc(4 * v8[0]);
    *(_DWORD *)(g_ClipsQueryCore + 4) = *(_DWORD *)(g_ClipsCurrentExpression + 6);
    *(_DWORD *)(g_ClipsQueryCore + 8) = *(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10);
    if ( InstanceQuery_TestClassRestriction(v4, 0, a3) == 1 )
      Parser_ParseForm(*(__int16 **)(g_ClipsQueryCore + 8), v7, (int)v7, a3);
    g_InstanceQuery_AbortFlag = 0;
    HIDWORD(g_ClipsHaltExecutionFlag) = 0;
    Mem_SmallBlockFree(*(_DWORD **)g_ClipsQueryCore, 4 * v8[0]);
    g_ClipsMemFreeListTemp = g_ClipsQueryCore;
    *(_DWORD *)g_ClipsQueryCore = *(_DWORD *)(g_ClipsMemoryTable + 128);
    *(_DWORD *)(g_ClipsMemoryTable + 128) = g_ClipsMemFreeListTemp;
    InstanceQuery_PopQueryFrame();
    return InstanceQuery_FreeRestrictionClassList(v4);
  }
  return result;
}
// 4CEEF9: variable 'v7' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51ACC0: using guessed type __int64 qword_51ACC0;
// 51B458: using guessed type int dword_51B458;
// 51B460: using guessed type int dword_51B460;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD70: using guessed type int dword_54DD70;

//----- (004CEF80) --------------------------------------------------------
int * InstanceQuery_DoForAllInstances(int a1, int a2, double a3)
{
  int *result; // eax
  int *v4; // ebx
  _DWORD *v5; // edx
  _DWORD *v6; // eax
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int v10; // ecx
  _DWORD v11[4]; // [esp+0h] [ebp-10h] BYREF

  v11[2] = a2;
  *(_DWORD *)(a1 + 4) = 2;
  *(_DWORD *)(a1 + 8) = g_ClipsFalseSymbol;
  result = InstanceQuery_ParseRestrictions(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10), (int)aDoForAllInstan, v11, a3);
  v4 = result;
  if ( result )
  {
    InstanceQuery_PushQueryFrame();
    v5 = *(_DWORD **)(g_ClipsMemoryTable + 128);
    if ( v5 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 128);
      *(_DWORD *)(g_ClipsMemoryTable + 128) = *v5;
      v6 = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      v6 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x20);
    }
    g_ClipsQueryCore = (int)v6;
    *v6 = Mem_SmallBlockAlloc(4 * v11[0]);
    *(_DWORD *)(g_ClipsQueryCore + 4) = *(_DWORD *)(g_ClipsCurrentExpression + 6);
    *(_DWORD *)(g_ClipsQueryCore + 8) = *(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10);
    *(_DWORD *)(g_ClipsQueryCore + 28) = v7;
    Rules_ValueInstall(*(_DWORD *)(g_ClipsQueryCore + 28), v7);
    InstanceQuery_ForEachClassRestriction(v4, v8, a3);
    Rules_ValueDeinstall(*(_DWORD *)(g_ClipsQueryCore + 28), v9);
    Rules_PropagateReturnValueDepth(*(_DWORD *)(g_ClipsQueryCore + 28));
    g_InstanceQuery_AbortFlag = v10;
    HIDWORD(g_ClipsHaltExecutionFlag) = v10;
    Mem_SmallBlockFree(*(_DWORD **)g_ClipsQueryCore, 4 * v11[0]);
    g_ClipsMemFreeListTemp = g_ClipsQueryCore;
    *(_DWORD *)g_ClipsQueryCore = *(_DWORD *)(g_ClipsMemoryTable + 128);
    *(_DWORD *)(g_ClipsMemoryTable + 128) = g_ClipsMemFreeListTemp;
    InstanceQuery_PopQueryFrame();
    return InstanceQuery_FreeRestrictionClassList(v4);
  }
  return result;
}
// 4CF026: variable 'v7' is possibly undefined
// 4CF03A: variable 'v8' is possibly undefined
// 4CF047: variable 'v9' is possibly undefined
// 4CF063: variable 'v10' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51ACC0: using guessed type __int64 qword_51ACC0;
// 51B458: using guessed type int dword_51B458;
// 51B460: using guessed type int dword_51B460;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD70: using guessed type int dword_54DD70;

//----- (004CF0E0) --------------------------------------------------------
int * InstanceQuery_DelayedDoForAllInstances(_DWORD *a1, double a2)
{
  int *result; // eax
  int *v4; // ebp
  _DWORD *v5; // edx
  _DWORD *v6; // eax
  int v7; // ecx
  int v8; // edx
  int v9; // eax
  int v10; // ecx
  int v11[5]; // [esp+0h] [ebp-14h] BYREF

  a1[1] = 2;
  a1[2] = g_ClipsFalseSymbol;
  result = InstanceQuery_ParseRestrictions(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10), (int)aDelayedDoForAl, v11, a2);
  v4 = result;
  if ( result )
  {
    InstanceQuery_PushQueryFrame();
    v5 = *(_DWORD **)(g_ClipsMemoryTable + 128);
    if ( v5 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 128);
      *(_DWORD *)(g_ClipsMemoryTable + 128) = *v5;
      v6 = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      v6 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x20);
    }
    g_ClipsQueryCore = (int)v6;
    *v6 = Mem_SmallBlockAlloc(4 * v11[0]);
    *(_DWORD *)(g_ClipsQueryCore + 4) = *(_DWORD *)(g_ClipsCurrentExpression + 6);
    *(_DWORD *)(g_ClipsQueryCore + 8) = 0;
    *(_DWORD *)(g_ClipsQueryCore + 12) = 0;
    *(_DWORD *)(g_ClipsQueryCore + 20) = v11[0];
    *(_DWORD *)(g_ClipsQueryCore + 24) = 0;
    InstanceQuery_ForEachClassRestriction(v4, 0, a2);
    g_InstanceQuery_AbortFlag = v7;
    *(_DWORD *)(g_ClipsQueryCore + 8) = *(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10);
    while ( *(_DWORD *)(g_ClipsQueryCore + 12) )
    {
      v8 = 0;
      if ( v11[0] > 0 )
      {
        v9 = 0;
        do
        {
          *(_DWORD *)(*(_DWORD *)g_ClipsQueryCore + v9) = *(_DWORD *)(**(_DWORD **)(g_ClipsQueryCore + 12) + v9);
          ++v8;
          v9 += 4;
        }
        while ( v8 < v11[0] );
      }
      InstanceQuery_DequeueDelayedBinding();
      ++g_ClipsCurrentEvaluationDepth;
      Parser_ParseForm(*(__int16 **)(g_ClipsQueryCore + 8), a1, v10, a2);
      --g_ClipsCurrentEvaluationDepth;
      Rules_RunPeriodicCleanup(0, 1);
      if ( g_ClipsHaltExecution || g_ClipsHaltExecutionFlag )
      {
        while ( *(_DWORD *)(g_ClipsQueryCore + 12) )
          InstanceQuery_DequeueDelayedBinding();
        break;
      }
    }
    HIDWORD(g_ClipsHaltExecutionFlag) = 0;
    Mem_SmallBlockFree(*(_DWORD **)g_ClipsQueryCore, 4 * v11[0]);
    g_ClipsMemFreeListTemp = g_ClipsQueryCore;
    *(_DWORD *)g_ClipsQueryCore = *(_DWORD *)(g_ClipsMemoryTable + 128);
    *(_DWORD *)(g_ClipsMemoryTable + 128) = g_ClipsMemFreeListTemp;
    InstanceQuery_PopQueryFrame();
    return InstanceQuery_FreeRestrictionClassList(v4);
  }
  return result;
}
// 4CF1B3: variable 'v7' is possibly undefined
// 4CF222: variable 'v10' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51A968: using guessed type int dword_51A968;
// 51A96C: using guessed type int dword_51A96C;
// 51ACC0: using guessed type __int64 qword_51ACC0;
// 51B458: using guessed type int dword_51B458;
// 51B460: using guessed type int dword_51B460;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD70: using guessed type int dword_54DD70;

//----- (004CF2F0) --------------------------------------------------------
_DWORD *InstanceQuery_PushQueryFrame()
{
  _DWORD *v0; // edx
  _DWORD *result; // eax

  v0 = *(_DWORD **)(g_ClipsMemoryTable + 32);
  if ( v0 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
    *(_DWORD *)(g_ClipsMemoryTable + 32) = *v0;
    result = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)8);
  }
  *result = g_ClipsQueryCore;
  result[1] = g_ClipsInstanceQueryCoreStack;
  g_ClipsInstanceQueryCoreStack = (int)result;
  return result;
}
// 51B458: using guessed type int dword_51B458;
// 51B45C: using guessed type int dword_51B45C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004CF340) --------------------------------------------------------
int InstanceQuery_PopQueryFrame()
{
  _DWORD *v0; // eax
  int result; // eax

  v0 = (_DWORD *)g_ClipsInstanceQueryCoreStack;
  g_ClipsQueryCore = *(_DWORD *)g_ClipsInstanceQueryCoreStack;
  g_ClipsInstanceQueryCoreStack = *(_DWORD *)(g_ClipsInstanceQueryCoreStack + 4);
  g_ClipsMemFreeListTemp = (int)v0;
  *v0 = *(_DWORD *)(g_ClipsMemoryTable + 32);
  result = g_ClipsMemFreeListTemp;
  *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
  return result;
}
// 51B458: using guessed type int dword_51B458;
// 51B45C: using guessed type int dword_51B45C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004CF380) --------------------------------------------------------
int  InstanceQuery_GetQueryFrameAtDepth(signed int a1)
{
  _DWORD *i; // edx

  if ( !a1 )
    return g_ClipsQueryCore;
  for ( i = (_DWORD *)g_ClipsInstanceQueryCoreStack; a1 > 1; i = (_DWORD *)i[1] )
    --a1;
  return *i;
}
// 51B458: using guessed type int dword_51B458;
// 51B45C: using guessed type int dword_51B45C;

//----- (004CF3B0) --------------------------------------------------------
int * InstanceQuery_ParseRestrictions(int a1, int a2, _DWORD *a3, double a4)
{
  int *v6; // ebp
  int *v7; // ebx
  int v8; // ecx
  int v9; // edi
  int *v11; // eax
  _DWORD v12[7]; // [esp+0h] [ebp-30h] BYREF
  _DWORD *v13; // [esp+1Ch] [ebp-14h]

  v12[6] = a2;
  v13 = a3;
  v6 = 0;
  v7 = 0;
  v8 = 0;
  v9 = 0;
  *a3 = 0;
  if ( !a1 )
    return v6;
  while ( 1 )
  {
    if ( Parser_ParseForm((__int16 *)a1, v12, v8, a4) )
    {
      InstanceQuery_FreeRestrictionClassList(v6);
      return 0;
    }
    if ( v12[1] != 2 || v12[2] != g_InternedSym_Qds )
      break;
    v9 = 1;
    ++*v13;
LABEL_6:
    a1 = *(_DWORD *)(a1 + 10);
    if ( !a1 )
      return v6;
  }
  v11 = InstanceQuery_ResolveClassRestriction(v8, v12);
  if ( v11 )
  {
    if ( v6 )
    {
      if ( v9 == 1 )
      {
        v8 = (int)v11;
        v9 = 0;
        v7[3] = (int)v11;
        v7 = v11;
      }
      else
      {
        *(_DWORD *)(v8 + 8) = v11;
      }
    }
    else
    {
      v8 = (int)v11;
      v7 = v11;
      v6 = v11;
    }
    while ( *(_DWORD *)(v8 + 8) )
      v8 = *(_DWORD *)(v8 + 8);
    goto LABEL_6;
  }
  Parser_ReportSyntaxError();
  InstanceQuery_FreeRestrictionClassList(v6);
  Lexer_ErrorRecover(1);
  return 0;
}
// 4CF3D7: variable 'v8' is possibly undefined
// 51B454: using guessed type int dword_51B454;

//----- (004CF480) --------------------------------------------------------
int *__fastcall InstanceQuery_ResolveClassRestriction(int a1, _DWORD *a2)
{
  int v2; // edx
  int v3; // edi
  int v4; // ecx
  int *v5; // ebp
  int v6; // eax
  int v7; // ecx
  int v8; // esi
  int v9; // eax
  _BYTE *v10; // edx
  int *v11; // eax
  int v12; // ecx
  _DWORD *v13; // ecx
  int *v14; // ecx
  int *v15; // ebx
  _DWORD *v16; // ecx
  int *result; // eax
  _DWORD *v18; // ecx
  int *v19; // ecx
  int v20; // ebx
  int v21; // eax
  _DWORD *v22; // ecx
  int *v23; // eax
  int v24; // ecx
  int v25; // esi
  _DWORD *v26; // edx
  int *v27; // ecx
  int v28; // ebx
  _DWORD *v29; // ecx
  int v30; // [esp+4h] [ebp-28h]
  int v32; // [esp+Ch] [ebp-20h]
  int *v33; // [esp+10h] [ebp-1Ch]
  int v34; // [esp+14h] [ebp-18h]

  v3 = Module_GetCurrent();
  if ( *(_DWORD *)(v2 + 4) == 57 )
  {
    Class_AddBusyReference(a2[2]);
    v18 = *(_DWORD **)(g_ClipsMemoryTable + 64);
    if ( v18 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
      *(_DWORD *)(g_ClipsMemoryTable + 64) = *v18;
      v19 = (int *)g_ClipsMemFreeListTemp;
    }
    else
    {
      v19 = (int *)Mem_HeapAllocWithRetry((_DWORD *)0x10);
    }
    v20 = (int)v19;
    v21 = a2[2];
    *v19 = v21;
    if ( Class_IsInScope(v21, v3) )
      v22[1] = v3;
    else
      v22[1] = **(_DWORD **)(*v22 + 8);
    *(_DWORD *)(v20 + 8) = 0;
    result = (int *)v20;
    *(_DWORD *)(v20 + 12) = 0;
  }
  else
  {
    v4 = a2[1];
    if ( v4 == 2 )
    {
      v23 = Class_LookupByQualifiedName(*(_BYTE **)(a2[2] + 16));
      v25 = (int)v23;
      if ( v23 )
      {
        Class_AddBusyReference((int)v23);
        v26 = *(_DWORD **)(g_ClipsMemoryTable + 64);
        if ( v26 )
        {
          g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
          *(_DWORD *)(g_ClipsMemoryTable + 64) = *v26;
          v27 = (int *)g_ClipsMemFreeListTemp;
        }
        else
        {
          v27 = (int *)Mem_HeapAllocWithRetry((_DWORD *)0x10);
        }
        v28 = (int)v27;
        *v27 = v25;
        if ( Class_IsInScope(v25, v3) )
          v29[1] = v3;
        else
          v29[1] = **(_DWORD **)(*v29 + 8);
        *(_DWORD *)(v28 + 8) = 0;
        result = (int *)v28;
        *(_DWORD *)(v28 + 12) = 0;
      }
      else
      {
        Class_ReportLookupError(v24, *(_DWORD *)(a2[2] + 16));
        return 0;
      }
    }
    else
    {
      if ( v4 == 4 )
      {
        v5 = 0;
        v33 = 0;
        v6 = a2[3] + 1;
        v7 = a2[4] + 1;
        v34 = v6;
        if ( v7 < v6 )
          return v5;
        v8 = 6 * v6 - 6;
        v30 = 6 * v7 - 6;
        while ( 1 )
        {
          v9 = v8 + a2[2];
          if ( *(_WORD *)(v9 + 14) != 2 )
            break;
          v10 = *(_BYTE **)(*(_DWORD *)(v9 + 16) + 16);
          v11 = Class_LookupByQualifiedName(v10);
          v32 = (int)v11;
          if ( !v11 )
          {
            Class_ReportLookupError(v12, (int)v10);
            break;
          }
          Class_AddBusyReference((int)v11);
          v13 = *(_DWORD **)(g_ClipsMemoryTable + 64);
          if ( v13 )
          {
            g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
            *(_DWORD *)(g_ClipsMemoryTable + 64) = *v13;
            v14 = (int *)g_ClipsMemFreeListTemp;
          }
          else
          {
            v14 = (int *)Mem_HeapAllocWithRetry((_DWORD *)0x10);
          }
          v15 = v14;
          *v14 = v32;
          if ( Class_IsInScope(v32, v3) )
            v16[1] = v3;
          else
            v16[1] = **(_DWORD **)(*v16 + 8);
          v15[2] = 0;
          v15[3] = 0;
          if ( v5 )
            v33[2] = (int)v15;
          else
            v5 = v15;
          v33 = v15;
          v8 += 6;
          ++v34;
          if ( v8 > v30 )
            return v5;
        }
        InstanceQuery_FreeRestrictionClassList(v5);
      }
      return 0;
    }
  }
  return result;
}
// 4CF494: variable 'v2' is possibly undefined
// 4CF560: variable 'v16' is possibly undefined
// 4CF5DC: variable 'v22' is possibly undefined
// 4CF656: variable 'v29' is possibly undefined
// 4CF67F: variable 'v24' is possibly undefined
// 4CF6B1: variable 'v12' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004CF700) --------------------------------------------------------
int * InstanceQuery_FreeRestrictionClassList(int *result)
{
  int *i; // ecx
  int *v2; // edx
  _DWORD *v3; // edx
  _DWORD *v4; // edx

  for ( i = result; i; *(_DWORD *)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp )
  {
    while ( 1 )
    {
      v2 = (int *)i[2];
      if ( !v2 )
        break;
      i[2] = v2[2];
      Class_ReleaseBusyReference(*v2);
      g_ClipsMemFreeListTemp = (int)v3;
      *v3 = *(_DWORD *)(g_ClipsMemoryTable + 64);
      *(_DWORD *)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
    }
    Class_ReleaseBusyReference(*i);
    g_ClipsMemFreeListTemp = (int)v4;
    *v4 = *(_DWORD *)(g_ClipsMemoryTable + 64);
    result = (int *)g_ClipsMemFreeListTemp;
  }
  return result;
}
// 4CF708: variable 'i' is possibly undefined
// 4CF721: variable 'v3' is possibly undefined
// 4CF74D: variable 'v4' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004CF770) --------------------------------------------------------
signed int  InstanceQuery_TestClassRestriction(int *a1, int a2, double a3)
{
  int *v4; // esi
  signed int v5; // eax

  v4 = a1;
  g_InstanceQuery_AbortFlag = 1;
  if ( a1 )
  {
    while ( 1 )
    {
      g_InstanceQuery_AbortFlag = 0;
      v5 = Class_NewTraversalID();
      if ( v5 == -1 )
        break;
      if ( InstanceQuery_TestInstancesRecursive(v4[1], v5, (int)a1, *v4, a3, a2) )
      {
        Class_ReleaseTraversalID();
        return 1;
      }
      Class_ReleaseTraversalID();
      if ( g_ClipsHaltExecution == 1 || g_InstanceQuery_AbortFlag == 1 )
        return 0;
      v4 = (int *)v4[2];
      if ( !v4 )
        return 0;
    }
  }
  return 0;
}
// 51A968: using guessed type int dword_51A968;
// 51B460: using guessed type int dword_51B460;

//----- (004CF800) --------------------------------------------------------
BOOL  InstanceQuery_TestInstancesRecursive(
        int a1,
        signed int a2,
        int a3,
        int a4,
        double a5,
        int a6)
{
  int v7; // ebx
  int v8; // eax
  BOOL result; // eax
  int v10; // edx
  int i; // ecx
  unsigned int v12; // edi
  int v13; // ebp
  _DWORD v14[6]; // [esp+0h] [ebp-30h] BYREF
  int v15; // [esp+18h] [ebp-18h]
  signed int v16; // [esp+1Ch] [ebp-14h]
  int v17; // [esp+20h] [ebp-10h]

  v15 = a1;
  v16 = a2;
  v17 = a4;
  v7 = ((a2 - (__CFSHL__(a2 >> 31, 3) + 8 * (a2 >> 31))) >> 3) + a4;
  v8 = 1 << (a2 % 8);
  if ( ((unsigned __int8)v8 & *(_BYTE *)(v7 + 108)) != 0 )
    return 0;
  v10 = v15;
  *(_BYTE *)(v7 + 108) |= v8;
  result = Class_IsInScope(v17, v10);
  if ( !result )
    return result;
  i = *(_DWORD *)(v17 + 80);
  if ( !i )
    goto LABEL_9;
  while ( 1 )
  {
    *(_DWORD *)(*(_DWORD *)g_ClipsQueryCore + 4 * a6) = i;
    if ( !*(_DWORD *)(a3 + 12) )
    {
      ++*(_DWORD *)(i + 40);
      ++g_ClipsCurrentEvaluationDepth;
      Parser_ParseForm(*(__int16 **)(g_ClipsQueryCore + 4), v14, i, a5);
      --g_ClipsCurrentEvaluationDepth;
      Rules_RunPeriodicCleanup(0, 1);
      --*(_DWORD *)(i + 40);
      if ( g_ClipsHaltExecution == 1 || v14[1] != 2 || v14[2] != g_ClipsFalseSymbol )
        goto LABEL_9;
      goto LABEL_15;
    }
    ++*(_DWORD *)(i + 40);
    if ( InstanceQuery_TestClassRestriction(*(_DWORD *)(a3 + 12), a6 + 1, a5) == 1 )
      break;
    --*(_DWORD *)(i + 40);
    if ( g_ClipsHaltExecution == 1 || g_InstanceQuery_AbortFlag == 1 )
      goto LABEL_9;
LABEL_15:
    for ( i = *(_DWORD *)(i + 52); i; i = *(_DWORD *)(i + 52) )
    {
      if ( (*(_BYTE *)(i + 24) & 2) == 0 )
        break;
    }
    if ( !i )
      goto LABEL_9;
  }
  --*(_DWORD *)(i + 40);
LABEL_9:
  if ( i )
    return g_ClipsHaltExecution != 1 && g_InstanceQuery_AbortFlag != 1;
  v12 = 0;
  v13 = 0;
  while ( v12 < *(unsigned __int16 *)(v17 + 40) )
  {
    if ( InstanceQuery_TestInstancesRecursive(v15, v16, a3, *(_DWORD *)(*(_DWORD *)(v17 + 42) + v13), a5, a6) )
      return 1;
    if ( g_ClipsHaltExecution == 1 || g_InstanceQuery_AbortFlag == 1 )
      return 0;
    v13 += 4;
    ++v12;
  }
  return 0;
}
// 4CF8AE: variable 'i' is possibly undefined
// 51A968: using guessed type int dword_51A968;
// 51A96C: using guessed type int dword_51A96C;
// 51B458: using guessed type int dword_51B458;
// 51B460: using guessed type int dword_51B460;
// 54DD70: using guessed type int dword_54DD70;

//----- (004CF9F0) --------------------------------------------------------
void  InstanceQuery_ForEachClassRestriction(int *a1, int a2, double a3)
{
  int *v4; // esi
  signed int v5; // eax

  v4 = a1;
  for ( g_InstanceQuery_AbortFlag = 1; v4; v4 = (int *)v4[2] )
  {
    g_InstanceQuery_AbortFlag = 0;
    v5 = Class_NewTraversalID();
    if ( v5 == -1 )
      break;
    InstanceQuery_ForEachInstanceRecursive(v4[1], v5, (int)a1, *v4, a3, a2);
    Class_ReleaseTraversalID();
    if ( g_ClipsHaltExecution == 1 )
      break;
    if ( g_InstanceQuery_AbortFlag == 1 )
      break;
  }
}
// 51A968: using guessed type int dword_51A968;
// 51B460: using guessed type int dword_51B460;

//----- (004CFA70) --------------------------------------------------------
void  InstanceQuery_ForEachInstanceRecursive(int a1, signed int a2, int a3, int a4, double a5, int a6)
{
  int v7; // ebx
  int v8; // eax
  int v9; // edx
  int i; // ecx
  unsigned int v11; // ebp
  int j; // edi
  bool v13; // zf
  int v14; // ecx
  int v15; // ecx
  _DWORD v16[6]; // [esp+0h] [ebp-30h] BYREF
  int v17; // [esp+18h] [ebp-18h]
  signed int v18; // [esp+1Ch] [ebp-14h]
  int v19; // [esp+20h] [ebp-10h]

  v17 = a1;
  v18 = a2;
  v19 = a4;
  v7 = ((a2 - (__CFSHL__(a2 >> 31, 3) + 8 * (a2 >> 31))) >> 3) + a4;
  v8 = 1 << (a2 % 8);
  if ( ((unsigned __int8)v8 & *(_BYTE *)(v7 + 108)) == 0 )
  {
    v9 = v17;
    *(_BYTE *)(v7 + 108) |= v8;
    if ( Class_IsInScope(v19, v9) )
    {
      i = *(_DWORD *)(v19 + 80);
      if ( i )
      {
        while ( 1 )
        {
          *(_DWORD *)(*(_DWORD *)g_ClipsQueryCore + 4 * a6) = i;
          if ( *(_DWORD *)(a3 + 12) )
            break;
          ++*(_DWORD *)(i + 40);
          ++g_ClipsCurrentEvaluationDepth;
          Parser_ParseForm(*(__int16 **)(g_ClipsQueryCore + 4), v16, i, a5);
          --g_ClipsCurrentEvaluationDepth;
          Rules_RunPeriodicCleanup(0, 1);
          --*(_DWORD *)(i + 40);
          if ( g_ClipsHaltExecution == 1 )
            goto LABEL_7;
          if ( v16[1] == 2 && v16[2] == g_ClipsFalseSymbol )
            goto LABEL_15;
          if ( *(_DWORD *)(g_ClipsQueryCore + 8) )
          {
            ++*(_DWORD *)(i + 40);
            ++g_ClipsCurrentEvaluationDepth;
            Rules_ValueDeinstall(*(_DWORD *)(g_ClipsQueryCore + 28), i);
            Parser_ParseForm(*(__int16 **)(g_ClipsQueryCore + 8), *(_DWORD **)(g_ClipsQueryCore + 28), v14, a5);
            Rules_ValueInstall(*(_DWORD *)(g_ClipsQueryCore + 28), v15);
            --g_ClipsCurrentEvaluationDepth;
            Rules_RunPeriodicCleanup(0, 1);
            --*(_DWORD *)(i + 40);
            if ( g_ClipsHaltExecutionFlag )
            {
              g_InstanceQuery_AbortFlag = 1;
              goto LABEL_7;
            }
            v13 = g_ClipsHaltExecution == 1;
            goto LABEL_14;
          }
          InstanceQuery_EnqueueDelayedBinding();
LABEL_15:
          for ( i = *(_DWORD *)(i + 52); i; i = *(_DWORD *)(i + 52) )
          {
            if ( (*(_BYTE *)(i + 24) & 2) == 0 )
              break;
          }
          if ( !i )
            goto LABEL_7;
        }
        ++*(_DWORD *)(i + 40);
        InstanceQuery_ForEachClassRestriction(*(_DWORD *)(a3 + 12), a6 + 1, a5);
        --*(_DWORD *)(i + 40);
        if ( g_ClipsHaltExecution == 1 )
          goto LABEL_7;
        v13 = g_InstanceQuery_AbortFlag == 1;
LABEL_14:
        if ( v13 )
          goto LABEL_7;
        goto LABEL_15;
      }
LABEL_7:
      if ( !i )
      {
        v11 = 0;
        for ( j = 0; v11 < *(unsigned __int16 *)(v19 + 40); j += 4 )
        {
          InstanceQuery_ForEachInstanceRecursive(v17, v18, a3, *(_DWORD *)(j + *(_DWORD *)(v19 + 42)), a5, a6);
          if ( g_ClipsHaltExecution == 1 || g_InstanceQuery_AbortFlag == 1 )
            break;
          ++v11;
        }
      }
    }
  }
}
// 4CFB17: variable 'i' is possibly undefined
// 4CFC30: variable 'v14' is possibly undefined
// 4CFC3D: variable 'v15' is possibly undefined
// 51A968: using guessed type int dword_51A968;
// 51A96C: using guessed type int dword_51A96C;
// 51ACC0: using guessed type __int64 qword_51ACC0;
// 51B458: using guessed type int dword_51B458;
// 51B460: using guessed type int dword_51B460;
// 54DD70: using guessed type int dword_54DD70;

//----- (004CFCB0) --------------------------------------------------------
int InstanceQuery_EnqueueDelayedBinding()
{
  _DWORD *v0; // edi
  _DWORD *v1; // eax
  _DWORD *v2; // edx
  int v3; // edx
  int v4; // eax
  int result; // eax
  _DWORD *v6; // esi
  int v7; // ecx

  v0 = Mem_SmallBlockAlloc(8u);
  v1 = Mem_SmallBlockAlloc(4 * *(_DWORD *)(g_ClipsQueryCore + 20));
  *v2 = v1;
  v3 = 0;
  v4 = 0;
  while ( v3 < *(_DWORD *)(g_ClipsQueryCore + 20) )
  {
    v6 = (_DWORD *)(*v0 + v4);
    ++v3;
    v7 = *(_DWORD *)(*(_DWORD *)g_ClipsQueryCore + v4);
    v4 += 4;
    *v6 = v7;
  }
  v0[1] = 0;
  if ( *(_DWORD *)(g_ClipsQueryCore + 12) )
    *(_DWORD *)(*(_DWORD *)(g_ClipsQueryCore + 16) + 4) = v0;
  else
    *(_DWORD *)(g_ClipsQueryCore + 12) = v0;
  *(_DWORD *)(g_ClipsQueryCore + 16) = v0;
  result = g_ClipsQueryCore;
  ++*(_DWORD *)(g_ClipsQueryCore + 24);
  return result;
}
// 4CFCD7: variable 'v2' is possibly undefined
// 51B458: using guessed type int dword_51B458;

//----- (004CFD30) --------------------------------------------------------
signed int InstanceQuery_DequeueDelayedBinding()
{
  *(_DWORD *)(g_ClipsQueryCore + 16) = *(_DWORD *)(g_ClipsQueryCore + 12);
  *(_DWORD *)(g_ClipsQueryCore + 12) = *(_DWORD *)(*(_DWORD *)(g_ClipsQueryCore + 12) + 4);
  Mem_SmallBlockFree(**(_DWORD ***)(g_ClipsQueryCore + 16), 4 * *(_DWORD *)(g_ClipsQueryCore + 20));
  return Mem_SmallBlockFree(*(_DWORD **)(g_ClipsQueryCore + 16), 8);
}
// 51B458: using guessed type int dword_51B458;

//----- (004CFD80) --------------------------------------------------------
int ObjectsCompiler_RegisterCodeGenerator()
{
  int result; // eax

  result = Rules_AddCodeGeneratorItem((int)aObjects, 0, (int)ObjectsCompiler_WriteRuntimeInitCall, (int)ObjectsCompiler_AssignConstructIndices, (int)ObjectsCompiler_GenerateObjectsCode, 13);
  g_ClipsConstructCompilerData = result;
  return result;
}
// 4CFE40: using guessed type int sub_4CFE40();
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004CFDB0) --------------------------------------------------------
int  ObjectsCompiler_WriteDefclassPointerRef(int a1, int a2, int a3)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( a2 )
    return Output_WriteFormatted(
             a3,
             *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 4),
             a1,
             (int)aSD_DD_1,
             *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 4));
  else
    return Output_WriteFormatted(a3, 0, a1, (int)aNull_7, v4);
}
// 4CFDC0: variable 'v4' is possibly undefined
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004CFE00) --------------------------------------------------------
int  ObjectsCompiler_WriteModuleItemHeaderRef(int a1, int a2)
{
  return Output_WriteFormatted(a2, **(_DWORD **)(g_ClipsConstructCompilerData + 20), a1, (int)aMihsSD_DD_1, **(_DWORD **)(g_ClipsConstructCompilerData + 20));
}
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004CFE40) --------------------------------------------------------
int ObjectsCompiler_AssignConstructIndices()
{
  int v0; // edx
  int i; // ecx
  int result; // eax

  Rules_DoForAllConstructs((void (*)(void))ObjectsCompiler_AssignClassCompileIndex, 0);
  v0 = 0;
  for ( i = 0; i != 668; i += 4 )
  {
    for ( result = *(_DWORD *)(i + g_Defclass_SlotNameHashTablePtr); result; ++v0 )
    {
      *(_DWORD *)(result + 24) = v0;
      result = *(_DWORD *)(result + 20);
    }
  }
  return result;
}
// 4CFE40: using guessed type int sub_4CFE40();
// 51ACF0: using guessed type int dword_51ACF0;
// 51AD70: using guessed type int dword_51AD70;
// 54E6BC: using guessed type int dword_54E6BC;

//----- (004CFEB0) --------------------------------------------------------
_DWORD * ObjectsCompiler_AssignClassCompileIndex(_DWORD *a1, _DWORD *a2)
{
  int v3; // ebx
  _DWORD *result; // eax
  int v6; // edx
  unsigned int v7; // ebx
  int v8; // edx
  int v9; // ebp
  int v10; // edi

  v3 = (*a2)++;
  result = a2;
  v6 = a1[16];
  a1[3] = v3;
  v7 = 0;
  if ( v6 )
  {
    v8 = 0;
    do
    {
      *(_DWORD *)(v8 + a1[13] + 28) = ((unsigned __int16)result[2] << 16) | (unsigned __int16)result[1];
      v9 = result[2] + 1;
      result[2] = v9;
      if ( v9 >= result[3] )
      {
        v10 = result[1];
        result[2] = 0;
        result[1] = v10 + 1;
      }
      ++v7;
      v8 += 44;
    }
    while ( v7 < a1[16] );
  }
  return result;
}

//----- (004CFF30) --------------------------------------------------------
int  ObjectsCompiler_WriteSlotNamePointerRef(int a1, int a2, int a3)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( a2 )
    return Output_WriteFormatted(
             a3,
             *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 32),
             a1,
             (int)aSD_DD_1,
             *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 32));
  else
    return Output_WriteFormatted(a3, 0, a1, (int)aNull_7, v4);
}
// 4CFF40: variable 'v4' is possibly undefined
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004CFF80) --------------------------------------------------------
int  ObjectsCompiler_WriteRuntimeInitCall(int a1, int a2)
{
  return Output_WriteFormatted(a1, a2, a1, (int)aObjectsruntime, *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 40));
}
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004CFFC0) --------------------------------------------------------
void  ObjectsCompiler_GenerateObjectsCode(const char *a1, const char *a2, DWORD a3, int a4, int a5)
{
  int v8; // eax
  int v9; // edx
  int v10; // ebx
  int v11; // edx
  int v12; // ecx
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // edx
  _DWORD v17[3]; // [esp+0h] [ebp-10Ch]
  const char *v18[3]; // [esp+Ch] [ebp-100h] BYREF
  const char *v19[3]; // [esp+18h] [ebp-F4h] BYREF
  const char *v20; // [esp+24h] [ebp-E8h] BYREF
  const char *v21; // [esp+30h] [ebp-DCh] BYREF
  const char *v22; // [esp+3Ch] [ebp-D0h] BYREF
  const char *v23; // [esp+48h] [ebp-C4h] BYREF
  const char *v24; // [esp+54h] [ebp-B8h] BYREF
  const char *v25[3]; // [esp+60h] [ebp-ACh] BYREF
  int v26; // [esp+6Ch] [ebp-A0h] BYREF
  int v27; // [esp+70h] [ebp-9Ch] BYREF
  int v28; // [esp+74h] [ebp-98h] BYREF
  int v29; // [esp+78h] [ebp-94h] BYREF
  int v30; // [esp+7Ch] [ebp-90h] BYREF
  int v31; // [esp+80h] [ebp-8Ch] BYREF
  int v32; // [esp+84h] [ebp-88h] BYREF
  int v33; // [esp+88h] [ebp-84h] BYREF
  int v34; // [esp+8Ch] [ebp-80h] BYREF
  int v35; // [esp+90h] [ebp-7Ch]
  int v36; // [esp+94h] [ebp-78h] BYREF
  int v37; // [esp+98h] [ebp-74h] BYREF
  int v38; // [esp+9Ch] [ebp-70h] BYREF
  int v39; // [esp+A0h] [ebp-6Ch] BYREF
  int v40; // [esp+A4h] [ebp-68h] BYREF
  int v41; // [esp+A8h] [ebp-64h] BYREF
  int v42; // [esp+ACh] [ebp-60h] BYREF
  int v43; // [esp+B0h] [ebp-5Ch] BYREF
  int v44; // [esp+B4h] [ebp-58h] BYREF
  int v45; // [esp+B8h] [ebp-54h] BYREF
  int v46; // [esp+BCh] [ebp-50h] BYREF
  int v47; // [esp+C0h] [ebp-4Ch] BYREF
  int v48; // [esp+C4h] [ebp-48h] BYREF
  int v49; // [esp+C8h] [ebp-44h] BYREF
  int v50; // [esp+CCh] [ebp-40h] BYREF
  int v51; // [esp+D0h] [ebp-3Ch] BYREF
  int v52; // [esp+D4h] [ebp-38h] BYREF
  int v53; // [esp+D8h] [ebp-34h] BYREF
  int v54; // [esp+DCh] [ebp-30h] BYREF
  int v55; // [esp+E0h] [ebp-2Ch] BYREF
  int v56; // [esp+E4h] [ebp-28h] BYREF
  int v57; // [esp+E8h] [ebp-24h] BYREF
  int v58; // [esp+ECh] [ebp-20h] BYREF
  int v59; // [esp+F0h] [ebp-1Ch]
  _DWORD *j; // [esp+F4h] [ebp-18h]
  int i; // [esp+F8h] [ebp-14h]
  int v62; // [esp+FCh] [ebp-10h]

  v59 = a4;
  v8 = 0;
  v58 = 1;
  v62 = 0;
  v9 = 0;
  do
  {
    ++v8;
    v9 += 3;
    v25[v8 + 2] = 0;
    *(int *)((char *)&v49 + v8 * 4) = 1;
    *(int *)((char *)&v33 + v8 * 4) = 0;
    *(int *)((char *)&v41 + v8 * 4) = 0;
    v17[v9] = 0;
  }
  while ( v8 != 8 );
  v10 = v59;
  Output_WriteFormatted(1, v9 * 4, v59, (int)aIncludeClassco, (char)v18[0]);
  Output_WriteFormatted(v12, v11, v10, (int)aIncludeClassin, (char)v18[0]);
  if ( ObjectsCompiler_WriteClassPointerArray(a1, a2, a3, v10, a5, &v58) )
  {
    if ( ObjectsCompiler_WriteClassHashTable(a1, a2, a3, v59, a5, &v58) )
    {
      ObjectsCompiler_WriteSlotNameHashTable(a1, a2, a3, v59, a5, &v58);
      if ( v13 )
      {
        if ( ObjectsCompiler_WriteSlotNameRecords(a1, a2, a3, v59, a5, &v58) )
        {
          for ( i = Module_NextEnum(0); i; ++v26 )
          {
            Module_SetCurrent(i);
            v14 = Rules_ConstructCodeFileOpen(
                    v34,
                    a1,
                    a3,
                    a2,
                    &v58,
                    v50,
                    v59,
                    (char)aDefclass_modul,
                    **(const char ***)(g_ClipsConstructCompilerData + 20),
                    v42,
                    v18);
            v34 = v14;
            if ( !v14 )
              break;
            ObjectsCompiler_WriteModuleRecord(v14, i, a5);
            v34 = Rules_ConstructCodeFileClose(v34, &v26, a5, &v50, &v42, (int)v18);
            for ( j = (_DWORD *)Class_GetNextRecord(0); j; j = (_DWORD *)Class_GetNextRecord((int)j) )
            {
              v15 = Rules_ConstructCodeFileOpen(
                      v35,
                      a1,
                      a3,
                      a2,
                      &v58,
                      v51,
                      v59,
                      (char)aDefclass_6,
                      *(const char **)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 4),
                      v43,
                      v19);
              v35 = v15;
              if ( !v15 )
                goto LABEL_20;
              ObjectsCompiler_WriteClassRecord(v15, a3, (int)j, a5, v62, v52, v28, v53, v29, v54, v30, v55, v31, v56, v32, v57, v33);
              ++v27;
              v35 = Rules_ConstructCodeFileClose(v35, &v27, a5, &v51, &v43, (int)v19);
              if ( !ObjectsCompiler_WriteClassLinkPointerArray(&v36, a1, a3, a2, v59, &v58, a5, (int)j, &v52, &v28, &v44, &v20)
                || !ObjectsCompiler_WriteSlotDescArray(&v37, a1, a3, a2, v59, &v58, a5, (int)j, &v53, &v29, &v45, &v21)
                || !ObjectsCompiler_WriteSlotDescPointerArray(&v38, a1, a3, a2, v59, &v58, a5, (int)j, &v54, &v30, &v46, &v22)
                || !ObjectsCompiler_WriteSlotIndexMapArray(&v39, a1, a3, a2, v59, &v58, a5, j, &v55, &v31, &v47, &v23)
                || !ObjectsCompiler_WriteHandlerArray(&v40, a1, a3, a2, v59, &v58, a5, (int)j, &v56, &v32, &v48, &v24)
                || !ObjectsCompiler_WriteHandlerIndexMapArray(&v41, a1, a3, a2, v59, &v58, a5, (int)j, &v57, &v33, &v49, v25) )
              {
                goto LABEL_20;
              }
            }
            i = Module_NextEnum(i);
            v62 = v16 + 1;
          }
LABEL_20:
          ObjectsCompiler_CloseConstructFileGroup(&v34, &v42, a5, (int)v18);
        }
      }
    }
  }
}
// 4D0036: variable 'v12' is possibly undefined
// 4D0036: variable 'v11' is possibly undefined
// 4D00B3: variable 'v13' is possibly undefined
// 4D04ED: variable 'v16' is possibly undefined
// 54E8F8: using guessed type int dword_54E8F8;

