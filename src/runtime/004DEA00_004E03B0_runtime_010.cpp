/* Generated from src/recovered/runtime/004D0560_legacy_runtime.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "runtime_internal.h"
#include "runtime_state.h"
#include "runtime_shared_state.h"
#include "../clips/clips_api.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004DEA00) --------------------------------------------------------
int  Method_ParseWildcardRestrictionString(_DWORD *theDefgeneric, char *restrictionString, int a3, _DWORD *theActions)
{
  _DWORD *freeRestriction; // edx
  signed int restrictionMem; // eax
  int defaultRestriction; // esi
  _DWORD *freeTypeInfo; // ecx
  _DWORD *defaultTypeInfo; // ecx
  int v9; // ecx
  _DWORD *defaultActions; // eax
  __int16 *defaultPackedActions; // eax
  unsigned int *defaultMethod; // eax
  int v14; // ecx
  int restrictionList; // esi
  int restrictionCount; // edi
  char *reqTypeCharPtr; // ebp
  char *v18; // eax
  char reqTypeChar; // al
  _DWORD *typeInfo; // ecx
  _DWORD *reqFreeRestriction; // ebx
  signed int newRestriction; // eax
  int argCount; // ebp
  char *charPtr; // edi
  int maxArgsCopy; // ebx
  _DWORD *wildcardTypeInfo; // edi
  int **Symbol; // eax
  signed int wildcardExprNode; // eax
  int v29; // ecx
  int **lengthSymbol; // eax
  signed int lengthNode; // eax
  int v32; // ecx
  int optionalArgsCopy; // ebp
  signed int procParamNode; // eax
  int v35; // ecx
  int *wildcardCountValue; // eax
  signed int countNode; // eax
  int v38; // ecx
  _DWORD *wildcardFreeRestriction; // ebp
  signed int wildcardRestriction; // eax
  int wildcardArgCount; // edi
  __int16 *wildcardPackedActions; // eax
  unsigned int *wildcardMethod; // eax
  int excessRestrictions; // eax
  __int16 *minPackedActions; // eax
  unsigned int *minMethod; // eax
  _DWORD *optionalTypeInfo; // ecx
  _DWORD *optFreeRestriction; // ebx
  signed int optionalRestriction; // eax
  char nextTypeChar; // dh
  __int16 *optPackedActions; // eax
  unsigned int *optMethod; // eax
  signed int lastRequiredRestriction; // [esp+0h] [ebp-44h]
  int methodPosition; // [esp+4h] [ebp-40h] BYREF
  int createMinimumMethod; // [esp+8h] [ebp-3Ch]
  _DWORD *actions; // [esp+Ch] [ebp-38h]
  char *str; // [esp+10h] [ebp-34h]
  int minArgs; // [esp+14h] [ebp-30h]
  int maxArgs; // [esp+18h] [ebp-2Ch]
  int optionalArgs; // [esp+1Ch] [ebp-28h]
  _DWORD *defgeneric; // [esp+20h] [ebp-24h]
  int argPosition; // [esp+24h] [ebp-20h]
  signed int lastRestriction; // [esp+28h] [ebp-1Ch]
  int charIndex; // [esp+2Ch] [ebp-18h]
  char curChar CLASH95_UNUSED; // [esp+30h] [ebp-14h]
  char v66 CLASH95_UNUSED; // [esp+31h] [ebp-13h]
  char defaultTypeChar; // [esp+34h] [ebp-10h]

  defgeneric = theDefgeneric;
  str = restrictionString;
  actions = theActions;
  if ( restrictionString )
  {
    v66 = 0;
    if ( *restrictionString == 42 )
    {
      v14 = 0;
      minArgs = 0;
    }
    else
    {
      curChar = *str;
      minArgs = atoi_(((const char*)(intptr_t)(a3)));
    }
    if ( str[1] == 42 )
    {
      maxArgs = -1;
    }
    else
    {
      curChar = str[1];
      maxArgs = atoi_(((const char*)(intptr_t)(v14)));
    }
    if ( str[2] )
    {
      defaultTypeChar = str[2];
      charIndex = 3;
    }
    else
    {
      defaultTypeChar = 117;
      charIndex = 2;
    }
    restrictionList = 0;
    restrictionCount = 0;
    lastRestriction = 0;
    if ( minArgs > 0 )
    {
      reqTypeCharPtr = &str[charIndex];
      do
      {
        if ( *reqTypeCharPtr )
        {
          v18 = &str[charIndex];
          ++reqTypeCharPtr;
          ++charIndex;
          reqTypeChar = *v18;
        }
        else
        {
          reqTypeChar = defaultTypeChar;
        }
        curChar = reqTypeChar;
        typeInfo = Method_BuildTypeRestrictionRecordFromFlags();
        reqFreeRestriction = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56);
        if ( reqFreeRestriction )
        {
          g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56);
          *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56) = *reqFreeRestriction;
          newRestriction = g_ClipsMemFreeListTemp;
        }
        else
        {
          newRestriction = Mem_HeapAllocWithRetry((_DWORD *)0xE);
        }
        *(_DWORD *)(uintptr_t)(newRestriction + 10) = 0;
        *(_DWORD *)(uintptr_t)(newRestriction + 6) = ((_DWORD)(uintptr_t)(typeInfo));
        if ( restrictionList )
          *(_DWORD *)(uintptr_t)(lastRestriction + 10) = newRestriction;
        else
          restrictionList = newRestriction;
        ++restrictionCount;
        lastRestriction = newRestriction;
      }
      while ( restrictionCount < minArgs );
    }
    lastRequiredRestriction = lastRestriction;
    argCount = minArgs;
    argPosition = minArgs + 1;
    createMinimumMethod = 1;
    optionalArgs = 0;
    charPtr = &str[charIndex];
    if ( str[charIndex] )
    {
      while ( charPtr[1] || argPosition != maxArgs )
      {
        optionalTypeInfo = Method_BuildTypeRestrictionRecordFromFlags();
        optFreeRestriction = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56);
        if ( optFreeRestriction )
        {
          g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56);
          *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56) = *optFreeRestriction;
          optionalRestriction = g_ClipsMemFreeListTemp;
        }
        else
        {
          optionalRestriction = Mem_HeapAllocWithRetry((_DWORD *)0xE);
        }
        *(_DWORD *)(uintptr_t)(optionalRestriction + 10) = 0;
        *(_DWORD *)(uintptr_t)(optionalRestriction + 6) = ((_DWORD)(uintptr_t)(optionalTypeInfo));
        if ( restrictionList )
          *(_DWORD *)(uintptr_t)(lastRestriction + 10) = optionalRestriction;
        else
          restrictionList = optionalRestriction;
        lastRestriction = optionalRestriction;
        ++argCount;
        ++charPtr;
        ++argPosition;
        ++optionalArgs;
        nextTypeChar = *charPtr;
        ++charIndex;
        if ( nextTypeChar || argCount == maxArgs )
        {
          Method_FindInsertionIndex((int)(intptr_t)defgeneric, restrictionList, 0, argCount, (unsigned int *)&methodPosition);
          optPackedActions = (__int16 *)AST_PackNodeChain(actions);
          optMethod = Defgeneric_AddMethod(defgeneric, 0, 0, methodPosition, restrictionList, argCount, 0, 0, optPackedActions, 0, 1);
          *((_BYTE *)optMethod + 24) |= 1u;
          if ( !*charPtr )
            goto LABEL_28;
        }
        else if ( !*charPtr )
        {
          goto LABEL_28;
        }
      }
      defaultTypeChar = *charPtr;
    }
LABEL_28:
    if ( optionalArgs + minArgs != maxArgs )
    {
      if ( !optionalArgs )
        createMinimumMethod = 0;
      maxArgsCopy = maxArgs;
      wildcardTypeInfo = Method_BuildTypeRestrictionRecordFromFlags();
      if ( maxArgsCopy != -1 )
      {
        Symbol = Rules_MakeSymbol(((_BYTE*)(asc_50E04C)));
        wildcardExprNode = AST_NewNode(10, (int)(intptr_t)Symbol);
        *(_DWORD *)(uintptr_t)(v29 + 4) = wildcardExprNode;
        lengthSymbol = Rules_MakeSymbol(((_BYTE*)(aLength_1)));
        lengthNode = AST_NewNode(10, (int)(intptr_t)lengthSymbol);
        optionalArgsCopy = optionalArgs;
        *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v32 + 4) + 6) = lengthNode;
        procParamNode = AST_NewProcParamNode(optionalArgsCopy + minArgs + 1);
        *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v35 + 4) + 6) + 6) = procParamNode;
        wildcardCountValue = ((int*)(intptr_t)(Rules_AddIntegerValue(maxArgsCopy - minArgs - optionalArgsCopy)));
        countNode = AST_NewNode(1, (int)(intptr_t)wildcardCountValue);
        *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v38 + 4) + 6) + 10) = countNode;
      }
      wildcardFreeRestriction = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56);
      if ( wildcardFreeRestriction )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56);
        *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56) = *wildcardFreeRestriction;
        wildcardRestriction = g_ClipsMemFreeListTemp;
      }
      else
      {
        wildcardRestriction = Mem_HeapAllocWithRetry((_DWORD *)0xE);
      }
      *(_DWORD *)(uintptr_t)(wildcardRestriction + 10) = 0;
      *(_DWORD *)(uintptr_t)(wildcardRestriction + 6) = ((_DWORD)(uintptr_t)(wildcardTypeInfo));
      if ( restrictionList )
        *(_DWORD *)(uintptr_t)(lastRestriction + 10) = wildcardRestriction;
      else
        restrictionList = wildcardRestriction;
      wildcardArgCount = optionalArgs + minArgs + 1;
      Method_FindInsertionIndex((int)(intptr_t)defgeneric, restrictionList, g_ClipsTrueSymbol, wildcardArgCount, (unsigned int *)&methodPosition);
      wildcardPackedActions = (__int16 *)AST_PackNodeChain(actions);
      wildcardMethod = Defgeneric_AddMethod(defgeneric, 0, 0, methodPosition, restrictionList, wildcardArgCount, 0, g_ClipsTrueSymbol, wildcardPackedActions, 0, 0);
      *((_BYTE *)wildcardMethod + 24) |= 1u;
    }
    if ( createMinimumMethod )
    {
      if ( lastRequiredRestriction )
      {
        excessRestrictions = *(_DWORD *)(uintptr_t)(lastRequiredRestriction + 10);
        *(_DWORD *)(uintptr_t)(lastRequiredRestriction + 10) = 0;
        Method_FreeRestrictionChain(excessRestrictions);
      }
      Method_FindInsertionIndex((int)(intptr_t)defgeneric, restrictionList, 0, minArgs, (unsigned int *)&methodPosition);
      minPackedActions = (__int16 *)AST_PackNodeChain(actions);
      minMethod = Defgeneric_AddMethod(defgeneric, 0, 0, methodPosition, restrictionList, minArgs, 0, 0, minPackedActions, 0, 1);
      *((_BYTE *)minMethod + 24) |= 1u;
    }
    return Method_FreeRestrictionChain(restrictionList);
  }
  else
  {
    freeRestriction = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56);
    if ( freeRestriction )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56) = *freeRestriction;
      restrictionMem = g_ClipsMemFreeListTemp;
    }
    else
    {
      restrictionMem = Mem_HeapAllocWithRetry((_DWORD *)0xE);
    }
    defaultRestriction = restrictionMem;
    freeTypeInfo = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
    if ( freeTypeInfo )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = *freeTypeInfo;
      defaultTypeInfo = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
    }
    else
    {
      defaultTypeInfo = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0xC);
    }
    Method_PackRestrictionTypes(defaultTypeInfo, 0);
    *(_DWORD *)(uintptr_t)(v9 + 4) = 0;
    *(_DWORD *)(uintptr_t)(defaultRestriction + 10) = 0;
    defaultActions = actions;
    *(_DWORD *)(uintptr_t)(defaultRestriction + 6) = v9;
    defaultPackedActions = (__int16 *)AST_PackNodeChain(defaultActions);
    defaultMethod = Defgeneric_AddMethod(defgeneric, 0, 0, 0, defaultRestriction, 1, 0, g_ClipsTrueSymbol, defaultPackedActions, 0, 0);
    *((_BYTE *)defaultMethod + 24) |= 1u;
    return Method_FreeRestrictionChain(defaultRestriction);
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
_DWORD *Method_BuildTypeRestrictionRecordFromFlags(void)
{
  _DWORD *freeListEntry; // edx
  signed int typeExprList; // esi
  signed int allocatedBlock; // eax
  _DWORD *restrictionRecord; // ebp
  char *keywordFlags; // eax
  char flagsByte; // dl
  char *flagsBitmap; // edi
  char *lexemeClassName; // ecx
  int lexemeTypeCode; // ebx
  char *numberClassName; // ecx
  int numberTypeCode; // ebx
  int v11; // eax
  char *instanceClassName; // ecx
  int instanceTypeCode; // ebx
  int v14; // eax
  char *addressClassName; // ecx
  int addressTypeCode; // ebx
  int v17; // eax

  freeListEntry = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
  typeExprList = 0;
  if ( freeListEntry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = *freeListEntry;
    allocatedBlock = g_ClipsMemFreeListTemp;
  }
  else
  {
    allocatedBlock = Mem_HeapAllocWithRetry((_DWORD *)0xC);
  }
  restrictionRecord = (_DWORD *)(uintptr_t)allocatedBlock;
  *(_DWORD *)(uintptr_t)(allocatedBlock + 4) = 0;
  keywordFlags = ((char*)(Rules_ApplyPatternKeywordFlags()));
  flagsByte = *keywordFlags;
  flagsBitmap = keywordFlags;
  if ( (*keywordFlags & 1) != 0 )
    goto LABEL_23;
  if ( (flagsByte & 2) != 0 && (flagsByte & 4) != 0 )
  {
    lexemeClassName = aLexeme;
    lexemeTypeCode = -1;
  }
  else if ( (*keywordFlags & 2) != 0 )
  {
    lexemeTypeCode = 2;
    lexemeClassName = 0;
  }
  else
  {
    if ( (*keywordFlags & 4) == 0 )
      goto LABEL_8;
    lexemeTypeCode = 3;
    lexemeClassName = 0;
  }
  typeExprList = Method_AddTypeRestrictionNode(0, ((_BYTE*)(lexemeClassName)), lexemeTypeCode);
LABEL_8:
  if ( (*flagsBitmap & 8) != 0 && (*flagsBitmap & 0x10) != 0 )
  {
    numberClassName = aNumber_0;
    numberTypeCode = -1;
    v11 = typeExprList;
  }
  else if ( (*flagsBitmap & 0x10) != 0 )
  {
    numberTypeCode = 1;
    v11 = typeExprList;
    numberClassName = 0;
  }
  else
  {
    if ( (*flagsBitmap & 8) == 0 )
      goto LABEL_12;
    v11 = typeExprList;
    numberClassName = 0;
    numberTypeCode = 0;
  }
  typeExprList = Method_AddTypeRestrictionNode(v11, ((_BYTE*)(numberClassName)), numberTypeCode);
LABEL_12:
  if ( (*flagsBitmap & 0x20) != 0 && (*flagsBitmap & 0x40) != 0 )
  {
    instanceClassName = aInstance_0;
    instanceTypeCode = -1;
    v14 = typeExprList;
  }
  else if ( (*flagsBitmap & 0x20) != 0 )
  {
    instanceTypeCode = 8;
    v14 = typeExprList;
    instanceClassName = 0;
  }
  else
  {
    if ( (*flagsBitmap & 0x40) == 0 )
      goto LABEL_16;
    instanceTypeCode = 7;
    v14 = typeExprList;
    instanceClassName = 0;
  }
  typeExprList = Method_AddTypeRestrictionNode(v14, ((_BYTE*)(instanceClassName)), instanceTypeCode);
LABEL_16:
  if ( *flagsBitmap < 0 && (*flagsBitmap & 0x40) != 0 && (flagsBitmap[1] & 1) != 0 )
  {
    addressClassName = aAddress;
    addressTypeCode = -1;
    v17 = typeExprList;
  }
  else
  {
    if ( *flagsBitmap < 0 )
      typeExprList = Method_AddTypeRestrictionNode(typeExprList, 0, 5);
    if ( (*flagsBitmap & 0x40) != 0 && (*flagsBitmap & 0x20) == 0 )
      typeExprList = Method_AddTypeRestrictionNode(typeExprList, 0, 7);
    if ( (flagsBitmap[1] & 1) == 0 )
      goto LABEL_21;
    addressTypeCode = 6;
    v17 = typeExprList;
    addressClassName = 0;
  }
  typeExprList = Method_AddTypeRestrictionNode(v17, ((_BYTE*)(addressClassName)), addressTypeCode);
LABEL_21:
  if ( flagsBitmap[1] < 0 )
    typeExprList = Method_AddTypeRestrictionNode(typeExprList, 0, 4);
LABEL_23:
  AST_DecrementNodeRefCount(((_DWORD*)(flagsBitmap)));
  Method_PackRestrictionTypes(restrictionRecord, typeExprList);
  return restrictionRecord;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004DF120) --------------------------------------------------------
signed int  Method_AddTypeRestrictionNode(int nextNode, _BYTE *className, int typeCode)
{
  signed int result; // eax
  int *theClass; // eax

  if ( typeCode == -1 )
  {
    theClass = Class_LookupByQualifiedName(className);
    result = AST_NewNode(0, (int)(intptr_t)theClass);
  }
  else
  {
    result = AST_NewNode(0, g_ClipsPrimitiveTypeClassMap[typeCode]);
  }
  *(_DWORD *)(uintptr_t)(result + 10) = nextNode;
  return result;
}
// 51AD7C: using guessed type int dword_51AD7C[];

//----- (004DF160) --------------------------------------------------------
signed int  MessageHandler_ParseDefinition(int readSource)
{
  int v2; // edx
  int classNameSymbol; // eax
  int *lookupClass; // eax
  int v6; // edx
  int v7; // edx
  int v8; // ecx
  int v9; // edx
  _DWORD *foundHandler; // ebp
  _DWORD *handler; // esi
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  char *statusText; // edx
  signed int selfParamNode; // eax
  int v19; // edx
  int handlerParams; // ebp
  int v21; // ecx
  int v22; // ecx
  int classNameString; // eax
  int v24; // ecx
  int v25; // ecx
  int v26; // ecx
  int v27; // ecx
  int v28; // ecx
  int v29; // ecx
  __int16 *actionsInstallPtr; // eax
  int v31; // edx
  int wildcardSymbol; // [esp+0h] [ebp-40h] BYREF
  int minParams; // [esp+4h] [ebp-3Ch] BYREF
  int maxParams; // [esp+8h] [ebp-38h] BYREF
  int parseError; // [esp+Ch] [ebp-34h] BYREF
  int localVarCount; // [esp+10h] [ebp-30h] BYREF
  __int16 *handlerActions; // [esp+14h] [ebp-2Ch]
  int paramsToFree; // [esp+18h] [ebp-28h]
  int handlerNameSymbol; // [esp+1Ch] [ebp-24h]
  int *handlerClass; // [esp+20h] [ebp-20h]
  int handlerType; // [esp+24h] [ebp-1Ch]

  Rules_SetPPBufferStatus(1);
  Rules_FlushPPBuffer();
  Rules_SetIndentDepth(3);
  handlerType = v2;
  IO_OutWriteToken(aDefmessageHa_1);
  if ( Rules_IsBloaded() )
  {
    Rules_ReportCannotLoadWithBload();
    return 1;
  }
  classNameSymbol = Rules_GetConstructNameAndComment(readSource, (int)(intptr_t)&g_ParserCurrentTokenType, 0, aDefmessageHa_2, 0, asc_50E0A8, 1, 0, 1);
  if ( !classNameSymbol )
    return 1;
  lookupClass = Class_LookupByQualifiedName((_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(classNameSymbol + 16));
  handlerClass = lookupClass;
  if ( !lookupClass )
  {
    Rules_PrintErrorID((int)(intptr_t)aMsgpsr, 1, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aAClassMustBeDe, v21);
    return 1;
  }
  if ( lookupClass == (int *)(uintptr_t)g_Class_InstanceName || lookupClass == (int *)(uintptr_t)g_Class_InstanceAddress || lookupClass == **(int ***)(uintptr_t)(g_Class_InstanceName + 36) )
  {
    Rules_PrintErrorID((int)(intptr_t)aMsgpsr, 8, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aMessageHandl_1, v22);
    classNameString = Rules_GetConstructNameString((int)(intptr_t)handlerClass);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], classNameString, v24);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__13, v25);
    return 1;
  }
  if ( MessageHandler_AnyHandlerBusy((int)(intptr_t)lookupClass) )
  {
    Rules_PrintErrorID((int)(intptr_t)aMsgpsr, 2, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aCannotReDefine, v26);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aOtherMessageHa, v27);
    return 1;
  }
  if ( g_ParserCurrentTokenType != 2 )
    goto LABEL_29;
  IO_OutNewline();
  IO_OutNewline();
  IO_OutWriteToken(asc_50E190);
  IO_OutWriteToken((char *)(uintptr_t)g_ClipsScanTokenPrintForm);
  IO_OutWriteToken(asc_50E190);
  handlerNameSymbol = g_ClipsParserTokenValue;
  Parser_NextToken(readSource, (int)(intptr_t)&g_ParserCurrentTokenType);
  if ( g_ParserCurrentTokenType == 100 )
    goto LABEL_17;
  IO_OutWriteToken(asc_50E190);
  if ( g_ParserCurrentTokenType != 3 )
  {
    if ( g_ParserCurrentTokenType == 2 )
    {
      handlerType = MessageHandler_TypeIndexFromKeyword((int)(intptr_t)aDefmessageHa_2);
      if ( handlerType == 4 )
        return 1;
      Parser_NextToken(readSource, (int)(intptr_t)&g_ParserCurrentTokenType);
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
  Parser_NextToken(readSource, v6);
LABEL_17:
  IO_OutNewline();
  IO_OutNewline();
  AST_Append(v8, v7);
  IO_OutWriteToken((char *)(uintptr_t)g_ClipsScanTokenPrintForm);
  foundHandler = Class_FindMessageHandler(((_DWORD*)(handlerClass)), v9, handlerType);
  handler = foundHandler;
  if ( Rules_GetLoadInProgress() && Rules_GetWatchCompilations() )
  {
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], (int)(intptr_t)aHandler, v12);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], *(_DWORD *)(uintptr_t)(handlerNameSymbol + 16), v13);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], (int)(intptr_t)asc_50E190, v14);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], (int)(intptr_t)g_MessageHandlerTypeNames[handlerType], v15);
    if ( foundHandler )
      statusText = aRedefined__0;
    else
      statusText = aDefined__0;
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], (int)(intptr_t)statusText, v16);
  }
  if ( foundHandler && (*foundHandler & 1) != 0 )
  {
    Rules_PrintErrorID((int)(intptr_t)aMsgpsr, 3, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aSystemMessageH, v28);
    return 1;
  }
  else
  {
    selfParamNode = AST_NewNode(2, g_MessageHandler_SelfSymbol);
    handlerParams = Parser_ParseProcParameters(readSource, ((_DWORD*)(&g_ParserCurrentTokenType)), ((_DWORD*)(&wildcardSymbol)), selfParamNode, ((_DWORD*)(&minParams)), ((_DWORD*)(&maxParams)), ((_DWORD*)(&parseError)), (int (*)(void))MessageHandler_CheckParamNotSelfReference);
    paramsToFree = handlerParams;
    if ( parseError )
    {
      return 1;
    }
    else
    {
      AST_Append((int)(intptr_t)handlerClass, v19);
      g_ClipsParseReturnContext = 1;
      handlerActions = (__int16 *)Parser_ParseProcActions(
                         (int)(intptr_t)aMessageHandl_2,
                         readSource,
                         handlerParams,
                         wildcardSymbol,
                         (int (*)(void))MessageHandler_ResolveSelfSlotGetRef,
                         (int (*)(void))MessageHandler_ResolveSelfSlotBindRef,
                         &localVarCount,
                         v29);
      if ( handlerActions )
      {
        if ( g_ParserCurrentTokenType == 101 )
        {
          IO_OutNewline();
          IO_OutNewline();
          IO_OutWriteToken((char *)(uintptr_t)g_ClipsScanTokenPrintForm);
          IO_OutWriteToken(asc_50E1FC);
          if ( handler )
          {
            AST_DeinstallNodeChain((__int16 *)(uintptr_t)handler[7]);
            AST_FreePackedNodeChain(handler[7]);
            if ( handler[8] )
              Mem_SmallBlockFree((_DWORD *)(uintptr_t)handler[8], strlen((const char *)(uintptr_t)handler[8]) + 1);
          }
          else
          {
            handler = Class_InsertMessageHandlerRecord(((_DWORD*)(handlerClass)), handlerNameSymbol, handlerType);
            ++*(_DWORD *)(uintptr_t)(handler[2] + 4);
          }
          AST_Free(paramsToFree);
          handler[4] = minParams;
          handler[5] = maxParams;
          handler[6] = localVarCount;
          actionsInstallPtr = handlerActions;
          handler[7] = ((_DWORD)(uintptr_t)(handlerActions));
          AST_InstallNodeChain(actionsInstallPtr);
          if ( Mem_GetAllocFlag() )
            handler[8] = 0;
          else
            handler[8] = ((_DWORD)(uintptr_t)(Rules_CopyPPBuffer()));
          return 0;
        }
        else
        {
          Parser_ReportSyntaxError();
          AST_Free(handlerParams);
          AST_FreePackedNodeChain(v31);
          return 1;
        }
      }
      else
      {
        AST_Free(handlerParams);
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
  char slotFlags; // dl
  unsigned int bufferSize; // edi
  int v3; // edx
  int v4; // ecx
  int v5; // edx
  int v6; // ecx
  const char *v7; // edx
  const char *paramPrefix; // eax
  const char *v9; // edx
  int v10; // ecx
  int v11; // edx
  _DWORD *v12; // ecx
  int savedLoadInProgress; // [esp+0h] [ebp-14h]
  const char *className; // [esp+8h] [ebp-Ch]
  const char *slotName; // [esp+Ch] [ebp-8h]
  _BYTE *slotDescPtr; // [esp+10h] [ebp-4h]

  slotDescPtr = (_BYTE *)(uintptr_t)result;
  slotFlags = *(_BYTE *)(uintptr_t)(result + 1);
  if ( (slotFlags & 8) != 0 || (slotFlags & 0x10) != 0 )
  {
    className = (const char *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(result + 4) + 16);
    slotName = (const char *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(result + 8) + 12) + 16);
    bufferSize = strlen(className) + 2 * strlen(slotName) + 80;
    Mem_SmallBlockAlloc(bufferSize);
    savedLoadInProgress = Rules_GetLoadInProgress();
    Rules_SetLoadInProgress(0);
    Mem_SetAllocFlag(v4, v3);
    if ( (slotDescPtr[1] & 8) != 0 )
    {
      sprintf_(((char*)(intptr_t)(v5)), "%s get-%s () ?self:%s)", className, slotName, slotName);
      if ( IO_OpenStringSource((int)(intptr_t)aDefaultPublicH, v7, 0) )
      {
        MessageHandler_ParseDefinition((int)(intptr_t)aDefaultPublicH);
        Rules_DestroyPPBuffer();
        IO_CloseStringRouter((int)(intptr_t)aDefaultPublicH);
      }
    }
    if ( (slotDescPtr[1] & 0x10) != 0 )
    {
      if ( (*slotDescPtr & 2) != 0 )
        paramPrefix = aAccessorSetterMultifieldParamPrefix;
      else
        paramPrefix = aAccessorSetterSinglefieldParamPrefix;
      sprintf_(((char*)(intptr_t)(v6)), "%s put-%s (%svalue) (bind ?self:%s ?value))", className, slotName, paramPrefix, slotName);
      if ( IO_OpenStringSource((int)(intptr_t)aDefaultPublicH, v9, 0) )
      {
        MessageHandler_ParseDefinition((int)(intptr_t)aDefaultPublicH);
        Rules_DestroyPPBuffer();
        IO_CloseStringRouter((int)(intptr_t)aDefaultPublicH);
      }
    }
    Rules_SetLoadInProgress(savedLoadInProgress);
    Mem_SetAllocFlag(v10, bufferSize);
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
signed int  MessageHandler_CheckParamNotSelfReference(int paramName)
{
  int v1; // ecx
  int v3; // ecx

  if ( strncmp_(paramName, (_DWORD)(uintptr_t)aSelf_0, 4) || *(_BYTE *)(uintptr_t)(v1 + 4) != 58 )
    return 0;
  Rules_PrintErrorID((int)(intptr_t)aMsgpsr, 4, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aIllegalSlotRef, v3);
  return 1;
}
// 4DF7C8: variable 'v1' is possibly undefined
// 4DF7F7: variable 'v3' is possibly undefined
// 48A1ED: using guessed type int __fastcall strncmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];

//----- (004DF810) --------------------------------------------------------
signed int  MessageHandler_ResolveSelfSlotGetRef(int varExpr, int theClass, int varName CLASH95_UNUSED)
{
  int v6; // edx
  int v7; // ecx
  int slotDesc; // eax
  int v9; // ecx
  int tokenType; // [esp+0h] [ebp-1Ch]
  int tokenValue; // [esp+4h] [ebp-18h]

  if ( *(_WORD *)(uintptr_t)varExpr != 15 && *(_WORD *)(uintptr_t)varExpr != 16 )
    return 0;
  if ( strncmp_(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(varExpr + 2) + 16), (_DWORD)(uintptr_t)aSelf_0, 4) )
    return 0;
  if ( *(_BYTE *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(varExpr + 2) + 16) + 4) != 58 )
    return 0;
  IO_OpenStringSource((int)(intptr_t)aHndVar, (const char *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(varExpr + 2) + 16) + 5), 0);
  Rules_GetPPBufferStatus();
  Rules_SetPPBufferStatus(0);
  Parser_NextToken((int)(intptr_t)aHndVar, v6);
  Rules_SetPPBufferStatus(v7);
  IO_CloseStringRouter((int)(intptr_t)aHndVar);
  if ( tokenType == 102 )
    return 0;
  slotDesc = MessageHandler_BuildSlotAccessNode(theClass, tokenType, 0, tokenValue, 0);
  if ( !slotDesc )
    return -1;
  AST_NewSlotReferenceNode(58, v9, slotDesc);
  return 1;
}
// 4DF88B: variable 'v6' is possibly undefined
// 4DF892: variable 'v7' is possibly undefined
// 4DF8A7: variable 'v10' is possibly undefined
// 4DF8B3: variable 'v11' is possibly undefined
// 4DF8D2: variable 'v9' is possibly undefined
// 48A1ED: using guessed type int __fastcall strncmp_(_DWORD, _DWORD);

//----- (004DF8F0) --------------------------------------------------------
signed int  MessageHandler_ResolveSelfSlotBindRef(int bindExpr, int theClass)
{
  int v4 CLASH95_UNUSED; // ecx; no longer consumed after the proven string-argument repair
  int v5; // ecx
  signed int result; // eax
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int *valueExprChain; // ebp
  int slotDesc; // eax
  int v12; // ecx
  int tokenType; // [esp+0h] [ebp-20h]
  int tokenValue; // [esp+4h] [ebp-1Ch]

  if ( !strcmp_(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(bindExpr + 6) + 2) + 16), ((_DWORD)(uintptr_t)(aSelf_0))) )
  {
    Rules_PrintErrorID((int)(intptr_t)aMsgpsr, 5, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aActiveInstance, v7);
    return -1;
  }
  else if ( !strncmp_(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(bindExpr + 6) + 2) + 16), (_DWORD)(uintptr_t)aSelf_0, 4)
         && *(_BYTE *)(uintptr_t)(v5 + 4) == 58
         && (IO_OpenStringSource((int)(intptr_t)aHndVar, (const char *)(uintptr_t)(v5 + 5), 0),
             Rules_GetPPBufferStatus(),
             Rules_SetPPBufferStatus(0),
             Parser_NextToken((int)(intptr_t)aHndVar, v8),
             Rules_SetPPBufferStatus(v9),
             IO_CloseStringRouter((int)(intptr_t)aHndVar),
             tokenType != 102) )
  {
    valueExprChain = (int *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(bindExpr + 6) + 10);
    slotDesc = MessageHandler_BuildSlotAccessNode(theClass, tokenType, 1, tokenValue, valueExprChain);
    if ( slotDesc )
    {
      AST_NewSlotReferenceNode(59, v12, slotDesc);
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(bindExpr + 6) + 10) = 0;
      AST_Free(*(_DWORD *)(uintptr_t)(bindExpr + 6));
      result = 1;
      *(_DWORD *)(uintptr_t)(bindExpr + 6) = ((_DWORD)(uintptr_t)(valueExprChain));
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
int  MessageHandler_BuildSlotAccessNode(int theClass, int tokenType, int writeFlag, int slotSymbol, int *writeExpression)
{
  unsigned int slotIndex; // eax
  int v7; // ecx
  int slotDesc; // esi
  signed int violationCode; // edi
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int classNameStr; // eax
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx

  if ( tokenType == 2 )
  {
    slotIndex = Instance_ResolveSlotIndex(writeFlag, slotSymbol);
    if ( slotIndex == -1 )
    {
      Rules_PrintErrorID((int)(intptr_t)aMsgpsr, 6, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aNoSuchSlot_0, v12);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(uintptr_t)(slotSymbol + 16), v13);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aInClass_1, v14);
      classNameStr = Rules_GetConstructNameString(theClass);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], classNameStr, v16);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aFor_selfRefere, v17);
      return 0;
    }
    else
    {
      slotDesc = *(_DWORD *)(uintptr_t)(4 * slotIndex + *(_DWORD *)(uintptr_t)(theClass + 56));
      if ( (*(_BYTE *)(uintptr_t)(slotDesc + 1) & 4) != 0 || theClass == *(_DWORD *)(uintptr_t)(slotDesc + 4) )
      {
        if ( !v7 )
          return slotDesc;
        if ( (*(_BYTE *)(uintptr_t)slotDesc & 0x10) != 0 && (*(_BYTE *)(uintptr_t)slotDesc & 0x20) == 0 )
        {
          MessageHandler_ReportSlotWriteAccessDenied(*(_DWORD *)(uintptr_t)(slotSymbol + 16), 0);
          return 0;
        }
        else
        {
          if ( !Rules_StaticConstraintCheckingEnabled() )
            return slotDesc;
          violationCode = Rules_CheckFieldExprListAgainstConstraint(writeExpression, *(_DWORD *)(uintptr_t)(slotDesc + 20));
          if ( !violationCode )
            return slotDesc;
          Rules_PrintErrorID((int)(intptr_t)aCstrnchk_2, 1, 0);
          Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aExpressionFor, (int)(intptr_t)aDirectSlotWrit);
          Instance_PrintSlotErrorContext((int)(intptr_t)g_IO_LogicalNameTable_WError[0], slotDesc, v18, 0);
          Rules_PrintConstraintViolationMessage(0, 0, 0, 0, 0, 0, violationCode, *(_DWORD *)(uintptr_t)(slotDesc + 20), 0);
          return 0;
        }
      }
      else
      {
        MessageHandler_ReportPrivateSlotAccessDenied(slotDesc);
        return 0;
      }
    }
  }
  else
  {
    Rules_PrintErrorID((int)(intptr_t)aMsgpsr, 7, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aIllegalValueFo, v11);
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
int  AST_NewSlotReferenceNode(__int16 refType, int theExpr, int slotDesc)
{
  _WORD *v4; // ecx
  int result; // eax
  int v6; // ecx
  __int16 handlerSlotRef; // [esp+0h] [ebp-10h] BYREF
  int slotID CLASH95_UNUSED; // [esp+2h] [ebp-Eh]
  int savedExpr CLASH95_UNUSED; // [esp+Ch] [ebp-4h]

  savedExpr = theExpr;
  Mem_AllocArray(((_BYTE*)(&handlerSlotRef)), 6);
  handlerSlotRef = *(_WORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(slotDesc + 4) + 24);
  slotID = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(slotDesc + 8) + 8);
  *v4 = refType;
  result = Rules_AddBitmapValue(((_BYTE*)(&handlerSlotRef)), 6);
  *(_DWORD *)(uintptr_t)(v6 + 2) = result;
  return result;
}
// 4DFBC1: variable 'v4' is possibly undefined
// 4DFBC9: variable 'v6' is possibly undefined

//----- (004DFBE0) --------------------------------------------------------
signed int Rules_SetupDefinstancesBsaveBload(void)
{
  return Rules_RegisterBinaryItem(
           (int)(intptr_t)aDefinstances_0,
           0,
           (int)(intptr_t)Rules_FindDefinstancesBsaveExpressions,
           (int)(intptr_t)Rules_CountDefinstancesBsaveExpressions,
           (int)(intptr_t)Rules_BsaveWriteDefinstancesCounts,
           (int)(intptr_t)Rules_BsaveWriteDefinstancesData,
           (int)(intptr_t)Rules_BloadAllocateDefinstancesArrays,
           (int)(intptr_t)Rules_BloadRefreshDefinstances,
           (int)(intptr_t)Rules_ClearDefinstancesBloadData);
}

//----- (004DFC20) --------------------------------------------------------
int  Rules_DefinstancesBloadModuleReference(int moduleIndex)
{
  return 12 * moduleIndex + g_DefinstancesBloadModuleRefArray;
}
// 54E914: using guessed type int dword_54E914;

//----- (004DFC40) --------------------------------------------------------
signed int Rules_CountDefinstancesBsaveExpressions(void)
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
__int16  Rules_MarkDefinstancesExpressionUsage(_DWORD *theDefinstances)
{
  int bsaveIndex; // edx
  int v2; // ecx
  int v3; // ecx

  bsaveIndex = g_Definstances_Count++;
  AST_MarkNodeFieldBound(theDefinstances, bsaveIndex);
  g_ClipsExpressionNodeIndex += AST_CountTreeNodes(*(_DWORD *)(uintptr_t)(v2 + 24));
  return Rules_MarkReferencedFunctions((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(v3 + 24));
}
// 4DFCA8: variable 'v2' is possibly undefined
// 4DFCB6: variable 'v3' is possibly undefined
// 51C710: using guessed type int dword_51C710;
// 54E680: using guessed type int dword_54E680;

//----- (004DFCC0) --------------------------------------------------------
signed int Rules_FindDefinstancesBsaveExpressions(void)
{
  return Rules_DoForAllConstructs((void (*)(void))Rules_BsaveWriteDefinstancesExpression, 0);
}
// 54E8F0: using guessed type int dword_54E8F0;

//----- (004DFCE0) --------------------------------------------------------
__int16 * Rules_BsaveWriteDefinstancesExpression(int theDefinstances, int filePtr)
{
  return Rules_BsaveWriteExpression((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(theDefinstances + 24), filePtr);
}

//----- (004DFCF0) --------------------------------------------------------
const void * Rules_BsaveWriteDefinstancesCounts(int filePtr, int a2)
{
  int v2; // ecx
  int v3; // ecx
  _DWORD spaceBuffer[4]; // [esp+0h] [ebp-10h] BYREF

  spaceBuffer[2] = a2;
  spaceBuffer[0] = 8;
  Rules_BsaveWriteBlock(4, filePtr, spaceBuffer);
  Rules_BsaveWriteBlock(4, v2, &g_Clips_DefinstancesCount);
  return Rules_BsaveWriteBlock(4, v3, &g_Definstances_Count);
}
// 4DFD1A: variable 'v2' is possibly undefined
// 4DFD2B: variable 'v3' is possibly undefined
// 51C710: using guessed type int dword_51C710;
// 51C714: using guessed type int dword_51C714;

//----- (004DFD40) --------------------------------------------------------
int  Rules_BsaveWriteDefinstancesData(int filePtr, int a2)
{
  int moduleItemRecord; // eax
  int v4; // ecx
  _DWORD *theModuleItem; // eax
  int v6; // ecx
  int result; // eax
  _DWORD itemHeaderBuffer[3]; // [esp-Ch] [ebp-20h] BYREF
  _DWORD spaceBuffer[5]; // [esp+0h] [ebp-14h] BYREF

  spaceBuffer[3] = a2;
  spaceBuffer[0] = 16 * g_Definstances_Count + 12 * g_Clips_DefinstancesCount;
  Rules_BsaveWriteBlock(4, filePtr, spaceBuffer);
  g_Definstances_Count = 0;
  if ( Module_NextEnum(0) )
  {
    do
    {
      moduleItemRecord = Module_FindItemByName((int)(intptr_t)aDefinstances_0);
      theModuleItem = (_DWORD *)(uintptr_t)Module_GetItem(v4, *(_DWORD *)(uintptr_t)(moduleItemRecord + 4));
      Module_AssignBsaveItemHeaderIndices(itemHeaderBuffer, theModuleItem);
      Rules_BsaveWriteBlock(12, filePtr, itemHeaderBuffer);
    }
    while ( Module_NextEnum(v6) );
  }
  Rules_DoForAllConstructs((void (*)(void))Rules_BsaveWriteDefinstancesRecord, 0);
  result = Rules_IsBloaded();
  if ( result )
  {
    Rules_ConstructQueuePop(((_DWORD*)(&g_Clips_DefinstancesCount)));
    return Rules_ConstructQueuePop(((_DWORD*)(&g_Definstances_Count)));
  }
  return result;
}
// 4DFDA2: variable 'v4' is possibly undefined
// 4DFDC0: variable 'v6' is possibly undefined
// 51C710: using guessed type int dword_51C710;
// 51C714: using guessed type int dword_51C714;
// 54E8F0: using guessed type int dword_54E8F0;

//----- (004DFE20) --------------------------------------------------------
const void * Rules_BsaveWriteDefinstancesRecord(int theDefinstances, int filePtr, int a3)
{
  int v4; // ecx
  _DWORD bsaveRecord[3]; // [esp-Ch] [ebp-18h] BYREF
  int expressionIndex CLASH95_UNUSED; // [esp+0h] [ebp-Ch]
  int v8 CLASH95_UNUSED; // [esp+4h] [ebp-8h]

  v8 = a3;
  AST_ExtractPatternBindingInfo(bsaveRecord, theDefinstances);
  if ( *(_DWORD *)(uintptr_t)(v4 + 24) )
  {
    expressionIndex = g_ClipsExpressionNodeIndex;
    g_ClipsExpressionNodeIndex += AST_CountTreeNodes(*(_DWORD *)(uintptr_t)(v4 + 24));
  }
  else
  {
    expressionIndex = -1;
  }
  return Rules_BsaveWriteBlock(16, filePtr, bsaveRecord);
}
// 4DFE32: variable 'v4' is possibly undefined
// 54E680: using guessed type int dword_54E680;

//----- (004DFE80) --------------------------------------------------------
int __thiscall Rules_BloadAllocateDefinstancesArrays(void *this_)
{
  int result; // eax
  _DWORD spaceBuffer[4]; // [esp+0h] [ebp-10h] BYREF

  spaceBuffer[2] = ((_DWORD)(uintptr_t)(this_));
  result = Rules_BloadReadBlock((uintptr_t)spaceBuffer, 4u);
  if ( spaceBuffer[0] )
  {
    Rules_BloadReadBlock((uintptr_t)&g_Clips_DefinstancesCount, 4u);
    result = Rules_BloadReadBlock((uintptr_t)&g_Definstances_Count, 4u);
    if ( g_Clips_DefinstancesCount )
    {
      spaceBuffer[0] = 12 * g_Clips_DefinstancesCount;
      result = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(12 * g_Clips_DefinstancesCount));
      g_DefinstancesBloadModuleRefArray = result;
      if ( g_Definstances_Count )
      {
        spaceBuffer[0] = 28 * g_Definstances_Count;
        result = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(28 * g_Definstances_Count));
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
signed int Rules_BloadRefreshDefinstances(void)
{
  int space; // [esp-8h] [ebp-Ch] BYREF

  Rules_BloadReadBlock((uintptr_t)&space, 4u);
  Rules_BloadAndRefresh(g_Clips_DefinstancesCount, 12, (void (__fastcall *)(signed int, signed int))Rules_BloadRefreshDefinstancesRecord);
  return Rules_BloadAndRefresh(g_Definstances_Count, 16, (void (__fastcall *)(signed int, signed int))Rules_BloadRefreshDefinstancesExpression);
}
// 51C710: using guessed type int dword_51C710;
// 51C714: using guessed type int dword_51C714;

//----- (004DFF80) --------------------------------------------------------
_DWORD * Rules_BloadRefreshDefinstancesRecord(_DWORD *bsaveData, int itemIndex)
{
  return Module_UpdateItemHeader(bsaveData, (_DWORD *)(uintptr_t)(12 * itemIndex + g_DefinstancesBloadModuleRefArray), g_ClipsDefinstancesBloadArray, 28);
}
// 51C70C: using guessed type int dword_51C70C;
// 54E914: using guessed type int dword_54E914;

//----- (004DFFC0) --------------------------------------------------------
int  Rules_BloadRefreshDefinstancesExpression(int bsaveBuffer, int itemIndex)
{
  _DWORD *theDefinstances; // edi
  int result; // eax

  theDefinstances = (_DWORD *)(uintptr_t)(g_ClipsDefinstancesBloadArray + 28 * itemIndex);
  Rules_BuildIndexedSlotDescriptor(bsaveBuffer, theDefinstances, g_DefinstancesBloadModuleRefArray, 12, 28, g_ClipsDefinstancesBloadArray);
  if ( *(_DWORD *)(uintptr_t)(bsaveBuffer + 12) == -1 )
  {
    result = 0;
    theDefinstances[5] = 0;
    theDefinstances[6] = 0;
  }
  else
  {
    result = g_ClipsPackedExpressionArray + 14 * *(_DWORD *)(uintptr_t)(bsaveBuffer + 12);
    theDefinstances[5] = 0;
    theDefinstances[6] = result;
  }
  return result;
}
// 51C70C: using guessed type int dword_51C70C;
// 54E688: using guessed type int dword_54E688;
// 54E914: using guessed type int dword_54E914;

//----- (004E0040) --------------------------------------------------------
signed int Rules_ClearDefinstancesBloadData(void)
{
  signed int result; // eax
  int recordOffset; // ecx
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
      recordOffset = 0;
      do
      {
        Rules_ReleaseSymbolReference((int *)(uintptr_t)(recordOffset + g_ClipsDefinstancesBloadArray), recordOffset);
        recordOffset = v2 + 28;
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
int Rules_RegisterDefinstancesCodeGenerator(void)
{
  int result; // eax

  result = Rules_AddCodeGeneratorItem((int)(intptr_t)aDefinstances_1, 0, 0, (int)(intptr_t)Compiler_RegisterDefinstancesModuleAssigner, (int)(intptr_t)Compiler_WriteDefinstancesToCode, 2);
  g_DefinstancesCodeGenItem = result;
  return result;
}
// 54E918: using guessed type int dword_54E918;

//----- (004E0120) --------------------------------------------------------
int  Rules_WriteDefinstancesModuleReference(int theFile, int count)
{
  return Output_WriteFormatted(count, *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_DefinstancesCodeGenItem + 20), theFile, (int)(intptr_t)aMihsSD_DD_7, *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_DefinstancesCodeGenItem + 20));
}
// 54E918: using guessed type int dword_54E918;

//----- (004E0160) --------------------------------------------------------
signed int Compiler_RegisterDefinstancesModuleAssigner(void)
{
  return Rules_RegisterModuleItemIdAssigner();
}
// 54E8F0: using guessed type int dword_54E8F0;

//----- (004E0170) --------------------------------------------------------
int  Compiler_WriteDefinstancesToCode(const char *fileName, const char *pathName, int fileID, int imageID, int maxIndices)
{
  int definstancesFile; // esi
  int v6; // ecx
  int v7; // eax
  int v8; // ecx
  int openedModuleFile; // edi
  int theDefinstances; // edi
  int v11; // eax
  int v12; // ecx
  int openedDefinstancesFile; // esi
  int prevModuleCount; // ebx
  int fileNameBuffer; // [esp+0h] [ebp-3Ch] BYREF
  int moduleArrayCount; // [esp+4h] [ebp-38h] BYREF
  int moduleArrayVersion; // [esp+8h] [ebp-34h] BYREF
  int definstancesArrayCount; // [esp+Ch] [ebp-30h] BYREF
  int definstancesArrayVersion; // [esp+10h] [ebp-2Ch] BYREF
  int moduleFile; // [esp+14h] [ebp-28h]
  int Enum; // [esp+18h] [ebp-24h]
  const char *savedFileName; // [esp+1Ch] [ebp-20h]
  const char *savedPathName; // [esp+20h] [ebp-1Ch]
  int savedImageID; // [esp+24h] [ebp-18h]
  int moduleCount; // [esp+28h] [ebp-14h]
  int savedFileID; // [esp+2Ch] [ebp-10h]

  savedFileName = fileName;
  savedPathName = pathName;
  savedImageID = imageID;
  savedFileID = fileID;
  moduleCount = 0;
  moduleArrayCount = 0;
  moduleArrayVersion = 1;
  definstancesArrayCount = 0;
  definstancesArrayVersion = 1;
  moduleFile = 0;
  Output_WriteFormatted(0, 1, imageID, (int)(intptr_t)aIncludeDefins_, 1);
  definstancesFile = 0;
  Enum = Module_NextEnum(0);
  if ( Enum )
  {
    while ( 1 )
    {
      Module_SetCurrent(Enum);
      v7 = Rules_ConstructCodeFileOpen(
             moduleFile,
             savedFileName,
             savedFileID,
             savedPathName,
             &fileNameBuffer,
             moduleArrayVersion,
             savedImageID,
             (char)(intptr_t)aDefinstances_m,
             **(const char ***)(uintptr_t)(g_DefinstancesCodeGenItem + 20),
             0,
             0);
      openedModuleFile = v7;
      if ( !v7 )
      {
        Compiler_CloseDefinstancesCodeFiles(0, definstancesFile, v8, maxIndices);
        return 0;
      }
      Compiler_WriteDefinstancesModuleHeaderToCode(v7, Enum, maxIndices);
      moduleFile = Rules_ConstructCodeFileClose(openedModuleFile, &moduleArrayCount, maxIndices, ((_DWORD*)(&moduleArrayVersion)), 0, 0);
      theDefinstances = Definstances_GetNextRecord(0);
      if ( theDefinstances )
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
      v11 = Rules_ConstructCodeFileOpen(
              definstancesFile,
              savedFileName,
              savedFileID,
              savedPathName,
              &fileNameBuffer,
              definstancesArrayVersion,
              savedImageID,
              (char)(intptr_t)aDefinstances_3,
              (const char *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_DefinstancesCodeGenItem + 20) + 4),
              0,
              0);
      openedDefinstancesFile = v11;
      if ( !v11 )
        break;
      Compiler_WriteDefinstancesConstructToCode(v11, theDefinstances, maxIndices, moduleCount);
      ++definstancesArrayCount;
      definstancesFile = Rules_ConstructCodeFileClose(openedDefinstancesFile, &definstancesArrayCount, maxIndices, ((_DWORD*)(&definstancesArrayVersion)), 0, 0);
      theDefinstances = Definstances_GetNextRecord(theDefinstances);
      if ( !theDefinstances )
        goto LABEL_6;
    }
    Compiler_CloseDefinstancesCodeFiles(moduleFile, 0, v12, maxIndices);
    return 0;
  }
  else
  {
LABEL_7:
    Compiler_CloseDefinstancesCodeFiles(moduleFile, definstancesFile, v6, maxIndices);
    return 1;
  }
}
// 4E0309: variable 'v6' is possibly undefined
// 4E0320: variable 'v8' is possibly undefined
// 4E0338: variable 'v12' is possibly undefined
// 54E918: using guessed type int dword_54E918;

//----- (004E0350) --------------------------------------------------------
int  Compiler_CloseDefinstancesCodeFiles(int moduleFile, int definstancesFile, int a3, int maxIndices)
{
  int result; // eax
  int count; // [esp+0h] [ebp-14h] BYREF
  _DWORD arrayVersion[4]; // [esp+4h] [ebp-10h] BYREF

  arrayVersion[3] = a3;
  result = definstancesFile;
  count = maxIndices;
  arrayVersion[0] = 0;
  if ( definstancesFile )
  {
    result = Rules_ConstructCodeFileClose(definstancesFile, &count, maxIndices, arrayVersion, 0, 0);
    if ( !moduleFile )
      return result;
    goto LABEL_5;
  }
  if ( moduleFile )
  {
LABEL_5:
    count = maxIndices;
    return Rules_ConstructCodeFileClose(moduleFile, &count, maxIndices, arrayVersion, 0, 0);
  }
  return result;
}

//----- (004E03B0) --------------------------------------------------------
int  Compiler_WriteDefinstancesModuleHeaderToCode(int theFile, int theModule, int maxIndices)
{
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  char v9; // [esp+0h] [ebp-Ch]
  char v10; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(maxIndices, theModule, theFile, (int)(intptr_t)asc_50E3D0, v9);
  Rules_WriteConstructModuleItemHeaderToCode(theFile, v4, v5, g_Clips_DefinstancesModuleItemIndex, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_DefinstancesCodeGenItem + 20) + 4));
  return Output_WriteFormatted(v7, v6, theFile, (int)(intptr_t)asc_50E3D4, v10);
}
// 4E03BB: variable 'v9' is possibly undefined
// 4E03D8: variable 'v4' is possibly undefined
// 4E03D8: variable 'v5' is possibly undefined
// 4E03E3: variable 'v7' is possibly undefined
// 4E03E3: variable 'v6' is possibly undefined
// 4E03E3: variable 'v10' is possibly undefined
// 54E8F0: using guessed type int dword_54E8F0;
// 54E918: using guessed type int dword_54E918;
