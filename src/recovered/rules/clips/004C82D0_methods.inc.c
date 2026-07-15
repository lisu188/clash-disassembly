/* CLIPS method lookup, dispatch, and late object-runtime support.
 * Original function-marker range: 0x004C82D0..0x004CFFC0.
 * Included by clash95.c; not a standalone translation unit. */

//----- (004C82D0) --------------------------------------------------------
signed int  Method_FindByIndex(int gfunc, int theIndex)
{
  int methodCount; // edx
  signed int result; // eax
  _DWORD *i; // edx

  methodCount = *(_DWORD *)(gfunc + 32);
  result = 0;
  if ( !methodCount )
    return -1;
  for ( i = *(_DWORD **)(gfunc + 28); theIndex != *i; i += 10 )
  {
    if ( (unsigned int)++result >= *(_DWORD *)(gfunc + 32) )
      return -1;
  }
  return result;
}

//----- (004C8300) --------------------------------------------------------
signed int  Defgeneric_PreviewGenericCommand(double a1)
{
  signed int result; // eax
  int generic; // esi
  int oldReentryFlag; // edi
  int genericName; // ebx
  int argCount; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // [esp+0h] [ebp-34h] BYREF
  int v10; // [esp+8h] [ebp-2Ch]
  int oldGeneric; // [esp+18h] [ebp-1Ch]

  g_ClipsEvaluationError = 0;
  result = Lexer_ParseValueList(1, &v9, 2, a1);
  if ( result )
  {
    generic = Defgeneric_LookupWithImports(*(_BYTE **)(v10 + 16));
    if ( generic )
    {
      oldReentryFlag = Rules_GetReentryGuardFlag();
      Rules_SetReentryGuardFlag(1);
      oldGeneric = g_ClipsCurrentGeneric;
      g_ClipsCurrentGeneric = generic;
      ++g_ClipsCurrentEvaluationDepth;
      genericName = Rules_GetConstructNameString(generic);
      argCount = AST_CountListNodes(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10));
      ProcParam_PushEvaluatedArgumentFrame(
        *(_DWORD **)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10),
        argCount,
        (int)aGenericFunct_1,
        genericName,
        a1,
        (int (*)(void))Method_PrintCallErrorBanner);
      if ( !g_ClipsEvaluationError )
      {
        ++*(_DWORD *)(generic + 20);
        Defgeneric_PrintApplicableMethods(generic, a1);
        --*(_DWORD *)(generic + 20);
      }
      ProcParam_PopFrame();
      g_ClipsCurrentGeneric = oldGeneric;
      --g_ClipsCurrentEvaluationDepth;
      return Rules_SetReentryGuardFlag(oldReentryFlag);
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
_DWORD * Defgeneric_AppendMethodSignatureText(char *buf, int bufMax, int a3, int theMethod)
{
  _DWORD *result; // eax
  int restrictionCount; // ebx
  _DWORD *v7; // edx
  int v8; // eax
  const char *bufPtr; // edi
  unsigned int typeIndex; // ebp
  unsigned int typeCount; // edx
  int v12; // ecx
  char v13[16]; // [esp+0h] [ebp-38h] BYREF
  int restrictionOffset; // [esp+10h] [ebp-28h]
  _DWORD *restrictionIndex; // [esp+14h] [ebp-24h]
  _DWORD *meth; // [esp+18h] [ebp-20h]
  int v17; // [esp+1Ch] [ebp-1Ch]
  int typeOffset; // [esp+20h] [ebp-18h]
  _DWORD *restriction; // [esp+24h] [ebp-14h]

  v17 = bufMax;
  meth = (_DWORD *)theMethod;
  *buf = 0;
  if ( (*(_BYTE *)(theMethod + 24) & 1) != 0 )
    strncpy_(a3, aSys);
  sprintf_(v13, "%-2d ", *meth);
  ((void (*)(void))strncat_)();
  result = meth;
  restrictionCount = meth[2];
  restrictionIndex = 0;
  if ( restrictionCount > 0 )
  {
    restrictionOffset = 0;
    do
    {
      v7 = (_DWORD *)(meth[7] + restrictionOffset);
      v8 = meth[2] - 1;
      restriction = v7;
      if ( (_DWORD *)v8 == restrictionIndex && meth[4] == -1 )
      {
        if ( !v7[2] && !restriction[1] )
        {
          strlen(buf);
          return (_DWORD *)((int (*)(void))strncat_)();
        }
        bufPtr = buf;
      }
      else
      {
        bufPtr = buf;
      }
      strlen(bufPtr);
      ((void (*)(void))strncat_)();
      typeIndex = 0;
      if ( restriction[2] )
      {
        typeOffset = 0;
        do
        {
          strlen(buf);
          Rules_GetConstructNameString(*(_DWORD *)(typeOffset + *restriction));
          ((void (*)(void))strncat_)();
          if ( typeIndex < restriction[2] - 1 )
          {
            strlen(buf);
            ((void (*)(void))strncat_)();
          }
          ++typeIndex;
          typeCount = restriction[2];
          typeOffset += 4;
        }
        while ( typeIndex < typeCount );
      }
      if ( restriction[1] )
      {
        if ( restriction[2] )
        {
          strlen(buf);
          ((void (*)(void))strncat_)();
        }
        strlen(buf);
        ((void (*)(void))strncat_)();
      }
      strlen(buf);
      ((void (*)(void))strncat_)();
      result = (_DWORD *)(meth[2] - 1);
      if ( result != restrictionIndex )
      {
        strlen(buf);
        result = (_DWORD *)((int (*)(void))strncat_)();
      }
      v12 = meth[2];
      restrictionOffset += 12;
      restrictionIndex = (_DWORD *)((char *)restrictionIndex + 1);
    }
    while ( (int)restrictionIndex < v12 );
  }
  return result;
}
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 48521A: using guessed type int __fastcall strncpy_(_DWORD, _DWORD);

//----- (004C86C0) --------------------------------------------------------
int  Defgeneric_CheckGenericExists(int functionName, _BYTE *genericName)
{
  int result; // eax
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx

  result = Defgeneric_LookupWithImports(genericName);
  if ( !result )
  {
    Rules_PrintErrorID((int)aGenrcfun, 3, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnableToFindGe, v4);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], v5, v5);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInFunction_2, v6);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], functionName, v7);
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
signed int  Defgeneric_CheckMethodExists(int functionName, int generic, int methodIndex)
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

  result = Method_FindByIndex(generic, methodIndex);
  if ( result == -1 )
  {
    Rules_PrintErrorID((int)aGenrcfun, 2, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnableToFindMe, v6);
    v7 = Rules_GetConstructNameString(generic);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], v7, v8);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_50B158, v9);
    Rules_PrintLongInteger(v10, v10);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInFunction_2, v11);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], functionName, v12);
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
  int genericPtr; // ecx
  int foundApplicable; // ebp
  unsigned int methodIndex; // edi
  int methodOffset; // esi
  int v6; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // eax
  int v14; // ecx
  char buf[280]; // [esp+0h] [ebp-118h] BYREF

  genericPtr = result;
  foundApplicable = 0;
  methodIndex = 0;
  if ( *(_DWORD *)(result + 32) )
  {
    methodOffset = 0;
    do
    {
      ++*(_DWORD *)(methodOffset + *(_DWORD *)(genericPtr + 28) + 4);
      if ( Method_RestrictionsSatisfiedByArgs(methodOffset + *(_DWORD *)(genericPtr + 28), a2) )
      {
        v6 = Rules_GetConstructNameString(genericPtr);
        Output_Write((int)g_IO_LogicalName_WDisplay, v6, v7);
        Output_Write((int)g_IO_LogicalName_WDisplay, (int)asc_50B158, v8);
        Defgeneric_AppendMethodSignatureText(buf, 255, v9, methodOffset + *(_DWORD *)(v9 + 28));
        Output_Write((int)g_IO_LogicalName_WDisplay, (int)buf, v10);
        foundApplicable = 1;
        Output_Write((int)g_IO_LogicalName_WDisplay, (int)asc_50B160, v11);
      }
      --*(_DWORD *)(methodOffset + *(_DWORD *)(genericPtr + 28) + 4);
      ++methodIndex;
      result = *(_DWORD *)(genericPtr + 32);
      methodOffset += 40;
    }
    while ( methodIndex < result );
  }
  if ( !foundApplicable )
  {
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aNoApplicableMe, genericPtr);
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
int  Defgeneric_PrintModuleIndexOrNull(int fp, int theModule, int imageID)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( theModule )
    return Output_WriteFormatted(
             imageID,
             *(_DWORD *)(*(_DWORD *)(g_DefgenericCodeGenItem + 20) + 4),
             fp,
             (int)aSD_DD,
             *(_DWORD *)(*(_DWORD *)(g_DefgenericCodeGenItem + 20) + 4));
  else
    return Output_WriteFormatted(imageID, 0, fp, (int)aNull_4, v4);
}
// 4C8980: variable 'v4' is possibly undefined
// 54E8CC: using guessed type int dword_54E8CC;

//----- (004C89C0) --------------------------------------------------------
int  Defgeneric_PrintModuleReference(int fp, int imageID)
{
  return Output_WriteFormatted(imageID, **(_DWORD **)(g_DefgenericCodeGenItem + 20), fp, (int)aMihsSD_DD, **(_DWORD **)(g_DefgenericCodeGenItem + 20));
}
// 54E8CC: using guessed type int dword_54E8CC;

//----- (004C8A00) --------------------------------------------------------
signed int Defgeneric_BeforeCode()
{
  return Rules_RegisterModuleItemIdAssigner();
}
// 54E6A4: using guessed type int dword_54E6A4;

//----- (004C8A10) --------------------------------------------------------
int  Defgeneric_DefgenericsToCode(const char *fileName, const char *pathName, int imageID, int headerFP, int maxIndices)
{
  int slotIndex; // eax
  int slotOffset; // edx
  const char **structNames; // eax
  int openedModuleFile; // eax
  int openedGenericFile; // eax
  int structNamesForMethod; // eax
  int v11; // ecx
  int numMethods; // edx
  int structNamesForRestriction; // eax
  int numRestrictions; // ecx
  _DWORD *restrictionPtr; // ebp
  int v16; // edx
  unsigned int typeIndex; // esi
  int typeOffset; // edi
  unsigned int restrictionLimit; // edi
  unsigned int methodLimit; // esi
  int prevModuleIndex; // ebp
  int v23; // [esp+0h] [ebp-D8h]
  int v24; // [esp+4h] [ebp-D4h]
  const char **nameBuffer; // [esp+8h] [ebp-D0h]
  const char *moduleNameBuf[3]; // [esp+Ch] [ebp-CCh] BYREF
  const char *genericNameBuf[3]; // [esp+18h] [ebp-C0h] BYREF
  const char *methodNameBuf[3]; // [esp+24h] [ebp-B4h] BYREF
  const char *restrictionNameBuf[3]; // [esp+30h] [ebp-A8h] BYREF
  const char *typeNameBuf[3]; // [esp+3Ch] [ebp-9Ch] BYREF
  int moduleCount; // [esp+48h] [ebp-90h] BYREF
  int genericCount; // [esp+4Ch] [ebp-8Ch] BYREF
  int methodCount; // [esp+50h] [ebp-88h] BYREF
  int restrictionCount; // [esp+54h] [ebp-84h] BYREF
  DWORD typeCount; // [esp+58h] [ebp-80h] BYREF
  int moduleReopen; // [esp+5Ch] [ebp-7Ch] BYREF
  int genericReopen; // [esp+60h] [ebp-78h] BYREF
  int methodReopen; // [esp+64h] [ebp-74h] BYREF
  int restrictionReopen; // [esp+68h] [ebp-70h] BYREF
  int typeReopen; // [esp+6Ch] [ebp-6Ch] BYREF
  int moduleArrayVersion; // [esp+70h] [ebp-68h] BYREF
  int genericArrayVersion; // [esp+74h] [ebp-64h] BYREF
  int methodArrayVersion; // [esp+78h] [ebp-60h] BYREF
  int restrictionArrayVersion; // [esp+7Ch] [ebp-5Ch] BYREF
  int typeArrayVersion; // [esp+80h] [ebp-58h] BYREF
  int moduleFile; // [esp+84h] [ebp-54h] BYREF
  int genericFile; // [esp+88h] [ebp-50h]
  int methodFile; // [esp+8Ch] [ebp-4Ch]
  int restrictionFile; // [esp+90h] [ebp-48h]
  int typeFile; // [esp+94h] [ebp-44h]
  int version; // [esp+98h] [ebp-40h] BYREF
  int imageIDLocal; // [esp+9Ch] [ebp-3Ch]
  int Enum; // [esp+A0h] [ebp-38h]
  int moduleIndex; // [esp+A4h] [ebp-34h]
  int i; // [esp+A8h] [ebp-30h]
  int methodOffset; // [esp+ACh] [ebp-2Ch]
  unsigned int methodIndex; // [esp+B0h] [ebp-28h]
  const char *pathNameLocal; // [esp+B4h] [ebp-24h]
  const char *fileNameLocal; // [esp+B8h] [ebp-20h]
  int headerFPLocal; // [esp+BCh] [ebp-1Ch]
  int methodPtr; // [esp+C0h] [ebp-18h]
  int restrictionOffset; // [esp+C4h] [ebp-14h]
  unsigned int restrictionIndex; // [esp+C8h] [ebp-10h]

  fileNameLocal = fileName;
  pathNameLocal = pathName;
  headerFPLocal = headerFP;
  imageIDLocal = imageID;
  slotIndex = 0;
  version = 1;
  moduleIndex = 0;
  slotOffset = 0;
  do
  {
    ++slotIndex;
    slotOffset += 12;
    typeNameBuf[slotIndex + 2] = 0;
    *(int *)((char *)&typeReopen + slotIndex * 4) = 1;
    *(int *)((char *)&typeArrayVersion + slotIndex * 4) = 0;
    *(DWORD *)((char *)&typeCount + slotIndex * 4) = 0;
    *(int *)((char *)&v23 + slotOffset) = 0;
  }
  while ( slotIndex != 5 );
  Output_WriteFormatted(0, slotOffset, headerFPLocal, (int)aIncludeGenrcfu, (char)moduleNameBuf[0]);
  Enum = Module_NextEnum(0);
  if ( Enum )
  {
    while ( 1 )
    {
      Module_SetCurrent(Enum);
      nameBuffer = moduleNameBuf;
      structNames = *(const char ***)(g_DefgenericCodeGenItem + 20);
      v24 = moduleReopen;
      openedModuleFile = Rules_ConstructCodeFileOpen(moduleFile, fileNameLocal, imageIDLocal, pathNameLocal, &version, moduleArrayVersion, headerFPLocal, (char)aDefgeneric_mod, *structNames, moduleReopen, moduleNameBuf);
      moduleFile = openedModuleFile;
      if ( !openedModuleFile )
        break;
      Defgeneric_ModuleToCode(openedModuleFile, Enum, maxIndices);
      moduleFile = Rules_ConstructCodeFileClose(moduleFile, &moduleCount, maxIndices, &moduleArrayVersion, &moduleReopen, (int)moduleNameBuf);
      for ( i = Defgeneric_GetNextInModule(0); i; i = Defgeneric_GetNextInModule(i) )
      {
        nameBuffer = genericNameBuf;
        openedGenericFile = Rules_ConstructCodeFileOpen(
               genericFile,
               fileNameLocal,
               imageIDLocal,
               pathNameLocal,
               &version,
               genericArrayVersion,
               headerFPLocal,
               (char)aDefgeneric_5,
               *(const char **)(*(_DWORD *)(g_DefgenericCodeGenItem + 20) + 4),
               genericReopen,
               genericNameBuf);
        genericFile = openedGenericFile;
        if ( !openedGenericFile )
          goto LABEL_34;
        Defgeneric_SingleToCode(openedGenericFile, imageIDLocal, i, maxIndices, moduleIndex, methodArrayVersion, methodCount);
        ++genericCount;
        genericFile = Rules_ConstructCodeFileClose(genericFile, &genericCount, maxIndices, &genericArrayVersion, &genericReopen, (int)genericNameBuf);
        if ( *(_DWORD *)(i + 32) )
        {
          nameBuffer = methodNameBuf;
          structNamesForMethod = *(_DWORD *)(g_DefgenericCodeGenItem + 20);
          v24 = methodReopen;
          methodFile = Rules_ConstructCodeFileOpen(methodFile, fileNameLocal, imageIDLocal, pathNameLocal, &version, methodArrayVersion, headerFPLocal, (char)aDefmethod_2, *(const char **)(structNamesForMethod + 8), methodReopen, methodNameBuf);
          if ( !methodFile )
            goto LABEL_34;
          numMethods = *(_DWORD *)(i + 32);
          methodIndex = 0;
          if ( numMethods )
          {
            methodOffset = 0;
            do
            {
              methodPtr = *(_DWORD *)(i + 28) + methodOffset;
              if ( methodIndex )
                Output_WriteFormatted(v11, methodFile, methodFile, (int)asc_50B1FC, (char)moduleNameBuf[0]);
              Defgeneric_MethodToCode(methodFile, imageIDLocal, restrictionArrayVersion, methodPtr, restrictionCount);
              if ( *(int *)(methodPtr + 8) > 0 )
              {
                nameBuffer = restrictionNameBuf;
                structNamesForRestriction = *(_DWORD *)(g_DefgenericCodeGenItem + 20);
                v24 = restrictionReopen;
                restrictionFile = Rules_ConstructCodeFileOpen(
                        restrictionFile,
                        fileNameLocal,
                        imageIDLocal,
                        pathNameLocal,
                        &version,
                        restrictionArrayVersion,
                        headerFPLocal,
                        (char)aRestriction,
                        *(const char **)(structNamesForRestriction + 12),
                        restrictionReopen,
                        restrictionNameBuf);
                if ( !restrictionFile )
                  goto LABEL_34;
                numRestrictions = *(_DWORD *)(methodPtr + 8);
                restrictionIndex = 0;
                if ( numRestrictions )
                {
                  restrictionOffset = 0;
                  do
                  {
                    restrictionPtr = (_DWORD *)(restrictionOffset + *(_DWORD *)(methodPtr + 28));
                    if ( restrictionIndex )
                      Output_WriteFormatted(restrictionIndex, restrictionOffset, restrictionFile, (int)asc_50B1FC, (char)moduleNameBuf[0]);
                    Defgeneric_RestrictionToCode(restrictionFile, imageIDLocal, typeArrayVersion, (int)restrictionPtr, (DWORD)restrictionPtr, typeCount);
                    if ( restrictionPtr[2] )
                    {
                      typeFile = Rules_ConstructCodeFileOpen(
                              typeFile,
                              fileNameLocal,
                              imageIDLocal,
                              pathNameLocal,
                              &version,
                              typeArrayVersion,
                              headerFPLocal,
                              (char)aVoid_1,
                              *(const char **)(*(_DWORD *)(g_DefgenericCodeGenItem + 20) + 16),
                              typeReopen,
                              typeNameBuf);
                      if ( !typeFile )
                        goto LABEL_34;
                      typeIndex = 0;
                      if ( restrictionPtr[2] )
                      {
                        typeOffset = 0;
                        do
                        {
                          if ( typeIndex )
                            Output_WriteFormatted(typeFile, v16, typeFile, (int)asc_50B1FC, (char)moduleNameBuf[0]);
                          ++typeIndex;
                          Defgeneric_RestrictionTypeToCode(typeFile, maxIndices, *(_DWORD *)(typeOffset + *restrictionPtr));
                          typeOffset += 4;
                        }
                        while ( typeIndex < restrictionPtr[2] );
                      }
                      typeCount += restrictionPtr[2];
                      typeFile = Rules_ConstructCodeFileClose(typeFile, (int *)&typeCount, maxIndices, &typeArrayVersion, &typeReopen, (int)typeNameBuf);
                    }
                    restrictionLimit = *(_DWORD *)(methodPtr + 8);
                    restrictionOffset += 12;
                    ++restrictionIndex;
                  }
                  while ( restrictionIndex < restrictionLimit );
                }
                restrictionCount += *(_DWORD *)(methodPtr + 8);
                restrictionFile = Rules_ConstructCodeFileClose(restrictionFile, &restrictionCount, maxIndices, &restrictionArrayVersion, &restrictionReopen, (int)restrictionNameBuf);
              }
              v11 = methodOffset + 40;
              methodLimit = *(_DWORD *)(i + 32);
              methodOffset += 40;
              ++methodIndex;
            }
            while ( methodIndex < methodLimit );
          }
          methodCount += *(_DWORD *)(i + 32);
          methodFile = Rules_ConstructCodeFileClose(methodFile, &methodCount, maxIndices, &methodArrayVersion, &methodReopen, (int)methodNameBuf);
        }
      }
      prevModuleIndex = moduleIndex;
      Enum = Module_NextEnum(Enum);
      moduleIndex = prevModuleIndex + 1;
      ++moduleCount;
      if ( !Enum )
        goto LABEL_33;
    }
LABEL_34:
    Defgeneric_CloseCodeFiles(&moduleFile, &moduleReopen, maxIndices, (int)moduleNameBuf);
    return 0;
  }
  else
  {
LABEL_33:
    Defgeneric_CloseCodeFiles(&moduleFile, &moduleReopen, maxIndices, (int)moduleNameBuf);
    return 1;
  }
}
// 4C8CDF: variable 'v11' is possibly undefined
// 4C8E7A: variable 'v16' is possibly undefined
// 54E8CC: using guessed type int dword_54E8CC;

//----- (004C9070) --------------------------------------------------------
int  Defgeneric_CloseCodeFiles(int *fileHandles, _DWORD *versions, int a3, int a4)
{
  _DWORD *versionPtr; // edi
  int v7; // eax
  int result; // eax
  int v9; // [esp+0h] [ebp-1Ch] BYREF
  int v10; // [esp+4h] [ebp-18h] BYREF
  _DWORD *versionEnd; // [esp+8h] [ebp-14h]
  int offset; // [esp+Ch] [ebp-10h]

  v9 = a3;
  versionPtr = versions;
  offset = a4;
  v10 = 0;
  versionEnd = versions + 5;
  do
  {
    v9 = a3;
    v7 = *fileHandles++;
    *(fileHandles - 1) = Rules_ConstructCodeFileClose(v7, &v9, a3, &v10, versionPtr, offset);
    result = offset + 12;
    ++versionPtr;
    offset += 12;
  }
  while ( versionPtr != versionEnd );
  return result;
}

//----- (004C90D0) --------------------------------------------------------
int  Defgeneric_ModuleToCode(int fp, int theModule, int imageID)
{
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  char v9; // [esp+0h] [ebp-Ch]
  char v10; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(imageID, theModule, fp, (int)asc_50B214, v9);
  Rules_WriteConstructModuleItemHeaderToCode(fp, v4, v5, g_DefgenericModuleItemIndex, *(_DWORD *)(*(_DWORD *)(g_DefgenericCodeGenItem + 20) + 4));
  return Output_WriteFormatted(v7, v6, fp, (int)asc_50B218, v10);
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
int  Defgeneric_SingleToCode(int fp, int imageID, int gfunc, signed int maxIndices, int moduleIndex, int a6, int methodArrayIndex)
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

  Output_WriteFormatted(gfunc, imageID, fp, (int)asc_50B214, v16);
  Rules_WriteConstructHeaderToCode(fp, gfunc, maxIndices, moduleIndex, **(_DWORD **)(g_DefgenericCodeGenItem + 20), *(_DWORD *)(*(_DWORD *)(g_DefgenericCodeGenItem + 20) + 4));
  Output_WriteFormatted(v10, v9, fp, (int)a00_15, v17);
  v12 = *(_DWORD *)(gfunc + 28);
  if ( v12 )
    Output_WriteFormatted(methodArrayIndex, v12, fp, (int)aSD_DD, *(_DWORD *)(*(_DWORD *)(g_DefgenericCodeGenItem + 20) + 8));
  else
    Output_WriteFormatted(v11, 0, fp, (int)aNull_4, v18);
  return Output_WriteFormatted(v14, v13, fp, (int)aU0, *(_DWORD *)(gfunc + 32));
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
int  Defgeneric_MethodToCode(int fp, int imageID, int restrictionArrayIndex, int theMethod, int a5)
{
  DWORD restrictionArrayName; // ebp
  int v7; // edx
  int v8; // ecx
  int v9; // ecx
  int v10; // edx
  int v11; // ecx
  int v13; // edx
  char v14; // [esp+0h] [ebp-Ch]

  restrictionArrayName = *(_DWORD *)theMethod;
  Output_WriteFormatted(restrictionArrayIndex, imageID, fp, (int)aU0DDDDU0, *(_DWORD *)theMethod);
  if ( *(_DWORD *)(theMethod + 28) )
  {
    v13 = *(_DWORD *)(g_DefgenericCodeGenItem + 20);
    restrictionArrayName = *(_DWORD *)(v13 + 12);
    Output_WriteFormatted(v8, v13, fp, (int)aSD_DD_7, restrictionArrayName);
  }
  else
  {
    Output_WriteFormatted(v8, v7, fp, (int)aNull_25, v14);
  }
  Rules_ExpressionToCode(fp, *(__int16 **)(theMethod + 32), v9, restrictionArrayName);
  return Output_WriteFormatted(v11, v10, fp, (int)aNull_26, v14);
}
// 4C91EA: variable 'v8' is possibly undefined
// 4C91EA: variable 'v7' is possibly undefined
// 4C91EA: variable 'v14' is possibly undefined
// 4C91F7: variable 'v9' is possibly undefined
// 4C9202: variable 'v11' is possibly undefined
// 4C9202: variable 'v10' is possibly undefined
// 54E8CC: using guessed type int dword_54E8CC;

//----- (004C9240) --------------------------------------------------------
int  Defgeneric_RestrictionToCode(int fp, int imageID, int typeArrayIndex, int theRestriction, DWORD a5, DWORD maxIndices)
{
  int v7; // edx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  char v12; // [esp+0h] [ebp-Ch]
  char v13; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(typeArrayIndex, imageID, fp, (int)asc_50B214, v12);
  if ( *(_DWORD *)theRestriction )
  {
    a5 = maxIndices;
    Output_WriteFormatted(v8, *(_DWORD *)(g_DefgenericCodeGenItem + 20), fp, (int)aSD_DD_7, *(_DWORD *)(*(_DWORD *)(g_DefgenericCodeGenItem + 20) + 16));
  }
  else
  {
    Output_WriteFormatted(v8, v7, fp, (int)aNull_25, v13);
  }
  Rules_ExpressionToCode(fp, *(__int16 **)(theRestriction + 4), v9, a5);
  return Output_WriteFormatted(v10, *(_DWORD *)(theRestriction + 8), fp, (int)aU, *(_DWORD *)(theRestriction + 8));
}
// 4C924B: variable 'v12' is possibly undefined
// 4C925F: variable 'v8' is possibly undefined
// 4C925F: variable 'v7' is possibly undefined
// 4C925F: variable 'v13' is possibly undefined
// 4C926C: variable 'v9' is possibly undefined
// 4C927B: variable 'v10' is possibly undefined
// 54E8CC: using guessed type int dword_54E8CC;

//----- (004C92B0) --------------------------------------------------------
int  Defgeneric_RestrictionTypeToCode(int fp, int maxIndices, int theClass)
{
  int v4; // edx
  int v5; // ecx
  char v7; // [esp+0h] [ebp-8h]

  Output_WriteFormatted(maxIndices, theClass, fp, (int)aVs_1, v7);
  return ObjectsCompiler_WriteDefclassPointerRef(fp, v4, v5);
}
// 4C92BE: variable 'v7' is possibly undefined
// 4C92CA: variable 'v4' is possibly undefined
// 4C92CA: variable 'v5' is possibly undefined

//----- (004C92E0) --------------------------------------------------------
signed int  Defgeneric_ParseDefgeneric(int readSource)
{
  _DWORD *v3; // edx
  int v4; // ecx
  signed int v5; // ecx
  int v6; // ecx
  char *ppForm; // eax
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
  if ( !Rules_GetConstructNameAndComment(readSource, (int)&g_ClipsMethodParserToken, (int (*)(void))Defgeneric_ParseConstruct, aDefgeneric_1, 0, asc_50B28C, 1, 1, 1)
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
      ppForm = Rules_CopyPPBuffer();
      Rules_ReplaceConstructPPForm(v8, (int)ppForm);
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
signed int  Defgeneric_ParseDefmethod(int readSource)
{
  int v1; // edx
  int genericNameToken; // ecx
  int addedGeneric; // eax
  _DWORD *gfunc; // edi
  signed int *paramsPtr; // edx
  int v7; // edx
  int v8; // ecx
  int i; // esi
  int foundMethod; // eax
  int existingMethod; // esi
  int v12; // ecx
  char *errorMessage; // edx
  int *conflictMethod; // ecx
  int conflictIndex; // edx
  int v16; // ecx
  __int16 *actions; // edx
  char *ppForm; // eax
  int v19; // ecx
  int isNew; // esi
  int *definedMethodPtr; // ecx
  int v22; // ecx
  char *definitionMsg; // edx
  int v24; // ecx
  int v25; // ecx
  signed int methodArrayIndex; // eax
  int v27; // ecx
  int insertPosition; // [esp+0h] [ebp-24h] BYREF
  int isNewGeneric; // [esp+4h] [ebp-20h] BYREF
  unsigned int localVarCount; // [esp+8h] [ebp-1Ch] BYREF
  int restrictions; // [esp+Ch] [ebp-18h]
  int wildcard; // [esp+10h] [ebp-14h] BYREF
  unsigned int methodIndex; // [esp+14h] [ebp-10h] BYREF
  int parameterCount; // [esp+18h] [ebp-Ch]
  int isNewMethod; // [esp+1Ch] [ebp-8h]
  int readSource2; // [esp+20h] [ebp-4h]

  readSource2 = readSource;
  Rules_SetPPBufferStatus(1);
  Rules_FlushPPBuffer();
  Rules_SetIndentDepth(3);
  isNewMethod = v1;
  IO_OutWriteToken(aDefmethod_0);
  if ( Rules_IsBloaded() == 1 )
  {
    Rules_ReportCannotLoadWithBload();
    return 1;
  }
  if ( !Method_ParseIndexModifier(readSource2, &methodIndex) || !Defgeneric_ParseDeclaration() )
    return 1;
  addedGeneric = Defgeneric_AddConstruct(genericNameToken, &isNewGeneric);
  gfunc = (_DWORD *)addedGeneric;
  if ( isNewGeneric )
    Defgeneric_CreateDefaultPPForm(addedGeneric);
  Rules_IncrementIndentDepth(1);
  parameterCount = Method_ParseParameterList(readSource2, paramsPtr, &wildcard);
  Rules_DecrementIndentDepth(1);
  if ( v7 == -1 )
  {
LABEL_9:
    if ( isNewGeneric )
    {
      Rules_UnlinkListNode((int)gfunc);
      Defgeneric_RemoveDefgeneric((int)gfunc);
      return 1;
    }
    return 1;
  }
  AST_Append(v8, v7);
  for ( i = restrictions; i; i = *(_DWORD *)(i + 10) )
  {
    Method_ReplaceCurrentArgumentRefs(*(int ***)(*(_DWORD *)(i + 6) + 4));
    if ( Parser_ReplaceProcVars((int)aMethod, *(_DWORD *)(*(_DWORD *)(i + 6) + 4), wildcard, restrictions, 0, 0) )
      goto LABEL_19;
  }
  foundMethod = Method_FindInsertionIndex((int)gfunc, restrictions, wildcard, parameterCount, (unsigned int *)&insertPosition);
  existingMethod = foundMethod;
  if ( foundMethod )
  {
    if ( (*(_BYTE *)(foundMethod + 24) & 1) != 0 )
    {
      Rules_PrintErrorID((int)aGenrcpsr, 17, 0);
      errorMessage = aCannotReplaceT;
LABEL_17:
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)errorMessage, v12);
      conflictIndex = *conflictMethod;
LABEL_18:
      Rules_PrintLongInteger((int)conflictMethod, conflictIndex);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__12, v16);
LABEL_19:
      Method_FreeRestrictionChain(restrictions);
      goto LABEL_9;
    }
    if ( methodIndex && methodIndex != *(_DWORD *)foundMethod )
    {
      Rules_PrintErrorID((int)aGenrcpsr, 2, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNewMethod, v24);
      Rules_PrintLongInteger(v25, methodIndex);
      errorMessage = aWouldBeIndisti;
      goto LABEL_17;
    }
  }
  else if ( methodIndex )
  {
    methodArrayIndex = Method_FindByIndex((int)gfunc, methodIndex);
    if ( methodArrayIndex == -1 )
    {
      isNewMethod = 1;
    }
    else if ( (*(_BYTE *)(gfunc[7] + 40 * methodArrayIndex + 24) & 1) != 0 )
    {
      Rules_PrintErrorID((int)aGenrcpsr, 17, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotReplaceT, v27);
      conflictIndex = methodIndex;
      goto LABEL_18;
    }
  }
  else
  {
    isNewMethod = 1;
  }
  g_ClipsParseReturnContext = 1;
  if ( !Parser_ParseProcActions((int)aMethod, readSource2, restrictions, wildcard, 0, 0, (int *)&localVarCount, 0) )
    goto LABEL_19;
  IO_OutNewline();
  IO_OutNewline();
  IO_OutWriteToken((char *)g_CLIPS_GenericParseTokenPrintStr);
  IO_OutWriteToken(asc_50B2C4);
  if ( Mem_GetAllocFlag() )
    ppForm = 0;
  else
    ppForm = Rules_CopyPPBuffer();
  Defgeneric_AddMethod(gfunc, existingMethod, methodIndex, insertPosition, restrictions, parameterCount, localVarCount, wildcard, actions, (unsigned int)ppForm, 0);
  Method_FreeRestrictionChain(restrictions);
  if ( Rules_GetLoadInProgress() && Rules_GetWatchCompilations() )
  {
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aMethod_0, v19);
    isNew = isNewMethod;
    Rules_PrintLongInteger((int)definedMethodPtr, *definedMethodPtr);
    if ( isNew )
      definitionMsg = aDefined_;
    else
      definitionMsg = aRedefined_;
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)definitionMsg, v22);
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
        _DWORD *gfunc,
        int existingMethod,
        unsigned int methodIndex,
        int position,
        int restrictions,
        int restrictionCount,
        unsigned int minRestrictions,
        int hasWildcard,
        __int16 *actions,
        unsigned int ppForm,
        int copyRestrictions)
{
  signed int existingIndex; // eax
  int foundIndex; // ebp
  int restrictionMinIndex; // eax
  _DWORD *restrictionArray; // eax
  int v15; // edx
  int restrictionOffset; // ebp
  int restrictionPtr; // ebx
  _DWORD *sourceRestriction; // edx
  int typeCount; // eax
  _DWORD *typeArray; // edi
  int copyTypeCount; // ecx
  const void **v22; // edx
  int typeOffset; // ecx
  int v24; // ecx
  unsigned int typeIndex; // edx
  int forwardIndex; // ebp
  int forwardDest; // edx
  int forwardSrc; // ebx
  int backwardIndex; // ebp
  int backwardDest; // ebx
  int backwardSrc; // edx
  int v33; // edx
  int v34; // edx
  int insertIndex; // [esp+4h] [ebp-24h]
  unsigned int *methodSlot; // [esp+14h] [ebp-14h]

  methodSlot = (unsigned int *)existingMethod;
  insertIndex = position;
  g_Defgeneric_SavedBusyCount = gfunc[5];
  if ( existingMethod )
  {
    AST_DeinstallNodeChain(*(__int16 **)(existingMethod + 32));
    AST_FreePackedNodeChain(*(_DWORD *)(v33 + 32));
    if ( *(_DWORD *)(v34 + 36) )
      Mem_SmallBlockFree((_DWORD *)methodSlot[9], strlen(*(const char **)(v34 + 36)) + 1);
  }
  else if ( methodIndex && (existingIndex = Method_FindByIndex((int)gfunc, methodIndex), foundIndex = existingIndex, existingIndex != -1) )
  {
    Defgeneric_DeleteMethodInfo((int)gfunc, 40 * existingIndex + gfunc[7]);
    if ( foundIndex >= position )
    {
      backwardIndex = foundIndex - 1;
      if ( backwardIndex >= position )
      {
        backwardDest = 40 * backwardIndex + 40;
        backwardSrc = 40 * backwardIndex;
        do
        {
          --backwardIndex;
          qmemcpy((void *)(gfunc[7] + backwardDest), (const void *)(gfunc[7] + backwardSrc), 0x28u);
          backwardSrc -= 40;
          backwardDest -= 40;
        }
        while ( backwardSrc >= 40 * insertIndex );
      }
    }
    else
    {
      forwardIndex = foundIndex + 1;
      insertIndex = position - 1;
      if ( forwardIndex <= position - 1 )
      {
        forwardDest = 40 * forwardIndex - 40;
        forwardSrc = 40 * forwardIndex;
        do
        {
          ++forwardIndex;
          qmemcpy((void *)(forwardDest + gfunc[7]), (const void *)(gfunc[7] + forwardSrc), 0x28u);
          forwardDest += 40;
          forwardSrc += 40;
        }
        while ( forwardDest <= 40 * insertIndex - 40 );
      }
    }
    methodSlot = (unsigned int *)(40 * insertIndex + gfunc[7]);
    *methodSlot = methodIndex;
  }
  else
  {
    methodSlot = Defgeneric_InsertMethodSlot(gfunc, position, methodIndex);
  }
  *((_BYTE *)methodSlot + 24) &= ~1u;
  methodSlot[8] = (unsigned int)actions;
  AST_InstallNodeChain(actions);
  methodSlot[9] = ppForm;
  if ( insertIndex != -1 )
  {
    methodSlot[5] = minRestrictions;
    methodSlot[2] = restrictionCount;
    if ( hasWildcard )
    {
      methodSlot[4] = -1;
      restrictionMinIndex = restrictionCount - 1;
    }
    else
    {
      restrictionMinIndex = restrictionCount;
      methodSlot[4] = restrictionCount;
    }
    methodSlot[3] = restrictionMinIndex;
    if ( restrictionCount )
    {
      restrictionArray = Mem_SmallBlockAlloc(12 * restrictionCount);
      *(_DWORD *)(v15 + 28) = restrictionArray;
    }
    else
    {
      methodSlot[7] = 0;
    }
    if ( restrictionCount > 0 )
    {
      restrictionOffset = 0;
      do
      {
        restrictionPtr = restrictionOffset + methodSlot[7];
        *(_DWORD *)(restrictionPtr + 4) = AST_PackNodeChain(*(_DWORD **)(*(_DWORD *)(restrictions + 6) + 4));
        typeCount = sourceRestriction[2];
        *(_DWORD *)(restrictionPtr + 8) = typeCount;
        if ( copyRestrictions )
        {
          if ( *sourceRestriction )
          {
            typeArray = Mem_SmallBlockAlloc(4 * typeCount);
            copyTypeCount = *(_DWORD *)(restrictionPtr + 8);
            *(_DWORD *)restrictionPtr = typeArray;
            qmemcpy(typeArray, *v22, 4 * copyTypeCount);
          }
          else
          {
            *(_DWORD *)restrictionPtr = 0;
          }
        }
        else
        {
          *(_DWORD *)restrictionPtr = *sourceRestriction;
          sourceRestriction[2] = 0;
          *sourceRestriction = 0;
        }
        AST_InstallNodeChain(*(__int16 **)(restrictionPtr + 4));
        if ( *(_DWORD *)(restrictionPtr + 8) )
        {
          typeOffset = 0;
          do
          {
            Class_AddBusyReference(*(_DWORD *)(typeOffset + *(_DWORD *)restrictionPtr));
            typeOffset = v24 + 4;
          }
          while ( typeIndex < *(_DWORD *)(restrictionPtr + 8) );
        }
        restrictionOffset += 12;
        restrictions = *(_DWORD *)(restrictions + 10);
      }
      while ( restrictionOffset < 12 * restrictionCount );
    }
  }
  gfunc[5] = g_Defgeneric_SavedBusyCount;
  return methodSlot;
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
int  Method_PackRestrictionTypes(_DWORD *restriction, int typeList)
{
  _DWORD *restr; // ecx
  int i; // eax
  int typeCount; // ebx
  _DWORD *typeArray; // eax
  int typeNode; // ebx
  unsigned int typeIndex; // edx
  int offset; // eax

  restr = restriction;
  restriction[2] = 0;
  for ( i = typeList; i; i = *(_DWORD *)(i + 10) )
    ++restr[2];
  typeCount = restr[2];
  if ( typeCount )
  {
    typeArray = Mem_SmallBlockAlloc(4 * typeCount);
    *restr = typeArray;
  }
  else
  {
    *restr = 0;
  }
  typeNode = typeList;
  typeIndex = 0;
  if ( restr[2] )
  {
    offset = 0;
    do
    {
      ++typeIndex;
      *(_DWORD *)(*restr + offset) = *(_DWORD *)(typeNode + 2);
      offset += 4;
      typeNode = *(_DWORD *)(typeNode + 10);
    }
    while ( typeIndex < restr[2] );
  }
  return AST_Free(typeList);
}
// 4C9AB3: variable 'v2' is possibly undefined

//----- (004C9B00) --------------------------------------------------------
int  Method_FreeRestrictionChain(int result)
{
  int i; // ebx
  _DWORD *current; // eax
  int restriction; // ecx
  int v4; // ecx
  int typeCount; // edx

  for ( i = result; i; *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp )
  {
    current = (_DWORD *)i;
    i = *(_DWORD *)(i + 10);
    restriction = *(_DWORD *)((char *)current + 6);
    g_ClipsMemFreeListTemp = (int)current;
    *current = *(_DWORD *)(g_ClipsMemoryTable + 56);
    *(_DWORD *)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
    AST_Free(*(_DWORD *)(restriction + 4));
    typeCount = *(_DWORD *)(v4 + 8);
    if ( typeCount )
      Mem_SmallBlockFree(*(_DWORD **)v4, 4 * typeCount);
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
int  Method_FindInsertionIndex(int gfunc, int params, int wildcardFlag, int restrictionCount, unsigned int *position)
{
  unsigned int methodIndex; // esi
  int methodOffset; // edi
  signed int comparison; // eax
  int maxRestrictions; // [esp+4h] [ebp-18h]
  int minRestrictions; // [esp+8h] [ebp-14h]

  if ( wildcardFlag )
  {
    minRestrictions = restrictionCount - 1;
    maxRestrictions = -1;
  }
  else
  {
    maxRestrictions = restrictionCount;
    minRestrictions = restrictionCount;
  }
  methodIndex = 0;
  if ( *(_DWORD *)(gfunc + 32) )
  {
    methodOffset = 0;
    while ( 1 )
    {
      comparison = Method_CompareRestrictionOrder(params, restrictionCount, maxRestrictions, minRestrictions, (_DWORD *)(methodOffset + *(_DWORD *)(gfunc + 28)));
      if ( !comparison )
        break;
      if ( comparison != -1 )
      {
        ++methodIndex;
        methodOffset += 40;
        if ( methodIndex < *(_DWORD *)(gfunc + 32) )
          continue;
      }
      goto LABEL_8;
    }
    *position = -1;
    return methodOffset + *(_DWORD *)(gfunc + 28);
  }
  else
  {
LABEL_8:
    *position = methodIndex;
    return 0;
  }
}

//----- (004C9C20) --------------------------------------------------------
signed int Defgeneric_ParseDeclaration()
{
  _BYTE *name; // ecx
  int v1; // eax
  _BYTE *v2; // ecx
  int deffunction; // esi
  int currentModule; // eax
  int ownerModule; // ecx
  int v6; // ecx
  int v7; // eax
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int Name; // eax
  int v12; // ecx
  int v14; // ecx
  int v15; // ecx
  int existingGeneric; // eax
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
    v1 = Deffunction_LookupByName(name);
    deffunction = v1;
    if ( v1 )
    {
      Rules_GetConstructOwnerModule(v1);
      currentModule = Module_GetCurrent();
      if ( ownerModule == currentModule )
      {
        Rules_PrintErrorID((int)aGenrcpsr, 5, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDefgenericsA_0, v15);
      }
      else
      {
        Rules_PrintErrorID((int)aGenrcpsr, 4, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDeffunction_0, v6);
        v7 = Rules_GetConstructNameString(deffunction);
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
      existingGeneric = Defgeneric_ParseConstruct(v2, (int)v2);
      if ( existingGeneric && Defgeneric_MethodsExecuting(existingGeneric) )
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
signed int  Defgeneric_CreateDefaultPPForm(int gfunc)
{
  int v2; // eax
  const char *Name; // esi
  const char *genericName; // edx
  _DWORD *ppForm; // eax
  const char *v6; // edx
  int v7; // ecx

  v2 = Module_GetCurrent();
  Name = (const char *)Module_GetName(v2);
  genericName = (const char *)Rules_GetConstructNameString(gfunc);
  ppForm = Mem_SmallBlockAlloc(strlen(genericName) + strlen(Name) + 17);
  sprintf_(ppForm, "(defgeneric %s::%s)\n", Name, v6);
  return Rules_ReplaceConstructPPForm(gfunc, v7);
}
// 4C9DFA: variable 'v6' is possibly undefined
// 4C9E06: variable 'v7' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (004C9E20) --------------------------------------------------------
int  Method_ParseIndexModifier(int readSource, _DWORD *indexOut)
{
  int result; // eax
  int status; // ecx
  int v6; // edx
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int methodIndex; // eax
  int v11; // edx
  int v12; // edx
  int v13; // ecx

  *indexOut = 0;
  result = Rules_GetConstructNameAndComment(readSource, (int)&g_ClipsMethodParserToken, 0, aDefmethod_1, 0, asc_50B47C, 1, 0, 1);
  status = result;
  if ( result )
  {
    if ( g_ClipsMethodParserToken == 1 )
    {
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(asc_50B480);
      IO_OutWriteToken((char *)g_CLIPS_GenericParseTokenPrintStr);
      methodIndex = *(_DWORD *)(g_Clips_CurrentTokenValue + 16);
      if ( methodIndex < v11 )
      {
        Rules_PrintErrorID((int)aGenrcpsr, 6, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aMethodIndexOut, v13);
        return 0;
      }
      *indexOut = methodIndex;
      AST_Append(v9, (int)&g_ClipsMethodParserToken);
      Parser_NextToken(readSource, v12);
    }
    if ( g_ClipsMethodParserToken == 3 )
    {
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(asc_50B480);
      IO_OutWriteToken((char *)g_CLIPS_GenericParseTokenPrintStr);
      AST_Append(v7, v6);
      Parser_NextToken(readSource, v8);
    }
    return status;
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
int  Method_ParseParameterList(int readSource, signed int *paramsOut, int *wildcardOut)
{
  signed int paramList; // esi
  int varName; // ebp
  _DWORD *v6; // edx
  _DWORD *v7; // ecx
  int v8; // ecx
  signed int v9; // eax
  int v10; // edx
  int v11; // ecx
  int v13; // ecx
  int v14; // edx
  int v15; // ecx
  int restrictedVar; // ebp
  int v17; // edx
  int v18; // ecx
  int v19; // edx
  int v20; // ecx
  int lastParam; // [esp+0h] [ebp-20h] BYREF
  signed int *paramsPtr; // [esp+4h] [ebp-1Ch]
  int *wildcardPtr; // [esp+8h] [ebp-18h]
  int paramCount; // [esp+Ch] [ebp-14h]

  paramsPtr = paramsOut;
  wildcardPtr = wildcardOut;
  paramList = 0;
  *wildcardOut = 0;
  *paramsOut = 0;
  paramCount = 0;
  if ( g_ClipsMethodParserToken != 100 )
  {
    Rules_PrintErrorID((int)aGenrcpsr, 7, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedAToBeg, v13);
    return -1;
  }
  Parser_NextToken(readSource, (int)&g_ClipsMethodParserToken);
  while ( g_ClipsMethodParserToken != 101 )
  {
    if ( *wildcardPtr )
    {
      Method_FreeRestrictionChain(paramList);
      Rules_PrintErrorID((int)aPrccode_1, v14, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoParametersAl, v15);
      return -1;
    }
    if ( g_ClipsMethodParserToken == 15 || g_ClipsMethodParserToken == 16 )
    {
      varName = g_Clips_CurrentTokenValue;
      if ( Method_CheckDuplicateParameterName(paramList, &lastParam, g_Clips_CurrentTokenValue) )
        goto LABEL_18;
      if ( g_ClipsMethodParserToken == 16 )
        *wildcardPtr = varName;
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
      v9 = Method_AppendParameterNode(paramList, lastParam, varName);
      v11 = paramCount + 1;
      paramList = v9;
      ++paramCount;
    }
    else
    {
      if ( g_ClipsMethodParserToken != 100 )
      {
        Method_FreeRestrictionChain(paramList);
        Rules_PrintErrorID((int)aGenrcpsr, v19, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedAVar_0, v20);
        return -1;
      }
      Parser_NextToken(readSource, (int)&g_ClipsMethodParserToken);
      if ( g_ClipsMethodParserToken != 15 && g_ClipsMethodParserToken != 16 )
      {
        Method_FreeRestrictionChain(paramList);
        Rules_PrintErrorID((int)aGenrcpsr, v17, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedAVaria, v18);
        return -1;
      }
      restrictedVar = g_Clips_CurrentTokenValue;
      if ( Method_CheckDuplicateParameterName(paramList, &lastParam, g_Clips_CurrentTokenValue) )
        goto LABEL_18;
      if ( g_ClipsMethodParserToken == 16 )
        *wildcardPtr = restrictedVar;
      IO_OutWriteToken(asc_50B480);
      if ( !Method_ParseParameterRestriction(readSource) )
      {
LABEL_18:
        Method_FreeRestrictionChain(paramList);
        return -1;
      }
      paramList = Method_AppendParameterNode(paramList, lastParam, restrictedVar);
      ++paramCount;
    }
    AST_Append(v11, v10);
    Parser_NextToken(readSource, (int)&g_ClipsMethodParserToken);
  }
  if ( paramCount )
  {
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken(asc_50B584);
  }
  *paramsPtr = paramList;
  return paramCount;
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
int  Method_ParseParameterRestriction(int readSource)
{
  int typeList; // edi
  int tokenType; // ecx
  int v4; // edx
  _DWORD *freeNode; // ebp
  _DWORD *restriction; // ecx
  int v7; // ecx
  int v9; // ecx
  signed int newClass; // eax
  int classNode; // esi
  int typeNode; // ebx
  int classIter; // ecx
  int existingClass; // eax
  int candidateClass; // edx
  int v16; // ecx
  int prevType; // eax
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int query; // [esp+0h] [ebp-1Ch]

  Parser_NextToken(readSource, (int)&g_ClipsMethodParserToken);
  typeList = 0;
  tokenType = g_ClipsMethodParserToken;
  query = 0;
  if ( g_ClipsMethodParserToken == 101 )
  {
LABEL_8:
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken(asc_50B584);
    if ( typeList || query )
    {
      freeNode = *(_DWORD **)(g_ClipsMemoryTable + 48);
      if ( freeNode )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
        *(_DWORD *)(g_ClipsMemoryTable + 48) = *freeNode;
        restriction = (_DWORD *)g_ClipsMemFreeListTemp;
      }
      else
      {
        restriction = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0xC);
      }
      restriction[1] = query;
      Method_PackRestrictionTypes(restriction, typeList);
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
    if ( query )
    {
      Rules_PrintErrorID((int)aGenrcpsr, 10, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aQueryMustBeLas, v9);
      AST_Free(query);
      AST_Free(typeList);
      return 0;
    }
    if ( g_ClipsMethodParserToken == 2 )
      break;
    if ( g_ClipsMethodParserToken == 100 )
    {
      query = Parser_ParseExpression(readSource, tokenType);
      if ( !query )
        goto LABEL_30;
      if ( Parser_GetLoopContextStack() )
      {
        Rules_PrintErrorID((int)aGenrcpsr, 12, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aBindsAreNotAll, v19);
        AST_Free(v20);
LABEL_30:
        AST_Free(typeList);
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
        AST_Free(typeList);
        return 0;
      }
      query = AST_NewNode(13, g_Clips_CurrentTokenValue);
    }
LABEL_7:
    IO_OutWriteToken(asc_50B480);
    Parser_NextToken(readSource, v4);
    if ( g_ClipsMethodParserToken == 101 )
      goto LABEL_8;
  }
  newClass = Method_ParseParameterClassName(g_Clips_CurrentTokenValue);
  classNode = newClass;
  if ( !newClass )
  {
    AST_Free(typeList);
    AST_Free(0);
    return 0;
  }
  if ( !typeList )
  {
    typeList = newClass;
    goto LABEL_7;
  }
  typeNode = typeList;
  while ( 1 )
  {
    classIter = classNode;
    if ( classNode )
      break;
LABEL_23:
    prevType = typeNode;
    typeNode = *(_DWORD *)(typeNode + 10);
    if ( !typeNode )
    {
      *(_DWORD *)(prevType + 10) = classNode;
      goto LABEL_7;
    }
  }
  while ( 1 )
  {
    existingClass = *(_DWORD *)(typeNode + 2);
    candidateClass = *(_DWORD *)(classIter + 2);
    if ( existingClass == candidateClass )
      break;
    if ( Method_CheckRedundantClassPair(existingClass, candidateClass) )
      goto LABEL_26;
    classIter = *(_DWORD *)(v16 + 10);
    if ( !classIter )
      goto LABEL_23;
  }
  Rules_PrintErrorID((int)aGenrcpsr, 11, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDuplicateClass, v18);
LABEL_26:
  AST_Free(0);
  AST_Free(typeList);
  AST_Free(classNode);
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
  int node; // ecx

  node = (int)result;
  if ( result )
  {
    do
    {
      if ( *(_WORD *)node == 15 )
      {
        result = (int **)(strcmp_(node, aCurrentArgumen) == 0);
        if ( result )
        {
          *(_WORD *)node = 10;
          result = Rules_MakeSymbol(aGnrcCurrentA_0);
          *(_DWORD *)(node + 2) = result;
        }
      }
      if ( *(_DWORD *)(node + 6) )
        result = (int **)Method_ReplaceCurrentArgumentRefs(*(_DWORD *)(node + 6));
      node = *(_DWORD *)(node + 10);
    }
    while ( node );
  }
  return result;
}
// 4CA44E: variable 'v1' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004CA4A0) --------------------------------------------------------
signed int  Method_CheckDuplicateParameterName(int paramList, _DWORD *lastNode, int name)
{
  int paramName; // ecx
  int v5; // ecx

  *lastNode = 0;
  if ( !paramList )
    return 0;
  while ( 1 )
  {
    paramName = *(_DWORD *)(paramList + 2);
    if ( name == paramName )
      break;
    *lastNode = paramList;
    paramList = *(_DWORD *)(paramList + 10);
    if ( !paramList )
      return 0;
  }
  Rules_PrintErrorID((int)aPrccode_1, 7, paramName ^ name);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDuplicateParam, v5);
  return 1;
}
// 4CA4DA: variable 'v5' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004CA4F0) --------------------------------------------------------
signed int  Method_AppendParameterNode(signed int paramList, int lastNode, int name)
{
  signed int result; // eax
  int v6; // ecx
  signed int newNode; // edx

  result = AST_NewNode(2, name);
  newNode = result;
  if ( paramList )
  {
    *(_DWORD *)(lastNode + 10) = result;
    result = paramList;
    *(_DWORD *)(newNode + 6) = v6;
  }
  else
  {
    *(_DWORD *)(result + 6) = v6;
  }
  return result;
}
// 4CA50C: variable 'v6' is possibly undefined

//----- (004CA520) --------------------------------------------------------
signed int  Method_ParseParameterClassName(int name)
{
  int v1; // edx
  int *theClass; // eax
  int v3; // ecx

  if ( Rules_FindModuleSeparator(*(_BYTE **)(name + 16)) )
  {
    Module_ReportIllegalSpecifierError();
    return 0;
  }
  else
  {
    theClass = Class_LookupInScope(*(_BYTE **)(v1 + 16));
    if ( theClass )
    {
      return AST_NewNode(5, (int)theClass);
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
signed int  Method_CheckRedundantClassPair(int class1, int class2)
{
  int class1Copy; // ecx
  int redundantClass; // eax
  int v5; // ecx
  int v6; // ecx
  signed int result; // eax

  if ( Class_HasSuperclass(class1, class2) )
  {
    redundantClass = class1Copy;
LABEL_3:
    Rules_GetConstructNameString(redundantClass);
    Rules_PrintErrorID((int)aGenrcpsr, 15, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], v5, v5);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aClassIsRedunda, v6);
    return 1;
  }
  result = Class_HasSuperclass(class2, class1Copy);
  if ( result )
  {
    redundantClass = class2;
    goto LABEL_3;
  }
  return result;
}
// 4CA58F: variable 'v3' is possibly undefined
// 4CA5B0: variable 'v5' is possibly undefined
// 4CA5BF: variable 'v6' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004CA5E0) --------------------------------------------------------
int  Defgeneric_AddConstruct(int nameToken, _DWORD *isNew)
{
  int existingGeneric; // eax
  int v4; // ecx
  int genericPtr; // edx
  int v6; // edx
  _DWORD *newGeneric; // eax
  int v9; // ecx

  existingGeneric = Defgeneric_ParseConstruct(*(_BYTE **)(nameToken + 16), nameToken);
  genericPtr = existingGeneric;
  if ( existingGeneric )
  {
    *isNew = 0;
    Rules_UnlinkListNode(existingGeneric);
  }
  else
  {
    *isNew = 1;
    newGeneric = Defgeneric_AllocateRecord(v4);
    ++*(_DWORD *)(v9 + 4);
    Defgeneric_InitializeFromRestrictionString((int)newGeneric, v9);
  }
  Rules_AppendConstructToModuleList(genericPtr);
  return v6;
}
// 4CA601: variable 'v5' is possibly undefined
// 4CA606: variable 'v6' is possibly undefined
// 4CA613: variable 'v4' is possibly undefined
// 4CA618: variable 'v9' is possibly undefined

//----- (004CA640) --------------------------------------------------------
_DWORD * Defgeneric_InsertMethodSlot(_DWORD *gfunc, int position, unsigned int methodIndex)
{
  unsigned int srcIndex; // ebx
  int destIndex; // edx
  int srcOffset; // ebp
  _DWORD *newSlot; // eax
  int nextIndex; // edx
  _DWORD *slot; // edx
  char v9; // al
  char v10; // bl
  int v11; // ebp
  char v12; // bh
  _DWORD *newMethods; // [esp+8h] [ebp-18h]

  newMethods = Mem_SmallBlockAlloc(40 * (gfunc[8] + 1));
  srcIndex = 0;
  destIndex = 0;
  if ( gfunc[8] )
  {
    srcOffset = 0;
    do
    {
      if ( srcIndex == position )
        ++destIndex;
      qmemcpy(&newMethods[10 * destIndex], (const void *)(srcOffset + gfunc[7]), 0x28u);
      ++srcIndex;
      srcOffset += 40;
      ++destIndex;
    }
    while ( srcIndex < gfunc[8] );
  }
  newSlot = &newMethods[10 * position];
  if ( methodIndex )
  {
    *newSlot = methodIndex;
    if ( methodIndex >= gfunc[9] )
      gfunc[9] = methodIndex + 1;
  }
  else
  {
    nextIndex = gfunc[9];
    gfunc[9] = nextIndex + 1;
    *newSlot = nextIndex;
  }
  slot = &newMethods[10 * position];
  slot[1] = 0;
  v9 = g_Rules_WatchMethods;
  slot[3] = 0;
  slot[4] = 0;
  slot[2] = 0;
  v10 = *((_BYTE *)slot + 24);
  slot[5] = 0;
  slot[7] = 0;
  *((_BYTE *)slot + 24) = v10 & 0xFD;
  v11 = slot[6];
  slot[8] = 0;
  slot[6] = (2 * (v9 & 1)) | v11;
  v12 = *((_BYTE *)slot + 24);
  slot[9] = 0;
  *((_BYTE *)slot + 24) = v12 & 0xFE;
  if ( gfunc[8] )
    Mem_SmallBlockFree((_DWORD *)gfunc[7], 40 * gfunc[8]);
  ++gfunc[8];
  gfunc[7] = newMethods;
  return &newMethods[10 * position];
}
// 51B3E4: using guessed type int dword_51B3E4;

//----- (004CA7F0) --------------------------------------------------------
signed int  Method_CompareRestrictionOrder(int params, int restrictionCount, int maxRestrictions, int minRestrictions, _DWORD *method)
{
  int index; // ecx
  int restrictionPtr; // ebx
  int paramRestriction; // esi
  signed int result; // eax
  int v10; // ecx
  int v12; // [esp+4h] [ebp-20h]
  int differs; // [esp+8h] [ebp-1Ch]
  int offset; // [esp+14h] [ebp-10h]

  index = 0;
  differs = 0;
  if ( restrictionCount > 0 )
  {
    offset = 0;
    v12 = restrictionCount - 1;
    while ( index < method[2] )
    {
      if ( index == v12 && maxRestrictions == -1 && method[4] != -1 )
        return 1;
      if ( index == method[2] - 1 && maxRestrictions != -1 && method[4] == -1 )
        return -1;
      restrictionPtr = offset + method[7];
      paramRestriction = *(_DWORD *)(params + 6);
      result = Method_CompareTypeArrays((_DWORD *)paramRestriction, (_DWORD *)restrictionPtr);
      if ( result )
        return result;
      if ( !*(_DWORD *)(paramRestriction + 4) && *(_DWORD *)(restrictionPtr + 4) )
        return 1;
      if ( *(_DWORD *)(paramRestriction + 4) && !*(_DWORD *)(restrictionPtr + 4) )
        return -1;
      if ( !AST_NodeListsEqual(*(__int16 **)(paramRestriction + 4), *(__int16 **)(restrictionPtr + 4)) )
        differs = 1;
      index = v10 + 1;
      params = *(_DWORD *)(params + 10);
      offset += 12;
      if ( index >= restrictionCount )
        break;
    }
  }
  if ( restrictionCount == method[2] )
    return differs != 0;
  if ( minRestrictions <= method[3] && maxRestrictions == -1 )
    return 1;
  return -1;
}
// 4CA8B6: variable 'v10' is possibly undefined

//----- (004CA920) --------------------------------------------------------
signed int  Method_CompareTypeArrays(_DWORD *types1, _DWORD *types2)
{
  unsigned int index; // ebx
  int offset; // ecx
  int *type1; // eax
  int *type2; // edx
  unsigned int count1; // eax
  unsigned int count2; // edx
  int v11; // ecx
  int differs; // [esp+0h] [ebp-18h]

  differs = 0;
  if ( !types1[2] && !types2[2] )
    return 0;
  if ( !types1[2] )
    return 1;
  if ( types2[2] )
  {
    index = 0;
    offset = 0;
    while ( index < types2[2] )
    {
      type1 = (int *)(offset + *types1);
      type2 = (int *)(offset + *types2);
      if ( *type1 != *type2 )
      {
        differs = 1;
        if ( Class_HasSuperclass(*type1, *type2) )
          return -1;
        if ( Class_HasSuperclass(*(_DWORD *)(v11 + *types2), *(_DWORD *)(v11 + *types1)) )
          return 1;
      }
      ++index;
      offset += 4;
      if ( index >= types1[2] )
        break;
    }
    count1 = types1[2];
    count2 = types2[2];
    if ( count1 < count2 )
      return -1;
    return count1 > count2 || differs;
  }
  return -1;
}
// 4CA94F: conditional instruction was optimized away because ebp.4!=0
// 4CA96A: variable 'v5' is possibly undefined
// 4CA9C6: variable 'v11' is possibly undefined

//----- (004CA9E0) --------------------------------------------------------
_DWORD * Defgeneric_AllocateRecord(int name)
{
  _DWORD *v2; // edx
  _DWORD *gfunc; // ecx
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
  Rules_InitConstructModuleRecord((int)aDefgeneric_1, name);
  gfunc[5] = 0;
  gfunc[9] = 1;
  gfunc[7] = 0;
  gfunc[8] = 0;
  result = gfunc;
  gfunc[6] = g_Rules_WatchGenericFunctions;
  return result;
}
// 4CAA15: variable 'v3' is possibly undefined
// 51B3E0: using guessed type int dword_51B3E0;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004CAA50) --------------------------------------------------------
int  Method_DispatchGenericCall(
        int gfunc,
        int prevMethod,
        _DWORD *params,
        int *theMethod,
        double a5,
        _DWORD *returnValue)
{
  int result; // eax
  int genericName; // ebx
  int argCount; // eax
  int v11; // ecx
  int v12; // edx
  int v13; // eax
  int v14; // ecx
  int v15; // edx
  int genericNameStr; // eax
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int genericNameStrForError; // eax
  int v23; // ecx
  int v24; // ecx
  __int16 callExpr; // [esp+0h] [ebp-34h] BYREF
  int v26; // [esp+2h] [ebp-32h]
  int argExprChain; // [esp+6h] [ebp-2Eh]
  int v28; // [esp+Ah] [ebp-2Ah]
  int savedReentryFlag; // [esp+10h] [ebp-24h]
  int prevMethodArg; // [esp+14h] [ebp-20h]
  int oldGeneric; // [esp+18h] [ebp-1Ch]
  _DWORD *argExpressions; // [esp+1Ch] [ebp-18h]
  int oldMethod; // [esp+20h] [ebp-14h]
  int oldReentryFlag; // [esp+24h] [ebp-10h]

  prevMethodArg = prevMethod;
  argExpressions = params;
  returnValue[1] = 2;
  result = g_ClipsFalseSymbol;
  returnValue[2] = g_ClipsFalseSymbol;
  g_ClipsEvaluationError = 0;
  if ( !g_ClipsHaltExecution )
  {
    oldReentryFlag = Rules_GetReentryGuardFlag();
    savedReentryFlag = oldReentryFlag;
    Rules_SetReentryGuardFlag(1);
    oldGeneric = g_ClipsCurrentGeneric;
    g_ClipsCurrentGeneric = gfunc;
    ++g_ClipsCurrentEvaluationDepth;
    oldMethod = g_ClipsCurrentMethod;
    ++*(_DWORD *)(gfunc + 20);
    genericName = Rules_GetConstructNameString(gfunc);
    argCount = AST_CountListNodes((int)argExpressions);
    ProcParam_PushEvaluatedArgumentFrame(argExpressions, argCount, v11, genericName, a5, (int (*)(void))Method_PrintCallErrorBanner);
    if ( g_ClipsEvaluationError )
    {
      v13 = oldGeneric;
      --*(_DWORD *)(gfunc + 20);
      g_ClipsCurrentGeneric = v13;
      g_ClipsCurrentMethod = oldMethod;
      --g_ClipsCurrentEvaluationDepth;
      Rules_RunPeriodicCleanup(0, 1);
      return Rules_SetReentryGuardFlag(oldReentryFlag);
    }
    else
    {
      if ( theMethod )
      {
        if ( Method_RestrictionsSatisfiedByArgs((int)theMethod, a5) )
        {
          ++theMethod[1];
          g_ClipsCurrentMethod = (int)theMethod;
        }
        else
        {
          Rules_PrintErrorID((int)aGenrcexe, 4, 0);
          Lexer_ErrorRecover(1);
          g_ClipsCurrentMethod = v14;
          Output_Write((int)g_IO_LogicalNameTable_WError[0], v15, v14);
          genericNameStr = Rules_GetConstructNameString(gfunc);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], genericNameStr, v17);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aMethod_2, v18);
          Rules_PrintLongInteger(v19, *theMethod);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIsNotApplicabl, v20);
        }
      }
      else
      {
        g_ClipsCurrentMethod = Method_FindApplicableMethod(gfunc, prevMethodArg, a5);
      }
      if ( g_ClipsCurrentMethod )
      {
        if ( *(_DWORD *)(g_ClipsCurrentGeneric + 24) )
          Method_PrintGenericCallTrace((int)asc_50B73C);
        if ( (*(_BYTE *)(g_ClipsCurrentMethod + 24) & 2) != 0 )
          Method_PrintMethodCallTrace((int)asc_50B73C);
        if ( (*(_BYTE *)(g_ClipsCurrentMethod + 24) & 1) != 0 )
        {
          callExpr = 10;
          v26 = *(_DWORD *)(*(_DWORD *)(g_ClipsCurrentMethod + 32) + 2);
          v28 = 0;
          argExprChain = ProcParam_BuildArgumentExpressionChain();
          Parser_ParseForm(&callExpr, returnValue, 0, a5);
        }
        else
        {
          Rules_ExecuteRuleActions(
            **(_DWORD **)(g_ClipsCurrentGeneric + 8),
            *(__int16 **)(g_ClipsCurrentMethod + 32),
            returnValue,
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
        genericNameStrForError = Rules_GetConstructNameString(gfunc);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], genericNameStrForError, v23);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__24, v24);
        Lexer_ErrorRecover(1);
      }
      --*(_DWORD *)(gfunc + 20);
      g_ClipsHaltExecutionFlag = 0;
      ProcParam_PopFrame();
      g_ClipsCurrentGeneric = oldGeneric;
      g_ClipsCurrentMethod = oldMethod;
      --g_ClipsCurrentEvaluationDepth;
      Rules_PropagateReturnValueDepth((int)returnValue);
      Rules_RunPeriodicCleanup(0, v12);
      return Rules_SetReentryGuardFlag(savedReentryFlag);
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
int  Method_RestrictionsSatisfiedByArgs(int method, double a2)
{
  int v2; // ecx
  int i; // ebp
  int restriction; // ebx
  int result; // eax
  unsigned int classIndex; // esi
  int *v7; // eax
  _DWORD *v8; // eax
  bool v9; // zf
  int v10; // edx
  int v11; // [esp+0h] [ebp-44h] BYREF
  __int64 v12; // [esp+4h] [ebp-40h]
  int methodBase; // [esp+18h] [ebp-2Ch]
  int restrictionIndex; // [esp+1Ch] [ebp-28h]
  int restrictionOffset; // [esp+20h] [ebp-24h]
  int argIndex; // [esp+24h] [ebp-20h]
  int argClass; // [esp+28h] [ebp-1Ch]

  methodBase = method;
  v2 = *(_DWORD *)(method + 12);
  if ( g_ClipsProcParamCount < v2 || g_ClipsProcParamCount > v2 && *(_DWORD *)(method + 16) != -1 )
    return 0;
  argIndex = 0;
  restrictionIndex = 0;
  if ( g_ClipsProcParamCount > 0 )
  {
    restrictionOffset = 0;
    for ( i = 0; ; i += 24 )
    {
      restriction = restrictionOffset + *(_DWORD *)(methodBase + 28);
      if ( !*(_DWORD *)(restriction + 8) )
        goto LABEL_7;
      result = Method_GetArgumentClass(i + g_ClipsProcParamArray);
      argClass = result;
      if ( !result )
        return result;
      classIndex = 0;
      if ( *(_DWORD *)(restriction + 8) )
        break;
LABEL_19:
      if ( classIndex == *(_DWORD *)(restriction + 8) )
        return 0;
LABEL_7:
      if ( *(_DWORD *)(restriction + 4) )
      {
        g_Method_CurrentArgParamPtr = i + g_ClipsProcParamArray;
        Parser_ParseForm(*(__int16 **)(restriction + 4), &v11, v2, a2);
        if ( v12 == __PAIR64__(g_ClipsFalseSymbol, 2) )
          return 0;
      }
      if ( *(_DWORD *)(methodBase + 8) - 1 != restrictionIndex )
      {
        ++restrictionIndex;
        restrictionOffset += 12;
      }
      v2 = g_ClipsProcParamCount;
      if ( ++argIndex >= g_ClipsProcParamCount )
        return 1;
    }
    v2 = 0;
    while ( 1 )
    {
      v7 = (int *)(v2 + *(_DWORD *)restriction);
      if ( argClass == *v7 || Class_HasSuperclass(argClass, *v7) )
        goto LABEL_19;
      v8 = (_DWORD *)(v2 + *(_DWORD *)restriction);
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
      ++classIndex;
      v2 += 4;
      if ( classIndex >= *(_DWORD *)(restriction + 8) )
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
  int nextMethod; // edx

  if ( !g_ClipsCurrentMethod )
    return 0;
  result = Method_FindApplicableMethod(g_ClipsCurrentGeneric, g_ClipsCurrentMethod, a1);
  nextMethod = result;
  if ( result )
  {
    result = 1;
    --*(_DWORD *)(nextMethod + 4);
  }
  return result;
}
// 51B3D4: using guessed type int dword_51B3D4;
// 51B3D8: using guessed type int dword_51B3D8;

//----- (004CAFC0) --------------------------------------------------------
int  Method_OverrideNextMethod(_DWORD *returnValue, int a2, double a3)
{
  _DWORD *returnValuePtr; // ecx
  int result; // eax
  int savedMethod; // esi
  int v6; // ecx
  __int16 callExpr; // [esp+0h] [ebp-20h] BYREF
  int v8; // [esp+2h] [ebp-1Eh]
  int v9; // [esp+6h] [ebp-1Ah]
  int v10; // [esp+Ah] [ebp-16h]
  int v11; // [esp+18h] [ebp-8h]

  v11 = a2;
  returnValuePtr = returnValue;
  returnValue[1] = 2;
  result = g_ClipsFalseSymbol;
  returnValuePtr[2] = g_ClipsFalseSymbol;
  if ( !g_ClipsHaltExecution )
  {
    savedMethod = g_ClipsCurrentMethod;
    if ( g_ClipsCurrentMethod )
      g_ClipsCurrentMethod = Method_FindApplicableMethod(g_ClipsCurrentGeneric, g_ClipsCurrentMethod, a3);
    if ( g_ClipsCurrentMethod )
    {
      if ( (*(_BYTE *)(g_ClipsCurrentMethod + 24) & 2) != 0 )
        Method_PrintMethodCallTrace((int)asc_50B73C);
      if ( (*(_BYTE *)(g_ClipsCurrentMethod + 24) & 1) != 0 )
      {
        callExpr = 10;
        v8 = *(_DWORD *)(*(_DWORD *)(g_ClipsCurrentMethod + 32) + 2);
        v10 = 0;
        v9 = ProcParam_BuildArgumentExpressionChain();
        Parser_ParseForm(&callExpr, returnValuePtr, (int)returnValuePtr, a3);
      }
      else
      {
        Rules_ExecuteRuleActions(
          **(_DWORD **)(g_ClipsCurrentGeneric + 8),
          *(__int16 **)(g_ClipsCurrentMethod + 32),
          returnValuePtr,
          *(_DWORD *)(g_ClipsCurrentMethod + 20),
          a3,
          (void (*)(void))Method_PrintCallErrorBanner);
      }
      --*(_DWORD *)(g_ClipsCurrentMethod + 4);
      if ( (*(_BYTE *)(g_ClipsCurrentMethod + 24) & 2) != 0 )
        Method_PrintMethodCallTrace((int)asc_50B740);
      result = 0;
      g_ClipsCurrentMethod = savedMethod;
      g_ClipsHaltExecutionFlag = 0;
    }
    else
    {
      g_ClipsCurrentMethod = savedMethod;
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
signed int  Method_EvaluateCallSpecificMethod(_DWORD *returnValue, double a2)
{
  signed int result; // eax
  int generic; // esi
  int methodByteOffset; // ebp
  _DWORD argBuffer[2]; // [esp+0h] [ebp-30h] BYREF
  int v7; // [esp+8h] [ebp-28h]

  returnValue[1] = 2;
  returnValue[2] = g_ClipsFalseSymbol;
  result = Lexer_ParseValueList(1, argBuffer, 2, a2);
  if ( result )
  {
    result = Defgeneric_CheckGenericExists((int)aCallSpecific_0, *(_BYTE **)(v7 + 16));
    generic = result;
    if ( result )
    {
      result = Lexer_ParseValueList(2, argBuffer, 1, a2);
      if ( result )
      {
        result = Defgeneric_CheckMethodExists((int)aCallSpecific_0, generic, *(_DWORD *)(v7 + 16));
        if ( result != -1 )
        {
          methodByteOffset = 40 * result;
          ++*(_DWORD *)(*(_DWORD *)(generic + 28) + 40 * result + 4);
          Method_DispatchGenericCall(
            generic,
            0,
            *(_DWORD **)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10),
            (int *)(40 * result + *(_DWORD *)(generic + 28)),
            a2,
            returnValue);
          result = *(_DWORD *)(generic + 28);
          --*(_DWORD *)(result + methodByteOffset + 4);
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
int  Method_FindApplicableMethod(int generic, int startMethod, double a3)
{
  int genericPtr; // ecx
  unsigned int candidate; // edx
  int matchedMethod; // edx
  int savedBusyCount; // ebp

  genericPtr = generic;
  if ( startMethod )
    candidate = startMethod + 40;
  else
    candidate = *(_DWORD *)(generic + 28);
  while ( 1 )
  {
    if ( candidate >= 40 * *(_DWORD *)(genericPtr + 32) + *(_DWORD *)(genericPtr + 28) )
      return 0;
    ++*(_DWORD *)(candidate + 4);
    if ( Method_RestrictionsSatisfiedByArgs(candidate, a3) )
      break;
    savedBusyCount = *(_DWORD *)(matchedMethod + 4);
    candidate = matchedMethod + 40;
    *(_DWORD *)(candidate - 36) = savedBusyCount - 1;
  }
  return matchedMethod;
}
// 4CB28D: variable 'v3' is possibly undefined
// 4CB2B8: variable 'v6' is possibly undefined

//----- (004CB2D0) --------------------------------------------------------
signed int  Method_PrintGenericCallTrace(int a1)
{
  int v1; // ecx
  int v2; // ecx
  int currentModule; // eax
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
  currentModule = Module_GetCurrent();
  if ( currentModule != *v5 )
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
  int currentModule; // eax
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
  currentModule = Module_GetCurrent();
  if ( currentModule != *v5 )
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
int  Method_GetArgumentClass(int argParam)
{
  int argType; // edx
  _DWORD *instancePtr; // eax
  int classPtr; // esi
  int v4; // edx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int genericNameString; // eax
  int v9; // ecx

  argType = *(_DWORD *)(argParam + 4);
  if ( argType != 8 )
  {
    if ( argType != 7 )
      return g_ClipsPrimitiveTypeClassMap[argType];
    instancePtr = *(_DWORD **)(argParam + 8);
    if ( (instancePtr[6] & 2) == 0 )
      goto LABEL_4;
LABEL_9:
    classPtr = 0;
    goto LABEL_5;
  }
  instancePtr = Instance_FindByName(*(_DWORD *)(argParam + 8));
  if ( !instancePtr )
    goto LABEL_9;
LABEL_4:
  classPtr = instancePtr[11];
LABEL_5:
  if ( !classPtr )
  {
    Lexer_ErrorRecover(1);
    Rules_PrintErrorID((int)aGenrcexe, v4, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnableToDeterm, v5);
    Rules_PrintDataObject((int)g_IO_LogicalNameTable_WError[0], v6);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInGenericFunct, v7);
    genericNameString = Rules_GetConstructNameString(g_ClipsCurrentGeneric);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], genericNameString, (int)g_IO_LogicalNameTable_WError[0]);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__24, v9);
  }
  return classPtr;
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
int  Deffunction_WriteConstructReference(int filePtr, int a2, int maxIndices)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( a2 )
    return Output_WriteFormatted(
             maxIndices,
             *(_DWORD *)(*(_DWORD *)(g_DeffunctionCodeGeneratorItem + 20) + 4),
             filePtr,
             (int)aSD_DD_0,
             *(_DWORD *)(*(_DWORD *)(g_DeffunctionCodeGeneratorItem + 20) + 4));
  else
    return Output_WriteFormatted(maxIndices, 0, filePtr, (int)aNull_5, v4);
}
// 4CB5A0: variable 'v4' is possibly undefined
// 54E8DC: using guessed type int dword_54E8DC;

//----- (004CB5E0) --------------------------------------------------------
int  Deffunction_WriteModuleItemReference(int filePtr, int a2)
{
  return Output_WriteFormatted(a2, **(_DWORD **)(g_DeffunctionCodeGeneratorItem + 20), filePtr, (int)aMihsSD_DD_0, **(_DWORD **)(g_DeffunctionCodeGeneratorItem + 20));
}
// 54E8DC: using guessed type int dword_54E8DC;

//----- (004CB620) --------------------------------------------------------
signed int Deffunction_RegisterModuleItemAssigner()
{
  return Rules_RegisterModuleItemIdAssigner();
}
// 54E6A8: using guessed type int dword_54E6A8;

//----- (004CB630) --------------------------------------------------------
int  Deffunction_WriteConstructCodeFiles(const char *fileName, const char *pathName, int fileID, int headerFP, int maxIndices)
{
  int codeFP; // esi
  int v6; // ecx
  int openedModuleFile; // eax
  int v8; // ecx
  int v9; // edi
  int theDeffunction; // edi
  int openedDeffunctionFile; // eax
  int v12; // ecx
  int v13; // esi
  int prevModuleCount; // ebx
  int fileCount; // [esp+0h] [ebp-3Ch] BYREF
  int moduleArrayCount; // [esp+4h] [ebp-38h] BYREF
  int moduleArrayVersion; // [esp+8h] [ebp-34h] BYREF
  int deffunctionArrayCount; // [esp+Ch] [ebp-30h] BYREF
  int deffunctionArrayVersion; // [esp+10h] [ebp-2Ch] BYREF
  int moduleFile; // [esp+14h] [ebp-28h]
  int Enum; // [esp+18h] [ebp-24h]
  const char *v23; // [esp+1Ch] [ebp-20h]
  const char *v24; // [esp+20h] [ebp-1Ch]
  int v25; // [esp+24h] [ebp-18h]
  int moduleCount; // [esp+28h] [ebp-14h]
  int v27; // [esp+2Ch] [ebp-10h]

  v23 = fileName;
  v24 = pathName;
  v25 = headerFP;
  v27 = fileID;
  moduleCount = 0;
  moduleArrayCount = 0;
  moduleArrayVersion = 1;
  deffunctionArrayCount = 0;
  deffunctionArrayVersion = 1;
  moduleFile = 0;
  Output_WriteFormatted(0, 1, headerFP, (int)aIncludeDffnxfu, 1);
  codeFP = 0;
  Enum = Module_NextEnum(0);
  if ( Enum )
  {
    while ( 1 )
    {
      Module_SetCurrent(Enum);
      openedModuleFile = Rules_ConstructCodeFileOpen(
             moduleFile,
             v23,
             v27,
             v24,
             &fileCount,
             moduleArrayVersion,
             v25,
             (char)aDeffunction_mo,
             **(const char ***)(g_DeffunctionCodeGeneratorItem + 20),
             0,
             0);
      v9 = openedModuleFile;
      if ( !openedModuleFile )
      {
        Deffunction_CloseCodeFiles(0, codeFP, v8, maxIndices);
        return 0;
      }
      Deffunction_WriteConstructHeader(openedModuleFile, Enum, maxIndices);
      moduleFile = Rules_ConstructCodeFileClose(v9, &moduleArrayCount, maxIndices, &moduleArrayVersion, 0, 0);
      theDeffunction = Deffunction_EnumNext(0);
      if ( theDeffunction )
        break;
LABEL_6:
      prevModuleCount = moduleCount;
      Enum = Module_NextEnum(Enum);
      moduleCount = prevModuleCount + 1;
      ++moduleArrayCount;
      if ( !Enum )
        goto LABEL_7;
    }
    while ( 1 )
    {
      openedDeffunctionFile = Rules_ConstructCodeFileOpen(
              codeFP,
              v23,
              v27,
              v24,
              &fileCount,
              deffunctionArrayVersion,
              v25,
              (char)aDeffunction_8,
              *(const char **)(*(_DWORD *)(g_DeffunctionCodeGeneratorItem + 20) + 4),
              0,
              0);
      v13 = openedDeffunctionFile;
      if ( !openedDeffunctionFile )
        break;
      Deffunction_WriteConstructBody(openedDeffunctionFile, theDeffunction, maxIndices, moduleCount);
      ++deffunctionArrayCount;
      codeFP = Rules_ConstructCodeFileClose(v13, &deffunctionArrayCount, maxIndices, &deffunctionArrayVersion, 0, 0);
      theDeffunction = Deffunction_EnumNext(theDeffunction);
      if ( !theDeffunction )
        goto LABEL_6;
    }
    Deffunction_CloseCodeFiles(moduleFile, 0, v12, maxIndices);
    return 0;
  }
  else
  {
LABEL_7:
    Deffunction_CloseCodeFiles(moduleFile, codeFP, v6, maxIndices);
    return 1;
  }
}
// 4CB7C9: variable 'v6' is possibly undefined
// 4CB7E0: variable 'v8' is possibly undefined
// 4CB7F8: variable 'v12' is possibly undefined
// 54E8DC: using guessed type int dword_54E8DC;

//----- (004CB810) --------------------------------------------------------
int  Deffunction_CloseCodeFiles(int headerFP, int codeFP, int a3, int maxIndices)
{
  int result; // eax
  int v6; // [esp+0h] [ebp-14h] BYREF
  _DWORD v7[4]; // [esp+4h] [ebp-10h] BYREF

  v7[3] = a3;
  result = codeFP;
  v6 = maxIndices;
  v7[0] = 0;
  if ( codeFP )
  {
    result = Rules_ConstructCodeFileClose(codeFP, &v6, maxIndices, v7, 0, 0);
    if ( !headerFP )
      return result;
    goto LABEL_5;
  }
  if ( headerFP )
  {
LABEL_5:
    v6 = maxIndices;
    return Rules_ConstructCodeFileClose(headerFP, &v6, maxIndices, v7, 0, 0);
  }
  return result;
}

//----- (004CB870) --------------------------------------------------------
int  Deffunction_WriteConstructHeader(int filePtr, int theModule, int maxIndices)
{
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  char v9; // [esp+0h] [ebp-Ch]
  char v10; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(maxIndices, theModule, filePtr, (int)asc_50B89C, v9);
  Rules_WriteConstructModuleItemHeaderToCode(filePtr, v4, v5, g_Clips_DeffunctionModuleItemIndex, *(_DWORD *)(*(_DWORD *)(g_DeffunctionCodeGeneratorItem + 20) + 4));
  return Output_WriteFormatted(v7, v6, filePtr, (int)asc_50B8A0, v10);
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
int  Deffunction_WriteConstructBody(int filePtr, int deffunction, int maxIndices, int moduleCount)
{
  int *v6; // eax
  DWORD moduleImage; // ebp
  signed int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  char v15; // [esp+0h] [ebp-Ch]
  char v16; // [esp+0h] [ebp-Ch]
  char v17; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(maxIndices, deffunction, filePtr, (int)asc_50B89C, v15);
  v6 = *(int **)(g_DeffunctionCodeGeneratorItem + 20);
  moduleImage = *v6;
  Rules_WriteConstructHeaderToCode(filePtr, deffunction, v8, moduleCount, *v6, v6[1]);
  Output_WriteFormatted(v10, v9, filePtr, (int)a000_0, v16);
  Rules_ExpressionToCode(filePtr, *(__int16 **)(deffunction + 30), v11, moduleImage);
  Output_WriteFormatted(*(_DWORD *)(deffunction + 38), *(_DWORD *)(deffunction + 42), filePtr, (int)aDDD, *(_DWORD *)(deffunction + 34));
  return Output_WriteFormatted(v13, v12, filePtr, (int)asc_50B8A0, v17);
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
int  Deffunction_ParseConstruct(int readSource)
{
  int (*v2)(void); // edx
  int deffunctionName; // edi
  int parameterList; // esi
  int v6; // edx
  int v7; // ecx
  __int16 *v8; // edx
  int v9; // [esp+0h] [ebp-30h] BYREF
  int minParams; // [esp+4h] [ebp-2Ch] BYREF
  int maxParams; // [esp+8h] [ebp-28h] BYREF
  int v12; // [esp+Ch] [ebp-24h] BYREF
  int errorFlag; // [esp+10h] [ebp-20h] BYREF
  int deffunction; // [esp+14h] [ebp-1Ch]

  errorFlag = 0;
  Rules_SetPPBufferStatus(1);
  Rules_FlushPPBuffer();
  Rules_SetIndentDepth(3);
  IO_OutWriteToken(aDeffunction_3);
  if ( Rules_IsBloaded() == 1 )
  {
    Rules_ReportCannotLoadWithBload();
    return 1;
  }
  deffunctionName = Rules_GetConstructNameAndComment(readSource, (int)g_Rules_ParsedConstructNameComment, (int (*)(void))Deffunction_FindByName, aDeffunction_4, v2, asc_50B8D8, 1, 1, 1);
  if ( !deffunctionName )
    return 1;
  if ( !Deffunction_ValidateNewName() )
    return 1;
  parameterList = Parser_ParseProcParameters(readSource, g_Rules_ParsedConstructNameComment, &v9, 0, &minParams, &maxParams, &errorFlag, 0);
  if ( errorFlag )
    return 1;
  deffunction = Deffunction_AddDeffunction(deffunctionName, 0, maxParams, minParams, 0, 1);
  if ( deffunction )
  {
    AST_Append(v7, v6);
    g_ClipsParseReturnContext = 1;
    if ( !Parser_ParseProcActions((int)aDeffunction_4, readSource, parameterList, v9, 0, 0, &v12, 0) )
    {
      AST_Free(parameterList);
      if ( !*(_DWORD *)(deffunction + 20) )
      {
        Rules_UnlinkListNode(deffunction);
        Deffunction_Free(deffunction);
        return 1;
      }
      return 1;
    }
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken((char *)g_Clips_DeffunctionEchoToken);
    IO_OutWriteToken(asc_50B8E8);
    Deffunction_AddDeffunction(deffunctionName, v8, maxParams, minParams, v12, 0);
    AST_Free(parameterList);
    return errorFlag;
  }
  else
  {
    AST_Free(parameterList);
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
  int conflictingGeneric; // eax
  _BYTE *v3; // edx
  int conflictModule; // esi
  int v5; // ecx
  int v6; // ecx
  int v7; // eax
  int v8; // ecx
  int Name; // eax
  int v10; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int existingDeffunction; // eax
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
    conflictingGeneric = Defgeneric_LookupLocalOnly(v1);
    if ( conflictingGeneric )
    {
      conflictModule = *(_DWORD *)Rules_GetConstructOwnerModule(conflictingGeneric);
      if ( conflictModule == Module_GetCurrent() )
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
        Name = Module_GetName(conflictModule);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], Name, (int)g_IO_LogicalNameTable_WError[0]);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aConflictsWit_0, v10);
      }
      return 0;
    }
    else
    {
      existingDeffunction = Deffunction_FindByName(v3, 0);
      if ( existingDeffunction && *(_DWORD *)(existingDeffunction + 24) )
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
int  Deffunction_AddDeffunction(int name, __int16 *actions, int maxParams, int minParams, int numLocalVars, int headerFlag)
{
  int existingDeffunction; // eax
  int v9; // edx
  int deffunction; // esi
  _DWORD *freeListItem; // ebx
  _DWORD *newDeffunction; // ecx
  int v13; // edx
  __int16 watchValue; // ax
  int v16; // ecx
  __int16 *oldCode; // eax
  int v18; // ecx
  int oldPackedCode; // eax
  int v20; // edx
  signed int v21; // ecx
  int v22; // ecx
  char *ppForm; // eax
  int watchFlag; // [esp+4h] [ebp-14h]

  existingDeffunction = Deffunction_FindByName(*(_BYTE **)(name + 16), maxParams);
  watchFlag = v9;
  deffunction = existingDeffunction;
  if ( existingDeffunction )
  {
    watchFlag = Deffunction_GetWatchFlagField(existingDeffunction);
    *(_DWORD *)(v16 + 38) = maxParams;
    *(_DWORD *)(v16 + 42) = numLocalVars;
    oldCode = *(__int16 **)(v16 + 30);
    *(_DWORD *)(v16 + 34) = minParams;
    AST_DeinstallNodeChain(oldCode);
    oldPackedCode = *(_DWORD *)(v18 + 30);
    *(_DWORD *)(v18 + 20) = v20;
    AST_FreePackedNodeChain(oldPackedCode);
    *(_DWORD *)(v21 + 30) = 0;
    Rules_ReplaceConstructPPForm(v21, 0);
    Rules_UnlinkListNode(v22);
  }
  else
  {
    freeListItem = *(_DWORD **)(g_ClipsMemoryTable + 184);
    if ( freeListItem )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 184);
      *(_DWORD *)(g_ClipsMemoryTable + 184) = *freeListItem;
    }
    else
    {
      Mem_HeapAllocWithRetry((_DWORD *)0x2E);
    }
    Rules_InitConstructModuleRecord((int)aDeffunction_4, name);
    ++*(_DWORD *)(name + 4);
    *(_DWORD *)((char *)newDeffunction + 30) = 0;
    newDeffunction[5] = 0;
    newDeffunction[6] = 0;
    *(_DWORD *)((char *)newDeffunction + 34) = minParams;
    *(_DWORD *)((char *)newDeffunction + 38) = maxParams;
    deffunction = (int)newDeffunction;
    *(_DWORD *)((char *)newDeffunction + 42) = numLocalVars;
  }
  Rules_AppendConstructToModuleList(deffunction);
  if ( actions )
  {
    AST_InstallNodeChain(actions);
    *(_DWORD *)(deffunction + 20) = v13;
    *(_DWORD *)(deffunction + 30) = actions;
  }
  if ( watchFlag )
    watchValue = 1;
  else
    watchValue = g_Rules_WatchDeffunctions;
  Deffunction_SetWatchFlagField(watchValue, deffunction);
  if ( Mem_GetAllocFlag() || headerFlag )
    return deffunction;
  ppForm = Rules_CopyPPBuffer();
  Rules_ReplaceConstructPPForm(deffunction, (int)ppForm);
  return deffunction;
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
int  Deffunction_CallDeffunction(int deffunction, _DWORD *argExprs, _DWORD *returnValue, double a4)
{
  int result; // eax
  int v8; // eax
  int nameString; // ebx
  int argCount; // eax
  int v11; // ecx
  int v12; // edx
  int savedDeffunction; // [esp+4h] [ebp-18h]
  int savedReentryFlag; // [esp+8h] [ebp-14h]

  returnValue[1] = 2;
  result = g_ClipsFalseSymbol;
  returnValue[2] = g_ClipsFalseSymbol;
  g_ClipsEvaluationError = 0;
  if ( !g_ClipsHaltExecution )
  {
    savedReentryFlag = Rules_GetReentryGuardFlag();
    Rules_SetReentryGuardFlag(1);
    v8 = g_CurrentDeffunction;
    g_CurrentDeffunction = deffunction;
    ++g_ClipsCurrentEvaluationDepth;
    savedDeffunction = v8;
    ++*(_DWORD *)(deffunction + 24);
    nameString = Rules_GetConstructNameString(deffunction);
    argCount = AST_CountListNodes((int)argExprs);
    ProcParam_PushEvaluatedArgumentFrame(argExprs, argCount, v11, nameString, a4, (int (*)(void))Deffunction_PrintErrorContext);
    if ( g_ClipsEvaluationError )
    {
      --*(_DWORD *)(deffunction + 24);
      g_CurrentDeffunction = savedDeffunction;
      --g_ClipsCurrentEvaluationDepth;
      Rules_RunPeriodicCleanup(0, 1);
      return Rules_SetReentryGuardFlag(savedReentryFlag);
    }
    else
    {
      if ( *(_WORD *)(deffunction + 28) )
        Deffunction_PrintCallTrace((int)asc_50BA48);
      Rules_ExecuteRuleActions(
        **(_DWORD **)(deffunction + 8),
        *(__int16 **)(deffunction + 30),
        returnValue,
        *(_DWORD *)(deffunction + 42),
        a4,
        (void (*)(void))Deffunction_PrintErrorContext);
      if ( *(_WORD *)(deffunction + 28) )
        Deffunction_PrintCallTrace((int)asc_50BA4C);
      LODWORD(g_ClipsHaltExecutionFlag) = 0;
      --*(_DWORD *)(deffunction + 24);
      ProcParam_PopFrame();
      g_CurrentDeffunction = savedDeffunction;
      --g_ClipsCurrentEvaluationDepth;
      Rules_PropagateReturnValueDepth((int)returnValue);
      Rules_RunPeriodicCleanup(0, v12);
      return Rules_SetReentryGuardFlag(savedReentryFlag);
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
  int currentModule; // eax
  int v3; // ecx
  _DWORD *v4; // edx
  int v5; // ecx
  int v6; // ecx
  int Name; // eax
  int v9; // ecx

  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)aDfn, a1);
  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], v1, v1);
  currentModule = Module_GetCurrent();
  if ( currentModule != *v4 )
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
int  Defglobal_ResetSingleDefglobal(int defglobal, int a2, double a3)
{
  _DWORD valueBuffer[6]; // [esp+0h] [ebp-18h] BYREF

  (void)a2;
  if ( Parser_ParseForm((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(defglobal + 52), valueBuffer, defglobal, a3) )
  {
    valueBuffer[1] = 2;
    valueBuffer[2] = g_ClipsFalseSymbol;
  }
  return Defglobal_SetValue(defglobal, valueBuffer, 0, a3);
}
// 54DD70: using guessed type int dword_54DD70;

//----- (004CC170) --------------------------------------------------------
int  Defglobal_SaveDefglobals(signed int logicalName)
{
  return Rules_SaveConstruct(logicalName, g_ClipsDefglobalConstructType);
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
_DWORD * Defglobal_GetDefglobalListCommand(int returnValue, double a2)
{
  return Rules_GetConstructListCommand(returnValue, g_ClipsDefglobalConstructType, a2);
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
int  Defglobal_ListDefglobalsCommand(int logicalName, double a2)
{
  return Rules_ListConstructsCommand(g_ClipsDefglobalConstructType, logicalName, a2);
}
// 54E6B4: using guessed type int dword_54E6B4;

//----- (004CC280) --------------------------------------------------------
int  Defglobal_GetWatchFlagField(int defglobal)
{
  return *(_DWORD *)(defglobal + 20) & 1;
}

//----- (004CC290) --------------------------------------------------------
int  Defglobal_SetWatchFlagField(char newState, int defglobal)
{
  int result; // eax

  *(_BYTE *)(defglobal + 20) &= ~1u;
  result = newState & 1;
  *(_DWORD *)(defglobal + 20) |= result;
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
  int tokenType; // eax
  int v4; // ecx
  int v5; // esi
  int v7; // [esp-4h] [ebp-28h] BYREF
  __int64 argValue; // [esp+0h] [ebp-24h]
  int v9; // [esp+1Ch] [ebp-8h]

  v9 = a1;
  tokenType = Lexer_TokenExpect(1);
  v5 = v4;
  if ( tokenType == -1 )
    return v4;
  Rules_RtnUnknown(1, &v7, a2);
  g_DefglobalResetGlobalsFlag = argValue != __PAIR64__(g_ClipsFalseSymbol, 2);
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
  int tokenType; // eax
  int v4; // ecx
  int v5; // eax
  int v6; // ecx
  int *moduleArg; // edx
  _DWORD v8[4]; // [esp+0h] [ebp-10h] BYREF

  v8[2] = a1;
  v8[1] = a3;
  tokenType = Lexer_TokenExpect(1);
  if ( tokenType != -1 )
  {
    if ( tokenType == 1 )
    {
      moduleArg = Rules_GetModuleNameArg(1, v4, v8, a2);
      if ( !v8[0] )
        Defglobal_ShowDefglobalsForModules(0, (int)moduleArg);
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
void __fastcall Defglobal_ShowDefglobalsForModules(int a1, int theModule)
{
  int Enum; // edi
  int printModuleName; // esi
  int Name; // eax
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int defglobal; // ebx
  int v9; // ecx

  Enum = theModule;
  printModuleName = 0;
  if ( !theModule )
  {
    printModuleName = 1;
    Enum = Module_NextEnum(0);
  }
  while ( Enum )
  {
    if ( printModuleName )
    {
      Name = Module_GetName(Enum);
      Output_Write(v5, Name, v5);
      Output_Write(v6, (int)asc_50BBE4, v6);
    }
    defglobal = *(_DWORD *)(Module_GetItem(Enum, g_ClipsDefglobalModuleItemId) + 4);
    if ( defglobal )
    {
      while ( g_ClipsHaltExecution != 1 )
      {
        if ( printModuleName )
          Output_Write(v7, (int)asc_50BBE8, v7);
        Defglobal_PrintDefglobalValue(v7, defglobal);
        Output_Write(v9, (int)asc_50BBEC, v9);
        defglobal = *(_DWORD *)(defglobal + 16);
        if ( !defglobal )
          goto LABEL_11;
      }
      return;
    }
LABEL_11:
    if ( !printModuleName )
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
signed int  Defglobal_PrintDefglobalValue(int logicalName, int defglobal)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx

  Output_Write(logicalName, (int)aDefglobalVariablePrefix, logicalName);
  Output_Write(v3, *(_DWORD *)(*(_DWORD *)defglobal + 16), v3);
  Output_Write(v4, (int)asc_50BBF4, v4);
  return Rules_PrintDataObject(v5, defglobal + 28);
}
// 4CC547: variable 'v3' is possibly undefined
// 4CC553: variable 'v4' is possibly undefined
// 4CC55D: variable 'v5' is possibly undefined

//----- (004CC570) --------------------------------------------------------
int  Defglobal_ParseDefglobalConstruct(int readSource, double a2)
{
  int tokenPrimed; // ebx
  int v5; // eax
  char *Name; // eax
  int v7; // eax
  char *v8; // eax
  int v10; // ecx
  int v11; // edx
  int tokenType; // [esp+0h] [ebp-1Ch] BYREF
  int v13; // [esp+4h] [ebp-18h]
  char *v14; // [esp+8h] [ebp-14h]
  _DWORD constructError[4]; // [esp+Ch] [ebp-10h] BYREF

  tokenPrimed = 1;
  constructError[0] = 0;
  Rules_SetPPBufferStatus(1);
  Rules_FlushPPBuffer();
  Rules_SetIndentDepth(3);
  IO_OutWriteToken(aDefglobal_5);
  if ( Rules_IsBloaded() == 1 )
  {
    Rules_ReportCannotLoadWithBload();
    return 1;
  }
  Parser_NextToken(readSource, (int)&tokenType);
  if ( tokenType == 2 )
  {
    tokenPrimed = 0;
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
  while ( Lexer_ParseDefglobal(readSource, constructError, &tokenType, tokenPrimed, a2) )
  {
    Rules_FlushPPBuffer();
    IO_OutWriteToken(aDefglobal_5);
    v7 = Module_GetCurrent();
    v8 = (char *)Module_GetName(v7);
    IO_OutWriteToken(v8);
    tokenPrimed = 0;
    IO_OutWriteToken(asc_50BC20);
  }
  return constructError[0];
}
// 4CC671: variable 'v11' is possibly undefined
// 4CC69D: variable 'v10' is possibly undefined

//----- (004CC6C0) --------------------------------------------------------
int  Lexer_ParseDefglobal(int readSource, _DWORD *errorFlag, _DWORD *token, int tokenPrimed, double a5)
{
  int globalSymbol; // ebp
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
  __int16 *valueExpr; // ebx
  _DWORD *v20; // edx
  int v21; // ecx
  int v22; // edx

  if ( !tokenPrimed )
    Parser_NextToken(readSource, (int)token);
  if ( *token == 101 )
    return 0;
  if ( *token != 13 )
    goto LABEL_16;
  globalSymbol = token[1];
  IO_OutWriteToken(asc_50BC20);
  if ( Rules_GetWatchItemState((int)aCompilations) == 1 && Rules_GetLoadInProgress() )
  {
    if ( Defglobal_FindNextChanged() )
      v9 = aRedefiningDefg;
    else
      v9 = aDefiningDefglo;
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)v9, v8);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], *(_DWORD *)(globalSymbol + 16), v10);
    v12 = asc_50BC64;
    goto LABEL_10;
  }
  if ( Rules_GetLoadInProgress() )
  {
    v12 = asc_50BC68;
LABEL_10:
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)v12, v11);
  }
  v13 = *(_BYTE **)(globalSymbol + 16);
  v14 = Module_GetCurrent();
  if ( Rules_FindImportExportConflict(aDefglobal_2, v14, v13) )
  {
    Lexer_WarnImpliedTemplate((int)aDefglobal_2, *(_DWORD *)(globalSymbol + 16), 0);
    *errorFlag = 1;
    return 0;
  }
  Parser_NextToken(readSource, v15);
  if ( strcmp_(v16, asc_50BC6C) )
  {
LABEL_16:
    Parser_ReportSyntaxError();
    *errorFlag = 1;
    return 0;
  }
  IO_OutWriteToken(asc_50BC20);
  result = Parser_ParseSingleExpression(readSource, 0, v17);
  valueExpr = (__int16 *)result;
  if ( result )
  {
    Lexer_ErrorRecover(0);
    if ( Parser_ParseForm(valueExpr, v20, v21, a5) )
    {
      AST_Free((int)valueExpr);
      *errorFlag = 1;
      return 0;
    }
    else
    {
      IO_OutWriteToken(asc_50BC70);
      Defglobal_AddDefglobal(globalSymbol, v22, valueExpr);
      return 1;
    }
  }
  else
  {
    *errorFlag = 1;
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
char * Defglobal_AddDefglobal(int globalName, int valueData, __int16 *valueExpr)
{
  int *foundDefglobal; // eax
  int *existingDefglobal; // ebx
  int isNew; // ebp
  _DWORD *freeList; // ebx
  signed int allocatedStruct; // eax
  _DWORD *defglobal; // ecx
  int v11; // ecx
  int valueType; // eax
  int v13; // edx
  int v14; // ecx
  __int16 *v15; // eax
  int v16; // ecx
  _BYTE *v17; // edx
  _DWORD *v18; // ecx
  char watchValue; // al
  char *result; // eax
  int v21; // ecx
  int moduleItem; // eax
  int whichModule; // eax
  int v24; // ecx
  int watchFlag; // [esp+0h] [ebp-14h]

  foundDefglobal = Defglobal_FindNextChanged();
  existingDefglobal = foundDefglobal;
  isNew = 0;
  watchFlag = 0;
  if ( foundDefglobal )
  {
    Rules_FreeConstructHeaderString(foundDefglobal, (int)foundDefglobal);
    watchFlag = existingDefglobal[5] & 1;
  }
  else
  {
    freeList = *(_DWORD **)(g_ClipsMemoryTable + 224);
    isNew = 1;
    if ( freeList )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 224);
      *(_DWORD *)(g_ClipsMemoryTable + 224) = *freeList;
      allocatedStruct = g_ClipsMemFreeListTemp;
    }
    else
    {
      allocatedStruct = Mem_HeapAllocWithRetry((_DWORD *)0x38);
    }
    defglobal = (_DWORD *)allocatedStruct;
  }
  if ( !isNew )
  {
    Rules_ValueDeinstall((int)(defglobal + 7), (int)defglobal);
    if ( *(_DWORD *)(v11 + 32) == 4 )
      Rules_ReturnMultifieldToPool(*(_DWORD **)(v11 + 36));
    AST_RemoveHashedNodeChain(*(__int16 **)(v11 + 52), v11);
  }
  valueType = *(_DWORD *)(valueData + 4);
  defglobal[8] = valueType;
  if ( valueType == 4 )
    Rules_AssignMultifieldRangeCopy(defglobal + 7, valueData);
  else
    defglobal[9] = *(_DWORD *)(valueData + 8);
  Rules_ValueInstall((int)(defglobal + 7), (int)defglobal);
  v15 = AST_AddHashedNodeChain(valueExpr, v13, v14);
  *(_DWORD *)(v16 + 52) = v15;
  AST_Free((int)valueExpr);
  g_Defglobal_ChangedFlag = 1;
  if ( watchFlag )
    watchValue = 1;
  else
    watchValue = g_Rules_WatchGlobals;
  *v17 &= ~1u;
  *(_DWORD *)v17 |= watchValue & 1;
  *v18 = globalName;
  ++*(_DWORD *)(globalName + 4);
  IO_OutWriteToken(asc_50BC64);
  result = (char *)Mem_GetAllocFlag();
  if ( result != (char *)1 )
  {
    result = Rules_CopyPPBuffer();
    *(_DWORD *)(v21 + 4) = result;
    *(_BYTE *)(v21 + 20) |= 2u;
    if ( !isNew )
      return result;
    goto LABEL_21;
  }
  *(_DWORD *)(v21 + 4) = 0;
  *(_BYTE *)(v21 + 20) |= 2u;
  if ( isNew )
  {
LABEL_21:
    *(_DWORD *)(v21 + 24) = 0;
    moduleItem = Module_FindItemByName((int)aDefglobal_2);
    whichModule = Module_GetItem(0, *(_DWORD *)(moduleItem + 4));
    *(_DWORD *)(v24 + 8) = whichModule;
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
signed int  Defglobal_ResolveGlobalVariableReference(int exprNode, int a2)
{
  int defglobal; // eax
  _DWORD lookupBuffer[5]; // [esp+0h] [ebp-14h] BYREF

  lookupBuffer[3] = a2;
  defglobal = Rules_FindImportExportConstruct(aDefglobal_2, lookupBuffer, *(_BYTE **)(*(_DWORD *)(exprNode + 2) + 16), 1, 0);
  if ( defglobal )
  {
    if ( lookupBuffer[0] > 1 )
    {
      Rules_ReportAmbiguousReferenceError((int)aDefglobal_2, *(_DWORD *)(*(_DWORD *)(exprNode + 2) + 16));
      return 0;
    }
    else
    {
      *(_WORD *)exprNode = 60;
      *(_DWORD *)(exprNode + 2) = defglobal;
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
int Defglobals_ResetCallback(int filePtr)
{
  return ((int (__cdecl *)(int, const char *))Output_WriteFormatted)(filePtr, "   ResetDefglobals();\n");
}

//----- (004CCAF0) --------------------------------------------------------
int  Defglobal_WriteConstructsToCCode(const char *fileName, const char *pathName, int fileID, int headerFP, int maxIndices)
{
  int codeFP; // esi
  int v6; // ecx
  int openedModuleFile; // eax
  int v8; // ecx
  int v9; // edi
  int theDefglobal; // edi
  int openedDefglobalFile; // eax
  int v12; // ecx
  int v13; // esi
  int fileCount; // [esp+0h] [ebp-3Ch] BYREF
  int moduleArrayCount; // [esp+4h] [ebp-38h] BYREF
  int moduleArrayVersion; // [esp+8h] [ebp-34h] BYREF
  int defglobalArrayCount; // [esp+Ch] [ebp-30h] BYREF
  int defglobalArrayVersion; // [esp+10h] [ebp-2Ch] BYREF
  int moduleFile; // [esp+14h] [ebp-28h]
  int Enum; // [esp+18h] [ebp-24h]
  const char *v22; // [esp+1Ch] [ebp-20h]
  const char *v23; // [esp+20h] [ebp-1Ch]
  int v24; // [esp+24h] [ebp-18h]
  int moduleCount; // [esp+28h] [ebp-14h]
  int v26; // [esp+2Ch] [ebp-10h]

  v22 = fileName;
  v23 = pathName;
  v24 = headerFP;
  v26 = fileID;
  moduleCount = 0;
  moduleArrayCount = 0;
  moduleArrayVersion = 1;
  defglobalArrayCount = 0;
  defglobalArrayVersion = 1;
  moduleFile = 0;
  Output_WriteFormatted(0, 1, headerFP, (int)aIncludeGloblde, 1);
  codeFP = 0;
  Enum = Module_NextEnum(0);
  if ( Enum )
  {
    while ( 1 )
    {
      Module_SetCurrent(Enum);
      openedModuleFile = Rules_ConstructCodeFileOpen(
             moduleFile,
             v22,
             v26,
             v23,
             &fileCount,
             moduleArrayVersion,
             v24,
             (char)aStructDefgloba,
             **(const char ***)(g_ClipsDefglobalCodeGenItem + 20),
             0,
             0);
      v9 = openedModuleFile;
      if ( !openedModuleFile )
      {
        Defglobal_CloseConstructCodeFiles(0, codeFP, v8, maxIndices);
        return 0;
      }
      Defglobal_WriteModuleHeaderToCode(openedModuleFile, Enum, maxIndices, moduleCount);
      moduleFile = Rules_ConstructCodeFileClose(v9, &moduleArrayCount, maxIndices, &moduleArrayVersion, 0, 0);
      theDefglobal = Defglobal_EnumNext(0);
      if ( theDefglobal )
        break;
LABEL_6:
      ++moduleCount;
      ++moduleArrayCount;
      Enum = Module_NextEnum(Enum);
      if ( !Enum )
        goto LABEL_7;
    }
    while ( 1 )
    {
      openedDefglobalFile = Rules_ConstructCodeFileOpen(
              codeFP,
              v22,
              v26,
              v23,
              &fileCount,
              defglobalArrayVersion,
              v24,
              (char)aStructDefglo_0,
              *(const char **)(*(_DWORD *)(g_ClipsDefglobalCodeGenItem + 20) + 4),
              0,
              0);
      v13 = openedDefglobalFile;
      if ( !openedDefglobalFile )
        break;
      Defglobal_WriteDefglobalEntryToCode(openedDefglobalFile, theDefglobal, maxIndices, v26, moduleCount);
      ++defglobalArrayCount;
      codeFP = Rules_ConstructCodeFileClose(v13, &defglobalArrayCount, maxIndices, &defglobalArrayVersion, 0, 0);
      theDefglobal = Defglobal_EnumNext(theDefglobal);
      if ( !theDefglobal )
        goto LABEL_6;
    }
    Defglobal_CloseConstructCodeFiles(moduleFile, 0, v12, maxIndices);
    return 0;
  }
  else
  {
LABEL_7:
    Defglobal_CloseConstructCodeFiles(moduleFile, codeFP, v6, maxIndices);
    return 1;
  }
}
// 4CCC90: variable 'v6' is possibly undefined
// 4CCCA7: variable 'v8' is possibly undefined
// 4CCCBF: variable 'v12' is possibly undefined
// 54E8EC: using guessed type int dword_54E8EC;

//----- (004CCCD0) --------------------------------------------------------
int  Defglobal_CloseConstructCodeFiles(int headerFP, int codeFP, int a3, int maxIndices)
{
  int result; // eax
  int v6; // [esp+0h] [ebp-14h] BYREF
  _DWORD v7[4]; // [esp+4h] [ebp-10h] BYREF

  v7[3] = a3;
  result = codeFP;
  v6 = maxIndices;
  v7[0] = 0;
  if ( codeFP )
  {
    result = Rules_ConstructCodeFileClose(codeFP, &v6, maxIndices, v7, 0, 0);
    if ( !headerFP )
      return result;
    goto LABEL_5;
  }
  if ( headerFP )
  {
LABEL_5:
    v6 = maxIndices;
    return Rules_ConstructCodeFileClose(headerFP, &v6, maxIndices, v7, 0, 0);
  }
  return result;
}

//----- (004CCD30) --------------------------------------------------------
int  Defglobal_WriteModuleHeaderToCode(int filePtr, int theModule, int maxIndices, int moduleCount)
{
  int v5; // edx
  int v6; // ecx
  int v7; // edx
  int v8; // ecx
  char v10; // [esp+0h] [ebp-Ch]
  char v11; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(maxIndices, theModule, filePtr, (int)asc_50BD24, v10);
  Rules_WriteConstructModuleItemHeaderToCode(filePtr, v5, v6, g_ClipsDefglobalModuleItemId, *(_DWORD *)(*(_DWORD *)(g_ClipsDefglobalCodeGenItem + 20) + 4));
  return Output_WriteFormatted(v8, v7, filePtr, (int)asc_50BD28, v11);
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
int  Defglobal_WriteDefglobalEntryToCode(int filePtr, int defglobal, int maxIndices, char a4, int moduleCount)
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

  Output_WriteFormatted(maxIndices, defglobal, filePtr, (int)asc_50BD24, a4);
  Rules_WriteConstructHeaderToCode(filePtr, defglobal, maxIndices, moduleCount, **(_DWORD **)(g_ClipsDefglobalCodeGenItem + 20), *(_DWORD *)(*(_DWORD *)(g_ClipsDefglobalCodeGenItem + 20) + 4));
  Output_WriteFormatted(v9, v8, filePtr, (int)asc_50BD2C, v19);
  Output_WriteFormatted(v11, v10, filePtr, (int)a00Ld, *(_DWORD *)(defglobal + 24));
  Output_WriteFormatted(v13, v12, filePtr, (int)aNullRvoid, v20);
  Output_WriteFormatted(maxIndices, v14, filePtr, (int)asc_50BD2C, v21);
  Rules_WriteExpressionRefToCode(filePtr, *(__int16 **)(defglobal + 52), v15, v22);
  return Output_WriteFormatted(v17, v16, filePtr, (int)asc_50BD28, v22);
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
int  Defglobal_WriteModuleItemHeaderReference(int filePtr, int a2)
{
  return Output_WriteFormatted(a2, **(_DWORD **)(g_ClipsDefglobalCodeGenItem + 20), filePtr, (int)aMihsSD_DD_6, **(_DWORD **)(g_ClipsDefglobalCodeGenItem + 20));
}
// 54E8EC: using guessed type int dword_54E8EC;

//----- (004CCE70) --------------------------------------------------------
int  Defglobal_WriteDefglobalArrayReference(int filePtr, int defglobalIndex, int maxIndices)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( defglobalIndex )
    return Output_WriteFormatted(
             maxIndices,
             *(_DWORD *)(*(_DWORD *)(g_ClipsDefglobalCodeGenItem + 20) + 4),
             filePtr,
             (int)aSD_LdLd_0,
             *(_DWORD *)(*(_DWORD *)(g_ClipsDefglobalCodeGenItem + 20) + 4));
  else
    return Output_WriteFormatted(maxIndices, 0, filePtr, (int)aNull_6, v4);
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
int  MessageHandler_EnumNext(int classPtr, int handlerIndex)
{
  if ( !handlerIndex )
    return *(_DWORD *)(classPtr + 88) != 0;
  if ( handlerIndex == *(_DWORD *)(classPtr + 96) )
    return 0;
  return handlerIndex + 1;
}

//----- (004CD1C0) --------------------------------------------------------
_BYTE * MessageHandler_SetWatchFlagField(char newState, int classPtr, int handlerIndex)
{
  _BYTE *result; // eax

  result = (_BYTE *)(*(_DWORD *)(classPtr + 88) + 36 * (handlerIndex - 1));
  *result &= ~0x10u;
  *(_DWORD *)result |= 16 * (newState & 1);
  return result;
}

//----- (004CD270) --------------------------------------------------------
int  MessageHandler_UndefineCommand(int a1, double a2)
{
  int result; // eax
  int v3; // ecx
  int v4; // ecx
  int *classPtr; // edi
  int v6; // ecx
  signed int *v7; // esi
  int v8; // ecx
  char *typeName; // ebx
  int v10; // ecx
  _DWORD v11[2]; // [esp-8h] [ebp-2Ch] BYREF
  signed int *parseBuffer; // [esp+0h] [ebp-24h]
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
    classPtr = Class_LookupByQualifiedName((_BYTE *)parseBuffer[4]);
    if ( !classPtr && strcmp_(v4, asc_50BFD4) )
      return Class_ReportLookupError(v6, parseBuffer[4]);
    result = Lexer_ParseValueList(2, v11, 2, a2);
    if ( result )
    {
      v7 = parseBuffer;
      if ( Rules_RtnArgCount() != 3 )
      {
        typeName = g_MessageHandler_PrimaryAfterTypeNames[0];
        return MessageHandler_UndefineForClassOrAll(classPtr, v7, v8, (int)typeName);
      }
      result = Lexer_ParseValueList(3, v11, 2, a2);
      if ( result )
      {
        typeName = (char *)parseBuffer[4];
        if ( strcmp_(v10, asc_50BFD4) )
          return MessageHandler_UndefineForClassOrAll(classPtr, v7, v8, (int)typeName);
        return MessageHandler_UndefineForClassOrAll(classPtr, v7, v8, 0);
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
  int *classPtr; // edi
  int *classNameSymbol; // ebp
  _DWORD *v4; // ecx
  int *handlerNameSymbol; // esi
  signed int handlerType; // ebx
  _DWORD *handler; // edx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  _DWORD parseBuffer[2]; // [esp+0h] [ebp-30h] BYREF
  int v16; // [esp+8h] [ebp-28h]

  result = Lexer_ParseValueList(1, parseBuffer, 2, a1);
  classPtr = 0;
  if ( result )
  {
    classNameSymbol = Rules_FindSymbolEntry(*(_BYTE **)(v16 + 16));
    result = Lexer_ParseValueList(2, v4, 2, a1);
    if ( result )
    {
      handlerNameSymbol = Rules_FindSymbolEntry(*(_BYTE **)(v16 + 16));
      if ( Rules_RtnArgCount() != 3 || (result = Lexer_ParseValueList(3, parseBuffer, 2, a1)) != 0 )
      {
        handlerType = MessageHandler_TypeIndexFromKeyword((int)aPpdefmessageHa);
        if ( handlerType == 4 )
        {
          return Lexer_ErrorRecover(1);
        }
        else
        {
          if ( classNameSymbol )
            classPtr = Class_LookupByQualifiedName((_BYTE *)classNameSymbol[4]);
          if ( classPtr && handlerNameSymbol && (handler = Class_FindMessageHandler(classPtr, (int)handlerNameSymbol, handlerType), result = handler == 0, handler) )
          {
            if ( handler[8] )
              return Output_WriteLongString((signed int)g_IO_LogicalName_WDisplay, (char *)handler[8]);
          }
          else
          {
            Rules_PrintErrorID((int)aMsgcom, 2, 0);
            Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnableToFind_0, v8);
            Output_Write((int)g_IO_LogicalNameTable_WError[0], handlerNameSymbol[4], v9);
            Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_50C030, v10);
            Output_Write((int)g_IO_LogicalNameTable_WError[0], v11, v11);
            Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aForClass, v12);
            Output_Write((int)g_IO_LogicalNameTable_WError[0], classNameSymbol[4], v13);
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
  int classArg[3]; // [esp+0h] [ebp-Ch] BYREF

  if ( !Rules_RtnArgCount() )
    return (int *)MessageHandler_PrintHandlerListTally((int)g_IO_LogicalName_WDisplay, 0, v1, 0);
  result = Class_ParseClassNameAndInheritFlag((int)aListDefmessage, classArg, a1);
  if ( result )
    return (int *)MessageHandler_PrintHandlerListTally((int)g_IO_LogicalName_WDisplay, (int)result, (int)g_IO_LogicalName_WDisplay, classArg[0]);
  return result;
}
// 4CD61D: variable 'v1' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (004CD640) --------------------------------------------------------
int * MessageHandler_PreviewSendCommand(int a1, double a2)
{
  int *result; // eax
  int v3; // ecx
  _DWORD parseBuffer[2]; // [esp-8h] [ebp-28h] BYREF
  int argSlot; // [esp+0h] [ebp-20h]
  int v6; // [esp+18h] [ebp-8h]

  v6 = a1;
  result = (int *)Lexer_ParseValueList(1, parseBuffer, 2, a2);
  if ( result )
  {
    if ( Class_LookupByQualifiedName(*(_BYTE **)(argSlot + 16)) )
    {
      result = (int *)Lexer_ParseValueList(2, parseBuffer, 2, a2);
      if ( result )
        return MessageHandler_PreviewSendForSymbol((int)g_IO_LogicalName_WDisplay, *(_BYTE **)(argSlot + 16));
    }
    else
    {
      return (int *)Class_ReportLookupError(v3, *(_DWORD *)(argSlot + 16));
    }
  }
  return result;
}
// 4CD6B9: variable 'v3' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (004CD6D0) --------------------------------------------------------
int  MessageHandler_GetRecordPPForm(int classPtr, int handlerIndex)
{
  return *(_DWORD *)(*(_DWORD *)(classPtr + 88) + 36 * (handlerIndex - 1) + 32);
}

//----- (004CD6F0) --------------------------------------------------------
int  MessageHandler_PrintHandlerListTally(int logicalName, int classPtr, int a3, int inheritFlag)
{
  unsigned __int16 *v5; // edx
  int handlerCount; // edi
  int v8; // ecx
  unsigned __int16 v9; // [esp+0h] [ebp-18h] BYREF
  int *v10; // [esp+2h] [ebp-16h]
  int classFrame[4]; // [esp+8h] [ebp-10h] BYREF

  classFrame[3] = a3;
  if ( classPtr )
  {
    classFrame[0] = classPtr;
    if ( inheritFlag )
    {
      v5 = (unsigned __int16 *)(classPtr + 46);
    }
    else
    {
      v5 = &v9;
      v9 = 1;
      v10 = classFrame;
    }
    handlerCount = MessageHandler_CountAndPrintHandlers(logicalName, v5, a3, 0);
  }
  else
  {
    handlerCount = 0;
    v9 = 1;
    for ( classFrame[0] = Class_GetNextRecord(0); classFrame[0]; classFrame[0] = Class_GetNextRecord(classFrame[0]) )
    {
      v10 = classFrame;
      handlerCount += MessageHandler_CountAndPrintHandlers(logicalName, &v9, v8, 0);
    }
  }
  return Rules_PrintTally(logicalName, handlerCount, (int)aMessageHandl_0, (int)aMessageHandl_5);
}
// 4CD775: variable 'v8' is possibly undefined

//----- (004CD790) --------------------------------------------------------
int * MessageHandler_PreviewSendForSymbol(int logicalName, _BYTE *handlerName)
{
  int *result; // eax
  int v4; // ecx
  int v5; // ecx

  result = Rules_FindSymbolEntry(handlerName);
  if ( result )
  {
    result = (int *)MessageHandler_BuildPreviewHandlerCore(v4, (int)result);
    if ( result )
    {
      MessageHandler_PrintHandlerPreview(logicalName, result, 0);
      return (int *)MessageHandler_FreeHandlerCore(v5);
    }
  }
  return result;
}
// 4CD7A8: variable 'v4' is possibly undefined
// 4CD7C0: variable 'v5' is possibly undefined

//----- (004CD7D0) --------------------------------------------------------
int  MessageHandler_CountAndPrintHandlers(int logicalName, unsigned __int16 *classArray, int a3, unsigned int classIndex)
{
  unsigned int handlerIndex; // ecx
  int i; // esi
  int classPtr; // eax
  int totalCount; // [esp+0h] [ebp-18h]

  totalCount = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(classArray + 1) + 4 * classIndex) + 96);
  if ( classIndex < (unsigned int)*classArray - 1 )
    totalCount += MessageHandler_CountAndPrintHandlers(logicalName, (int)classArray, a3, classIndex + 1);
  handlerIndex = 0;
  for ( i = 0; ; i += 36 )
  {
    classPtr = *(_DWORD *)(4 * classIndex + *(_DWORD *)(classArray + 1));
    if ( handlerIndex >= *(_DWORD *)(classPtr + 96) )
      break;
    MessageHandler_PrintNameTypeAndClass(logicalName, (_DWORD *)(i + *(_DWORD *)(classPtr + 88)), 1);
  }
  return totalCount;
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
signed int  MessageHandler_UndefineForClassOrAll(_DWORD *theClass, signed int *handlerName, int a3, int typeSpecified)
{
  int v6; // edx
  signed int typeIndex; // ebp
  int v8; // eax
  int v9; // edx
  _DWORD *classRecord; // esi
  int success; // [esp+0h] [ebp-14h]

  v6 = typeSpecified;
  if ( !handlerName )
    handlerName = Str_Intern(asc_50BFD4, a3);
  if ( v6 )
  {
    typeIndex = MessageHandler_TypeIndexFromKeyword((int)aUndefmessageHa);
    if ( typeIndex == 4 )
      return 0;
  }
  else
  {
    typeIndex = -1;
  }
  if ( theClass )
    return MessageHandler_RemoveByNameAndType(theClass, (int)handlerName, 1, typeIndex);
  v8 = Class_GetNextRecord(0);
  success = v9;
  classRecord = (_DWORD *)v8;
  if ( v8 )
  {
    do
    {
      if ( !MessageHandler_RemoveByNameAndType(classRecord, (int)handlerName, 0, typeIndex) )
        success = 0;
      classRecord = (_DWORD *)Class_GetNextRecord((int)classRecord);
    }
    while ( classRecord );
  }
  return success;
}
// 4CD913: variable 'v6' is possibly undefined
// 4CD92A: variable 'v9' is possibly undefined

//----- (004CD9A0) --------------------------------------------------------
BOOL  MessageHandler_WatchCommand(int watchFlag, int arguments, double a3)
{
  if ( watchFlag )
    return MessageHandler_DispatchWatchCommand((int)aWatch_2, 0, 0, watchFlag, a3, (void (*)(void))MessageHandler_SetWatchFlagField, arguments);
  else
    return MessageHandler_DispatchWatchCommand((int)aUnwatch_1, 0, 0, 0, a3, (void (*)(void))MessageHandler_SetWatchFlagField, arguments);
}
// 4CD1C0: using guessed type int sub_4CD1C0();

//----- (004CD9D0) --------------------------------------------------------
BOOL  MessageHandler_ListWatchItemsCommand(int logicalName, int arguments, double a3)
{
  return MessageHandler_DispatchWatchCommand((int)aListWatchIte_2, logicalName, (void (*)(void))MessageHandler_PrintWatchStatusLine, -1, a3, 0, arguments);
}

//----- (004CD9F0) --------------------------------------------------------
BOOL  MessageHandler_DispatchWatchCommand(
        int commandName,
        int logicalName,
        void (*printFunction)(void),
        int a4,
        double a5,
        void (*actionFunction)(void),
        int arguments)
{
  int currentArg; // esi
  BOOL result; // eax
  int classRecord; // esi
  int Name; // eax
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int nextArg; // ebx
  signed int typeIndex; // eax
  __int16 *v17; // eax
  int v18; // ebx
  int v19; // ecx
  int v20; // [esp+0h] [ebp-40h] BYREF
  int valueType; // [esp+4h] [ebp-3Ch]
  int valueNode; // [esp+8h] [ebp-38h]
  int v23; // [esp+18h] [ebp-28h]
  int *theClass; // [esp+1Ch] [ebp-24h]
  int handlerName; // [esp+20h] [ebp-20h]
  int Enum; // [esp+24h] [ebp-1Ch]
  int argIndex; // [esp+28h] [ebp-18h]
  void (*v28)(void); // [esp+2Ch] [ebp-14h]
  int v29; // [esp+30h] [ebp-10h]

  currentArg = arguments;
  v23 = commandName;
  v29 = a4;
  v28 = printFunction;
  argIndex = 2;
  if ( arguments )
  {
    while ( 1 )
    {
      if ( !currentArg )
        return 1;
      if ( Parser_ParseForm((__int16 *)currentArg, &v20, (int)printFunction, a5) )
        return 0;
      if ( valueType != 2 || (theClass = Class_LookupByQualifiedName(*(_BYTE **)(valueNode + 16))) == 0 )
      {
        Parser_ReportError(argIndex, (int)aClassName);
        return 0;
      }
      nextArg = *(_DWORD *)(currentArg + 10);
      if ( nextArg )
      {
        v17 = *(__int16 **)(currentArg + 10);
        ++argIndex;
        currentArg = nextArg;
        if ( Parser_ParseForm(v17, &v20, v14, a5) )
          return 0;
        if ( valueType != 2 )
        {
          Parser_ReportError(argIndex, (int)aHandlerName);
          return 0;
        }
        v18 = *(_DWORD *)(nextArg + 10);
        handlerName = *(_DWORD *)(valueNode + 16);
        if ( v18 )
        {
          currentArg = *(_DWORD *)(currentArg + 10);
          ++argIndex;
          if ( Parser_ParseForm((__int16 *)currentArg, &v20, 2, a5) )
            return 0;
          if ( v19 != valueType )
          {
            Parser_ReportError(argIndex, (int)aHandlerType);
            return 0;
          }
          typeIndex = MessageHandler_TypeIndexFromKeyword(v23);
          if ( typeIndex == 4 )
            return 0;
        }
        else
        {
          typeIndex = -1;
        }
      }
      else
      {
        typeIndex = -1;
        handlerName = 0;
      }
      if ( !MessageHandler_ForEachMatchingHandler((int)theClass, handlerName, logicalName, typeIndex, v29, 0, v28, actionFunction) )
        break;
      currentArg = *(_DWORD *)(currentArg + 10);
      ++argIndex;
    }
    Parser_ReportError(argIndex, (int)aHandler_0);
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
        if ( !actionFunction )
        {
          Name = Module_GetName(Enum);
          Output_Write(logicalName, Name, v12);
          Output_Write(logicalName, (int)asc_50C164, v13);
        }
        classRecord = Class_GetNextRecord(0);
        if ( classRecord )
          break;
LABEL_11:
        Enum = Module_NextEnum(Enum);
        if ( !Enum )
          goto LABEL_12;
      }
      while ( 1 )
      {
        result = MessageHandler_ForEachMatchingHandler(classRecord, 0, logicalName, -1, v29, 1, v28, actionFunction);
        if ( !result )
          break;
        classRecord = Class_GetNextRecord(classRecord);
        if ( !classRecord )
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
        int theClass,
        int handlerName,
        int logicalName,
        int typeIndex,
        int a5,
        int printHeader,
        void (*printFunction)(void),
        void (*actionFunction)(void))
{
  int found; // ebx
  int i; // ecx

  found = 0;
  for ( i = MessageHandler_EnumNext(theClass, 0); i; i = MessageHandler_EnumNext(theClass, i) )
  {
    if ( (typeIndex == -1 || *(_DWORD *)(36 * (i - 1) + *(_DWORD *)(theClass + 88)) << 29 >> 30 == typeIndex)
      && (!handlerName || !strcmp_(i, *(_DWORD *)(*(_DWORD *)(36 * (i - 1) + *(_DWORD *)(theClass + 88) + 8) + 16))) )
    {
      if ( actionFunction )
      {
        actionFunction();
      }
      else
      {
        if ( printHeader )
          Output_Write(logicalName, (int)asc_50C19C, i);
        printFunction();
      }
      found = 1;
    }
  }
  return !handlerName || typeIndex == -1 || found;
}
// 4CDC8C: variable 'i' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004CDD40) --------------------------------------------------------
signed int  MessageHandler_PrintWatchStatusLine(int theClass, int handlerIndex)
{
  int className; // eax
  int v4; // ecx
  int v5; // ecx
  int handlerOffset; // ebx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx

  className = Rules_GetConstructNameString(theClass);
  Output_Write(v4, className, v4);
  Output_Write(v5, (int)asc_50C030, v5);
  handlerOffset = 36 * (handlerIndex - 1);
  Output_Write(v7, *(_DWORD *)(*(_DWORD *)(handlerOffset + *(_DWORD *)(theClass + 88) + 8) + 16), v7);
  Output_Write(v8, (int)asc_50C030, v8);
  Output_Write(v9, (int)g_MessageHandlerTypeNames[*(_DWORD *)(handlerOffset + *(_DWORD *)(theClass + 88)) << 29 >> 30], v9);
  if ( (*(_DWORD *)(handlerOffset + *(_DWORD *)(theClass + 88)) & 0x10) != 0 )
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
int  Definstances_GetNextRecord(int previousRecord)
{
  return Class_Enum(previousRecord, g_Clips_DefinstancesModuleItemIndex);
}
// 54E8F0: using guessed type int dword_54E8F0;

//----- (004CDF50) --------------------------------------------------------
int  Definstances_FindByName(_BYTE *constructName, int a2)
{
  return Rules_FindConstructByNameGeneric(constructName, a2);
}
// 54E8F4: using guessed type int dword_54E8F4;

//----- (004CDF60) --------------------------------------------------------
BOOL Definstances_IsDeletable()
{
  int theDefinstances; // edx

  return !Rules_IsBloaded() && *(_DWORD *)(theDefinstances + 20) == 0;
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
  int theRecord; // edx

  if ( Rules_IsBloaded() )
    return 0;
  if ( !v0 )
    return Definstances_RemoveAll();
  result = Definstances_IsDeletable();
  if ( result )
  {
    Rules_UnlinkListNode(theRecord);
    Definstances_FreeRecord(theRecord);
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
int  Definstances_ListCommand(int logicalName, double a2)
{
  return Rules_ListConstructsCommand(g_ClipsDefinstancesConstructType, logicalName, a2);
}
// 54E8F4: using guessed type int dword_54E8F4;

//----- (004CE060) --------------------------------------------------------
_DWORD * Definstances_GetListCommand(int returnValue, double a2)
{
  return Rules_GetConstructListCommand(returnValue, g_ClipsDefinstancesConstructType, a2);
}
// 54E8F4: using guessed type int dword_54E8F4;

//----- (004CE0A0) --------------------------------------------------------
signed int  Definstances_ParseAndCreate(int readSource)
{
  int lastNode; // edi
  int constructName; // ebx
  _DWORD *v4; // edx
  _DWORD *v5; // ecx
  char *makeInstanceName; // eax
  int **Symbol; // ebx
  int v8; // ecx
  int v9; // eax
  int instanceNode; // ebp
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  char *ppForm; // eax
  _DWORD *packedActions; // eax
  int v16; // edx
  int v17; // ecx
  int v18; // edx
  int nameSymbol; // eax
  int v20; // edx
  int v21; // edx
  int v23; // ecx
  int activeFlag; // [esp+0h] [ebp-20h] BYREF
  _DWORD *newRecord; // [esp+4h] [ebp-1Ch]

  Rules_SetPPBufferStatus(1);
  Rules_FlushPPBuffer();
  Rules_SetIndentDepth(3);
  lastNode = 0;
  IO_OutWriteToken(aDefinstances_2);
  if ( Rules_IsBloaded() )
  {
    Rules_ReportCannotLoadWithBload();
    return 1;
  }
  constructName = Definstances_ParseHeaderAndActiveFlag(readSource, &activeFlag);
  if ( !constructName )
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
  Rules_InitConstructModuleRecord((int)aDefinstances, constructName);
  v5[5] = 0;
  v5[6] = 0;
  newRecord = v5;
  if ( activeFlag )
    makeInstanceName = aActiveMakeIn_1;
  else
    makeInstanceName = aMakeInstance_2;
  Symbol = Rules_MakeSymbol(makeInstanceName);
  if ( g_ParserCurrentTokenType == 100 )
  {
    while ( 1 )
    {
      AST_NewNode(103, (int)Symbol);
      v9 = Rules_ParseObjectInstanceFunctionCall(v8, readSource);
      instanceNode = v9;
      if ( !v9 )
      {
        AST_Free(newRecord[6]);
        g_ClipsMemFreeListTemp = (int)newRecord;
        *newRecord = *(_DWORD *)(g_ClipsMemoryTable + 112);
        *(_DWORD *)(g_ClipsMemoryTable + 112) = g_ClipsMemFreeListTemp;
        return 1;
      }
      if ( AST_TreeContainsSpecialTag(v9, 0) == 1 )
        break;
      if ( lastNode )
        *(_DWORD *)(lastNode + 10) = v11;
      else
        newRecord[6] = v11;
      Parser_NextToken(readSource, (int)&g_ParserCurrentTokenType);
      IO_OutNewline();
      AST_Append(v13, v12);
      IO_OutWriteToken((char *)g_ClipsScanTokenPrintForm);
      lastNode = instanceNode;
      if ( g_ParserCurrentTokenType != 100 )
        goto LABEL_13;
    }
    Rules_ReportLocalVariableError();
    AST_Free(v23);
    AST_Free(newRecord[6]);
    g_ClipsMemFreeListTemp = (int)newRecord;
    *newRecord = *(_DWORD *)(g_ClipsMemoryTable + 112);
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
        if ( newRecord[6] )
          IO_OutNewline();
        IO_OutNewline();
        IO_OutWriteToken(asc_50C2E4);
        ppForm = Rules_CopyPPBuffer();
        Rules_ReplaceConstructPPForm((signed int)newRecord, (int)ppForm);
      }
      packedActions = AST_PackNodeChain((_DWORD *)newRecord[6]);
      *(_DWORD *)(v16 + 24) = packedActions;
      AST_Free(v17);
      nameSymbol = Rules_GetConstructNameSymbol(v18);
      ++*(_DWORD *)(nameSymbol + 4);
      AST_InstallNodeChain(*(__int16 **)(v20 + 24));
      Rules_AppendConstructToModuleList(v21);
      return 0;
    }
    else
    {
      AST_Free(newRecord[6]);
      g_ClipsMemFreeListTemp = (int)newRecord;
      *newRecord = *(_DWORD *)(g_ClipsMemoryTable + 112);
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
int  Definstances_ParseHeaderAndActiveFlag(int readSource, _DWORD *activeFlag)
{
  int result; // eax
  int constructName; // ecx
  int v6; // edx
  int v7; // ecx
  int v8; // edx
  int v9; // edx
  int v10; // ecx
  int v11; // edx

  *activeFlag = 0;
  result = Rules_GetConstructNameAndComment(
             readSource,
             (int)&g_ParserCurrentTokenType,
             (int (*)(void))Definstances_FindByName,
             aDefinstances,
             (int (*)(void))Definstances_DeleteRecord,
             aDefinstancesConstructMarker,
             1,
             0,
             1);
  constructName = result;
  if ( result )
  {
    if ( g_ParserCurrentTokenType == 2 && !strcmp_(result, aActive) )
    {
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(asc_50C2F4);
      IO_OutWriteToken((char *)g_ClipsScanTokenPrintForm);
      AST_Append(v10, v9);
      Parser_NextToken(readSource, v11);
      *activeFlag = 1;
    }
    if ( g_ParserCurrentTokenType == 3 )
    {
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(asc_50C2F4);
      IO_OutWriteToken((char *)g_ClipsScanTokenPrintForm);
      AST_Append(v7, v6);
      Parser_NextToken(readSource, v8);
    }
    return constructName;
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
int  Definstances_FreeRecord(int theDefinstances)
{
  int nameSymbol; // eax
  int rhs; // eax
  int result; // eax

  nameSymbol = Rules_GetConstructNameSymbol(theDefinstances);
  Rules_DecrementSymbolCount(nameSymbol, theDefinstances);
  rhs = *(_DWORD *)(theDefinstances + 24);
  AST_DeinstallNodeChain((__int16 *)(uintptr_t)(unsigned int)rhs);
  AST_FreePackedNodeChain(rhs);
  Rules_ReplaceConstructPPForm(theDefinstances, 0);
  g_ClipsMemFreeListTemp = theDefinstances;
  *(_DWORD *)theDefinstances = *(_DWORD *)(g_ClipsMemoryTable + 112);
  result = g_ClipsMemoryTable;
  *(_DWORD *)(g_ClipsMemoryTable + 112) = g_ClipsMemFreeListTemp;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004CE490) --------------------------------------------------------
int  Definstances_SaveConstruct(signed int logicalName)
{
  return Rules_SaveConstruct(logicalName, g_ClipsDefinstancesConstructType);
}
// 54E8F4: using guessed type int dword_54E8F4;

//----- (004CE4A0) --------------------------------------------------------
signed int Definstances_RemoveAll()
{
  int allDeleted; // esi
  int currentRecord; // ebx
  int theRecord; // ecx
  int v4; // ecx
  int constructName; // eax
  int v6; // ecx

  allDeleted = 1;
  if ( Rules_IsBloaded() )
    return 0;
  currentRecord = Class_Enum(0, g_Clips_DefinstancesModuleItemIndex);
  if ( !currentRecord )
    return allDeleted;
  do
  {
    while ( 1 )
    {
      currentRecord = Class_Enum(currentRecord, g_Clips_DefinstancesModuleItemIndex);
      if ( !Definstances_IsDeletable() )
        break;
      Rules_UnlinkListNode(theRecord);
      Definstances_FreeRecord(v4);
      if ( !currentRecord )
        return allDeleted;
    }
    constructName = Rules_GetConstructNameString(theRecord);
    Definstances_ReportCannotDelete(constructName, v6);
    allDeleted = 0;
  }
  while ( currentRecord );
  return 0;
}
// 4CE4E5: variable 'v3' is possibly undefined
// 4CE4EC: variable 'v4' is possibly undefined
// 4CE503: variable 'v6' is possibly undefined
// 54E8F0: using guessed type int dword_54E8F0;

//----- (004CE520) --------------------------------------------------------
signed int  Definstances_ReportCannotDelete(int constructName, int a2)
{
  return Rules_ReportCantDeleteItem(a2, constructName);
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

//----- (004CE630) --------------------------------------------------------
int  Definstances_FreeModuleData(int moduleData)
{
  int result; // eax
  _DWORD *freed_node; // ecx

  result = Rules_ClearModuleConstructList(moduleData, g_ClipsDefinstancesConstructType, moduleData);
  freed_node = (_DWORD *)moduleData;
  g_ClipsMemFreeListTemp = moduleData;
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
  __int64 clearReadyResult; // [esp+0h] [ebp-10h]

  HIDWORD(clearReadyResult) = a2;
  LODWORD(clearReadyResult) = 1;
  sub_4A9430_Impl((int (*)(int, intptr_t))Definstances_CheckRecordBusy, g_Clips_DefinstancesModuleItemIndex, (intptr_t)&clearReadyResult, 0);
  return clearReadyResult;
}
// 54E8F0: using guessed type int dword_54E8F0;

//----- (004CE6A0) --------------------------------------------------------
int  Definstances_CheckRecordBusy(int result, _DWORD *clearReadyFlag)
{
  if ( *(_DWORD *)(result + 20) )
    *clearReadyFlag = 0;
  return result;
}

//----- (004CE6B0) --------------------------------------------------------
signed int Definstances_ResetAll()
{
  return sub_4A9430_Impl((int (*)(int, intptr_t))Definstances_ExecuteRecordActions, g_Clips_DefinstancesModuleItemIndex, 0, 1);
}
// 54E8F0: using guessed type int dword_54E8F0;

//----- (004CE6D0) --------------------------------------------------------
int  Definstances_ExecuteRecordActions(int theDefinstances, int a2, double a3)
{
  int record; // ecx
  __int16 *expression; // ecx
  int result; // eax
  _DWORD v9[6]; // [esp+0h] [ebp-18h] BYREF

  (void)a2;
  record = theDefinstances;
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
  _DWORD *queryFrame; // eax

  queryFrame = (_DWORD *)InstanceQuery_GetQueryFrameAtDepth(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 2) + 16));
  return Instance_GetQualifiedName(
           *(_DWORD *)(*queryFrame + 4 * *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 2) + 16)),
           (int)this);
}
// 51A960: using guessed type int dword_51A960;

//----- (004CE8D0) --------------------------------------------------------
int  InstanceQuery_ResolveBoundSlotValue(int returnValue, int a2, double a3)
{
  _DWORD *queryFrame; // eax
  int v5; // edx
  int theInstance; // ebx
  int result; // eax
  _DWORD *v8; // ecx
  _DWORD slotNameValue[9]; // [esp-4h] [ebp-24h] BYREF

  slotNameValue[7] = a2;
  *(_DWORD *)(returnValue + 4) = 2;
  *(_DWORD *)(returnValue + 8) = g_ClipsFalseSymbol;
  queryFrame = (_DWORD *)InstanceQuery_GetQueryFrameAtDepth(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 2) + 16));
  v5 = *(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10);
  theInstance = *(_DWORD *)(*queryFrame + 4 * *(_DWORD *)(*(_DWORD *)(v5 + 2) + 16));
  Parser_ParseForm(*(__int16 **)(v5 + 10), slotNameValue, returnValue, a3);
  if ( slotNameValue[1] == 2 )
  {
    result = Instance_GetSlotValueBySymbol(theInstance, slotNameValue[2]);
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
int * InstanceQuery_AnyInstancep(int returnValue, double a2)
{
  int *result; // eax
  _DWORD *v3; // edx
  _DWORD *v4; // eax
  int *v5; // ecx
  signed int testResult; // ebx
  int *v7; // ecx
  _DWORD varCount[4]; // [esp+0h] [ebp-10h] BYREF

  varCount[2] = returnValue;
  result = InstanceQuery_ParseRestrictions(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10), (int)aAnyInstancep, varCount, a2);
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
    *v4 = Mem_SmallBlockAlloc(4 * varCount[0]);
    *(_DWORD *)(g_ClipsQueryCore + 4) = *(_DWORD *)(g_ClipsCurrentExpression + 6);
    testResult = InstanceQuery_TestClassRestriction(v5, 0, a2);
    g_InstanceQuery_AbortFlag = 0;
    Mem_SmallBlockFree(*(_DWORD **)g_ClipsQueryCore, 4 * varCount[0]);
    g_ClipsMemFreeListTemp = g_ClipsQueryCore;
    *(_DWORD *)g_ClipsQueryCore = *(_DWORD *)(g_ClipsMemoryTable + 128);
    *(_DWORD *)(g_ClipsMemoryTable + 128) = g_ClipsMemFreeListTemp;
    InstanceQuery_PopQueryFrame();
    InstanceQuery_FreeRestrictionClassList(v7);
    return (int *)testResult;
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
int * InstanceQuery_FindInstance(_DWORD *returnValue, double a2)
{
  int *restrictionList; // ebp
  _DWORD *v4; // edx
  _DWORD *v5; // eax
  int instanceIndex; // ecx
  int coreOffset; // ebx
  int v8; // edx
  signed int *instanceName; // eax
  int v10; // edx
  int v11; // ecx
  int *result; // eax
  signed int varCount[5]; // [esp+0h] [ebp-14h] BYREF

  returnValue[1] = 4;
  returnValue[3] = 0;
  returnValue[4] = -1;
  restrictionList = InstanceQuery_ParseRestrictions(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10), (int)aFindInstance, varCount, a2);
  if ( restrictionList )
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
    *v5 = Mem_SmallBlockAlloc(4 * varCount[0]);
    *(_DWORD *)(g_ClipsQueryCore + 4) = *(_DWORD *)(g_ClipsCurrentExpression + 6);
    if ( InstanceQuery_TestClassRestriction(restrictionList, 0, a2) == 1 )
    {
      returnValue[2] = Rules_CreateEphemeralMultifield(varCount[0]);
      returnValue[4] = varCount[0] - 1;
      instanceIndex = 1;
      if ( varCount[0] >= 1 )
      {
        coreOffset = 4;
        v8 = 0;
        do
        {
          *(_WORD *)(v8 + returnValue[2] + 14) = 8;
          instanceName = Instance_GetQualifiedName(*(_DWORD *)(coreOffset + *(_DWORD *)g_ClipsQueryCore - 4), instanceIndex);
          coreOffset += 4;
          *(_DWORD *)(v10 + returnValue[2] + 16) = instanceName;
          instanceIndex = v11 + 1;
          v8 = v10 + 6;
        }
        while ( instanceIndex <= varCount[0] );
      }
    }
    else
    {
      returnValue[2] = Rules_CreateEphemeralMultifield(0);
    }
    g_InstanceQuery_AbortFlag = 0;
    Mem_SmallBlockFree(*(_DWORD **)g_ClipsQueryCore, 4 * varCount[0]);
    g_ClipsMemFreeListTemp = g_ClipsQueryCore;
    *(_DWORD *)g_ClipsQueryCore = *(_DWORD *)(g_ClipsMemoryTable + 128);
    *(_DWORD *)(g_ClipsMemoryTable + 128) = g_ClipsMemFreeListTemp;
    InstanceQuery_PopQueryFrame();
    return InstanceQuery_FreeRestrictionClassList(restrictionList);
  }
  else
  {
    result = Rules_CreateEphemeralMultifield(0);
    returnValue[2] = result;
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
int * InstanceQuery_FindAllInstances(_DWORD *returnValue, double a2)
{
  _DWORD *v3; // edx
  _DWORD *v4; // eax
  int v5; // ecx
  int instanceIndex; // ecx
  int fieldPos; // esi
  int v8; // ebx
  int v9; // edx
  signed int *instanceName; // eax
  int v11; // edx
  int v12; // ecx
  int *result; // eax
  int varCount; // [esp+0h] [ebp-18h] BYREF
  int *restrictionList; // [esp+4h] [ebp-14h]

  returnValue[1] = 4;
  returnValue[3] = 0;
  returnValue[4] = -1;
  restrictionList = InstanceQuery_ParseRestrictions(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10), (int)aFindAllInstanc, &varCount, a2);
  if ( restrictionList )
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
    *v4 = Mem_SmallBlockAlloc(4 * varCount);
    *(_DWORD *)(g_ClipsQueryCore + 4) = *(_DWORD *)(g_ClipsCurrentExpression + 6);
    *(_DWORD *)(g_ClipsQueryCore + 8) = 0;
    *(_DWORD *)(g_ClipsQueryCore + 12) = 0;
    *(_DWORD *)(g_ClipsQueryCore + 20) = varCount;
    *(_DWORD *)(g_ClipsQueryCore + 24) = 0;
    InstanceQuery_ForEachClassRestriction(restrictionList, 0, a2);
    g_InstanceQuery_AbortFlag = v5;
    returnValue[2] = Rules_CreateEphemeralMultifield(varCount * *(_DWORD *)(g_ClipsQueryCore + 24));
    while ( *(_DWORD *)(g_ClipsQueryCore + 12) )
    {
      instanceIndex = 0;
      fieldPos = returnValue[4] + 2;
      if ( varCount > 0 )
      {
        v8 = 0;
        v9 = 6 * fieldPos - 6;
        do
        {
          *(_WORD *)(v9 + returnValue[2] + 14) = 8;
          instanceName = Instance_GetQualifiedName(*(_DWORD *)(v8 + **(_DWORD **)(g_ClipsQueryCore + 12)), instanceIndex);
          v8 += 4;
          instanceIndex = v12 + 1;
          ++fieldPos;
          *(_DWORD *)(v11 + returnValue[2] + 16) = instanceName;
          v9 = v11 + 6;
        }
        while ( instanceIndex < varCount );
      }
      returnValue[4] = fieldPos - 2;
      InstanceQuery_DequeueDelayedBinding();
    }
    Mem_SmallBlockFree(*(_DWORD **)g_ClipsQueryCore, 4 * varCount);
    g_ClipsMemFreeListTemp = g_ClipsQueryCore;
    *(_DWORD *)g_ClipsQueryCore = *(_DWORD *)(g_ClipsMemoryTable + 128);
    *(_DWORD *)(g_ClipsMemoryTable + 128) = g_ClipsMemFreeListTemp;
    InstanceQuery_PopQueryFrame();
    return InstanceQuery_FreeRestrictionClassList(restrictionList);
  }
  else
  {
    result = Rules_CreateEphemeralMultifield(0);
    returnValue[2] = result;
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
int * InstanceQuery_DoForInstance(int returnValue, int a2, double a3)
{
  int *result; // eax
  int *restrictionList; // ebx
  _DWORD *v5; // edx
  _DWORD *v6; // eax
  _DWORD *v7; // ecx
  _DWORD varCount[4]; // [esp+0h] [ebp-10h] BYREF

  varCount[2] = a2;
  *(_DWORD *)(returnValue + 4) = 2;
  *(_DWORD *)(returnValue + 8) = g_ClipsFalseSymbol;
  result = InstanceQuery_ParseRestrictions(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10), (int)aDoForInstance, varCount, a3);
  restrictionList = result;
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
    *v6 = Mem_SmallBlockAlloc(4 * varCount[0]);
    *(_DWORD *)(g_ClipsQueryCore + 4) = *(_DWORD *)(g_ClipsCurrentExpression + 6);
    *(_DWORD *)(g_ClipsQueryCore + 8) = *(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10);
    if ( InstanceQuery_TestClassRestriction(restrictionList, 0, a3) == 1 )
      Parser_ParseForm(*(__int16 **)(g_ClipsQueryCore + 8), v7, (int)v7, a3);
    g_InstanceQuery_AbortFlag = 0;
    HIDWORD(g_ClipsHaltExecutionFlag) = 0;
    Mem_SmallBlockFree(*(_DWORD **)g_ClipsQueryCore, 4 * varCount[0]);
    g_ClipsMemFreeListTemp = g_ClipsQueryCore;
    *(_DWORD *)g_ClipsQueryCore = *(_DWORD *)(g_ClipsMemoryTable + 128);
    *(_DWORD *)(g_ClipsMemoryTable + 128) = g_ClipsMemFreeListTemp;
    InstanceQuery_PopQueryFrame();
    return InstanceQuery_FreeRestrictionClassList(restrictionList);
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
int * InstanceQuery_DoForAllInstances(int returnValue, int a2, double a3)
{
  int *result; // eax
  int *restrictionList; // ebx
  _DWORD *v5; // edx
  _DWORD *v6; // eax
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int v10; // ecx
  _DWORD varCount[4]; // [esp+0h] [ebp-10h] BYREF

  varCount[2] = a2;
  *(_DWORD *)(returnValue + 4) = 2;
  *(_DWORD *)(returnValue + 8) = g_ClipsFalseSymbol;
  result = InstanceQuery_ParseRestrictions(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10), (int)aDoForAllInstan, varCount, a3);
  restrictionList = result;
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
    *v6 = Mem_SmallBlockAlloc(4 * varCount[0]);
    *(_DWORD *)(g_ClipsQueryCore + 4) = *(_DWORD *)(g_ClipsCurrentExpression + 6);
    *(_DWORD *)(g_ClipsQueryCore + 8) = *(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10);
    *(_DWORD *)(g_ClipsQueryCore + 28) = v7;
    Rules_ValueInstall(*(_DWORD *)(g_ClipsQueryCore + 28), v7);
    InstanceQuery_ForEachClassRestriction(restrictionList, v8, a3);
    Rules_ValueDeinstall(*(_DWORD *)(g_ClipsQueryCore + 28), v9);
    Rules_PropagateReturnValueDepth(*(_DWORD *)(g_ClipsQueryCore + 28));
    g_InstanceQuery_AbortFlag = v10;
    HIDWORD(g_ClipsHaltExecutionFlag) = v10;
    Mem_SmallBlockFree(*(_DWORD **)g_ClipsQueryCore, 4 * varCount[0]);
    g_ClipsMemFreeListTemp = g_ClipsQueryCore;
    *(_DWORD *)g_ClipsQueryCore = *(_DWORD *)(g_ClipsMemoryTable + 128);
    *(_DWORD *)(g_ClipsMemoryTable + 128) = g_ClipsMemFreeListTemp;
    InstanceQuery_PopQueryFrame();
    return InstanceQuery_FreeRestrictionClassList(restrictionList);
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
int * InstanceQuery_DelayedDoForAllInstances(_DWORD *returnValue, double a2)
{
  int *result; // eax
  int *restrictionList; // ebp
  _DWORD *v5; // edx
  _DWORD *v6; // eax
  int v7; // ecx
  int copyIndex; // edx
  int copyOffset; // eax
  int v10; // ecx
  int varCount[5]; // [esp+0h] [ebp-14h] BYREF

  returnValue[1] = 2;
  returnValue[2] = g_ClipsFalseSymbol;
  result = InstanceQuery_ParseRestrictions(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10), (int)aDelayedDoForAl, varCount, a2);
  restrictionList = result;
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
    *v6 = Mem_SmallBlockAlloc(4 * varCount[0]);
    *(_DWORD *)(g_ClipsQueryCore + 4) = *(_DWORD *)(g_ClipsCurrentExpression + 6);
    *(_DWORD *)(g_ClipsQueryCore + 8) = 0;
    *(_DWORD *)(g_ClipsQueryCore + 12) = 0;
    *(_DWORD *)(g_ClipsQueryCore + 20) = varCount[0];
    *(_DWORD *)(g_ClipsQueryCore + 24) = 0;
    InstanceQuery_ForEachClassRestriction(restrictionList, 0, a2);
    g_InstanceQuery_AbortFlag = v7;
    *(_DWORD *)(g_ClipsQueryCore + 8) = *(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10);
    while ( *(_DWORD *)(g_ClipsQueryCore + 12) )
    {
      copyIndex = 0;
      if ( varCount[0] > 0 )
      {
        copyOffset = 0;
        do
        {
          *(_DWORD *)(*(_DWORD *)g_ClipsQueryCore + copyOffset) = *(_DWORD *)(**(_DWORD **)(g_ClipsQueryCore + 12) + copyOffset);
          ++copyIndex;
          copyOffset += 4;
        }
        while ( copyIndex < varCount[0] );
      }
      InstanceQuery_DequeueDelayedBinding();
      ++g_ClipsCurrentEvaluationDepth;
      Parser_ParseForm(*(__int16 **)(g_ClipsQueryCore + 8), returnValue, v10, a2);
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
    Mem_SmallBlockFree(*(_DWORD **)g_ClipsQueryCore, 4 * varCount[0]);
    g_ClipsMemFreeListTemp = g_ClipsQueryCore;
    *(_DWORD *)g_ClipsQueryCore = *(_DWORD *)(g_ClipsMemoryTable + 128);
    *(_DWORD *)(g_ClipsMemoryTable + 128) = g_ClipsMemFreeListTemp;
    InstanceQuery_PopQueryFrame();
    return InstanceQuery_FreeRestrictionClassList(restrictionList);
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
  _DWORD *freeListNode; // edx
  _DWORD *result; // eax

  freeListNode = *(_DWORD **)(g_ClipsMemoryTable + 32);
  if ( freeListNode )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
    *(_DWORD *)(g_ClipsMemoryTable + 32) = *freeListNode;
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
  _DWORD *topFrame; // eax
  int result; // eax

  topFrame = (_DWORD *)g_ClipsInstanceQueryCoreStack;
  g_ClipsQueryCore = *(_DWORD *)g_ClipsInstanceQueryCoreStack;
  g_ClipsInstanceQueryCoreStack = *(_DWORD *)(g_ClipsInstanceQueryCoreStack + 4);
  g_ClipsMemFreeListTemp = (int)topFrame;
  *topFrame = *(_DWORD *)(g_ClipsMemoryTable + 32);
  result = g_ClipsMemFreeListTemp;
  *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
  return result;
}
// 51B458: using guessed type int dword_51B458;
// 51B45C: using guessed type int dword_51B45C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004CF380) --------------------------------------------------------
int  InstanceQuery_GetQueryFrameAtDepth(signed int depth)
{
  _DWORD *i; // edx

  if ( !depth )
    return g_ClipsQueryCore;
  for ( i = (_DWORD *)g_ClipsInstanceQueryCoreStack; depth > 1; i = (_DWORD *)i[1] )
    --depth;
  return *i;
}
// 51B458: using guessed type int dword_51B458;
// 51B45C: using guessed type int dword_51B45C;

//----- (004CF3B0) --------------------------------------------------------
int * InstanceQuery_ParseRestrictions(int queryExpr, int functionName, _DWORD *varCountOut, double a4)
{
  int *classListHead; // ebp
  int *lastClass; // ebx
  int v8; // ecx
  int newGroup; // edi
  int *classNode; // eax
  _DWORD token[7]; // [esp+0h] [ebp-30h] BYREF
  _DWORD *varCountPtr; // [esp+1Ch] [ebp-14h]

  token[6] = functionName;
  varCountPtr = varCountOut;
  classListHead = 0;
  lastClass = 0;
  v8 = 0;
  newGroup = 0;
  *varCountOut = 0;
  if ( !queryExpr )
    return classListHead;
  while ( 1 )
  {
    if ( Parser_ParseForm((__int16 *)queryExpr, token, v8, a4) )
    {
      InstanceQuery_FreeRestrictionClassList(classListHead);
      return 0;
    }
    if ( token[1] != 2 || token[2] != g_InternedSym_Qds )
      break;
    newGroup = 1;
    ++*varCountPtr;
LABEL_6:
    queryExpr = *(_DWORD *)(queryExpr + 10);
    if ( !queryExpr )
      return classListHead;
  }
  classNode = InstanceQuery_ResolveClassRestriction(v8, token);
  if ( classNode )
  {
    if ( classListHead )
    {
      if ( newGroup == 1 )
      {
        v8 = (int)classNode;
        newGroup = 0;
        lastClass[3] = (int)classNode;
        lastClass = classNode;
      }
      else
      {
        *(_DWORD *)(v8 + 8) = classNode;
      }
    }
    else
    {
      v8 = (int)classNode;
      lastClass = classNode;
      classListHead = classNode;
    }
    while ( *(_DWORD *)(v8 + 8) )
      v8 = *(_DWORD *)(v8 + 8);
    goto LABEL_6;
  }
  Parser_ReportSyntaxError();
  InstanceQuery_FreeRestrictionClassList(classListHead);
  Lexer_ErrorRecover(1);
  return 0;
}
// 4CF3D7: variable 'v8' is possibly undefined
// 51B454: using guessed type int dword_51B454;

//----- (004CF480) --------------------------------------------------------
int *__fastcall InstanceQuery_ResolveClassRestriction(int a1, _DWORD *classToken)
{
  int v2; // edx
  int currentModule; // edi
  int restrictionType; // ecx
  int *restrictionListHead; // ebp
  int firstField; // eax
  int lastField; // ecx
  int fieldOffset; // esi
  int fieldPtr; // eax
  _BYTE *className; // edx
  int *lookedUpClass; // eax
  int v12; // ecx
  _DWORD *arrayFreeNode; // ecx
  int *arrayNode; // ecx
  int *restrictionNode; // ebx
  _DWORD *v16; // ecx
  int *result; // eax
  _DWORD *singleFreeNode; // ecx
  int *singleNode; // ecx
  int singleNodeAddr; // ebx
  int resolvedClass; // eax
  _DWORD *v22; // ecx
  int *namedClass; // eax
  int v24; // ecx
  int lookupClass; // esi
  _DWORD *namedFreeNode; // edx
  int *namedNode; // ecx
  int namedNodeAddr; // ebx
  _DWORD *v29; // ecx
  int lastFieldOffset; // [esp+4h] [ebp-28h]
  int arrayClass; // [esp+Ch] [ebp-20h]
  int *lastNode; // [esp+10h] [ebp-1Ch]
  int fieldIndex; // [esp+14h] [ebp-18h]

  currentModule = Module_GetCurrent();
  if ( *(_DWORD *)(v2 + 4) == 57 )
  {
    Class_AddBusyReference(classToken[2]);
    singleFreeNode = *(_DWORD **)(g_ClipsMemoryTable + 64);
    if ( singleFreeNode )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
      *(_DWORD *)(g_ClipsMemoryTable + 64) = *singleFreeNode;
      singleNode = (int *)g_ClipsMemFreeListTemp;
    }
    else
    {
      singleNode = (int *)Mem_HeapAllocWithRetry((_DWORD *)0x10);
    }
    singleNodeAddr = (int)singleNode;
    resolvedClass = classToken[2];
    *singleNode = resolvedClass;
    if ( Class_IsInScope(resolvedClass, currentModule) )
      v22[1] = currentModule;
    else
      v22[1] = **(_DWORD **)(*v22 + 8);
    *(_DWORD *)(singleNodeAddr + 8) = 0;
    result = (int *)singleNodeAddr;
    *(_DWORD *)(singleNodeAddr + 12) = 0;
  }
  else
  {
    restrictionType = classToken[1];
    if ( restrictionType == 2 )
    {
      namedClass = Class_LookupByQualifiedName(*(_BYTE **)(classToken[2] + 16));
      lookupClass = (int)namedClass;
      if ( namedClass )
      {
        Class_AddBusyReference((int)namedClass);
        namedFreeNode = *(_DWORD **)(g_ClipsMemoryTable + 64);
        if ( namedFreeNode )
        {
          g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
          *(_DWORD *)(g_ClipsMemoryTable + 64) = *namedFreeNode;
          namedNode = (int *)g_ClipsMemFreeListTemp;
        }
        else
        {
          namedNode = (int *)Mem_HeapAllocWithRetry((_DWORD *)0x10);
        }
        namedNodeAddr = (int)namedNode;
        *namedNode = lookupClass;
        if ( Class_IsInScope(lookupClass, currentModule) )
          v29[1] = currentModule;
        else
          v29[1] = **(_DWORD **)(*v29 + 8);
        *(_DWORD *)(namedNodeAddr + 8) = 0;
        result = (int *)namedNodeAddr;
        *(_DWORD *)(namedNodeAddr + 12) = 0;
      }
      else
      {
        Class_ReportLookupError(v24, *(_DWORD *)(classToken[2] + 16));
        return 0;
      }
    }
    else
    {
      if ( restrictionType == 4 )
      {
        restrictionListHead = 0;
        lastNode = 0;
        firstField = classToken[3] + 1;
        lastField = classToken[4] + 1;
        fieldIndex = firstField;
        if ( lastField < firstField )
          return restrictionListHead;
        fieldOffset = 6 * firstField - 6;
        lastFieldOffset = 6 * lastField - 6;
        while ( 1 )
        {
          fieldPtr = fieldOffset + classToken[2];
          if ( *(_WORD *)(fieldPtr + 14) != 2 )
            break;
          className = *(_BYTE **)(*(_DWORD *)(fieldPtr + 16) + 16);
          lookedUpClass = Class_LookupByQualifiedName(className);
          arrayClass = (int)lookedUpClass;
          if ( !lookedUpClass )
          {
            Class_ReportLookupError(v12, (int)className);
            break;
          }
          Class_AddBusyReference((int)lookedUpClass);
          arrayFreeNode = *(_DWORD **)(g_ClipsMemoryTable + 64);
          if ( arrayFreeNode )
          {
            g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
            *(_DWORD *)(g_ClipsMemoryTable + 64) = *arrayFreeNode;
            arrayNode = (int *)g_ClipsMemFreeListTemp;
          }
          else
          {
            arrayNode = (int *)Mem_HeapAllocWithRetry((_DWORD *)0x10);
          }
          restrictionNode = arrayNode;
          *arrayNode = arrayClass;
          if ( Class_IsInScope(arrayClass, currentModule) )
            v16[1] = currentModule;
          else
            v16[1] = **(_DWORD **)(*v16 + 8);
          restrictionNode[2] = 0;
          restrictionNode[3] = 0;
          if ( restrictionListHead )
            lastNode[2] = (int)restrictionNode;
          else
            restrictionListHead = restrictionNode;
          lastNode = restrictionNode;
          fieldOffset += 6;
          ++fieldIndex;
          if ( fieldOffset > lastFieldOffset )
            return restrictionListHead;
        }
        InstanceQuery_FreeRestrictionClassList(restrictionListHead);
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
  int *subNode; // edx
  _DWORD *v3; // edx
  _DWORD *v4; // edx

  for ( i = result; i; *(_DWORD *)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp )
  {
    while ( 1 )
    {
      subNode = (int *)i[2];
      if ( !subNode )
        break;
      i[2] = subNode[2];
      Class_ReleaseBusyReference(*subNode);
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
signed int  InstanceQuery_TestClassRestriction(int *restrictionList, int queryIndex, double a3)
{
  int *currentRestriction; // esi
  signed int traversalID; // eax

  currentRestriction = restrictionList;
  g_InstanceQuery_AbortFlag = 1;
  if ( restrictionList )
  {
    while ( 1 )
    {
      g_InstanceQuery_AbortFlag = 0;
      traversalID = Class_NewTraversalID();
      if ( traversalID == -1 )
        break;
      if ( InstanceQuery_TestInstancesRecursive(currentRestriction[1], traversalID, (int)restrictionList, *currentRestriction, a3, queryIndex) )
      {
        Class_ReleaseTraversalID();
        return 1;
      }
      Class_ReleaseTraversalID();
      if ( g_ClipsHaltExecution == 1 || g_InstanceQuery_AbortFlag == 1 )
        return 0;
      currentRestriction = (int *)currentRestriction[2];
      if ( !currentRestriction )
        return 0;
    }
  }
  return 0;
}
// 51A968: using guessed type int dword_51A968;
// 51B460: using guessed type int dword_51B460;

//----- (004CF800) --------------------------------------------------------
BOOL  InstanceQuery_TestInstancesRecursive(
        int theModule,
        signed int traversalID,
        int restriction,
        int theClass,
        double a5,
        int queryIndex)
{
  int traversalByte; // ebx
  int traversalMask; // eax
  BOOL result; // eax
  int v10; // edx
  int i; // ecx
  unsigned int subclassIndex; // edi
  int subclassOffset; // ebp
  _DWORD v14[6]; // [esp+0h] [ebp-30h] BYREF
  int v15; // [esp+18h] [ebp-18h]
  signed int v16; // [esp+1Ch] [ebp-14h]
  int v17; // [esp+20h] [ebp-10h]

  v15 = theModule;
  v16 = traversalID;
  v17 = theClass;
  traversalByte = ((traversalID - (__CFSHL__(traversalID >> 31, 3) + 8 * (traversalID >> 31))) >> 3) + theClass;
  traversalMask = 1 << (traversalID % 8);
  if ( ((unsigned __int8)traversalMask & *(_BYTE *)(traversalByte + 108)) != 0 )
    return 0;
  v10 = v15;
  *(_BYTE *)(traversalByte + 108) |= traversalMask;
  result = Class_IsInScope(v17, v10);
  if ( !result )
    return result;
  i = *(_DWORD *)(v17 + 80);
  if ( !i )
    goto LABEL_9;
  while ( 1 )
  {
    *(_DWORD *)(*(_DWORD *)g_ClipsQueryCore + 4 * queryIndex) = i;
    if ( !*(_DWORD *)(restriction + 12) )
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
    if ( InstanceQuery_TestClassRestriction(*(_DWORD *)(restriction + 12), queryIndex + 1, a5) == 1 )
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
  subclassIndex = 0;
  subclassOffset = 0;
  while ( subclassIndex < *(unsigned __int16 *)(v17 + 40) )
  {
    if ( InstanceQuery_TestInstancesRecursive(v15, v16, restriction, *(_DWORD *)(*(_DWORD *)(v17 + 42) + subclassOffset), a5, queryIndex) )
      return 1;
    if ( g_ClipsHaltExecution == 1 || g_InstanceQuery_AbortFlag == 1 )
      return 0;
    subclassOffset += 4;
    ++subclassIndex;
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
void  InstanceQuery_ForEachClassRestriction(int *restrictionList, int queryIndex, double a3)
{
  int *currentRestriction; // esi
  signed int traversalID; // eax

  currentRestriction = restrictionList;
  for ( g_InstanceQuery_AbortFlag = 1; currentRestriction; currentRestriction = (int *)currentRestriction[2] )
  {
    g_InstanceQuery_AbortFlag = 0;
    traversalID = Class_NewTraversalID();
    if ( traversalID == -1 )
      break;
    InstanceQuery_ForEachInstanceRecursive(currentRestriction[1], traversalID, (int)restrictionList, *currentRestriction, a3, queryIndex);
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
void  InstanceQuery_ForEachInstanceRecursive(int theModule, signed int traversalID, int restriction, int theClass, double a5, int queryIndex)
{
  int traversalByte; // ebx
  int traversalMask; // eax
  int v9; // edx
  int i; // ecx
  unsigned int subclassIndex; // ebp
  int j; // edi
  bool v13; // zf
  int v14; // ecx
  int v15; // ecx
  _DWORD v16[6]; // [esp+0h] [ebp-30h] BYREF
  int v17; // [esp+18h] [ebp-18h]
  signed int v18; // [esp+1Ch] [ebp-14h]
  int v19; // [esp+20h] [ebp-10h]

  v17 = theModule;
  v18 = traversalID;
  v19 = theClass;
  traversalByte = ((traversalID - (__CFSHL__(traversalID >> 31, 3) + 8 * (traversalID >> 31))) >> 3) + theClass;
  traversalMask = 1 << (traversalID % 8);
  if ( ((unsigned __int8)traversalMask & *(_BYTE *)(traversalByte + 108)) == 0 )
  {
    v9 = v17;
    *(_BYTE *)(traversalByte + 108) |= traversalMask;
    if ( Class_IsInScope(v19, v9) )
    {
      i = *(_DWORD *)(v19 + 80);
      if ( i )
      {
        while ( 1 )
        {
          *(_DWORD *)(*(_DWORD *)g_ClipsQueryCore + 4 * queryIndex) = i;
          if ( *(_DWORD *)(restriction + 12) )
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
        InstanceQuery_ForEachClassRestriction(*(_DWORD *)(restriction + 12), queryIndex + 1, a5);
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
        subclassIndex = 0;
        for ( j = 0; subclassIndex < *(unsigned __int16 *)(v19 + 40); j += 4 )
        {
          InstanceQuery_ForEachInstanceRecursive(v17, v18, restriction, *(_DWORD *)(j + *(_DWORD *)(v19 + 42)), a5, queryIndex);
          if ( g_ClipsHaltExecution == 1 || g_InstanceQuery_AbortFlag == 1 )
            break;
          ++subclassIndex;
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
  _DWORD *bindingNode; // edi
  _DWORD *valuesArray; // eax
  _DWORD *v2; // edx
  int copyIndex; // edx
  int copyOffset; // eax
  int result; // eax
  _DWORD *destSlot; // esi
  int value; // ecx

  bindingNode = Mem_SmallBlockAlloc(8u);
  valuesArray = Mem_SmallBlockAlloc(4 * *(_DWORD *)(g_ClipsQueryCore + 20));
  *v2 = valuesArray;
  copyIndex = 0;
  copyOffset = 0;
  while ( copyIndex < *(_DWORD *)(g_ClipsQueryCore + 20) )
  {
    destSlot = (_DWORD *)(*bindingNode + copyOffset);
    ++copyIndex;
    value = *(_DWORD *)(*(_DWORD *)g_ClipsQueryCore + copyOffset);
    copyOffset += 4;
    *destSlot = value;
  }
  bindingNode[1] = 0;
  if ( *(_DWORD *)(g_ClipsQueryCore + 12) )
    *(_DWORD *)(*(_DWORD *)(g_ClipsQueryCore + 16) + 4) = bindingNode;
  else
    *(_DWORD *)(g_ClipsQueryCore + 12) = bindingNode;
  *(_DWORD *)(g_ClipsQueryCore + 16) = bindingNode;
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
int  ObjectsCompiler_WriteDefclassPointerRef(int imageID, int theDefclass, int fileID)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( theDefclass )
    return Output_WriteFormatted(
             fileID,
             *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 4),
             imageID,
             (int)aSD_DD_1,
             *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 4));
  else
    return Output_WriteFormatted(fileID, 0, imageID, (int)aNull_7, v4);
}
// 4CFDC0: variable 'v4' is possibly undefined
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004CFE00) --------------------------------------------------------
int  ObjectsCompiler_WriteModuleItemHeaderRef(int imageID, int fileID)
{
  return Output_WriteFormatted(fileID, **(_DWORD **)(g_ClipsConstructCompilerData + 20), imageID, (int)aMihsSD_DD_1, **(_DWORD **)(g_ClipsConstructCompilerData + 20));
}
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004CFE40) --------------------------------------------------------
int ObjectsCompiler_AssignConstructIndices()
{
  int slotIndex; // edx
  int i; // ecx
  int result; // eax

  Rules_DoForAllConstructs((void (*)(void))ObjectsCompiler_AssignClassCompileIndex, 0);
  slotIndex = 0;
  for ( i = 0; i != 668; i += 4 )
  {
    for ( result = *(_DWORD *)(i + g_Defclass_SlotNameHashTablePtr); result; ++slotIndex )
    {
      *(_DWORD *)(result + 24) = slotIndex;
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
_DWORD * ObjectsCompiler_AssignClassCompileIndex(_DWORD *theClass, _DWORD *indexCounter)
{
  int classIndex; // ebx
  _DWORD *result; // eax
  int v6; // edx
  unsigned int slotIndex; // ebx
  int slotOffset; // edx
  int v9; // ebp
  int v10; // edi

  classIndex = (*indexCounter)++;
  result = indexCounter;
  v6 = theClass[16];
  theClass[3] = classIndex;
  slotIndex = 0;
  if ( v6 )
  {
    slotOffset = 0;
    do
    {
      *(_DWORD *)(slotOffset + theClass[13] + 28) = ((unsigned __int16)result[2] << 16) | (unsigned __int16)result[1];
      v9 = result[2] + 1;
      result[2] = v9;
      if ( v9 >= result[3] )
      {
        v10 = result[1];
        result[2] = 0;
        result[1] = v10 + 1;
      }
      ++slotIndex;
      slotOffset += 44;
    }
    while ( slotIndex < theClass[16] );
  }
  return result;
}

//----- (004CFF30) --------------------------------------------------------
int  ObjectsCompiler_WriteSlotNamePointerRef(int imageID, int slotNamePtr, int fileID)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( slotNamePtr )
    return Output_WriteFormatted(
             fileID,
             *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 32),
             imageID,
             (int)aSD_DD_1,
             *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 32));
  else
    return Output_WriteFormatted(fileID, 0, imageID, (int)aNull_7, v4);
}
// 4CFF40: variable 'v4' is possibly undefined
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004CFF80) --------------------------------------------------------
int  ObjectsCompiler_WriteRuntimeInitCall(int fileID, int imageID)
{
  return Output_WriteFormatted(fileID, imageID, fileID, (int)aObjectsruntime, *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 40));
}
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004CFFC0) --------------------------------------------------------
void  ObjectsCompiler_GenerateObjectsCode(const char *fileName, const char *pathName, DWORD fileNameBuffer, int fileID, int maxIndices)
{
  int initIndex; // eax
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
  int moduleFileCount; // [esp+6Ch] [ebp-A0h] BYREF
  int classFileCount; // [esp+70h] [ebp-9Ch] BYREF
  int v28; // [esp+74h] [ebp-98h] BYREF
  int v29; // [esp+78h] [ebp-94h] BYREF
  int v30; // [esp+7Ch] [ebp-90h] BYREF
  int v31; // [esp+80h] [ebp-8Ch] BYREF
  int v32; // [esp+84h] [ebp-88h] BYREF
  int v33; // [esp+88h] [ebp-84h] BYREF
  int moduleFile; // [esp+8Ch] [ebp-80h] BYREF
  int classFile; // [esp+90h] [ebp-7Ch]
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
  int version; // [esp+ECh] [ebp-20h] BYREF
  int fileIDCopy; // [esp+F0h] [ebp-1Ch]
  _DWORD *j; // [esp+F4h] [ebp-18h]
  int i; // [esp+F8h] [ebp-14h]
  int moduleIndex; // [esp+FCh] [ebp-10h]

  fileIDCopy = fileID;
  initIndex = 0;
  version = 1;
  moduleIndex = 0;
  v9 = 0;
  do
  {
    ++initIndex;
    v9 += 3;
    v25[initIndex + 2] = 0;
    *(int *)((char *)&v49 + initIndex * 4) = 1;
    *(int *)((char *)&v33 + initIndex * 4) = 0;
    *(int *)((char *)&v41 + initIndex * 4) = 0;
    v17[v9] = 0;
  }
  while ( initIndex != 8 );
  v10 = fileIDCopy;
  Output_WriteFormatted(1, v9 * 4, fileIDCopy, (int)aIncludeClassco, (char)v18[0]);
  Output_WriteFormatted(v12, v11, v10, (int)aIncludeClassin, (char)v18[0]);
  if ( ObjectsCompiler_WriteClassPointerArray(fileName, pathName, fileNameBuffer, v10, maxIndices, &version) )
  {
    if ( ObjectsCompiler_WriteClassHashTable(fileName, pathName, fileNameBuffer, fileIDCopy, maxIndices, &version) )
    {
      ObjectsCompiler_WriteSlotNameHashTable(fileName, pathName, fileNameBuffer, fileIDCopy, maxIndices, &version);
      if ( v13 )
      {
        if ( ObjectsCompiler_WriteSlotNameRecords(fileName, pathName, fileNameBuffer, fileIDCopy, maxIndices, &version) )
        {
          for ( i = Module_NextEnum(0); i; ++moduleFileCount )
          {
            Module_SetCurrent(i);
            v14 = Rules_ConstructCodeFileOpen(
                    moduleFile,
                    fileName,
                    fileNameBuffer,
                    pathName,
                    &version,
                    v50,
                    fileIDCopy,
                    (char)aDefclass_modul,
                    **(const char ***)(g_ClipsConstructCompilerData + 20),
                    v42,
                    v18);
            moduleFile = v14;
            if ( !v14 )
              break;
            ObjectsCompiler_WriteModuleRecord(v14, i, maxIndices);
            moduleFile = Rules_ConstructCodeFileClose(moduleFile, &moduleFileCount, maxIndices, &v50, &v42, (int)v18);
            for ( j = (_DWORD *)Class_GetNextRecord(0); j; j = (_DWORD *)Class_GetNextRecord((int)j) )
            {
              v15 = Rules_ConstructCodeFileOpen(
                      classFile,
                      fileName,
                      fileNameBuffer,
                      pathName,
                      &version,
                      v51,
                      fileIDCopy,
                      (char)aDefclass_6,
                      *(const char **)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 4),
                      v43,
                      v19);
              classFile = v15;
              if ( !v15 )
                goto LABEL_20;
              ObjectsCompiler_WriteClassRecord(v15, fileNameBuffer, (int)j, maxIndices, moduleIndex, v52, v28, v53, v29, v54, v30, v55, v31, v56, v32, v57, v33);
              ++classFileCount;
              classFile = Rules_ConstructCodeFileClose(classFile, &classFileCount, maxIndices, &v51, &v43, (int)v19);
              if ( !ObjectsCompiler_WriteClassLinkPointerArray(&v36, fileName, fileNameBuffer, pathName, fileIDCopy, &version, maxIndices, (int)j, &v52, &v28, &v44, &v20)
                || !ObjectsCompiler_WriteSlotDescArray(&v37, fileName, fileNameBuffer, pathName, fileIDCopy, &version, maxIndices, (int)j, &v53, &v29, &v45, &v21)
                || !ObjectsCompiler_WriteSlotDescPointerArray(&v38, fileName, fileNameBuffer, pathName, fileIDCopy, &version, maxIndices, (int)j, &v54, &v30, &v46, &v22)
                || !ObjectsCompiler_WriteSlotIndexMapArray(&v39, fileName, fileNameBuffer, pathName, fileIDCopy, &version, maxIndices, j, &v55, &v31, &v47, &v23)
                || !ObjectsCompiler_WriteHandlerArray(&v40, fileName, fileNameBuffer, pathName, fileIDCopy, &version, maxIndices, (int)j, &v56, &v32, &v48, &v24)
                || !ObjectsCompiler_WriteHandlerIndexMapArray(&v41, fileName, fileNameBuffer, pathName, fileIDCopy, &version, maxIndices, (int)j, &v57, &v33, &v49, v25) )
              {
                goto LABEL_20;
              }
            }
            i = Module_NextEnum(i);
            moduleIndex = v16 + 1;
          }
LABEL_20:
          ObjectsCompiler_CloseConstructFileGroup(&moduleFile, &v42, maxIndices, (int)v18);
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

