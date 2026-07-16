/* Generated from src/recovered/rules/clips/004C82D0_methods.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

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
  result = Rules_GetConstructNameAndComment(readSource, (int)(intptr_t)&g_ClipsMethodParserToken, 0, aDefmethod_1, 0, asc_50B47C, 1, 0, 1);
  status = result;
  if ( result )
  {
    if ( g_ClipsMethodParserToken == 1 )
    {
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(asc_50B480);
      IO_OutWriteToken((char *)(uintptr_t)g_CLIPS_GenericParseTokenPrintStr);
      methodIndex = *(_DWORD *)(uintptr_t)(g_Clips_CurrentTokenValue + 16);
      if ( methodIndex < v11 )
      {
        Rules_PrintErrorID((int)(intptr_t)aGenrcpsr, 6, 0);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aMethodIndexOut, v13);
        return 0;
      }
      *indexOut = methodIndex;
      AST_Append(v9, (int)(intptr_t)&g_ClipsMethodParserToken);
      Parser_NextToken(readSource, v12);
    }
    if ( g_ClipsMethodParserToken == 3 )
    {
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(asc_50B480);
      IO_OutWriteToken((char *)(uintptr_t)g_CLIPS_GenericParseTokenPrintStr);
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
    Rules_PrintErrorID((int)(intptr_t)aGenrcpsr, 7, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aExpectedAToBeg, v13);
    return -1;
  }
  Parser_NextToken(readSource, (int)(intptr_t)&g_ClipsMethodParserToken);
  while ( g_ClipsMethodParserToken != 101 )
  {
    if ( *wildcardPtr )
    {
      Method_FreeRestrictionChain(paramList);
      Rules_PrintErrorID((int)(intptr_t)aPrccode_1, v14, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aNoParametersAl, v15);
      return -1;
    }
    if ( g_ClipsMethodParserToken == 15 || g_ClipsMethodParserToken == 16 )
    {
      varName = g_Clips_CurrentTokenValue;
      if ( Method_CheckDuplicateParameterName(paramList, &lastParam, g_Clips_CurrentTokenValue) )
        goto LABEL_18;
      if ( g_ClipsMethodParserToken == 16 )
        *wildcardPtr = varName;
      v6 = *(_DWORD **)(uintptr_t)(g_ClipsMemoryTable + 48);
      if ( v6 )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
        *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = *v6;
        v7 = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
      }
      else
      {
        v7 = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0xC);
      }
      Method_PackRestrictionTypes(v7, 0);
      *(_DWORD *)(uintptr_t)(v8 + 4) = 0;
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
        Rules_PrintErrorID((int)(intptr_t)aGenrcpsr, v19, 0);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aExpectedAVar_0, v20);
        return -1;
      }
      Parser_NextToken(readSource, (int)(intptr_t)&g_ClipsMethodParserToken);
      if ( g_ClipsMethodParserToken != 15 && g_ClipsMethodParserToken != 16 )
      {
        Method_FreeRestrictionChain(paramList);
        Rules_PrintErrorID((int)(intptr_t)aGenrcpsr, v17, 0);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aExpectedAVaria, v18);
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
    Parser_NextToken(readSource, (int)(intptr_t)&g_ClipsMethodParserToken);
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

  Parser_NextToken(readSource, (int)(intptr_t)&g_ClipsMethodParserToken);
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
      freeNode = *(_DWORD **)(uintptr_t)(g_ClipsMemoryTable + 48);
      if ( freeNode )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
        *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = *freeNode;
        restriction = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
      }
      else
      {
        restriction = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0xC);
      }
      restriction[1] = query;
      Method_PackRestrictionTypes(restriction, typeList);
      return v7;
    }
    else
    {
      Rules_PrintErrorID((int)(intptr_t)aGenrcpsr, 13, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aExpectedAValid, v22);
      return 0;
    }
  }
  while ( 1 )
  {
    if ( query )
    {
      Rules_PrintErrorID((int)(intptr_t)aGenrcpsr, 10, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aQueryMustBeLas, v9);
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
        Rules_PrintErrorID((int)(intptr_t)aGenrcpsr, 12, 0);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aBindsAreNotAll, v19);
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
        Rules_PrintErrorID((int)(intptr_t)aGenrcpsr, 13, 0);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aExpectedAValid, v21);
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
    typeNode = *(_DWORD *)(uintptr_t)(typeNode + 10);
    if ( !typeNode )
    {
      *(_DWORD *)(uintptr_t)(prevType + 10) = classNode;
      goto LABEL_7;
    }
  }
  while ( 1 )
  {
    existingClass = *(_DWORD *)(uintptr_t)(typeNode + 2);
    candidateClass = *(_DWORD *)(uintptr_t)(classIter + 2);
    if ( existingClass == candidateClass )
      break;
    if ( Method_CheckRedundantClassPair(existingClass, candidateClass) )
      goto LABEL_26;
    classIter = *(_DWORD *)(uintptr_t)(v16 + 10);
    if ( !classIter )
      goto LABEL_23;
  }
  Rules_PrintErrorID((int)(intptr_t)aGenrcpsr, 11, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDuplicateClass, v18);
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
    paramName = *(_DWORD *)(uintptr_t)(paramList + 2);
    if ( name == paramName )
      break;
    *lastNode = paramList;
    paramList = *(_DWORD *)(uintptr_t)(paramList + 10);
    if ( !paramList )
      return 0;
  }
  Rules_PrintErrorID((int)(intptr_t)aPrccode_1, 7, paramName ^ name);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDuplicateParam, v5);
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
    *(_DWORD *)(uintptr_t)(lastNode + 10) = result;
    result = paramList;
    *(_DWORD *)(uintptr_t)(newNode + 6) = v6;
  }
  else
  {
    *(_DWORD *)(uintptr_t)(result + 6) = v6;
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

  if ( Rules_FindModuleSeparator(*(_BYTE **)(uintptr_t)(name + 16)) )
  {
    Module_ReportIllegalSpecifierError();
    return 0;
  }
  else
  {
    theClass = Class_LookupInScope(*(_BYTE **)(uintptr_t)(v1 + 16));
    if ( theClass )
    {
      return AST_NewNode(5, (int)(intptr_t)theClass);
    }
    else
    {
      Rules_PrintErrorID((int)(intptr_t)aGenrcpsr, 14, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aUnknownClassIn, v3);
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
    Rules_PrintErrorID((int)(intptr_t)aGenrcpsr, 15, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v5, v5);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aClassIsRedunda, v6);
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

  existingGeneric = Defgeneric_ParseConstruct(*(_BYTE **)(uintptr_t)(nameToken + 16), nameToken);
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
    ++*(_DWORD *)(uintptr_t)(v9 + 4);
    Defgeneric_InitializeFromRestrictionString((int)(intptr_t)newGeneric, v9);
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
      qmemcpy(&newMethods[10 * destIndex], (const void *)(uintptr_t)(srcOffset + gfunc[7]), 0x28u);
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
    Mem_SmallBlockFree((_DWORD *)(uintptr_t)gfunc[7], 40 * gfunc[8]);
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
      paramRestriction = *(_DWORD *)(uintptr_t)(params + 6);
      result = Method_CompareTypeArrays((_DWORD *)(uintptr_t)paramRestriction, (_DWORD *)(uintptr_t)restrictionPtr);
      if ( result )
        return result;
      if ( !*(_DWORD *)(uintptr_t)(paramRestriction + 4) && *(_DWORD *)(uintptr_t)(restrictionPtr + 4) )
        return 1;
      if ( *(_DWORD *)(uintptr_t)(paramRestriction + 4) && !*(_DWORD *)(uintptr_t)(restrictionPtr + 4) )
        return -1;
      if ( !AST_NodeListsEqual(*(__int16 **)(uintptr_t)(paramRestriction + 4), *(__int16 **)(uintptr_t)(restrictionPtr + 4)) )
        differs = 1;
      index = v10 + 1;
      params = *(_DWORD *)(uintptr_t)(params + 10);
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
      type1 = (int *)(uintptr_t)(offset + *types1);
      type2 = (int *)(uintptr_t)(offset + *types2);
      if ( *type1 != *type2 )
      {
        differs = 1;
        if ( Class_HasSuperclass(*type1, *type2) )
          return -1;
        if ( Class_HasSuperclass(*(_DWORD *)(uintptr_t)(v11 + *types2), *(_DWORD *)(uintptr_t)(v11 + *types1)) )
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

  v2 = *(_DWORD **)(uintptr_t)(g_ClipsMemoryTable + 160);
  if ( v2 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 160);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 160) = *v2;
  }
  else
  {
    Mem_HeapAllocWithRetry((_DWORD *)0x28);
  }
  Rules_InitConstructModuleRecord((int)(intptr_t)aDefgeneric_1, name);
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
    ++*(_DWORD *)(uintptr_t)(gfunc + 20);
    genericName = Rules_GetConstructNameString(gfunc);
    argCount = AST_CountListNodes((int)(intptr_t)argExpressions);
    ProcParam_PushEvaluatedArgumentFrame(argExpressions, argCount, v11, genericName, a5, (int (*)(void))Method_PrintCallErrorBanner);
    if ( g_ClipsEvaluationError )
    {
      v13 = oldGeneric;
      --*(_DWORD *)(uintptr_t)(gfunc + 20);
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
        if ( Method_RestrictionsSatisfiedByArgs((int)(intptr_t)theMethod, a5) )
        {
          ++theMethod[1];
          g_ClipsCurrentMethod = (int)(intptr_t)theMethod;
        }
        else
        {
          Rules_PrintErrorID((int)(intptr_t)aGenrcexe, 4, 0);
          Lexer_ErrorRecover(1);
          g_ClipsCurrentMethod = v14;
          Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v15, v14);
          genericNameStr = Rules_GetConstructNameString(gfunc);
          Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], genericNameStr, v17);
          Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aMethod_2, v18);
          Rules_PrintLongInteger(v19, *theMethod);
          Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aIsNotApplicabl, v20);
        }
      }
      else
      {
        g_ClipsCurrentMethod = Method_FindApplicableMethod(gfunc, prevMethodArg, a5);
      }
      if ( g_ClipsCurrentMethod )
      {
        if ( *(_DWORD *)(uintptr_t)(g_ClipsCurrentGeneric + 24) )
          Method_PrintGenericCallTrace((int)(intptr_t)asc_50B73C);
        if ( (*(_BYTE *)(uintptr_t)(g_ClipsCurrentMethod + 24) & 2) != 0 )
          Method_PrintMethodCallTrace((int)(intptr_t)asc_50B73C);
        if ( (*(_BYTE *)(uintptr_t)(g_ClipsCurrentMethod + 24) & 1) != 0 )
        {
          callExpr = 10;
          v26 = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentMethod + 32) + 2);
          v28 = 0;
          argExprChain = ProcParam_BuildArgumentExpressionChain();
          Parser_ParseForm(&callExpr, returnValue, 0, a5);
        }
        else
        {
          Rules_ExecuteRuleActions(
            **(_DWORD **)(uintptr_t)(g_ClipsCurrentGeneric + 8),
            *(__int16 **)(uintptr_t)(g_ClipsCurrentMethod + 32),
            returnValue,
            *(_DWORD *)(uintptr_t)(g_ClipsCurrentMethod + 20),
            a5,
            (void (*)(void))Method_PrintCallErrorBanner);
        }
        --*(_DWORD *)(uintptr_t)(g_ClipsCurrentMethod + 4);
        if ( (*(_BYTE *)(uintptr_t)(g_ClipsCurrentMethod + 24) & 2) != 0 )
          Method_PrintMethodCallTrace((int)(intptr_t)asc_50B740);
        if ( *(_DWORD *)(uintptr_t)(g_ClipsCurrentGeneric + 24) )
          Method_PrintGenericCallTrace((int)(intptr_t)asc_50B740);
      }
      else if ( !g_ClipsEvaluationError )
      {
        Rules_PrintErrorID((int)(intptr_t)aGenrcexe, 1, 0);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aNoApplicable_0, v21);
        genericNameStrForError = Rules_GetConstructNameString(gfunc);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], genericNameStrForError, v23);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__24, v24);
        Lexer_ErrorRecover(1);
      }
      --*(_DWORD *)(uintptr_t)(gfunc + 20);
      g_ClipsHaltExecutionFlag = 0;
      ProcParam_PopFrame();
      g_ClipsCurrentGeneric = oldGeneric;
      g_ClipsCurrentMethod = oldMethod;
      --g_ClipsCurrentEvaluationDepth;
      Rules_PropagateReturnValueDepth((int)(intptr_t)returnValue);
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

  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aGenericFunct_5, (int)(intptr_t)this);
  v1 = Rules_GetConstructNameString(g_ClipsCurrentGeneric);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v1, (int)(intptr_t)g_IO_LogicalNameTable_WError[0]);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aMethod_2, v2);
  Rules_PrintLongInteger(v3, *(_DWORD *)(uintptr_t)g_ClipsCurrentMethod);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__24, v4);
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
  v2 = *(_DWORD *)(uintptr_t)(method + 12);
  if ( g_ClipsProcParamCount < v2 || g_ClipsProcParamCount > v2 && *(_DWORD *)(uintptr_t)(method + 16) != -1 )
    return 0;
  argIndex = 0;
  restrictionIndex = 0;
  if ( g_ClipsProcParamCount > 0 )
  {
    restrictionOffset = 0;
    for ( i = 0; ; i += 24 )
    {
      restriction = restrictionOffset + *(_DWORD *)(uintptr_t)(methodBase + 28);
      if ( !*(_DWORD *)(uintptr_t)(restriction + 8) )
        goto LABEL_7;
      result = Method_GetArgumentClass(i + g_ClipsProcParamArray);
      argClass = result;
      if ( !result )
        return result;
      classIndex = 0;
      if ( *(_DWORD *)(uintptr_t)(restriction + 8) )
        break;
LABEL_19:
      if ( classIndex == *(_DWORD *)(uintptr_t)(restriction + 8) )
        return 0;
LABEL_7:
      if ( *(_DWORD *)(uintptr_t)(restriction + 4) )
      {
        g_Method_CurrentArgParamPtr = i + g_ClipsProcParamArray;
        Parser_ParseForm(*(__int16 **)(uintptr_t)(restriction + 4), &v11, v2, a2);
        if ( v12 == __PAIR64__(g_ClipsFalseSymbol, 2) )
          return 0;
      }
      if ( *(_DWORD *)(uintptr_t)(methodBase + 8) - 1 != restrictionIndex )
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
      v7 = (int *)(uintptr_t)(v2 + *(_DWORD *)(uintptr_t)restriction);
      if ( argClass == *v7 || Class_HasSuperclass(argClass, *v7) )
        goto LABEL_19;
      v8 = (_DWORD *)(uintptr_t)(v2 + *(_DWORD *)(uintptr_t)restriction);
      if ( *v8 == g_Class_InstanceAddress )
        break;
      if ( *v8 == g_Class_InstanceName )
      {
        v9 = *(_DWORD *)(uintptr_t)(i + g_ClipsProcParamArray + 4) == 8;
LABEL_24:
        if ( v9 )
          goto LABEL_19;
        goto LABEL_25;
      }
      if ( *v8 == **(_DWORD **)(uintptr_t)(g_Class_InstanceName + 36) )
      {
        v10 = *(_DWORD *)(uintptr_t)(i + g_ClipsProcParamArray + 4);
        if ( v10 == 8 )
          goto LABEL_19;
        v9 = v10 == 7;
        goto LABEL_24;
      }
LABEL_25:
      ++classIndex;
      v2 += 4;
      if ( classIndex >= *(_DWORD *)(uintptr_t)(restriction + 8) )
        goto LABEL_19;
    }
    v9 = *(_DWORD *)(uintptr_t)(i + g_ClipsProcParamArray + 4) == 7;
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
    --*(_DWORD *)(uintptr_t)(nextMethod + 4);
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
      if ( (*(_BYTE *)(uintptr_t)(g_ClipsCurrentMethod + 24) & 2) != 0 )
        Method_PrintMethodCallTrace((int)(intptr_t)asc_50B73C);
      if ( (*(_BYTE *)(uintptr_t)(g_ClipsCurrentMethod + 24) & 1) != 0 )
      {
        callExpr = 10;
        v8 = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentMethod + 32) + 2);
        v10 = 0;
        v9 = ProcParam_BuildArgumentExpressionChain();
        Parser_ParseForm(&callExpr, returnValuePtr, (int)(intptr_t)returnValuePtr, a3);
      }
      else
      {
        Rules_ExecuteRuleActions(
          **(_DWORD **)(uintptr_t)(g_ClipsCurrentGeneric + 8),
          *(__int16 **)(uintptr_t)(g_ClipsCurrentMethod + 32),
          returnValuePtr,
          *(_DWORD *)(uintptr_t)(g_ClipsCurrentMethod + 20),
          a3,
          (void (*)(void))Method_PrintCallErrorBanner);
      }
      --*(_DWORD *)(uintptr_t)(g_ClipsCurrentMethod + 4);
      if ( (*(_BYTE *)(uintptr_t)(g_ClipsCurrentMethod + 24) & 2) != 0 )
        Method_PrintMethodCallTrace((int)(intptr_t)asc_50B740);
      result = 0;
      g_ClipsCurrentMethod = savedMethod;
      g_ClipsHaltExecutionFlag = 0;
    }
    else
    {
      g_ClipsCurrentMethod = savedMethod;
      Rules_PrintErrorID((int)(intptr_t)aGenrcexe, 2, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aShadowedMethod, v6);
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
    result = Defgeneric_CheckGenericExists((int)(intptr_t)aCallSpecific_0, *(_BYTE **)(uintptr_t)(v7 + 16));
    generic = result;
    if ( result )
    {
      result = Lexer_ParseValueList(2, argBuffer, 1, a2);
      if ( result )
      {
        result = Defgeneric_CheckMethodExists((int)(intptr_t)aCallSpecific_0, generic, *(_DWORD *)(uintptr_t)(v7 + 16));
        if ( result != -1 )
        {
          methodByteOffset = 40 * result;
          ++*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(generic + 28) + 40 * result + 4);
          Method_DispatchGenericCall(
            generic,
            0,
            *(_DWORD **)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10) + 10),
            (int *)(uintptr_t)(40 * result + *(_DWORD *)(uintptr_t)(generic + 28)),
            a2,
            returnValue);
          result = *(_DWORD *)(uintptr_t)(generic + 28);
          --*(_DWORD *)(uintptr_t)(result + methodByteOffset + 4);
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
      return (_DWORD *)(uintptr_t)Method_DispatchGenericCall(g_ClipsCurrentGeneric, g_ClipsCurrentMethod, *(_DWORD **)(uintptr_t)(g_ClipsCurrentExpression + 6), 0, a2, result);
    }
    else
    {
      Rules_PrintErrorID((int)(intptr_t)aGenrcexe, 2, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aShadowedMethod, v2);
      return (_DWORD *)(uintptr_t)Lexer_ErrorRecover(1);
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
  result[1] = *(_DWORD *)(uintptr_t)(g_Method_CurrentArgParamPtr + 4);
  result[2] = *(_DWORD *)(uintptr_t)(g_Method_CurrentArgParamPtr + 8);
  result[3] = *(_DWORD *)(uintptr_t)(g_Method_CurrentArgParamPtr + 12);
  result[4] = *(_DWORD *)(uintptr_t)(g_Method_CurrentArgParamPtr + 16);
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
    candidate = *(_DWORD *)(uintptr_t)(generic + 28);
  while ( 1 )
  {
    if ( candidate >= 40 * *(_DWORD *)(uintptr_t)(genericPtr + 32) + *(_DWORD *)(uintptr_t)(genericPtr + 28) )
      return 0;
    ++*(_DWORD *)(uintptr_t)(candidate + 4);
    if ( Method_RestrictionsSatisfiedByArgs(candidate, a3) )
      break;
    savedBusyCount = *(_DWORD *)(uintptr_t)(matchedMethod + 4);
    candidate = matchedMethod + 40;
    *(_DWORD *)(uintptr_t)(candidate - 36) = savedBusyCount - 1;
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

  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)aGnc, a1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], v1, v1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)asc_50B7D0, v2);
  currentModule = Module_GetCurrent();
  if ( currentModule != *v5 )
  {
    Name = Module_GetName(**(_DWORD **)(uintptr_t)(g_ClipsCurrentGeneric + 8));
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], Name, (int)(intptr_t)g_IO_LogicalNameTable_WTrace[0]);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)asc_50B7D4, v11);
  }
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)g_ClipsCurrentGeneric + 16), v4);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)asc_50B7D0, v6);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)aEd_1, v7);
  Rules_PrintLongInteger(v8, g_ClipsCurrentEvaluationDepth);
  return ProcParam_PrintArguments((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0]);
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

  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)aMth, a1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], v1, v1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)asc_50B7D0, v2);
  currentModule = Module_GetCurrent();
  if ( currentModule != *v5 )
  {
    Name = Module_GetName(**(_DWORD **)(uintptr_t)(g_ClipsCurrentGeneric + 8));
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], Name, (int)(intptr_t)g_IO_LogicalNameTable_WTrace[0]);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)asc_50B7D4, v7);
  }
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)g_ClipsCurrentGeneric + 16), v4);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)asc_50B7E8, v8);
  if ( (*(_BYTE *)(uintptr_t)(g_ClipsCurrentMethod + 24) & 1) != 0 )
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)aSys_0, v9);
  Rules_PrintLongInteger(v9, *(_DWORD *)(uintptr_t)g_ClipsCurrentMethod);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)asc_50B7D0, v10);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)aEd_1, v11);
  Rules_PrintLongInteger(v12, g_ClipsCurrentEvaluationDepth);
  return ProcParam_PrintArguments((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0]);
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

  argType = *(_DWORD *)(uintptr_t)(argParam + 4);
  if ( argType != 8 )
  {
    if ( argType != 7 )
      return g_ClipsPrimitiveTypeClassMap[argType];
    instancePtr = *(_DWORD **)(uintptr_t)(argParam + 8);
    if ( (instancePtr[6] & 2) == 0 )
      goto LABEL_4;
LABEL_9:
    classPtr = 0;
    goto LABEL_5;
  }
  instancePtr = Instance_FindByName(*(_DWORD *)(uintptr_t)(argParam + 8));
  if ( !instancePtr )
    goto LABEL_9;
LABEL_4:
  classPtr = instancePtr[11];
LABEL_5:
  if ( !classPtr )
  {
    Lexer_ErrorRecover(1);
    Rules_PrintErrorID((int)(intptr_t)aGenrcexe, v4, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aUnableToDeterm, v5);
    Rules_PrintDataObject((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v6);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aInGenericFunct, v7);
    genericNameString = Rules_GetConstructNameString(g_ClipsCurrentGeneric);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], genericNameString, (int)(intptr_t)g_IO_LogicalNameTable_WError[0]);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__24, v9);
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
int Deffunction_RegisterCodeGenerator(void)
{
  int result; // eax

  result = Rules_AddCodeGeneratorItem((int)(intptr_t)aDeffunctions_1, 0, 0, (int)(intptr_t)Deffunction_RegisterModuleItemAssigner, (int)(intptr_t)Deffunction_WriteConstructCodeFiles, 2);
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
             *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_DeffunctionCodeGeneratorItem + 20) + 4),
             filePtr,
             (int)(intptr_t)aSD_DD_0,
             *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_DeffunctionCodeGeneratorItem + 20) + 4));
  else
    return Output_WriteFormatted(maxIndices, 0, filePtr, (int)(intptr_t)aNull_5, v4);
}
// 4CB5A0: variable 'v4' is possibly undefined
// 54E8DC: using guessed type int dword_54E8DC;

//----- (004CB5E0) --------------------------------------------------------
int  Deffunction_WriteModuleItemReference(int filePtr, int a2)
{
  return Output_WriteFormatted(a2, **(_DWORD **)(uintptr_t)(g_DeffunctionCodeGeneratorItem + 20), filePtr, (int)(intptr_t)aMihsSD_DD_0, **(_DWORD **)(uintptr_t)(g_DeffunctionCodeGeneratorItem + 20));
}
// 54E8DC: using guessed type int dword_54E8DC;

//----- (004CB620) --------------------------------------------------------
signed int Deffunction_RegisterModuleItemAssigner(void)
{
  return Rules_RegisterModuleItemIdAssigner();
}
// 54E6A8: using guessed type int dword_54E6A8;
