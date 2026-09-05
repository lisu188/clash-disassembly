/* Generated from src/recovered/runtime/004D0560_legacy_runtime.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "runtime_internal.h"
#include "runtime_state.h"
#include "runtime_shared_state.h"
#include "../clips/clips_api.h"
#include "../media/media_api.h"
#include "../state/state_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004D8120) --------------------------------------------------------
int Compiler_AssignModuleIndices(void)
{
  int result; // eax
  int i; // ecx
  int v2; // ecx

  result = Module_NextEnum(0);
  for ( i = 0; result; i = v2 + 1 )
  {
    *(_DWORD *)(uintptr_t)(result + 24) = i;
    result = Module_NextEnum(result);
  }
  return result;
}
// 4D8136: variable 'v2' is possibly undefined
// 4D8120: using guessed type int sub_4D8120();

//----- (004D8150) --------------------------------------------------------
int  Compiler_WriteModuleReference(int fp, int theModule)
{
  char v3; // [esp+0h] [ebp-Ch]

  if ( theModule )
    return Output_WriteFormatted(
             theModule,
             *(_DWORD *)(uintptr_t)(g_ClipsDefmoduleCompilerItem + 20),
             fp,
             (int)(intptr_t)aSD_LdLd_5,
             *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefmoduleCompilerItem + 20) + 4));
  else
    return Output_WriteFormatted(0, 0, fp, (int)(intptr_t)aNull_18, v3);
}
// 4D8161: variable 'v3' is possibly undefined
// 51ACF0: using guessed type int dword_51ACF0;
// 54E6D0: using guessed type int dword_54E6D0;
// 54E908: using guessed type int dword_54E908;

//----- (004D81C0) --------------------------------------------------------
int __fastcall Compiler_WriteModuleListSetupCode(char imageID)
{
  int v1; // edx
  int v2; // ecx
  int v3; // edx
  int v4; // ecx
  char v6; // [esp-4h] [ebp-4h]

  v6 = imageID;
  if ( Module_NextEnum(0) )
    Output_WriteFormatted(
      v2,
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefmoduleCompilerItem + 20) + 4),
      v2,
      (int)(intptr_t)aSetlistofdefmo,
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefmoduleCompilerItem + 20) + 4));
  else
    Output_WriteFormatted(v2, v1, v2, (int)(intptr_t)aSetlistofdef_0, v6);
  return Output_WriteFormatted(v4, v3, v4, (int)(intptr_t)aSetcurrentmo_0, v6);
}
// 4D81E1: variable 'v2' is possibly undefined
// 4D81EF: variable 'v4' is possibly undefined
// 4D81EF: variable 'v3' is possibly undefined
// 4D81EF: variable 'v6' is possibly undefined
// 4D81FF: variable 'v1' is possibly undefined
// 54E908: using guessed type int dword_54E908;

//----- (004D8220) --------------------------------------------------------
signed int  Compiler_WriteModuleTableFile(const char *fileName, const char *pathName, int fileId, int headerFile, int maxIndices)
{
  int portItemCount; // ebp
  signed int result; // eax
  int moduleFile; // edi
  int v8; // edx
  int v9; // ecx
  int v10; // eax
  int v11; // edx
  int v12; // ecx
  int v13; // esi
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int itemList; // eax
  int theItem; // esi
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
  int itemsInFile; // [esp+0h] [ebp-38h] BYREF
  int arrayVersion; // [esp+4h] [ebp-34h] BYREF
  int fileVersion; // [esp+8h] [ebp-30h] BYREF
  const char *pathNameLocal; // [esp+Ch] [ebp-2Ch]
  const char *fileNameLocal; // [esp+10h] [ebp-28h]
  int headerFP; // [esp+14h] [ebp-24h]
  int itemFile; // [esp+18h] [ebp-20h]
  int fileIdLocal; // [esp+1Ch] [ebp-1Ch]
  int itemsWritten; // [esp+20h] [ebp-18h]
  int *Enum; // [esp+24h] [ebp-14h]
  int itemIndex; // [esp+28h] [ebp-10h]

  fileNameLocal = fileName;
  pathNameLocal = pathName;
  headerFP = headerFile;
  fileIdLocal = fileId;
  itemFile = 0;
  itemsWritten = 0;
  arrayVersion = 1;
  fileVersion = 2;
  Output_WriteFormatted(0, 0, headerFile, (int)(intptr_t)aIncludeModulde, 0);
  portItemCount = 0;
  result = Rules_OpenConstructCodeFile(fileNameLocal, (int)(intptr_t)pathNameLocal, 1, 0);
  moduleFile = result;
  if ( result )
  {
    Output_WriteFormatted(
      *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsDefmoduleCompilerItem + 20),
      *(_DWORD *)(uintptr_t)(g_ClipsDefmoduleCompilerItem + 20),
      result,
      (int)(intptr_t)aStructDefmodul,
      *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsDefmoduleCompilerItem + 20));
    Output_WriteFormatted(v9, v8, headerFP, (int)(intptr_t)aExternStructDe, *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsDefmoduleCompilerItem + 20));
    Enum = (int *)(uintptr_t)Module_NextEnum(0);
    if ( Enum )
    {
      while ( 1 )
      {
        v10 = Rules_ConstructCodeFileOpen(
                itemFile,
                fileNameLocal,
                fileIdLocal,
                pathNameLocal,
                &fileVersion,
                arrayVersion,
                headerFP,
                (char)(intptr_t)aStructDefmod_0,
                (const char *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefmoduleCompilerItem + 20) + 4),
                0,
                0);
        v13 = v10;
        itemFile = v10;
        if ( !v10 )
          break;
        Output_WriteFormatted(v12, v11, v10, (int)(intptr_t)asc_50D6C8, itemsInFile);
        Compiler_WriteSymbolReference(v13, *Enum, v14);
        Output_WriteFormatted(v16, v15, v13, (int)(intptr_t)aNull_30, itemsInFile);
        Output_WriteFormatted(fileIdLocal, itemsWritten, v13, (int)(intptr_t)aSD_1D, *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsDefmoduleCompilerItem + 20));
        itemList = Module_GetItemList();
        itemIndex = 0;
        theItem = itemList;
        while ( 1 )
        {
          v19 = Module_GetItemCount();
          if ( v19 <= v20 || !theItem )
            break;
          v22 = *(_DWORD *)(uintptr_t)(theItem + 20);
          ++itemsWritten;
          if ( v22 )
            (*(void (__fastcall **)(int, int))(uintptr_t)(theItem + 20))(maxIndices, Enum[6]);
          else
            Output_WriteFormatted(v21, 0, moduleFile, (int)(intptr_t)aNull_18, itemsInFile);
          v23 = Module_GetItemCount();
          if ( v24 >= v23 )
          {
            if ( Enum[7] )
              Output_WriteFormatted(v25, v24, moduleFile, (int)(intptr_t)asc_50D6E8, itemsInFile);
          }
          else
          {
            Output_WriteFormatted(v25, v24, moduleFile, (int)(intptr_t)asc_50D6E4, itemsInFile);
          }
          theItem = *(_DWORD *)(uintptr_t)(theItem + 28);
          ++itemIndex;
        }
        if ( Enum[3] )
        {
          Output_WriteFormatted(
            itemFile,
            *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefmoduleCompilerItem + 20) + 8),
            itemFile,
            (int)(intptr_t)aSD_DD_9,
            *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefmoduleCompilerItem + 20) + 8));
          for ( i = Enum[3]; i; ++portItemCount )
            i = *(_DWORD *)(uintptr_t)(i + 12);
        }
        else
        {
          Output_WriteFormatted(v21, v20, itemFile, (int)(intptr_t)aNull_31, itemsInFile);
        }
        if ( Enum[4] )
        {
          Output_WriteFormatted(
            itemFile,
            *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefmoduleCompilerItem + 20) + 8),
            itemFile,
            (int)(intptr_t)aSD_DD_9,
            *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefmoduleCompilerItem + 20) + 8));
          for ( j = Enum[4]; j; ++portItemCount )
            j = *(_DWORD *)(uintptr_t)(j + 12);
        }
        else
        {
          Output_WriteFormatted(v28, v27, itemFile, (int)(intptr_t)aNull_31, itemsInFile);
        }
        Output_WriteFormatted(v30, v29, itemFile, (int)(intptr_t)a0Ld, Enum[6]);
        if ( Enum[7] )
          Output_WriteFormatted(
            itemFile,
            *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefmoduleCompilerItem + 20) + 4),
            itemFile,
            (int)(intptr_t)aSD_DD_10,
            *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefmoduleCompilerItem + 20) + 4));
        else
          Output_WriteFormatted(v31, 0, itemFile, (int)(intptr_t)aNull_32, itemsInFile);
        ++itemsInFile;
        itemFile = Rules_ConstructCodeFileClose(itemFile, &itemsInFile, maxIndices, &arrayVersion, 0, 0);
        Enum = (int *)(uintptr_t)Module_NextEnum((int)(intptr_t)Enum);
        if ( !Enum )
          goto LABEL_23;
      }
      itemsInFile = maxIndices;
      Rules_ConstructCodeFileClose(0, &itemsInFile, maxIndices, &arrayVersion, 0, 0);
      fclose_(v26);
      return 0;
    }
    else
    {
LABEL_23:
      itemsInFile = maxIndices;
      Rules_ConstructCodeFileClose(itemFile, &itemsInFile, maxIndices, &arrayVersion, 0, 0);
      Output_WriteFormatted(v33, v32, moduleFile, (int)(intptr_t)Lexer_ArrayClose, itemsInFile);
      fclose_(v34);
      if ( portItemCount )
        return Compiler_WritePortItemTableFile(fileNameLocal, pathNameLocal, fileIdLocal, headerFP, maxIndices, &fileVersion);
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
        const char *fileName,
        const char *fileID,
        int imageID,
        int headerFP,
        int maxIndices,
        int *fileVersion)
{
  int fp; // edi
  int filePtr; // eax
  int v8; // edx
  int v9; // ecx
  int portItemFile; // esi
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
  int theDefmodule; // [esp+0h] [ebp-34h] BYREF
  int *thePortItem; // [esp+4h] [ebp-30h] BYREF
  int count; // [esp+8h] [ebp-2Ch] BYREF
  int importChecked; // [esp+Ch] [ebp-28h] BYREF
  int exportChecked; // [esp+10h] [ebp-24h] BYREF
  int arrayVersion; // [esp+14h] [ebp-20h] BYREF
  const char *fileIDLocal; // [esp+18h] [ebp-1Ch]
  const char *fileNameLocal; // [esp+1Ch] [ebp-18h]
  int headerFPLocal; // [esp+20h] [ebp-14h]
  int imageIDLocal; // [esp+24h] [ebp-10h]

  fileNameLocal = fileName;
  fileIDLocal = fileID;
  headerFPLocal = headerFP;
  imageIDLocal = imageID;
  theDefmodule = 0;
  thePortItem = 0;
  count = 0;
  importChecked = 0;
  exportChecked = 0;
  arrayVersion = 1;
  fp = 0;
  thePortItem = (int *)(uintptr_t)Module_NextPortItemEnum(&theDefmodule, (int *)&thePortItem, &exportChecked, &importChecked);
  if ( thePortItem )
  {
    while ( 1 )
    {
      filePtr = Rules_ConstructCodeFileOpen(
             fp,
             fileNameLocal,
             imageIDLocal,
             fileIDLocal,
             fileVersion,
             arrayVersion,
             headerFPLocal,
             (char)(intptr_t)aStructPortitem,
             (const char *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefmoduleCompilerItem + 20) + 8),
             0,
             0);
      portItemFile = filePtr;
      fp = filePtr;
      if ( !filePtr )
        break;
      Output_WriteFormatted(v9, v8, filePtr, (int)(intptr_t)asc_50D6C8, theDefmodule);
      Compiler_WriteSymbolReference(portItemFile, *thePortItem, v11);
      Output_WriteFormatted(v13, v12, portItemFile, (int)(intptr_t)asc_50D6E4, theDefmodule);
      Compiler_WriteSymbolReference(portItemFile, thePortItem[1], v14);
      Output_WriteFormatted(v16, v15, portItemFile, (int)(intptr_t)asc_50D6E4, theDefmodule);
      Compiler_WriteSymbolReference(portItemFile, thePortItem[2], v17);
      Output_WriteFormatted(v19, v18, portItemFile, (int)(intptr_t)asc_50D6E4, theDefmodule);
      if ( thePortItem[3] )
        Output_WriteFormatted(imageIDLocal, (count + 1) % maxIndices, portItemFile, (int)(intptr_t)aSD_DD_10, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefmoduleCompilerItem + 20) + 8));
      else
        Output_WriteFormatted(v21, v20, portItemFile, (int)(intptr_t)aNull_32, theDefmodule);
      ++count;
      Rules_ConstructCodeFileClose(fp, &count, maxIndices, &arrayVersion, 0, 0);
      thePortItem = (int *)(uintptr_t)Module_NextPortItemEnum(&theDefmodule, (int *)&thePortItem, &exportChecked, &importChecked);
      if ( !thePortItem )
        goto LABEL_6;
    }
    count = maxIndices;
    Rules_ConstructCodeFileClose(0, &count, maxIndices, &arrayVersion, 0, 0);
    return 0;
  }
  else
  {
LABEL_6:
    count = maxIndices;
    Rules_ConstructCodeFileClose(fp, &count, maxIndices, &arrayVersion, 0, 0);
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
int  Module_NextPortItemEnum(int *theDefmodule, int *thePortItem, _DWORD *exportChecked, _DWORD *importChecked)
{
  int currentPortItem; // ebp

  if ( !*theDefmodule )
  {
    *theDefmodule = Module_NextEnum(0);
    *thePortItem = 0;
    *importChecked = 0;
    *exportChecked = 0;
  }
  while ( *theDefmodule )
  {
    if ( *thePortItem )
      *thePortItem = *(_DWORD *)(uintptr_t)(*thePortItem + 12);
    currentPortItem = *thePortItem;
    if ( *thePortItem )
      return currentPortItem;
    if ( !*importChecked )
    {
      *thePortItem = *(_DWORD *)(uintptr_t)(*theDefmodule + 12);
      *importChecked = 1;
      if ( !*thePortItem )
      {
        *thePortItem = *(_DWORD *)(uintptr_t)(*theDefmodule + 16);
        *exportChecked = 1;
      }
LABEL_10:
      currentPortItem = *thePortItem;
      if ( *thePortItem )
        return currentPortItem;
      goto LABEL_15;
    }
    if ( *exportChecked )
      goto LABEL_10;
    *exportChecked = 1;
    *thePortItem = *(_DWORD *)(uintptr_t)(*theDefmodule + 16);
    currentPortItem = *thePortItem;
    if ( *thePortItem )
      return *thePortItem;
LABEL_15:
    *theDefmodule = Module_NextEnum(*theDefmodule);
    *importChecked = currentPortItem;
    *exportChecked = currentPortItem;
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
  Rules_RegisterEvaluationHandler((int)(intptr_t)&g_EvalNodeDescFetchJoinObjectSlotFieldRecord, 47);
  Rules_RegisterEvaluationHandler((int)(intptr_t)&g_EvalNodeDescFetchJoinObjectSlotFieldSimple, 48);
  Rules_RegisterEvaluationHandler((int)(intptr_t)&g_EvalNodeDescFetchObjectSlotFieldRecord, 45);
  Rules_RegisterEvaluationHandler((int)(intptr_t)&g_EvalNodeDescFetchObjectSlotFieldSimple, 46);
  Rules_RegisterEvaluationHandler((int)(intptr_t)&g_EvalNodeDescObjectSlotBoundVariableEqual, 50);
  Rules_RegisterEvaluationHandler((int)(intptr_t)&g_EvalNodeDescObjectSlotIndexInRange, 49);
  Rules_RegisterEvaluationHandler((int)(intptr_t)&g_EvalNodeDescObjectSlotFieldsEqual, 51);
  Rules_RegisterEvaluationHandler((int)(intptr_t)&g_EvalNodeDescObjectSlotElementFieldEqual, 53);
  Rules_RegisterEvaluationHandler((int)(intptr_t)&g_EvalNodeDescObjectSlotElementsEqual, 55);
  Rules_RegisterEvaluationHandler((int)(intptr_t)&g_EvalDescriptor_JoinObjectSlotFieldsEqual, 52);
  Rules_RegisterEvaluationHandler((int)(intptr_t)&g_EvalDescriptor_JoinObjectSlotElementFieldEqual, 54);
  return Rules_RegisterEvaluationHandler((int)(intptr_t)&g_EvalDescriptor_JoinObjectSlotElementsEqual, 56);
}

//----- (004D89B0) --------------------------------------------------------
unsigned int  Rules_EvalObjectSlotBoundVariableEqual(int theValue, _DWORD *theResult, int a3, double a4)
{
  int compareInfo; // ecx
  __int16 *boundField; // esi
  int theSegment; // edx
  int fieldIndex; // edi
  int fieldValue; // eax
  unsigned int resultBits; // eax
  unsigned int result; // eax
  int v12; // [esp-4h] [ebp-28h] BYREF
  int comparisonType; // [esp+0h] [ebp-24h]
  int comparisonValue; // [esp+4h] [ebp-20h]
  int v15 CLASH95_UNUSED; // [esp+1Ch] [ebp-8h]

  v15 = a3;
  compareInfo = *(_DWORD *)(uintptr_t)(theValue + 16);
  if ( (*(_BYTE *)(uintptr_t)(compareInfo + 1) & 2) != 0 )
  {
    /* 4D89xx: `mov esi,[esi+6]` etc. are 32-BIT loads out of emulated memory. */
    Parser_ParseForm((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6), &v12, compareInfo, a4);
    boundField = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10);
  }
  else
  {
    /* 4D89C8: `mov esi, ds:dword_51A960; mov esi,[esi+6]` - 32-bit load. */
    boundField = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6);
    if ( (*(_DWORD *)(uintptr_t)(g_ObjectPatternActiveClassNode + 4) & 0xFC) == 0x10 )
    {
      theSegment = *(_DWORD *)(uintptr_t)(g_ObjectPatternActiveClassNode + 8);
      if ( (*(_BYTE *)(uintptr_t)(compareInfo + 1) & 4) != 0 )
      {
        comparisonType = *(__int16 *)(uintptr_t)(theSegment + 6 * (*(_DWORD *)(uintptr_t)compareInfo & 0x7F) + 14);
        fieldIndex = *(_DWORD *)(uintptr_t)compareInfo & 0x7F;
      }
      else
      {
        comparisonType = *(__int16 *)(uintptr_t)(theSegment + 6 * (*(_DWORD *)(uintptr_t)(theSegment + 6) - ((*(_DWORD *)(uintptr_t)compareInfo & 0x7F) + 1)) + 14);
        fieldIndex = *(_DWORD *)(uintptr_t)(theSegment + 6) - ((*(_DWORD *)(uintptr_t)compareInfo & 0x7F) + 1);
      }
      fieldValue = *(_DWORD *)(uintptr_t)(theSegment + 6 * fieldIndex + 16);
    }
    else
    {
      comparisonType = *(_DWORD *)(uintptr_t)(g_ObjectPatternActiveClassNode + 4) << 24 >> 26;
      fieldValue = *(_DWORD *)(uintptr_t)(g_ObjectPatternActiveClassNode + 8);
    }
    comparisonValue = fieldValue;
  }
  if ( *boundField == comparisonType && comparisonValue == *(_DWORD *)(boundField + 1) )
    resultBits = *(_DWORD *)(uintptr_t)compareInfo << 24;
  else
    resultBits = *(_DWORD *)(uintptr_t)compareInfo << 23;
  result = resultBits >> 31;
  theResult[1] = 2;
  if ( result )
    theResult[2] = g_ClipsTrueSymbol;
  else
    theResult[2] = g_ClipsFalseSymbol;
  return result;
}
// 4D8A2F: variable 'v5' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51B47C: using guessed type int dword_51B47C;
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (004D8AF0) --------------------------------------------------------
signed int  Rules_FetchJoinObjectSlotFieldRecord(int theValue, _DWORD *theResult, _DWORD *a3)
{
  uintptr_t payload; // ecx
  int module; // [esp+0h] [ebp-14h] BYREF
  int slot_constraints; // [esp+4h] [ebp-10h] BYREF

  (void)a3;
  payload = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)theValue + 16);
  if ( !payload )
    return 1;
  Rules_ResolveJoinBindingRecord(((*(_DWORD *)payload << 9) >> 24) - 1, (_DWORD *)&module, (_DWORD *)&slot_constraints);
  Rules_FetchObjectSlotFieldRecordCore(theResult, (_DWORD *)(uintptr_t)(unsigned int)module, (int)payload, (_DWORD *)(uintptr_t)(unsigned int)slot_constraints);
  return 1;
}

//----- (004D8B40) --------------------------------------------------------
signed int  Rules_FetchJoinObjectSlotFieldSimple(int theValue, int theResult)
{
  int matchVar; // esi
  _DWORD *v3; // ecx
  _DWORD *theInstance; // [esp+0h] [ebp-14h] BYREF
  _DWORD v6[4]; // [esp+4h] [ebp-10h] BYREF

  v6[2] = theResult;
  matchVar = *(_DWORD *)(uintptr_t)(theValue + 16);
  Rules_ResolveJoinBindingRecord((unsigned __int8)*(_DWORD *)(uintptr_t)(matchVar + 4) - 1, &theInstance, v6);
  Rules_FetchObjectSlotFieldSimpleCore(v3, theInstance, (int)(intptr_t)v3, matchVar);
  return 1;
}
// 4D8B66: variable 'v3' is possibly undefined

//----- (004D8B90) --------------------------------------------------------
signed int  Rules_FetchObjectSlotFieldRecord(int theValue, _DWORD *theResult)
{
  Rules_FetchObjectSlotFieldRecordCore(theResult, (_DWORD *)(uintptr_t)g_ClipsObjectReteCurrentInstance, *(_DWORD *)(uintptr_t)(theValue + 16), (_DWORD *)(uintptr_t)g_ObjectPatternMarkerListHead);
  return 1;
}
// 51B478: using guessed type int dword_51B478;
// 51B484: using guessed type int dword_51B484;

//----- (004D8BD0) --------------------------------------------------------
signed int  Rules_FetchObjectSlotFieldSimple(int theValue, _DWORD *theResult, int theMarks)
{
  Rules_FetchObjectSlotFieldSimpleCore(theResult, (_DWORD *)(uintptr_t)g_ClipsObjectReteCurrentInstance, theMarks, *(_DWORD *)(uintptr_t)(theValue + 16));
  return 1;
}
// 51B478: using guessed type int dword_51B478;

//----- (004D8C00) --------------------------------------------------------
signed int  Rules_EvalObjectSlotIndexInRange(int theValue, _DWORD *theResult)
{
  int rangeBitmap; // ecx
  unsigned int minLength; // eax

  theResult[1] = 2;
  theResult[2] = g_ClipsFalseSymbol;
  rangeBitmap = *(_DWORD *)(uintptr_t)(theValue + 16);
  minLength = *(_DWORD *)(uintptr_t)rangeBitmap & 0x7FFF;
  if ( minLength > g_ObjectPatternMatchFieldCount || *(char *)(uintptr_t)(rangeBitmap + 1) < 0 && minLength < g_ObjectPatternMatchFieldCount )
    return 0;
  theResult[2] = g_ClipsTrueSymbol;
  return 1;
}
// 51B480: using guessed type int dword_51B480;
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (004D8C60) --------------------------------------------------------
unsigned int  Rules_EvalObjectSlotFieldsEqual(int theValue, _DWORD *theResult)
{
  unsigned int *compareInfo; // eax
  int slotNameMap; // esi
  int slotArray; // ecx
  int firstSlot; // ebx
  int secondSlot; // ecx
  unsigned int resultBits; // eax
  unsigned int result; // eax

  compareInfo = (unsigned int *)(uintptr_t)*(_DWORD *)(uintptr_t)(theValue + 16);
  slotNameMap = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsObjectReteCurrentInstance + 44) + 60);
  slotArray = *(_DWORD *)(uintptr_t)(g_ClipsObjectReteCurrentInstance + 72);
  firstSlot = *(_DWORD *)(uintptr_t)(slotArray + 4 * *(_DWORD *)(uintptr_t)(slotNameMap + 4 * (*compareInfo & 0x7FFF)) - 4);
  secondSlot = *(_DWORD *)(uintptr_t)(slotArray + 4 * *(_DWORD *)(uintptr_t)(slotNameMap + 4 * ((2 * *compareInfo) >> 17)) - 4);
  if ( *(_DWORD *)(uintptr_t)(firstSlot + 4) << 24 >> 26 == *(_DWORD *)(uintptr_t)(secondSlot + 4) << 24 >> 26 && *(_DWORD *)(uintptr_t)(firstSlot + 8) == *(_DWORD *)(uintptr_t)(secondSlot + 8) )
    resultBits = *compareInfo << 16;
  else
    resultBits = *compareInfo;
  result = resultBits >> 31;
  theResult[1] = 2;
  if ( result )
    theResult[2] = g_ClipsTrueSymbol;
  else
    theResult[2] = g_ClipsFalseSymbol;
  return result;
}
// 51B478: using guessed type int dword_51B478;
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (004D8CF0) --------------------------------------------------------
unsigned int  Rules_EvalObjectSlotElementFieldEqual(int theValue, _DWORD *theResult)
{
  unsigned int *compareInfo; // esi
  int fieldPtr; // eax
  int secondSlot; // edx
  unsigned int resultBits; // eax
  unsigned int result; // eax

  compareInfo = (unsigned int *)(uintptr_t)*(_DWORD *)(uintptr_t)(theValue + 16);
  fieldPtr = Rules_ResolveObjectSlotFieldPointer(g_ClipsObjectReteCurrentInstance, *compareInfo & 0x7FFF, compareInfo[1] & 0x7F, compareInfo[1] << 24 >> 31);
  secondSlot = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsObjectReteCurrentInstance + 72)
                 + 4 * *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsObjectReteCurrentInstance + 44) + 60) + 4 * ((2 * *compareInfo) >> 17))
                 - 4);
  if ( *(_WORD *)(uintptr_t)fieldPtr == *(_DWORD *)(uintptr_t)(secondSlot + 4) << 24 >> 26 && *(_DWORD *)(uintptr_t)(fieldPtr + 2) == *(_DWORD *)(uintptr_t)(secondSlot + 8) )
    resultBits = *compareInfo << 16;
  else
    resultBits = *compareInfo;
  result = resultBits >> 31;
  theResult[1] = 2;
  if ( result )
    theResult[2] = g_ClipsTrueSymbol;
  else
    theResult[2] = g_ClipsFalseSymbol;
  return result;
}
// 51B478: using guessed type int dword_51B478;
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (004D8D90) --------------------------------------------------------
unsigned int  Rules_EvalObjectSlotElementsEqual(int theValue, _DWORD *theResult)
{
  unsigned int *compareInfo; // esi
  __int16 *firstField; // ebp
  __int16 *secondField; // eax
  unsigned int resultBits; // eax
  unsigned int result; // eax

  compareInfo = (unsigned int *)(uintptr_t)*(_DWORD *)(uintptr_t)(theValue + 16);
  firstField = (__int16 *)(uintptr_t)Rules_ResolveObjectSlotFieldPointer(g_ClipsObjectReteCurrentInstance, *compareInfo & 0x7FFF, compareInfo[1] & 0x7F, compareInfo[1] << 24 >> 31);
  secondField = (__int16 *)(uintptr_t)Rules_ResolveObjectSlotFieldPointer(g_ClipsObjectReteCurrentInstance, (2 * *compareInfo) >> 17, compareInfo[1] << 17 >> 25, compareInfo[1] << 16 >> 31);
  if ( *firstField == *secondField && *(_DWORD *)(firstField + 1) == *(_DWORD *)(secondField + 1) )
    resultBits = *compareInfo << 16;
  else
    resultBits = *compareInfo;
  result = resultBits >> 31;
  theResult[1] = 2;
  if ( result )
    theResult[2] = g_ClipsTrueSymbol;
  else
    theResult[2] = g_ClipsFalseSymbol;
  return result;
}
// 51B478: using guessed type int dword_51B478;
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (004D8E30) --------------------------------------------------------
unsigned int  Rules_EvalJoinObjectSlotFieldsEqual(int theValue, _DWORD *theResult, int theBinds)
{
  /* 4D8E3D: `mov ecx,[eax+10h]` - a 32-BIT load whose result stays live in ecx
     across both sub_4D90D0 calls; IDA split it into two undefined temps v4/v6. */
  unsigned int *compareInfo; // ecx
  int firstSlot; // edi
  int secondSlot; // eax
  unsigned int resultBits; // eax
  unsigned int result; // eax
  int firstInstance; // [esp+0h] [ebp-1Ch] BYREF
  int secondInstance; // [esp+4h] [ebp-18h] BYREF
  _DWORD marksBuffer[5]; // [esp+8h] [ebp-14h] BYREF

  marksBuffer[3] = theBinds;
  compareInfo = (unsigned int *)(uintptr_t)*(_DWORD *)(uintptr_t)(theValue + 16);
  Rules_ResolveJoinBindingRecord((unsigned __int8)compareInfo[1] - 1, &firstInstance, marksBuffer);
  firstSlot = *(_DWORD *)(uintptr_t)(4 * *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(firstInstance + 44) + 60) + 4 * (*compareInfo & 0x7FFF))
                 + *(_DWORD *)(uintptr_t)(firstInstance + 72)
                 - 4);
  Rules_ResolveJoinBindingRecord((compareInfo[1] << 16 >> 24) - 1, &secondInstance, marksBuffer);
  secondSlot = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(secondInstance + 72)
                 + 4 * *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(secondInstance + 44) + 60) + 4 * ((2 * *compareInfo) >> 17))
                 - 4);
  if ( *(_DWORD *)(uintptr_t)(firstSlot + 4) << 24 >> 26 == *(_DWORD *)(uintptr_t)(secondSlot + 4) << 24 >> 26 && *(_DWORD *)(uintptr_t)(firstSlot + 8) == *(_DWORD *)(uintptr_t)(secondSlot + 8) )
    resultBits = *compareInfo << 16;
  else
    resultBits = *compareInfo;
  result = resultBits >> 31;
  theResult[1] = 2;
  if ( result )
    theResult[2] = g_ClipsTrueSymbol;
  else
    theResult[2] = g_ClipsFalseSymbol;
  return result;
}
// 4D8E53: variable 'v4' is possibly undefined
// 4D8E8B: variable 'v6' is possibly undefined
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (004D8F10) --------------------------------------------------------
unsigned int  Rules_EvalJoinObjectSlotElementFieldEqual(int theValue, _DWORD *theResult, int theBinds)
{
  _DWORD *compareInfo; // esi
  int firstFieldPtr; // ecx
  int secondSlot; // eax
  unsigned int resultBits; // eax
  unsigned int result; // eax
  int firstInstance; // [esp+0h] [ebp-1Ch] BYREF
  int secondInstance; // [esp+4h] [ebp-18h] BYREF
  _DWORD marksBuffer[5]; // [esp+8h] [ebp-14h] BYREF

  marksBuffer[3] = theBinds;
  compareInfo = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(theValue + 16);
  Rules_ResolveJoinBindingRecord((unsigned __int8)compareInfo[1] - 1, &firstInstance, marksBuffer);
  /* 4D8F4B: `call sub_4D9430; mov ecx, eax` - IDA dropped the returned pointer. */
  firstFieldPtr = Rules_ResolveObjectSlotFieldPointer(firstInstance, *compareInfo & 0x7FFF, compareInfo[1] << 9 >> 25, *compareInfo >> 31);
  Rules_ResolveJoinBindingRecord((compareInfo[1] << 16 >> 24) - 1, &secondInstance, marksBuffer);
  secondSlot = *(_DWORD *)(uintptr_t)(4 * *(_DWORD *)(uintptr_t)(4 * ((unsigned int)(2 * *compareInfo) >> 17) + *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(secondInstance + 44) + 60))
                 + *(_DWORD *)(uintptr_t)(secondInstance + 72)
                 - 4);
  if ( *(_WORD *)(uintptr_t)firstFieldPtr == *(_DWORD *)(uintptr_t)(secondSlot + 4) << 24 >> 26 && *(_DWORD *)(uintptr_t)(firstFieldPtr + 2) == *(_DWORD *)(uintptr_t)(secondSlot + 8) )
    resultBits = *compareInfo << 16;
  else
    resultBits = compareInfo[1] << 8;
  result = resultBits >> 31;
  theResult[1] = 2;
  if ( result )
    theResult[2] = g_ClipsTrueSymbol;
  else
    theResult[2] = g_ClipsFalseSymbol;
  return result;
}
// 4D8F9C: variable 'v5' is possibly undefined
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (004D9000) --------------------------------------------------------
unsigned int  Rules_EvalJoinObjectSlotElementsEqual(int theValue, _DWORD *theResult)
{
  unsigned int *compareInfo; // esi
  __int16 *firstField; // ebp
  __int16 *secondField; // eax
  unsigned int resultBits; // eax
  unsigned int result; // eax
  int firstInstance; // [esp+0h] [ebp-20h] BYREF
  int secondInstance; // [esp+4h] [ebp-1Ch] BYREF
  _DWORD marksBuffer[6]; // [esp+8h] [ebp-18h] BYREF

  compareInfo = (unsigned int *)(uintptr_t)*(_DWORD *)(uintptr_t)(theValue + 16);
  Rules_ResolveJoinBindingRecord((unsigned __int8)compareInfo[1] - 1, &firstInstance, marksBuffer);
  firstField = (__int16 *)(uintptr_t)Rules_ResolveObjectSlotFieldPointer(firstInstance, *compareInfo & 0x7FFF, compareInfo[1] << 9 >> 25, compareInfo[1] << 8 >> 31);
  Rules_ResolveJoinBindingRecord((compareInfo[1] << 16 >> 24) - 1, &secondInstance, marksBuffer);
  secondField = (__int16 *)(uintptr_t)Rules_ResolveObjectSlotFieldPointer(firstInstance, (2 * *compareInfo) >> 17, (2 * compareInfo[1]) >> 25, (unsigned __int64)compareInfo[1] >> 31);
  if ( *firstField == *secondField && *(_DWORD *)(firstField + 1) == *(_DWORD *)(secondField + 1) )
    resultBits = *compareInfo << 16;
  else
    resultBits = *compareInfo;
  result = resultBits >> 31;
  theResult[1] = 2;
  if ( result )
    theResult[2] = g_ClipsTrueSymbol;
  else
    theResult[2] = g_ClipsFalseSymbol;
  return result;
}
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (004D90D0) --------------------------------------------------------
int  Rules_ResolveJoinBindingRecord(int patternIndex, _DWORD *theInstance, _DWORD *theMarks)
{
  uintptr_t active_cell; // eax
  uintptr_t fact_list; // ecx
  int offset; // eax

  offset = 4 * patternIndex;
  if ( g_Rules_GlobalRHSBinds && (((unsigned int)*(_DWORD *)(uintptr_t)(unsigned int)g_CurrentPatternEntityPtr << 16) >> 25) - 1 == patternIndex )
  {
    active_cell = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_Rules_GlobalRHSBinds + 8);
    *theInstance = (int)(uintptr_t)(unsigned int)*(_DWORD *)active_cell;
    *theMarks = *(_DWORD *)(active_cell + 4);
    return *theMarks;
  }
  fact_list = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_Clips_CurrentPartialMatch + offset + 8);
  *theInstance = (int)(uintptr_t)(unsigned int)*(_DWORD *)fact_list;
  *theMarks = *(_DWORD *)(fact_list + 4);
  return *theMarks;
}
// 51ACFC: using guessed type int dword_51ACFC;
// 51AD00: using guessed type int dword_51AD00;
// 51AD04: using guessed type int dword_51AD04;

//----- (004D9140) --------------------------------------------------------
_DWORD * Rules_FetchObjectSlotFieldRecordCore(_DWORD *returnValue, _DWORD *theInstance, int matchVar, _DWORD *extentMarks)
{
  _DWORD *result; // eax
  int slotNameId; // edx
  int slotOffset; // edi
  int slotArrayBase; // edx
  int *slotPtr; // edi
  int fieldType; // ebp
  int fieldPosition; // eax
  int fieldIndex; // edx
  int slotValue; // eax
  int extentSize; // [esp+0h] [ebp-18h] BYREF
  int basisSlot; // [esp+4h] [ebp-14h] BYREF
  int slotIndex; // [esp+8h] [ebp-10h]

  result = theInstance;
  if ( *(char *)(uintptr_t)(matchVar + 3) < 0 )
  {
    returnValue[1] = 7;
    returnValue[2] = theInstance;
  }
  else if ( (*(_WORD *)(uintptr_t)matchVar & 0x7FFF) != 0 )
  {
    slotNameId = *(_DWORD *)(uintptr_t)matchVar & 0x7FFF;
    if ( slotNameId == 1 )
    {
      returnValue[1] = 8;
      result = (_DWORD *)(uintptr_t)result[7];
      returnValue[2] = result;
    }
    else
    {
      slotOffset = 4 * (*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(result[11] + 60) + 4 * slotNameId) - 1);
      slotArrayBase = result[18];
      slotPtr = (int *)(uintptr_t)(slotArrayBase + slotOffset);
      if ( result[5] )
      {
        if ( !g_Rules_JoinOperationInProgress )
        {
          slotIndex = ((int)(intptr_t)slotPtr - slotArrayBase) >> 2;
          basisSlot = 12 * slotIndex + result[5];
          if ( *(_DWORD *)(uintptr_t)(basisSlot + 8) )
            slotPtr = &basisSlot;
        }
      }
      if ( (*(_BYTE *)(uintptr_t)(matchVar + 4) & 1) != 0 )
      {
        returnValue[1] = *(_DWORD *)(uintptr_t)(*slotPtr + 4) << 24 >> 26;
        result = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(*slotPtr + 8);
        fieldType = returnValue[1];
        returnValue[2] = result;
        if ( fieldType == 4 )
        {
          returnValue[3] = 0;
          result = (_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*slotPtr + 8) + 6) - 1);
          returnValue[4] = result;
        }
      }
      else
      {
        fieldPosition = Rules_ComputeObjectMultifieldSegmentOffset(extentMarks, *slotPtr, &extentSize, (unsigned int)(2 * *(_DWORD *)(uintptr_t)matchVar) >> 24);
        fieldIndex = fieldPosition - 1;
        if ( extentSize == -1 )
        {
          slotValue = *slotPtr;
          if ( (*(_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)*slotPtr & 2) != 0 )
          {
            returnValue[1] = *(__int16 *)(uintptr_t)(*(_DWORD *)(uintptr_t)(slotValue + 8) + 6 * fieldIndex + 14);
            result = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*slotPtr + 8) + 6 * fieldIndex + 16);
          }
          else
          {
            returnValue[1] = *(_DWORD *)(uintptr_t)(slotValue + 4) << 24 >> 26;
            result = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(*slotPtr + 8);
          }
          returnValue[2] = result;
        }
        else
        {
          returnValue[1] = 4;
          returnValue[2] = *(_DWORD *)(uintptr_t)(*slotPtr + 8);
          returnValue[3] = fieldIndex;
          result = (_DWORD *)(uintptr_t)(extentSize + fieldPosition - 2);
          returnValue[4] = result;
        }
      }
    }
  }
  else
  {
    returnValue[1] = 2;
    result = (_DWORD *)(uintptr_t)Rules_GetConstructNameSymbol(theInstance[11]);
    returnValue[2] = result;
  }
  return result;
}
// 51A954: using guessed type int dword_51A954;

//----- (004D92D0) --------------------------------------------------------
_DWORD * Rules_FetchObjectSlotFieldSimpleCore(_DWORD *result, _DWORD *theInstance, int theMarks, int matchVar)
{
  int slotOffset; // esi
  int slotArrayBase; // edx
  _DWORD *slotPtr; // esi
  int slotValue; // edx
  int fieldsStart; // ecx
  int fieldIndex; // edx
  unsigned int fieldOffset; // ebx
  _DWORD basisSlotBuffer[4]; // [esp+0h] [ebp-10h] BYREF

  basisSlotBuffer[3] = theMarks;
  slotOffset = 4 * (*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theInstance[11] + 60) + 4 * (*(_DWORD *)(uintptr_t)matchVar & 0x7FFF)) - 1);
  slotArrayBase = theInstance[18];
  slotPtr = (_DWORD *)(uintptr_t)(slotArrayBase + slotOffset);
  if ( theInstance[5] )
  {
    if ( !g_Rules_JoinOperationInProgress )
    {
      basisSlotBuffer[0] = 12 * (((int)(intptr_t)slotPtr - slotArrayBase) >> 2) + theInstance[5];
      if ( *(_DWORD *)(uintptr_t)(basisSlotBuffer[0] + 8) )
        slotPtr = basisSlotBuffer;
    }
  }
  slotValue = *(_DWORD *)(uintptr_t)(*slotPtr + 8);
  fieldsStart = slotValue + 14;
  if ( *(char *)(uintptr_t)(matchVar + 1) >= 0 )
  {
    fieldOffset = 3 * (*(_DWORD *)(uintptr_t)(slotValue + 6) - (((unsigned int)(2 * *(_DWORD *)(uintptr_t)matchVar) >> 25) + 1));
    result[1] = *(__int16 *)(uintptr_t)(fieldsStart + 2 * fieldOffset);
    result[2] = *(_DWORD *)(uintptr_t)(fieldsStart + 2 * fieldOffset + 2);
  }
  else if ( *(char *)(uintptr_t)(matchVar + 2) >= 0 )
  {
    fieldIndex = *(_DWORD *)(uintptr_t)matchVar << 9 >> 25;
    result[1] = *(__int16 *)(uintptr_t)(fieldsStart + 6 * fieldIndex);
    result[2] = *(_DWORD *)(uintptr_t)(fieldsStart + 6 * fieldIndex + 2);
  }
  else
  {
    result[1] = 4;
    result[2] = slotValue;
    result[3] = *(_DWORD *)(uintptr_t)matchVar << 9 >> 25;
    result[4] = *(_DWORD *)(uintptr_t)(slotValue + 6) - (((unsigned int)(2 * *(_DWORD *)(uintptr_t)matchVar) >> 25) + 1);
  }
  return result;
}
// 51A954: using guessed type int dword_51A954;

//----- (004D93C0) --------------------------------------------------------
int  Rules_ComputeObjectMultifieldSegmentOffset(_DWORD *markerList, int slotPtr, int *extentSize, int fieldIndex)
{
  int adjustedIndex; // ecx
  int i; // esi
  int markerSpan; // edx
  int result; // eax
  int rangeSize; // edx

  adjustedIndex = fieldIndex;
  *extentSize = -1;
  if ( !slotPtr )
    return fieldIndex;
  for ( i = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)slotPtr + 8) + 12); markerList; markerList = (_DWORD *)(uintptr_t)markerList[4] )
  {
    if ( i == markerList[1] )
      break;
  }
  while ( markerList && i == markerList[1] )
  {
    if ( fieldIndex == *markerList )
    {
      rangeSize = markerList[3] - markerList[2] + 1;
      result = adjustedIndex;
      *extentSize = rangeSize;
      return result;
    }
    if ( fieldIndex < *markerList )
      break;
    markerSpan = markerList[3] - markerList[2];
    markerList = (_DWORD *)(uintptr_t)markerList[4];
    adjustedIndex += markerSpan;
  }
  return adjustedIndex;
}

//----- (004D9430) --------------------------------------------------------
int  Rules_ResolveObjectSlotFieldPointer(int theInstance, int slotNameID, int fieldIndex, int fromBeginning)
{
  int segment; // eax
  int fieldsBase; // edx

  segment = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theInstance + 72)
                             + 4 * *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theInstance + 44) + 60) + 4 * slotNameID)
                             - 4)
                 + 8);
  fieldsBase = segment + 14;
  if ( fromBeginning )
    return fieldsBase + 6 * fieldIndex;
  else
    return fieldsBase + 6 * (*(_DWORD *)(uintptr_t)(segment + 6) - fieldIndex - 1);
}

//----- (004D9471) --------------------------------------------------------
unsigned int  Str_DecodeMultibyteChar(_WORD *wideChar, unsigned __int8 *mbChar, unsigned int count)
{
  unsigned int charLength; // eax
  const CHAR *mbSource; // edx
  unsigned int bytesConsumed; // edi
  WCHAR WideCharStr[2]; // [esp+0h] [ebp-4h] BYREF

  if ( !mbChar )
    return 0;
  if ( !count )
    return -1;
  if ( !*mbChar )
  {
    if ( wideChar )
      *wideChar = 0;
    return 0;
  }
  if ( g_CRT_MbcsCodePageActive && (g_Clips_DbcsLeadByteTable[*mbChar] & 1) != 0 && !mbChar[1] )
    return -1;
  charLength = mbclen_();
  bytesConsumed = charLength;
  if ( count < charLength )
    charLength = count;
  if ( !MultiByteToWideChar(CodePage, 8u, mbSource, charLength, WideCharStr, 1) )
    return -1;
  if ( wideChar )
    *wideChar = WideCharStr[0];
  return bytesConsumed;
}
// 4D94E0: variable 'v6' is possibly undefined
// 4E4C37: using guessed type int mbclen_(void);
// 54E718: using guessed type int dword_54E718;

//----- (004D977B) --------------------------------------------------------
void Fpu_ClearExceptions(void)
{
  return;
}

//----- (004D97D5) --------------------------------------------------------
signed int  Str_ConfigureCodePage(UINT codePage, int leadByteTable)
{
  UINT activeCodePage; // esi
  UINT ACP; // eax
  signed int result; // eax
  int i; // eax
  int j; // eax
  UINT OEMCP; // eax
  int v8; // ecx
  int k; // edx
  int m; // eax
  int cpInfo; // [esp+0h] [ebp-28h] BYREF
  _BYTE leadByteRanges[34]; // [esp+6h] [ebp-22h]

  activeCodePage = codePage;
  switch ( codePage )
  {
    case 0xFFFFFFFF:
      ACP = GetACP();
LABEL_3:
      activeCodePage = ACP;
      break;
    case 0xFFFFFFFE:
      ACP = GetOEMCP();
      goto LABEL_3;
    case 0xFFFFFFFD:
      memset_(leadByteTable, 0);
      result = 0;
      g_CRT_MbcsCodePageActive = 0;
      CodePage = 0;
      return result;
    case 0xFFFFFFFC:
      memset_(leadByteTable, 0);
      for ( i = 129; i <= 159; g_CRT_MbcsLeadByteTable[i] = 1 )
        ++i;
      for ( j = 224; j <= 252; g_CRT_MbcsLeadByteTable[j] = 1 )
        ++j;
      OEMCP = 932;
      g_CRT_MbcsCodePageActive = 1;
      goto LABEL_27;
  }
  if ( !activeCodePage )
    activeCodePage = 1;
  if ( !GetCPInfo(activeCodePage, (LPCPINFO)&cpInfo) )
    return 1;
  memset_(v8, 0);
  g_CRT_MbcsCodePageActive = leadByteRanges[0] != 0;
  for ( k = 0; leadByteRanges[k] || leadByteRanges[k + 1]; k += 2 )
  {
    for ( m = (unsigned __int8)leadByteRanges[k]; m <= (unsigned __int8)leadByteRanges[k + 1]; g_CRT_MbcsLeadByteTable[m] = 1 )
      ++m;
  }
  if ( activeCodePage != 1 )
  {
    CodePage = activeCodePage;
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
int  Rules_ParseDeftemplateFactPattern(int readSource, _DWORD *theDeftemplate)
{
  signed int v4; // eax
  int topNode; // esi
  _DWORD *nameNode; // eax
  int firstSlot; // eax
  int theToken[3]; // [esp+0h] [ebp-24h] BYREF
  _DWORD errorFlag[6]; // [esp+Ch] [ebp-18h] BYREF

  Parser_NextToken(readSource, (int)(intptr_t)theToken);
  if ( theToken[0] == 92 || theToken[0] == 91 )
  {
    Parser_ReportSyntaxError();
    return 0;
  }
  else
  {
    v4 = AST_AllocNode();
    *(_DWORD *)(uintptr_t)v4 = 17;
    topNode = v4;
    BYTE1(v4) = *(_BYTE *)(uintptr_t)(v4 + 8);
    *(_DWORD *)(uintptr_t)(topNode + 32) = 0;
    *(_DWORD *)(uintptr_t)(topNode + 40) = 1;
    *(_BYTE *)(uintptr_t)(topNode + 8) = BYTE1(v4) & 0xFE;
    nameNode = (_DWORD *)(uintptr_t)AST_AllocNode();
    *(_DWORD *)(uintptr_t)(topNode + 68) = nameNode;
    *nameNode = 2;
    *(_BYTE *)(uintptr_t)(*(_DWORD *)(uintptr_t)(topNode + 68) + 8) &= ~1u;
    *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(topNode + 68) + 4) = *theDeftemplate;
    errorFlag[0] = 0;
    firstSlot = Lexer_ParseRuleRHS(readSource, theToken, errorFlag, (int)(intptr_t)theDeftemplate);
    if ( errorFlag[0] )
    {
      AST_FreeNode(firstSlot);
      AST_FreeNode(topNode);
      return 0;
    }
    else
    {
      *(_DWORD *)(uintptr_t)(topNode + 64) = firstSlot;
      return topNode;
    }
  }
}

//----- (004D9C40) --------------------------------------------------------
int  Lexer_ParseRuleRHS(int readSource, int *theToken, _DWORD *error, int theDeftemplate)
{
  int firstSlot; // ebp
  int tokenType; // ecx
  int v8; // ecx
  _DWORD *slotPtr; // ebx
  unsigned int *nextSlot; // eax
  int nodeToFree; // eax
  int v13; // edx
  int v14; // edx
  int position; // [esp+0h] [ebp-1Ch] BYREF
  int deftemplate; // [esp+4h] [ebp-18h]
  _DWORD *errorPtr; // [esp+8h] [ebp-14h]
  unsigned int *lastSlot; // [esp+Ch] [ebp-10h]

  deftemplate = theDeftemplate;
  errorPtr = error;
  firstSlot = 0;
  tokenType = *theToken;
  lastSlot = 0;
  if ( tokenType == 101 )
    return firstSlot;
  while ( 1 )
  {
    IO_OutNewline();
    IO_OutWriteToken(asc_50D750);
    IO_OutWriteToken((char *)(uintptr_t)theToken[2]);
    if ( *theToken != 100 || (Parser_NextToken(readSource, (int)(intptr_t)theToken), *theToken != 2) )
    {
      *errorPtr = 1;
      Parser_ReportSyntaxError();
LABEL_12:
      nodeToFree = firstSlot;
      goto LABEL_13;
    }
    slotPtr = Lexer_FindTemplateSlot(deftemplate, theToken[1], &position);
    if ( !slotPtr )
    {
      v13 = deftemplate;
      *errorPtr = 1;
      Rules_ReportInvalidSlotError(v8, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)v13 + 16));
      goto LABEL_12;
    }
    if ( Lexer_CheckDuplicateSlotName(firstSlot, theToken[1]) == 1 )
    {
      *errorPtr = 1;
      goto LABEL_12;
    }
    nextSlot = Lexer_ParseSlotValueList(readSource, (int)(intptr_t)theToken, errorPtr, (int)(intptr_t)slotPtr, position + 1);
    if ( *errorPtr )
      break;
    if ( lastSlot )
      lastSlot[16] = (unsigned int)(intptr_t)nextSlot;
    else
      firstSlot = (int)(intptr_t)nextSlot;
    while ( nextSlot[16] )
      nextSlot = (unsigned int *)(uintptr_t)nextSlot[16];
    lastSlot = nextSlot;
    Parser_NextToken(readSource, (int)(intptr_t)theToken);
    if ( *theToken == 101 )
      return firstSlot;
  }
  AST_FreeNode(firstSlot);
  nodeToFree = v14;
LABEL_13:
  AST_FreeNode(nodeToFree);
  return 0;
}
// 4D9D28: variable 'v8' is possibly undefined
// 4D9D42: variable 'v14' is possibly undefined

//----- (004D9D70) --------------------------------------------------------
unsigned int * Lexer_ParseSlotValueList(int readSource, int theToken, _DWORD *error, int theSlot, int position)
{
  int v7; // edx
  int v8; // ecx
  unsigned int *restrictionNode; // eax
  unsigned int *nextSlot; // edx
  int v12; // edx
  int v13; // edx

  IO_OutWriteToken(asc_50D750);
  Parser_NextToken(readSource, v7);
  if ( (*(_BYTE *)(uintptr_t)(theSlot + 4) & 1) != 0 )
  {
    nextSlot = Rules_ParsePatternFieldList(readSource, (int *)(uintptr_t)theToken, v8, 1, position - 1, (int *)(uintptr_t)*(_DWORD *)(uintptr_t)(theSlot + 8), 1);
    if ( !nextSlot )
    {
      *error = 1;
      return 0;
    }
  }
  else
  {
    restrictionNode = Rules_ParsePatternFieldList(readSource, (int *)(uintptr_t)theToken, *(_DWORD *)(uintptr_t)theSlot, 0, position - 1, (int *)(uintptr_t)*(_DWORD *)(uintptr_t)(theSlot + 8), 0);
    nextSlot = restrictionNode;
    if ( !restrictionNode )
    {
      *error = 1;
      return 0;
    }
    if ( *restrictionNode == 16 || *restrictionNode == 4 )
    {
      Rules_ReportSingleFieldSlotCardError();
      *error = 1;
      AST_FreeNode(v12);
      return 0;
    }
  }
  if ( *(_DWORD *)(uintptr_t)theToken == 101 )
  {
    if ( !nextSlot[17] && (*(_BYTE *)(uintptr_t)(theSlot + 4) & 1) != 0 )
    {
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(asc_50D754);
    }
    return nextSlot;
  }
  else
  {
    IO_OutNewline();
    IO_OutWriteToken(asc_50D750);
    IO_OutWriteToken((char *)(uintptr_t)*(_DWORD *)(uintptr_t)(theToken + 8));
    Parser_ReportSyntaxError();
    *error = 1;
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
signed int  Lexer_CheckDuplicateSlotName(int theSlots, int slotName)
{
  int existingName; // ecx

  if ( !theSlots )
    return 0;
  while ( 1 )
  {
    existingName = *(_DWORD *)(uintptr_t)(theSlots + 36);
    if ( slotName == existingName )
      break;
    theSlots = *(_DWORD *)(uintptr_t)(theSlots + 64);
    if ( !theSlots )
      return 0;
  }
  Rules_ReportAlreadyParsed(existingName, *(_DWORD *)(uintptr_t)(existingName + 16));
  return 1;
}

//----- (004D9ED0) --------------------------------------------------------
int * Lexer_ParseRuleLHS(int readSource, int a2, int ruleName, double a4)
{
  _DWORD *v5; // edx
  _DWORD *theLHS; // eax
  int theToken[3]; // [esp+0h] [ebp-Ch] BYREF

  theToken[2] = a2;
  theToken[0] = 0;
  g_CLIPS_CurrentRuleSalience = 0;
  g_Rules_DeclaredAutoFocusFlag = 0;
  g_ClipsParsedFormAst = 0;
  Rules_SetIndentDepth(3);
  theLHS = Lexer_ParseRuleLHSPatterns(readSource, v5, theToken, ruleName, a4);
  if ( theToken[0] )
    return 0;
  else
    return Rules_BuildConjunctionFromPatternList((int)(intptr_t)theLHS);
}
// 4D9EFF: variable 'v5' is possibly undefined
// 51C6F4: using guessed type int dword_51C6F4;
// 54E90C: using guessed type int dword_54E90C;
// 54E910: using guessed type int dword_54E910;

//----- (004D9F20) --------------------------------------------------------
_DWORD * Lexer_ParseRuleLHSPatterns(int readSource, _DWORD *theToken, int *error, int ruleName, double a5)
{
  _DWORD *theNode; // eax
  int v9; // edx
  int v10; // edi
  _DWORD *result; // eax
  _DWORD *v12; // [esp+0h] [ebp-10h]

  *error = 0;
  if ( *theToken == 2 && !strcmp_(error, Lexer_Token_Arrow) )
    return 0;
  theNode = Lexer_ParsePatternCE(readSource, 2, (int)(intptr_t)Lexer_Token_Arrow, a5, 1, (int)(intptr_t)theToken, ruleName);
  v10 = (int)(intptr_t)theNode;
  v12 = theNode;
  if ( *error == 1 )
  {
    AST_FreeNode((int)(intptr_t)theNode);
    return 0;
  }
  else
  {
    AST_Append(*error, v9);
    result = (_DWORD *)(uintptr_t)Lexer_ParsePatternCEList(2, error, Lexer_Token_Arrow, readSource, a5);
    if ( *error == 1 )
    {
      AST_FreeNode(v10);
      return 0;
    }
    else if ( v10 )
    {
      *(_DWORD *)(uintptr_t)(v10 + 68) = result;
      return v12;
    }
  }
  return result;
}
// 4D9F76: variable 'v9' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
