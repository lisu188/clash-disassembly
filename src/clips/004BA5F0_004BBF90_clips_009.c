/* Generated from src/recovered/rules/clips/004ACB00_compiler.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004BA5F0) --------------------------------------------------------
int  Rules_DeftemplateBloadRefreshSlot(_DWORD *bsaveSlot, int slotIndex)
{
  int result; // eax
  int slotNameSymbol; // edx
  int defaultExprIndex; // ebp
  int v8; // edx
  int constraintIndex; // edx
  int v10; // edx
  char v11; // bl
  int v12; // edx
  int v13; // edx
  int v14; // edx
  int v15; // edx

  result = g_DeftemplateSlotTable + 20 * slotIndex;
  slotNameSymbol = *(_DWORD *)(uintptr_t)(g_ClipsBloadSymbolPointerArray + 4 * *bsaveSlot);
  *(_DWORD *)(uintptr_t)result = slotNameSymbol;
  ++*(_DWORD *)(uintptr_t)(slotNameSymbol + 4);
  defaultExprIndex = bsaveSlot[3];
  if ( defaultExprIndex == -1 )
    v8 = 0;
  else
    v8 = 14 * defaultExprIndex + g_ClipsPackedExpressionArray;
  *(_DWORD *)(uintptr_t)(result + 12) = v8;
  constraintIndex = bsaveSlot[2];
  if ( constraintIndex == -1 )
    v10 = 0;
  else
    v10 = g_ClipsConstraintRecordArrayBase + 42 * constraintIndex;
  v11 = *(_BYTE *)(uintptr_t)(result + 4);
  *(_DWORD *)(uintptr_t)(result + 8) = v10;
  v12 = bsaveSlot[1];
  *(_BYTE *)(uintptr_t)(result + 4) = v11 & 0xFE;
  *(_DWORD *)(uintptr_t)(result + 4) |= v12 & 1;
  v13 = bsaveSlot[1];
  *(_BYTE *)(uintptr_t)(result + 4) &= ~2u;
  *(_DWORD *)(uintptr_t)(result + 4) |= v13 & 2;
  v14 = bsaveSlot[1];
  *(_BYTE *)(uintptr_t)(result + 4) &= ~4u;
  *(_DWORD *)(uintptr_t)(result + 4) |= v14 & 4;
  v15 = bsaveSlot[1];
  *(_BYTE *)(uintptr_t)(result + 4) &= ~8u;
  *(_DWORD *)(uintptr_t)(result + 4) |= v15 & 8;
  if ( bsaveSlot[4] == -1 )
    *(_DWORD *)(uintptr_t)(result + 16) = 0;
  else
    *(_DWORD *)(uintptr_t)(result + 16) = 20 * (slotIndex + 1) + g_DeftemplateSlotTable;
  return result;
}
// 54E674: using guessed type int dword_54E674;
// 54E688: using guessed type int dword_54E688;
// 54E68C: using guessed type int dword_54E68C;
// 54E844: using guessed type int dword_54E844;

//----- (004BA700) --------------------------------------------------------
int Rules_DeftemplateClearBloaded(void)
{
  int v0; // ecx
  int v1; // edx
  int v2; // edx
  int v3; // ecx
  int v4; // edx
  signed int *v5; // eax
  char v6; // dl

  v0 = 0;
  if ( g_DeftemplateBsaveCount > 0 )
  {
    v1 = 0;
    do
    {
      Rules_ReleaseSymbolReference((int *)(uintptr_t)(v1 + g_DeftemplateRecordTable), v0 + 1);
      v1 = v2 + 36;
    }
    while ( v0 < g_DeftemplateBsaveCount );
  }
  if ( g_Deftemplate_SlotCount > 0 )
  {
    v0 = 0;
    do
    {
      Rules_DecrementSymbolCount(*(_DWORD *)(uintptr_t)(v0 + g_DeftemplateSlotTable), v0);
      v0 = v3 + 20;
    }
    while ( v4 < g_Deftemplate_SlotCount );
  }
  if ( 12 * g_DeftemplateModuleItemCount )
    Mem_ReleasePoolBlock(g_ClipsDeftemplateModuleItemArray, 12 * g_DeftemplateModuleItemCount);
  if ( 36 * g_DeftemplateBsaveCount )
    Mem_ReleasePoolBlock(g_DeftemplateRecordTable, 36 * g_DeftemplateBsaveCount);
  if ( 20 * g_Deftemplate_SlotCount )
    Mem_ReleasePoolBlock(g_DeftemplateSlotTable, 20 * g_Deftemplate_SlotCount);
  v5 = Str_Intern(aInitialFact_0, v0);
  return Rules_CreateDeftemplateRecord((int)(intptr_t)v5, v6);
}
// 4BA71A: variable 'v0' is possibly undefined
// 4BA726: variable 'v2' is possibly undefined
// 4BA752: variable 'v3' is possibly undefined
// 4BA757: variable 'v4' is possibly undefined
// 4BA7C9: variable 'v6' is possibly undefined
// 54E840: using guessed type int dword_54E840;
// 54E844: using guessed type int dword_54E844;
// 54E848: using guessed type int dword_54E848;
// 54E84C: using guessed type int dword_54E84C;
// 54E850: using guessed type int dword_54E850;
// 54E854: using guessed type int dword_54E854;

//----- (004BA800) --------------------------------------------------------
int  Rules_DeftemplateGetBloadedModuleItem(int moduleIndex)
{
  return 12 * moduleIndex + g_ClipsDeftemplateModuleItemArray;
}
// 54E84C: using guessed type int dword_54E84C;

//----- (004BA820) --------------------------------------------------------
int Rules_RegisterDeftemplateCodeGen(void)
{
  int result; // eax

  result = Rules_AddCodeGeneratorItem((int)(intptr_t)aDeftemplate_3, 0, 0, 0, (int)(intptr_t)Rules_DeftemplateGenerateCode, 3);
  g_Clips_DeftemplateCodeGenItem = result;
  return result;
}
// 54E858: using guessed type int dword_54E858;

//----- (004BA850) --------------------------------------------------------
int  Rules_DeftemplateGenerateCode(const char *fileName, const char *fileNameBuffer, int pathName, int headerFP, int maxIndices)
{
  int v5; // edx
  int v6; // esi
  int Enum; // eax
  int v8; // edx
  int slotFile; // esi
  int v10; // eax
  int moduleFilePtr; // edi
  int v12; // eax
  int recordFilePtr; // edi
  int v14; // eax
  int v15; // edi
  int v16; // eax
  int theSlot; // edi
  int v18; // eax
  int slotFilePtr; // esi
  int v20; // eax
  int v21; // ecx
  int fileCount; // [esp+0h] [ebp-50h] BYREF
  int slotArrayCount; // [esp+4h] [ebp-4Ch] BYREF
  int slotArrayVersion; // [esp+8h] [ebp-48h] BYREF
  int moduleArrayCount; // [esp+Ch] [ebp-44h] BYREF
  int moduleArrayVersion; // [esp+10h] [ebp-40h] BYREF
  int recordArrayCount; // [esp+14h] [ebp-3Ch] BYREF
  int recordArrayVersion; // [esp+18h] [ebp-38h] BYREF
  int moduleFile; // [esp+1Ch] [ebp-34h]
  int theModule; // [esp+20h] [ebp-30h]
  int moduleCount; // [esp+24h] [ebp-2Ch]
  int recordFile; // [esp+28h] [ebp-28h]
  int theDeftemplate; // [esp+2Ch] [ebp-24h]
  const char *fileNameBufferPtr; // [esp+30h] [ebp-20h]
  const char *fileNamePtr; // [esp+34h] [ebp-1Ch]
  int headerFilePtr; // [esp+38h] [ebp-18h]
  int pathNamePtr; // [esp+3Ch] [ebp-14h]
  int slotCount; // [esp+40h] [ebp-10h]

  fileNamePtr = fileName;
  fileNameBufferPtr = fileNameBuffer;
  headerFilePtr = headerFP;
  pathNamePtr = pathName;
  slotCount = 0;
  slotArrayCount = 0;
  slotArrayVersion = 1;
  moduleCount = 0;
  moduleArrayCount = 0;
  moduleArrayVersion = 1;
  recordArrayCount = 0;
  recordArrayVersion = 1;
  moduleFile = 0;
  recordFile = 0;
  Output_WriteFormatted(0, 1, headerFP, (int)(intptr_t)aIncludeTmpltde, 1);
  v6 = v5;
  Enum = Module_NextEnum(0);
  slotFile = v8 ^ v6;
  theModule = Enum;
  if ( Enum )
  {
    while ( 1 )
    {
      Module_SetCurrent(theModule);
      v10 = Rules_ConstructCodeFileOpen(
              moduleFile,
              fileNamePtr,
              pathNamePtr,
              fileNameBufferPtr,
              &fileCount,
              moduleArrayVersion,
              headerFilePtr,
              (char)(intptr_t)aStructDeftempl,
              **(const char ***)(uintptr_t)(g_Clips_DeftemplateCodeGenItem + 20),
              0,
              0);
      moduleFilePtr = v10;
      if ( !v10 )
      {
        Rules_DeftemplateCodeGenCloseFiles(0, recordFile, maxIndices, slotFile);
        return 0;
      }
      Rules_DeftemplateWriteModuleHeaderToCode(v10, theModule, maxIndices, moduleCount);
      moduleFile = Rules_ConstructCodeFileClose(moduleFilePtr, &moduleArrayCount, maxIndices, &moduleArrayVersion, 0, 0);
      theDeftemplate = Rules_GetNextDeftemplate(0);
      if ( theDeftemplate )
        break;
LABEL_9:
      theModule = Module_NextEnum(theModule);
      moduleCount = v21 + 1;
      ++moduleArrayCount;
      if ( !theModule )
        goto LABEL_10;
    }
    while ( 1 )
    {
      v12 = Rules_ConstructCodeFileOpen(
              recordFile,
              fileNamePtr,
              pathNamePtr,
              fileNameBufferPtr,
              &fileCount,
              recordArrayVersion,
              headerFilePtr,
              (char)(intptr_t)aStructDeftem_0,
              *(const char **)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_Clips_DeftemplateCodeGenItem + 20) + 4),
              0,
              0);
      recordFilePtr = v12;
      if ( !v12 )
      {
        Rules_DeftemplateCodeGenCloseFiles(moduleFile, 0, maxIndices, slotFile);
        return 0;
      }
      Rules_DeftemplateWriteRecordToCode(v12, theDeftemplate, maxIndices, pathNamePtr, moduleCount, slotCount);
      v14 = recordFilePtr;
      ++recordArrayCount;
      v15 = theDeftemplate;
      v16 = Rules_ConstructCodeFileClose(v14, &recordArrayCount, maxIndices, &recordArrayVersion, 0, 0);
      theSlot = *(_DWORD *)(uintptr_t)(v15 + 20);
      recordFile = v16;
      if ( theSlot )
        break;
LABEL_8:
      theDeftemplate = Rules_GetNextDeftemplate(theDeftemplate);
      if ( !theDeftemplate )
        goto LABEL_9;
    }
    while ( 1 )
    {
      v18 = Rules_ConstructCodeFileOpen(
              slotFile,
              fileNamePtr,
              pathNamePtr,
              fileNameBufferPtr,
              &fileCount,
              slotArrayVersion,
              headerFilePtr,
              (char)(intptr_t)aStructTemplate,
              *(const char **)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_Clips_DeftemplateCodeGenItem + 20) + 8),
              0,
              0);
      slotFilePtr = v18;
      if ( !v18 )
        break;
      Rules_DeftemplateWriteSlotToCode(v18, theSlot, maxIndices, pathNamePtr, slotCount++);
      ++slotArrayCount;
      v20 = Rules_ConstructCodeFileClose(slotFilePtr, &slotArrayCount, maxIndices, &slotArrayVersion, 0, 0);
      theSlot = *(_DWORD *)(uintptr_t)(theSlot + 16);
      slotFile = v20;
      if ( !theSlot )
        goto LABEL_8;
    }
    Rules_DeftemplateCodeGenCloseFiles(moduleFile, recordFile, maxIndices, 0);
    return 0;
  }
  else
  {
LABEL_10:
    Rules_DeftemplateCodeGenCloseFiles(moduleFile, recordFile, maxIndices, slotFile);
    return 1;
  }
}
// 4BA8AD: variable 'v5' is possibly undefined
// 4BA8B4: variable 'v8' is possibly undefined
// 4BAA90: variable 'v21' is possibly undefined
// 54E858: using guessed type int dword_54E858;

//----- (004BAB10) --------------------------------------------------------
int  Rules_DeftemplateCodeGenCloseFiles(int moduleFile, int recordFile, int maxIndices, int slotFile)
{
  int result; // eax
  int v8; // [esp+0h] [ebp-14h] BYREF
  _DWORD v9[4]; // [esp+4h] [ebp-10h] BYREF

  result = slotFile;
  v8 = maxIndices;
  v9[0] = 0;
  if ( slotFile )
    result = Rules_ConstructCodeFileClose(slotFile, &v8, maxIndices, v9, 0, 0);
  if ( recordFile )
  {
    v8 = maxIndices;
    result = Rules_ConstructCodeFileClose(recordFile, &v8, maxIndices, v9, 0, 0);
  }
  if ( moduleFile )
  {
    v8 = maxIndices;
    return Rules_ConstructCodeFileClose(moduleFile, &v8, maxIndices, v9, 0, 0);
  }
  return result;
}

//----- (004BAB90) --------------------------------------------------------
int  Rules_DeftemplateWriteModuleHeaderToCode(int filePtr, int theModule, int maxIndices, int moduleCount)
{
  int v5; // edx
  int v6; // ecx
  int v7; // edx
  int v8; // ecx
  char v10; // [esp+0h] [ebp-Ch]
  char v11; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(maxIndices, theModule, filePtr, (int)(intptr_t)asc_50A17C, v10);
  Rules_WriteConstructModuleItemHeaderToCode(filePtr, v5, v6, g_ClipsDeftemplateModuleItemId, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_Clips_DeftemplateCodeGenItem + 20) + 4));
  return Output_WriteFormatted(v8, v7, filePtr, (int)(intptr_t)asc_50A180, v11);
}
// 4BAB9B: variable 'v10' is possibly undefined
// 4BABB8: variable 'v5' is possibly undefined
// 4BABB8: variable 'v6' is possibly undefined
// 4BABC3: variable 'v8' is possibly undefined
// 4BABC3: variable 'v7' is possibly undefined
// 4BABC3: variable 'v11' is possibly undefined
// 54E654: using guessed type int dword_54E654;
// 54E858: using guessed type int dword_54E858;

//----- (004BABE0) --------------------------------------------------------
int  Rules_DeftemplateWriteRecordToCode(int filePtr, int theDeftemplate, int maxIndices, char a4, int moduleCount, int a6)
{
  int v9; // edx
  int v10; // ecx
  int v11; // edx
  int v12; // ecx
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // eax
  int v18; // edx
  int v19; // ecx
  char v21; // [esp+0h] [ebp-10h]
  int v22; // [esp+0h] [ebp-10h]

  Output_WriteFormatted(maxIndices, theDeftemplate, filePtr, (int)(intptr_t)asc_50A17C, a4);
  Rules_WriteConstructHeaderToCode(filePtr, theDeftemplate, maxIndices, moduleCount, **(_DWORD **)(uintptr_t)(g_Clips_DeftemplateCodeGenItem + 20), *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_Clips_DeftemplateCodeGenItem + 20) + 4));
  Output_WriteFormatted(v10, v9, filePtr, (int)(intptr_t)asc_50A184, v21);
  if ( *(_DWORD *)(uintptr_t)(theDeftemplate + 20) )
    Output_WriteFormatted(
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_Clips_DeftemplateCodeGenItem + 20) + 8),
      v22,
      filePtr,
      (int)(intptr_t)aSD_DD_5,
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_Clips_DeftemplateCodeGenItem + 20) + 8));
  else
    Output_WriteFormatted(v12, v11, filePtr, (int)(intptr_t)aNull_19, v22);
  Output_WriteFormatted(v14, v13, filePtr, (int)(intptr_t)aD00DLd, *(_BYTE *)(uintptr_t)(theDeftemplate + 24) & 1);
  v17 = *(_DWORD *)(uintptr_t)(theDeftemplate + 32);
  if ( v17 )
    Rules_FactPatternNetworkWriteNodeRefToCode(v17, filePtr, maxIndices);
  else
    Output_WriteFormatted(v16, v15, filePtr, (int)(intptr_t)aNull_3, v22);
  return Output_WriteFormatted(v19, v18, filePtr, (int)(intptr_t)asc_50A180, v22);
}
// 4BAC26: variable 'v10' is possibly undefined
// 4BAC26: variable 'v9' is possibly undefined
// 4BAC26: variable 'v21' is possibly undefined
// 4BAC69: variable 'v22' is possibly undefined
// 4BAC8C: variable 'v14' is possibly undefined
// 4BAC8C: variable 'v13' is possibly undefined
// 4BACA1: variable 'v16' is possibly undefined
// 4BACA1: variable 'v15' is possibly undefined
// 4BACAF: variable 'v19' is possibly undefined
// 4BACAF: variable 'v18' is possibly undefined
// 4BACC6: variable 'v12' is possibly undefined
// 4BACC6: variable 'v11' is possibly undefined
// 54E858: using guessed type int dword_54E858;

//----- (004BACE0) --------------------------------------------------------
int  Rules_DeftemplateWriteSlotToCode(int filePtr, int theSlot, int maxIndices, char a4, int slotIndex)
{
  int *v8; // edx
  int v9; // ecx
  int v10; // edx
  int v11; // ecx
  int v12; // ecx
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  char v19; // [esp+0h] [ebp-10h]
  char v20; // [esp+0h] [ebp-10h]
  int v21; // [esp+0h] [ebp-10h]

  Output_WriteFormatted(maxIndices, theSlot, filePtr, (int)(intptr_t)asc_50A17C, a4);
  Compiler_WriteSymbolReference(filePtr, *v8, v9);
  Output_WriteFormatted(v11, v10, filePtr, (int)(intptr_t)aDDDD, *(_BYTE *)(uintptr_t)(theSlot + 4) & 1);
  Compiler_WriteConstraintReference(filePtr, *(_DWORD *)(uintptr_t)(theSlot + 8), v12, a4);
  Output_WriteFormatted(maxIndices, v13, filePtr, (int)(intptr_t)asc_50A184, v19);
  Rules_WriteExpressionRefToCode(filePtr, *(__int16 **)(uintptr_t)(theSlot + 12), v14, v20);
  Output_WriteFormatted(v16, v15, filePtr, (int)(intptr_t)asc_50A184, v20);
  if ( *(_DWORD *)(uintptr_t)(theSlot + 16) )
    return Output_WriteFormatted(v21, (slotIndex + 1) % maxIndices, filePtr, (int)(intptr_t)aSD_DD_6, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_Clips_DeftemplateCodeGenItem + 20) + 8));
  else
    return Output_WriteFormatted(v17, 0, filePtr, (int)(intptr_t)aNull_20, v21);
}
// 4BACFF: variable 'v8' is possibly undefined
// 4BAD01: variable 'v9' is possibly undefined
// 4BAD31: variable 'v11' is possibly undefined
// 4BAD31: variable 'v10' is possibly undefined
// 4BAD3E: variable 'v12' is possibly undefined
// 4BAD4B: variable 'v13' is possibly undefined
// 4BAD4B: variable 'v19' is possibly undefined
// 4BAD5B: variable 'v14' is possibly undefined
// 4BAD5B: variable 'v20' is possibly undefined
// 4BAD66: variable 'v16' is possibly undefined
// 4BAD66: variable 'v15' is possibly undefined
// 4BAD7B: variable 'v17' is possibly undefined
// 4BAD7B: variable 'v21' is possibly undefined
// 54E858: using guessed type int dword_54E858;

//----- (004BADD0) --------------------------------------------------------
int  Rules_DeftemplateWriteModuleHeaderRef(int filePtr, int maxIndices)
{
  return Output_WriteFormatted(maxIndices, **(_DWORD **)(uintptr_t)(g_Clips_DeftemplateCodeGenItem + 20), filePtr, (int)(intptr_t)aMihsSD_DD_3, **(_DWORD **)(uintptr_t)(g_Clips_DeftemplateCodeGenItem + 20));
}
// 54E858: using guessed type int dword_54E858;

//----- (004BAE10) --------------------------------------------------------
int  Rules_DeftemplateWriteRecordRefToCode(int filePtr, int recordIndex, int maxIndices)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( recordIndex )
    return Output_WriteFormatted(
             maxIndices,
             *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_Clips_DeftemplateCodeGenItem + 20) + 4),
             filePtr,
             (int)(intptr_t)aSD_LdLd,
             *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_Clips_DeftemplateCodeGenItem + 20) + 4));
  else
    return Output_WriteFormatted(maxIndices, 0, filePtr, (int)(intptr_t)aNull_3, v4);
}
// 4BAE20: variable 'v4' is possibly undefined
// 54E858: using guessed type int dword_54E858;

//----- (004BAE60) --------------------------------------------------------
signed int Rules_RegisterDefruleBinaryItem(void)
{
  return Rules_RegisterBinaryItem(
           (int)(intptr_t)aDefrule_1,
           20,
           (int)(intptr_t)Rules_DefruleBsaveWriteExpressions,
           (int)(intptr_t)Rules_DefruleBsaveFind,
           (int)(intptr_t)Rules_DefruleBsaveWriteCounts,
           (int)(intptr_t)Rules_DefruleBsaveWriteData,
           (int)(intptr_t)Rules_JoinNetworkBloadStorage,
           (int)(intptr_t)Rules_JoinNetworkBload,
           (int)(intptr_t)Rules_ClearBloadedJoinNetwork);
}

//----- (004BAEA0) --------------------------------------------------------
int Rules_DefruleBsaveFind(void)
{
  int i; // ebx
  _DWORD *j; // ecx
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  int k; // edx
  int v6; // edx
  int v7; // edx

  if ( Rules_IsBloaded() )
  {
    Rules_ConstructQueuePush(g_DefruleModuleBloadCount);
    Rules_ConstructQueuePush(g_RuleJoinNodeBsaveCount);
    Rules_ConstructQueuePush(g_Clips_JoinTestCount);
  }
  Rules_JoinNetworkAssignCodeGenIds(&g_DefruleModuleBloadCount, &g_RuleJoinNodeBsaveCount, &g_Clips_JoinTestCount);
  for ( i = Module_NextEnum(0); i; i = Module_NextEnum(i) )
  {
    Module_SetCurrent(i);
    for ( j = (_DWORD *)(uintptr_t)Rules_GetNextDefrule(0); j; j = (_DWORD *)(uintptr_t)Rules_GetNextDefrule(v4) )
    {
      AST_MarkNodeFieldBound(j, j[3]);
      g_ClipsExpressionNodeIndex += AST_CountTreeNodes(*(_DWORD *)(uintptr_t)(v2 + 32));
      Rules_MarkReferencedFunctions(*(__int16 **)(uintptr_t)(v3 + 32));
      for ( k = v4; k; k = *(_DWORD *)(uintptr_t)(v7 + 48) )
      {
        g_ClipsExpressionNodeIndex += AST_CountTreeNodes(*(_DWORD *)(uintptr_t)(k + 36));
        Rules_MarkReferencedFunctions(*(__int16 **)(uintptr_t)(v6 + 36));
      }
    }
  }
  return Rules_ClearJoinNetworkMarkedFlags();
}
// 4BAF10: variable 'v2' is possibly undefined
// 4BAF1E: variable 'v3' is possibly undefined
// 4BAF26: variable 'v4' is possibly undefined
// 4BAF3A: variable 'v6' is possibly undefined
// 4BAF42: variable 'v7' is possibly undefined
// 54E680: using guessed type int dword_54E680;
// 54E85C: using guessed type int dword_54E85C;
// 54E864: using guessed type int dword_54E864;
// 54E868: using guessed type int dword_54E868;

//----- (004BAF80) --------------------------------------------------------
int  Rules_DefruleBsaveWriteExpressions(int a1)
{
  int i; // edi
  int j; // esi
  int k; // ecx
  int v5; // ecx

  for ( i = Module_NextEnum(0); i; i = Module_NextEnum(i) )
  {
    Module_SetCurrent(i);
    for ( j = Rules_GetNextDefrule(0); j; j = Rules_GetNextDefrule(j) )
    {
      Rules_BsaveWriteExpression(*(__int16 **)(uintptr_t)(j + 32), a1);
      for ( k = j; k; k = *(_DWORD *)(uintptr_t)(v5 + 48) )
        Rules_BsaveWriteExpression(*(__int16 **)(uintptr_t)(k + 36), a1);
    }
  }
  return Rules_ClearJoinNetworkMarkedFlags();
}
// 4BAFC5: variable 'v5' is possibly undefined

//----- (004BB000) --------------------------------------------------------
const void * Rules_DefruleBsaveWriteCounts(int filePtr, int a2)
{
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  _DWORD v6[4]; // [esp+0h] [ebp-10h] BYREF

  v6[2] = a2;
  v6[0] = 12;
  Rules_BsaveWriteBlock(4, filePtr, v6);
  Rules_BsaveWriteBlock(4, v2, &g_DefruleModuleBloadCount);
  Rules_BsaveWriteBlock(4, v3, &g_RuleJoinNodeBsaveCount);
  return Rules_BsaveWriteBlock(4, v4, &g_Clips_JoinTestCount);
}
// 4BB02A: variable 'v2' is possibly undefined
// 4BB03B: variable 'v3' is possibly undefined
// 4BB04C: variable 'v4' is possibly undefined
// 54E85C: using guessed type int dword_54E85C;
// 54E864: using guessed type int dword_54E864;
// 54E868: using guessed type int dword_54E868;

//----- (004BB060) --------------------------------------------------------
int  Rules_DefruleBsaveWriteData(const void *filePtr, int a2)
{
  int i; // ecx
  int v4; // eax
  _DWORD *moduleItem; // eax
  int v6; // ecx
  int j; // ebx
  int k; // ecx
  int v9; // ecx
  int result; // eax
  _DWORD v11[3]; // [esp-Ch] [ebp-20h] BYREF
  _DWORD v12[5]; // [esp+0h] [ebp-14h] BYREF

  v12[3] = a2;
  v12[0] = 12 * g_DefruleModuleBloadCount + 32 * g_Clips_JoinTestCount + 44 * g_RuleJoinNodeBsaveCount;
  Rules_BsaveWriteBlock(4, (int)(intptr_t)filePtr, v12);
  g_RuleJoinNodeBsaveCount = 0;
  for ( i = Module_NextEnum(0); i; i = Module_NextEnum(v6) )
  {
    Module_SetCurrent(i);
    v4 = Module_FindItemByName((int)(intptr_t)aDefrule_1);
    moduleItem = (_DWORD *)(uintptr_t)Module_GetItem(0, *(_DWORD *)(uintptr_t)(v4 + 4));
    Module_AssignBsaveItemHeaderIndices(v11, moduleItem);
    Rules_BsaveWriteBlock(12, (int)(intptr_t)filePtr, v11);
  }
  for ( j = Module_NextEnum(0); j; j = Module_NextEnum(j) )
  {
    Module_SetCurrent(j);
    for ( k = Rules_GetNextDefrule(0); k; k = Rules_GetNextDefrule(v9) )
      Rules_BsaveDefruleDisjuncts(filePtr, k);
  }
  Rules_ClearJoinNetworkMarkedFlags();
  Rules_BsaveJoinNetworkForModules((int)(intptr_t)filePtr);
  result = Rules_IsBloaded();
  if ( result )
  {
    Rules_ConstructQueuePop(&g_DefruleModuleBloadCount);
    Rules_ConstructQueuePop(&g_RuleJoinNodeBsaveCount);
    return Rules_ConstructQueuePop(&g_Clips_JoinTestCount);
  }
  return result;
}
// 4BB0EF: variable 'v6' is possibly undefined
// 4BB12C: variable 'v9' is possibly undefined
// 54E85C: using guessed type int dword_54E85C;
// 54E864: using guessed type int dword_54E864;
// 54E868: using guessed type int dword_54E868;

//----- (004BB190) --------------------------------------------------------
const void * Rules_BsaveDefruleDisjuncts(const void *result, int theDefrule)
{
  int filePtr; // esi
  int isFirstDisjunct; // ebx
  int theDisjunct; // ecx
  int i; // edi
  _DWORD *disjunctData; // ecx
  int disjunctFlags; // eax
  int v8; // eax
  int logicalJoinNode; // ebx
  int logicalJoinBsaveId; // eax
  int lastJoinNode; // ebp
  int lastJoinBsaveId; // eax
  int v13; // ecx
  _DWORD bsaveDisjunct[5]; // [esp+0h] [ebp-40h] BYREF
  int packedFlags; // [esp+14h] [ebp-2Ch]
  int dynamicSalienceIndex; // [esp+18h] [ebp-28h]
  int actionsIndex; // [esp+1Ch] [ebp-24h]
  int logicalJoinIndex; // [esp+20h] [ebp-20h]
  int lastJoinIndex; // [esp+24h] [ebp-1Ch]
  int nextDisjunctIndex; // [esp+28h] [ebp-18h]

  filePtr = (int)(intptr_t)result;
  isFirstDisjunct = 1;
  theDisjunct = theDefrule;
  for ( i = 0; theDisjunct; isFirstDisjunct = 0 )
  {
    ++g_RuleJoinNodeBsaveCount;
    AST_ExtractPatternBindingInfo(bsaveDisjunct, theDisjunct);
    bsaveDisjunct[3] = disjunctData[5];
    bsaveDisjunct[4] = disjunctData[6];
    disjunctFlags = disjunctData[7];
    LOWORD(packedFlags) = packedFlags & 0xF000;
    packedFlags |= disjunctFlags & 0x7FF;
    v8 = disjunctData[7] << 17 >> 31;
    BYTE1(packedFlags) &= ~0x10u;
    packedFlags |= (v8 & 1) << 12;
    if ( disjunctData[8] )
    {
      if ( isFirstDisjunct )
      {
        dynamicSalienceIndex = g_ClipsExpressionNodeIndex;
        i = g_ClipsExpressionNodeIndex;
        g_ClipsExpressionNodeIndex += AST_CountTreeNodes(disjunctData[8]);
      }
      else
      {
        dynamicSalienceIndex = i;
      }
    }
    else
    {
      dynamicSalienceIndex = -1;
    }
    if ( disjunctData[9] )
    {
      actionsIndex = g_ClipsExpressionNodeIndex;
      g_ClipsExpressionNodeIndex += AST_CountTreeNodes(disjunctData[9]);
    }
    else
    {
      actionsIndex = -1;
    }
    logicalJoinNode = disjunctData[10];
    if ( logicalJoinNode )
      logicalJoinBsaveId = *(_DWORD *)(uintptr_t)(logicalJoinNode + 4);
    else
      logicalJoinBsaveId = -1;
    logicalJoinIndex = logicalJoinBsaveId;
    lastJoinNode = disjunctData[11];
    if ( lastJoinNode )
      lastJoinBsaveId = *(_DWORD *)(uintptr_t)(lastJoinNode + 4);
    else
      lastJoinBsaveId = -1;
    lastJoinIndex = lastJoinBsaveId;
    if ( disjunctData[12] )
      nextDisjunctIndex = g_RuleJoinNodeBsaveCount;
    else
      nextDisjunctIndex = -1;
    result = Rules_BsaveWriteBlock(44, filePtr, bsaveDisjunct);
    theDisjunct = *(_DWORD *)(uintptr_t)(v13 + 48);
  }
  return result;
}
// 4BB1C1: variable 'v6' is possibly undefined
// 4BB296: variable 'v13' is possibly undefined
// 54E680: using guessed type int dword_54E680;
// 54E864: using guessed type int dword_54E864;

//----- (004BB2E0) --------------------------------------------------------
int  Rules_BsaveJoinNetworkForModules(int filePtr)
{
  int result; // eax
  int i; // edi
  int theDefrule; // esi
  int *joinNode; // ecx
  int *nextJoin; // eax

  result = Module_NextEnum(0);
  for ( i = result; result; i = result )
  {
    Module_SetCurrent(i);
    theDefrule = Rules_GetNextDefrule(0);
    while ( theDefrule )
    {
      joinNode = *(int **)(uintptr_t)(theDefrule + 44);
      if ( joinNode )
      {
        do
        {
          if ( (*(_BYTE *)joinNode & 0x20) != 0 )
            Rules_BsaveJoinNode(filePtr, joinNode);
          if ( (*(_BYTE *)joinNode & 4) != 0 )
            nextJoin = (int *)(uintptr_t)joinNode[4];
          else
            nextJoin = (int *)(uintptr_t)joinNode[6];
          joinNode = nextJoin;
        }
        while ( nextJoin );
      }
      if ( *(_DWORD *)(uintptr_t)(theDefrule + 48) )
        theDefrule = *(_DWORD *)(uintptr_t)(theDefrule + 48);
      else
        theDefrule = Rules_GetNextDefrule(theDefrule);
    }
    result = Module_NextEnum(i);
  }
  return result;
}
// 4BB320: variable 'v5' is possibly undefined

//----- (004BB360) --------------------------------------------------------
const void * Rules_BsaveJoinNode(int filePtr, int *theJoin)
{
  unsigned int v3; // eax
  unsigned int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int rightSideEntry; // ebp
  int v10; // eax
  int lastLevel; // eax
  int v12; // eax
  int nextLevel; // ecx
  int v14; // eax
  int rightMatchNode; // esi
  int v16; // eax
  int rightDriveNode; // edi
  int v18; // eax
  int ruleToActivate; // ebp
  _DWORD bsaveJoin[2]; // [esp+0h] [ebp-34h] BYREF
  int rightSideEntryIndex; // [esp+8h] [ebp-2Ch]
  int nextLevelIndex; // [esp+Ch] [ebp-28h]
  int lastLevelIndex; // [esp+10h] [ebp-24h]
  int rightDriveIndex; // [esp+14h] [ebp-20h]
  int rightMatchIndex; // [esp+18h] [ebp-1Ch]
  int ruleBsaveIndex; // [esp+1Ch] [ebp-18h]

  *(_BYTE *)theJoin &= ~0x20u;
  v3 = (unsigned int)(*theJoin << 16) >> 25;
  LOWORD(bsaveJoin[0]) &= 0xC07Fu;
  bsaveJoin[0] |= (v3 & 0x7F) << 7;
  v4 = (unsigned int)(*theJoin << 23) >> 29;
  LOBYTE(bsaveJoin[0]) &= 0x8Fu;
  bsaveJoin[0] |= 16 * (v4 & 7);
  v5 = *theJoin;
  LOBYTE(bsaveJoin[0]) &= ~1u;
  bsaveJoin[0] |= v5 & 1;
  v6 = *theJoin;
  LOBYTE(bsaveJoin[0]) &= ~2u;
  bsaveJoin[0] |= v6 & 2;
  v7 = *theJoin;
  LOBYTE(bsaveJoin[0]) &= ~4u;
  bsaveJoin[0] |= v7 & 4;
  v8 = *theJoin;
  LOBYTE(bsaveJoin[0]) &= ~8u;
  bsaveJoin[0] |= v8 & 8;
  if ( (*(_BYTE *)theJoin & 4) != 0 )
  {
    rightSideEntry = theJoin[4];
    if ( rightSideEntry )
      v10 = *(_DWORD *)(uintptr_t)(rightSideEntry + 4);
    else
      v10 = -1;
    rightSideEntryIndex = v10;
  }
  else
  {
    rightSideEntryIndex = -1;
  }
  lastLevel = theJoin[6];
  if ( lastLevel )
    v12 = *(_DWORD *)(uintptr_t)(lastLevel + 4);
  else
    v12 = -1;
  lastLevelIndex = v12;
  nextLevel = theJoin[5];
  if ( nextLevel )
    v14 = *(_DWORD *)(uintptr_t)(nextLevel + 4);
  else
    v14 = -1;
  nextLevelIndex = v14;
  rightMatchNode = theJoin[8];
  if ( rightMatchNode )
    v16 = *(_DWORD *)(uintptr_t)(rightMatchNode + 4);
  else
    v16 = -1;
  rightMatchIndex = v16;
  rightDriveNode = theJoin[7];
  if ( rightDriveNode )
    v18 = *(_DWORD *)(uintptr_t)(rightDriveNode + 4);
  else
    v18 = -1;
  rightDriveIndex = v18;
  bsaveJoin[1] = AST_GetHashedNodeIndex((__int16 *)(uintptr_t)theJoin[3]);
  ruleToActivate = theJoin[9];
  if ( ruleToActivate )
    ruleBsaveIndex = *(_DWORD *)(uintptr_t)(ruleToActivate + 12);
  else
    ruleBsaveIndex = -1;
  return Rules_BsaveWriteBlock(32, filePtr, bsaveJoin);
}

//----- (004BB4C0) --------------------------------------------------------
int  Rules_BsavePackSharedRecordHeader(int result, int sourceRecord)
{
  int v2; // ecx
  int linkedNode; // esi
  int linkedIndex; // ecx
  char v5; // bh
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx

  v2 = *(_DWORD *)(uintptr_t)(sourceRecord + 12);
  *(_BYTE *)(uintptr_t)(result + 4) &= ~2u;
  *(_DWORD *)(uintptr_t)(result + 4) |= v2 & 2;
  linkedNode = *(_DWORD *)(uintptr_t)(sourceRecord + 8);
  if ( linkedNode )
    linkedIndex = *(_DWORD *)(uintptr_t)(linkedNode + 4);
  else
    linkedIndex = -1;
  v5 = *(_BYTE *)(uintptr_t)(result + 4);
  *(_DWORD *)(uintptr_t)result = linkedIndex;
  v6 = *(_DWORD *)(uintptr_t)(sourceRecord + 12);
  *(_BYTE *)(uintptr_t)(result + 4) = v5 & 0xFE;
  *(_DWORD *)(uintptr_t)(result + 4) |= v6 & 1;
  v7 = *(_DWORD *)(uintptr_t)(sourceRecord + 12);
  *(_BYTE *)(uintptr_t)(result + 4) &= ~4u;
  *(_DWORD *)(uintptr_t)(result + 4) |= v7 & 4;
  v8 = *(_DWORD *)(uintptr_t)(sourceRecord + 12) << 26 >> 31;
  *(_BYTE *)(uintptr_t)(result + 4) &= ~0x40u;
  *(_DWORD *)(uintptr_t)(result + 4) |= (v8 & 1) << 6;
  v9 = *(_DWORD *)(uintptr_t)(sourceRecord + 12) << 25 >> 31;
  *(_BYTE *)(uintptr_t)(result + 4) &= ~0x80u;
  *(_DWORD *)(uintptr_t)(result + 4) |= (v9 & 1) << 7;
  return result;
}

//----- (004BB550) --------------------------------------------------------
signed int Rules_JoinNetworkBloadStorage(void)
{
  signed int result; // eax
  int v1[3]; // [esp+0h] [ebp-Ch] BYREF

  Rules_BloadReadBlock((uintptr_t)v1, 4u);
  Rules_BloadReadBlock((uintptr_t)&g_DefruleModuleBloadCount, 4u);
  Rules_BloadReadBlock((uintptr_t)&g_RuleJoinNodeBsaveCount, 4u);
  Rules_BloadReadBlock((uintptr_t)&g_Clips_JoinTestCount, 4u);
  if ( !g_DefruleModuleBloadCount )
  {
    g_ClipsJoinNetworkModuleBloadArray = 0;
    g_ClipsBloadJoinArray = 0;
    g_ClipsJoinNodeArray = 0;
  }
  v1[0] = 16 * g_DefruleModuleBloadCount;
  result = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(16 * g_DefruleModuleBloadCount));
  g_ClipsJoinNetworkModuleBloadArray = result;
  if ( g_RuleJoinNodeBsaveCount )
  {
    v1[0] = 52 * g_RuleJoinNodeBsaveCount;
    g_ClipsBloadJoinArray = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(52 * g_RuleJoinNodeBsaveCount));
    v1[0] = 40 * g_Clips_JoinTestCount;
    result = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(40 * g_Clips_JoinTestCount));
    g_ClipsJoinNodeArray = result;
  }
  else
  {
    g_ClipsBloadJoinArray = 0;
    g_ClipsJoinNodeArray = 0;
  }
  return result;
}
// 54E85C: using guessed type int dword_54E85C;
// 54E860: using guessed type int dword_54E860;
// 54E864: using guessed type int dword_54E864;
// 54E868: using guessed type int dword_54E868;
// 54E86C: using guessed type int dword_54E86C;
// 54E870: using guessed type int dword_54E870;

//----- (004BB620) --------------------------------------------------------
signed int Rules_JoinNetworkBload(void)
{
  int v3; // [esp-8h] [ebp-Ch] BYREF

  Rules_BloadReadBlock((uintptr_t)&v3, 4u);
  Rules_BloadAndRefresh(g_DefruleModuleBloadCount, 12, (void (__fastcall *)(signed int, signed int))Rules_DefruleModuleBloadFixup);
  Rules_BloadAndRefresh(g_RuleJoinNodeBsaveCount, 44, (void (__fastcall *)(signed int, signed int))Rules_JoinBloadFixup);
  return Rules_BloadAndRefresh(g_Clips_JoinTestCount, 32, (void (__fastcall *)(signed int, signed int))Rules_JoinTestBloadFixup);
}
// 54E85C: using guessed type int dword_54E85C;
// 54E864: using guessed type int dword_54E864;
// 54E868: using guessed type int dword_54E868;

//----- (004BB680) --------------------------------------------------------
int  Rules_DefruleModuleBloadFixup(_DWORD *bsaveModule, int moduleIndex)
{
  int offset; // esi
  int result; // eax

  offset = 16 * moduleIndex;
  Module_UpdateItemHeader(bsaveModule, (_DWORD *)(uintptr_t)(16 * moduleIndex + g_ClipsJoinNetworkModuleBloadArray), g_ClipsBloadJoinArray, 52);
  result = g_ClipsJoinNetworkModuleBloadArray;
  *(_DWORD *)(uintptr_t)(offset + g_ClipsJoinNetworkModuleBloadArray + 12) = 0;
  return result;
}
// 54E860: using guessed type int dword_54E860;
// 54E870: using guessed type int dword_54E870;

//----- (004BB6C0) --------------------------------------------------------
int  Rules_JoinBloadFixup(_DWORD *bsaveJoin, int joinIndex)
{
  int networkTestIndex; // ecx
  int networkTestExpr; // eax
  int secondaryTestIndex; // ebx
  int secondaryTestExpr; // eax
  int join40Index; // ebp
  int join40Ptr; // eax
  int join44Index; // eax
  int join44Ptr; // eax
  int bloadJoinIndex; // edx
  int bloadJoinPtr; // edx
  int joinOffset; // eax
  int v16; // edi
  int packedFlags; // edx
  int v18; // edi
  int v19; // edx
  int v20; // esi
  int watchActivations; // edx
  int result; // eax
  int watchRules; // edx

  Rules_BuildIndexedSlotDescriptor((int)(intptr_t)bsaveJoin, (_DWORD *)(uintptr_t)(g_ClipsBloadJoinArray + 52 * joinIndex), g_ClipsJoinNetworkModuleBloadArray, 16, 52, g_ClipsBloadJoinArray);
  networkTestIndex = bsaveJoin[6];
  if ( networkTestIndex == -1 )
    networkTestExpr = 0;
  else
    networkTestExpr = g_ClipsPackedExpressionArray + 14 * networkTestIndex;
  *(_DWORD *)(uintptr_t)(g_ClipsBloadJoinArray + 52 * joinIndex + 32) = networkTestExpr;
  secondaryTestIndex = bsaveJoin[7];
  if ( secondaryTestIndex == -1 )
    secondaryTestExpr = 0;
  else
    secondaryTestExpr = g_ClipsPackedExpressionArray + 14 * secondaryTestIndex;
  *(_DWORD *)(uintptr_t)(52 * joinIndex + g_ClipsBloadJoinArray + 36) = secondaryTestExpr;
  join40Index = bsaveJoin[8];
  if ( join40Index == -1 )
    join40Ptr = 0;
  else
    join40Ptr = g_ClipsJoinNodeArray + 40 * join40Index;
  *(_DWORD *)(uintptr_t)(g_ClipsBloadJoinArray + 52 * joinIndex + 40) = join40Ptr;
  join44Index = bsaveJoin[9];
  if ( join44Index == -1 )
    join44Ptr = 0;
  else
    join44Ptr = 40 * join44Index + g_ClipsJoinNodeArray;
  *(_DWORD *)(uintptr_t)(g_ClipsBloadJoinArray + 52 * joinIndex + 44) = join44Ptr;
  bloadJoinIndex = bsaveJoin[10];
  if ( bloadJoinIndex == -1 )
    bloadJoinPtr = 0;
  else
    bloadJoinPtr = g_ClipsBloadJoinArray + 52 * bloadJoinIndex;
  joinOffset = 52 * joinIndex;
  *(_DWORD *)(uintptr_t)(g_ClipsBloadJoinArray + joinOffset + 48) = bloadJoinPtr;
  *(_DWORD *)(uintptr_t)(g_ClipsBloadJoinArray + joinOffset + 20) = bsaveJoin[3];
  *(_DWORD *)(uintptr_t)(g_ClipsBloadJoinArray + 52 * joinIndex + 24) = bsaveJoin[4];
  v16 = g_ClipsBloadJoinArray;
  packedFlags = bsaveJoin[5];
  *(_WORD *)(uintptr_t)(g_ClipsBloadJoinArray + joinOffset + 28) &= 0xF800u;
  *(_DWORD *)(uintptr_t)(v16 + joinOffset + 28) |= packedFlags & 0x7FF;
  v18 = g_ClipsBloadJoinArray;
  v19 = bsaveJoin[5] << 19 >> 31;
  *(_BYTE *)(uintptr_t)(g_ClipsBloadJoinArray + joinOffset + 29) &= ~0x40u;
  *(_DWORD *)(uintptr_t)(v18 + joinOffset + 28) |= v19 << 14;
  *(_BYTE *)(uintptr_t)(g_ClipsBloadJoinArray + joinOffset + 29) &= ~0x80u;
  *(_BYTE *)(uintptr_t)(g_ClipsBloadJoinArray + joinOffset + 29) &= ~8u;
  v20 = g_ClipsBloadJoinArray;
  watchActivations = g_Rules_WatchActivationsFlag & 1;
  *(_BYTE *)(uintptr_t)(g_ClipsBloadJoinArray + joinOffset + 29) &= ~0x10u;
  *(_DWORD *)(uintptr_t)(v20 + joinOffset + 28) |= watchActivations << 12;
  result = g_ClipsBloadJoinArray + joinOffset;
  watchRules = g_WatchRulesFlag & 1;
  *(_BYTE *)(uintptr_t)(result + 29) &= ~0x20u;
  *(_DWORD *)(uintptr_t)(result + 28) |= watchRules << 13;
  return result;
}
// 51A1DC: using guessed type int dword_51A1DC;
// 51AD08: using guessed type int dword_51AD08;
// 54E688: using guessed type int dword_54E688;
// 54E860: using guessed type int dword_54E860;
// 54E86C: using guessed type int dword_54E86C;
// 54E870: using guessed type int dword_54E870;

//----- (004BB8C0) --------------------------------------------------------
int  Rules_JoinTestBloadFixup(int *bsaveNode, int nodeIndex)
{
  int joinBase; // esi
  int nodeOffset; // ebx
  int packedFlags; // edi
  int v5; // esi
  int v6; // edi
  int v7; // esi
  int v8; // edi
  int v9; // esi
  int v10; // edi
  int v11; // esi
  unsigned int depthBits; // edi
  _WORD *v13; // ebx
  unsigned int rhsTypeBits; // esi
  int exprIndex; // ebp
  int networkTestExpr; // esi
  int join20Index; // ecx
  int join20Ptr; // ebx
  int join24Index; // ebx
  int join24Ptr; // esi
  int join16Index; // esi
  int join16Ptr; // ebx
  int join32Index; // edi
  int join32Ptr; // ebx
  int join28Index; // ebp
  int join28Ptr; // esi
  int bloadJoinIndex; // ecx
  int bloadJoinPtr; // ecx
  int result; // eax

  joinBase = g_ClipsJoinNodeArray;
  nodeOffset = 40 * nodeIndex;
  packedFlags = *bsaveNode;
  *(_BYTE *)(uintptr_t)(g_ClipsJoinNodeArray + nodeOffset) &= ~1u;
  *(_DWORD *)(uintptr_t)(joinBase + nodeOffset) |= packedFlags & 1;
  v5 = g_ClipsJoinNodeArray;
  v6 = *bsaveNode;
  *(_BYTE *)(uintptr_t)(g_ClipsJoinNodeArray + nodeOffset) &= ~2u;
  *(_DWORD *)(uintptr_t)(v5 + nodeOffset) |= v6 & 2;
  v7 = g_ClipsJoinNodeArray;
  v8 = *bsaveNode;
  *(_BYTE *)(uintptr_t)(g_ClipsJoinNodeArray + nodeOffset) &= ~4u;
  *(_DWORD *)(uintptr_t)(v7 + nodeOffset) |= v8 & 4;
  v9 = g_ClipsJoinNodeArray;
  v10 = *bsaveNode;
  *(_BYTE *)(uintptr_t)(g_ClipsJoinNodeArray + nodeOffset) &= ~8u;
  *(_DWORD *)(uintptr_t)(v9 + nodeOffset) |= v10 & 8;
  v11 = g_ClipsJoinNodeArray;
  depthBits = (unsigned int)(*bsaveNode << 18) >> 25;
  *(_BYTE *)(uintptr_t)(g_ClipsJoinNodeArray + nodeOffset + 1) &= 1u;
  *(_DWORD *)(uintptr_t)(v11 + nodeOffset) = ((depthBits & 0x7F) << 9) | *(_DWORD *)(uintptr_t)(v11 + 40 * nodeIndex);
  v13 = (_WORD *)(uintptr_t)(g_ClipsJoinNodeArray + 40 * nodeIndex);
  rhsTypeBits = (unsigned int)(*bsaveNode << 25) >> 29;
  *v13 &= 0xFE3Fu;
  *(_DWORD *)v13 |= (rhsTypeBits & 7) << 6;
  exprIndex = bsaveNode[1];
  if ( exprIndex == -1 )
    networkTestExpr = 0;
  else
    networkTestExpr = 14 * exprIndex + g_ClipsPackedExpressionArray;
  *(_DWORD *)(uintptr_t)(g_ClipsJoinNodeArray + 40 * nodeIndex + 12) = networkTestExpr;
  join20Index = bsaveNode[3];
  if ( join20Index == -1 )
    join20Ptr = 0;
  else
    join20Ptr = 40 * join20Index + g_ClipsJoinNodeArray;
  *(_DWORD *)(uintptr_t)(g_ClipsJoinNodeArray + 40 * nodeIndex + 20) = join20Ptr;
  join24Index = bsaveNode[4];
  if ( join24Index == -1 )
    join24Ptr = 0;
  else
    join24Ptr = 40 * join24Index + g_ClipsJoinNodeArray;
  *(_DWORD *)(uintptr_t)(g_ClipsJoinNodeArray + 40 * nodeIndex + 24) = join24Ptr;
  if ( (*(_BYTE *)bsaveNode & 4) != 0 )
  {
    join16Index = bsaveNode[2];
    if ( join16Index == -1 )
      join16Ptr = 0;
    else
      join16Ptr = 40 * join16Index + g_ClipsJoinNodeArray;
    *(_DWORD *)(uintptr_t)(g_ClipsJoinNodeArray + 40 * nodeIndex + 16) = join16Ptr;
  }
  join32Index = bsaveNode[6];
  if ( join32Index == -1 )
    join32Ptr = 0;
  else
    join32Ptr = 40 * join32Index + g_ClipsJoinNodeArray;
  *(_DWORD *)(uintptr_t)(g_ClipsJoinNodeArray + 40 * nodeIndex + 32) = join32Ptr;
  join28Index = bsaveNode[5];
  if ( join28Index == -1 )
    join28Ptr = 0;
  else
    join28Ptr = 40 * join28Index + g_ClipsJoinNodeArray;
  *(_DWORD *)(uintptr_t)(g_ClipsJoinNodeArray + 40 * nodeIndex + 28) = join28Ptr;
  bloadJoinIndex = bsaveNode[7];
  if ( bloadJoinIndex == -1 )
    bloadJoinPtr = 0;
  else
    bloadJoinPtr = 52 * bloadJoinIndex + g_ClipsBloadJoinArray;
  result = 5 * nodeIndex;
  *(_DWORD *)(uintptr_t)(g_ClipsJoinNodeArray + 8 * result + 36) = bloadJoinPtr;
  *(_BYTE *)(uintptr_t)(g_ClipsJoinNodeArray + 8 * result) &= ~0x10u;
  *(_BYTE *)(uintptr_t)(g_ClipsJoinNodeArray + 8 * result) &= ~0x20u;
  *(_DWORD *)(uintptr_t)(g_ClipsJoinNodeArray + 8 * result + 4) = 0;
  *(_DWORD *)(uintptr_t)(g_ClipsJoinNodeArray + 8 * result + 8) = 0;
  return result;
}
// 54E688: using guessed type int dword_54E688;
// 54E860: using guessed type int dword_54E860;
// 54E86C: using guessed type int dword_54E86C;

//----- (004BBB60) --------------------------------------------------------
int  Rules_BloadUnpackSharedRecordHeader(int destHeader, int *bsaveRecord)
{
  char v3; // bl
  int v4; // eax
  int v5; // eax
  int v6; // eax
  unsigned int v7; // eax
  unsigned int v8; // eax
  int v9; // ebx
  int joinIndex; // esi
  bool v11; // zf
  int v12; // edx
  int result; // eax

  v3 = *(_BYTE *)(uintptr_t)(destHeader + 12) & 0xFE;
  v4 = bsaveRecord[1];
  *(_BYTE *)(uintptr_t)(destHeader + 12) = v3;
  *(_DWORD *)(uintptr_t)(destHeader + 12) |= v4 & 1;
  v5 = bsaveRecord[1];
  *(_BYTE *)(uintptr_t)(destHeader + 12) &= ~2u;
  *(_DWORD *)(uintptr_t)(destHeader + 12) |= v5 & 2;
  v6 = bsaveRecord[1];
  *(_BYTE *)(uintptr_t)(destHeader + 12) &= ~4u;
  *(_DWORD *)(uintptr_t)(destHeader + 12) |= v6 & 4;
  v7 = (unsigned int)(bsaveRecord[1] << 25) >> 31;
  *(_BYTE *)(uintptr_t)(destHeader + 12) &= ~0x20u;
  *(_DWORD *)(uintptr_t)(destHeader + 12) |= 32 * (v7 & 1);
  v8 = (unsigned int)(bsaveRecord[1] << 24) >> 31;
  *(_BYTE *)(uintptr_t)(destHeader + 12) &= ~0x40u;
  v9 = *(_DWORD *)(uintptr_t)(destHeader + 12);
  *(_DWORD *)(uintptr_t)destHeader = 0;
  *(_DWORD *)(uintptr_t)(destHeader + 12) = ((v8 & 1) << 6) | v9;
  BYTE1(v9) = *(_BYTE *)(uintptr_t)(destHeader + 12);
  *(_DWORD *)(uintptr_t)(destHeader + 4) = 0;
  *(_BYTE *)(uintptr_t)(destHeader + 12) = BYTE1(v9) & 0xE7;
  joinIndex = *bsaveRecord;
  if ( *bsaveRecord == -1 )
  {
    v12 = 0;
    v11 = 1;
  }
  else
  {
    v11 = 40 * joinIndex + g_ClipsJoinNodeArray == 0;
    v12 = 40 * joinIndex + g_ClipsJoinNodeArray;
  }
  result = v12;
  *(_DWORD *)(uintptr_t)(destHeader + 8) = v12;
  if ( !v11 )
  {
    do
    {
      *(_DWORD *)(uintptr_t)(result + 16) = destHeader;
      result = *(_DWORD *)(uintptr_t)(result + 32);
    }
    while ( result );
  }
  return result;
}
// 54E86C: using guessed type int dword_54E86C;

//----- (004BBC30) --------------------------------------------------------
signed int Rules_ClearBloadedJoinNetwork(void)
{
  int module_node; // edx
  int offset; // edx
  int index; // ecx
  signed int result; // eax
  int findCursor; // [esp+0h] [ebp-1Ch] BYREF
  _DWORD parserEntry[6]; // [esp+4h] [ebp-18h] BYREF

  findCursor = 0;
  parserEntry[0] = 0;
  Rules_FindPatternParser((_DWORD *)&findCursor, parserEntry);
  if ( parserEntry[0] )
  {
    do
    {
      (*(void (__fastcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)parserEntry[0] + 12))(parserEntry[0]);
      parserEntry[0] = 0;
      Rules_FindPatternParser((_DWORD *)&findCursor, parserEntry);
    }
    while ( parserEntry[0] );
  }
  Module_BeginEnum();
  for ( module_node = Module_NextEnum(0); module_node; module_node = Module_NextEnum(module_node) )
  {
    Module_SetCurrent(module_node);
    Rules_ClearActivationsForModule();
  }
  Module_EndEnum();
  Rules_ClearFocusStack();
  if ( g_Clips_JoinTestCount > 0 )
  {
    offset = 0;
    for ( index = 0; index < g_Clips_JoinTestCount; ++index )
    {
      Rules_ReleaseJoinNetworkNodeChain(*(_DWORD *)(uintptr_t)(offset + g_ClipsJoinNodeArray + 8));
      offset += 40;
    }
  }
  if ( g_RuleJoinNodeBsaveCount > 0 )
  {
    offset = 0;
    for ( index = 0; index < g_RuleJoinNodeBsaveCount; ++index )
    {
      Rules_ReleaseSymbolReference((int *)(uintptr_t)(offset + g_ClipsBloadJoinArray), index + 1);
      offset += 52;
    }
  }
  if ( 16 * g_DefruleModuleBloadCount )
    Mem_ReleasePoolBlock(g_ClipsJoinNetworkModuleBloadArray, 16 * g_DefruleModuleBloadCount);
  if ( 52 * g_RuleJoinNodeBsaveCount )
    Mem_ReleasePoolBlock(g_ClipsBloadJoinArray, 52 * g_RuleJoinNodeBsaveCount);
  result = 40 * g_Clips_JoinTestCount;
  if ( 40 * g_Clips_JoinTestCount )
    return Mem_ReleasePoolBlock(g_ClipsJoinNodeArray, 40 * g_Clips_JoinTestCount);
  return result;
}
// 54E85C: using guessed type int dword_54E85C;
// 54E860: using guessed type int dword_54E860;
// 54E864: using guessed type int dword_54E864;
// 54E868: using guessed type int dword_54E868;
// 54E86C: using guessed type int dword_54E86C;
// 54E870: using guessed type int dword_54E870;

//----- (004BBD90) --------------------------------------------------------
int  Rules_JoinNetworkModuleRecord(int moduleIndex)
{
  return g_ClipsJoinNetworkModuleBloadArray + 16 * moduleIndex;
}
// 54E870: using guessed type int dword_54E870;

//----- (004BBDA0) --------------------------------------------------------
int  Rules_ParseDeftemplate(char *readSource, double a2)
{
  int v3; // edx
  int v4; // ecx
  int deftemplateName; // edi
  int v7; // ecx
  _DWORD *slotList; // ebx
  _DWORD *freeNode; // ebp
  signed int newDeftemplate; // esi
  char v11; // ah
  int v12; // ecx
  __int16 v13; // ax
  int v14; // ecx
  _DWORD *v15; // ecx
  char *v16; // eax
  _DWORD inputToken[9]; // [esp+0h] [ebp-24h] BYREF

  g_DeftemplateSlotParseErrorFlag = 0;
  Rules_SetPPBufferStatus(1);
  Rules_FlushPPBuffer();
  IO_OutWriteToken(aDeftemplate_8);
  if ( Rules_IsBloaded() == 1 )
  {
    Rules_ReportCannotLoadWithBload();
    return 1;
  }
  g_Rules_DeftemplateWatchFlag = v3;
  deftemplateName = Rules_GetConstructNameAndComment(
         (int)(intptr_t)readSource,
         (int)(intptr_t)inputToken,
         (int (*)(void))Rules_FindDeftemplateByName,
         aDeftemplate_9,
         (int (*)(void))Rules_DeleteDeftemplate,
         asc_50A228,
         1,
         1,
         1);
  if ( !deftemplateName )
    return 1;
  if ( Rules_IsReservedPatternSymbol(v4, (int)(intptr_t)aDeftemplate_9) )
  {
    Rules_PrintReservedSymbolErrorMessage(v7, (int)(intptr_t)aADeftemplateNa);
    return 1;
  }
  else
  {
    slotList = Rules_ParseTemplateSlotList(readSource, inputToken, a2);
    if ( g_DeftemplateSlotParseErrorFlag == 1 )
    {
      return 1;
    }
    else
    {
      freeNode = *(_DWORD **)(uintptr_t)(g_ClipsMemoryTable + 144);
      if ( freeNode )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 144);
        *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 144) = *freeNode;
        newDeftemplate = g_ClipsMemFreeListTemp;
      }
      else
      {
        newDeftemplate = Mem_HeapAllocWithRetry((_DWORD *)0x24);
      }
      *(_DWORD *)(uintptr_t)(newDeftemplate + 16) = 0;
      *(_WORD *)(uintptr_t)(newDeftemplate + 24) = 0;
      *(_DWORD *)(uintptr_t)(newDeftemplate + 28) = 0;
      *(_DWORD *)(uintptr_t)(newDeftemplate + 32) = 0;
      *(_DWORD *)(uintptr_t)newDeftemplate = deftemplateName;
      v11 = *(_BYTE *)(uintptr_t)(newDeftemplate + 24);
      *(_DWORD *)(uintptr_t)(newDeftemplate + 20) = slotList;
      *(_BYTE *)(uintptr_t)(newDeftemplate + 24) = v11 | 4;
      for ( *(_DWORD *)(uintptr_t)(newDeftemplate + 8) = Module_GetItem(0, g_ClipsDeftemplateModuleItemId); slotList; slotList = (_DWORD *)(uintptr_t)slotList[4] )
      {
        v13 = (*(_WORD *)(uintptr_t)(v12 + 24) >> 3) + 1;
        *(_WORD *)(uintptr_t)(v12 + 24) &= 7u;
        *(_DWORD *)(uintptr_t)(v12 + 24) |= 8 * (v13 & 0x1FFF);
      }
      if ( Mem_GetAllocFlag() == 1 )
      {
        *(_DWORD *)(uintptr_t)(v14 + 4) = 0;
      }
      else
      {
        v16 = Rules_CopyPPBuffer();
        *(_DWORD *)(uintptr_t)(v14 + 4) = v16;
      }
      if ( (g_Rules_DeftemplateWatchFlag & 1) != 0 || Rules_GetWatchItemState((int)(intptr_t)aFacts_0) )
        Rules_SetFactWatchFlag(1, v14);
      Rules_AppendConstructToModuleList(v14);
      Rules_DeftemplateInstallSlots(v15, (int)(intptr_t)v15);
      return 0;
    }
  }
}
// 4BBDEB: variable 'v3' is possibly undefined
// 4BBE2C: variable 'v4' is possibly undefined
// 4BBEB1: variable 'v12' is possibly undefined
// 4BBEFA: variable 'v14' is possibly undefined
// 4BBF1F: variable 'v15' is possibly undefined
// 4BBF38: variable 'v7' is possibly undefined
// 51A948: using guessed type int dword_51A948;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E654: using guessed type int dword_54E654;
// 54E874: using guessed type int dword_54E874;

//----- (004BBF90) --------------------------------------------------------
_DWORD * Rules_DeftemplateInstallSlots(_DWORD *result, int a2)
{
  __int16 **i; // edx
  int v3; // edx
  int v4; // edx
  _DWORD *v5; // eax
  int v6; // ecx
  int v7; // edx

  ++*(_DWORD *)(uintptr_t)(*result + 4);
  for ( i = (__int16 **)(uintptr_t)result[5]; i; i = *(__int16 ***)(uintptr_t)(v7 + 16) )
  {
    ++*((_DWORD *)*i + 1);
    AST_AddHashedNodeChain(i[3], (int)(intptr_t)i, a2);
    AST_Free(*(_DWORD *)(uintptr_t)(v3 + 12));
    v5 = *(_DWORD **)(uintptr_t)(v4 + 8);
    *(_DWORD *)(uintptr_t)(v4 + 12) = v6;
    result = AST_InternNode(v5);
    *(_DWORD *)(uintptr_t)(v7 + 8) = result;
  }
  return result;
}
// 4BBFA6: variable 'a2' is possibly undefined
// 4BBFAD: variable 'v3' is possibly undefined
// 4BBFB5: variable 'v4' is possibly undefined
// 4BBFB8: variable 'v6' is possibly undefined
// 4BBFC0: variable 'v7' is possibly undefined
