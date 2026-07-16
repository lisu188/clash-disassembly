/* Generated from src/recovered/rules/clips/004C82D0_methods.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004C82D0) --------------------------------------------------------
signed int  Method_FindByIndex(int gfunc, int theIndex)
{
  int methodCount; // edx
  signed int result; // eax
  _DWORD *i; // edx

  methodCount = *(_DWORD *)(uintptr_t)(gfunc + 32);
  result = 0;
  if ( !methodCount )
    return -1;
  for ( i = *(_DWORD **)(uintptr_t)(gfunc + 28); theIndex != *i; i += 10 )
  {
    if ( (unsigned int)++result >= *(_DWORD *)(uintptr_t)(gfunc + 32) )
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
    generic = Defgeneric_LookupWithImports(*(_BYTE **)(uintptr_t)(v10 + 16));
    if ( generic )
    {
      oldReentryFlag = Rules_GetReentryGuardFlag();
      Rules_SetReentryGuardFlag(1);
      oldGeneric = g_ClipsCurrentGeneric;
      g_ClipsCurrentGeneric = generic;
      ++g_ClipsCurrentEvaluationDepth;
      genericName = Rules_GetConstructNameString(generic);
      argCount = AST_CountListNodes(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10));
      ProcParam_PushEvaluatedArgumentFrame(
        *(_DWORD **)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10),
        argCount,
        (int)(intptr_t)aGenericFunct_1,
        genericName,
        a1,
        (int (*)(void))Method_PrintCallErrorBanner);
      if ( !g_ClipsEvaluationError )
      {
        ++*(_DWORD *)(uintptr_t)(generic + 20);
        Defgeneric_PrintApplicableMethods(generic, a1);
        --*(_DWORD *)(uintptr_t)(generic + 20);
      }
      ProcParam_PopFrame();
      g_ClipsCurrentGeneric = oldGeneric;
      --g_ClipsCurrentEvaluationDepth;
      return Rules_SetReentryGuardFlag(oldReentryFlag);
    }
    else
    {
      Rules_PrintErrorID((int)(intptr_t)aGenrcfun, 3, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aUnableToFindGe, v6);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(uintptr_t)(v10 + 16), v7);
      return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aInFunctionPrev, v8);
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
  meth = (_DWORD *)(uintptr_t)theMethod;
  *buf = 0;
  if ( (*(_BYTE *)(uintptr_t)(theMethod + 24) & 1) != 0 )
    strncpy_(a3, aSys);
  sprintf_(v13, "%-2d ", *meth);
  ((void (*)(void))(uintptr_t)strncat_)();
  result = meth;
  restrictionCount = meth[2];
  restrictionIndex = 0;
  if ( restrictionCount > 0 )
  {
    restrictionOffset = 0;
    do
    {
      v7 = (_DWORD *)(uintptr_t)(meth[7] + restrictionOffset);
      v8 = meth[2] - 1;
      restriction = v7;
      if ( (_DWORD *)(uintptr_t)v8 == restrictionIndex && meth[4] == -1 )
      {
        if ( !v7[2] && !restriction[1] )
        {
          strlen(buf);
          return (_DWORD *)(uintptr_t)((int (*)(void))(uintptr_t)strncat_)();
        }
        bufPtr = buf;
      }
      else
      {
        bufPtr = buf;
      }
      strlen(bufPtr);
      ((void (*)(void))(uintptr_t)strncat_)();
      typeIndex = 0;
      if ( restriction[2] )
      {
        typeOffset = 0;
        do
        {
          strlen(buf);
          Rules_GetConstructNameString(*(_DWORD *)(uintptr_t)(typeOffset + *restriction));
          ((void (*)(void))(uintptr_t)strncat_)();
          if ( typeIndex < restriction[2] - 1 )
          {
            strlen(buf);
            ((void (*)(void))(uintptr_t)strncat_)();
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
          ((void (*)(void))(uintptr_t)strncat_)();
        }
        strlen(buf);
        ((void (*)(void))(uintptr_t)strncat_)();
      }
      strlen(buf);
      ((void (*)(void))(uintptr_t)strncat_)();
      result = (_DWORD *)(uintptr_t)(meth[2] - 1);
      if ( result != restrictionIndex )
      {
        strlen(buf);
        result = (_DWORD *)(uintptr_t)((int (*)(void))(uintptr_t)strncat_)();
      }
      v12 = meth[2];
      restrictionOffset += 12;
      restrictionIndex = (_DWORD *)((char *)restrictionIndex + 1);
    }
    while ( (int)(intptr_t)restrictionIndex < v12 );
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
    Rules_PrintErrorID((int)(intptr_t)aGenrcfun, 3, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aUnableToFindGe, v4);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v5, v5);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aInFunction_2, v6);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], functionName, v7);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__23, v8);
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
    Rules_PrintErrorID((int)(intptr_t)aGenrcfun, 2, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aUnableToFindMe, v6);
    v7 = Rules_GetConstructNameString(generic);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v7, v8);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_50B158, v9);
    Rules_PrintLongInteger(v10, v10);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aInFunction_2, v11);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], functionName, v12);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__23, v13);
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
  if ( *(_DWORD *)(uintptr_t)(result + 32) )
  {
    methodOffset = 0;
    do
    {
      ++*(_DWORD *)(uintptr_t)(methodOffset + *(_DWORD *)(uintptr_t)(genericPtr + 28) + 4);
      if ( Method_RestrictionsSatisfiedByArgs(methodOffset + *(_DWORD *)(uintptr_t)(genericPtr + 28), a2) )
      {
        v6 = Rules_GetConstructNameString(genericPtr);
        Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, v6, v7);
        Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)asc_50B158, v8);
        Defgeneric_AppendMethodSignatureText(buf, 255, v9, methodOffset + *(_DWORD *)(uintptr_t)(v9 + 28));
        Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)buf, v10);
        foundApplicable = 1;
        Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)asc_50B160, v11);
      }
      --*(_DWORD *)(uintptr_t)(methodOffset + *(_DWORD *)(uintptr_t)(genericPtr + 28) + 4);
      ++methodIndex;
      result = *(_DWORD *)(uintptr_t)(genericPtr + 32);
      methodOffset += 40;
    }
    while ( methodIndex < result );
  }
  if ( !foundApplicable )
  {
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aNoApplicableMe, genericPtr);
    v13 = Rules_GetConstructNameString(v12);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, v13, (int)(intptr_t)g_IO_LogicalName_WDisplay);
    return Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)a__23, v14);
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
int Defgeneric_CompilerSetup(void)
{
  int result; // eax

  result = Rules_AddCodeGeneratorItem((int)(intptr_t)aGenerics, 0, 0, (int)(intptr_t)Defgeneric_BeforeCode, (int)(intptr_t)Defgeneric_DefgenericsToCode, 5);
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
             *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_DefgenericCodeGenItem + 20) + 4),
             fp,
             (int)(intptr_t)aSD_DD,
             *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_DefgenericCodeGenItem + 20) + 4));
  else
    return Output_WriteFormatted(imageID, 0, fp, (int)(intptr_t)aNull_4, v4);
}
// 4C8980: variable 'v4' is possibly undefined
// 54E8CC: using guessed type int dword_54E8CC;

//----- (004C89C0) --------------------------------------------------------
int  Defgeneric_PrintModuleReference(int fp, int imageID)
{
  return Output_WriteFormatted(imageID, **(_DWORD **)(uintptr_t)(g_DefgenericCodeGenItem + 20), fp, (int)(intptr_t)aMihsSD_DD, **(_DWORD **)(uintptr_t)(g_DefgenericCodeGenItem + 20));
}
// 54E8CC: using guessed type int dword_54E8CC;

//----- (004C8A00) --------------------------------------------------------
signed int Defgeneric_BeforeCode(void)
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
  Output_WriteFormatted(0, slotOffset, headerFPLocal, (int)(intptr_t)aIncludeGenrcfu, (char)(intptr_t)moduleNameBuf[0]);
  Enum = Module_NextEnum(0);
  if ( Enum )
  {
    while ( 1 )
    {
      Module_SetCurrent(Enum);
      nameBuffer = moduleNameBuf;
      structNames = *(const char ***)(uintptr_t)(g_DefgenericCodeGenItem + 20);
      v24 = moduleReopen;
      openedModuleFile = Rules_ConstructCodeFileOpen(moduleFile, fileNameLocal, imageIDLocal, pathNameLocal, &version, moduleArrayVersion, headerFPLocal, (char)(intptr_t)aDefgeneric_mod, *structNames, moduleReopen, moduleNameBuf);
      moduleFile = openedModuleFile;
      if ( !openedModuleFile )
        break;
      Defgeneric_ModuleToCode(openedModuleFile, Enum, maxIndices);
      moduleFile = Rules_ConstructCodeFileClose(moduleFile, &moduleCount, maxIndices, &moduleArrayVersion, &moduleReopen, (int)(intptr_t)moduleNameBuf);
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
               (char)(intptr_t)aDefgeneric_5,
               *(const char **)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_DefgenericCodeGenItem + 20) + 4),
               genericReopen,
               genericNameBuf);
        genericFile = openedGenericFile;
        if ( !openedGenericFile )
          goto LABEL_34;
        Defgeneric_SingleToCode(openedGenericFile, imageIDLocal, i, maxIndices, moduleIndex, methodArrayVersion, methodCount);
        ++genericCount;
        genericFile = Rules_ConstructCodeFileClose(genericFile, &genericCount, maxIndices, &genericArrayVersion, &genericReopen, (int)(intptr_t)genericNameBuf);
        if ( *(_DWORD *)(uintptr_t)(i + 32) )
        {
          nameBuffer = methodNameBuf;
          structNamesForMethod = *(_DWORD *)(uintptr_t)(g_DefgenericCodeGenItem + 20);
          v24 = methodReopen;
          methodFile = Rules_ConstructCodeFileOpen(methodFile, fileNameLocal, imageIDLocal, pathNameLocal, &version, methodArrayVersion, headerFPLocal, (char)(intptr_t)aDefmethod_2, *(const char **)(uintptr_t)(structNamesForMethod + 8), methodReopen, methodNameBuf);
          if ( !methodFile )
            goto LABEL_34;
          numMethods = *(_DWORD *)(uintptr_t)(i + 32);
          methodIndex = 0;
          if ( numMethods )
          {
            methodOffset = 0;
            do
            {
              methodPtr = *(_DWORD *)(uintptr_t)(i + 28) + methodOffset;
              if ( methodIndex )
                Output_WriteFormatted(v11, methodFile, methodFile, (int)(intptr_t)asc_50B1FC, (char)(intptr_t)moduleNameBuf[0]);
              Defgeneric_MethodToCode(methodFile, imageIDLocal, restrictionArrayVersion, methodPtr, restrictionCount);
              if ( *(int *)(uintptr_t)(methodPtr + 8) > 0 )
              {
                nameBuffer = restrictionNameBuf;
                structNamesForRestriction = *(_DWORD *)(uintptr_t)(g_DefgenericCodeGenItem + 20);
                v24 = restrictionReopen;
                restrictionFile = Rules_ConstructCodeFileOpen(
                        restrictionFile,
                        fileNameLocal,
                        imageIDLocal,
                        pathNameLocal,
                        &version,
                        restrictionArrayVersion,
                        headerFPLocal,
                        (char)(intptr_t)aRestriction,
                        *(const char **)(uintptr_t)(structNamesForRestriction + 12),
                        restrictionReopen,
                        restrictionNameBuf);
                if ( !restrictionFile )
                  goto LABEL_34;
                numRestrictions = *(_DWORD *)(uintptr_t)(methodPtr + 8);
                restrictionIndex = 0;
                if ( numRestrictions )
                {
                  restrictionOffset = 0;
                  do
                  {
                    restrictionPtr = (_DWORD *)(uintptr_t)(restrictionOffset + *(_DWORD *)(uintptr_t)(methodPtr + 28));
                    if ( restrictionIndex )
                      Output_WriteFormatted(restrictionIndex, restrictionOffset, restrictionFile, (int)(intptr_t)asc_50B1FC, (char)(intptr_t)moduleNameBuf[0]);
                    Defgeneric_RestrictionToCode(restrictionFile, imageIDLocal, typeArrayVersion, (int)(intptr_t)restrictionPtr, (DWORD)(intptr_t)restrictionPtr, typeCount);
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
                              (char)(intptr_t)aVoid_1,
                              *(const char **)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_DefgenericCodeGenItem + 20) + 16),
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
                            Output_WriteFormatted(typeFile, v16, typeFile, (int)(intptr_t)asc_50B1FC, (char)(intptr_t)moduleNameBuf[0]);
                          ++typeIndex;
                          Defgeneric_RestrictionTypeToCode(typeFile, maxIndices, *(_DWORD *)(uintptr_t)(typeOffset + *restrictionPtr));
                          typeOffset += 4;
                        }
                        while ( typeIndex < restrictionPtr[2] );
                      }
                      typeCount += restrictionPtr[2];
                      typeFile = Rules_ConstructCodeFileClose(typeFile, (int *)&typeCount, maxIndices, &typeArrayVersion, &typeReopen, (int)(intptr_t)typeNameBuf);
                    }
                    restrictionLimit = *(_DWORD *)(uintptr_t)(methodPtr + 8);
                    restrictionOffset += 12;
                    ++restrictionIndex;
                  }
                  while ( restrictionIndex < restrictionLimit );
                }
                restrictionCount += *(_DWORD *)(uintptr_t)(methodPtr + 8);
                restrictionFile = Rules_ConstructCodeFileClose(restrictionFile, &restrictionCount, maxIndices, &restrictionArrayVersion, &restrictionReopen, (int)(intptr_t)restrictionNameBuf);
              }
              v11 = methodOffset + 40;
              methodLimit = *(_DWORD *)(uintptr_t)(i + 32);
              methodOffset += 40;
              ++methodIndex;
            }
            while ( methodIndex < methodLimit );
          }
          methodCount += *(_DWORD *)(uintptr_t)(i + 32);
          methodFile = Rules_ConstructCodeFileClose(methodFile, &methodCount, maxIndices, &methodArrayVersion, &methodReopen, (int)(intptr_t)methodNameBuf);
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
    Defgeneric_CloseCodeFiles(&moduleFile, &moduleReopen, maxIndices, (int)(intptr_t)moduleNameBuf);
    return 0;
  }
  else
  {
LABEL_33:
    Defgeneric_CloseCodeFiles(&moduleFile, &moduleReopen, maxIndices, (int)(intptr_t)moduleNameBuf);
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

  Output_WriteFormatted(imageID, theModule, fp, (int)(intptr_t)asc_50B214, v9);
  Rules_WriteConstructModuleItemHeaderToCode(fp, v4, v5, g_DefgenericModuleItemIndex, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_DefgenericCodeGenItem + 20) + 4));
  return Output_WriteFormatted(v7, v6, fp, (int)(intptr_t)asc_50B218, v10);
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

  Output_WriteFormatted(gfunc, imageID, fp, (int)(intptr_t)asc_50B214, v16);
  Rules_WriteConstructHeaderToCode(fp, gfunc, maxIndices, moduleIndex, **(_DWORD **)(uintptr_t)(g_DefgenericCodeGenItem + 20), *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_DefgenericCodeGenItem + 20) + 4));
  Output_WriteFormatted(v10, v9, fp, (int)(intptr_t)a00_15, v17);
  v12 = *(_DWORD *)(uintptr_t)(gfunc + 28);
  if ( v12 )
    Output_WriteFormatted(methodArrayIndex, v12, fp, (int)(intptr_t)aSD_DD, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_DefgenericCodeGenItem + 20) + 8));
  else
    Output_WriteFormatted(v11, 0, fp, (int)(intptr_t)aNull_4, v18);
  return Output_WriteFormatted(v14, v13, fp, (int)(intptr_t)aU0, *(_DWORD *)(uintptr_t)(gfunc + 32));
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

  restrictionArrayName = *(_DWORD *)(uintptr_t)theMethod;
  Output_WriteFormatted(restrictionArrayIndex, imageID, fp, (int)(intptr_t)aU0DDDDU0, *(_DWORD *)(uintptr_t)theMethod);
  if ( *(_DWORD *)(uintptr_t)(theMethod + 28) )
  {
    v13 = *(_DWORD *)(uintptr_t)(g_DefgenericCodeGenItem + 20);
    restrictionArrayName = *(_DWORD *)(uintptr_t)(v13 + 12);
    Output_WriteFormatted(v8, v13, fp, (int)(intptr_t)aSD_DD_7, restrictionArrayName);
  }
  else
  {
    Output_WriteFormatted(v8, v7, fp, (int)(intptr_t)aNull_25, v14);
  }
  Rules_ExpressionToCode(fp, *(__int16 **)(uintptr_t)(theMethod + 32), v9, restrictionArrayName);
  return Output_WriteFormatted(v11, v10, fp, (int)(intptr_t)aNull_26, v14);
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

  Output_WriteFormatted(typeArrayIndex, imageID, fp, (int)(intptr_t)asc_50B214, v12);
  if ( *(_DWORD *)(uintptr_t)theRestriction )
  {
    a5 = maxIndices;
    Output_WriteFormatted(v8, *(_DWORD *)(uintptr_t)(g_DefgenericCodeGenItem + 20), fp, (int)(intptr_t)aSD_DD_7, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_DefgenericCodeGenItem + 20) + 16));
  }
  else
  {
    Output_WriteFormatted(v8, v7, fp, (int)(intptr_t)aNull_25, v13);
  }
  Rules_ExpressionToCode(fp, *(__int16 **)(uintptr_t)(theRestriction + 4), v9, a5);
  return Output_WriteFormatted(v10, *(_DWORD *)(uintptr_t)(theRestriction + 8), fp, (int)(intptr_t)aU, *(_DWORD *)(uintptr_t)(theRestriction + 8));
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

  Output_WriteFormatted(maxIndices, theClass, fp, (int)(intptr_t)aVs_1, v7);
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
  if ( !Rules_GetConstructNameAndComment(readSource, (int)(intptr_t)&g_ClipsMethodParserToken, (int (*)(void))Defgeneric_ParseConstruct, aDefgeneric_1, 0, asc_50B28C, 1, 1, 1)
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
      Rules_ReplaceConstructPPForm(v8, (int)(intptr_t)ppForm);
    }
    return 0;
  }
  else
  {
    Rules_PrintErrorID((int)(intptr_t)aGenrcpsr, 1, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aExpectedToComp, v6);
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
  gfunc = (_DWORD *)(uintptr_t)addedGeneric;
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
      Rules_UnlinkListNode((int)(intptr_t)gfunc);
      Defgeneric_RemoveDefgeneric((int)(intptr_t)gfunc);
      return 1;
    }
    return 1;
  }
  AST_Append(v8, v7);
  for ( i = restrictions; i; i = *(_DWORD *)(uintptr_t)(i + 10) )
  {
    Method_ReplaceCurrentArgumentRefs(*(int ***)(uintptr_t)(*(_DWORD *)(uintptr_t)(i + 6) + 4));
    if ( Parser_ReplaceProcVars((int)(intptr_t)aMethod, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(i + 6) + 4), wildcard, restrictions, 0, 0) )
      goto LABEL_19;
  }
  foundMethod = Method_FindInsertionIndex((int)(intptr_t)gfunc, restrictions, wildcard, parameterCount, (unsigned int *)&insertPosition);
  existingMethod = foundMethod;
  if ( foundMethod )
  {
    if ( (*(_BYTE *)(uintptr_t)(foundMethod + 24) & 1) != 0 )
    {
      Rules_PrintErrorID((int)(intptr_t)aGenrcpsr, 17, 0);
      errorMessage = aCannotReplaceT;
LABEL_17:
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)errorMessage, v12);
      conflictIndex = *conflictMethod;
LABEL_18:
      Rules_PrintLongInteger((int)(intptr_t)conflictMethod, conflictIndex);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__12, v16);
LABEL_19:
      Method_FreeRestrictionChain(restrictions);
      goto LABEL_9;
    }
    if ( methodIndex && methodIndex != *(_DWORD *)(uintptr_t)foundMethod )
    {
      Rules_PrintErrorID((int)(intptr_t)aGenrcpsr, 2, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aNewMethod, v24);
      Rules_PrintLongInteger(v25, methodIndex);
      errorMessage = aWouldBeIndisti;
      goto LABEL_17;
    }
  }
  else if ( methodIndex )
  {
    methodArrayIndex = Method_FindByIndex((int)(intptr_t)gfunc, methodIndex);
    if ( methodArrayIndex == -1 )
    {
      isNewMethod = 1;
    }
    else if ( (*(_BYTE *)(uintptr_t)(gfunc[7] + 40 * methodArrayIndex + 24) & 1) != 0 )
    {
      Rules_PrintErrorID((int)(intptr_t)aGenrcpsr, 17, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aCannotReplaceT, v27);
      conflictIndex = methodIndex;
      goto LABEL_18;
    }
  }
  else
  {
    isNewMethod = 1;
  }
  g_ClipsParseReturnContext = 1;
  if ( !Parser_ParseProcActions((int)(intptr_t)aMethod, readSource2, restrictions, wildcard, 0, 0, (int *)&localVarCount, 0) )
    goto LABEL_19;
  IO_OutNewline();
  IO_OutNewline();
  IO_OutWriteToken((char *)(uintptr_t)g_CLIPS_GenericParseTokenPrintStr);
  IO_OutWriteToken(asc_50B2C4);
  if ( Mem_GetAllocFlag() )
    ppForm = 0;
  else
    ppForm = Rules_CopyPPBuffer();
  Defgeneric_AddMethod(gfunc, existingMethod, methodIndex, insertPosition, restrictions, parameterCount, localVarCount, wildcard, actions, (unsigned int)(intptr_t)ppForm, 0);
  Method_FreeRestrictionChain(restrictions);
  if ( Rules_GetLoadInProgress() && Rules_GetWatchCompilations() )
  {
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], (int)(intptr_t)aMethod_0, v19);
    isNew = isNewMethod;
    Rules_PrintLongInteger((int)(intptr_t)definedMethodPtr, *definedMethodPtr);
    if ( isNew )
      definitionMsg = aDefined_;
    else
      definitionMsg = aRedefined_;
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], (int)(intptr_t)definitionMsg, v22);
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
        unsigned int localVarCount,
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

  methodSlot = (unsigned int *)(uintptr_t)existingMethod;
  insertIndex = position;
  g_Defgeneric_SavedBusyCount = gfunc[5];
  if ( existingMethod )
  {
    AST_DeinstallNodeChain(*(__int16 **)(uintptr_t)(existingMethod + 32));
    AST_FreePackedNodeChain(*(_DWORD *)(uintptr_t)(v33 + 32));
    if ( *(_DWORD *)(uintptr_t)(v34 + 36) )
      Mem_SmallBlockFree((_DWORD *)(uintptr_t)methodSlot[9], strlen(*(const char **)(uintptr_t)(v34 + 36)) + 1);
  }
  else if ( methodIndex && (existingIndex = Method_FindByIndex((int)(intptr_t)gfunc, methodIndex), foundIndex = existingIndex, existingIndex != -1) )
  {
    Defgeneric_DeleteMethodInfo((int)(intptr_t)gfunc, 40 * existingIndex + gfunc[7]);
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
          qmemcpy((void *)(uintptr_t)(gfunc[7] + backwardDest), (const void *)(uintptr_t)(gfunc[7] + backwardSrc), 0x28u);
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
          qmemcpy((void *)(uintptr_t)(forwardDest + gfunc[7]), (const void *)(uintptr_t)(gfunc[7] + forwardSrc), 0x28u);
          forwardDest += 40;
          forwardSrc += 40;
        }
        while ( forwardDest <= 40 * insertIndex - 40 );
      }
    }
    methodSlot = (unsigned int *)(uintptr_t)(40 * insertIndex + gfunc[7]);
    *methodSlot = methodIndex;
  }
  else
  {
    methodSlot = Defgeneric_InsertMethodSlot(gfunc, position, methodIndex);
  }
  *((_BYTE *)methodSlot + 24) &= ~1u;
  methodSlot[8] = (unsigned int)(intptr_t)actions;
  AST_InstallNodeChain(actions);
  methodSlot[9] = ppForm;
  if ( insertIndex != -1 )
  {
    methodSlot[5] = localVarCount;
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
      *(_DWORD *)(uintptr_t)(v15 + 28) = restrictionArray;
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
        *(_DWORD *)(uintptr_t)(restrictionPtr + 4) = AST_PackNodeChain(*(_DWORD **)(uintptr_t)(*(_DWORD *)(uintptr_t)(restrictions + 6) + 4));
        typeCount = sourceRestriction[2];
        *(_DWORD *)(uintptr_t)(restrictionPtr + 8) = typeCount;
        if ( copyRestrictions )
        {
          if ( *sourceRestriction )
          {
            typeArray = Mem_SmallBlockAlloc(4 * typeCount);
            copyTypeCount = *(_DWORD *)(uintptr_t)(restrictionPtr + 8);
            *(_DWORD *)(uintptr_t)restrictionPtr = typeArray;
            qmemcpy(typeArray, *v22, 4 * copyTypeCount);
          }
          else
          {
            *(_DWORD *)(uintptr_t)restrictionPtr = 0;
          }
        }
        else
        {
          *(_DWORD *)(uintptr_t)restrictionPtr = *sourceRestriction;
          sourceRestriction[2] = 0;
          *sourceRestriction = 0;
        }
        AST_InstallNodeChain(*(__int16 **)(uintptr_t)(restrictionPtr + 4));
        if ( *(_DWORD *)(uintptr_t)(restrictionPtr + 8) )
        {
          typeOffset = 0;
          do
          {
            Class_AddBusyReference(*(_DWORD *)(uintptr_t)(typeOffset + *(_DWORD *)(uintptr_t)restrictionPtr));
            typeOffset = v24 + 4;
          }
          while ( typeIndex < *(_DWORD *)(uintptr_t)(restrictionPtr + 8) );
        }
        restrictionOffset += 12;
        restrictions = *(_DWORD *)(uintptr_t)(restrictions + 10);
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
  for ( i = typeList; i; i = *(_DWORD *)(uintptr_t)(i + 10) )
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
      *(_DWORD *)(uintptr_t)(*restr + offset) = *(_DWORD *)(uintptr_t)(typeNode + 2);
      offset += 4;
      typeNode = *(_DWORD *)(uintptr_t)(typeNode + 10);
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

  for ( i = result; i; *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp )
  {
    current = (_DWORD *)(uintptr_t)i;
    i = *(_DWORD *)(uintptr_t)(i + 10);
    restriction = *(_DWORD *)((char *)current + 6);
    g_ClipsMemFreeListTemp = (int)(intptr_t)current;
    *current = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
    AST_Free(*(_DWORD *)(uintptr_t)(restriction + 4));
    typeCount = *(_DWORD *)(uintptr_t)(v4 + 8);
    if ( typeCount )
      Mem_SmallBlockFree(*(_DWORD **)(uintptr_t)v4, 4 * typeCount);
    g_ClipsMemFreeListTemp = v4;
    *(_DWORD *)(uintptr_t)v4 = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
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
  if ( *(_DWORD *)(uintptr_t)(gfunc + 32) )
  {
    methodOffset = 0;
    while ( 1 )
    {
      comparison = Method_CompareRestrictionOrder(params, restrictionCount, maxRestrictions, minRestrictions, (_DWORD *)(uintptr_t)(methodOffset + *(_DWORD *)(uintptr_t)(gfunc + 28)));
      if ( !comparison )
        break;
      if ( comparison != -1 )
      {
        ++methodIndex;
        methodOffset += 40;
        if ( methodIndex < *(_DWORD *)(uintptr_t)(gfunc + 32) )
          continue;
      }
      goto LABEL_8;
    }
    *position = -1;
    return methodOffset + *(_DWORD *)(uintptr_t)(gfunc + 28);
  }
  else
  {
LABEL_8:
    *position = methodIndex;
    return 0;
  }
}

//----- (004C9C20) --------------------------------------------------------
signed int Defgeneric_ParseDeclaration(void)
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
    Rules_PrintErrorID((int)(intptr_t)aGenrcpsr, 3, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDefgenericsAre, v14);
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
        Rules_PrintErrorID((int)(intptr_t)aGenrcpsr, 5, 0);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDefgenericsA_0, v15);
      }
      else
      {
        Rules_PrintErrorID((int)(intptr_t)aGenrcpsr, 4, 0);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDeffunction_0, v6);
        v7 = Rules_GetConstructNameString(deffunction);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v7, v8);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aImportedFromMo, v9);
        Name = Module_GetName(v10);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], Name, (int)(intptr_t)g_IO_LogicalNameTable_WError[0]);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aConflictsWithT, v12);
      }
      return 0;
    }
    else
    {
      existingGeneric = Defgeneric_ParseConstruct(v2, (int)(intptr_t)v2);
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
          Rules_PrintErrorID((int)(intptr_t)aGenrcpsr, 16, 0);
          Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aTheSystemFunct, v19);
          Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v20, v20);
          Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aCannotBeOverlo, v21);
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
  Name = (const char *)(uintptr_t)Module_GetName(v2);
  genericName = (const char *)(uintptr_t)Rules_GetConstructNameString(gfunc);
  ppForm = Mem_SmallBlockAlloc(strlen(genericName) + strlen(Name) + 17);
  sprintf_(ppForm, "(defgeneric %s::%s)\n", Name, v6);
  return Rules_ReplaceConstructPPForm(gfunc, v7);
}
// 4C9DFA: variable 'v6' is possibly undefined
// 4C9E06: variable 'v7' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
