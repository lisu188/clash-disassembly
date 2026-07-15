/* Generated from src/recovered/runtime/004D0560_legacy_runtime.inc.c; original address order retained. */
#include "../recovered_internal.h"

//----- (004D0560) --------------------------------------------------------
int  ObjectsCompiler_WriteClassPointerArray(
        const char *fileName,
        const char *pathName,
        int fileID,
        int headerFP,
        int imageID,
        int *fileCount)
{
  int result; // eax
  int v7; // ecx
  int outFile; // edi
  int classIndex; // esi
  int tableOffset; // ebp
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  int v14; // ecx
  char v15; // [esp+0h] [ebp-14h]
  int v16; // [esp+0h] [ebp-14h]

  v15 = headerFP;
  result = Rules_ConstructCodeFileOpen(
             0,
             fileName,
             fileID,
             pathName,
             fileCount,
             1,
             headerFP,
             (char)aDefclass_7,
             *(const char **)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 44),
             0,
             0);
  outFile = result;
  if ( result )
  {
    classIndex = 0;
    tableOffset = 0;
    while ( classIndex < (unsigned __int16)g_ClipsDefclassIdCount )
    {
      if ( classIndex > 0 )
        Output_WriteFormatted(v7, (unsigned __int16)g_ClipsDefclassIdCount, outFile, (int)asc_50C57C, v15);
      tableOffset += 4;
      ++classIndex;
      ObjectsCompiler_WriteDefclassPointerRef(outFile, *(_DWORD *)(g_ClipsDefclassIdTable + tableOffset - 4), imageID);
    }
    Output_WriteFormatted(v7, (unsigned __int16)g_ClipsDefclassIdCount, outFile, (int)asc_50C580, v15);
    Output_WriteFormatted(
      v11,
      *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 48),
      outFile,
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
        const char *fileName,
        const char *pathName,
        int fileID,
        int a4,
        int imageID,
        int *fileCount)
{
  int outFile; // esi
  int v7; // ecx
  int v8; // edx
  int hashIndex; // [esp+0h] [ebp-14h] BYREF
  int arrayVersion[4]; // [esp+4h] [ebp-10h] BYREF

  arrayVersion[0] = 1;
  outFile = Rules_ConstructCodeFileOpen(
         0,
         fileName,
         fileID,
         pathName,
         fileCount,
         1,
         a4,
         (char)aDefclass_7,
         *(const char **)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 40),
         0,
         0);
  if ( !outFile )
    return 0;
  hashIndex = 0;
  while ( 1 )
  {
    ObjectsCompiler_WriteDefclassPointerRef(outFile, *(_DWORD *)(g_DefclassHashTable + 4 * hashIndex), imageID);
    v8 = hashIndex + 1;
    hashIndex = v8;
    if ( v8 >= 167 )
      break;
    if ( v8 > 0 )
      Output_WriteFormatted(v7, v8, outFile, (int)asc_50C57C, hashIndex);
  }
  Rules_ConstructCodeFileClose(outFile, &hashIndex, v8, arrayVersion, 0, 0);
  return 1;
}
// 4D06A4: control flows out of bounds to 4D05E2
// 4D06DE: variable 'v7' is possibly undefined
// 51AD68: using guessed type int dword_51AD68;
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004D0710) --------------------------------------------------------
void  ObjectsCompiler_WriteSlotNameHashTable(const char *fileName, const char *pathName, int fileID, int a4, int imageID, int *fileCount)
{
  int outFile; // esi
  int v7; // ecx
  int v8; // edx
  int hashIndex; // [esp+0h] [ebp-14h]
  int arrayVersion[4]; // [esp+4h] [ebp-10h] BYREF

  arrayVersion[0] = 1;
  outFile = Rules_ConstructCodeFileOpen(
         0,
         fileName,
         fileID,
         pathName,
         fileCount,
         1,
         a4,
         (char)aSlot_name,
         *(const char **)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 36),
         0,
         0);
  if ( !outFile )
    return;
  hashIndex = 0;
  while ( 1 )
  {
    ObjectsCompiler_WriteSlotNamePointerRef(outFile, *(_DWORD *)(g_Defclass_SlotNameHashTablePtr + 4 * hashIndex), imageID);
    v8 = hashIndex + 1;
    hashIndex = v8;
    if ( v8 >= 167 )
      break;
    if ( v8 > 0 )
      Output_WriteFormatted(v7, v8, outFile, (int)asc_50C57C, v8);
  }
  Rules_ConstructCodeFileClose(outFile, &hashIndex, v8, arrayVersion, 0, 0);
}
// 4D0754: control flows out of bounds to 4D05E2
// 4D0782: control flows out of bounds to 4D06E8
// 4D076B: variable 'v9' is possibly undefined
// 4D0792: variable 'v7' is possibly undefined
// 51AD70: using guessed type int dword_51AD70;
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004D07A0) --------------------------------------------------------
signed int  ObjectsCompiler_WriteSlotNameRecords(
        const char *fileName,
        const char *pathName,
        int fileID,
        int headerFP,
        int imageID,
        int *fileCount)
{
  int theFile; // eax
  int *slotNameEntry; // edi
  signed int result; // eax
  int v10; // ecx
  int outFile; // esi
  int v12; // ecx
  int v13; // edx
  int v14; // ecx
  int v15; // ecx
  int v16; // edx
  int v17; // ecx
  int v18; // edx
  int v19; // ecx
  int elementCount; // [esp+0h] [ebp-28h] BYREF
  int arrayVersion; // [esp+4h] [ebp-24h] BYREF
  int bucketOffset; // [esp+8h] [ebp-20h]
  int hashIndex; // [esp+Ch] [ebp-1Ch]
  const char *pathNameCopy; // [esp+10h] [ebp-18h]
  int headerFPCopy; // [esp+14h] [ebp-14h]
  const char *fileNameCopy; // [esp+18h] [ebp-10h]

  fileNameCopy = fileName;
  pathNameCopy = pathName;
  headerFPCopy = headerFP;
  theFile = 0;
  elementCount = 0;
  arrayVersion = 1;
  hashIndex = 0;
  bucketOffset = 0;
  while ( 1 )
  {
    slotNameEntry = *(int **)(bucketOffset + g_Defclass_SlotNameHashTablePtr);
    if ( slotNameEntry )
      break;
LABEL_5:
    bucketOffset += 4;
    if ( (unsigned int)++hashIndex >= 0xA7 )
    {
      if ( theFile )
        Rules_ConstructCodeFileClose(theFile, &elementCount, elementCount, &arrayVersion, 0, 0);
      return 1;
    }
  }
  while ( 1 )
  {
    result = Rules_ConstructCodeFileOpen(
               theFile,
               fileNameCopy,
               fileID,
               pathNameCopy,
               fileCount,
               arrayVersion,
               headerFPCopy,
               (char)aSlot_name_0,
               *(const char **)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 32),
               0,
               0);
    outFile = result;
    if ( !result )
      return result;
    Output_WriteFormatted(v10, *slotNameEntry, result, (int)aU1U, *slotNameEntry);
    Compiler_WriteSymbolReference(outFile, slotNameEntry[3], v12);
    Output_WriteFormatted(v14, v13, outFile, (int)asc_50C5DC, elementCount);
    Compiler_WriteSymbolReference(outFile, slotNameEntry[4], v15);
    Output_WriteFormatted(v17, v16, outFile, (int)asc_50C5DC, elementCount);
    ObjectsCompiler_WriteSlotNamePointerRef(outFile, slotNameEntry[5], imageID);
    Output_WriteFormatted(v19, v18, outFile, (int)a0l, elementCount++);
    theFile = Rules_ConstructCodeFileClose(outFile, &elementCount, imageID, &arrayVersion, 0, 0);
    slotNameEntry = (int *)slotNameEntry[5];
    if ( !slotNameEntry )
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
int  ObjectsCompiler_CloseConstructFileGroup(int *fileArray, _DWORD *codeFiles, int maxIndices, int codeFileBaseOffset)
{
  _DWORD *codeFilePtr; // edi
  int theFile; // eax
  int result; // eax
  int elementCount; // [esp+0h] [ebp-1Ch] BYREF
  int arrayVersion; // [esp+4h] [ebp-18h] BYREF
  _DWORD *codeFilesEnd; // [esp+8h] [ebp-14h]
  int codeFileOffset; // [esp+Ch] [ebp-10h]

  elementCount = maxIndices;
  codeFilePtr = codeFiles;
  codeFileOffset = codeFileBaseOffset;
  arrayVersion = 0;
  codeFilesEnd = codeFiles + 8;
  do
  {
    elementCount = maxIndices;
    theFile = *fileArray++;
    *(fileArray - 1) = Rules_ConstructCodeFileClose(theFile, &elementCount, maxIndices, &arrayVersion, codeFilePtr, codeFileOffset);
    result = codeFileOffset + 12;
    ++codeFilePtr;
    codeFileOffset += 12;
  }
  while ( codeFilePtr != codeFilesEnd );
  return result;
}

//----- (004D0960) --------------------------------------------------------
int  ObjectsCompiler_WriteModuleRecord(int theFile, int a2, int a3)
{
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  char v9; // [esp+0h] [ebp-Ch]
  char v10; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(a3, a2, theFile, (int)asc_50C5E8, v9);
  Rules_WriteConstructModuleItemHeaderToCode(theFile, v4, v5, g_CLIPS_DefclassModuleItemIndex, *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 4));
  return Output_WriteFormatted(v7, v6, theFile, (int)asc_50C5EC, v10);
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
        int theFile,
        int fileNameBuffer,
        int theDefclass,
        char a4,
        int moduleIndex,
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
  unsigned __int16 subclassCount; // bx
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

  Output_WriteFormatted(theDefclass, fileNameBuffer, theFile, (int)asc_50C5E8, a4);
  Rules_WriteConstructHeaderToCode(theFile, theDefclass, v44, moduleIndex, **(_DWORD **)(g_ClipsConstructCompilerData + 20), *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 4));
  Output_WriteFormatted(v19, *(_DWORD *)(theDefclass + 20) << 30 >> 31, theFile, (int)a1UUU00U0U, (*(_DWORD *)(theDefclass + 20) & 2) != 0);
  LOWORD(v21) = *(_WORD *)(theDefclass + 34);
  if ( (_WORD)v21 )
    Output_WriteFormatted(a7, *(unsigned __int16 *)(theDefclass + 34), theFile, (int)aUSD_DD, *(_WORD *)(theDefclass + 34));
  else
    Output_WriteFormatted(v20, v21, theFile, (int)a0Null, v44);
  HIWORD(v22) = 0;
  subclassCount = *(_WORD *)(theDefclass + 40);
  if ( subclassCount )
  {
    Output_WriteFormatted(*(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 8), subclassCount, theFile, (int)aUSD_DD, subclassCount);
  }
  else
  {
    LOWORD(v22) = *(_WORD *)(theDefclass + 34);
    Output_WriteFormatted((unsigned __int16)v22 + a7, v22, theFile, (int)a0Null, v44);
  }
  HIWORD(v25) = 0;
  LOWORD(v24) = *(_WORD *)(theDefclass + 46);
  if ( (_WORD)v24 )
  {
    Output_WriteFormatted(
      *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 8),
      *(unsigned __int16 *)(theDefclass + 46),
      theFile,
      (int)aUSD_DD,
      *(_WORD *)(theDefclass + 46));
  }
  else
  {
    LOWORD(v25) = *(_WORD *)(theDefclass + 40);
    Output_WriteFormatted(v24, v25, theFile, (int)a0Null_0, v44);
  }
  if ( *(_DWORD *)(theDefclass + 52) )
    Output_WriteFormatted(
      *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 12),
      *(_DWORD *)(g_ClipsConstructCompilerData + 20),
      theFile,
      (int)aSD_DD_8,
      *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 12));
  else
    Output_WriteFormatted(v27, v26, theFile, (int)aNull_27, v44);
  if ( *(_DWORD *)(theDefclass + 56) )
    Output_WriteFormatted(
      *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 16),
      *(_DWORD *)(g_ClipsConstructCompilerData + 20),
      theFile,
      (int)aSD_DD_8,
      *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 16));
  else
    Output_WriteFormatted(v29, v28, theFile, (int)aNull_27, v44);
  if ( *(_DWORD *)(theDefclass + 60) )
    Output_WriteFormatted(
      *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 20),
      *(_DWORD *)(g_ClipsConstructCompilerData + 20),
      theFile,
      (int)aSD_DD_8,
      *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 20));
  else
    Output_WriteFormatted(v31, v30, theFile, (int)aNull_27, v44);
  Output_WriteFormatted(*(_DWORD *)(theDefclass + 64), *(_DWORD *)(theDefclass + 68), theFile, (int)aUUUUNullNull, *(_DWORD *)(theDefclass + 64));
  if ( *(_DWORD *)(theDefclass + 88) )
    Output_WriteFormatted(
      *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 24),
      *(_DWORD *)(g_ClipsConstructCompilerData + 20),
      theFile,
      (int)aSD_DD_8,
      *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 24));
  else
    Output_WriteFormatted(v33, v32, theFile, (int)aNull_27, v44);
  if ( *(_DWORD *)(theDefclass + 92) )
    Output_WriteFormatted(
      *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 28),
      *(_DWORD *)(g_ClipsConstructCompilerData + 20),
      theFile,
      (int)aSD_DD_8,
      *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 28));
  else
    Output_WriteFormatted(v35, v34, theFile, (int)aNull_27, v44);
  Output_WriteFormatted(v37, v36, theFile, (int)aU_0, *(_DWORD *)(theDefclass + 96));
  ObjectsCompiler_WriteDefclassPointerRef(theFile, *(_DWORD *)(theDefclass + 100), v44);
  Output_WriteFormatted(v39, v38, theFile, (int)asc_50C5DC, v44);
  Compiler_WriteBitMapReference(theFile, *(_DWORD *)(theDefclass + 104), v40);
  return Output_WriteFormatted(v42, v41, theFile, (int)asc_50C67C, v45);
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
        int *theFilePtr,
        const char *fileName,
        int fileID,
        const char *pathName,
        int a5,
        int *fileCount,
        int imageID,
        int theDefclass,
        int *arrayVersion,
        int *elementCount,
        int *a11,
        const char **codeFile)
{
  int result; // eax
  int v14; // ecx
  int v15; // edx
  int totalLinkCount; // [esp+0h] [ebp-2Ch]
  int i; // [esp+4h] [ebp-28h]
  int subclassOffset; // [esp+8h] [ebp-24h]
  int precedenceOffset; // [esp+Ch] [ebp-20h]
  unsigned int superclassIndex; // [esp+10h] [ebp-1Ch]
  unsigned int precedenceIndex; // [esp+14h] [ebp-18h]
  unsigned int subclassIndex; // [esp+18h] [ebp-14h]
  int wroteElement; // [esp+1Ch] [ebp-10h]

  wroteElement = 0;
  totalLinkCount = *(unsigned __int16 *)(theDefclass + 40) + *(unsigned __int16 *)(theDefclass + 34) + *(unsigned __int16 *)(theDefclass + 46);
  if ( !totalLinkCount )
    return 1;
  result = Rules_ConstructCodeFileOpen(
             *theFilePtr,
             fileName,
             fileID,
             pathName,
             fileCount,
             *arrayVersion,
             a5,
             (char)aDefclass_7,
             *(const char **)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 8),
             *a11,
             codeFile);
  *theFilePtr = result;
  if ( result )
  {
    v14 = 0;
    superclassIndex = 0;
    for ( i = 0; ; i += 4 )
    {
      v15 = superclassIndex;
      if ( *(unsigned __int16 *)(theDefclass + 34) <= superclassIndex )
        break;
      if ( wroteElement )
        Output_WriteFormatted(v14, *theFilePtr, *theFilePtr, (int)asc_50C5DC, totalLinkCount);
      ObjectsCompiler_WriteDefclassPointerRef(*theFilePtr, *(_DWORD *)(i + *(_DWORD *)(theDefclass + 36)), imageID);
      wroteElement = 1;
      ++superclassIndex;
    }
    subclassIndex = 0;
    subclassOffset = 0;
    while ( *(unsigned __int16 *)(theDefclass + 40) > subclassIndex )
    {
      if ( wroteElement )
        Output_WriteFormatted(*theFilePtr, v15, *theFilePtr, (int)asc_50C5DC, totalLinkCount);
      ObjectsCompiler_WriteDefclassPointerRef(*theFilePtr, *(_DWORD *)(subclassOffset + *(_DWORD *)(theDefclass + 42)), imageID);
      wroteElement = 1;
      v15 = subclassOffset + 4;
      subclassOffset += 4;
      ++subclassIndex;
    }
    precedenceIndex = 0;
    precedenceOffset = 0;
    while ( *(unsigned __int16 *)(theDefclass + 46) > precedenceIndex )
    {
      if ( wroteElement )
        Output_WriteFormatted(*theFilePtr, v15, *theFilePtr, (int)asc_50C5DC, totalLinkCount);
      ObjectsCompiler_WriteDefclassPointerRef(*theFilePtr, *(_DWORD *)(precedenceOffset + *(_DWORD *)(theDefclass + 48)), imageID);
      wroteElement = 1;
      v15 = precedenceOffset + 4;
      precedenceOffset += 4;
      ++precedenceIndex;
    }
    *elementCount += totalLinkCount;
    *theFilePtr = Rules_ConstructCodeFileClose(*theFilePtr, elementCount, imageID, arrayVersion, a11, (int)codeFile);
    return 1;
  }
  return result;
}
// 4D0E9F: variable 'v16' is possibly undefined
// 4D0E39: variable 'v14' is possibly undefined
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004D0EF0) --------------------------------------------------------
int  ObjectsCompiler_WriteSlotDescArray(
        int *theFilePtr,
        const char *fileName,
        DWORD fileID,
        const char *pathName,
        int headerFP,
        int *fileCount,
        int imageID,
        int theDefclass,
        int *arrayVersion,
        int *elementCount,
        int *reopenOldFile,
        const char **codeFile)
{
  int result; // eax
  int v15; // edx
  int v16; // ecx
  int slotDesc; // esi
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
  __int16 *defaultExpr; // eax
  int v30; // ecx
  int slotOffset; // [esp+0h] [ebp-14h]
  char v32; // [esp+0h] [ebp-14h]
  char v33; // [esp+0h] [ebp-14h]
  char v34; // [esp+0h] [ebp-14h]
  char v35; // [esp+0h] [ebp-14h]
  int v36; // [esp+0h] [ebp-14h]
  unsigned int slotIndex; // [esp+4h] [ebp-10h]

  if ( !*(_DWORD *)(theDefclass + 64) )
    return 1;
  result = Rules_ConstructCodeFileOpen(
             *theFilePtr,
             fileName,
             fileID,
             pathName,
             fileCount,
             *arrayVersion,
             headerFP,
             (char)aSlot_desc,
             *(const char **)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 12),
             *reopenOldFile,
             codeFile);
  *theFilePtr = result;
  if ( result )
  {
    slotIndex = 0;
    if ( *(_DWORD *)(theDefclass + 64) )
    {
      slotOffset = 0;
      do
      {
        v15 = slotOffset;
        v16 = slotIndex;
        slotDesc = slotOffset + *(_DWORD *)(theDefclass + 52);
        if ( slotIndex )
          Output_WriteFormatted(slotIndex, slotOffset, *theFilePtr, (int)asc_50C57C, slotOffset);
        Output_WriteFormatted(v16, v15, *theFilePtr, (int)aUUUUUUUUUUUUUU, *(_BYTE *)slotDesc & 1);
        ObjectsCompiler_WriteDefclassPointerRef(*theFilePtr, *(_DWORD *)(slotDesc + 4), imageID);
        Output_WriteFormatted(v18, *theFilePtr, *theFilePtr, (int)asc_50C5DC, slotOffset);
        ObjectsCompiler_WriteSlotNamePointerRef(*theFilePtr, *(_DWORD *)(slotDesc + 8), imageID);
        Output_WriteFormatted(*theFilePtr, v19, *theFilePtr, (int)asc_50C6C0, v32);
        Compiler_WriteSymbolReference(*theFilePtr, *(_DWORD *)(slotDesc + 12), v20);
        if ( *(_DWORD *)(slotDesc + 16) )
        {
          Output_WriteFormatted(v22, *theFilePtr, *theFilePtr, (int)aVoid_2, v33);
          if ( (*(_BYTE *)slotDesc & 0x40) != 0 )
          {
            Rules_ExpressionToCode(*theFilePtr, *(__int16 **)(slotDesc + 16), v23, fileID);
          }
          else
          {
            defaultExpr = (__int16 *)AST_BuildExpressionFromValue(*(_DWORD **)(slotDesc + 16));
            Rules_ExpressionToCode(*theFilePtr, defaultExpr, (int)defaultExpr, fileID);
            AST_Free(v30);
          }
        }
        else
        {
          Output_WriteFormatted(v22, v21, *theFilePtr, (int)aNull_28, v33);
        }
        Output_WriteFormatted(*theFilePtr, v24, *theFilePtr, (int)asc_50C5DC, v34);
        Compiler_WriteConstraintReference(*theFilePtr, *(_DWORD *)(slotDesc + 20), imageID, fileID);
        Output_WriteFormatted(v26, v25, *theFilePtr, (int)a00l, v35);
        if ( (*(_BYTE *)slotDesc & 1) != 0 )
        {
          Output_WriteFormatted(
            *theFilePtr,
            *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 12),
            *theFilePtr,
            (int)aSD_UU000Null,
            *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 12));
        }
        else
        {
          LOBYTE(v27) = *(_BYTE *)slotDesc;
          Output_WriteFormatted(v28, v27, *theFilePtr, (int)aNull000Null, v36);
        }
        slotOffset = v36 + 44;
        ++slotIndex;
      }
      while ( slotIndex < *(_DWORD *)(theDefclass + 64) );
    }
    *elementCount += *(_DWORD *)(theDefclass + 64);
    *theFilePtr = Rules_ConstructCodeFileClose(*theFilePtr, elementCount, imageID, arrayVersion, reopenOldFile, (int)codeFile);
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
        int *theFilePtr,
        const char *fileName,
        int fileID,
        const char *pathName,
        int a5,
        int *fileCount,
        int imageID,
        int theDefclass,
        int *arrayVersion,
        int *elementCount,
        int *a11,
        const char **codeFile)
{
  int outFile; // eax
  unsigned int slotIndex; // edx
  int slotOffset; // ecx
  char v17; // [esp+0h] [ebp-Ch]

  if ( !*(_DWORD *)(theDefclass + 72) )
    return 1;
  outFile = Rules_ConstructCodeFileOpen(
          *theFilePtr,
          fileName,
          fileID,
          pathName,
          fileCount,
          *arrayVersion,
          a5,
          (char)aSlot_desc_0,
          *(const char **)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 16),
          *a11,
          codeFile);
  *theFilePtr = outFile;
  if ( !outFile )
    return 0;
  slotIndex = 0;
  if ( *(_DWORD *)(theDefclass + 72) )
  {
    slotOffset = 0;
    do
    {
      if ( slotIndex )
        Output_WriteFormatted(slotOffset, slotIndex, *theFilePtr, (int)asc_50C5DC, v17);
      Output_WriteFormatted(slotOffset + 4, slotIndex + 1, *theFilePtr, (int)aSD_UU, *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 12));
    }
    while ( slotIndex < *(_DWORD *)(theDefclass + 72) );
  }
  *elementCount += *(_DWORD *)(theDefclass + 72);
  *theFilePtr = Rules_ConstructCodeFileClose(*theFilePtr, elementCount, imageID, arrayVersion, a11, (int)codeFile);
  return 1;
}
// 4D1212: variable 'v15' is possibly undefined
// 4D121C: variable 'v16' is possibly undefined
// 4D121C: variable 'v17' is possibly undefined
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004D12A0) --------------------------------------------------------
int  ObjectsCompiler_WriteSlotIndexMapArray(
        int *theFilePtr,
        const char *fileName,
        int fileID,
        const char *pathName,
        int a5,
        int *fileCount,
        int imageID,
        _DWORD *theDefclass,
        int *arrayVersion,
        int *elementCount,
        int *a11,
        const char **codeFile)
{
  int result; // eax
  unsigned int mapIndex; // edx
  int mapOffset; // ecx
  char separatorChar; // [esp+0h] [ebp-Ch]

  if ( !theDefclass[18] )
    return 1;
  result = Rules_ConstructCodeFileOpen(
             *theFilePtr,
             fileName,
             fileID,
             pathName,
             fileCount,
             *arrayVersion,
             a5,
             (char)aUnsigned,
             *(const char **)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 20),
             *a11,
             codeFile);
  *theFilePtr = result;
  if ( result )
  {
    mapIndex = 0;
    mapOffset = 0;
    do
    {
      if ( mapIndex )
        Output_WriteFormatted(mapOffset, mapIndex, *theFilePtr, (int)asc_50C5DC, separatorChar);
      Output_WriteFormatted(mapOffset + 4, mapIndex + 1, *theFilePtr, (int)aU_1, *(_DWORD *)(mapOffset + theDefclass[15]));
    }
    while ( mapIndex <= theDefclass[19] );
    *elementCount += theDefclass[19] + 1;
    *theFilePtr = Rules_ConstructCodeFileClose(*theFilePtr, elementCount, imageID, arrayVersion, a11, (int)codeFile);
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
        int *theFilePtr,
        const char *fileName,
        char fileID,
        const char *pathName,
        int a5,
        int *fileCount,
        int imageID,
        int theDefclass,
        int *arrayVersion,
        int *elementCount,
        int *a11,
        const char **codeFile)
{
  int result; // eax
  int v14; // edx
  int handlerCount; // ecx
  DWORD handlerIndex; // ebp
  int theHandler; // esi
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // edx
  char fileIDCopy; // [esp+0h] [ebp-14h]
  char v23; // [esp+0h] [ebp-14h]
  int handlerOffset; // [esp+4h] [ebp-10h]

  fileIDCopy = fileID;
  if ( !*(_DWORD *)(theDefclass + 96) )
    return 1;
  result = Rules_ConstructCodeFileOpen(
             *theFilePtr,
             fileName,
             fileID,
             pathName,
             fileCount,
             *arrayVersion,
             a5,
             (char)aHandler_1,
             *(const char **)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 24),
             *a11,
             codeFile);
  *theFilePtr = result;
  if ( result )
  {
    handlerCount = *(_DWORD *)(theDefclass + 96);
    handlerIndex = 0;
    if ( handlerCount )
    {
      handlerOffset = 0;
      do
      {
        if ( handlerIndex )
          Output_WriteFormatted(handlerCount, v14, *theFilePtr, (int)asc_50C57C, fileIDCopy);
        theHandler = handlerOffset + *(_DWORD *)(theDefclass + 88);
        Output_WriteFormatted(handlerCount, v14, *theFilePtr, (int)aUU000, *(_BYTE *)theHandler & 1);
        Compiler_WriteSymbolReference(*theFilePtr, *(_DWORD *)(theHandler + 8), v18);
        Output_WriteFormatted(v19, *theFilePtr, *theFilePtr, (int)asc_50C5DC, fileIDCopy);
        ObjectsCompiler_WriteDefclassPointerRef(*theFilePtr, *(_DWORD *)(theHandler + 12), imageID);
        Output_WriteFormatted(*(_DWORD *)(theHandler + 24), *theFilePtr, *theFilePtr, (int)aDDD_0, *(_DWORD *)(theHandler + 16));
        Rules_ExpressionToCode(*theFilePtr, *(__int16 **)(theHandler + 28), v20, handlerIndex);
        Output_WriteFormatted(*theFilePtr, v21, *theFilePtr, (int)aNull_29, v23);
        ++handlerIndex;
        handlerOffset += 36;
      }
      while ( handlerIndex < *(_DWORD *)(theDefclass + 96) );
    }
    *elementCount += *(_DWORD *)(theDefclass + 96);
    *theFilePtr = Rules_ConstructCodeFileClose(*theFilePtr, elementCount, imageID, arrayVersion, a11, (int)codeFile);
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
        int *theFilePtr,
        const char *fileName,
        int fileID,
        const char *pathName,
        int a5,
        int *fileCount,
        int imageID,
        int theDefclass,
        int *arrayVersion,
        int *elementCount,
        int *a11,
        const char **codeFile)
{
  int result; // eax
  unsigned int mapIndex; // edx
  int mapOffset; // ecx
  char v16; // [esp+0h] [ebp-Ch]

  if ( !*(_DWORD *)(theDefclass + 96) )
    return 1;
  result = Rules_ConstructCodeFileOpen(
             *theFilePtr,
             fileName,
             fileID,
             pathName,
             fileCount,
             *arrayVersion,
             a5,
             (char)aUnsigned,
             *(const char **)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 28),
             *a11,
             codeFile);
  *theFilePtr = result;
  if ( result )
  {
    mapIndex = 0;
    if ( *(_DWORD *)(theDefclass + 96) )
    {
      mapOffset = 0;
      do
      {
        if ( mapIndex )
          Output_WriteFormatted(mapOffset, mapIndex, *theFilePtr, (int)asc_50C5DC, v16);
        Output_WriteFormatted(mapOffset + 4, mapIndex + 1, *theFilePtr, (int)aU_1, *(_DWORD *)(mapOffset + *(_DWORD *)(theDefclass + 92)));
      }
      while ( mapIndex < *(_DWORD *)(theDefclass + 96) );
    }
    *elementCount += *(_DWORD *)(theDefclass + 96);
    *theFilePtr = Rules_ConstructCodeFileClose(*theFilePtr, elementCount, imageID, arrayVersion, a11, (int)codeFile);
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
_DWORD * Rules_ParseObjectPattern(int readSource)
{
  unsigned __int16 *v2; // esi
  unsigned __int16 *clsset; // ebp
  unsigned __int16 *tmpset; // esi
  int v5; // edx
  int v7; // ecx
  int v8; // edx
  int restrictionNode; // ecx
  _BYTE *packedBitmap; // eax
  int bitCount; // edx
  int bitmapValue; // eax
  _DWORD *v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int *slotConstraints; // ebx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // ecx
  _DWORD *isaNode; // eax
  int isaSymbol; // edx
  int v26; // ecx
  int tokenType; // [esp+0h] [ebp-30h] BYREF
  int tokenValue; // [esp+4h] [ebp-2Ch]
  char *tokenPrintForm; // [esp+8h] [ebp-28h]
  int multip; // [esp+Ch] [ebp-24h] BYREF
  int multipleRestrictions; // [esp+10h] [ebp-20h]
  int lastNode; // [esp+14h] [ebp-1Ch]
  _DWORD *firstNode; // [esp+18h] [ebp-18h]

  firstNode = 0;
  lastNode = 0;
  multipleRestrictions = 0;
  v2 = (unsigned __int16 *)Rules_AllocateClassBitmap((unsigned __int16)g_ClipsDefclassIdCount - 1, 1);
  clsset = v2;
  if ( Rules_IsClassBitmapEmpty(v2) )
  {
    Rules_PrintErrorID((int)aObjrtbld, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoObjectsOfExi, v7);
    Mem_SmallBlockFree(v2, ((int)*v2 >> 3) + 3);
    return 0;
  }
  else
  {
    tmpset = (unsigned __int16 *)Rules_AllocateClassBitmap((unsigned __int16)g_ClipsDefclassIdCount - 1, 1);
    Rules_IncrementIndentDepth(7);
    Parser_NextToken(readSource, v5);
    if ( tokenType != 101 )
    {
      while ( 1 )
      {
        multipleRestrictions = 1;
        IO_OutNewline();
        IO_OutWriteToken(asc_50C7F8);
        IO_OutWriteToken(tokenPrintForm);
        if ( tokenType != 100 || (Parser_NextToken(readSource, (int)&tokenType), tokenType != 2) )
        {
          Parser_ReportSyntaxError();
          goto LABEL_5;
        }
        if ( Rules_CheckDuplicateAttributeRestriction((int)firstNode, tokenValue) )
          goto LABEL_5;
        if ( tokenValue == g_Symbol_IsA )
        {
          if ( !Rules_ParseObjectPatternClassRestriction(readSource, (int)&tokenType) )
            goto LABEL_5;
          Rules_ResetClassBitmapToScope(tmpset, 0);
          if ( !Rules_ProcessObjectPatternClassRestriction(tmpset, (int *)(v14 + 68), 1) )
          {
            AST_FreeNode(v15);
            goto LABEL_5;
          }
          Rules_AndClassBitmaps((int)clsset, tmpset);
        }
        else if ( tokenValue == g_Clips_NameSymbol )
        {
          if ( !Rules_ParseObjectPatternNameRestriction(readSource, (int)&tokenType) )
            goto LABEL_5;
          Rules_ResetClassBitmapToScope(tmpset, 1);
        }
        else
        {
          slotConstraints = Rules_ResolveSlotConstraintAcrossClasses((int)clsset, tokenValue, &multip);
          if ( slotConstraints )
          {
            Rules_ResetClassBitmapToScope(tmpset, 1);
            if ( !Rules_ParseObjectPatternSlotRestriction(readSource, (int)&tokenType, multip, slotConstraints) )
              goto LABEL_5;
          }
          else
          {
            Rules_ResetClassBitmapToScope(tmpset, 0);
            *(_DWORD *)(AST_AllocNode() + 36) = tokenValue;
          }
        }
        if ( Rules_IsClassBitmapEmpty(tmpset) )
        {
          Rules_PrintErrorID((int)aObjrtbld, 2, 0);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoObjectsOfE_0, v17);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(*(_DWORD *)(v18 + 36) + 16), v18);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aRestrictionInO, v19);
          AST_FreeNode(v20);
          goto LABEL_5;
        }
        if ( Rules_IsClassBitmapEmpty(clsset) )
          break;
        if ( restrictionNode )
        {
          if ( firstNode )
            *(_DWORD *)(lastNode + 64) = restrictionNode;
          else
            firstNode = (_DWORD *)restrictionNode;
          lastNode = restrictionNode;
        }
        AST_Append(restrictionNode, v8);
        Parser_NextToken(readSource, (int)&tokenType);
        if ( tokenType == 101 )
          goto LABEL_20;
      }
      Rules_PrintErrorID((int)aObjrtbld, 1, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoObjectsOfExi, v21);
      AST_FreeNode(v22);
      goto LABEL_5;
    }
LABEL_20:
    if ( !firstNode )
    {
      if ( Rules_IsClassBitmapEmpty(clsset) )
      {
        Rules_PrintErrorID((int)aObjrtbld, 1, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoObjectsOfExi, v23);
LABEL_5:
        Mem_SmallBlockFree(clsset, ((int)*clsset >> 3) + 3);
        Mem_SmallBlockFree(tmpset, ((int)*tmpset >> 3) + 3);
        AST_FreeNode((int)firstNode);
        Rules_DecrementIndentDepth(7);
        return 0;
      }
      isaNode = (_DWORD *)AST_AllocNode();
      *isaNode = 17;
      isaSymbol = g_Symbol_IsA;
      isaNode[8] = 1;
      isaNode[9] = isaSymbol;
      firstNode = isaNode;
      isaNode[10] = v26;
    }
    if ( multipleRestrictions )
    {
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(tokenPrintForm);
    }
    Mem_SmallBlockFree(tmpset, ((int)*tmpset >> 3) + 3);
    packedBitmap = Rules_TrimClassBitmapToHighestBit(clsset);
    LOWORD(bitCount) = *(_WORD *)packedBitmap;
    bitmapValue = Rules_AddBitmapValue(packedBitmap, ((bitCount - (__CFSHL__(bitCount >> 31, 3) + 8 * (bitCount >> 31))) >> 3) + 3);
    firstNode[15] = bitmapValue;
    ++*(_DWORD *)(bitmapValue + 4);
    Mem_SmallBlockFree(v13, ((int)*(unsigned __int16 *)v13 >> 3) + 3);
    Rules_DecrementIndentDepth(7);
    return firstNode;
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
int  Rules_AnalyzeObjectPatternRestrictions(int topNode)
{
  int extractedNodes; // eax
  int result; // eax
  unsigned __int16 *origBitmap; // edi
  int isaValueList; // ebx
  int classNameItem; // esi
  int *theDefclass; // eax
  int defclassIndex; // ecx
  int byteOffset; // ebx
  int classBit; // eax
  char *bytePtr; // edi
  unsigned int slotIndex; // eax
  int slotDefclass; // ecx
  int slotDesc; // esi
  char *intersectedConstraint; // eax
  _DWORD *tmpConstraint; // edx
  int isUnmatchable; // ecx
  char clearedByte; // dl
  _DWORD *subNode; // ebx
  int subConstraint; // ecx
  int savedMinFields; // ebp
  int savedMaxFields; // edi
  char *subIntersected; // eax
  int restoreConstraint; // ecx
  _DWORD *subTmpConstraint; // edx
  int subUnmatchable; // ecx
  char *subBytePtr; // ebx
  char subClearedByte; // dh
  _WORD *packedBitmap; // eax
  _BYTE *trimmedPtr; // ecx
  int bitmapWord; // edx
  int bitmapValue; // eax
  _DWORD *freedBitmap; // ecx
  int v33; // ecx
  int v34; // ecx
  int v35; // ecx
  _DWORD *isaEndNode; // [esp+0h] [ebp-3Ch] BYREF
  _DWORD *isaRestriction; // [esp+4h] [ebp-38h] BYREF
  _DWORD *nameRestriction; // [esp+8h] [ebp-34h] BYREF
  BOOL bitmapModified; // [esp+Ch] [ebp-30h]
  int bitMask; // [esp+10h] [ebp-2Ch]
  _WORD *newBitmap; // [esp+14h] [ebp-28h]
  int patternPtr; // [esp+18h] [ebp-24h]
  _DWORD *curNode; // [esp+1Ch] [ebp-20h]
  int classID; // [esp+20h] [ebp-1Ch]

  patternPtr = topNode;
  bitmapModified = 0;
  extractedNodes = Rules_ExtractObjectPatternRestrictionNodes(*(_DWORD *)(topNode + 24), *(_DWORD *)(topNode + 64), &isaRestriction, (int)&isaEndNode, (int *)&nameRestriction);
  *(_DWORD *)(patternPtr + 64) = extractedNodes;
  result = Rules_StaticConstraintCheckingEnabled();
  if ( result )
  {
    origBitmap = *(unsigned __int16 **)(isaEndNode[15] + 16);
    newBitmap = (_WORD *)Rules_AllocateClassBitmap(*origBitmap, 0);
    if ( isaRestriction && (isaValueList = isaRestriction[4]) != 0 && *(_DWORD *)(isaValueList + 6) )
    {
      classNameItem = *(_DWORD *)(isaValueList + 6);
      do
      {
        theDefclass = Class_LookupInScope(*(_BYTE **)(*(_DWORD *)(classNameItem + 2) + 16));
        if ( theDefclass )
        {
          defclassIndex = *((unsigned __int16 *)theDefclass + 12);
          if ( (unsigned __int16)defclassIndex <= (int)*origBitmap )
          {
            byteOffset = (int)*((unsigned __int16 *)theDefclass + 12) >> 3;
            classBit = 1 << (defclassIndex % 8);
            if ( ((unsigned __int8)classBit & *((_BYTE *)origBitmap + byteOffset + 2)) != 0 )
              *((_BYTE *)newBitmap + byteOffset + 2) |= classBit;
          }
        }
        classNameItem = *(_DWORD *)(classNameItem + 10);
      }
      while ( classNameItem );
      bitmapModified = Rules_ClassBitmapsIdentical(newBitmap, origBitmap) == 0;
    }
    else
    {
      qmemcpy(newBitmap + 1, origBitmap + 1, ((int)(unsigned __int16)*newBitmap >> 3) + 1);
    }
    curNode = *(_DWORD **)(patternPtr + 64);
    if ( curNode != isaEndNode )
    {
      while ( curNode == isaRestriction || curNode == nameRestriction )
      {
LABEL_6:
        curNode = (_DWORD *)curNode[16];
        if ( curNode == isaEndNode )
          goto LABEL_7;
      }
      classID = 0;
      while ( 1 )
      {
LABEL_20:
        if ( (unsigned __int16)classID > (int)(unsigned __int16)*newBitmap )
          goto LABEL_6;
        bytePtr = (char *)newBitmap + ((int)(unsigned __int16)classID >> 3);
        bitMask = 1 << ((unsigned __int16)classID % 8);
        if ( ((unsigned __int8)bitMask & (unsigned __int8)bytePtr[2]) != 0 )
        {
          slotIndex = Instance_ResolveSlotIndex(*(_DWORD *)(g_ClipsDefclassIdTable + 4 * (unsigned __int16)classID), curNode[9]);
          slotDesc = *(_DWORD *)(*(_DWORD *)(slotDefclass + 56) + 4 * slotIndex);
          intersectedConstraint = Rules_IntersectConstraints(curNode[4], *(_DWORD *)(slotDesc + 20));
          Rules_ConstraintIsUnmatchable(intersectedConstraint);
          AST_DecrementNodeRefCount(tmpConstraint);
          if ( isUnmatchable )
          {
            clearedByte = ~(_BYTE)bitMask & bytePtr[2];
            bitmapModified = 1;
            bytePtr[2] = clearedByte;
            ++classID;
          }
          else
          {
            if ( *curNode != 18 )
              goto LABEL_22;
            subNode = (_DWORD *)curNode[17];
            if ( !subNode )
              goto LABEL_22;
            do
            {
              if ( *subNode == 18 || *subNode == 16 )
                subConstraint = *(_DWORD *)(subNode[4] + 26);
              else
                subConstraint = subNode[4];
              savedMinFields = *(_DWORD *)(subConstraint + 18);
              *(_DWORD *)(subConstraint + 18) = *(_DWORD *)(*(_DWORD *)(slotDesc + 20) + 18);
              savedMaxFields = *(_DWORD *)(subConstraint + 22);
              *(_DWORD *)(subConstraint + 22) = *(_DWORD *)(*(_DWORD *)(slotDesc + 20) + 22);
              subIntersected = Rules_IntersectConstraints(subConstraint, *(_DWORD *)(slotDesc + 20));
              *(_DWORD *)(restoreConstraint + 18) = savedMinFields;
              *(_DWORD *)(restoreConstraint + 22) = savedMaxFields;
              Rules_ConstraintIsUnmatchable(subIntersected);
              AST_DecrementNodeRefCount(subTmpConstraint);
              if ( subUnmatchable )
              {
                subBytePtr = (char *)newBitmap + ((int)(unsigned __int16)classID >> 3);
                subClearedByte = ~(1 << ((unsigned __int16)classID % 8)) & subBytePtr[2];
                bitmapModified = 1;
                subBytePtr[2] = subClearedByte;
                ++classID;
                goto LABEL_20;
              }
              subNode = (_DWORD *)subNode[16];
            }
            while ( subNode );
            ++classID;
          }
        }
        else
        {
LABEL_22:
          ++classID;
        }
      }
    }
LABEL_7:
    if ( bitmapModified )
    {
      if ( Rules_IsClassBitmapEmpty(newBitmap) )
      {
        Rules_PrintErrorID((int)aObjrtbld, 3, 1);
        Mem_SmallBlockFree(newBitmap, ((int)(unsigned __int16)*newBitmap >> 3) + 3);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoObjectsOfE_1, v33);
        Rules_PrintLongInteger(v34, *(_DWORD *)(patternPtr + 28));
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__25, v35);
        return 1;
      }
      else
      {
        packedBitmap = Rules_TrimClassBitmapToHighestBit(newBitmap);
        Rules_DecrementBitmapRefCountIfSet(isaEndNode[15], (int)packedBitmap);
        LOWORD(bitmapWord) = *(_WORD *)trimmedPtr;
        bitmapValue = Rules_AddBitmapValue(trimmedPtr, ((bitmapWord - (__CFSHL__(bitmapWord >> 31, 3) + 8 * (bitmapWord >> 31))) >> 3) + 3);
        isaEndNode[15] = bitmapValue;
        ++*(_DWORD *)(isaEndNode[15] + 4);
        Mem_SmallBlockFree(freedBitmap, ((int)*(unsigned __int16 *)freedBitmap >> 3) + 3);
        return 0;
      }
    }
    else
    {
      Mem_SmallBlockFree(newBitmap, ((int)(unsigned __int16)*newBitmap >> 3) + 3);
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
