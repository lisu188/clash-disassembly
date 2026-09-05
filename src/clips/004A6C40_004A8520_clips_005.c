/* Generated from src/recovered/rules/clips/004A0080_symbols.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "clips_shared_state.h"
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004A6C40) --------------------------------------------------------
signed int  Rules_WriteFunctionDefinitionRecordsToCode(const char *fileName)
{
  int version; // edi
  int functionList; // ecx
  int bsaveIndex; // esi
  DWORD i; // ebp
  signed int result; // eax
  int v6; // edx
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int v10; // edx
  int v11; // ecx
  int functionListHead; // eax
  int v13; // edx
  int v14; // ecx
  int fctnPtr; // esi
  int v16; // edx
  int v17; // ecx
  int v18; // ecx
  int v19; // edx
  int v20; // ecx
  int v21; // edx
  int v22; // ecx
  int v23; // ecx
  int v24; // edx
  int v25; // ecx
  int v26; // edx
  int v27; // ecx
  int v28; // edx
  int v29; // ecx
  int v30; // ecx
  int v31; // ecx
  int v32; // ecx
  char v34; // [esp+0h] [ebp-20h]
  char v35; // [esp+0h] [ebp-20h]
  char v36; // [esp+0h] [ebp-20h]
  const char *v37; // [esp+0h] [ebp-20h]
  char v38; // [esp+0h] [ebp-20h]
  char v39; // [esp+0h] [ebp-20h]
  char v40; // [esp+0h] [ebp-20h]
  int entryCount; // [esp+4h] [ebp-1Ch]

  version = 1;
  functionList = Rules_GetFunctionDefinitionListHead();
  bsaveIndex = 0;
  for ( i = 1; functionList; ++bsaveIndex )
  {
    *(_WORD *)(uintptr_t)(functionList + 25) = bsaveIndex;
    functionList = *(_DWORD *)(uintptr_t)(functionList + 27);
  }
  result = Rules_OpenConstructCodeFile(fileName, 2, 1, 1u);
  if ( result )
  {
    Output_WriteFormatted(result, result, result, (int)(intptr_t)asc_507E94, (char)(intptr_t)fileName);
    Output_WriteFormatted(v7, v6, v6, (int)(intptr_t)asc_507DA4, v34);
    Output_WriteFormatted(v9, v8, v8, (int)(intptr_t)aFunctionListDe, v35);
    Output_WriteFormatted(v11, v10, v10, (int)(intptr_t)asc_507DF4, v36);
    functionListHead = Rules_GetFunctionDefinitionListHead();
    entryCount = v13;
    fctnPtr = functionListHead;
    while ( fctnPtr )
    {
      if ( i )
      {
        Output_WriteFormatted(v14, g_ConstructsToCImageId, v14, (int)(intptr_t)aStructFunction, g_ConstructsToCImageId);
        Output_WriteFormatted(v17, v16, g_ClipsCodeHeaderFile, (int)(intptr_t)aExternStructFu, g_ConstructsToCImageId);
        i = 0;
      }
      Output_WriteFormatted(v14, v13, v14, (int)(intptr_t)asc_507F14, (char)(intptr_t)v37);
      Compiler_WriteSymbolReference(v18, *(_DWORD *)(uintptr_t)fctnPtr, v18);
      Output_WriteFormatted(v20, v19, v20, (int)(intptr_t)aS_4, *(_DWORD *)(uintptr_t)(fctnPtr + 4));
      Output_WriteFormatted(v22, v21, v22, (int)(intptr_t)aC, *(_BYTE *)(uintptr_t)(fctnPtr + 8));
      Output_WriteFormatted(v23, *(_DWORD *)(uintptr_t)(fctnPtr + 4), v23, (int)(intptr_t)aPtifS, *(_DWORD *)(uintptr_t)(fctnPtr + 4));
      Output_WriteFormatted(v25, v24, v25, (int)(intptr_t)aNull_0, v38);
      if ( *(_DWORD *)(uintptr_t)(fctnPtr + 17) )
        Output_WriteFormatted(v27, v26, v27, (int)(intptr_t)aS_5, *(_DWORD *)(uintptr_t)(fctnPtr + 17));
      else
        Output_WriteFormatted(v27, v26, v27, (int)(intptr_t)aNull_0, v39);
      Output_WriteFormatted(v29, v28, v29, (int)(intptr_t)a000, v39);
      Rules_WriteFunctionRecordRefToCode(v30, *(_DWORD *)(uintptr_t)(fctnPtr + 27), v30);
      fctnPtr = *(_DWORD *)(uintptr_t)(fctnPtr + 27);
      if ( (__int16)++entryCount <= g_ClipsCodeMaxIndicesPerArray && fctnPtr )
      {
        Output_WriteFormatted(v31, g_ClipsCodeMaxIndicesPerArray, v31, (int)(intptr_t)asc_507F54, v40);
      }
      else
      {
        Output_WriteFormatted(v31, g_ClipsCodeMaxIndicesPerArray, v31, (int)(intptr_t)asc_507F4C, v40);
        fclose_(v32);
        ++version;
        entryCount = 1;
        if ( fctnPtr )
        {
          result = Rules_OpenConstructCodeFile(v37, 2, version, i);
          v14 = result;
          if ( !result )
            return result;
          i = 1;
        }
      }
    }
    return 1;
  }
  return result;
}
// 4A6CA7: variable 'v7' is possibly undefined
// 4A6CA7: variable 'v6' is possibly undefined
// 4A6CA7: variable 'v34' is possibly undefined
// 4A6CB5: variable 'v9' is possibly undefined
// 4A6CB5: variable 'v8' is possibly undefined
// 4A6CB5: variable 'v35' is possibly undefined
// 4A6CC3: variable 'v11' is possibly undefined
// 4A6CC3: variable 'v10' is possibly undefined
// 4A6CC3: variable 'v36' is possibly undefined
// 4A6CD5: variable 'v13' is possibly undefined
// 4A6CF5: variable 'v14' is possibly undefined
// 4A6D11: variable 'v17' is possibly undefined
// 4A6D11: variable 'v16' is possibly undefined
// 4A6D21: variable 'v37' is possibly undefined
// 4A6D2D: variable 'v18' is possibly undefined
// 4A6D3C: variable 'v20' is possibly undefined
// 4A6D3C: variable 'v19' is possibly undefined
// 4A6D50: variable 'v22' is possibly undefined
// 4A6D50: variable 'v21' is possibly undefined
// 4A6D62: variable 'v23' is possibly undefined
// 4A6D70: variable 'v25' is possibly undefined
// 4A6D70: variable 'v24' is possibly undefined
// 4A6D70: variable 'v38' is possibly undefined
// 4A6D8A: variable 'v27' is possibly undefined
// 4A6D8A: variable 'v26' is possibly undefined
// 4A6D98: variable 'v29' is possibly undefined
// 4A6D98: variable 'v28' is possibly undefined
// 4A6D98: variable 'v39' is possibly undefined
// 4A6DA5: variable 'v30' is possibly undefined
// 4A6DC9: variable 'v31' is possibly undefined
// 4A6DC9: variable 'v40' is possibly undefined
// 4A6DD3: variable 'v32' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51ACF0: using guessed type int dword_51ACF0;
// 54E6D0: using guessed type int dword_54E6D0;
// 54E6E8: using guessed type int dword_54E6E8;

//----- (004A6E50) --------------------------------------------------------
int  Rules_WriteFunctionRecordRefToCode(int theFile, int fctnPtr, int a3)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( fctnPtr )
    return Output_WriteFormatted(*(__int16 *)(uintptr_t)(fctnPtr + 25), *(__int16 *)(uintptr_t)(fctnPtr + 25) % g_ClipsCodeMaxIndicesPerArray, theFile, (int)(intptr_t)aPD_DD, g_ConstructsToCImageId);
  else
    return Output_WriteFormatted(a3, 0, theFile, (int)(intptr_t)aNull_1, v4);
}
// 4A6E5E: variable 'v4' is possibly undefined
// 51ACF0: using guessed type int dword_51ACF0;
// 54E6D0: using guessed type int dword_54E6D0;

//----- (004A6EB0) --------------------------------------------------------
signed int  Rules_WriteConstructsToCDriverFile(const char *fileName, char a2, DWORD a3)
{
  int v3; // ecx
  int v4; // eax
  int v5; // ecx
  int fp; // esi
  int v7; // edx
  int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // edx
  int v12; // ecx
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // edx
  int v18; // ecx
  int v19; // edx
  int v20; // ecx
  int v21; // edx
  int v22; // edx
  int v23; // ecx
  int v24; // edx
  int v25; // ecx
  int v26; // edx
  int v27; // edx
  int v28; // ecx
  int v29; // edx
  int v30; // ecx
  int v31; // edx
  int v32; // ecx
  int v33; // edx
  int v34; // ecx
  int v35; // edx
  int v36; // ecx
  int v37; // edx
  int v38; // ecx
  int v39; // edx
  int v40; // ecx
  int v41; // edx
  int v42; // ecx
  int v43; // edx
  int v44; // ecx
  int v45; // edx
  int v46; // ecx
  int v47; // edx
  int v48; // ecx
  int v49; // edx
  int v50; // edx
  int v51; // ecx
  int v52; // edx
  int v53; // ecx
  int v54; // edx
  int v55; // ecx
  int v56; // edx
  int v57; // ecx
  int v58; // edx
  int i; // ecx
  int v60; // edx
  int v61; // ecx
  int v62; // ecx
  char v64; // [esp-8h] [ebp-68h]
  char v65; // [esp-8h] [ebp-68h]
  char v66; // [esp-8h] [ebp-68h]
  char v67; // [esp-8h] [ebp-68h]
  char v68; // [esp-8h] [ebp-68h]
  char v69; // [esp-8h] [ebp-68h]
  char v70; // [esp-8h] [ebp-68h]
  char v71; // [esp-8h] [ebp-68h]
  char v72; // [esp-8h] [ebp-68h]
  char v73; // [esp-8h] [ebp-68h]
  char v74; // [esp-8h] [ebp-68h]
  char v75; // [esp-8h] [ebp-68h]
  char v76; // [esp-8h] [ebp-68h]
  char v77; // [esp-8h] [ebp-68h]
  char v78; // [esp-8h] [ebp-68h]
  char v79; // [esp-8h] [ebp-68h]
  char v80; // [esp-8h] [ebp-68h]
  char v81; // [esp-8h] [ebp-68h]
  char v82; // [esp-8h] [ebp-68h]
  CHAR fileNameBuffer[96]; // [esp+0h] [ebp-60h] BYREF

  sprintf_(fileNameBuffer, "%s.c", fileName);
  v4 = IO_FOpen(fileNameBuffer, (unsigned __int8 *)aW_2, v3, a3);
  fp = v4;
  if ( v4 )
  {
    Output_WriteFormatted(v5, v4, v4, (int)(intptr_t)aIncludeS_h, v5);
    Output_WriteFormatted(v8, v7, v7, (int)(intptr_t)asc_507D2C, a2);
    Output_WriteFormatted(v10, v9, v9, (int)(intptr_t)aIncludeUtility, v64);
    Output_WriteFormatted(v12, v11, v11, (int)(intptr_t)aIncludeGenerat, v65);
    Output_WriteFormatted(v14, v13, v13, (int)(intptr_t)aIncludeExpress, v66);
    Output_WriteFormatted(v16, v15, v15, (int)(intptr_t)aIncludeExtnfun, v67);
    Output_WriteFormatted(v18, v17, v17, (int)(intptr_t)aIncludeObjrtmc, v68);
    Output_WriteFormatted(v20, v19, v19, (int)(intptr_t)aIncludeRulebld, v69);
    Output_WriteFormatted(g_ClipsCodeHeaderFile, v21, g_ClipsCodeHeaderFile, (int)(intptr_t)aIfAnsi_compile, v70);
    Output_WriteFormatted(v23, v22, g_ClipsCodeHeaderFile, (int)(intptr_t)aVoidInitcimage, g_ConstructsToCImageId);
    Output_WriteFormatted(v25, v24, g_ClipsCodeHeaderFile, (int)(intptr_t)aElse, v71);
    Output_WriteFormatted(g_ClipsCodeHeaderFile, v26, g_ClipsCodeHeaderFile, (int)(intptr_t)aVoidInitcima_0, g_ConstructsToCImageId);
    Output_WriteFormatted(v28, v27, g_ClipsCodeHeaderFile, (int)(intptr_t)aEndif_0, v72);
    Output_WriteFormatted(v30, v29, v29, (int)(intptr_t)asc_507D2C, v73);
    Output_WriteFormatted(v32, v31, v31, (int)(intptr_t)asc_508048, v74);
    Output_WriteFormatted(v34, v33, v33, (int)(intptr_t)aConstructImage, v75);
    Output_WriteFormatted(v36, v35, v35, (int)(intptr_t)asc_508048, v76);
    Output_WriteFormatted(v38, v37, v37, (int)(intptr_t)aVoidInitcima_1, g_ConstructsToCImageId);
    Output_WriteFormatted(v40, v39, v39, (int)(intptr_t)asc_5080C0, v77);
    Output_WriteFormatted(v42, v41, v41, (int)(intptr_t)aClear_0, v78);
    Output_WriteFormatted(v44, v43, v43, (int)(intptr_t)aPeriodiccleanu, v79);
    Output_WriteFormatted(v46, v45, v45, (int)(intptr_t)aSetsymboltable, g_ConstructsToCImageId);
    Output_WriteFormatted(v48, v47, v47, (int)(intptr_t)aSetfloattableF, g_ConstructsToCImageId);
    Output_WriteFormatted(g_ConstructsToCImageId, v49, v49, (int)(intptr_t)aSetintegertabl, g_ConstructsToCImageId);
    Output_WriteFormatted(v51, v50, v50, (int)(intptr_t)aSetbitmaptable, g_ConstructsToCImageId);
    Output_WriteFormatted(v53, v52, v52, (int)(intptr_t)aRefreshspecial, v80);
    Output_WriteFormatted(v55, v54, v54, (int)(intptr_t)aInstallfunctio, g_ConstructsToCImageId);
    Output_WriteFormatted(v57, v56, v56, (int)(intptr_t)aInitexpression, v81);
    for ( i = g_CodeGeneratorItemList; i; i = *(_DWORD *)(uintptr_t)(i + 24) )
    {
      if ( *(_DWORD *)(uintptr_t)(i + 8) )
      {
        (*(void (__fastcall **)(int, int))(uintptr_t)(i + 8))(i, g_ConstructsToCImageId);
        Output_WriteFormatted(v61, v60, fp, (int)(intptr_t)asc_507D2C, v82);
      }
    }
    Output_WriteFormatted(i, v58, fp, (int)(intptr_t)asc_5081DC, v82);
    fclose_(v62);
    return 1;
  }
  else
  {
    Rules_OpenFileErrorMessage(v5, (int)(intptr_t)fileNameBuffer);
    return 0;
  }
}
// 4A6EB0: could not find valid save-restore pair for ebx
// 4A6ED3: variable 'v3' is possibly undefined
// 4A6EED: variable 'v5' is possibly undefined
// 4A6EFB: variable 'v8' is possibly undefined
// 4A6EFB: variable 'v7' is possibly undefined
// 4A6F09: variable 'v10' is possibly undefined
// 4A6F09: variable 'v9' is possibly undefined
// 4A6F09: variable 'v64' is possibly undefined
// 4A6F17: variable 'v12' is possibly undefined
// 4A6F17: variable 'v11' is possibly undefined
// 4A6F17: variable 'v65' is possibly undefined
// 4A6F25: variable 'v14' is possibly undefined
// 4A6F25: variable 'v13' is possibly undefined
// 4A6F25: variable 'v66' is possibly undefined
// 4A6F33: variable 'v16' is possibly undefined
// 4A6F33: variable 'v15' is possibly undefined
// 4A6F33: variable 'v67' is possibly undefined
// 4A6F41: variable 'v18' is possibly undefined
// 4A6F41: variable 'v17' is possibly undefined
// 4A6F41: variable 'v68' is possibly undefined
// 4A6F4F: variable 'v20' is possibly undefined
// 4A6F4F: variable 'v19' is possibly undefined
// 4A6F4F: variable 'v69' is possibly undefined
// 4A6F63: variable 'v21' is possibly undefined
// 4A6F63: variable 'v70' is possibly undefined
// 4A6F7E: variable 'v23' is possibly undefined
// 4A6F7E: variable 'v22' is possibly undefined
// 4A6F92: variable 'v25' is possibly undefined
// 4A6F92: variable 'v24' is possibly undefined
// 4A6F92: variable 'v71' is possibly undefined
// 4A6FAC: variable 'v26' is possibly undefined
// 4A6FC0: variable 'v28' is possibly undefined
// 4A6FC0: variable 'v27' is possibly undefined
// 4A6FC0: variable 'v72' is possibly undefined
// 4A6FCE: variable 'v30' is possibly undefined
// 4A6FCE: variable 'v29' is possibly undefined
// 4A6FCE: variable 'v73' is possibly undefined
// 4A6FDC: variable 'v32' is possibly undefined
// 4A6FDC: variable 'v31' is possibly undefined
// 4A6FDC: variable 'v74' is possibly undefined
// 4A6FEA: variable 'v34' is possibly undefined
// 4A6FEA: variable 'v33' is possibly undefined
// 4A6FEA: variable 'v75' is possibly undefined
// 4A6FF8: variable 'v36' is possibly undefined
// 4A6FF8: variable 'v35' is possibly undefined
// 4A6FF8: variable 'v76' is possibly undefined
// 4A700D: variable 'v38' is possibly undefined
// 4A700D: variable 'v37' is possibly undefined
// 4A701B: variable 'v40' is possibly undefined
// 4A701B: variable 'v39' is possibly undefined
// 4A701B: variable 'v77' is possibly undefined
// 4A7029: variable 'v42' is possibly undefined
// 4A7029: variable 'v41' is possibly undefined
// 4A7029: variable 'v78' is possibly undefined
// 4A7037: variable 'v44' is possibly undefined
// 4A7037: variable 'v43' is possibly undefined
// 4A7037: variable 'v79' is possibly undefined
// 4A704C: variable 'v46' is possibly undefined
// 4A704C: variable 'v45' is possibly undefined
// 4A7060: variable 'v48' is possibly undefined
// 4A7060: variable 'v47' is possibly undefined
// 4A7075: variable 'v49' is possibly undefined
// 4A708A: variable 'v51' is possibly undefined
// 4A708A: variable 'v50' is possibly undefined
// 4A7098: variable 'v53' is possibly undefined
// 4A7098: variable 'v52' is possibly undefined
// 4A7098: variable 'v80' is possibly undefined
// 4A70AD: variable 'v55' is possibly undefined
// 4A70AD: variable 'v54' is possibly undefined
// 4A70BB: variable 'v57' is possibly undefined
// 4A70BB: variable 'v56' is possibly undefined
// 4A70BB: variable 'v81' is possibly undefined
// 4A70EA: variable 'v61' is possibly undefined
// 4A70EA: variable 'v60' is possibly undefined
// 4A70EA: variable 'v82' is possibly undefined
// 4A70F2: variable 'i' is possibly undefined
// 4A70FF: variable 'v58' is possibly undefined
// 4A7109: variable 'v62' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51ACF0: using guessed type int dword_51ACF0;
// 51ACF4: using guessed type int dword_51ACF4;
// 54E6D0: using guessed type int dword_54E6D0;
// 54E6E8: using guessed type int dword_54E6E8;

//----- (004A7140) --------------------------------------------------------
int  Rules_OpenConstructCodeFile(const char *fileName, int fileID, int version, DWORD reopenOldFile)
{
  char v4; // si
  int v5; // ecx
  char *fileMode; // edx
  int v7; // eax
  int v8; // ecx
  int fp; // ebx
  int v10; // edx
  int v11; // ecx
  CHAR fileNameBuffer[84]; // [esp+0h] [ebp-54h] BYREF

  v4 = (char)(intptr_t)fileName;
  sprintf_(fileNameBuffer, "%s%d_%d.c", fileName, fileID, version);
  if ( v5 )
    fileMode = aA_0;
  else
    fileMode = aW_2;
  v7 = IO_FOpen(fileNameBuffer, (unsigned __int8 *)fileMode, v5, reopenOldFile);
  fp = v7;
  if ( v7 )
  {
    if ( !v8 )
    {
      Output_WriteFormatted(0, v7, v7, (int)(intptr_t)aIncludeS_h, v4);
      Output_WriteFormatted(v11, v10, v10, (int)(intptr_t)asc_507D2C, fileNameBuffer[0]);
    }
    return fp;
  }
  else
  {
    Rules_OpenFileErrorMessage(v8, (int)(intptr_t)fileNameBuffer);
    return 0;
  }
}
// 4A715D: variable 'v5' is possibly undefined
// 4A7175: variable 'v8' is possibly undefined
// 4A718C: variable 'v11' is possibly undefined
// 4A718C: variable 'v10' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (004A71C0) --------------------------------------------------------
signed int  Rules_WriteHashedExpressionsToCode(DWORD reopenOldFile)
{
  int i; // ebx
  signed int result; // eax
  int j; // ecx
  __int16 *exprPtr; // edx
  int v5; // ecx

  for ( i = 0; i != 2012; i += 4 )
  {
    result = g_ExpressionHashTable;
    for ( j = *(_DWORD *)(uintptr_t)(i + g_ExpressionHashTable); j; j = *(_DWORD *)(uintptr_t)(j + 12) )
    {
      exprPtr = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(j + 8);
      *(_DWORD *)(uintptr_t)(j + 16) = g_ClipsCodeMaxIndicesPerArray * g_ClipsExpressionCodeFileVersion + g_ClipsConstructCodeEntryIndexInFile;
      result = Rules_ExpressionToCode(0, exprPtr, j, reopenOldFile);
    }
  }
  return result;
}
// 4A71FE: variable 'v5' is possibly undefined
// 51A9FC: using guessed type int dword_51A9FC;
// 51ACF0: using guessed type int dword_51ACF0;
// 54E6D8: using guessed type int dword_54E6D8;
// 54E6DC: using guessed type int dword_54E6DC;

//----- (004A7220) --------------------------------------------------------
int  Rules_WriteExpressionRefToCode(int theFile, __int16 *theExpression, int maxIndices, char imageID)
{
  signed int exprID; // eax
  char v9; // [esp+0h] [ebp-8h]

  if ( !theExpression )
    return Output_WriteFormatted(maxIndices, 0, theFile, (int)(intptr_t)aNull_1, v9);
  exprID = AST_GetHashedNodeIndex(theExpression);
  return Output_WriteFormatted(exprID, exprID % maxIndices, theFile, (int)(intptr_t)aED_LdLd, imageID);
}
// 4A7234: variable 'v9' is possibly undefined

//----- (004A7270) --------------------------------------------------------
signed int  Rules_ExpressionToCode(int theFile, __int16 *theExpression, int a3, DWORD reopenOldFile)
{
  int v6; // ecx
  int v7; // edx
  int v8; // ecx
  int v9; // ecx
  int dataFile; // eax
  int v11; // edx
  int v12; // ecx
  char v13; // [esp+0h] [ebp-10h]

  if ( theExpression )
  {
    if ( theFile )
      Output_WriteFormatted(g_ClipsExpressionCodeFileVersion, g_ClipsConstructCodeEntryIndexInFile, theFile, (int)(intptr_t)aED_DLd, g_ConstructsToCImageId);
    if ( g_Rules_ExprCodeNeedNewFileFlag == 1 )
    {
      dataFile = Rules_OpenConstructCodeFile((const char *)(uintptr_t)g_Rules_ConstructsToCodeBaseName, 3, g_ClipsExpressionCodeFileVersion, reopenOldFile);
      g_ClipsCodeDataFile = dataFile;
      if ( !dataFile )
        return -1;
      Output_WriteFormatted(g_ConstructsToCImageId, g_ClipsExpressionCodeFileVersion, dataFile, (int)(intptr_t)aStructExprED_D, g_ConstructsToCImageId);
      Output_WriteFormatted(v12, v11, g_ClipsCodeHeaderFile, (int)(intptr_t)aExternStructEx, g_ConstructsToCImageId);
      g_Rules_ExprCodeNeedNewFileFlag = 0;
    }
    else
    {
      Output_WriteFormatted(a3, (int)(intptr_t)theExpression, g_ClipsCodeDataFile, (int)(intptr_t)asc_508250, v13);
    }
    Rules_WriteExpressionNodeToCode(theExpression, v6);
    if ( g_ClipsConstructCodeEntryIndexInFile >= g_ClipsCodeMaxIndicesPerArray )
    {
      g_ClipsConstructCodeEntryIndexInFile = 0;
      ++g_ClipsExpressionCodeFileVersion;
      Output_WriteFormatted(0, v7, g_ClipsCodeDataFile, (int)(intptr_t)asc_507DA0, v13);
      fclose_(v8);
      g_ClipsCodeDataFile = v9;
      g_Rules_ExprCodeNeedNewFileFlag = 1;
    }
    return 1;
  }
  else
  {
    if ( theFile )
      Output_WriteFormatted(a3, 0, theFile, (int)(intptr_t)aNull_1, v13);
    return 0;
  }
}
// 4A7284: variable 'v13' is possibly undefined
// 4A72CF: variable 'a3' is possibly undefined
// 4A72CF: variable 'a2' is possibly undefined
// 4A72D9: variable 'v6' is possibly undefined
// 4A730C: variable 'v7' is possibly undefined
// 4A731E: variable 'v8' is possibly undefined
// 4A7323: variable 'v9' is possibly undefined
// 4A739A: variable 'v12' is possibly undefined
// 4A739A: variable 'v11' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51ACF0: using guessed type int dword_51ACF0;
// 54E6D0: using guessed type int dword_54E6D0;
// 54E6D4: using guessed type int dword_54E6D4;
// 54E6D8: using guessed type int dword_54E6D8;
// 54E6DC: using guessed type int dword_54E6DC;
// 54E6E0: using guessed type int dword_54E6E0;
// 54E6E4: using guessed type int dword_54E6E4;
// 54E6E8: using guessed type int dword_54E6E8;

//----- (004A73B0) --------------------------------------------------------
__int16 * Rules_WriteExpressionNodeToCode(__int16 *result, int a2)
{
  __int16 *exprNode; // esi
  int v3; // edx
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  unsigned __int16 nodeType; // ax
  int v9; // edx
  int v10; // ecx
  int v11; // edx
  int v12; // ecx
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int primitiveEntity; // edx
  int v19; // edx
  char v20; // [esp+0h] [ebp-18h]
  char v21; // [esp+0h] [ebp-18h]
  char v22; // [esp+0h] [ebp-18h]
  char v23; // [esp+0h] [ebp-18h]

  exprNode = result;
  if ( result )
  {
    while ( 1 )
    {
      Output_WriteFormatted(a2, g_ClipsCodeDataFile, g_ClipsCodeDataFile, (int)(intptr_t)asc_507F14, v20);
      Output_WriteFormatted(g_ClipsCodeDataFile, v3, g_ClipsCodeDataFile, (int)(intptr_t)aD_37, *exprNode);
      Output_WriteFormatted(v5, v4, g_ClipsCodeDataFile, (int)(intptr_t)aVs, v21);
      nodeType = *exprNode;
      if ( (unsigned __int16)*exprNode >= 0xAu )
      {
        if ( (unsigned __int16)*exprNode <= 0xAu )
        {
          Rules_WriteFunctionRecordRefToCode(g_ClipsCodeDataFile, *(_DWORD *)(exprNode + 1), v7);
        }
        else if ( nodeType >= 0x23u )
        {
          if ( nodeType <= 0x23u )
          {
            Rules_DeftemplateWriteRecordRefToCode(g_ClipsCodeDataFile, *(_DWORD *)(exprNode + 1), g_ClipsCodeMaxIndicesPerArray);
          }
          else if ( nodeType >= 0x3Cu )
          {
            if ( nodeType <= 0x3Cu )
            {
              Defglobal_WriteDefglobalArrayReference(g_ClipsCodeDataFile, *(_DWORD *)(exprNode + 1), g_ClipsCodeMaxIndicesPerArray);
            }
            else
            {
              if ( nodeType != 105 )
                goto LABEL_20;
              Output_WriteFormatted(v7, v6, g_ClipsCodeDataFile, (int)(intptr_t)aNull_1, v22);
            }
          }
          else
          {
            if ( nodeType != 57 )
              goto LABEL_20;
            ObjectsCompiler_WriteDefclassPointerRef(g_ClipsCodeDataFile, *(_DWORD *)(exprNode + 1), g_ClipsCodeMaxIndicesPerArray);
          }
        }
        else if ( nodeType < 0xCu )
        {
          Defgeneric_PrintModuleIndexOrNull(g_ClipsCodeDataFile, *(_DWORD *)(exprNode + 1), g_ClipsCodeMaxIndicesPerArray);
        }
        else
        {
          if ( nodeType > 0xCu )
          {
            if ( nodeType != 13 )
              goto LABEL_20;
LABEL_36:
            Compiler_WriteSymbolReference(g_ClipsCodeDataFile, *(_DWORD *)(exprNode + 1), v7);
            goto LABEL_6;
          }
          Deffunction_WriteConstructReference(g_ClipsCodeDataFile, *(_DWORD *)(exprNode + 1), g_ClipsCodeMaxIndicesPerArray);
        }
      }
      else if ( nodeType >= 3u )
      {
        if ( nodeType <= 3u )
          goto LABEL_36;
        if ( nodeType >= 7u )
        {
          if ( nodeType > 7u )
          {
            if ( nodeType != 8 )
            {
LABEL_20:
              primitiveEntity = g_Clips_PrimitiveEntityTable[*exprNode];
              if ( primitiveEntity )
              {
                if ( (*(_BYTE *)(uintptr_t)(primitiveEntity + 1) & 0x40) != 0 )
                  Compiler_WriteBitMapReference(g_ClipsCodeDataFile, *(_DWORD *)(exprNode + 1), v7);
                else
                  Output_WriteFormatted(g_ClipsCodeDataFile, primitiveEntity, g_ClipsCodeDataFile, (int)(intptr_t)aNull_1, v22);
              }
              else
              {
                Output_WriteFormatted(v7, 0, g_ClipsCodeDataFile, (int)(intptr_t)aNull_1, v22);
              }
              goto LABEL_6;
            }
            goto LABEL_36;
          }
          Output_WriteFormatted(v7, v6, g_ClipsCodeDataFile, (int)(intptr_t)aDummyinstance, v22);
        }
        else
        {
          if ( nodeType != 6 )
            goto LABEL_20;
          Output_WriteFormatted(v7, v6, g_ClipsCodeDataFile, (int)(intptr_t)aDummyfact, v22);
        }
      }
      else
      {
        if ( !nodeType )
        {
          Compiler_WriteFloatReference(g_ClipsCodeDataFile, *(_DWORD *)(exprNode + 1));
          goto LABEL_6;
        }
        if ( nodeType > 1u )
          goto LABEL_36;
        Compiler_WriteIntegerReference(g_ClipsCodeDataFile, *(_DWORD *)(exprNode + 1));
      }
LABEL_6:
      Output_WriteFormatted(v10, v9, g_ClipsCodeDataFile, (int)(intptr_t)asc_508278, v22);
      ++g_ClipsConstructCodeEntryIndexInFile;
      if ( *(_DWORD *)(exprNode + 3) )
        Output_WriteFormatted(g_ClipsExpressionCodeFileVersion, v11, g_ClipsCodeDataFile, (int)(intptr_t)aED_DLd_0, g_ConstructsToCImageId);
      else
        Output_WriteFormatted(v12, v11, g_ClipsCodeDataFile, (int)(intptr_t)aNull_0, v23);
      if ( *(_DWORD *)(exprNode + 5) )
      {
        AST_CountTreeNodes(*(_DWORD *)(exprNode + 3));
        result = (__int16 *)(uintptr_t)Output_WriteFormatted(g_ClipsExpressionCodeFileVersion, v19, g_ClipsCodeDataFile, (int)(intptr_t)aED_DLd_1, g_ConstructsToCImageId);
      }
      else
      {
        result = (__int16 *)(uintptr_t)Output_WriteFormatted(v14, v13, g_ClipsCodeDataFile, (int)(intptr_t)aNull_2, v23);
      }
      if ( *(_DWORD *)(exprNode + 3) )
      {
        Output_WriteFormatted(v16, g_ClipsCodeDataFile, g_ClipsCodeDataFile, (int)(intptr_t)asc_508250, v23);
        result = (__int16 *)Rules_WriteExpressionNodeToCode(*(_DWORD *)(exprNode + 3), v17);
      }
      exprNode = *(__int16 **)(exprNode + 5);
      if ( !exprNode )
        return result;
      Output_WriteFormatted(g_ClipsCodeDataFile, v15, g_ClipsCodeDataFile, (int)(intptr_t)asc_508250, v23);
    }
  }
  return result;
}
// 4A73CC: variable 'a2' is possibly undefined
// 4A73CC: variable 'v20' is possibly undefined
// 4A73E4: variable 'v3' is possibly undefined
// 4A73F8: variable 'v5' is possibly undefined
// 4A73F8: variable 'v4' is possibly undefined
// 4A73F8: variable 'v21' is possibly undefined
// 4A7443: variable 'v10' is possibly undefined
// 4A7443: variable 'v9' is possibly undefined
// 4A7443: variable 'v22' is possibly undefined
// 4A746F: variable 'v12' is possibly undefined
// 4A746F: variable 'v11' is possibly undefined
// 4A746F: variable 'v23' is possibly undefined
// 4A748D: variable 'v14' is possibly undefined
// 4A748D: variable 'v13' is possibly undefined
// 4A74A7: variable 'v16' is possibly undefined
// 4A74B2: variable 'v17' is possibly undefined
// 4A74CA: variable 'v15' is possibly undefined
// 4A7531: variable 'v7' is possibly undefined
// 4A7583: variable 'v6' is possibly undefined
// 4A7716: variable 'v19' is possibly undefined
// 51ACF0: using guessed type int dword_51ACF0;
// 54E530: using guessed type int dword_54E530[70];
// 54E6D0: using guessed type int dword_54E6D0;
// 54E6D4: using guessed type int dword_54E6D4;
// 54E6D8: using guessed type int dword_54E6D8;
// 54E6DC: using guessed type int dword_54E6DC;

//----- (004A7730) --------------------------------------------------------
signed int Rules_RegisterConstructsToCFunction(void)
{
  return Rules_RegisterHostFunction(aConstructsToC, 118, (int)(intptr_t)aConstructstocc, (int)(intptr_t)Rules_ConstructsToCCommand, (int)(intptr_t)a23Kii);
}

//----- (004A7760) --------------------------------------------------------
int  Rules_AddCodeGeneratorItem(int itemName, int priority, int initFunction, int beforeFunction, int generateFunction, int arrayCount)
{
  int construct_code_count; // ecx
  _DWORD *freeNode; // ebx
  int prevItem; // ebp
  _DWORD *newItem; // eax
  int newItemPtr; // ebx
  int arrayBytes; // edi
  _DWORD *nameCopy; // eax
  int slot_offset; // edx
  char *copySrc; // esi
  char *copyDst; // edi
  int nextOffset; // edx
  char v20; // al
  char v21; // al
  int listCursor; // eax
  int result; // eax
  int totalArrayBytes; // [esp+4h] [ebp-18h]
  char prefixBuffer[16]; // [esp+Ch] [ebp-10h] BYREF

  construct_code_count = arrayCount;
  freeNode = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 112);
  prevItem = 0;
  if ( freeNode )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 112);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 112) = *freeNode;
    newItem = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
  }
  else
  {
    newItem = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x1C);
  }
  *newItem = itemName;
  newItem[2] = initFunction;
  newItem[1] = beforeFunction;
  newItem[3] = generateFunction;
  newItemPtr = (int)(intptr_t)newItem;
  newItem[4] = priority;
  if ( construct_code_count )
  {
    if ( construct_code_count + g_Rules_CodeGeneratorItemIndex > 44 )
    {
      Rules_ReportSystemError((int)(intptr_t)aConscomp, 2);
      IO_RunRouterExitCallbacks();
    }
    arrayBytes = 4 * construct_code_count;
    *(_DWORD *)(uintptr_t)(newItemPtr + 20) = Mem_SmallBlockAlloc(4 * construct_code_count);
    if ( construct_code_count > 0 )
    {
      totalArrayBytes = arrayBytes;
      slot_offset = 0;
      do
      {
        if ( g_Rules_CodeGeneratorItemIndex >= 18 )
          sprintf_(prefixBuffer, "%c_", (unsigned __int8)g_Rules_CodeGeneratorItemPrefixTable[g_Rules_CodeGeneratorItemIndex]);
        else
          sprintf_(prefixBuffer, "%c", (unsigned __int8)g_Rules_CodeGeneratorItemLetterTable[g_Rules_CodeGeneratorItemIndex]);
        ++g_Rules_CodeGeneratorItemIndex;
        nameCopy = Mem_SmallBlockAlloc(strlen(prefixBuffer) + 1);
        *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(newItemPtr + 20) + slot_offset) = nameCopy;
        copySrc = prefixBuffer;
        copyDst = (char *)nameCopy;
        nextOffset = slot_offset + 4;
        do
        {
          v20 = *copySrc;
          *copyDst = *copySrc;
          if ( !v20 )
            break;
          v21 = copySrc[1];
          copySrc += 2;
          copyDst[1] = v21;
          copyDst += 2;
        }
        while ( v21 );
        slot_offset = nextOffset;
      }
      while ( nextOffset < totalArrayBytes );
    }
  }
  else
  {
    newItem[5] = 0;
  }
  if ( g_CodeGeneratorItemList )
  {
    listCursor = g_CodeGeneratorItemList;
    do
    {
      if ( priority >= *(_DWORD *)(uintptr_t)(listCursor + 16) )
        break;
      prevItem = listCursor;
      listCursor = *(_DWORD *)(uintptr_t)(listCursor + 24);
    }
    while ( listCursor );
    if ( prevItem )
    {
      *(_DWORD *)(uintptr_t)(newItemPtr + 24) = listCursor;
      *(_DWORD *)(uintptr_t)(prevItem + 24) = newItemPtr;
    }
    else
    {
      *(_DWORD *)(uintptr_t)(newItemPtr + 24) = g_CodeGeneratorItemList;
      g_CodeGeneratorItemList = newItemPtr;
    }
    return newItemPtr;
  }
  else
  {
    *(_DWORD *)(uintptr_t)(newItemPtr + 24) = 0;
    result = newItemPtr;
    g_CodeGeneratorItemList = newItemPtr;
  }
  return result;
}
// 4A77B4: variable 'v8' is possibly undefined
// 4A77F2: variable 'v14' is possibly undefined
// 4A7850: variable 'v16' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51ACF4: using guessed type int dword_51ACF4;
// 51ACF8: using guessed type int dword_51ACF8;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004A7920) --------------------------------------------------------
int  Rules_ConstructCodeFileClose(int result, int *theCount, int maxIndices, _DWORD *arrayVersion, _DWORD *canBeReopened, int codeFile)
{
  int curFile; // esi
  int v8; // edx
  int codeFileInfo; // ecx
  int v10; // ecx
  char v11; // [esp+0h] [ebp-Ch]

  curFile = result;
  v8 = maxIndices;
  codeFileInfo = codeFile;
  if ( v8 > *theCount )
  {
    if ( !canBeReopened )
      return result;
    *canBeReopened = 1;
    fclose_(codeFile);
    return 0;
  }
  if ( canBeReopened )
    *canBeReopened = 0;
  if ( !result )
  {
    if ( !canBeReopened || !codeFile )
    {
      Rules_ReportSystemError(codeFile, 3);
      IO_RunRouterExitCallbacks();
    }
    if ( !*(_DWORD *)(uintptr_t)codeFileInfo )
      return 0;
    curFile = Rules_OpenConstructCodeFile((const char *)(uintptr_t)*(_DWORD *)(uintptr_t)codeFileInfo, *(_DWORD *)(uintptr_t)(codeFileInfo + 4), *(_DWORD *)(uintptr_t)(codeFileInfo + 8), (DWORD)(intptr_t)arrayVersion);
    if ( !curFile )
    {
      Rules_ReportSystemError(codeFileInfo, 4);
      IO_RunRouterExitCallbacks();
    }
  }
  Output_WriteFormatted(codeFileInfo, v8, curFile, (int)(intptr_t)asc_507DA0, v11);
  fclose_(v10);
  *theCount = 0;
  result = 0;
  ++*arrayVersion;
  return result;
}
// 4A7983: variable 'v9' is possibly undefined
// 4A79C0: variable 'v8' is possibly undefined
// 4A79C0: variable 'v11' is possibly undefined
// 4A79CA: variable 'v10' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);

//----- (004A79F0) --------------------------------------------------------
int  Rules_ConstructCodeFileOpen(
        int theFile,
        const char *fileName,
        int imageID,
        const char *fileID,
        int *fileCount,
        int arrayVersion,
        int headerFP,
        char structureName,
        const char *structPrefix,
        int reopenOldFile,
        const char **codeFile)
{
  const char **codeFileInfo; // ecx
  const char *curFileName; // edi
  int curFileID; // edx
  int curVersion; // eax
  int result; // eax
  int v18; // edx
  int v19; // ecx
  int v20; // edx
  int v21; // ecx
  int v22; // edx
  int v23; // edx
  int v24; // [esp-8h] [ebp-68h]
  char arrayNameBuffer[80]; // [esp+0h] [ebp-60h] BYREF
  int savedImageID; // [esp+50h] [ebp-10h]

  savedImageID = imageID;
  codeFileInfo = codeFile;
  if ( reopenOldFile )
  {
    if ( !codeFile )
    {
      Rules_ReportSystemError(0, 5);
      IO_RunRouterExitCallbacks();
    }
    curFileName = *codeFileInfo;
    curFileID = (int)(intptr_t)codeFileInfo[1];
    curVersion = (int)(intptr_t)codeFileInfo[2];
  }
  else
  {
    curFileName = fileName;
    curFileID = (int)(intptr_t)fileID;
    curVersion = *fileCount;
    if ( codeFile )
    {
      codeFile[2] = (const char *)(uintptr_t)curVersion;
      *codeFile = fileName;
      codeFile[1] = fileID;
    }
  }
  if ( theFile )
  {
    Output_WriteFormatted((int)(intptr_t)codeFileInfo, curFileID, theFile, (int)(intptr_t)asc_508250, arrayNameBuffer[0]);
    return theFile;
  }
  else
  {
    result = Rules_OpenConstructCodeFile(curFileName, curFileID, curVersion, (DWORD)(intptr_t)fileName);
    if ( result )
    {
      if ( reopenOldFile )
      {
        Output_WriteFormatted(result, result, result, (int)(intptr_t)asc_508250, arrayNameBuffer[0]);
        return v23;
      }
      else
      {
        v24 = savedImageID;
        ++*fileCount;
        sprintf_(arrayNameBuffer, "%s%d_%d", structPrefix, v24, arrayVersion);
        Output_WriteFormatted(v19, v18, v19, (int)(intptr_t)aSS_0, structureName);
        Output_WriteFormatted(v21, v20, headerFP, (int)(intptr_t)aExternSS, structureName);
        return v22;
      }
    }
  }
  return result;
}
// 4A7A2A: variable 'v13' is possibly undefined
// 4A7A8F: variable 'v19' is possibly undefined
// 4A7A8F: variable 'v18' is possibly undefined
// 4A7AA5: variable 'v21' is possibly undefined
// 4A7AA5: variable 'v20' is possibly undefined
// 4A7AAD: variable 'v22' is possibly undefined
// 4A7AFE: variable 'v23' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (004A7B10) --------------------------------------------------------
signed int Rules_RegisterModuleItemIdAssigner(void)
{
  return Rules_DoForAllConstructs((void (*)(void))Rules_AssignNextModuleItemId, 0);
}

//----- (004A7B40) --------------------------------------------------------
int  Rules_AssignNextModuleItemId(int theConstruct, _DWORD *countBuffer)
{
  int result; // eax

  result = (*countBuffer)++;
  *(_DWORD *)(uintptr_t)(theConstruct + 12) = result;
  return result;
}

//----- (004A7B60) --------------------------------------------------------
int  Rules_WriteConstructHeaderToCode(int theFile, int theConstruct, signed int maxIndices, int a4, int imageID, char constructPrefix)
{
  int *v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  int nextConstruct; // ecx
  char v18; // [esp+0h] [ebp-Ch]
  char v19; // [esp+0h] [ebp-Ch]
  char v20; // [esp+0h] [ebp-Ch]
  char v21; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(a4, theConstruct, theFile, (int)(intptr_t)asc_507F14, v18);
  Compiler_WriteSymbolReference(theFile, *v9, v10);
  Output_WriteFormatted(v11, v11, theFile, (int)(intptr_t)aNull_17, v19);
  Output_WriteFormatted(v12, imageID, theFile, (int)(intptr_t)aMihsSD_DD_2, imageID);
  Output_WriteFormatted(v14, v13, theFile, (int)(intptr_t)a0_1, v20);
  nextConstruct = *(_DWORD *)(uintptr_t)(theConstruct + 16);
  if ( nextConstruct )
    return Output_WriteFormatted(nextConstruct, *(_DWORD *)(uintptr_t)(nextConstruct + 12) % maxIndices, theFile, (int)(intptr_t)aChsSD_LdLd, constructPrefix);
  else
    return Output_WriteFormatted(0, v15, theFile, (int)(intptr_t)aNull_2, v21);
}
// 4A7B75: variable 'v18' is possibly undefined
// 4A7B7F: variable 'v9' is possibly undefined
// 4A7B81: variable 'v10' is possibly undefined
// 4A7B8E: variable 'v11' is possibly undefined
// 4A7B8E: variable 'v19' is possibly undefined
// 4A7BB5: variable 'v12' is possibly undefined
// 4A7BC3: variable 'v14' is possibly undefined
// 4A7BC3: variable 'v13' is possibly undefined
// 4A7BC3: variable 'v20' is possibly undefined
// 4A7BD8: variable 'v15' is possibly undefined
// 4A7BD8: variable 'v21' is possibly undefined

//----- (004A7C20) --------------------------------------------------------
int  Rules_WriteConstructModuleItemHeaderToCode(int theFile, int theModule, int a3, int a4, char constructPrefix)
{
  int v7; // edx
  int theModuleItem; // ebx
  int v9; // edx
  int v10; // ecx
  int v11; // ecx
  int firstItem; // edx
  int v13; // edx
  int v14; // ecx
  int lastItem; // edi
  int v16; // edx
  int v17; // ecx
  char v19; // [esp+0h] [ebp-10h]
  int v20; // [esp+0h] [ebp-10h]

  Output_WriteFormatted(a3, a4, theFile, (int)(intptr_t)asc_507F14, v19);
  theModuleItem = Module_GetItem(theModule, v7);
  Compiler_WriteModuleReference(theFile, theModule);
  Output_WriteFormatted(v10, v9, theFile, (int)(intptr_t)asc_508278, theModuleItem);
  firstItem = *(_DWORD *)(uintptr_t)(theModuleItem + 4);
  if ( firstItem )
    Output_WriteFormatted(v11, *(_DWORD *)(uintptr_t)(firstItem + 12) % v11, theFile, (int)(intptr_t)aChsSD_LdLd_0, constructPrefix);
  else
    Output_WriteFormatted(v11, 0, theFile, (int)(intptr_t)aNull_0, v20);
  lastItem = *(_DWORD *)(uintptr_t)(v20 + 8);
  if ( lastItem )
    Output_WriteFormatted(v14, *(_DWORD *)(uintptr_t)(lastItem + 12) % v14, theFile, (int)(intptr_t)aChsSD_LdLd_1, constructPrefix);
  else
    Output_WriteFormatted(v14, v13, theFile, (int)(intptr_t)aNull_1, v20);
  return Output_WriteFormatted(v17, v16, theFile, (int)(intptr_t)asc_508384, v20);
}
// 4A7C36: variable 'v19' is possibly undefined
// 4A7C40: variable 'v7' is possibly undefined
// 4A7C59: variable 'v10' is possibly undefined
// 4A7C59: variable 'v9' is possibly undefined
// 4A7C8D: variable 'v11' is possibly undefined
// 4A7C98: variable 'v20' is possibly undefined
// 4A7CA5: variable 'v14' is possibly undefined
// 4A7CA5: variable 'v13' is possibly undefined
// 4A7CB3: variable 'v17' is possibly undefined
// 4A7CB3: variable 'v16' is possibly undefined

//----- (004A7DA3) --------------------------------------------------------
int  IO_RenameFile(const CHAR *oldFileName, const CHAR *newFileName, int a3)
{
  if ( MoveFileA(oldFileName, newFileName) )
    return 0;
  else
    return _set_errno_nt_(a3);
}
// 485357: using guessed type int __cdecl _set_errno_nt_(_DWORD);

//----- (004A7DC0) --------------------------------------------------------
signed int  Rules_PrintArgumentValueList(int logicalName, _DWORD *theSegment)
{
  int logicalNameCopy; // ecx
  __int16 fieldIndex; // bx
  signed int result; // eax
  int fieldValue; // edi

  logicalNameCopy = logicalName;
  fieldIndex = 0;
  while ( 1 )
  {
    result = *theSegment << 17 >> 23;
    if ( fieldIndex >= result )
      break;
    fieldValue = *(_DWORD *)(uintptr_t)theSegment[fieldIndex + 2];
    if ( fieldValue )
      (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)fieldValue + 4))();
    if ( ++fieldIndex < *theSegment << 17 >> 23 )
      Output_Write(logicalNameCopy, (int)(intptr_t)asc_5083B0, logicalNameCopy);
  }
  return result;
}
// 4A7E05: variable 'v2' is possibly undefined

//----- (004A7E20) --------------------------------------------------------
_DWORD * Rules_MultifieldCopyWithMarkers(int *srcSegment, int a2, int a3)
{
  int totalFields; // eax
  signed int newSegmentPtr; // eax
  char v6; // dl
  __int16 v7; // cx
  int v8; // edx
  _DWORD *newSegment; // ebx
  __int16 i; // ax
  int fieldIndex; // ecx
  _DWORD *fieldPtr; // esi

  totalFields = a3 + a2 + ((unsigned int)(*srcSegment << 17) >> 23);
  if ( (unsigned int)(4 * totalFields + 8) < 0x1F4 && *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 16 * totalFields + 32) )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(16 * (a3 + a2 + ((unsigned int)(*srcSegment << 17) >> 23)) + g_ClipsMemoryTable + 32);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 16 * (a3 + a2 + ((unsigned int)(*srcSegment << 17) >> 23)) + 32) = *(_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
    newSegmentPtr = g_ClipsMemFreeListTemp;
  }
  else
  {
    newSegmentPtr = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(4 * (a3 + a2 + ((unsigned int)(*srcSegment << 17) >> 23)) + 8));
  }
  v6 = *(_BYTE *)(uintptr_t)newSegmentPtr | 1;
  *(_BYTE *)(uintptr_t)newSegmentPtr = v6;
  *(_BYTE *)(uintptr_t)newSegmentPtr = v6 & 0xF9;
  *(_DWORD *)(uintptr_t)newSegmentPtr |= 4 * (a2 & 1);
  *(_BYTE *)(uintptr_t)newSegmentPtr &= ~8u;
  *(_DWORD *)(uintptr_t)newSegmentPtr |= 8 * (a3 & 1);
  *(_BYTE *)(uintptr_t)newSegmentPtr &= 0xCFu;
  v7 = *(_WORD *)(uintptr_t)newSegmentPtr;
  *(_DWORD *)(uintptr_t)(newSegmentPtr + 4) = 0;
  v8 = *srcSegment;
  *(_WORD *)(uintptr_t)newSegmentPtr = v7 & 0x803F;
  newSegment = (_DWORD *)(uintptr_t)newSegmentPtr;
  *(_DWORD *)(uintptr_t)newSegmentPtr |= v8 & 0x7FC0;
  for ( i = 0; ; ++i )
  {
    fieldIndex = i;
    fieldPtr = &newSegment[fieldIndex];
    if ( i >= *newSegment << 17 >> 23 )
      break;
    fieldPtr[2] = srcSegment[fieldIndex + 2];
  }
  if ( a2 )
  {
    ++i;
    fieldPtr[2] = 0;
  }
  if ( a3 )
    newSegment[i + 2] = 0;
  return newSegment;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004A7F90) --------------------------------------------------------
_WORD * Rules_MergeMultifieldValues(_DWORD *firstSegment, _DWORD *secondSegment, int a3, int a4)
{
  int totalFields; // eax
  signed int newSegmentPtr; // eax
  char v8; // bl
  char v9; // bh
  int combinedLength; // ecx
  _WORD *newSegment; // edx
  __int16 i; // ax
  int srcOffset; // ebx
  int writeIndex; // eax
  int j; // ebx
  _WORD *writePtr; // esi
  int fieldValue; // ecx

  totalFields = a3 + a4 + (*firstSegment << 17 >> 23) + (*secondSegment << 17 >> 23);
  if ( (unsigned int)(4 * totalFields + 8) < 0x1F4 && *(_DWORD *)(uintptr_t)(16 * totalFields + g_ClipsMemoryTable + 32) )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(16 * (a3 + a4 + (*firstSegment << 17 >> 23) + (*secondSegment << 17 >> 23)) + g_ClipsMemoryTable + 32);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 16 * (a3 + a4 + (*firstSegment << 17 >> 23) + (*secondSegment << 17 >> 23)) + 32) = *(_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
    newSegmentPtr = g_ClipsMemFreeListTemp;
  }
  else
  {
    newSegmentPtr = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(4 * (a3 + a4 + (*firstSegment << 17 >> 23) + (*secondSegment << 17 >> 23)) + 8));
  }
  v8 = *(_BYTE *)(uintptr_t)newSegmentPtr | 1;
  *(_BYTE *)(uintptr_t)newSegmentPtr = v8;
  *(_BYTE *)(uintptr_t)newSegmentPtr = v8 & 0xF9;
  *(_DWORD *)(uintptr_t)newSegmentPtr |= 4 * (a4 & 1);
  *(_BYTE *)(uintptr_t)newSegmentPtr &= ~8u;
  *(_DWORD *)(uintptr_t)newSegmentPtr |= 8 * (a3 & 1);
  v9 = *(_BYTE *)(uintptr_t)newSegmentPtr;
  *(_DWORD *)(uintptr_t)(newSegmentPtr + 4) = 0;
  *(_BYTE *)(uintptr_t)newSegmentPtr = v9 & 0xCF;
  combinedLength = (((unsigned __int16)(2 * *(_WORD *)firstSegment) >> 7) + ((unsigned __int16)(2 * *(_WORD *)secondSegment) >> 7)) & 0x1FF;
  *(_WORD *)(uintptr_t)newSegmentPtr &= 0x803Fu;
  newSegment = (_WORD *)(uintptr_t)newSegmentPtr;
  *(_DWORD *)(uintptr_t)newSegmentPtr |= combinedLength << 6;
  for ( i = 0; i < *firstSegment << 17 >> 23; ++i )
  {
    srcOffset = 4 * i;
    *(_DWORD *)&newSegment[srcOffset / 2u + 4] = firstSegment[srcOffset / 4u + 2];
  }
  writeIndex = *firstSegment << 17 >> 23;
  for ( j = 0; ; ++j )
  {
    writePtr = &newSegment[2 * (__int16)writeIndex];
    if ( (__int16)writeIndex >= (unsigned __int16)(2 * *newSegment) >> 7 )
      break;
    LOWORD(writeIndex) = writeIndex + 1;
    fieldValue = secondSegment[(__int16)j + 2];
    *((_DWORD *)writePtr + 2) = fieldValue;
  }
  if ( a4 )
  {
    LOWORD(writeIndex) = writeIndex + 1;
    *((_DWORD *)writePtr + 2) = 0;
  }
  if ( a3 )
    *(_DWORD *)&newSegment[2 * (__int16)writeIndex + 4] = 0;
  return newSegment;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004A8170) --------------------------------------------------------
int  Rules_ResetDataObjectValue(int theDataObject)
{
  char incrementalResetFlag; // al
  int v2; // edx
  int result; // eax

  *(_DWORD *)(uintptr_t)(theDataObject + 8) = 0;
  *(_DWORD *)(uintptr_t)theDataObject = 0;
  *(_DWORD *)(uintptr_t)(theDataObject + 4) = 0;
  *(_BYTE *)(uintptr_t)(theDataObject + 12) &= 0xF8u;
  incrementalResetFlag = Rules_GetIncrementalReset();
  *(_BYTE *)(uintptr_t)(v2 + 12) &= ~8u;
  result = 8 * (incrementalResetFlag & 1);
  *(_DWORD *)(uintptr_t)(v2 + 12) |= result;
  *(_BYTE *)(uintptr_t)(v2 + 12) &= 0x8Fu;
  return result;
}
// 4A8196: variable 'v2' is possibly undefined

//----- (004A81C0) --------------------------------------------------------
signed int  Rules_AppendExpressionValueNode(int theValue, _DWORD *theExpression, signed int *theList)
{
  _DWORD *freeNode; // edx
  signed int listNode; // eax
  char v7; // cl
  signed int newNode; // edx
  _DWORD *freeEntry; // ecx
  _DWORD *v10; // ecx
  _DWORD *valueEntry; // ebp
  _DWORD *exprCopy; // eax
  int v13; // ecx
  signed int listTail; // esi

  freeNode = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
  if ( freeNode )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = *freeNode;
    listNode = g_ClipsMemFreeListTemp;
  }
  else
  {
    listNode = Mem_HeapAllocWithRetry((_DWORD *)0xC);
  }
  *(_WORD *)(uintptr_t)listNode &= 0x8000u;
  v7 = *(_BYTE *)(uintptr_t)listNode;
  *(_DWORD *)(uintptr_t)(listNode + 4) = 0;
  *(_BYTE *)(uintptr_t)listNode = v7 | 0x40;
  newNode = listNode;
  freeEntry = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
  if ( freeEntry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = *freeEntry;
    v10 = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
  }
  else
  {
    v10 = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0xC);
  }
  v10[2] = 0;
  valueEntry = v10;
  *v10 = theValue;
  if ( theExpression )
  {
    exprCopy = Rules_CopyExpressionChain(theExpression);
    *(_DWORD *)(uintptr_t)(v13 + 4) = exprCopy;
  }
  else
  {
    v10[1] = 0;
  }
  *(_DWORD *)(uintptr_t)(newNode + 8) = valueEntry;
  listTail = theList[1];
  if ( listTail )
    *(_DWORD *)(uintptr_t)(listTail + 4) = newNode;
  else
    *theList = newNode;
  theList[1] = newNode;
  return newNode;
}
// 4A8231: variable 'v13' is possibly undefined
// 4A8234: variable 'v8' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004A8280) --------------------------------------------------------
signed int  Rules_MultifieldAppendValue(_DWORD *theSegment, int newValue, int a3, int a4)
{
  int totalFields; // eax
  signed int newSegmentPtr; // eax
  char v7; // dl
  char v8; // bh
  __int16 newLength; // dx
  signed int newSegment; // ebp
  __int16 i; // ax
  int fieldIndex; // ecx
  int fieldPtr; // ebx
  __int16 writeIndex; // ax
  int v15; // edx

  totalFields = a3 + a4 + (*theSegment << 17 >> 23);
  if ( (unsigned int)(4 * totalFields + 12) < 0x1F4 && *(_DWORD *)(uintptr_t)(16 * totalFields + g_ClipsMemoryTable + 48) )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(16 * (a3 + a4 + (*theSegment << 17 >> 23)) + g_ClipsMemoryTable + 48);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 16 * (a3 + a4 + (*theSegment << 17 >> 23)) + 48) = *(_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
    newSegmentPtr = g_ClipsMemFreeListTemp;
  }
  else
  {
    newSegmentPtr = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(4 * (a3 + a4 + (*theSegment << 17 >> 23)) + 12));
  }
  v7 = *(_BYTE *)(uintptr_t)newSegmentPtr | 1;
  *(_BYTE *)(uintptr_t)newSegmentPtr = v7;
  *(_BYTE *)(uintptr_t)newSegmentPtr = v7 & 0xF9;
  *(_DWORD *)(uintptr_t)newSegmentPtr |= 4 * (a4 & 1);
  *(_BYTE *)(uintptr_t)newSegmentPtr &= ~8u;
  *(_DWORD *)(uintptr_t)newSegmentPtr |= 8 * (a3 & 1);
  v8 = *(_BYTE *)(uintptr_t)newSegmentPtr;
  *(_DWORD *)(uintptr_t)(newSegmentPtr + 4) = 0;
  *(_BYTE *)(uintptr_t)newSegmentPtr = v8 & 0xCF;
  newLength = ((unsigned __int16)(2 * *(_WORD *)theSegment) >> 7) + 1;
  *(_WORD *)(uintptr_t)newSegmentPtr &= 0x803Fu;
  newSegment = newSegmentPtr;
  *(_DWORD *)(uintptr_t)newSegmentPtr |= (newLength & 0x1FF) << 6;
  for ( i = 0; ; ++i )
  {
    fieldIndex = i;
    fieldPtr = fieldIndex * 4 + newSegment;
    if ( i >= *theSegment << 17 >> 23 )
      break;
    *(_DWORD *)(uintptr_t)(fieldPtr + 8) = theSegment[fieldIndex + 2];
  }
  *(_DWORD *)(uintptr_t)(fieldPtr + 8) = newValue;
  writeIndex = i + 1;
  if ( a4 )
  {
    v15 = writeIndex++;
    *(_DWORD *)(uintptr_t)(newSegment + 4 * v15 + 8) = 0;
  }
  if ( a3 )
    *(_DWORD *)(uintptr_t)(newSegment + 4 * writeIndex + 8) = 0;
  return newSegment;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004A8410) --------------------------------------------------------
_DWORD * Rules_CopyExpressionChain(_DWORD *theExpression)
{
  _DWORD *srcNode; // edx
  _DWORD *copyHead; // edi
  _DWORD *i; // ecx
  _DWORD *freeNode; // ebx
  _DWORD *newNode; // eax

  srcNode = theExpression;
  copyHead = 0;
  for ( i = 0; srcNode; i = newNode )
  {
    freeNode = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 80);
    if ( freeNode )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 80);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 80) = *freeNode;
      newNode = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
    }
    else
    {
      newNode = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x14);
    }
    newNode[4] = 0;
    *newNode = *srcNode;
    newNode[1] = srcNode[1];
    newNode[2] = srcNode[2];
    newNode[3] = srcNode[3];
    if ( i )
      i[4] = newNode;
    else
      copyHead = newNode;
    srcNode = (_DWORD *)(uintptr_t)srcNode[4];
  }
  return copyHead;
}
// 4A845C: variable 'i' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004A8520) --------------------------------------------------------
int  Rules_ReleaseJoinNetworkNodeChain(int result)
{
  int nextMatch; // edx
  int v2; // edx

  if ( result )
  {
    do
    {
      while ( 1 )
      {
        nextMatch = *(_DWORD *)(uintptr_t)(result + 4);
        if ( ((*(_BYTE *)(uintptr_t)result & 0x10) == 0 || (*(_BYTE *)(uintptr_t)result & 0x20) != 0) && (*(_BYTE *)(uintptr_t)result & 1) != 0 )
          break;
        *(_DWORD *)(uintptr_t)(result + 4) = g_PartialMatchFreeListHead;
        g_PartialMatchFreeListHead = result;
        result = nextMatch;
        if ( !nextMatch )
          return result;
      }
      Rules_FreePartialMatch(result);
      result = v2;
    }
    while ( v2 );
  }
  return result;
}
// 4A8558: variable 'v2' is possibly undefined
// 51A974: using guessed type int dword_51A974;
