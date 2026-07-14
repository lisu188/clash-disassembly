/* Recovered CRT, C++ support, streams, threading, and library runtime.
 * Original function-marker range: 0x004D0560..0x004E7F70.
 * Included by clash95.c; not a standalone translation unit. */

//----- (004D0560) --------------------------------------------------------
int  ObjectsCompiler_WriteClassPointerArray(
        const char *fileName,
        const char *pathName,
        int fileID,
        int a4,
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

  v15 = a4;
  result = Rules_ConstructCodeFileOpen(
             0,
             fileName,
             fileID,
             pathName,
             fileCount,
             1,
             a4,
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
        int a4,
        int imageID,
        int *fileCount)
{
  int v7; // eax
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
  const char *v24; // [esp+10h] [ebp-18h]
  int v25; // [esp+14h] [ebp-14h]
  const char *v26; // [esp+18h] [ebp-10h]

  v26 = fileName;
  v24 = pathName;
  v25 = a4;
  v7 = 0;
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
      if ( v7 )
        Rules_ConstructCodeFileClose(v7, &elementCount, elementCount, &arrayVersion, 0, 0);
      return 1;
    }
  }
  while ( 1 )
  {
    result = Rules_ConstructCodeFileOpen(
               v7,
               v26,
               fileID,
               v24,
               fileCount,
               arrayVersion,
               v25,
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
    v7 = Rules_ConstructCodeFileClose(outFile, &elementCount, imageID, &arrayVersion, 0, 0);
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
        int a2,
        int theDefclass,
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

  Output_WriteFormatted(theDefclass, a2, theFile, (int)asc_50C5E8, a4);
  Rules_WriteConstructHeaderToCode(theFile, theDefclass, v44, a5, **(_DWORD **)(g_ClipsConstructCompilerData + 20), *(_DWORD *)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 4));
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
             a5,
             (char)aSlot_desc,
             *(const char **)(*(_DWORD *)(g_ClipsConstructCompilerData + 20) + 12),
             *a11,
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
    *theFilePtr = Rules_ConstructCodeFileClose(*theFilePtr, elementCount, imageID, arrayVersion, a11, (int)codeFile);
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
  int v15; // ecx
  DWORD handlerIndex; // ebp
  int theHandler; // esi
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // edx
  char v22; // [esp+0h] [ebp-14h]
  char v23; // [esp+0h] [ebp-14h]
  int handlerOffset; // [esp+4h] [ebp-10h]

  v22 = fileID;
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
    v15 = *(_DWORD *)(theDefclass + 96);
    handlerIndex = 0;
    if ( v15 )
    {
      handlerOffset = 0;
      do
      {
        if ( handlerIndex )
          Output_WriteFormatted(v15, v14, *theFilePtr, (int)asc_50C57C, v22);
        theHandler = handlerOffset + *(_DWORD *)(theDefclass + 88);
        Output_WriteFormatted(v15, v14, *theFilePtr, (int)aUU000, *(_BYTE *)theHandler & 1);
        Compiler_WriteSymbolReference(*theFilePtr, *(_DWORD *)(theHandler + 8), v18);
        Output_WriteFormatted(v19, *theFilePtr, *theFilePtr, (int)asc_50C5DC, v22);
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
  int v11; // edx
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
    LOWORD(v11) = *(_WORD *)packedBitmap;
    bitmapValue = Rules_AddBitmapValue(packedBitmap, ((v11 - (__CFSHL__(v11 >> 31, 3) + 8 * (v11 >> 31))) >> 3) + 3);
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
  int v1; // eax
  int result; // eax
  unsigned __int16 *origBitmap; // edi
  int isaValueList; // ebx
  int classNameItem; // esi
  int *theDefclass; // eax
  int v7; // ecx
  int v8; // ebx
  int v9; // eax
  char *bytePtr; // edi
  unsigned int slotIndex; // eax
  int v12; // ecx
  int slotDesc; // esi
  char *intersectedConstraint; // eax
  _DWORD *v15; // edx
  int v16; // ecx
  char v17; // dl
  _DWORD *subNode; // ebx
  int subConstraint; // ecx
  int savedMinFields; // ebp
  int savedMaxFields; // edi
  char *v22; // eax
  int v23; // ecx
  _DWORD *v24; // edx
  int v25; // ecx
  char *v26; // ebx
  char v27; // dh
  _WORD *packedBitmap; // eax
  _BYTE *v29; // ecx
  int v30; // edx
  int bitmapValue; // eax
  _DWORD *v32; // ecx
  int v33; // ecx
  int v34; // ecx
  int v35; // ecx
  _DWORD *isaEndNode; // [esp+0h] [ebp-3Ch] BYREF
  _DWORD *isaRestriction; // [esp+4h] [ebp-38h] BYREF
  _DWORD *nameRestriction; // [esp+8h] [ebp-34h] BYREF
  BOOL bitmapModified; // [esp+Ch] [ebp-30h]
  int bitMask; // [esp+10h] [ebp-2Ch]
  _WORD *newBitmap; // [esp+14h] [ebp-28h]
  int v42; // [esp+18h] [ebp-24h]
  _DWORD *curNode; // [esp+1Ch] [ebp-20h]
  int classID; // [esp+20h] [ebp-1Ch]

  v42 = topNode;
  bitmapModified = 0;
  v1 = Rules_ExtractObjectPatternRestrictionNodes(*(_DWORD *)(topNode + 24), *(_DWORD *)(topNode + 64), &isaRestriction, (int)&isaEndNode, (int *)&nameRestriction);
  *(_DWORD *)(v42 + 64) = v1;
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
          v7 = *((unsigned __int16 *)theDefclass + 12);
          if ( (unsigned __int16)v7 <= (int)*origBitmap )
          {
            v8 = (int)*((unsigned __int16 *)theDefclass + 12) >> 3;
            v9 = 1 << (v7 % 8);
            if ( ((unsigned __int8)v9 & *((_BYTE *)origBitmap + v8 + 2)) != 0 )
              *((_BYTE *)newBitmap + v8 + 2) |= v9;
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
    curNode = *(_DWORD **)(v42 + 64);
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
          slotDesc = *(_DWORD *)(*(_DWORD *)(v12 + 56) + 4 * slotIndex);
          intersectedConstraint = Rules_IntersectConstraints(curNode[4], *(_DWORD *)(slotDesc + 20));
          Rules_ConstraintIsUnmatchable(intersectedConstraint);
          AST_DecrementNodeRefCount(v15);
          if ( v16 )
          {
            v17 = ~(_BYTE)bitMask & bytePtr[2];
            bitmapModified = 1;
            bytePtr[2] = v17;
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
              v22 = Rules_IntersectConstraints(subConstraint, *(_DWORD *)(slotDesc + 20));
              *(_DWORD *)(v23 + 18) = savedMinFields;
              *(_DWORD *)(v23 + 22) = savedMaxFields;
              Rules_ConstraintIsUnmatchable(v22);
              AST_DecrementNodeRefCount(v24);
              if ( v25 )
              {
                v26 = (char *)newBitmap + ((int)(unsigned __int16)classID >> 3);
                v27 = ~(1 << ((unsigned __int16)classID % 8)) & v26[2];
                bitmapModified = 1;
                v26[2] = v27;
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
        Rules_PrintLongInteger(v34, *(_DWORD *)(v42 + 28));
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__25, v35);
        return 1;
      }
      else
      {
        packedBitmap = Rules_TrimClassBitmapToHighestBit(newBitmap);
        Rules_DecrementBitmapRefCountIfSet(isaEndNode[15], (int)packedBitmap);
        LOWORD(v30) = *(_WORD *)v29;
        bitmapValue = Rules_AddBitmapValue(v29, ((v30 - (__CFSHL__(v30 >> 31, 3) + 8 * (v30 >> 31))) >> 3) + 3);
        isaEndNode[15] = bitmapValue;
        ++*(_DWORD *)(isaEndNode[15] + 4);
        Mem_SmallBlockFree(v32, ((int)*(unsigned __int16 *)v32 >> 3) + 3);
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

//----- (004D1F50) --------------------------------------------------------
_DWORD * Rules_AddObjectPatternNode(int thePattern)
{
  int multifieldNode; // ebp
  int v3; // eax
  _DWORD *v4; // edx
  int v5; // eax
  int curPattern; // esi
  BOOL endSlot; // edi
  int *patternNode; // edx
  _DWORD *alphaNode; // edx
  _DWORD *v10; // ebp
  _DWORD *newAlphaNode; // ebx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  _DWORD *nodeSlotGroup; // [esp+0h] [ebp-2Ch] BYREF
  int classBitmap; // [esp+4h] [ebp-28h]
  int slotBitmap; // [esp+8h] [ebp-24h]
  int currentLevel; // [esp+Ch] [ebp-20h]
  int *lastNode; // [esp+10h] [ebp-1Ch]

  currentLevel = Rules_GetObjectPatternNetworkRoot();
  multifieldNode = 0;
  slotBitmap = Rules_BuildAttributeIndexBitmap(*(_DWORD *)(thePattern + 64));
  v3 = *(_DWORD *)(thePattern + 64);
  lastNode = 0;
  v5 = Rules_PruneEmptyObjectPatternNodes(v3, v4);
  *(_DWORD *)(thePattern + 64) = v5;
  curPattern = v5;
  do
  {
    if ( (*(_BYTE *)(curPattern + 8) & 4) != 0 )
    {
      multifieldNode = curPattern;
      curPattern = *(_DWORD *)(curPattern + 68);
    }
    endSlot = !*(_DWORD *)(curPattern + 64) && multifieldNode;
    patternNode = (int *)Rules_FindObjectPatternNode(currentLevel, curPattern, endSlot, (int *)&nodeSlotGroup);
    if ( !patternNode )
      patternNode = Rules_CreateObjectPatternNode(curPattern, nodeSlotGroup, endSlot, (int)lastNode);
    if ( !*(_DWORD *)(curPattern + 64) && multifieldNode )
    {
      curPattern = multifieldNode;
      multifieldNode = 0;
    }
    lastNode = patternNode;
    curPattern = *(_DWORD *)(curPattern + 64);
    currentLevel = patternNode[4];
  }
  while ( curPattern && !*(_DWORD *)(curPattern + 60) );
  alphaNode = (_DWORD *)lastNode[8];
  if ( alphaNode )
  {
    while ( classBitmap != alphaNode[5] || slotBitmap != alphaNode[6] )
    {
      alphaNode = (_DWORD *)alphaNode[8];
      if ( !alphaNode )
        goto LABEL_18;
    }
    return alphaNode;
  }
  else
  {
LABEL_18:
    v10 = *(_DWORD **)(g_ClipsMemoryTable + 176);
    if ( v10 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 176);
      *(_DWORD *)(g_ClipsMemoryTable + 176) = *v10;
      newAlphaNode = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      newAlphaNode = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x2C);
    }
    Rules_ResetDataObjectValue((int)newAlphaNode);
    v12 = (int)lastNode;
    newAlphaNode[4] = 0;
    newAlphaNode[7] = v12;
    v13 = classBitmap;
    newAlphaNode[5] = classBitmap;
    ++*(_DWORD *)(v13 + 4);
    Rules_AdjustClassBusyCountFromBitmap(classBitmap, 1);
    v14 = slotBitmap;
    newAlphaNode[6] = slotBitmap;
    if ( v14 )
      ++*(_DWORD *)(v14 + 4);
    v15 = (int)lastNode;
    newAlphaNode[10] = 0;
    newAlphaNode[8] = *(_DWORD *)(v15 + 32);
    lastNode[8] = (int)newAlphaNode;
    newAlphaNode[9] = Rules_GetReactiveRuleList();
    Rules_SetReactiveRuleList((int)newAlphaNode);
    return newAlphaNode;
  }
}
// 4D1F7D: variable 'v4' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004D20F0) --------------------------------------------------------
int  Rules_FindObjectPatternNode(int listOfNodes, int thePattern, int endSlot, int *nodeSlotGroup)
{
  int curNode; // esi
  BOOL selectorsMatch; // eax

  curNode = listOfNodes;
  *nodeSlotGroup = 0;
  if ( !listOfNodes )
    return 0;
  while ( 1 )
  {
    selectorsMatch = *(_DWORD *)thePattern == 18 || *(_DWORD *)thePattern == 16 ? *(_DWORD *)curNode << 30 >> 31 : (*(_BYTE *)curNode & 2) == 0;
    if ( selectorsMatch
      && *(_DWORD *)(thePattern + 40) == *(_DWORD *)(curNode + 8)
      && *(_DWORD *)curNode << 21 >> 24 == *(_DWORD *)(thePattern + 32)
      && *(_DWORD *)(thePattern + 12) << 18 >> 25 == *(_DWORD *)curNode << 13 >> 24
      && endSlot == *(_DWORD *)curNode << 29 >> 31
      && AST_NodeListsEqual(*(__int16 **)(curNode + 12), *(__int16 **)(thePattern + 52)) )
    {
      break;
    }
    if ( !*nodeSlotGroup && *(_DWORD *)curNode << 21 >> 24 == *(_DWORD *)(thePattern + 32) && *(_DWORD *)(thePattern + 40) == *(_DWORD *)(curNode + 8) )
      *nodeSlotGroup = curNode;
    curNode = *(_DWORD *)(curNode + 28);
    if ( !curNode )
      return 0;
  }
  return curNode;
}
// 4D2152: variable 'a3' is possibly undefined

//----- (004D21C0) --------------------------------------------------------
int * Rules_CreateObjectPatternNode(int thePattern, _DWORD *nodeSlotGroup, int endSlot, int upperLevel)
{
  _DWORD *v7; // edx
  signed int nodeMem; // edx
  char v9; // ah
  __int16 *networkTest; // eax
  int *v11; // edx
  char v12; // cl
  int *newNode; // ebx
  int v14; // edx
  int v15; // ecx
  _DWORD *curNode; // edx
  _DWORD *prevNode; // edi
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
    nodeMem = g_ClipsMemFreeListTemp;
  }
  else
  {
    nodeMem = Mem_HeapAllocWithRetry((_DWORD *)0x28);
  }
  *(_DWORD *)(nodeMem + 32) = 0;
  *(_DWORD *)(nodeMem + 4) = 0;
  *(_DWORD *)(nodeMem + 16) = 0;
  *(_DWORD *)(nodeMem + 28) = 0;
  *(_DWORD *)(nodeMem + 24) = 0;
  v9 = *(_BYTE *)nodeMem;
  *(_DWORD *)(nodeMem + 36) = 0;
  *(_BYTE *)nodeMem = v9 & 0xFC;
  networkTest = AST_AddHashedNodeChain(*(__int16 **)(thePattern + 52), nodeMem, endSlot);
  v11[3] = (int)networkTest;
  v22 = (unsigned __int8)*(_DWORD *)(thePattern + 32);
  *(_WORD *)v11 &= 0xF807u;
  *v11 |= 8 * v22;
  v23 = *(_DWORD *)(thePattern + 12) << 18 >> 25;
  *v11 &= 0xFFF807FF;
  *v11 |= v23 << 11;
  v11[2] = *(_DWORD *)(thePattern + 40);
  newNode = v11;
  if ( *(_DWORD *)thePattern == 18 || *(_DWORD *)thePattern == 16 )
    *(_BYTE *)v11 |= 2u;
  *(_BYTE *)v11 &= ~4u;
  v14 = *v11;
  newNode[5] = upperLevel;
  *newNode = (4 * (v12 & 1)) | v14;
  if ( nodeSlotGroup )
  {
    curNode = nodeSlotGroup;
    prevNode = 0;
    do
    {
      if ( curNode[2] != nodeSlotGroup[2] )
        break;
      if ( *curNode << 21 >> 24 != *nodeSlotGroup << 21 >> 24 )
        break;
      v19 = curNode[3];
      if ( v19 )
      {
        if ( *(_WORD *)v19 == 50 && (**(_DWORD **)(*(_DWORD *)(v19 + 2) + 16) & 0x80) != 0 )
          break;
      }
      prevNode = curNode;
      curNode = (_DWORD *)curNode[7];
    }
    while ( curNode );
    if ( curNode )
    {
      newNode[6] = curNode[6];
      newNode[7] = (int)curNode;
      v20 = curNode[6];
      if ( v20 )
      {
        *(_DWORD *)(v20 + 28) = newNode;
      }
      else
      {
        v21 = curNode[5];
        if ( v21 )
          *(_DWORD *)(v21 + 16) = newNode;
        else
          Rules_SetObjectPatternNetworkRoot((int)newNode);
      }
      curNode[6] = newNode;
      return newNode;
    }
    else
    {
      newNode[6] = (int)prevNode;
      prevNode[7] = newNode;
      return newNode;
    }
  }
  else
  {
    if ( upperLevel )
    {
      newNode[7] = *(_DWORD *)(upperLevel + 16);
      *(_DWORD *)(upperLevel + 16) = newNode;
    }
    else
    {
      newNode[7] = Rules_GetObjectPatternNetworkRoot();
      Rules_SetObjectPatternNetworkRoot((int)newNode);
    }
    v15 = newNode[7];
    if ( v15 )
      *(_DWORD *)(v15 + 24) = newNode;
    return newNode;
  }
}
// 4D2227: variable 'a3' is possibly undefined
// 4D222C: variable 'v11' is possibly undefined
// 4D2281: variable 'v12' is possibly undefined
// 4D2330: variable 'v17' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004D2380) --------------------------------------------------------
int  Rules_RemoveObjectPatternNode(int *alphaNode)
{
  int v2; // edx
  int v3; // ecx
  int v4; // ecx
  int curReactiveNode; // edx
  _DWORD *v6; // ecx
  int i; // ebx
  _DWORD *curAlphaNode; // edx
  _DWORD *j; // eax
  int v10; // ebx
  int result; // eax
  int patternNode; // edx
  int rightNode; // ebp
  int v14; // ecx
  int v15; // edx
  _DWORD *v16; // ecx
  int v17; // eax
  _DWORD *v18; // ecx
  int v19; // ecx
  int v20; // edx
  _DWORD *v21; // ecx

  Rules_UnlinkObjectPatternFromGlobalLists(alphaNode);
  Rules_AdjustClassBusyCountFromBitmap(alphaNode[5], v2);
  Rules_DecrementBitmapRefCountIfSet(alphaNode[5], v3);
  if ( alphaNode[6] )
    Rules_DecrementBitmapCount(alphaNode[6], v4);
  curReactiveNode = Rules_GetReactiveRuleList();
  for ( i = 0; (_DWORD *)curReactiveNode != v6; curReactiveNode = *(_DWORD *)(curReactiveNode + 36) )
    i = curReactiveNode;
  if ( i )
    *(_DWORD *)(i + 36) = *(_DWORD *)(curReactiveNode + 36);
  else
    Rules_SetReactiveRuleList(*(_DWORD *)(curReactiveNode + 36));
  curAlphaNode = *(_DWORD **)(v6[7] + 32);
  for ( j = 0; curAlphaNode != v6; curAlphaNode = (_DWORD *)curAlphaNode[8] )
    j = curAlphaNode;
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
      patternNode = v6[7];
      if ( !*(_DWORD *)(patternNode + 16) )
      {
        while ( patternNode )
        {
          if ( *(_DWORD *)(patternNode + 24) || (rightNode = *(_DWORD *)(patternNode + 28)) != 0 )
          {
            if ( *(_DWORD *)(patternNode + 24) )
            {
              v17 = *(_DWORD *)(patternNode + 28);
              *(_DWORD *)(*(_DWORD *)(patternNode + 24) + 28) = v17;
              if ( v17 )
                *(_DWORD *)(v17 + 24) = *(_DWORD *)(patternNode + 24);
              AST_RemoveHashedNodeChain(*(__int16 **)(patternNode + 12), patternNode);
              g_ClipsMemFreeListTemp = (int)v18;
              *v18 = *(_DWORD *)(g_ClipsMemoryTable + 160);
              result = g_ClipsMemFreeListTemp;
              *(_DWORD *)(g_ClipsMemoryTable + 160) = g_ClipsMemFreeListTemp;
            }
            else
            {
              v19 = patternNode;
              v20 = *(_DWORD *)(patternNode + 20);
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
          v14 = patternNode;
          v15 = *(_DWORD *)(patternNode + 20);
          if ( v15 )
            *(_DWORD *)(v15 + 16) = rightNode;
          else
            Rules_SetObjectPatternNetworkRoot(rightNode);
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
  int alphaNodeAddr; // ebx
  int i; // ecx
  int v3; // ecx
  int *deletedInstance; // ecx
  int v5; // ecx

  alphaNodeAddr = (int)result;
  for ( i = g_Clips_InstanceListHead; i; i = *(_DWORD *)(v3 + 68) )
    result = Rules_RemoveMatchingPatternListEntry(i, alphaNodeAddr);
  deletedInstance = (int *)g_Instance_DeletedListHead;
  if ( g_Instance_DeletedListHead )
  {
    do
    {
      result = Rules_RemoveMatchingPatternListEntry(*deletedInstance, alphaNodeAddr);
      deletedInstance = *(int **)(v5 + 4);
    }
    while ( deletedInstance );
  }
  return result;
}
// 4D25F8: variable 'v3' is possibly undefined
// 4D2613: variable 'v5' is possibly undefined
// 51A28C: using guessed type int dword_51A28C;
// 51AD0C: using guessed type int dword_51AD0C;

//----- (004D2630) --------------------------------------------------------
int * Rules_RemoveMatchingPatternListEntry(int theInstance, int patternNode)
{
  int *result; // eax
  int *prevEntry; // edx

  result = *(int **)(theInstance + 16);
  prevEntry = 0;
  if ( result )
  {
    do
    {
      while ( 1 )
      {
        while ( patternNode != result[2] )
        {
          prevEntry = result;
          result = (int *)*result;
          if ( !result )
            return result;
        }
        --*(_DWORD *)(theInstance + 40);
        if ( prevEntry )
          break;
        *(_DWORD *)(theInstance + 16) = *result;
        g_ClipsMemFreeListTemp = (int)result;
        *result = *(_DWORD *)(g_ClipsMemoryTable + 48);
        *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
        result = *(int **)(theInstance + 16);
        if ( !result )
          return result;
      }
      *prevEntry = *result;
      g_ClipsMemFreeListTemp = (int)result;
      *result = *(_DWORD *)(g_ClipsMemoryTable + 48);
      *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
      result = (int *)*prevEntry;
    }
    while ( *prevEntry );
  }
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004D26C0) --------------------------------------------------------
signed int  Rules_CheckDuplicateAttributeRestriction(int restrictionList, int slotName)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx

  if ( !restrictionList )
    return 0;
  while ( slotName != *(_DWORD *)(restrictionList + 36) )
  {
    restrictionList = *(_DWORD *)(restrictionList + 64);
    if ( !restrictionList )
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
unsigned int * Rules_ParseObjectPatternClassRestriction(int readSource, int theToken)
{
  int *newNode; // esi
  char v5; // dl
  int v6; // ecx
  unsigned int *result; // eax
  int v8; // ecx
  int *v9; // eax

  newNode = (int *)Rules_CreateLHSParseNode();
  v5 = *(_BYTE *)newNode & 0xFC;
  *(_BYTE *)newNode = v5;
  *(_BYTE *)newNode = v5 | 2;
  IO_OutWriteToken(asc_50C7F8);
  Parser_NextToken(readSource, theToken);
  result = Rules_ParsePatternFieldList(readSource, (int *)theToken, v6, 0, 0, newNode, 0);
  if ( !result )
  {
    v9 = newNode;
LABEL_7:
    AST_DecrementNodeRefCount(v9);
    return 0;
  }
  if ( *(_DWORD *)theToken != 101 || *result == 18 || *result == 16 )
  {
    IO_OutNewline();
    if ( *(_DWORD *)theToken != 101 )
    {
      IO_OutWriteToken(asc_50C7F8);
      IO_OutWriteToken(*(char **)(theToken + 8));
    }
    Parser_ReportSyntaxError();
    AST_FreeNode(v8);
    v9 = newNode;
    goto LABEL_7;
  }
  *((_BYTE *)result + 8) |= 0x10u;
  return result;
}
// 4D2765: variable 'v6' is possibly undefined
// 4D27A4: variable 'v8' is possibly undefined

//----- (004D27E0) --------------------------------------------------------
unsigned int * Rules_ParseObjectPatternNameRestriction(int readSource, int theToken)
{
  int *newNode; // esi
  char v5; // dl
  int v6; // ecx
  unsigned int *result; // eax
  int v8; // ecx
  int *v9; // eax

  newNode = (int *)Rules_CreateLHSParseNode();
  v5 = *(_BYTE *)newNode & 0xDE;
  *(_BYTE *)newNode = v5;
  *(_BYTE *)newNode = v5 | 0x20;
  IO_OutWriteToken(asc_50C7F8);
  Parser_NextToken(readSource, theToken);
  result = Rules_ParsePatternFieldList(readSource, (int *)theToken, v6, 0, 1u, newNode, 0);
  if ( !result )
  {
    v9 = newNode;
LABEL_7:
    AST_DecrementNodeRefCount(v9);
    return 0;
  }
  if ( *(_DWORD *)theToken != 101 || *result == 18 || *result == 16 )
  {
    IO_OutNewline();
    if ( *(_DWORD *)theToken != 101 )
    {
      IO_OutWriteToken(asc_50C7F8);
      IO_OutWriteToken(*(char **)(theToken + 8));
    }
    Parser_ReportSyntaxError();
    AST_FreeNode(v8);
    v9 = newNode;
    goto LABEL_7;
  }
  *((_BYTE *)result + 8) |= 0x10u;
  return result;
}
// 4D2825: variable 'v6' is possibly undefined
// 4D2864: variable 'v8' is possibly undefined

//----- (004D28A0) --------------------------------------------------------
unsigned int * Rules_ParseObjectPatternSlotRestriction(int readSource, int theToken, int multiSlot, int *slotConstraints)
{
  int v8; // edx
  int v9; // ecx
  unsigned int slotNameID; // eax
  int v11; // ecx
  unsigned int *result; // eax
  int v13; // edx
  unsigned int *v14; // ecx

  IO_OutWriteToken(asc_50C7F8);
  Parser_NextToken(readSource, v8);
  slotNameID = Class_FindSlotNameID(v9);
  result = Rules_ParsePatternFieldList(readSource, (int *)theToken, v11, multiSlot, slotNameID, slotConstraints, 1);
  if ( result )
  {
    if ( *(_DWORD *)theToken == 101 )
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
      IO_OutWriteToken(*(char **)(theToken + 8));
      Parser_ReportSyntaxError();
      AST_FreeNode(v13);
      AST_DecrementNodeRefCount(slotConstraints);
      return 0;
    }
  }
  else
  {
    AST_DecrementNodeRefCount(slotConstraints);
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
int  Rules_AllocateClassBitmap(int maxClassID, int set)
{
  int clampedMaxClassID; // ebx
  _BYTE *bitmapMem; // eax
  int v5; // edx
  _WORD *theBitmap; // ecx
  int v7; // ecx

  clampedMaxClassID = maxClassID;
  if ( maxClassID == -1 )
    clampedMaxClassID = 0;
  bitmapMem = Mem_SmallBlockAlloc(((clampedMaxClassID - (__CFSHL__(clampedMaxClassID >> 31, 3) + 8 * (clampedMaxClassID >> 31))) >> 3) + 3);
  Mem_AllocArray(bitmapMem, v5);
  *theBitmap = clampedMaxClassID;
  Rules_ResetClassBitmapToScope(theBitmap, set);
  return v7;
}
// 4D2989: variable 'v5' is possibly undefined
// 4D2992: variable 'v6' is possibly undefined
// 4D299A: variable 'v7' is possibly undefined

//----- (004D29A0) --------------------------------------------------------
__int16  Rules_ResetClassBitmapToScope(_WORD *theBitmap, int set)
{
  int v3; // eax
  int bytesRemaining; // ebx
  char *bytePtr; // esi
  int classID; // ebx
  int tableOffset; // esi
  int theDefclass; // ecx
  char classFlags; // ah
  char *classBytePtr; // edi
  int theModule; // [esp+0h] [ebp-18h]

  v3 = (int)(unsigned __int16)*theBitmap >> 3;
  bytesRemaining = v3 + 1;
  if ( v3 + 1 > 0 )
  {
    bytePtr = (char *)theBitmap + bytesRemaining;
    do
    {
      --bytePtr;
      --bytesRemaining;
      bytePtr[2] = 0;
    }
    while ( bytesRemaining > 0 );
  }
  if ( set )
  {
    theModule = Module_GetCurrent();
    classID = 0;
    tableOffset = 0;
    while ( 1 )
    {
      LOWORD(v3) = *theBitmap;
      if ( classID > (unsigned __int16)*theBitmap )
        break;
      if ( *(_DWORD *)(tableOffset + g_ClipsDefclassIdTable)
        && Class_IsInScope(*(_DWORD *)(tableOffset + g_ClipsDefclassIdTable), theModule)
        && (classFlags = *(_BYTE *)(theDefclass + 20), (classFlags & 8) != 0)
        && (classFlags & 4) == 0 )
      {
        classBytePtr = (char *)theBitmap + ((classID - (__CFSHL__(classID >> 31, 3) + 8 * (classID >> 31))) >> 3);
        classBytePtr[2] |= 1 << (classID % 8);
        tableOffset += 4;
        ++classID;
      }
      else
      {
        tableOffset += 4;
        ++classID;
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
void  Rules_AdjustClassBusyCountFromBitmap(int bitmapHashNode, int offset)
{
  unsigned __int16 *theBitmap; // edi
  unsigned __int16 i; // si

  if ( !g_Rules_ClearInProgressFlag )
  {
    theBitmap = *(unsigned __int16 **)(bitmapHashNode + 16);
    for ( i = 0; i <= (int)*theBitmap; ++i )
    {
      if ( ((unsigned __int8)(1 << (i % 8)) & *((_BYTE *)theBitmap + ((int)i >> 3) + 2)) != 0 )
        *(_DWORD *)(*(_DWORD *)(g_ClipsDefclassIdTable + 4 * i) + 26) += offset;
    }
  }
  return;
}
// 4D2AD2: control flows out of bounds to 4D29E4
// 51A180: using guessed type int dword_51A180;
// 51AD64: using guessed type int dword_51AD64;

//----- (004D2B40) --------------------------------------------------------
signed int  Rules_IsClassBitmapEmpty(unsigned __int16 *theBitmap)
{
  int byteIndex; // eax

  byteIndex = ((int)*theBitmap >> 3) + 1;
  if ( !(_WORD)byteIndex )
    return 1;
  while ( !*((_BYTE *)theBitmap + (unsigned __int16)byteIndex + 1) )
  {
    LOWORD(byteIndex) = byteIndex - 1;
    if ( !(_WORD)byteIndex )
      return 1;
  }
  return 0;
}

//----- (004D2B80) --------------------------------------------------------
signed int  Rules_ClassBitmapsIdentical(unsigned __int16 *cs1, _WORD *cs2)
{
  unsigned __int16 *v2; // edi
  int v3; // ecx
  _WORD *bytePtr2; // ebx
  unsigned __int16 *bytePtr1; // esi
  int i; // ecx

  v2 = cs1;
  v3 = *cs1;
  HIWORD(cs1) = 0;
  if ( (unsigned __int16)v3 != (unsigned __int16)*cs2 )
    return 0;
  bytePtr2 = cs2;
  bytePtr1 = v2;
  LOWORD(cs1) = *cs2;
  for ( i = (unsigned int)cs1 ^ v3; i < ((int)*v2 >> 3) + 1; ++i )
  {
    if ( *((_BYTE *)bytePtr1 + 2) != *((_BYTE *)bytePtr2 + 2) )
      return 0;
    bytePtr2 = (_WORD *)((char *)bytePtr2 + 1);
    bytePtr1 = (unsigned __int16 *)((char *)bytePtr1 + 1);
  }
  return 1;
}

//----- (004D2BD0) --------------------------------------------------------
signed int  Rules_ProcessObjectPatternClassRestriction(_WORD *clsset, int *classRestrictions, int defaultToScope)
{
  unsigned __int16 *tmpset1; // ebp
  int v6; // ecx
  int v7; // eax
  _DWORD **v8; // ecx
  _DWORD *chkNode; // ecx
  unsigned __int16 *tmpset2; // esi
  int v11; // edi
  int theNode; // eax
  int *v13; // ecx
  int *theDefclass; // eax
  int v15; // ecx
  int v16; // ecx
  int includeFlag; // ebx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int constantRestriction; // [esp+8h] [ebp-14h]

  while ( 1 )
  {
    constantRestriction = 1;
    if ( !*classRestrictions )
      break;
    tmpset1 = (unsigned __int16 *)Rules_AllocateClassBitmap((unsigned __int16)g_ClipsDefclassIdCount - 1, 1);
    v7 = Rules_AllocateClassBitmap((unsigned __int16)g_ClipsDefclassIdCount - v6, 0);
    chkNode = *v8;
    tmpset2 = (unsigned __int16 *)v7;
    if ( chkNode )
    {
      v11 = v7 + 2;
      do
      {
        if ( *chkNode == 2 )
        {
          theDefclass = Class_LookupInScope(*(_BYTE **)(chkNode[1] + 16));
          *(_DWORD *)(v15 + 4) = theDefclass;
          if ( !theDefclass )
          {
            Rules_PrintErrorID((int)aObjrtbld, 5, 0);
            Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUndefinedClass, v18);
            Mem_SmallBlockFree(tmpset1, ((int)*tmpset1 >> 3) + 3);
            Mem_SmallBlockFree(tmpset2, ((int)*tmpset2 >> 3) + 3);
            return 0;
          }
          if ( (*(_BYTE *)(v15 + 8) & 1) != 0 )
          {
            Rules_ResetClassBitmapToScope(tmpset2, 1);
            includeFlag = 0;
          }
          else
          {
            includeFlag = 1;
            Rules_ResetClassBitmapToScope(tmpset2, 0);
          }
          Class_MarkBitmapSubclasses(v11, *(_DWORD *)(v16 + 4), includeFlag);
          Rules_AndClassBitmaps((int)tmpset1, tmpset2);
        }
        else
        {
          constantRestriction = 0;
        }
        chkNode = (_DWORD *)chkNode[16];
      }
      while ( chkNode );
    }
    if ( Rules_IsClassBitmapEmpty(tmpset1) )
    {
      Rules_PrintErrorID((int)aObjrtbld, 2, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoObjectsOfE_0, v19);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIsARestriction, v20);
      Mem_SmallBlockFree(tmpset1, ((int)*tmpset1 >> 3) + 3);
      Mem_SmallBlockFree(tmpset2, ((int)*tmpset2 >> 3) + 3);
      return 0;
    }
    if ( constantRestriction )
    {
      theNode = *classRestrictions;
      *classRestrictions = *(_DWORD *)(*classRestrictions + 68);
      *(_DWORD *)(theNode + 68) = 0;
      AST_FreeNode(theNode);
    }
    Rules_OrClassBitmaps((int)clsset, tmpset1);
    Mem_SmallBlockFree(tmpset1, ((int)*tmpset1 >> 3) + 3);
    classRestrictions = v13;
    Mem_SmallBlockFree(tmpset2, ((int)*tmpset2 >> 3) + 3);
    defaultToScope = 0;
  }
  if ( defaultToScope )
    Rules_ResetClassBitmapToScope(clsset, 1);
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
_DWORD * Rules_ResolveSlotConstraintAcrossClasses(int clsset, int slotName, _DWORD *multip)
{
  _DWORD *slotConstraints; // esi
  int i; // ebx
  int v6; // ecx
  unsigned int slotIndex; // eax
  _BYTE *slotDesc; // edx
  _DWORD *v9; // edx
  int v11; // edi
  int bucketOffset; // [esp+4h] [ebp-18h]

  slotConstraints = 0;
  bucketOffset = 0;
  *multip = 0;
  do
  {
    for ( i = *(_DWORD *)(bucketOffset + g_DefclassHashTable); i; i = *(_DWORD *)(i + 100) )
    {
      v6 = 8;
      if ( ((unsigned __int8)(1 << (*(unsigned __int16 *)(i + 24) % 8)) & *(_BYTE *)(clsset
                                                                                   + ((int)*(unsigned __int16 *)(i + 24) >> 3)
                                                                                   + 2)) != 0 )
      {
        LOBYTE(v6) = *(unsigned __int16 *)(i + 24) % 8;
        slotIndex = Instance_ResolveSlotIndex(v6, slotName);
        if ( slotIndex == -1 || (slotDesc = *(_BYTE **)(4 * slotIndex + *(_DWORD *)(i + 56)), (*(_DWORD *)slotDesc & 0x200) == 0) )
        {
          v11 = ((int)*(unsigned __int16 *)(i + 24) >> 3) + clsset;
          *(_BYTE *)(v11 + 2) &= ~(1 << (*(unsigned __int16 *)(i + 24) % 8));
        }
        else
        {
          if ( (*slotDesc & 2) != 0 )
            *multip = 1;
          Rules_UnionConstraints(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(i + 56) + 4 * slotIndex) + 20), (int)slotConstraints);
          AST_DecrementNodeRefCount(slotConstraints);
          slotConstraints = v9;
        }
      }
    }
    bucketOffset += 4;
  }
  while ( bucketOffset != 668 );
  return slotConstraints;
}
// 4D2EE2: variable 'v9' is possibly undefined
// 51AD68: using guessed type int dword_51AD68;

//----- (004D2F50) --------------------------------------------------------
int  Rules_AndClassBitmaps(int cs1, unsigned __int16 *cs2)
{
  int result; // eax
  int v5; // edx
  char v6; // ch

  result = ((int)*cs2 >> 3) + 1;
  if ( (int)*cs2 >> 3 != 0xFFFF )
  {
    do
    {
      v5 = cs1 + (unsigned __int16)result;
      v6 = *((_BYTE *)cs2 + (unsigned __int16)result-- + 1) & *(_BYTE *)(v5 + 1);
      *(_BYTE *)(v5 + 1) = v6;
    }
    while ( (_WORD)result );
  }
  return result;
}

//----- (004D2FA0) --------------------------------------------------------
int  Rules_OrClassBitmaps(int cs1, unsigned __int16 *cs2)
{
  int result; // eax
  int v5; // edx
  char v6; // ch

  result = ((int)*cs2 >> 3) + 1;
  if ( (int)*cs2 >> 3 != 0xFFFF )
  {
    do
    {
      v5 = cs1 + (unsigned __int16)result;
      v6 = *((_BYTE *)cs2 + (unsigned __int16)result-- + 1) | *(_BYTE *)(v5 + 1);
      *(_BYTE *)(v5 + 1) = v6;
    }
    while ( (_WORD)result );
  }
  return result;
}

//----- (004D2FF0) --------------------------------------------------------
_WORD * Rules_TrimClassBitmapToHighestBit(_WORD *result)
{
  _DWORD *oldBitmap; // ebp
  unsigned __int16 i; // bx
  int newBitmap; // ebx
  int v4; // ecx

  oldBitmap = result;
  for ( i = *result; i; --i )
  {
    if ( ((unsigned __int8)(1 << (i % 8)) & *((_BYTE *)result + ((int)i >> 3) + 2)) != 0 )
      break;
  }
  if ( i != (unsigned __int16)*result )
  {
    newBitmap = Rules_AllocateClassBitmap(i, 0);
    qmemcpy((void *)(newBitmap + 2), (char *)oldBitmap + 2, ((v4 - (__CFSHL__(v4 >> 31, 3) + 8 * (v4 >> 31))) >> 3) + 1);
    Mem_SmallBlockFree(oldBitmap, ((int)*(unsigned __int16 *)oldBitmap >> 3) + 3);
    return (_WORD *)newBitmap;
  }
  return result;
}
// 4D3071: variable 'v4' is possibly undefined

//----- (004D30C0) --------------------------------------------------------
int  Rules_ExtractObjectPatternRestrictionNodes(int a1, int restrictionList, _DWORD *isaNodeOut, int endNodeOut, int *nameNodeOut)
{
  _DWORD *newNode; // eax
  int *v7; // ecx
  int curNode; // eax
  int slotSymbol; // edx
  int lastNode; // edx

  *isaNodeOut = 0;
  *nameNodeOut = 0;
  newNode = (_DWORD *)AST_AllocNode();
  *(_DWORD *)endNodeOut = newNode;
  *newNode = 17;
  *(_DWORD *)(*(_DWORD *)endNodeOut + 36) = g_Symbol_IsA;
  *(_DWORD *)(*(_DWORD *)endNodeOut + 40) = 0;
  *(_DWORD *)(*(_DWORD *)endNodeOut + 32) = 1;
  *(_DWORD *)(*(_DWORD *)endNodeOut + 24) = a1;
  *(_DWORD *)(*(_DWORD *)endNodeOut + 60) = *(_DWORD *)(restrictionList + 60);
  curNode = restrictionList;
  *(_DWORD *)(restrictionList + 60) = 0;
  do
  {
    slotSymbol = *(_DWORD *)(curNode + 36);
    if ( slotSymbol == g_Symbol_IsA )
    {
      *v7 = curNode;
    }
    else if ( slotSymbol == g_Clips_NameSymbol )
    {
      *nameNodeOut = curNode;
    }
    lastNode = curNode;
    curNode = *(_DWORD *)(curNode + 64);
  }
  while ( curNode );
  if ( !lastNode )
    return *(_DWORD *)endNodeOut;
  *(_DWORD *)(lastNode + 64) = *(_DWORD *)endNodeOut;
  return restrictionList;
}
// 4D3150: variable 'v7' is possibly undefined
// 54E6F8: using guessed type int dword_54E6F8;
// 54E6FC: using guessed type int dword_54E6FC;

//----- (004D3170) --------------------------------------------------------
int  Rules_BuildAttributeIndexBitmap(int thePattern)
{
  int v1; // esi
  int i; // ebx
  int bitmapSize; // ebp
  _BYTE *theBitmap; // edi
  _WORD *v5; // ecx
  int j; // ebx
  _BYTE *bytePtr; // esi
  int bitmapValue; // ecx

  v1 = thePattern;
  for ( i = -1; thePattern; thePattern = *(_DWORD *)(thePattern + 64) )
  {
    if ( i < *(_DWORD *)(thePattern + 40) )
      i = *(_DWORD *)(thePattern + 40);
  }
  if ( (unsigned int)i < 2 )
    return 0;
  bitmapSize = ((i - (__CFSHL__(i >> 31, 3) + 8 * (i >> 31))) >> 3) + 3;
  theBitmap = Mem_SmallBlockAlloc(bitmapSize);
  Mem_AllocArray(theBitmap, bitmapSize);
  *v5 = i;
  for ( j = v1; j; j = *(_DWORD *)(j + 64) )
  {
    bytePtr = &theBitmap[(*(_DWORD *)(j + 40) - (__CFSHL__(*(int *)(j + 40) >> 31, 3) + 8 * (*(int *)(j + 40) >> 31))) >> 3];
    bytePtr[2] |= 1 << (*(_DWORD *)(j + 40) % 8);
  }
  Rules_AddBitmapValue(theBitmap, ((int)*(unsigned __int16 *)theBitmap >> 3) + 3);
  Mem_SmallBlockFree(theBitmap, bitmapSize);
  return bitmapValue;
}
// 4D3191: simplified comparisons for 'ebx.4': ==0 || ==1 became <2u
// 4D31C6: variable 'v5' is possibly undefined
// 4D3237: variable 'v8' is possibly undefined

//----- (004D3250) --------------------------------------------------------
int  Rules_PruneEmptyObjectPatternNodes(int topNode, _DWORD *classBitmapOut)
{
  int curNode; // ecx
  int listHead; // esi
  int prevNode; // ebx
  int bitmapValue; // edx
  int v8; // ecx
  int v9; // ecx
  int childList; // eax

  curNode = topNode;
  listHead = topNode;
  prevNode = 0;
  if ( !topNode )
    return listHead;
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
                bitmapValue = *(_DWORD *)(curNode + 60);
                if ( bitmapValue )
                {
                  *classBitmapOut = bitmapValue;
                  prevNode = curNode;
                  curNode = *(_DWORD *)(curNode + 64);
                  goto LABEL_9;
                }
                if ( *(_DWORD *)curNode != 17 && *(_DWORD *)curNode != 15 || *(_DWORD *)(curNode + 52) )
                  break;
                if ( prevNode )
                  *(_DWORD *)(prevNode + 64) = *(_DWORD *)(curNode + 64);
                else
                  listHead = *(_DWORD *)(curNode + 64);
                *(_DWORD *)(curNode + 64) = 0;
                AST_FreeNode(curNode);
                if ( !prevNode )
                  goto LABEL_24;
                curNode = *(_DWORD *)(prevNode + 64);
LABEL_9:
                if ( !curNode )
                  return listHead;
              }
              if ( *(_DWORD *)curNode != 18 && *(_DWORD *)curNode != 16
                || (*(_BYTE *)(curNode + 8) & 4) != 0
                || *(_DWORD *)(curNode + 52)
                || (*(_DWORD *)(curNode + 8) & 0x3F8000) != 0
                || (*(_WORD *)(curNode + 10) & 0x1FC0) != 0 )
              {
                break;
              }
              if ( prevNode )
                *(_DWORD *)(prevNode + 64) = *(_DWORD *)(curNode + 64);
              else
                listHead = *(_DWORD *)(curNode + 64);
              *(_DWORD *)(curNode + 64) = 0;
              AST_FreeNode(curNode);
              if ( !prevNode )
                goto LABEL_24;
              curNode = *(_DWORD *)(prevNode + 64);
              if ( !curNode )
                return listHead;
            }
            if ( *(_DWORD *)curNode != 18 && *(_DWORD *)curNode != 16
              || (*(_BYTE *)(curNode + 8) & 4) != 0
              || !*(_DWORD *)(curNode + 52)
              || (*(_DWORD *)(curNode + 8) & 0x3F8000) != 0
              || (*(_WORD *)(curNode + 10) & 0x1FC0) != 0 )
            {
              break;
            }
            *(_DWORD *)curNode = 17;
            prevNode = curNode;
            curNode = *(_DWORD *)(curNode + 64);
            if ( !curNode )
              return listHead;
          }
          if ( *(_DWORD *)curNode != 18 || (*(_BYTE *)(curNode + 8) & 4) == 0 || *(_DWORD *)(curNode + 68) )
            break;
          *(_DWORD *)curNode = 17;
          Rules_AppendMultifieldWildcardBitmapTest(curNode, 0);
          *(_BYTE *)(v8 + 8) &= ~4u;
LABEL_44:
          prevNode = v8;
          curNode = *(_DWORD *)(v8 + 64);
          if ( !curNode )
            return listHead;
        }
        if ( *(_DWORD *)curNode == 18 && (*(_BYTE *)(curNode + 8) & 4) != 0 )
          break;
        prevNode = curNode;
        curNode = *(_DWORD *)(curNode + 64);
        if ( !curNode )
          return listHead;
      }
      Rules_AppendFieldCardinalityBitmapTest(*(_DWORD **)(curNode + 68));
      childList = Rules_PruneEmptyObjectPatternNodes(*(_DWORD *)(v9 + 68), (int)classBitmapOut);
      *(_DWORD *)(v8 + 68) = childList;
      if ( childList )
        goto LABEL_44;
      if ( prevNode )
        *(_DWORD *)(prevNode + 64) = *(_DWORD *)(v8 + 64);
      else
        listHead = *(_DWORD *)(v8 + 64);
      *(_DWORD *)(v8 + 64) = 0;
      AST_FreeNode(v8);
      if ( prevNode )
        break;
LABEL_24:
      curNode = listHead;
      if ( !listHead )
        return 0;
    }
    curNode = *(_DWORD *)(prevNode + 64);
  }
  while ( curNode );
  return listHead;
}
// 4D33BA: variable 'v8' is possibly undefined
// 4D33DD: variable 'v9' is possibly undefined

//----- (004D3430) --------------------------------------------------------
int Rules_CreateDefaultObjectPatternRestriction()
{
  int classID; // ecx
  _WORD *theBitmap; // eax
  int v2; // ecx
  char *bytePtr; // esi
  _WORD *packedBitmap; // ebx
  int v5; // edx
  int bitmapValue; // eax
  int v7; // ecx
  _DWORD *topNode; // ecx
  int v9; // eax
  _DWORD *valueNode; // eax
  int v11; // ecx

  LOWORD(classID) = *((_WORD *)Class_LookupInScope(aInitialObjec_2) + 12);
  theBitmap = (_WORD *)Rules_AllocateClassBitmap(classID, 0);
  bytePtr = (char *)theBitmap + ((v2 - (__CFSHL__(v2 >> 31, 3) + 8 * (v2 >> 31))) >> 3);
  bytePtr[2] |= 1 << (v2 % 8);
  packedBitmap = Rules_TrimClassBitmapToHighestBit(theBitmap);
  AST_AllocNode();
  LOWORD(v5) = *packedBitmap;
  bitmapValue = Rules_AddBitmapValue(packedBitmap, v5 / 8 + 3);
  *(_DWORD *)(v7 + 60) = bitmapValue;
  ++*(_DWORD *)(bitmapValue + 4);
  Mem_SmallBlockFree(packedBitmap, (unsigned __int16)*packedBitmap / 8 + 3);
  *topNode = 17;
  topNode[8] = 1;
  v9 = g_Clips_NameSymbol;
  topNode[10] = 1;
  topNode[9] = v9;
  valueNode = (_DWORD *)AST_AllocNode();
  *(_DWORD *)(v11 + 68) = valueNode;
  *valueNode = 8;
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
int  Rules_ParseActionExpressionList(int a1, int readSource)
{
  int v4; // edx
  int v5; // ecx
  unsigned int *v6; // edx
  char *v8; // [esp+0h] [ebp-14h]

  Rules_IncrementIndentDepth(3);
  AST_Append(v5, v4);
  *(_DWORD *)(a1 + 6) = Parser_ParseProgram(readSource, v6, 1);
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
int  Rules_SetObjectPatternNegatedFlag(int result, char value)
{
  char patternFlags; // bl

  patternFlags = *(_BYTE *)(result + 12);
  if ( (patternFlags & 8) != 0 )
  {
    *(_BYTE *)(result + 12) = patternFlags & 0xF7;
    *(_DWORD *)(result + 12) |= 8 * (value & 1);
  }
  return result;
}

//----- (004D35A0) --------------------------------------------------------
void  Rules_TriggerObjectPatternMatchForAll(double a1)
{
  _DWORD *theInstance; // ecx
  int v2; // ecx

  theInstance = (_DWORD *)g_Clips_InstanceListHead;
  if ( g_Clips_InstanceListHead )
  {
    do
    {
      Rules_ObjectMatchAction((unsigned __int16 *)1, theInstance, -1, a1);
      theInstance = *(_DWORD **)(v2 + 68);
    }
    while ( theInstance );
  }
}
// 4D35BE: variable 'v2' is possibly undefined
// 51AD0C: using guessed type int dword_51AD0C;

//----- (004D35E0) --------------------------------------------------------
signed int  Rules_ParseDefclass(char *readSource, double a2)
{
  int *slots; // edi
  int v4; // ecx
  int v6; // ecx
  unsigned __int16 *v7; // eax
  unsigned __int16 *v8; // ecx
  int precedenceList; // ebp
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
  int cls; // [esp+0h] [ebp-38h] BYREF
  int roleSpecified; // [esp+4h] [ebp-34h] BYREF
  int abstract; // [esp+8h] [ebp-30h] BYREF
  int matchSpecified; // [esp+Ch] [ebp-2Ch] BYREF
  int reactive; // [esp+10h] [ebp-28h] BYREF
  int className; // [esp+14h] [ebp-24h]
  unsigned __int16 *superclasses; // [esp+18h] [ebp-20h]
  int parseError; // [esp+1Ch] [ebp-1Ch]

  slots = 0;
  roleSpecified = 0;
  abstract = 0;
  matchSpecified = 0;
  reactive = 1;
  Rules_SetPPBufferStatus(1);
  Rules_FlushPPBuffer();
  Rules_SetIndentDepth(3);
  IO_OutWriteToken(aDefclass_3);
  if ( Rules_IsBloaded() )
  {
    Rules_ReportCannotLoadWithBload();
    return 1;
  }
  v4 = Rules_GetConstructNameAndComment((int)readSource, (int)&g_ParserCurrentTokenType, (int (*)(void))Class_LookupCurrentScopedName, aDefclass_4, 0, asc_50C9A0, 1, 1, 1);
  className = v4;
  if ( !v4 )
    return 1;
  if ( !Rules_ValidateClassRedefinition(v4, &cls) )
    return 1;
  v7 = (unsigned __int16 *)Class_ParseSuperclasses((int)readSource, v6);
  superclasses = v7;
  if ( !v7 )
    return 1;
  precedenceList = Class_BuildPrecedenceList(cls, v7);
  if ( !precedenceList )
  {
    Class_FreeOrRecycleArray(v8, 1);
    return 1;
  }
  Parser_NextToken((int)readSource, (int)&g_ParserCurrentTokenType);
  parseError = 0;
  if ( g_ParserCurrentTokenType == 101 )
    goto LABEL_11;
  while ( 1 )
  {
    if ( g_ParserCurrentTokenType != 100
      || (IO_OutNewline(),
          AST_Append(v14, v13),
          IO_OutWriteToken(asc_50C9A4),
          Parser_NextToken((int)readSource, v15),
          g_ParserCurrentTokenType != 2) )
    {
      Parser_ReportSyntaxError();
      parseError = 1;
      goto LABEL_11;
    }
    if ( !strcmp_(v16, aRole) )
    {
      if ( !Rules_ParseClassAttributeFlag((int)readSource, (int)aRole, (int)aConcrete, &roleSpecified, &abstract) )
      {
        parseError = 1;
        goto LABEL_11;
      }
      goto LABEL_44;
    }
    if ( !strcmp_(v17, aPatternMatch) )
    {
      if ( !Rules_ParseClassAttributeFlag((int)readSource, (int)aPatternMatch, (int)aNonReactive, &matchSpecified, &reactive) )
      {
        parseError = 1;
        goto LABEL_11;
      }
      goto LABEL_44;
    }
    if ( !strcmp_(v18, aSlot_6) )
    {
      slots = Class_ParseSlot(readSource, slots, 0, (unsigned __int16 *)precedenceList, a2, 0);
      if ( !slots )
      {
        parseError = 1;
        goto LABEL_11;
      }
      goto LABEL_44;
    }
    if ( !strcmp_(v19, aSingleSlot) )
    {
      slots = Class_ParseSlot(readSource, slots, 0, (unsigned __int16 *)precedenceList, a2, 1);
      if ( !slots )
      {
        parseError = 1;
        goto LABEL_11;
      }
      goto LABEL_44;
    }
    if ( !strcmp_(v20, aMultislot_0) )
    {
      slots = Class_ParseSlot(readSource, slots, 1, (unsigned __int16 *)precedenceList, a2, 1);
      if ( !slots )
      {
        parseError = 1;
        goto LABEL_11;
      }
      goto LABEL_44;
    }
    if ( strcmp_(v21, aMessageHandl_6) )
      break;
    if ( !Rules_SkipMessageHandlerBody((int)readSource) )
    {
      parseError = 1;
      goto LABEL_11;
    }
LABEL_44:
    Parser_NextToken((int)readSource, (int)&g_ParserCurrentTokenType);
    if ( g_ParserCurrentTokenType == 101 )
      goto LABEL_11;
  }
  Parser_ReportSyntaxError();
  parseError = v22;
LABEL_11:
  if ( g_ParserCurrentTokenType != 101 || parseError == 1 )
  {
    Class_FreeOrRecycleArray(superclasses, 1);
    Class_FreeOrRecycleArray((unsigned __int16 *)precedenceList, 1);
    Class_DeleteSlotList((int)slots);
    return 1;
  }
  else
  {
    IO_OutWriteToken(asc_50CA24);
    if ( !roleSpecified )
      abstract = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(precedenceList + 2) + 4) + 20) << 29 >> 31;
    if ( !matchSpecified )
      reactive = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(precedenceList + 2) + 4) + 20) << 28 >> 31;
    if ( abstract && reactive )
    {
      Rules_PrintErrorID((int)aClasspsr, 1, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAnAbstractClas, v23);
      Class_FreeOrRecycleArray(superclasses, 1);
      Class_FreeOrRecycleArray((unsigned __int16 *)precedenceList, 1);
      Class_DeleteSlotList((int)slots);
      return 1;
    }
    else
    {
      cls = Class_AllocateRecord(className);
      v10 = abstract;
      *(_BYTE *)(cls + 20) &= ~4u;
      *(_DWORD *)(cls + 20) |= 4 * (v10 & 1);
      v11 = reactive;
      *(_BYTE *)(cls + 20) &= ~8u;
      *(_DWORD *)(cls + 20) |= 8 * (v11 & 1);
      *(_WORD *)(cls + 34) = *superclasses;
      *(_DWORD *)(cls + 36) = *(_DWORD *)(superclasses + 1);
      v12 = cls;
      **(_DWORD **)(precedenceList + 2) = cls;
      *(_WORD *)(v12 + 46) = *(_WORD *)precedenceList;
      *(_DWORD *)(cls + 48) = *(_DWORD *)(precedenceList + 2);
      g_ClipsMemFreeListTemp = (int)superclasses;
      *(_DWORD *)superclasses = *(_DWORD *)(g_ClipsMemoryTable + 24);
      *(_DWORD *)(g_ClipsMemoryTable + 24) = g_ClipsMemFreeListTemp;
      g_ClipsMemFreeListTemp = precedenceList;
      *(_DWORD *)precedenceList = *(_DWORD *)(g_ClipsMemoryTable + 24);
      *(_DWORD *)(g_ClipsMemoryTable + 24) = g_ClipsMemFreeListTemp;
      if ( slots )
        Class_FlattenSlotLinksToArray(cls, slots);
      Rules_InstallDefclass(cls);
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
signed int __fastcall Rules_ValidateClassRedefinition(int a1, int *existingClass)
{
  int v2; // eax
  int v4; // ecx
  int *v5; // ecx
  int v6; // eax
  int v7; // ecx
  int v8; // ecx

  v2 = Class_LookupCurrentScopedName();
  *existingClass = v2;
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
signed int  Rules_ParseClassAttributeFlag(int readSource, int qualifierName, int clearRelation, _DWORD *alreadyTestedFlag, _DWORD *binaryFlag)
{
  int v7; // edx
  int v8; // ecx
  int v9; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx

  if ( *alreadyTestedFlag )
  {
    Rules_PrintErrorID((int)aClasspsr, 4, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aClass_2, v11);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], qualifierName, v12);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAlreadyDeclare, v13);
    return 0;
  }
  IO_OutWriteToken(asc_50CAF8);
  Parser_NextToken(readSource, v7);
  if ( g_ParserCurrentTokenType == 2 )
  {
    if ( !strcmp_(v8, v8) )
    {
      *binaryFlag = 1;
      goto LABEL_5;
    }
    if ( !strcmp_(v9, clearRelation) )
    {
      *binaryFlag = 0;
LABEL_5:
      Parser_NextToken(readSource, (int)&g_ParserCurrentTokenType);
      if ( g_ParserCurrentTokenType == 101 )
      {
        *alreadyTestedFlag = 1;
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
signed int  Rules_SkipMessageHandlerBody(int readSource)
{
  int parenDepth; // ebx
  int justOpenedParen; // esi
  int *tokenPtr; // ecx
  int tokenType; // edx

  parenDepth = 1;
  justOpenedParen = 0;
LABEL_2:
  IO_OutWriteToken(asc_50CAF8);
  while ( 1 )
  {
    Parser_NextToken(readSource, (int)tokenPtr);
    tokenType = *tokenPtr;
    if ( *tokenPtr == 102 )
    {
      Parser_ReportSyntaxError();
      return 0;
    }
    if ( tokenType == 100 )
    {
      justOpenedParen = 1;
      ++parenDepth;
    }
    else
    {
      if ( tokenType == 101 )
      {
        --parenDepth;
        if ( !justOpenedParen )
        {
          IO_OutNewline();
          IO_OutNewline();
          IO_OutWriteToken(asc_50CB18);
        }
      }
      justOpenedParen = 0;
    }
    if ( parenDepth <= 0 )
      return 1;
    if ( !justOpenedParen )
      goto LABEL_2;
  }
}
// 4D3C70: variable 'v4' is possibly undefined

//----- (004D3CE0) --------------------------------------------------------
_DWORD * Rules_InstallDefclass(int theDefclass)
{
  int classNameSymbol; // eax
  unsigned int nameHash; // eax
  unsigned int watchInstances; // ebx
  int v4; // ecx
  unsigned int watchSlots; // esi
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
  int oldFlags; // ebx
  int v20; // esi
  char *ppForm; // eax
  signed int v22; // ecx

  classNameSymbol = Rules_GetConstructNameSymbol(theDefclass);
  nameHash = Class_HashClassName(classNameSymbol);
  watchInstances = 0;
  *(_DWORD *)(v4 + 30) = nameHash;
  watchSlots = 0;
  Rules_GetConstructNameString(v4);
  v6 = Class_LookupCurrentScopedName();
  if ( v6 )
  {
    oldFlags = *(_DWORD *)(v6 + 20);
    v20 = oldFlags;
    Class_DeleteRecursive(v6);
    watchInstances = (unsigned int)(oldFlags << 27) >> 31;
    watchSlots = (unsigned int)(v20 << 26) >> 31;
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
    if ( watchInstances )
      *(_BYTE *)(v14 + 20) = v15 | 0x10;
    if ( watchSlots )
      *(_BYTE *)(v14 + 20) |= 0x20u;
  }
  if ( !Mem_GetAllocFlag() )
  {
    ppForm = Rules_CopyPPBuffer();
    Rules_ReplaceConstructPPForm(v22, (int)ppForm);
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
unsigned __int16  Rules_LinkClassToSuperclasses(int theDefclass)
{
  int v1; // ecx
  unsigned int superclassIndex; // esi
  int linkOffset; // edi
  unsigned __int16 result; // ax
  int theSuperclass; // eax

  v1 = theDefclass;
  superclassIndex = 0;
  linkOffset = 0;
  result = *(_WORD *)(theDefclass + 34);
  if ( result )
  {
    do
    {
      theSuperclass = *(_DWORD *)(linkOffset + *(_DWORD *)(v1 + 36));
      linkOffset += 4;
      ++superclassIndex;
      Class_InsertLinkEntry((unsigned __int16 *)(theSuperclass + 40), v1, -1);
      result = *(_WORD *)(v1 + 34);
    }
    while ( superclassIndex < result );
  }
  return result;
}
// 4D3DDB: variable 'v1' is possibly undefined

//----- (004D3E10) --------------------------------------------------------
_DWORD * Rules_BuildInheritedSlotArray(int theDefclass)
{
  unsigned int precedenceIndex; // ebp
  int *slotLinks; // esi
  _DWORD *result; // eax
  unsigned int slotIndex; // edx
  int templateOffset; // ebp
  int *curLink; // eax
  _BYTE *theSlot; // ebx
  unsigned int slotCount; // [esp+0h] [ebp-24h] BYREF
  _DWORD *templateSlotPtr; // [esp+4h] [ebp-20h]
  int precedenceOffset; // [esp+8h] [ebp-1Ch]

  slotCount = 0;
  precedenceIndex = 1;
  slotLinks = Class_AppendNonPrivateSlotLinks(0, theDefclass, 0, &slotCount);
  precedenceOffset = 4;
  while ( precedenceIndex < *(unsigned __int16 *)(theDefclass + 46) )
  {
    ++precedenceIndex;
    slotLinks = Class_AppendNonPrivateSlotLinks(slotLinks, *(_DWORD *)(precedenceOffset + *(_DWORD *)(theDefclass + 48)), 1, &slotCount);
    precedenceOffset += 4;
  }
  result = (_DWORD *)slotCount;
  *(_DWORD *)(theDefclass + 68) = 0;
  *(_DWORD *)(theDefclass + 72) = result;
  if ( slotCount )
  {
    result = Mem_SmallBlockAlloc(4 * slotCount);
    *(_DWORD *)(theDefclass + 56) = result;
  }
  slotIndex = 0;
  if ( slotCount )
  {
    templateOffset = 0;
    do
    {
      templateSlotPtr = (_DWORD *)(templateOffset + *(_DWORD *)(theDefclass + 56));
      curLink = slotLinks;
      theSlot = (_BYTE *)*slotLinks;
      slotLinks = (int *)slotLinks[1];
      *templateSlotPtr = theSlot;
      if ( (*theSlot & 1) == 0 )
        ++*(_DWORD *)(theDefclass + 68);
      g_ClipsMemFreeListTemp = (int)curLink;
      *curLink = *(_DWORD *)(g_ClipsMemoryTable + 32);
      result = (_DWORD *)g_ClipsMemoryTable;
      *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
      ++slotIndex;
      templateOffset += 4;
    }
    while ( slotIndex < slotCount );
  }
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004D3F00) --------------------------------------------------------
_DWORD * Class_BuildSlotIndexMap(_DWORD *result)
{
  _DWORD *theDefclass; // edx
  int v2; // ecx
  unsigned int slotIndex; // ecx
  int templateOffset; // eax
  unsigned int slotNameID; // esi
  _DWORD *v6; // eax
  _DWORD *v7; // edx
  unsigned int mapIndex; // ecx
  int mapOffset; // eax
  int slotOffset; // ecx

  theDefclass = result;
  result[19] = 0;
  v2 = result[18];
  result[15] = 0;
  if ( v2 )
  {
    slotIndex = 0;
    if ( result[18] )
    {
      templateOffset = 0;
      do
      {
        slotNameID = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(theDefclass[14] + templateOffset) + 8) + 8);
        if ( slotNameID > theDefclass[19] )
          theDefclass[19] = slotNameID;
        ++slotIndex;
        templateOffset += 4;
      }
      while ( slotIndex < theDefclass[18] );
    }
    v6 = Mem_SmallBlockAlloc(4 * (theDefclass[19] + 1));
    v7[15] = v6;
    mapIndex = 0;
    mapOffset = 0;
    do
    {
      *(_DWORD *)(v7[15] + mapOffset) = 0;
      ++mapIndex;
      mapOffset += 4;
    }
    while ( mapIndex <= v7[19] );
    result = 0;
    if ( v7[18] )
    {
      slotOffset = 0;
      do
      {
        result = (_DWORD *)((char *)result + 1);
        *(_DWORD *)(v7[15] + 4 * *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(slotOffset + v7[14]) + 8) + 8)) = result;
        slotOffset += 4;
      }
      while ( (unsigned int)result < v7[18] );
    }
  }
  return result;
}
// 4D3F5D: variable 'v7' is possibly undefined

//----- (004D3FC0) --------------------------------------------------------
int * Class_AppendNonPrivateSlotLinks(int *linkList, int theDefclass, int inherited, _DWORD *slotCount)
{
  int slotIndex; // ebp
  int slotOffset; // edi
  int slotDesc; // ebx
  int *i; // eax
  _DWORD *v9; // edx
  int *newLink; // eax
  bool notInherited; // [esp+8h] [ebp-10h]

  slotIndex = *(_DWORD *)(theDefclass + 64) - 1;
  if ( slotIndex >= 0 )
  {
    notInherited = inherited == 0;
    slotOffset = 44 * slotIndex;
    do
    {
      slotDesc = slotOffset + *(_DWORD *)(theDefclass + 52);
      if ( (*(_BYTE *)slotDesc & 8) == 0 || notInherited )
      {
        for ( i = linkList; i; i = (int *)i[1] )
        {
          if ( *(_DWORD *)(slotDesc + 8) == *(_DWORD *)(*i + 8) )
            break;
        }
        if ( !i )
        {
          v9 = *(_DWORD **)(g_ClipsMemoryTable + 32);
          if ( v9 )
          {
            g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
            *(_DWORD *)(g_ClipsMemoryTable + 32) = *v9;
            newLink = (int *)g_ClipsMemFreeListTemp;
          }
          else
          {
            newLink = (int *)Mem_HeapAllocWithRetry((_DWORD *)8);
          }
          *newLink = slotDesc;
          newLink[1] = (int)linkList;
          linkList = newLink;
          ++*slotCount;
        }
      }
      slotOffset -= 44;
      --slotIndex;
    }
    while ( slotOffset >= 0 );
  }
  return linkList;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004D4070) --------------------------------------------------------
_DWORD * Class_FlattenSlotLinksToArray(int theDefclass, int *slotLinks)
{
  int *i; // edi
  _DWORD *result; // eax
  int v5; // ebp
  int arrayOffset; // edx
  int *linkEntry; // ebp
  const void *srcSlot; // esi
  _DWORD *slotIndex; // [esp+0h] [ebp-1Ch]
  int *curLink; // [esp+4h] [ebp-18h]

  for ( i = slotLinks; slotLinks; slotLinks = (int *)slotLinks[1] )
  {
    *(_DWORD *)(*slotLinks + 4) = theDefclass;
    ++*(_DWORD *)(theDefclass + 64);
  }
  curLink = i;
  slotIndex = 0;
  result = Mem_SmallBlockAlloc(44 * *(_DWORD *)(theDefclass + 64));
  v5 = *(_DWORD *)(theDefclass + 64);
  *(_DWORD *)(theDefclass + 52) = result;
  if ( v5 )
  {
    arrayOffset = 0;
    do
    {
      linkEntry = curLink;
      srcSlot = (const void *)*curLink;
      curLink = (int *)curLink[1];
      qmemcpy((void *)(arrayOffset + *(_DWORD *)(theDefclass + 52)), srcSlot, 0x2Cu);
      *(_DWORD *)(arrayOffset + *(_DWORD *)(theDefclass + 52) + 32) = arrayOffset + *(_DWORD *)(theDefclass + 52);
      *(_DWORD *)(arrayOffset + *(_DWORD *)(theDefclass + 52) + 40) = 0;
      g_ClipsMemFreeListTemp = *linkEntry;
      *(_DWORD *)g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 176);
      *(_DWORD *)(g_ClipsMemoryTable + 176) = g_ClipsMemFreeListTemp;
      g_ClipsMemFreeListTemp = (int)linkEntry;
      *linkEntry = *(_DWORD *)(g_ClipsMemoryTable + 32);
      result = (_DWORD *)((char *)slotIndex + 1);
      *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
      arrayOffset += 44;
      slotIndex = result;
    }
    while ( (unsigned int)result < *(_DWORD *)(theDefclass + 64) );
  }
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004D4170) --------------------------------------------------------
signed int  Class_BuildModuleScopeBitmap(_DWORD *theDefclass)
{
  int moduleCount; // eax
  int i; // edi
  int moduleID; // esi
  _DWORD *v4; // ecx
  _BYTE *bytePtr; // ebx
  int bitmapValue; // eax
  int bitmapSize; // [esp+4h] [ebp-28h]
  _BYTE *className; // [esp+Ch] [ebp-20h]
  _BYTE *scopeMap; // [esp+10h] [ebp-1Ch]

  className = *(_BYTE **)(*theDefclass + 16);
  moduleCount = Module_GetModuleCount();
  bitmapSize = ((moduleCount - (__CFSHL__(moduleCount >> 31, 3) + 8 * (moduleCount >> 31))) >> 3) + 1;
  scopeMap = Mem_SmallBlockAlloc(bitmapSize);
  Mem_AllocArray(scopeMap, bitmapSize);
  Module_BeginEnum();
  for ( i = Module_NextEnum(0); i; i = Module_NextEnum(i) )
  {
    Module_SetCurrent(i);
    moduleID = *(_DWORD *)(i + 24);
    if ( Rules_FindImportExportConstruct(aDefclass_4, v4, className, 1, 0) )
    {
      bytePtr = &scopeMap[(moduleID - (__CFSHL__(moduleID >> 31, 3) + 8 * (moduleID >> 31))) >> 3];
      *bytePtr |= 1 << (moduleID % 8);
    }
  }
  Module_EndEnum();
  bitmapValue = Rules_AddBitmapValue(scopeMap, bitmapSize);
  theDefclass[26] = bitmapValue;
  ++*(_DWORD *)(bitmapValue + 4);
  return Mem_SmallBlockFree(scopeMap, bitmapSize);
}
// 4D41E6: variable 'v4' is possibly undefined

//----- (004D4260) --------------------------------------------------------
_DWORD * Class_GenerateDefaultSlotHandlersAndFlag(_DWORD *result)
{
  _DWORD *theDefclass; // edx
  int slotOffset; // ebx
  unsigned int slotIndex; // ecx
  unsigned int handlerIndex; // ebx
  int handlerOffset; // ecx

  theDefclass = result;
  if ( result[16] )
  {
    slotOffset = 0;
    do
    {
      result = (_DWORD *)Class_GeneratePublicSlotHandlers(slotOffset + theDefclass[13]);
      slotOffset += 44;
    }
    while ( slotIndex < theDefclass[16] );
  }
  handlerIndex = 0;
  if ( theDefclass[24] )
  {
    handlerOffset = 0;
    do
    {
      result = (_DWORD *)theDefclass[22];
      LOBYTE(result[handlerOffset]) |= 1u;
      ++handlerIndex;
      handlerOffset += 9;
    }
    while ( handlerIndex < theDefclass[24] );
  }
  return result;
}
// 4D4273: variable 'v1' is possibly undefined
// 4D4286: variable 'v3' is possibly undefined

//----- (004D42C0) --------------------------------------------------------
int  Class_BrowseClassesCommand(int a1, double a2)
{
  int *theDefclass; // eax
  int result; // eax
  int v4; // ecx
  int argValue; // [esp-8h] [ebp-24h] BYREF
  int v6; // [esp+0h] [ebp-1Ch]
  int v7; // [esp+14h] [ebp-8h]

  v7 = a1;
  if ( !Rules_RtnArgCount() )
  {
    theDefclass = Class_LookupByQualifiedName(aObject_1);
    return Class_PrintClassBrowse((int)g_IO_LogicalName_WDisplay, (int)theDefclass, 0);
  }
  result = Lexer_ParseValueList(1, &argValue, 2, a2);
  if ( result )
  {
    theDefclass = Class_LookupByQualifiedName(*(_BYTE **)(v6 + 16));
    if ( !theDefclass )
      return Class_ReportLookupError(v4, *(_DWORD *)(v6 + 16));
    return Class_PrintClassBrowse((int)g_IO_LogicalName_WDisplay, (int)theDefclass, 0);
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
signed int  Class_PrintClassDescription(int logicalName, int theDefclass)
{
  int v4; // ecx
  char *v5; // edx
  int maxOverrideMessageLength; // ebp
  int v7; // edi
  unsigned int slotIndex; // ebx
  int slotOffset; // edx
  unsigned int slotNameLength; // kr04_4
  int slotDesc; // ecx
  unsigned int overrideMessageLength; // kr08_4
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int precedenceIndex; // ecx
  int precedenceOffset; // edx
  char buf[84]; // [esp+0h] [ebp-88h] BYREF
  char slotNamePrintFormat[12]; // [esp+54h] [ebp-34h] BYREF
  char overrideMessagePrintFormat[12]; // [esp+60h] [ebp-28h] BYREF
  int v22; // [esp+6Ch] [ebp-1Ch]
  int maxSlotNameLength; // [esp+70h] [ebp-18h]

  v22 = logicalName;
  Class_PrintSeparatorLine(logicalName, (int)buf, 61, 82);
  Class_PrintSeparatorLine(v22, (int)buf, 42, 82);
  if ( (*(_BYTE *)(theDefclass + 20) & 4) != 0 )
  {
    v5 = aAbstractDirect;
  }
  else
  {
    Output_Write(v22, (int)aConcreteDirect, v4);
    if ( (*(_BYTE *)(theDefclass + 20) & 8) != 0 )
      v5 = aReactiveDirect;
    else
      v5 = aNonReactiveDir;
  }
  Output_Write(v22, (int)v5, v4);
  Class_PrintNameList(v22, (int)aDirectSupercla, (unsigned __int16 *)(theDefclass + 34));
  Class_PrintNameList(v22, (int)aInheritancePre, (unsigned __int16 *)(theDefclass + 46));
  Class_PrintNameList(v22, (int)aDirectSubclass, (unsigned __int16 *)(theDefclass + 40));
  if ( *(_DWORD *)(theDefclass + 56) )
  {
    maxOverrideMessageLength = 8;
    Class_PrintSeparatorLine(v22, (int)buf, 45, 82);
    v7 = *(_DWORD *)(theDefclass + 72);
    slotIndex = 0;
    maxSlotNameLength = 5;
    if ( v7 )
    {
      slotOffset = 0;
      do
      {
        slotNameLength = strlen(*(const char **)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(theDefclass + 56) + slotOffset) + 8) + 12) + 16))
            + 1;
        if ( (int)(slotNameLength - 1) > maxSlotNameLength )
          maxSlotNameLength = slotNameLength - 1;
        slotDesc = *(_DWORD *)(*(_DWORD *)(theDefclass + 56) + slotOffset);
        if ( (*(_BYTE *)slotDesc & 0x10) == 0 )
        {
          overrideMessageLength = strlen(*(const char **)(*(_DWORD *)(slotDesc + 12) + 16)) + 1;
          if ( (int)(overrideMessageLength - 1) > maxOverrideMessageLength )
            maxOverrideMessageLength = overrideMessageLength - 1;
        }
        ++slotIndex;
        slotOffset += 4;
      }
      while ( slotIndex < *(_DWORD *)(theDefclass + 72) );
    }
    if ( maxSlotNameLength > 16 )
      maxSlotNameLength = 16;
    if ( maxOverrideMessageLength > 12 )
      maxOverrideMessageLength = 12;
    sprintf_(slotNamePrintFormat, "%%-%d.%ds : ", maxSlotNameLength, maxSlotNameLength);
    sprintf_(overrideMessagePrintFormat, "%%-%d.%ds ", maxOverrideMessageLength, maxOverrideMessageLength);
    Class_PrintSlotBasicInfoTable(v22, slotNamePrintFormat, buf, overrideMessagePrintFormat, theDefclass);
    Output_Write(v22, (int)aConstraintInfo, 82);
    Class_PrintSlotConstraintTable(v22, slotNamePrintFormat, v13, buf, theDefclass);
  }
  if ( *(_DWORD *)(theDefclass + 96) )
  {
LABEL_19:
    Class_PrintSeparatorLine(v22, (int)buf, 45, 82);
    Output_Write(v22, (int)aRecognizedMess, v14);
    MessageHandler_CountAndPrintHandlers(v22, (unsigned __int16 *)(theDefclass + 46), v15, 0);
  }
  else
  {
    precedenceIndex = 1;
    precedenceOffset = 4;
    while ( precedenceIndex < *(unsigned __int16 *)(theDefclass + 46) )
    {
      if ( *(_DWORD *)(*(_DWORD *)(precedenceOffset + *(_DWORD *)(theDefclass + 48)) + 96) )
        goto LABEL_19;
      precedenceOffset += 4;
      ++precedenceIndex;
    }
  }
  Class_PrintSeparatorLine(v22, (int)buf, 42, 82);
  return Class_PrintSeparatorLine(v22, (int)buf, 61, 82);
}
// 4D43D9: variable 'v4' is possibly undefined
// 4D4527: variable 'v13' is possibly undefined
// 4D4550: variable 'v14' is possibly undefined
// 4D455E: variable 'v15' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (004D45E0) --------------------------------------------------------
char * Class_SlotAccessModeString(int slotDesc)
{
  char accessFlags; // bl
  char accessFlags2; // cl

  accessFlags = *(_BYTE *)(slotDesc + 1);
  if ( (accessFlags & 8) != 0 && (accessFlags & 0x10) != 0 )
    return aRw_0;
  accessFlags2 = *(_BYTE *)(slotDesc + 1);
  if ( (accessFlags2 & 8) == 0 && (accessFlags2 & 0x10) == 0 )
    return aNil_6;
  if ( (*(_BYTE *)(slotDesc + 1) & 8) != 0 )
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
  int *c1; // [esp+0h] [ebp-10h] BYREF
  int *c2; // [esp+4h] [ebp-Ch] BYREF

  result = Class_ParseTwoClassNameArgs(&c1, &c2, a1);
  if ( result )
    return Class_HasSuperclass((int)c2, (int)c1);
  return result;
}

//----- (004D46A0) --------------------------------------------------------
signed int  Class_SubclassPCommand(double a1)
{
  signed int result; // eax
  int *c1; // [esp+0h] [ebp-10h] BYREF
  int *c2; // [esp+4h] [ebp-Ch] BYREF

  result = Class_ParseTwoClassNameArgs(&c1, &c2, a1);
  if ( result )
    return Class_HasSuperclass((int)c1, (int)c2);
  return result;
}

//----- (004D46F0) --------------------------------------------------------
signed int  Class_SlotExistPCommand(int *a1, double a2)
{
  signed int result; // eax
  int inheritFlag; // esi
  signed int slotDesc; // edi
  int v5; // ecx
  int argValue; // [esp-8h] [ebp-30h] BYREF
  int *v7[6]; // [esp+10h] [ebp-18h] BYREF

  v7[4] = a1;
  result = Class_CheckSlotExists((int)aSlotExistp_0, v7, 1, 0, a2);
  inheritFlag = 0;
  slotDesc = result;
  if ( result )
  {
    if ( Rules_RtnArgCount() == 3 )
    {
      result = Lexer_ParseValueList(3, &argValue, 2, a2);
      if ( !result )
        return result;
      if ( strcmp_(v5, aInherit_0) )
      {
        Parser_ReportError(3, (int)aKeywordInher_0);
        Lexer_ErrorRecover(1);
        return 0;
      }
      inheritFlag = 1;
    }
    if ( v7[0] == *(int **)(slotDesc + 4) )
      return 1;
    else
      return inheritFlag;
  }
  return result;
}
// 4D4762: variable 'v5' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004D47C0) --------------------------------------------------------
signed int  Class_MessageHandlerExistPCommand(double a1)
{
  signed int handlerType; // esi
  signed int result; // eax
  int v3; // ecx
  int *theDefclass; // edi
  int handlerName; // ebp
  _DWORD argValue[2]; // [esp+0h] [ebp-30h] BYREF
  int v7; // [esp+8h] [ebp-28h]

  handlerType = 2;
  result = Lexer_ParseValueList(1, argValue, 2, a1);
  if ( result )
  {
    theDefclass = Class_LookupByQualifiedName(*(_BYTE **)(v7 + 16));
    if ( !theDefclass )
    {
      Class_ReportLookupError(v3, *(_DWORD *)(v7 + 16));
      return 0;
    }
    result = Lexer_ParseValueList(2, argValue, 2, a1);
    if ( result )
    {
      handlerName = v7;
      if ( Rules_RtnArgCount() == 3 )
      {
        result = Lexer_ParseValueList(3, argValue, 2, a1);
        if ( !result )
          return result;
        handlerType = MessageHandler_TypeIndexFromKeyword((int)aMessageHandl_8);
        if ( handlerType == 4 )
        {
          Lexer_ErrorRecover(1);
          return 0;
        }
      }
      result = (signed int)Class_FindMessageHandler(theDefclass, handlerName, handlerType);
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
  int *classBuffer[4]; // [esp-Ch] [ebp-10h] BYREF

  classBuffer[2] = a1;
  result = (_BYTE *)Class_CheckSlotExists((int)aSlotWritable_0, classBuffer, 1, 1, a2);
  if ( result )
    return (_BYTE *)((*result & 0x10) == 0);
  return result;
}

//----- (004D4910) --------------------------------------------------------
_BYTE * Class_SlotInitablePCommand(int *a1, double a2)
{
  _BYTE *result; // eax
  int *classBuffer[4]; // [esp-Ch] [ebp-10h] BYREF

  classBuffer[2] = a1;
  result = (_BYTE *)Class_CheckSlotExists((int)aSlotInitable_0, classBuffer, 1, 1, a2);
  if ( result )
    return (_BYTE *)((*result & 0x10) == 0 || (*result & 0x20) != 0);
  return result;
}

//----- (004D4980) --------------------------------------------------------
signed int  Class_SlotPublicPCommand(int *a1, double a2)
{
  signed int result; // eax
  int *classBuffer[4]; // [esp-Ch] [ebp-10h] BYREF

  classBuffer[2] = a1;
  result = Class_CheckSlotExists((int)aSlotPublicp_0, classBuffer, 0, 1, a2);
  if ( result )
    return (*(_BYTE *)(result + 1) & 4) != 0;
  return result;
}

//----- (004D49E0) --------------------------------------------------------
signed int  Class_SlotDirectAccessPCommand(int *a1, double a2)
{
  signed int result; // eax
  int *classBuffer[4]; // [esp+0h] [ebp-10h] BYREF

  classBuffer[2] = a1;
  result = Class_CheckSlotExists((int)aSlotDirectAc_0, classBuffer, 1, 1, a2);
  if ( result )
    return (*(_BYTE *)(result + 1) & 4) != 0 || classBuffer[0] == *(int **)(result + 4);
  return result;
}

//----- (004D4A50) --------------------------------------------------------
signed int  Class_ClassExistPCommand(int a1, double a2)
{
  signed int result; // eax
  _DWORD argValue[9]; // [esp-8h] [ebp-24h] BYREF

  argValue[7] = a1;
  result = Lexer_ParseValueList(1, argValue, 2, a2);
  if ( result )
    return Class_LookupByQualifiedName(*(_BYTE **)(argValue[2] + 16)) != 0;
  return result;
}

//----- (004D4AA0) --------------------------------------------------------
signed int  Class_ParseTwoClassNameArgs(int **c1, int **c2, double a3)
{
  signed int result; // eax
  int *firstClass; // eax
  int v6; // ecx
  int *secondClass; // eax
  _DWORD argValue[2]; // [esp+0h] [ebp-28h] BYREF
  int v9; // [esp+8h] [ebp-20h]

  result = Lexer_ParseValueList(1, argValue, 2, a3);
  if ( result )
  {
    firstClass = Class_LookupByQualifiedName(*(_BYTE **)(v9 + 16));
    *c1 = firstClass;
    if ( firstClass )
    {
      result = Lexer_ParseValueList(2, argValue, 2, a3);
      if ( !result )
        return result;
      secondClass = Class_LookupByQualifiedName(*(_BYTE **)(v9 + 16));
      *c2 = secondClass;
      if ( secondClass )
        return 1;
    }
    Class_ReportLookupError(v6, *(_DWORD *)(v9 + 16));
    return 0;
  }
  return result;
}
// 4D4B02: variable 'v6' is possibly undefined

//----- (004D4B30) --------------------------------------------------------
signed int  Class_CheckSlotExists(int functionName, int **classBuffer, int inheritFlag, int reportError, double a5)
{
  signed int result; // eax
  unsigned int slotIndex; // eax
  int v11; // ecx
  int *v12; // edx
  int slotDesc; // edi
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx

  result = Class_ParseClassReference(classBuffer, inheritFlag, a5);
  if ( result )
  {
    slotIndex = Instance_ResolveSlotIndex(result, result);
    if ( slotIndex == -1 )
    {
      if ( reportError )
      {
        Instance_ReportNoSuchSlotError(v11, functionName);
        Lexer_ErrorRecover(1);
      }
      return 0;
    }
    else
    {
      v12 = *classBuffer;
      slotDesc = *(_DWORD *)((*classBuffer)[14] + 4 * slotIndex);
      if ( v12 == *(int **)(slotDesc + 4) || inheritFlag )
      {
        return slotDesc;
      }
      else
      {
        Rules_PrintErrorID((int)aClassexm, 1, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInheritedSlot, v14);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(v15 + 16), v15);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFromClass, v16);
        Class_PrintName(*(_DWORD *)(slotDesc + 4), 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIsNotValidForF, v17);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], functionName, v18);
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
int * Class_ResolveSlotBySymbolName(_BYTE *slotName, int inheritFlag)
{
  int *result; // eax
  int v3; // ecx
  unsigned int slotIndex; // eax
  int v5; // ecx

  result = Rules_FindSymbolEntry(slotName);
  if ( result )
  {
    slotIndex = Instance_ResolveSlotIndex(v3, (int)result);
    if ( slotIndex == -1 )
      return 0;
    result = *(int **)(*(_DWORD *)(v5 + 56) + 4 * slotIndex);
    if ( v5 != result[1] && !inheritFlag )
      return 0;
  }
  return result;
}
// 4D4C24: variable 'v3' is possibly undefined
// 4D4C2E: variable 'v5' is possibly undefined

//----- (004D4C50) --------------------------------------------------------
int *__fastcall Class_LookupClassOrReportError(int a1, _BYTE *className)
{
  int *result; // eax
  int v3; // ecx

  result = Class_LookupByQualifiedName(className);
  if ( !result )
  {
    Class_ReportLookupError(v3, (int)className);
    return 0;
  }
  return result;
}
// 4D4C68: variable 'v3' is possibly undefined

//----- (004D4C80) --------------------------------------------------------
signed int  Class_ParseClassNameArg(int functionName, double a2)
{
  signed int result; // eax
  _DWORD argValue[9]; // [esp-8h] [ebp-24h] BYREF

  argValue[7] = functionName;
  result = Lexer_ParseValueList(1, argValue, 2, a2);
  if ( result )
    return *(_DWORD *)(argValue[2] + 16);
  return result;
}

//----- (004D4CB0) --------------------------------------------------------
signed int  Class_PrintClassBrowse(int logicalName, int theDefclass, unsigned int depth)
{
  int v3; // ecx
  unsigned int i; // esi
  int v6; // eax
  int v7; // ecx
  int v8; // ecx
  signed int result; // eax
  int v10; // ecx
  unsigned int subclassIndex; // edi
  int subclassOffset; // esi

  v3 = logicalName;
  for ( i = 0; i < depth; ++i )
    Output_Write(v3, (int)asc_50CE18, v3);
  v6 = Rules_GetConstructNameString(theDefclass);
  Output_Write(v7, v6, v7);
  if ( *(_WORD *)(theDefclass + 34) > 1u )
    Output_Write(v8, (int)asc_50CE1C, v8);
  result = Output_Write(v8, (int)asc_50CE14, v8);
  subclassIndex = 0;
  subclassOffset = 0;
  while ( subclassIndex < *(unsigned __int16 *)(theDefclass + 40) )
  {
    subclassOffset += 4;
    ++subclassIndex;
    result = Class_PrintClassBrowse(v10, *(_DWORD *)(*(_DWORD *)(theDefclass + 42) + subclassOffset - 4), depth + 1);
  }
  return result;
}
// 4D4CCB: variable 'v3' is possibly undefined
// 4D4CEB: variable 'v7' is possibly undefined
// 4D4D24: variable 'v8' is possibly undefined
// 4D4D3B: variable 'v10' is possibly undefined

//----- (004D4D50) --------------------------------------------------------
signed int  Class_PrintSeparatorLine(int logicalName, int buf, char sepChar, int lineWidth)
{
  int bufBase; // esi
  int fillCount; // ecx
  int i; // eax

  bufBase = buf;
  fillCount = lineWidth - 2;
  for ( i = 0; i < fillCount; *(_BYTE *)(buf - 1) = sepChar )
  {
    ++buf;
    ++i;
  }
  *(_BYTE *)(i + bufBase) = 10;
  *(_BYTE *)(bufBase + i + 1) = 0;
  return Output_Write(logicalName, bufBase, fillCount);
}

//----- (004D4DA0) --------------------------------------------------------
int  Class_PrintSlotBasicInfoTable(
        int logicalName,
        const char *slotNamePrintFormat,
        const char *buf,
        const char *overrideMessagePrintFormat,
        int theDefclass)
{
  char *headerFieldLabels; // esi
  const char *v7; // ecx
  const char *v8; // edi
  unsigned int v9; // kr04_4
  char *v10; // edi
  char v11; // al
  char v12; // al
  int v13; // ecx
  int v14; // ecx
  int result; // eax
  int slotDesc; // ebx
  char *multiplicityStr; // esi
  char *v18; // edi
  char v19; // al
  char v20; // al
  const char *v21; // edi
  char *defaultTypeStr; // esi
  char *v23; // edi
  char v24; // al
  char v25; // al
  char *inheritStr; // esi
  char *v27; // edi
  char v28; // al
  char v29; // al
  char *accessStr; // esi
  char *v31; // edi
  char v32; // al
  char v33; // al
  char *storageStr; // esi
  char *v35; // edi
  char v36; // al
  char v37; // al
  char *reactiveStr; // esi
  char *v39; // edi
  char v40; // al
  char v41; // al
  char *compositionStr; // esi
  char *v43; // edi
  char v44; // al
  char v45; // al
  char *visibilityStr; // esi
  char *v47; // edi
  char v48; // al
  char v49; // al
  char *accessModeStr; // edx
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
  char *overrideMessage; // esi
  int v69; // ecx
  int v70; // ecx
  int slotOffset; // [esp+8h] [ebp-18h]
  unsigned int slotIndex; // [esp+Ch] [ebp-14h]

  headerFieldLabels = aFldDefPrpAccSt;
  sprintf_(buf, slotNamePrintFormat, aSlots_0);
  v8 = v7;
  v9 = strlen(v7) + 1;
  v10 = (char *)&v8[v9 - 1];
  do
  {
    v11 = *headerFieldLabels;
    *v10 = *headerFieldLabels;
    if ( !v11 )
      break;
    v12 = headerFieldLabels[1];
    headerFieldLabels += 2;
    v10[1] = v12;
    v10 += 2;
  }
  while ( v12 );
  Output_Write(logicalName, (int)buf, ~v9);
  sprintf_(buf, overrideMessagePrintFormat, aOvrdMsg);
  Output_Write(logicalName, (int)buf, v13);
  Output_Write(logicalName, (int)aSourceS, v14);
  result = theDefclass;
  slotIndex = 0;
  if ( *(_DWORD *)(theDefclass + 72) )
  {
    slotOffset = 0;
    do
    {
      slotDesc = *(_DWORD *)(slotOffset + *(_DWORD *)(theDefclass + 56));
      sprintf_(buf, slotNamePrintFormat, *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(slotDesc + 8) + 12) + 16));
      if ( (*(_BYTE *)slotDesc & 2) != 0 )
        multiplicityStr = aMlt;
      else
        multiplicityStr = aSgl;
      v18 = (char *)&buf[strlen(buf)];
      do
      {
        v19 = *multiplicityStr;
        *v18 = *multiplicityStr;
        if ( !v19 )
          break;
        v20 = multiplicityStr[1];
        multiplicityStr += 2;
        v18[1] = v20;
        v18 += 2;
      }
      while ( v20 );
      v21 = buf;
      if ( (*(_BYTE *)(slotDesc + 1) & 1) != 0 )
      {
        defaultTypeStr = aNil_5;
      }
      else
      {
        if ( (*(_BYTE *)slotDesc & 0x40) != 0 )
          defaultTypeStr = aDyn;
        else
          defaultTypeStr = aStc;
        v21 = buf;
      }
      v23 = (char *)&v21[strlen(v21)];
      do
      {
        v24 = *defaultTypeStr;
        *v23 = *defaultTypeStr;
        if ( !v24 )
          break;
        v25 = defaultTypeStr[1];
        defaultTypeStr += 2;
        v23[1] = v25;
        v23 += 2;
      }
      while ( v25 );
      if ( (*(_BYTE *)slotDesc & 8) != 0 )
        inheritStr = aNil_5;
      else
        inheritStr = aInh;
      v27 = (char *)&buf[strlen(buf)];
      do
      {
        v28 = *inheritStr;
        *v27 = *inheritStr;
        if ( !v28 )
          break;
        v29 = inheritStr[1];
        inheritStr += 2;
        v27[1] = v29;
        v27 += 2;
      }
      while ( v29 );
      if ( (*(_BYTE *)slotDesc & 0x20) != 0 )
      {
        accessStr = aInt_0;
      }
      else if ( (*(_BYTE *)slotDesc & 0x10) != 0 )
      {
        accessStr = aR_5;
      }
      else
      {
        accessStr = aRw;
      }
      v31 = (char *)&buf[strlen(buf)];
      do
      {
        v32 = *accessStr;
        *v31 = *accessStr;
        if ( !v32 )
          break;
        v33 = accessStr[1];
        accessStr += 2;
        v31[1] = v33;
        v31 += 2;
      }
      while ( v33 );
      if ( (*(_BYTE *)slotDesc & 1) != 0 )
        storageStr = aShr;
      else
        storageStr = aLcl;
      v35 = (char *)&buf[strlen(buf)];
      do
      {
        v36 = *storageStr;
        *v35 = *storageStr;
        if ( !v36 )
          break;
        v37 = storageStr[1];
        storageStr += 2;
        v35[1] = v37;
        v35 += 2;
      }
      while ( v37 );
      if ( (*(_BYTE *)(slotDesc + 1) & 2) != 0 )
        reactiveStr = aRct;
      else
        reactiveStr = aNil_5;
      v39 = (char *)&buf[strlen(buf)];
      do
      {
        v40 = *reactiveStr;
        *v39 = *reactiveStr;
        if ( !v40 )
          break;
        v41 = reactiveStr[1];
        reactiveStr += 2;
        v39[1] = v41;
        v39 += 2;
      }
      while ( v41 );
      if ( (*(_BYTE *)slotDesc & 4) != 0 )
        compositionStr = aCmp;
      else
        compositionStr = aExc;
      v43 = (char *)&buf[strlen(buf)];
      do
      {
        v44 = *compositionStr;
        *v43 = *compositionStr;
        if ( !v44 )
          break;
        v45 = compositionStr[1];
        compositionStr += 2;
        v43[1] = v45;
        v43 += 2;
      }
      while ( v45 );
      if ( (*(_BYTE *)(slotDesc + 1) & 4) != 0 )
        visibilityStr = aPub;
      else
        visibilityStr = aPrv;
      v47 = (char *)&buf[strlen(buf)];
      do
      {
        v48 = *visibilityStr;
        *v47 = *visibilityStr;
        if ( !v48 )
          break;
        v49 = visibilityStr[1];
        visibilityStr += 2;
        v47[1] = v49;
        v47 += 2;
      }
      while ( v49 );
      accessModeStr = Class_SlotAccessModeString(slotDesc);
      if ( !accessModeStr[1] )
      {
        v51 = asc_50CEE8;
        v52 = (char *)&buf[strlen(buf)];
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
      v55 = accessModeStr;
      v56 = (char *)&buf[strlen(buf)];
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
      if ( !accessModeStr[1] || !accessModeStr[2] )
      {
        v59 = asc_50CEE8;
        v60 = (char *)&buf[strlen(buf)];
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
      v64 = strlen(buf) + 1;
      v65 = (char *)&buf[v64 - 1];
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
      Output_Write(logicalName, (int)buf, ~v64);
      if ( (*(_BYTE *)slotDesc & 0x10) != 0 )
        overrideMessage = aNil_6;
      else
        overrideMessage = *(char **)(*(_DWORD *)(slotDesc + 12) + 16);
      sprintf_(buf, overrideMessagePrintFormat, overrideMessage);
      Output_Write(logicalName, (int)buf, 0);
      Class_PrintSlotSourceClasses(logicalName, *(_DWORD *)(*(_DWORD *)(slotDesc + 8) + 12), v69, (unsigned __int16 *)(*(_DWORD *)(slotDesc + 4) + 46), 1);
      Output_Write(logicalName, (int)asc_50CE14, v70);
      slotOffset += 4;
      result = ++slotIndex;
    }
    while ( slotIndex < *(_DWORD *)(theDefclass + 72) );
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
signed int  Class_PrintSlotSourceClasses(int logicalName, int slotName, int classIndex, unsigned __int16 *precedenceList, int a5)
{
  _BYTE *foundSlot; // eax
  int v9; // ecx
  _BYTE *slotDesc; // edx
  int v12; // ecx

  while ( 1 )
  {
    if ( classIndex == *precedenceList )
      return 0;
    foundSlot = (_BYTE *)Class_FindSlotBySymbol(*(_DWORD *)(*(_DWORD *)(precedenceList + 1) + 4 * classIndex), slotName);
    slotDesc = foundSlot;
    if ( foundSlot )
    {
      if ( (*foundSlot & 8) == 0 || v9 )
        break;
    }
    ++classIndex;
  }
  if ( (*slotDesc & 4) != 0 )
  {
    if ( Class_PrintSlotSourceClasses(logicalName, slotName, classIndex + 1, (int)precedenceList, 0) )
      Output_Write(logicalName, (int)asc_50CEE8, v12);
  }
  Class_PrintName(*(_DWORD *)(*(_DWORD *)(precedenceList + 1) + 4 * classIndex), 0);
  return 1;
}
// 4D5240: variable 'v12' is possibly undefined
// 4D5265: variable 'v9' is possibly undefined

//----- (004D5270) --------------------------------------------------------
signed int  Class_PrintSlotConstraintTable(
        int logicalName,
        const char *slotNamePrintFormat,
        int bufferSize,
        const char *buf,
        signed int theDefclass)
{
  char *srcPtr; // esi
  unsigned int bufLen; // kr04_4
  char *dstPtr; // edi
  char v8; // al
  char v9; // al
  signed int result; // eax
  int slotDesc; // eax
  char *theConstraint; // ebp
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
  int slotIndex; // [esp+Ch] [ebp-18h]
  int i; // [esp+10h] [ebp-14h]

  srcPtr = aSymStrInnInaEx;
  sprintf_(buf, slotNamePrintFormat, aSlots_0);
  bufLen = strlen(buf) + 1;
  dstPtr = (char *)&buf[bufLen - 1];
  do
  {
    v8 = *srcPtr;
    *dstPtr = *srcPtr;
    if ( !v8 )
      break;
    v9 = srcPtr[1];
    srcPtr += 2;
    dstPtr[1] = v9;
    dstPtr += 2;
  }
  while ( v9 );
  Output_Write(logicalName, (int)buf, ~bufLen);
  result = theDefclass;
  slotIndex = 0;
  if ( *(_DWORD *)(theDefclass + 72) )
  {
    for ( i = 0; ; i += 4 )
    {
      slotDesc = *(_DWORD *)(i + *(_DWORD *)(theDefclass + 56));
      theConstraint = *(char **)(slotDesc + 20);
      sprintf_(buf, slotNamePrintFormat, *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(slotDesc + 8) + 12) + 16));
      if ( theConstraint )
        break;
      IO_OpenStringDestination((int)aDescribeClas_1, (const void *)v13, bufferSize);
      Output_Write((int)aDescribeClas_1, (int)aRngOo__Oo, v14);
      if ( (**(_BYTE **)(i + *(_DWORD *)(theDefclass + 56)) & 2) != 0 )
      {
        v16 = aCrd0__Oo;
LABEL_9:
        Output_Write((int)aDescribeClas_1, (int)v16, v15);
      }
LABEL_10:
      Output_Write((int)aDescribeClas_1, (int)asc_50CE14, v15);
      IO_CloseStringRouter((int)aDescribeClas_1);
      result = Output_Write(logicalName, v17, v18);
      if ( (unsigned int)++slotIndex >= *(_DWORD *)(theDefclass + 72) )
        return result;
    }
    v19 = Class_ConstraintTypeMarker(theConstraint, *(_DWORD *)theConstraint << 30 >> 31, *(_DWORD *)theConstraint << 21 >> 31);
    v20 = (char *)&buf[strlen(buf)];
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
    v23 = Class_ConstraintTypeMarker(theConstraint, *(_DWORD *)theConstraint << 29 >> 31, *(_DWORD *)theConstraint << 20 >> 31);
    v24 = (char *)&buf[strlen(buf)];
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
    v27 = Class_ConstraintTypeMarker(theConstraint, *(_DWORD *)theConstraint << 26 >> 31, *(_DWORD *)theConstraint << 17 >> 31);
    v28 = (char *)&buf[strlen(buf)];
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
    v31 = Class_ConstraintTypeMarker(theConstraint, *(_DWORD *)theConstraint << 25 >> 31, 0);
    v32 = (char *)&buf[strlen(buf)];
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
    v35 = Class_ConstraintTypeMarker(theConstraint, *(_DWORD *)theConstraint << 24 >> 31, 0);
    v36 = (char *)&buf[strlen(buf)];
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
    v39 = Class_ConstraintTypeMarker(theConstraint, *(_DWORD *)theConstraint << 23 >> 31, 0);
    v40 = (char *)&buf[strlen(buf)];
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
    v43 = Class_ConstraintTypeMarker(theConstraint, *(_DWORD *)theConstraint << 27 >> 31, *(_DWORD *)theConstraint << 18 >> 31);
    v44 = (char *)&buf[strlen(buf)];
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
    v47 = Class_ConstraintTypeMarker(theConstraint, *(_DWORD *)theConstraint << 28 >> 31, *(_DWORD *)theConstraint << 19 >> 31);
    v48 = (char *)&buf[strlen(buf)];
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
    IO_OpenStringDestination((int)aDescribeClas_1, &buf[strlen(buf)], bufferSize - (strlen(buf) + 1));
    v51 = *theConstraint;
    if ( (*theConstraint & 0x10) != 0 || (v51 & 8) != 0 || (v51 & 1) != 0 )
    {
      Output_Write((int)aDescribeClas_1, (int)aRng, v15);
      Rules_PrintFieldExprList((signed int)aDescribeClas_1, *(__int16 **)(theConstraint + 10));
      Output_Write((int)aDescribeClas_1, (int)a___0, v52);
      Rules_PrintFieldExprList((signed int)aDescribeClas_1, *(__int16 **)(theConstraint + 14));
      Output_Write((int)aDescribeClas_1, (int)asc_50CF34, v53);
    }
    if ( (**(_BYTE **)(i + *(_DWORD *)(theDefclass + 56)) & 2) == 0 )
      goto LABEL_10;
    Output_Write((int)aDescribeClas_1, (int)aCrd, v15);
    Rules_PrintFieldExprList((signed int)aDescribeClas_1, *(__int16 **)(theConstraint + 18));
    Output_Write((int)aDescribeClas_1, (int)a___0, v54);
    Rules_PrintFieldExprList((signed int)aDescribeClas_1, *(__int16 **)(theConstraint + 22));
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
char * Class_ConstraintTypeMarker(_BYTE *theConstraint, int typeAllowed, int typeRestricted)
{
  if ( !typeAllowed && (*theConstraint & 1) == 0 )
    return asc_50CF94;
  if ( typeRestricted || (theConstraint[1] & 2) != 0 )
    return asc_50CF84;
  return asc_50CF8C;
}

//----- (004D56A0) --------------------------------------------------------
unsigned int  Class_ClassAbstractPCommand(int a1, double a2)
{
  unsigned int result; // eax
  int *theDefclass; // eax
  int v4; // ecx
  int argValue; // [esp-8h] [ebp-24h] BYREF
  int argDataObject; // [esp+0h] [ebp-1Ch]
  int v7; // [esp+14h] [ebp-8h]

  v7 = a1;
  result = Lexer_ParseValueList(1, &argValue, 2, a2);
  if ( result )
  {
    theDefclass = Class_LookupByQualifiedName(*(_BYTE **)(argDataObject + 16));
    if ( theDefclass )
    {
      return (unsigned int)(theDefclass[5] << 29) >> 31;
    }
    else
    {
      Class_ReportLookupError(v4, *(_DWORD *)(argDataObject + 16));
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
  int *theDefclass; // eax
  int v4; // ecx
  int argValue; // [esp-8h] [ebp-24h] BYREF
  int argDataObject; // [esp+0h] [ebp-1Ch]
  int v7; // [esp+14h] [ebp-8h]

  v7 = a1;
  result = Lexer_ParseValueList(1, &argValue, 2, a2);
  if ( result )
  {
    theDefclass = Class_LookupByQualifiedName(*(_BYTE **)(argDataObject + 16));
    if ( theDefclass )
    {
      return (unsigned int)(theDefclass[5] << 28) >> 31;
    }
    else
    {
      Class_ReportLookupError(v4, *(_DWORD *)(argDataObject + 16));
      return 0;
    }
  }
  return result;
}
// 4D5763: variable 'v4' is possibly undefined

//----- (004D5780) --------------------------------------------------------
int * Class_ParseClassNameAndInheritFlag(int functionName, _DWORD *inheritFlag, double a3)
{
  int *result; // eax
  int v6; // ecx
  int *theDefclass; // ebp
  int secondArgValue; // ecx
  _DWORD argValue[2]; // [esp+0h] [ebp-2Ch] BYREF
  int argDataObject; // [esp+8h] [ebp-24h]

  *inheritFlag = 0;
  if ( Rules_RtnArgCount() )
  {
    result = (int *)Lexer_ParseValueList(1, argValue, 2, a3);
    if ( result )
    {
      theDefclass = Class_LookupByQualifiedName(*(_BYTE **)(argDataObject + 16));
      if ( theDefclass )
      {
        if ( Rules_RtnArgCount() == 2 )
        {
          result = (int *)Lexer_ParseValueList(2, argValue, 2, a3);
          if ( result )
          {
            if ( !strcmp_(secondArgValue, aInherit_1) )
            {
              *inheritFlag = 1;
              return theDefclass;
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
          return theDefclass;
        }
      }
      else
      {
        Class_ReportLookupError(v6, *(_DWORD *)(argDataObject + 16));
        return 0;
      }
    }
  }
  else
  {
    Rules_ExpectedCountError(functionName, 1);
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
  int *theDefclass; // eax
  _DWORD *returnValue; // ecx
  unsigned int v5[3]; // [esp+0h] [ebp-Ch] BYREF

  v5[2] = a1;
  theDefclass = Class_ParseClassNameAndInheritFlag((int)aClassSlots_0, v5, a2);
  if ( theDefclass )
    return Class_SlotsFunction((int)theDefclass, returnValue, v5[0]);
  else
    return Rules_SetMultifieldErrorValue((int)returnValue);
}
// 4D5889: variable 'v3' is possibly undefined

//----- (004D58B0) --------------------------------------------------------
__int16  Class_ClassSuperclassesCommand(int a1, double a2)
{
  int *theDefclass; // eax
  _DWORD *returnValue; // ecx
  int v5[3]; // [esp+0h] [ebp-Ch] BYREF

  v5[2] = a1;
  theDefclass = Class_ParseClassNameAndInheritFlag((int)aClassSupercl_0, v5, a2);
  if ( theDefclass )
    return Class_SuperclassesFunction((int)theDefclass, returnValue, v5[0]);
  else
    return (unsigned __int16)Rules_SetMultifieldErrorValue((int)returnValue);
}
// 4D58C9: variable 'v3' is possibly undefined

//----- (004D58F0) --------------------------------------------------------
void  Class_ClassSubclassesCommand(int a1, double a2)
{
  int *theDefclass; // eax
  int returnValue; // ecx
  int v4[3]; // [esp+0h] [ebp-Ch] BYREF

  v4[2] = a1;
  theDefclass = Class_ParseClassNameAndInheritFlag((int)aClassSubclas_0, v4, a2);
  if ( theDefclass )
    Class_SubclassesFunction((int)theDefclass, v4[0]);
  else
    Rules_SetMultifieldErrorValue(returnValue);
}
// 4D5909: variable 'v3' is possibly undefined

//----- (004D5930) --------------------------------------------------------
_DWORD * Class_GetDefmessageHandlerListCommand(int a1, double a2)
{
  int *theDefclass; // eax
  int returnValue; // ecx
  int v6[4]; // [esp+0h] [ebp-10h] BYREF

  v6[2] = a1;
  if ( !Rules_RtnArgCount() )
    return (_DWORD *)Class_MessageHandlerListFunction(0, 0);
  theDefclass = Class_ParseClassNameAndInheritFlag((int)aGetDefmessag_0, v6, a2);
  if ( theDefclass )
    return (_DWORD *)Class_MessageHandlerListFunction((int)theDefclass, v6[0]);
  else
    return Rules_SetMultifieldErrorValue(returnValue);
}
// 4D5953: variable 'v4' is possibly undefined

//----- (004D5980) --------------------------------------------------------
_DWORD * Class_SlotFacetsCommand(int a1, int *result, double a3)
{
  return Class_DispatchSlotQuery(a1, result, (int (*)(void))Class_SlotFacetsQuery, a3);
}

//----- (004D59A0) --------------------------------------------------------
_DWORD * Class_SlotSourcesCommand(int a1, int *result, double a3)
{
  return Class_DispatchSlotQuery(a1, result, (int (*)(void))Class_SlotSourcesQuery, a3);
}

//----- (004D59C0) --------------------------------------------------------
_DWORD * Class_SlotTypesCommand(int a1, int *result, double a3)
{
  return Class_DispatchSlotQuery(a1, result, (int (*)(void))Class_SlotTypesQuery, a3);
}

//----- (004D59E0) --------------------------------------------------------
_DWORD * Class_SlotAllowedValuesFunction(int a1, int *result, double a3)
{
  return Class_DispatchSlotQuery(a1, result, (int (*)(void))Class_SlotAllowedValuesQuery, a3);
}

//----- (004D5A00) --------------------------------------------------------
_DWORD * Class_SlotRangeFunction(int a1, int *result, double a3)
{
  return Class_DispatchSlotQuery(a1, result, (int (*)(void))Class_SlotRangeQuery, a3);
}

//----- (004D5A20) --------------------------------------------------------
_DWORD * Class_SlotCardinalityFunction(int a1, int *result, double a3)
{
  return Class_DispatchSlotQuery(a1, result, (int (*)(void))Class_SlotCardinalityQuery, a3);
}

//----- (004D5A40) --------------------------------------------------------
int  Class_IsAbstract(int theDefclass)
{
  return *(_DWORD *)(theDefclass + 20) << 29 >> 31;
}

//----- (004D5A60) --------------------------------------------------------
_DWORD * Class_SlotsFunction(int theDefclass, _DWORD *returnValue, unsigned int inheritFlag)
{
  unsigned int v3; // esi
  signed int slotCount; // ebx
  _DWORD *result; // eax
  int returnObj; // edx
  _DWORD *classPtr; // ecx
  unsigned int templateIndex; // ebx
  int templateOffset; // esi
  int slotTemplate; // edi
  int slotOffset; // ebx
  int slotName; // [esp+0h] [ebp-18h]

  v3 = inheritFlag;
  if ( inheritFlag )
    slotCount = *(_DWORD *)(theDefclass + 72);
  else
    slotCount = *(_DWORD *)(theDefclass + 64);
  returnValue[1] = 4;
  returnValue[4] = slotCount - 1;
  returnValue[3] = 0;
  result = Rules_CreateEphemeralMultifield(slotCount);
  *(_DWORD *)(returnObj + 8) = result;
  if ( slotCount )
  {
    if ( v3 )
    {
      templateIndex = 0;
      if ( classPtr[18] )
      {
        templateOffset = 0;
        result = 0;
        do
        {
          *(_WORD *)((char *)result + *(_DWORD *)(returnObj + 8) + 14) = 2;
          slotTemplate = *(_DWORD *)(classPtr[14] + templateOffset);
          templateOffset += 4;
          ++templateIndex;
          *(_DWORD *)((char *)result + *(_DWORD *)(returnObj + 8) + 16) = *(_DWORD *)(*(_DWORD *)(slotTemplate + 8) + 12);
          result = (_DWORD *)((char *)result + 6);
        }
        while ( templateIndex < classPtr[18] );
      }
    }
    else if ( classPtr[16] )
    {
      slotOffset = 0;
      result = 0;
      do
      {
        *(_WORD *)((char *)result + *(_DWORD *)(returnObj + 8) + 14) = 2;
        slotName = *(_DWORD *)(classPtr[13] + slotOffset + 8);
        slotOffset += 44;
        *(_DWORD *)((char *)result + *(_DWORD *)(returnObj + 8) + 16) = *(_DWORD *)(slotName + 12);
        ++v3;
        result = (_DWORD *)((char *)result + 6);
      }
      while ( v3 < classPtr[16] );
    }
  }
  return result;
}
// 4D5A91: variable 'v6' is possibly undefined
// 4D5A9C: variable 'v7' is possibly undefined

//----- (004D5B40) --------------------------------------------------------
int  Class_MessageHandlerListFunction(int theDefclass, int inheritFlag)
{
  int currentClass; // ebp
  _DWORD *returnValue; // ecx
  int i; // ebx
  int precedenceCount; // edx
  int v7; // edi
  int v8; // eax
  int *precedenceList; // edx
  int precClass; // esi
  _DWORD *multifield; // eax
  int v12; // ecx
  int result; // eax
  int v14; // eax
  int sourceClass; // ebx
  int v16; // edx
  int v17; // edx
  unsigned int handlerIndex; // edi
  int handlerOffset; // esi
  int classNameSymbol; // eax
  int v21; // ecx
  int v22; // edx
  signed int *handlerTypeSymbol; // eax
  int v24; // edx
  int fieldOffset; // [esp+4h] [ebp-38h]
  int savedNext; // [esp+10h] [ebp-2Ch]
  int firstClass; // [esp+14h] [ebp-28h]
  int fieldCount; // [esp+18h] [ebp-24h]
  int precedenceEnd; // [esp+1Ch] [ebp-20h]
  int j; // [esp+20h] [ebp-1Ch]
  int fieldsFilled; // [esp+24h] [ebp-18h]
  int precedenceOffset; // [esp+28h] [ebp-14h]

  if ( theDefclass )
  {
    currentClass = theDefclass;
    savedNext = Class_GetNextRecord(theDefclass);
    Rules_SetConstructNextInModule(theDefclass, 0);
  }
  else
  {
    inheritFlag = 0;
    currentClass = Class_GetNextRecord(0);
    savedNext = Class_GetNextRecord(currentClass);
  }
  firstClass = currentClass;
  for ( i = 0; currentClass; currentClass = Class_GetNextRecord(currentClass) )
  {
    if ( inheritFlag )
      precedenceCount = *(unsigned __int16 *)(currentClass + 46);
    else
      precedenceCount = 1;
    v7 = precedenceCount;
    v8 = 0;
    if ( precedenceCount > 0 )
    {
      precedenceList = *(int **)(currentClass + 48);
      do
      {
        precClass = *precedenceList++;
        ++v8;
        i += *(_DWORD *)(precClass + 96);
      }
      while ( v8 < v7 );
    }
  }
  returnValue[1] = 4;
  returnValue[3] = 0;
  fieldCount = 3 * i;
  returnValue[4] = 3 * i - 1;
  multifield = Rules_CreateEphemeralMultifield(3 * i);
  *(_DWORD *)(v12 + 8) = multifield;
  result = firstClass;
  fieldsFilled = 0;
  for ( j = firstClass; result; j = result )
  {
    if ( inheritFlag )
      v14 = *(unsigned __int16 *)(j + 46);
    else
      v14 = 1;
    if ( v14 > 0 )
    {
      precedenceOffset = 0;
      precedenceEnd = 4 * v14;
      do
      {
        sourceClass = *(_DWORD *)(precedenceOffset + *(_DWORD *)(j + 48));
        if ( inheritFlag )
          v16 = fieldCount - 3 * *(_DWORD *)(sourceClass + 96) - fieldsFilled;
        else
          v16 = fieldsFilled;
        v17 = v16 + 1;
        handlerIndex = 0;
        if ( *(_DWORD *)(sourceClass + 96) )
        {
          handlerOffset = 0;
          do
          {
            fieldOffset = 6 * (v17 - 1);
            *(_WORD *)(*(_DWORD *)(v12 + 8) + fieldOffset + 14) = 2;
            classNameSymbol = Rules_GetConstructNameSymbol(sourceClass);
            *(_DWORD *)(fieldOffset + *(_DWORD *)(v21 + 8) + 16) = classNameSymbol;
            *(_WORD *)(*(_DWORD *)(v21 + 8) + 6 * v22 + 14) = 2;
            *(_DWORD *)(6 * v22 + *(_DWORD *)(v21 + 8) + 16) = *(_DWORD *)(handlerOffset + *(_DWORD *)(sourceClass + 88) + 8);
            *(_WORD *)(6 * (v22 + 1) + *(_DWORD *)(v21 + 8) + 14) = 2;
            handlerTypeSymbol = Str_Intern(g_MessageHandlerTypeNames[*(_DWORD *)(handlerOffset + *(_DWORD *)(sourceClass + 88)) << 29 >> 30], v21);
            ++handlerIndex;
            handlerOffset += 36;
            *(_DWORD *)(6 * (v24 - 1) + *(_DWORD *)(v12 + 8) + 16) = handlerTypeSymbol;
            v17 = v24 + 1;
          }
          while ( handlerIndex < *(_DWORD *)(sourceClass + 96) );
        }
        fieldsFilled += 3 * *(_DWORD *)(sourceClass + 96);
        precedenceOffset += 4;
      }
      while ( precedenceOffset < precedenceEnd );
    }
    result = Class_GetNextRecord(j);
  }
  if ( firstClass )
    return Rules_SetConstructNextInModule(firstClass, savedNext);
  return result;
}
// 4D5BB0: variable 'v4' is possibly undefined
// 4D5BD3: variable 'v12' is possibly undefined
// 4D5C61: variable 'v21' is possibly undefined
// 4D5C6F: variable 'v22' is possibly undefined
// 4D5CF4: variable 'v24' is possibly undefined
// 51AD3C: using guessed type char *off_51AD3C[4];

//----- (004D5DC0) --------------------------------------------------------
__int16  Class_SuperclassesFunction(int theDefclass, _DWORD *result, int inheritFlag)
{
  int startOffset; // edx
  unsigned __int16 *classLinks; // edi
  signed int linkCount; // eax
  _DWORD *v7; // eax
  unsigned int v8; // edx
  int lastIndex; // ecx
  unsigned int linkIndex; // ecx
  int linkOffset; // ebx
  int fieldOffset; // edx
  int v13; // edx
  int fieldAddr; // ebp
  int v15; // ecx

  if ( inheritFlag )
  {
    startOffset = 1;
    classLinks = (unsigned __int16 *)(theDefclass + 46);
  }
  else
  {
    classLinks = (unsigned __int16 *)(theDefclass + 34);
    startOffset = 0;
  }
  result[1] = 4;
  result[3] = 0;
  linkCount = *classLinks - startOffset;
  result[4] = linkCount - 1;
  v7 = Rules_CreateEphemeralMultifield(linkCount);
  lastIndex = result[4];
  result[2] = v7;
  if ( lastIndex != -1 )
  {
    linkIndex = v8;
    linkOffset = 4 * v8;
    fieldOffset = 0;
    LOWORD(v7) = *classLinks;
    if ( linkIndex < *classLinks )
    {
      do
      {
        *(_WORD *)(fieldOffset + result[2] + 14) = 2;
        v7 = (_DWORD *)Rules_GetConstructNameSymbol(*(_DWORD *)(linkOffset + *(_DWORD *)(classLinks + 1)));
        linkOffset += 4;
        fieldAddr = v13 + result[2];
        fieldOffset = v13 + 6;
        *(_DWORD *)(fieldAddr + 16) = v7;
        LOWORD(v7) = *classLinks;
      }
      while ( v15 + 1 < (unsigned int)*classLinks );
    }
  }
  return (__int16)v7;
}
// 4D5DFD: variable 'v8' is possibly undefined
// 4D5E39: variable 'v13' is possibly undefined
// 4D5E3B: variable 'v15' is possibly undefined

//----- (004D5E50) --------------------------------------------------------
void  Class_SubclassesFunction(int theDefclass, int inheritFlag)
{
  signed int traversalID; // eax
  _DWORD *returnValue; // ecx
  signed int subclassCount; // edx
  _DWORD *multifield; // eax
  int v7; // ecx
  int v8; // edx
  signed int secondTraversalID; // eax
  int v10; // ecx

  traversalID = Class_NewTraversalID();
  if ( traversalID != -1 )
  {
    Class_CountSubclasses(theDefclass, inheritFlag, traversalID);
    Class_ReleaseTraversalID();
    returnValue[1] = 4;
    returnValue[4] = subclassCount - 1;
    returnValue[3] = 0;
    multifield = Rules_CreateEphemeralMultifield(subclassCount);
    *(_DWORD *)(v7 + 8) = multifield;
    if ( v8 )
    {
      secondTraversalID = Class_NewTraversalID();
      if ( secondTraversalID != -1 )
      {
        Class_CollectSubclassNames(*(_DWORD *)(v10 + 8), 1, inheritFlag, theDefclass, secondTraversalID);
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
signed int * Class_SlotFacetsQuery(int theDefclass, _BYTE *slotName, int a3)
{
  signed int *result; // eax
  _BYTE *slotDesc; // ecx
  int i; // eax
  char *cardinalityStr; // eax
  _BYTE *v7; // ecx
  char *defaultModeStr; // eax
  _BYTE *v9; // ecx
  char *inheritStr; // eax
  _BYTE *v11; // ecx
  char *accessStr; // eax
  _BYTE *v13; // ecx
  char *sharingStr; // eax
  int v15; // ecx
  char *reactiveStr; // eax
  _BYTE *v17; // ecx
  char *compositeStr; // eax
  int v19; // ecx
  char *visibilityStr; // eax
  int v21; // ecx
  char *accessorStr; // eax
  int v23; // ecx
  int v24; // ecx

  result = (signed int *)Class_ResolveNamedSlot(a3, theDefclass, slotName);
  if ( result )
  {
    *(_DWORD *)(a3 + 16) = 9;
    *(_DWORD *)(a3 + 8) = Rules_CreateEphemeralMultifield(10);
    for ( i = 0; i != 60; *(_WORD *)(*(_DWORD *)(a3 + 8) + i + 8) = 2 )
      i += 6;
    if ( (*slotDesc & 2) != 0 )
      cardinalityStr = aMlt_0;
    else
      cardinalityStr = aSgl_0;
    *(_DWORD *)(*(_DWORD *)(a3 + 8) + 16) = Str_Intern(cardinalityStr, (int)slotDesc);
    if ( (v7[1] & 1) != 0 )
    {
      defaultModeStr = aNil_7;
    }
    else if ( (*v7 & 0x40) != 0 )
    {
      defaultModeStr = aDyn_0;
    }
    else
    {
      defaultModeStr = aStc_0;
    }
    *(_DWORD *)(*(_DWORD *)(a3 + 8) + 22) = Str_Intern(defaultModeStr, (int)v7);
    if ( (*v9 & 8) != 0 )
      inheritStr = aNil_7;
    else
      inheritStr = aInh_0;
    *(_DWORD *)(*(_DWORD *)(a3 + 8) + 28) = Str_Intern(inheritStr, (int)v9);
    if ( (*v11 & 0x20) != 0 )
    {
      accessStr = aInt_1;
    }
    else if ( (*v11 & 0x10) != 0 )
    {
      accessStr = aR_9;
    }
    else
    {
      accessStr = aRw_1;
    }
    *(_DWORD *)(*(_DWORD *)(a3 + 8) + 34) = Str_Intern(accessStr, (int)v11);
    if ( (*v13 & 1) != 0 )
      sharingStr = aShr_0;
    else
      sharingStr = aLcl_0;
    *(_DWORD *)(*(_DWORD *)(a3 + 8) + 40) = Str_Intern(sharingStr, (int)v13);
    if ( (*(_BYTE *)(v15 + 1) & 2) != 0 )
      reactiveStr = aRct_0;
    else
      reactiveStr = aNil_7;
    *(_DWORD *)(*(_DWORD *)(a3 + 8) + 46) = Str_Intern(reactiveStr, v15);
    if ( (*v17 & 4) != 0 )
      compositeStr = aCmpFacet;
    else
      compositeStr = aExcFacet;
    *(_DWORD *)(*(_DWORD *)(a3 + 8) + 52) = Str_Intern(compositeStr, (int)v17);
    if ( (*(_BYTE *)(v19 + 1) & 4) != 0 )
      visibilityStr = aPubFacet;
    else
      visibilityStr = aPrvFacet;
    *(_DWORD *)(*(_DWORD *)(a3 + 8) + 58) = Str_Intern(visibilityStr, v19);
    accessorStr = Class_SlotAccessModeString(v21);
    *(_DWORD *)(*(_DWORD *)(a3 + 8) + 64) = Str_Intern(accessorStr, v23);
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
_DWORD * Class_SlotSourcesQuery(int theDefclass, _BYTE *slotName, int a3)
{
  _DWORD *result; // eax
  _DWORD *freeNode; // edx
  signed int classCount; // ecx
  int *listNode; // eax
  int ownerClass; // edx
  int precedenceIndex; // esi
  int i; // edi
  int classRecord; // eax
  int sourceClass; // ebx
  _BYTE *foundSlot; // eax
  _BYTE *inheritedSlot; // ebp
  _DWORD *v14; // edx
  int *newNode; // eax
  int *curEntry; // ebx
  _DWORD *multifield; // eax
  int v18; // edx
  int fieldOffset; // edx
  int classNameSymbol; // eax
  int v21; // edx
  _DWORD *slotDesc; // [esp+4h] [ebp-10h]
  int *nameList; // [esp+8h] [ebp-Ch]

  result = (_DWORD *)Class_ResolveNamedSlot(a3, theDefclass, slotName);
  slotDesc = result;
  if ( result )
  {
    freeNode = *(_DWORD **)(g_ClipsMemoryTable + 32);
    classCount = 1;
    if ( freeNode )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
      *(_DWORD *)(g_ClipsMemoryTable + 32) = *freeNode;
      listNode = (int *)g_ClipsMemFreeListTemp;
    }
    else
    {
      listNode = (int *)Mem_HeapAllocWithRetry((_DWORD *)8);
    }
    ownerClass = slotDesc[1];
    listNode[1] = 0;
    nameList = listNode;
    *listNode = ownerClass;
    if ( (*(_BYTE *)slotDesc & 4) != 0 )
    {
      precedenceIndex = 1;
      for ( i = 4; ; i += 4 )
      {
        classRecord = slotDesc[1];
        if ( precedenceIndex >= *(unsigned __int16 *)(classRecord + 46) )
          break;
        sourceClass = *(_DWORD *)(i + *(_DWORD *)(classRecord + 48));
        foundSlot = (_BYTE *)Class_FindSlotBySymbol(sourceClass, *(_DWORD *)(slotDesc[2] + 12));
        inheritedSlot = foundSlot;
        if ( foundSlot )
        {
          if ( (*foundSlot & 8) == 0 )
          {
            v14 = *(_DWORD **)(g_ClipsMemoryTable + 32);
            if ( v14 )
            {
              g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
              *(_DWORD *)(g_ClipsMemoryTable + 32) = *v14;
              newNode = (int *)g_ClipsMemFreeListTemp;
            }
            else
            {
              newNode = (int *)Mem_HeapAllocWithRetry((_DWORD *)8);
            }
            *newNode = sourceClass;
            newNode[1] = (int)nameList;
            ++classCount;
            nameList = newNode;
            if ( (*inheritedSlot & 4) == 0 )
              break;
          }
        }
        ++precedenceIndex;
      }
    }
    *(_DWORD *)(a3 + 16) = classCount - 1;
    curEntry = nameList;
    multifield = Rules_CreateEphemeralMultifield(classCount);
    *(_DWORD *)(v18 + 8) = multifield;
    if ( nameList )
    {
      fieldOffset = 0;
      do
      {
        *(_WORD *)(fieldOffset + *(_DWORD *)(a3 + 8) + 14) = 2;
        classNameSymbol = Rules_GetConstructNameSymbol(*curEntry);
        *(_DWORD *)(v21 + *(_DWORD *)(a3 + 8) + 16) = classNameSymbol;
        fieldOffset = v21 + 6;
        curEntry = (int *)curEntry[1];
      }
      while ( curEntry );
    }
    return Mem_ReturnListToFreePool(nameList);
  }
  return result;
}
// 4D6177: variable 'v5' is possibly undefined
// 4D619E: variable 'v18' is possibly undefined
// 4D61C3: variable 'v21' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004D6210) --------------------------------------------------------
_DWORD * Class_SlotTypesQuery(int theDefclass, _BYTE *slotName, int a3)
{
  _DWORD *result; // eax
  _DWORD *theConstraint; // edx
  signed int typeCount; // edx
  int bitIndex; // ebx
  int v8; // edx
  int typeIndex; // edi
  int fieldOffset; // esi
  int lastFieldOffset; // [esp+0h] [ebp-18h]
  char typeBits0; // [esp+4h] [ebp-14h]
  char typeBits1; // [esp+5h] [ebp-13h]

  result = (_DWORD *)Class_ResolveNamedSlot(a3, theDefclass, slotName);
  if ( result )
  {
    theConstraint = (_DWORD *)result[5];
    if ( theConstraint && (*theConstraint & 1) == 0 )
    {
      typeBits1 = 0;
      typeBits0 = 0;
      typeCount = 0;
      if ( (*(_BYTE *)result[5] & 2) != 0 )
      {
        typeCount = 1;
        typeBits0 = 4;
      }
      if ( (*(_BYTE *)result[5] & 4) != 0 )
      {
        ++typeCount;
        typeBits0 |= 8u;
      }
      if ( (*(_BYTE *)result[5] & 8) != 0 )
      {
        ++typeCount;
        typeBits0 |= 1u;
      }
      if ( (*(_BYTE *)result[5] & 0x10) != 0 )
      {
        ++typeCount;
        typeBits0 |= 2u;
      }
      if ( (*(_BYTE *)result[5] & 0x20) != 0 )
      {
        ++typeCount;
        typeBits1 |= 1u;
      }
      if ( (*(_BYTE *)result[5] & 0x40) != 0 )
      {
        ++typeCount;
        typeBits0 |= 0x80u;
      }
      if ( *(char *)result[5] < 0 )
      {
        ++typeCount;
        typeBits0 |= 0x20u;
      }
      if ( (*(_BYTE *)(result[5] + 1) & 1) != 0 )
      {
        ++typeCount;
        typeBits0 |= 0x40u;
      }
    }
    else
    {
      typeBits1 = -1;
      typeCount = 8;
      typeBits0 = -17;
    }
    *(_DWORD *)(a3 + 16) = typeCount - 1;
    bitIndex = 0;
    result = Rules_CreateEphemeralMultifield(typeCount);
    *(_DWORD *)(a3 + 8) = result;
    if ( v8 >= 1 )
    {
      typeIndex = 0;
      fieldOffset = 0;
      lastFieldOffset = 6 * v8 - 6;
      do
      {
        result = (_DWORD *)(unsigned __int8)*(&typeBits0 + ((bitIndex - (__CFSHL__(bitIndex >> 31, 3) + 8 * (bitIndex >> 31))) >> 3));
        if ( ((unsigned __int8)(1 << (bitIndex % 8)) & (unsigned __int8)result) != 0 )
        {
          *(_WORD *)(fieldOffset + *(_DWORD *)(a3 + 8) + 14) = 2;
          fieldOffset += 6;
          result = (_DWORD *)Rules_GetConstructNameSymbol(g_ClipsPrimitiveTypeClassMap[typeIndex]);
          *(_DWORD *)(*(_DWORD *)(a3 + 8) + fieldOffset + 10) = result;
        }
        ++typeIndex;
        ++bitIndex;
      }
      while ( fieldOffset <= lastFieldOffset );
    }
  }
  return result;
}
// 4D626A: variable 'v8' is possibly undefined
// 51AD7C: using guessed type int dword_51AD7C[];

//----- (004D63B0) --------------------------------------------------------
int  Class_SlotAllowedValuesQuery(int theDefclass, _BYTE *slotName, _DWORD *a3)
{
  int result; // eax
  int theConstraint; // ecx
  int v5; // eax
  signed int valueCount; // eax
  int v7; // edx
  int fieldOffset; // edx

  result = Class_ResolveNamedSlot((int)a3, theDefclass, slotName);
  if ( result )
  {
    theConstraint = *(_DWORD *)(result + 20);
    if ( theConstraint && (v5 = *(_DWORD *)(result + 20), *(_DWORD *)(theConstraint + 6)) )
    {
      valueCount = AST_CountTreeNodes(*(_DWORD *)(v5 + 6));
      a3[4] = valueCount - 1;
      a3[2] = Rules_CreateEphemeralMultifield(valueCount);
      result = *(_DWORD *)(*(_DWORD *)(v7 + 20) + 6);
      if ( result )
      {
        fieldOffset = 0;
        do
        {
          *(_WORD *)(fieldOffset + a3[2] + 14) = *(_WORD *)result;
          *(_DWORD *)(a3[2] + fieldOffset + 16) = *(_DWORD *)(result + 2);
          result = *(_DWORD *)(result + 10);
          fieldOffset += 6;
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
int  Class_SlotRangeQuery(int theDefclass, _BYTE *slotName, _DWORD *a3)
{
  int result; // eax
  char *theConstraint; // ecx
  char constraintFlags; // bl
  int hasRange; // eax
  int v8; // edx

  result = Class_ResolveNamedSlot((int)a3, theDefclass, slotName);
  if ( result )
  {
    theConstraint = *(char **)(result + 20);
    if ( theConstraint && ((constraintFlags = *theConstraint, (*theConstraint & 1) != 0) || (constraintFlags & 8) != 0 || (constraintFlags & 0x10) != 0 ? (hasRange = 1) : (hasRange = 0), hasRange) )
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
_DWORD * Class_SlotCardinalityQuery(int theDefclass, _BYTE *slotName, int a3)
{
  _DWORD *result; // eax
  _DWORD *theMultifield; // eax
  int v5; // edx
  int theConstraint; // ecx

  result = (_DWORD *)Class_ResolveNamedSlot(a3, theDefclass, slotName);
  if ( result )
  {
    if ( (*(_BYTE *)result & 2) != 0 )
    {
      *(_DWORD *)(a3 + 16) = 1;
      theMultifield = Rules_CreateEphemeralMultifield(2);
      *(_DWORD *)(a3 + 8) = theMultifield;
      theConstraint = *(_DWORD *)(v5 + 20);
      if ( theConstraint )
      {
        *(_WORD *)(*(_DWORD *)(a3 + 8) + 14) = **(_WORD **)(theConstraint + 18);
        *(_DWORD *)(*(_DWORD *)(a3 + 8) + 16) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v5 + 20) + 18) + 2);
        *(_WORD *)(*(_DWORD *)(a3 + 8) + 20) = **(_WORD **)(*(_DWORD *)(v5 + 20) + 22);
        result = *(_DWORD **)(*(_DWORD *)(*(_DWORD *)(v5 + 20) + 22) + 2);
        *(_DWORD *)(*(_DWORD *)(a3 + 8) + 22) = result;
      }
      else
      {
        *((_WORD *)theMultifield + 7) = 1;
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
_DWORD * Class_DispatchSlotQuery(int a1, int *result, int (*queryFunction)(void), double a4)
{
  int returnValue; // ecx
  int *v6[3]; // [esp+0h] [ebp-Ch] BYREF

  v6[2] = result;
  if ( Class_ParseClassReference(v6, a1, a4) )
    return (_DWORD *)queryFunction();
  else
    return Rules_SetMultifieldErrorValue(returnValue);
}
// 4D65C8: variable 'v4' is possibly undefined

//----- (004D65F0) --------------------------------------------------------
int  Class_CountSubclasses(int theDefclass, int inheritFlag, signed int traversalID)
{
  int subclassCount; // esi
  int linkOffset; // ebp
  int theSubclass; // eax
  int bitIndex; // [esp+8h] [ebp-24h]
  int byteIndex; // [esp+Ch] [ebp-20h]
  unsigned int subclassIndex; // [esp+18h] [ebp-14h]

  byteIndex = (traversalID - (__CFSHL__(traversalID >> 31, 3) + 8 * (traversalID >> 31))) >> 3;
  subclassCount = 0;
  linkOffset = 0;
  subclassIndex = 0;
  bitIndex = traversalID % 8;
  while ( *(unsigned __int16 *)(theDefclass + 40) > subclassIndex )
  {
    theSubclass = *(_DWORD *)(*(_DWORD *)(theDefclass + 42) + linkOffset);
    if ( (*(_BYTE *)(theSubclass + byteIndex + 108) & (unsigned __int8)(1 << bitIndex)) == 0 )
    {
      ++subclassCount;
      *(_BYTE *)(theSubclass + byteIndex + 108) |= 1 << bitIndex;
      if ( inheritFlag )
      {
        if ( *(_WORD *)(theSubclass + 40) )
          subclassCount += Class_CountSubclasses(theSubclass, inheritFlag, traversalID);
      }
    }
    linkOffset += 4;
    ++subclassIndex;
  }
  return subclassCount;
}

//----- (004D66B0) --------------------------------------------------------
int  Class_CollectSubclassNames(int multifieldValue, int startIndex, int inheritFlag, int theDefclass, signed int traversalID)
{
  int fieldPosition; // esi
  int theSubclass; // ebx
  int classNameSymbol; // eax
  int fieldOffset; // edx
  int bitIndex; // [esp+10h] [ebp-1Ch]
  int byteIndex; // [esp+14h] [ebp-18h]
  unsigned int subclassIndex; // [esp+18h] [ebp-14h]
  int linkOffset; // [esp+1Ch] [ebp-10h]

  fieldPosition = startIndex;
  subclassIndex = 0;
  byteIndex = (traversalID - (__CFSHL__(traversalID >> 31, 3) + 8 * (traversalID >> 31))) >> 3;
  bitIndex = traversalID % 8;
  linkOffset = 0;
  while ( *(unsigned __int16 *)(theDefclass + 40) > subclassIndex )
  {
    theSubclass = *(_DWORD *)(linkOffset + *(_DWORD *)(theDefclass + 42));
    if ( (*(_BYTE *)(theSubclass + byteIndex + 108) & (unsigned __int8)(1 << bitIndex)) == 0 )
    {
      *(_BYTE *)(theSubclass + byteIndex + 108) |= 1 << bitIndex;
      *(_WORD *)(multifieldValue + 6 * (fieldPosition++ - 1) + 14) = 2;
      classNameSymbol = Rules_GetConstructNameSymbol(theSubclass);
      *(_DWORD *)(fieldOffset + multifieldValue + 16) = classNameSymbol;
      if ( inheritFlag )
      {
        if ( *(_WORD *)(theSubclass + 40) )
          fieldPosition += Class_CollectSubclassNames(multifieldValue, fieldPosition, inheritFlag, theSubclass, traversalID);
      }
    }
    linkOffset += 4;
    ++subclassIndex;
  }
  return fieldPosition - startIndex;
}
// 4D66B0: could not find valid save-restore pair for ebx
// 4D6778: variable 'v10' is possibly undefined

//----- (004D67B0) --------------------------------------------------------
int  Class_ResolveNamedSlot(int result, int theDefclass, _BYTE *slotName)
{
  int *slotSymbol; // eax
  int v6; // ecx
  unsigned int slotIndex; // eax
  int v8; // ecx

  slotSymbol = Rules_FindSymbolEntry(slotName);
  if ( slotSymbol )
  {
    slotIndex = Instance_ResolveSlotIndex(v6, (int)slotSymbol);
    if ( slotIndex == -1 )
    {
      Instance_ReportNoSuchSlotError(v8, v8);
      Lexer_ErrorRecover(1);
      Rules_SetMultifieldErrorValue(result);
      return 0;
    }
    else
    {
      *(_DWORD *)(result + 4) = 4;
      *(_DWORD *)(result + 12) = 0;
      return *(_DWORD *)(*(_DWORD *)(theDefclass + 56) + 4 * slotIndex);
    }
  }
  else
  {
    Lexer_ErrorRecover(1);
    Rules_SetMultifieldErrorValue(result);
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
int  Compiler_GenerateConstructTables(DWORD imageID)
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
  Compiler_WriteConstantsReferenceFile(v1, imageID);
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
int  Compiler_WriteSymbolTableFile(const char *fileName, int version)
{
  int symbolTable; // esi
  DWORD arrayVersion; // ebp
  _DWORD **bucket; // edx
  _DWORD *i; // eax
  int j; // ecx
  int result; // eax
  int v8; // edx
  int outFile; // ecx
  int entriesThisFile; // edi
  _DWORD *symbolNode; // esi
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  _DWORD *bucketPtr; // [esp+0h] [ebp-30h]
  int k; // [esp+8h] [ebp-28h]
  int newHeader; // [esp+Ch] [ebp-24h]
  int writtenCount; // [esp+14h] [ebp-1Ch]
  int symbolCount; // [esp+18h] [ebp-18h]

  symbolTable = Rules_GetSymbolTable();
  newHeader = 1;
  arrayVersion = 1;
  symbolCount = 0;
  writtenCount = 0;
  bucket = (_DWORD **)symbolTable;
  do
  {
    for ( i = *bucket; i; ++symbolCount )
      i = (_DWORD *)*i;
    ++bucket;
  }
  while ( bucket != (_DWORD **)(symbolTable + 4052) );
  if ( !symbolCount )
    return version;
  for ( j = 1;
        j <= symbolCount / g_ClipsCodeMaxIndicesPerArray + 1;
        Output_WriteFormatted(j + 1, g_ConstructsToCImageId, g_ClipsCodeHeaderFile, (int)aExternStructSy, g_ConstructsToCImageId) )
  {
    ;
  }
  outFile = Rules_OpenConstructCodeFile(fileName, 1, version, 1u);
  if ( !outFile )
    return -1;
  entriesThisFile = 0;
  bucketPtr = (_DWORD *)symbolTable;
  for ( k = 0; k < 1013; ++k )
  {
    symbolNode = (_DWORD *)*bucketPtr;
    if ( *bucketPtr )
    {
      do
      {
        if ( newHeader )
        {
          Output_WriteFormatted(outFile, 0, outFile, (int)aStructSymbolha, g_ConstructsToCImageId);
          newHeader = v8;
        }
        if ( *symbolNode )
          Output_WriteFormatted(outFile, g_ClipsCodeMaxIndicesPerArray, outFile, (int)aSD_DD_2, g_ConstructsToCImageId);
        else
          Output_WriteFormatted(outFile, v8, outFile, (int)aNull_8, (char)bucketPtr);
        ++entriesThisFile;
        Output_WriteFormatted(v12, k, v12, (int)aLd000D, symbolNode[1] + 1);
        Compiler_WriteEscapedStringLiteral(v13, symbolNode[4], v13, entriesThisFile);
        if ( ++writtenCount == symbolCount || entriesThisFile >= g_ClipsCodeMaxIndicesPerArray )
        {
          Output_WriteFormatted(v14, symbolCount, v14, (int)asc_50D12C, (char)bucketPtr);
          fclose_(v15);
          ++arrayVersion;
          v8 = symbolCount;
          ++version;
          entriesThisFile = 0;
          if ( writtenCount < symbolCount )
          {
            result = Rules_OpenConstructCodeFile(fileName, 1, version, arrayVersion);
            outFile = result;
            if ( !result )
              return result;
            newHeader = 1;
          }
        }
        else
        {
          Output_WriteFormatted(v14, symbolCount, v14, (int)asc_50D134, (char)bucketPtr);
        }
        symbolNode = (_DWORD *)*symbolNode;
      }
      while ( symbolNode );
    }
    ++bucketPtr;
  }
  return version;
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
int  Compiler_WriteBitMapTableFile(const char *fileName, int version)
{
  int bitmapTable; // esi
  int wordsThisArray; // edi
  _DWORD **bucket; // edx
  _DWORD *i; // eax
  signed int j; // ebp
  int result; // eax
  int outFile; // edx
  int v9; // ecx
  int entriesThisFile; // ebp
  int *m; // esi
  int v12; // edx
  int v13; // edx
  unsigned __int16 bitmapSize; // ax
  int v15; // ecx
  int **bucketPtr; // [esp+0h] [ebp-38h]
  int k; // [esp+8h] [ebp-30h]
  int valueArrayVersion; // [esp+Ch] [ebp-2Ch]
  int newHeader; // [esp+10h] [ebp-28h]
  int writtenCount; // [esp+18h] [ebp-20h]
  int bitmapCount; // [esp+1Ch] [ebp-1Ch]
  int arrayVersion; // [esp+20h] [ebp-18h]

  bitmapTable = Rules_GetBitmapTable();
  wordsThisArray = 0;
  newHeader = 1;
  arrayVersion = 1;
  valueArrayVersion = 1;
  bitmapCount = 0;
  writtenCount = 0;
  bucket = (_DWORD **)bitmapTable;
  do
  {
    for ( i = *bucket; i; ++bitmapCount )
      i = (_DWORD *)*i;
    ++bucket;
  }
  while ( bucket != (_DWORD **)(bitmapTable + 668) );
  if ( !bitmapCount )
    return version;
  for ( j = 1; j <= bitmapCount / g_ClipsCodeMaxIndicesPerArray + 1; ++j )
    Output_WriteFormatted(g_ClipsCodeMaxIndicesPerArray, g_ClipsCodeHeaderFile, g_ClipsCodeHeaderFile, (int)aExternStructBi, g_ConstructsToCImageId);
  outFile = Rules_OpenConstructCodeFile(fileName, 1, version, j);
  if ( !outFile )
    return -1;
  entriesThisFile = 0;
  bucketPtr = (int **)bitmapTable;
  for ( k = 0; k < 167; ++k )
  {
    for ( m = *bucketPtr; m; m = (int *)*m )
    {
      if ( newHeader )
      {
        Output_WriteFormatted(arrayVersion, outFile, outFile, (int)aStructBitmapha, g_ConstructsToCImageId);
        newHeader = 0;
      }
      if ( *m )
      {
        if ( entriesThisFile + 1 < g_ClipsCodeMaxIndicesPerArray )
          Output_WriteFormatted(g_ConstructsToCImageId, outFile, outFile, (int)aBD_DD, g_ConstructsToCImageId);
        else
          Output_WriteFormatted(v9, outFile, outFile, (int)aBD_DD, g_ConstructsToCImageId);
      }
      else
      {
        Output_WriteFormatted(v9, outFile, outFile, (int)aNull_8, (char)bucketPtr);
      }
      Output_WriteFormatted(g_ConstructsToCImageId, v12, v12, (int)aLd000DCharLD_D, m[1] + 1);
      bitmapSize = *((_WORD *)m + 10);
      wordsThisArray += bitmapSize >> 2;
      if ( (bitmapSize & 3) != 0 )
        ++wordsThisArray;
      if ( wordsThisArray >= g_ClipsCodeMaxIndicesPerArray )
      {
        wordsThisArray = 0;
        ++valueArrayVersion;
      }
      ++entriesThisFile;
      if ( ++writtenCount == bitmapCount || entriesThisFile >= g_ClipsCodeMaxIndicesPerArray )
      {
        Output_WriteFormatted(bitmapCount, v13, v13, (int)asc_50D12C, (char)bucketPtr);
        entriesThisFile = 0;
        fclose_(v15);
        v9 = version + 1;
        ++arrayVersion;
        ++version;
        if ( writtenCount < bitmapCount )
        {
          result = Rules_OpenConstructCodeFile(fileName, 1, version, 0);
          outFile = result;
          if ( !result )
            return result;
          newHeader = 1;
        }
      }
      else
      {
        Output_WriteFormatted(bitmapCount, v13, v13, (int)asc_50D134, (char)bucketPtr);
      }
    }
    v9 = (int)++bucketPtr;
  }
  return version;
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
int  Compiler_WriteBitMapValuesFile(const char *fileName, int version)
{
  DWORD bitmapTable; // ebp
  int **bucket; // esi
  int *i; // eax
  unsigned __int16 bitmapSize; // dx
  int wordTotal; // ebx
  int j; // ecx
  int result; // eax
  int v9; // ecx
  int *m; // esi
  unsigned __int16 sizeBytes; // ax
  int v12; // edx
  int wordIndex; // edi
  unsigned int byteBase; // ebp
  unsigned int byteInWord; // edx
  unsigned int byteIndex; // eax
  int v17; // ecx
  char byteVal; // bl
  int newWordsThisFile; // edi
  int v20; // ecx
  DWORD nextArrayVersion; // ebp
  char v22; // [esp+1h] [ebp-45h]
  int wordValue; // [esp+2h] [ebp-44h]
  int **bucketPtr; // [esp+6h] [ebp-40h]
  int k; // [esp+Ah] [ebp-3Ch]
  const char *savedFileName; // [esp+Eh] [ebp-38h]
  int newHeader; // [esp+12h] [ebp-34h]
  int arrayVersion; // [esp+16h] [ebp-30h]
  int versionCounter; // [esp+1Ah] [ebp-2Ch]
  int wordsThisFile; // [esp+1Eh] [ebp-28h]
  int wordsWritten; // [esp+22h] [ebp-24h]
  int totalWordCount; // [esp+26h] [ebp-20h]
  int wordCount; // [esp+2Ah] [ebp-1Ch]
  int outFile; // [esp+2Eh] [ebp-18h]

  savedFileName = fileName;
  versionCounter = version;
  bitmapTable = Rules_GetBitmapTable();
  bucket = (int **)bitmapTable;
  newHeader = 1;
  arrayVersion = 1;
  totalWordCount = 0;
  wordsWritten = 0;
  do
  {
    for ( i = *bucket; i; i = (int *)*i )
    {
      bitmapSize = *((_WORD *)i + 10);
      wordTotal = (bitmapSize >> 2) + totalWordCount;
      totalWordCount = wordTotal;
      if ( (bitmapSize & 3) != 0 )
        totalWordCount = wordTotal + 1;
    }
    ++bucket;
  }
  while ( bucket != (int **)(bitmapTable + 668) );
  if ( !totalWordCount )
    return versionCounter;
  for ( j = 1;
        j <= totalWordCount / g_ClipsCodeMaxIndicesPerArray + 1;
        Output_WriteFormatted(j + 1, g_ClipsCodeHeaderFile, g_ClipsCodeHeaderFile, (int)aExternUnsigned, g_ConstructsToCImageId) )
  {
    v22 = HIBYTE(j);
  }
  outFile = Rules_OpenConstructCodeFile(savedFileName, 1, versionCounter, bitmapTable);
  if ( !outFile )
    return -1;
  bucketPtr = (int **)bitmapTable;
  wordsThisFile = 0;
  for ( k = 0; k < 167; ++k )
  {
    for ( m = *bucketPtr; m; m = (int *)*m )
    {
      if ( newHeader )
      {
        v22 = HIBYTE(arrayVersion);
        Output_WriteFormatted(0, outFile, outFile, (int)aUnsignedLongLD, g_ConstructsToCImageId);
        newHeader = v9;
      }
      sizeBytes = *((_WORD *)m + 10);
      v12 = sizeBytes >> 2;
      wordCount = v12;
      if ( (sizeBytes & 3) != 0 )
        wordCount = v12 + 1;
      wordIndex = 0;
      if ( wordCount > 0 )
      {
        byteBase = 0;
        do
        {
          if ( wordIndex > 0 )
            Output_WriteFormatted(v9, v12, outFile, (int)asc_50D1F8, wordValue);
          byteInWord = 0;
          wordValue = 0;
          byteIndex = byteBase;
          do
          {
            v17 = *((unsigned __int16 *)m + 10);
            if ( byteIndex >= (unsigned __int16)v17 )
              break;
            v17 = m[4];
            ++byteInWord;
            byteVal = *(_BYTE *)(v17 + byteIndex++);
            *(&v22 + byteInWord) = byteVal;
          }
          while ( byteInWord < 4 );
          Output_WriteFormatted(v17, outFile, outFile, (int)a0xLxl, wordValue);
          ++wordIndex;
          v9 = wordCount;
          byteBase += 4;
        }
        while ( wordIndex < wordCount );
      }
      newWordsThisFile = wordCount + wordsThisFile;
      wordsWritten += wordCount;
      wordsThisFile += wordCount;
      if ( wordsWritten == totalWordCount || newWordsThisFile >= g_ClipsCodeMaxIndicesPerArray )
      {
        Output_WriteFormatted(v9, v12, outFile, (int)asc_50D204, wordValue);
        fclose_(v20);
        wordsThisFile = 0;
        nextArrayVersion = arrayVersion + 1;
        ++versionCounter;
        ++arrayVersion;
        if ( wordsWritten < totalWordCount )
        {
          result = Rules_OpenConstructCodeFile(savedFileName, 1, versionCounter, nextArrayVersion);
          outFile = result;
          if ( !result )
            return result;
          newHeader = 1;
        }
      }
      else
      {
        Output_WriteFormatted(outFile, v12, outFile, (int)asc_50D208, wordValue);
      }
    }
    v9 = (int)++bucketPtr;
  }
  return versionCounter;
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
int  Compiler_WriteFloatTableFile(const char *fileName, int version)
{
  DWORD arrayVersion; // ebp
  _DWORD **bucket; // edx
  _DWORD *i; // eax
  int j; // edi
  int result; // eax
  int outFile; // edx
  int v8; // ecx
  int entriesThisFile; // edi
  double *k; // esi
  int v11; // edx
  int v12; // ecx
  char floatStr; // al
  int v14; // edx
  int v15; // ecx
  int v16; // edx
  int v17; // ecx
  int v18; // ecx
  int floatTable; // [esp+0h] [ebp-34h]
  double **bucketPtr; // [esp+4h] [ebp-30h]
  int bucketIndex; // [esp+Ch] [ebp-28h]
  int newHeader; // [esp+10h] [ebp-24h]
  int writtenCount; // [esp+18h] [ebp-1Ch]
  int floatCount; // [esp+1Ch] [ebp-18h]

  floatTable = Rules_GetFloatTable();
  newHeader = 1;
  arrayVersion = 1;
  floatCount = 0;
  writtenCount = 0;
  bucket = (_DWORD **)floatTable;
  do
  {
    for ( i = *bucket; i; ++floatCount )
      i = (_DWORD *)*i;
    ++bucket;
  }
  while ( bucket != (_DWORD **)(floatTable + 2012) );
  if ( !floatCount )
    return version;
  for ( j = 1; j <= floatCount / g_ClipsCodeMaxIndicesPerArray + 1; ++j )
    Output_WriteFormatted(g_ClipsCodeMaxIndicesPerArray, floatCount % g_ClipsCodeMaxIndicesPerArray, g_ClipsCodeHeaderFile, (int)aExternStructFl, g_ConstructsToCImageId);
  outFile = Rules_OpenConstructCodeFile(fileName, 1, version, 1u);
  if ( !outFile )
    return -1;
  entriesThisFile = 0;
  bucketIndex = 0;
  bucketPtr = (double **)floatTable;
  do
  {
    for ( k = *bucketPtr; k; k = *(double **)k )
    {
      if ( newHeader )
      {
        Output_WriteFormatted(g_ConstructsToCImageId, outFile, outFile, (int)aStructFloathas, g_ConstructsToCImageId);
        newHeader = 0;
      }
      if ( *(_DWORD *)k )
        Output_WriteFormatted(g_ClipsCodeMaxIndicesPerArray, outFile, outFile, (int)aFD_DD, g_ConstructsToCImageId);
      else
        Output_WriteFormatted(v8, outFile, outFile, (int)aNull_8, floatTable);
      Output_WriteFormatted(bucketIndex, v11, v11, (int)aLd000D, *((_DWORD *)k + 1) + 1);
      floatStr = Rules_FloatToSymbol(v12, k[2]);
      Output_WriteFormatted(v15, v14, v14, (int)aS_11, floatStr);
      ++entriesThisFile;
      v17 = writtenCount + 1;
      writtenCount = v17;
      if ( v17 == floatCount || entriesThisFile >= g_ClipsCodeMaxIndicesPerArray )
      {
        ++arrayVersion;
        Output_WriteFormatted(v17, v16, v16, (int)asc_50D12C, floatTable);
        entriesThisFile = 0;
        fclose_(v18);
        v8 = ++version;
        if ( writtenCount < floatCount )
        {
          result = Rules_OpenConstructCodeFile(fileName, 1, version, arrayVersion);
          outFile = result;
          if ( !result )
            return result;
          newHeader = 1;
        }
      }
      else
      {
        Output_WriteFormatted(v17, v16, v16, (int)asc_50D134, floatTable);
      }
    }
    v8 = (int)++bucketPtr;
    ++bucketIndex;
  }
  while ( bucketIndex < 503 );
  return version;
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
int  Compiler_WriteIntegerTableFile(const char *fileName, int version)
{
  DWORD arrayVersion; // ebp
  _DWORD **bucket; // edx
  _DWORD *i; // eax
  int j; // edi
  int result; // eax
  int outFile; // edx
  int v8; // ecx
  int entriesThisFile; // edi
  _DWORD *integerNode; // esi
  int v11; // edx
  int v12; // edx
  int v13; // ecx
  int v14; // edx
  int v15; // ecx
  int integerTable; // [esp+0h] [ebp-34h]
  _DWORD *bucketPtr; // [esp+4h] [ebp-30h]
  int bucketIndex; // [esp+Ch] [ebp-28h]
  int newHeader; // [esp+10h] [ebp-24h]
  int writtenCount; // [esp+18h] [ebp-1Ch]
  int integerCount; // [esp+1Ch] [ebp-18h]

  integerTable = Rules_GetIntegerTable();
  newHeader = 1;
  arrayVersion = 1;
  integerCount = 0;
  writtenCount = 0;
  bucket = (_DWORD **)integerTable;
  do
  {
    for ( i = *bucket; i; ++integerCount )
      i = (_DWORD *)*i;
    ++bucket;
  }
  while ( bucket != (_DWORD **)(integerTable + 668) );
  if ( !integerCount )
    return version;
  for ( j = 1; j <= integerCount / g_ClipsCodeMaxIndicesPerArray + 1; ++j )
    Output_WriteFormatted(g_ClipsCodeMaxIndicesPerArray, integerCount % g_ClipsCodeMaxIndicesPerArray, g_ClipsCodeHeaderFile, (int)aExternStructIn, g_ConstructsToCImageId);
  outFile = Rules_OpenConstructCodeFile(fileName, 1, version, 1u);
  if ( !outFile )
    return -1;
  entriesThisFile = 0;
  bucketIndex = 0;
  bucketPtr = (_DWORD *)integerTable;
  do
  {
    integerNode = (_DWORD *)*bucketPtr;
    if ( *bucketPtr )
    {
      do
      {
        if ( newHeader )
        {
          Output_WriteFormatted(g_ConstructsToCImageId, outFile, outFile, (int)aStructIntegerh, g_ConstructsToCImageId);
          newHeader = 0;
        }
        if ( *integerNode )
          Output_WriteFormatted(g_ClipsCodeMaxIndicesPerArray, outFile, outFile, (int)aID_DD, g_ConstructsToCImageId);
        else
          Output_WriteFormatted(v8, outFile, outFile, (int)aNull_8, integerTable);
        Output_WriteFormatted(bucketIndex, v11, v11, (int)aLd000D, integerNode[1] + 1);
        Output_WriteFormatted(v13, v12, v12, (int)aLd, integerNode[4]);
        ++entriesThisFile;
        if ( ++writtenCount == integerCount || entriesThisFile >= g_ClipsCodeMaxIndicesPerArray )
        {
          Output_WriteFormatted(integerCount, v14, v14, (int)asc_50D12C, integerTable);
          fclose_(v15);
          ++arrayVersion;
          v8 = integerCount;
          ++version;
          entriesThisFile = 0;
          if ( writtenCount < integerCount )
          {
            result = Rules_OpenConstructCodeFile(fileName, 1, version, arrayVersion);
            outFile = result;
            if ( !result )
              return result;
            newHeader = 1;
          }
        }
        else
        {
          Output_WriteFormatted(integerCount, v14, v14, (int)asc_50D134, integerTable);
        }
        integerNode = (_DWORD *)*integerNode;
      }
      while ( integerNode );
    }
    v8 = (int)++bucketPtr;
    ++bucketIndex;
  }
  while ( bucketIndex < 167 );
  return version;
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
signed int  Compiler_WriteConstantsReferenceFile(const char *fileName, DWORD imageID)
{
  int *symbolTable; // esi
  signed int result; // eax
  int symbolFile; // ebx
  int v6; // edx
  int symbolIndex; // ecx
  int v8; // ecx
  int *floatTable; // esi
  int v10; // edx
  int v11; // ecx
  int floatFile; // ebx
  int v13; // edx
  int v14; // edx
  int v15; // ecx
  int floatIndex; // ecx
  int integerTable; // ebp
  int v18; // edx
  int integerFile; // ebx
  int integerIndex; // esi
  int v21; // edx
  int *integerEntry; // ecx
  int v23; // ecx
  int *bitmapTable; // esi
  int v25; // edx
  int bitmapFile; // ebx
  int v27; // edx
  int v28; // ecx
  int bitmapIndex; // ecx
  int v30; // edx
  int v31; // ecx
  char v32; // [esp+0h] [ebp-18h]
  char v33; // [esp+0h] [ebp-18h]
  char v34; // [esp+0h] [ebp-18h]
  char v35; // [esp+0h] [ebp-18h]

  symbolTable = (int *)Rules_GetSymbolTable();
  result = Rules_OpenConstructCodeFile(fileName, 1, 1, imageID);
  symbolFile = result;
  if ( result )
  {
    Output_WriteFormatted(g_ConstructsToCImageId, result, g_ClipsCodeHeaderFile, (int)aExternStruct_0, g_ConstructsToCImageId);
    Output_WriteFormatted(0, v6, v6, (int)aStructSymbol_0, g_ConstructsToCImageId);
    do
    {
      Compiler_WriteSymbolReference(symbolFile, *symbolTable, symbolIndex);
      if ( v8 != 1012 )
        Output_WriteFormatted(v8, v8 + 1, symbolFile, (int)asc_50D208, v32);
      symbolIndex = v8 + 1;
      ++symbolTable;
    }
    while ( symbolIndex < 1013 );
    Output_WriteFormatted(symbolIndex, 1, symbolFile, (int)asc_50D204, v32);
    fclose_(0);
    floatTable = (int *)Rules_GetFloatTable();
    result = Rules_OpenConstructCodeFile(fileName, v10, 2, imageID);
    floatFile = result;
    if ( result )
    {
      Output_WriteFormatted(v11, result, g_ClipsCodeHeaderFile, (int)aExternStruct_1, g_ConstructsToCImageId);
      Output_WriteFormatted(0, v13, v13, (int)aStructFloath_0, g_ConstructsToCImageId);
      do
      {
        if ( *floatTable )
          Compiler_WriteFloatReference(floatFile, *floatTable);
        else
          Output_WriteFormatted(v15, v14, floatFile, (int)aNull_9, v33);
        v14 = floatIndex + 1;
        if ( floatIndex != 502 )
          Output_WriteFormatted(floatIndex, v14, floatFile, (int)asc_50D208, v33);
        v15 = floatIndex + 1;
        ++floatTable;
      }
      while ( v15 < 503 );
      Output_WriteFormatted(v15, 1, floatFile, (int)asc_50D204, v33);
      fclose_(0);
      integerTable = Rules_GetIntegerTable();
      result = Rules_OpenConstructCodeFile(fileName, v18, 3, integerTable);
      integerFile = result;
      if ( result )
      {
        Output_WriteFormatted(g_ConstructsToCImageId, result, g_ClipsCodeHeaderFile, (int)aExternStruct_2, g_ConstructsToCImageId);
        integerIndex = 0;
        Output_WriteFormatted(integerTable, v21, v21, (int)aStructIntege_0, g_ConstructsToCImageId);
        do
        {
          if ( *integerEntry )
            Compiler_WriteIntegerReference(integerFile, *integerEntry);
          else
            Output_WriteFormatted((int)integerEntry, 0, integerFile, (int)aNull_9, v34);
          if ( integerIndex != 166 )
            Output_WriteFormatted(v23, integerIndex + 1, integerFile, (int)asc_50D208, v34);
          ++integerIndex;
          integerEntry = (int *)(v23 + 4);
        }
        while ( integerIndex < 167 );
        Output_WriteFormatted((int)integerEntry, 1, integerFile, (int)asc_50D204, v34);
        fclose_(0);
        bitmapTable = (int *)Rules_GetBitmapTable();
        result = Rules_OpenConstructCodeFile(fileName, v25, 4, integerTable);
        bitmapFile = result;
        if ( result )
        {
          Output_WriteFormatted(g_ConstructsToCImageId, result, g_ClipsCodeHeaderFile, (int)aExternStruct_3, g_ConstructsToCImageId);
          Output_WriteFormatted(0, v27, v27, (int)aStructBitmap_0, g_ConstructsToCImageId);
          do
          {
            Compiler_WriteBitMapReference(bitmapFile, *bitmapTable, v28);
            v30 = bitmapIndex + 1;
            if ( bitmapIndex != 166 )
              Output_WriteFormatted(bitmapIndex, v30, bitmapFile, (int)asc_50D208, v35);
            v28 = bitmapIndex + 1;
            ++bitmapTable;
          }
          while ( v28 < 167 );
          Output_WriteFormatted(v28, v30, bitmapFile, (int)asc_50D204, v35);
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
int  Compiler_WriteSymbolReference(int fp, int theSymbol, int a3)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( theSymbol )
    return Output_WriteFormatted(
             *(_DWORD *)(theSymbol + 12) << 16 >> 18,
             (*(_DWORD *)(theSymbol + 12) << 16 >> 18) % (unsigned int)g_ClipsCodeMaxIndicesPerArray,
             fp,
             (int)aSD_DD_3,
             g_ConstructsToCImageId);
  else
    return Output_WriteFormatted(a3, 0, fp, (int)aNull_9, v4);
}
// 4D7AEE: variable 'v4' is possibly undefined
// 51ACF0: using guessed type int dword_51ACF0;
// 54E6D0: using guessed type int dword_54E6D0;

//----- (004D7B40) --------------------------------------------------------
int  Compiler_WriteFloatReference(int fp, int theFloat)
{
  return Output_WriteFormatted(
           *(_DWORD *)(theFloat + 12) << 16 >> 18,
           (*(_DWORD *)(theFloat + 12) << 16 >> 18) % (unsigned int)g_ClipsCodeMaxIndicesPerArray,
           fp,
           (int)aFD_DD_0,
           g_ConstructsToCImageId);
}
// 51ACF0: using guessed type int dword_51ACF0;
// 54E6D0: using guessed type int dword_54E6D0;

//----- (004D7B90) --------------------------------------------------------
int  Compiler_WriteIntegerReference(int fp, int theInteger)
{
  return Output_WriteFormatted(
           *(_DWORD *)(theInteger + 12) << 16 >> 18,
           (*(_DWORD *)(theInteger + 12) << 16 >> 18) % (unsigned int)g_ClipsCodeMaxIndicesPerArray,
           fp,
           (int)aID_DD_0,
           g_ConstructsToCImageId);
}
// 51ACF0: using guessed type int dword_51ACF0;
// 54E6D0: using guessed type int dword_54E6D0;

//----- (004D7BE0) --------------------------------------------------------
int  Compiler_WriteBitMapReference(int fp, int theBitMap, int a3)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( theBitMap )
    return Output_WriteFormatted(
             *(_DWORD *)(theBitMap + 12) << 16 >> 18,
             (*(_DWORD *)(theBitMap + 12) << 16 >> 18) % (unsigned int)g_ClipsCodeMaxIndicesPerArray,
             fp,
             (int)aBD_DD_0,
             g_ConstructsToCImageId);
  else
    return Output_WriteFormatted(a3, 0, fp, (int)aNull_9, v4);
}
// 4D7BEE: variable 'v4' is possibly undefined
// 51ACF0: using guessed type int dword_51ACF0;
// 54E6D0: using guessed type int dword_54E6D0;

//----- (004D7C40) --------------------------------------------------------
int  Compiler_WriteEscapedStringLiteral(int fp, int a2, int a3, char a4)
{
  const char *str; // edx
  signed int charIndex; // esi
  unsigned int lengthPlusOne; // kr04_4
  const char *charPtr; // ecx
  char currentChar; // ah
  int v10; // edx
  int v11; // ecx
  char v13; // [esp-Ch] [ebp-10h]

  Output_WriteFormatted(a3, a2, fp, (int)asc_50D454, a4);
  charIndex = 0;
  lengthPlusOne = strlen(str) + 1;
  charPtr = (const char *)(lengthPlusOne - 1);
  if ( (int)(lengthPlusOne - 1) > 0 )
  {
    charPtr = str;
    do
    {
      currentChar = *charPtr;
      if ( *charPtr == 34 || currentChar == 92 )
      {
        CRT_PutcToStream(charPtr, fp);
      }
      else if ( currentChar == 10 )
      {
        CRT_PutcToStream(charPtr, fp);
        v10 = fp;
        goto LABEL_6;
      }
      v10 = fp;
LABEL_6:
      CRT_PutcToStream(charPtr, v10);
      ++charIndex;
      charPtr = (const char *)(v11 + 1);
    }
    while ( charIndex < (int)(lengthPlusOne - 1) );
  }
  return Output_WriteFormatted((int)charPtr, (int)str, fp, (int)asc_50D454, v13);
}
// 4D7C5A: variable 'v5' is possibly undefined
// 4D7C83: variable 'v8' is possibly undefined
// 4D7C89: variable 'v11' is possibly undefined
// 4D7C94: variable 'v13' is possibly undefined
// 488A97: using guessed type int __fastcall sub_488A97(_DWORD, _DWORD);

//----- (004D7CC0) --------------------------------------------------------
int  Compiler_WriteConstraintTableFile(const char *fileName, int fileId, DWORD imageId, int headerFile, int maxIndices)
{
  int bucketOffset; // eax
  int i; // esi
  int v8; // ecx
  int v9; // ecx
  int result; // eax
  int arrayIndex; // edi
  int j; // ecx
  int v13; // ecx
  int outputFile; // edi
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
  int newVersion; // ebx
  int v37; // [esp+0h] [ebp-30h]
  char v38; // [esp+0h] [ebp-30h]
  char v39; // [esp+0h] [ebp-30h]
  char v40; // [esp+0h] [ebp-30h]
  char v41; // [esp+0h] [ebp-30h]
  char v42; // [esp+0h] [ebp-30h]
  char v43; // [esp+0h] [ebp-30h]
  int hashOffset; // [esp+4h] [ebp-2Ch]
  int newHeader; // [esp+Ch] [ebp-24h]
  int version; // [esp+10h] [ebp-20h]
  int constraintsWritten; // [esp+14h] [ebp-1Ch]
  int indexInFile; // [esp+18h] [ebp-18h]
  int arrayVersion; // [esp+1Ch] [ebp-14h]
  unsigned __int16 numberOfConstraints; // [esp+20h] [ebp-10h]

  v37 = fileId;
  newHeader = 1;
  version = 1;
  arrayVersion = 1;
  bucketOffset = 0;
  numberOfConstraints = 0;
  do
  {
    for ( i = *(_DWORD *)(g_ConstraintHashTable + bucketOffset); i; ++numberOfConstraints )
    {
      *(_WORD *)(i + 4) = numberOfConstraints;
      i = *(_DWORD *)(i + 30);
    }
    bucketOffset += 4;
  }
  while ( bucketOffset != 668 );
  if ( !Rules_DynamicConstraintCheckingEnabled() && numberOfConstraints )
  {
    Rules_PrintWarningID((int)aCstrncmp, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aConstraintsA_0, v8);
    Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aWhenDynamicC_0, v9);
    return -1;
  }
  if ( !numberOfConstraints )
    return -1;
  arrayIndex = 1;
  for ( j = maxIndices; arrayIndex <= numberOfConstraints / j + 1; Output_WriteFormatted(j, numberOfConstraints % j, headerFile, (int)aExternConstrai, imageId) )
    ++arrayIndex;
  outputFile = Rules_OpenConstructCodeFile(fileName, v37, 1, imageId);
  if ( !outputFile )
    return -1;
  indexInFile = 0;
  constraintsWritten = 0;
  hashOffset = 0;
  do
  {
    v15 = hashOffset;
    for ( k = *(_DWORD *)(hashOffset + g_ConstraintHashTable); k; k = *(_DWORD *)(k + 30) )
    {
      if ( newHeader )
      {
        Output_WriteFormatted(0, arrayVersion, outputFile, (int)aConstraint_rec, imageId);
        newHeader = v13;
      }
      Output_WriteFormatted(v13, v15, outputFile, (int)aDDDDDDDDDDDDDD, *(_BYTE *)k & 1);
      Output_WriteFormatted(v18, v17, outputFile, (int)a0, v37);
      Rules_WriteExpressionRefToCode(outputFile, *(__int16 **)(k + 6), maxIndices, imageId);
      Output_WriteFormatted(v20, v19, outputFile, (int)asc_50D54C, v38);
      Rules_WriteExpressionRefToCode(outputFile, *(__int16 **)(k + 10), maxIndices, imageId);
      Output_WriteFormatted(v22, v21, outputFile, (int)asc_50D54C, v39);
      Rules_WriteExpressionRefToCode(outputFile, *(__int16 **)(k + 14), maxIndices, imageId);
      Output_WriteFormatted(v24, v23, outputFile, (int)asc_50D54C, v40);
      Rules_WriteExpressionRefToCode(outputFile, *(__int16 **)(k + 18), maxIndices, imageId);
      Output_WriteFormatted(v26, v25, outputFile, (int)asc_50D54C, v41);
      Rules_WriteExpressionRefToCode(outputFile, *(__int16 **)(k + 22), maxIndices, imageId);
      Output_WriteFormatted(v28, v27, outputFile, (int)aNull_10, v42);
      if ( *(_DWORD *)(k + 30) )
      {
        if ( indexInFile + 1 < maxIndices )
          Output_WriteFormatted(arrayVersion, maxIndices, outputFile, (int)aCD_DD, imageId);
        else
          Output_WriteFormatted(v30, maxIndices, outputFile, (int)aCD_DD, imageId);
      }
      else
      {
        Output_WriteFormatted(v30, v29, outputFile, (int)aNull_11, v43);
      }
      Output_WriteFormatted(v32, v31, outputFile, (int)aDD_1, *(_DWORD *)(k + 34));
      v33 = constraintsWritten + 1;
      v34 = indexInFile + 1;
      constraintsWritten = v33;
      ++indexInFile;
      if ( numberOfConstraints == v33 || v34 >= maxIndices )
      {
        Output_WriteFormatted(v34, v33, outputFile, (int)asc_50D578, v43);
        fclose_(0);
        indexInFile = v35;
        v13 = constraintsWritten;
        newVersion = version + 1;
        v15 = arrayVersion + 1;
        ++version;
        ++arrayVersion;
        if ( numberOfConstraints > constraintsWritten )
        {
          result = Rules_OpenConstructCodeFile(fileName, 1, newVersion, imageId);
          outputFile = result;
          if ( !result )
            return result;
          newHeader = 1;
        }
      }
      else
      {
        Output_WriteFormatted(v34, v33, outputFile, (int)asc_50D580, v43);
      }
    }
    v13 = hashOffset + 4;
    hashOffset = v13;
  }
  while ( v13 < 668 );
  return version;
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
int  Compiler_WriteConstraintReference(int codeFile, int constraintPtr, int maxIndices, char imageId)
{
  char v8; // [esp+0h] [ebp-8h]

  if ( constraintPtr && Rules_DynamicConstraintCheckingEnabled() )
    return Output_WriteFormatted(*(unsigned __int16 *)(constraintPtr + 4), *(unsigned __int16 *)(constraintPtr + 4) % maxIndices, codeFile, (int)aCD_DD_0, imageId);
  else
    return Output_WriteFormatted(maxIndices, constraintPtr, codeFile, (int)aNull_21, v8);
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
int  Compiler_WriteModuleReference(int fp, int theModule)
{
  char v3; // [esp+0h] [ebp-Ch]

  if ( theModule )
    return Output_WriteFormatted(
             theModule,
             *(_DWORD *)(g_ClipsDefmoduleCompilerItem + 20),
             fp,
             (int)aSD_LdLd_5,
             *(_DWORD *)(*(_DWORD *)(g_ClipsDefmoduleCompilerItem + 20) + 4));
  else
    return Output_WriteFormatted(0, 0, fp, (int)aNull_18, v3);
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
  const char *v40; // [esp+Ch] [ebp-2Ch]
  const char *v41; // [esp+10h] [ebp-28h]
  int v42; // [esp+14h] [ebp-24h]
  int itemFile; // [esp+18h] [ebp-20h]
  int v44; // [esp+1Ch] [ebp-1Ch]
  int itemsWritten; // [esp+20h] [ebp-18h]
  int *Enum; // [esp+24h] [ebp-14h]
  int itemIndex; // [esp+28h] [ebp-10h]

  v41 = fileName;
  v40 = pathName;
  v42 = headerFile;
  v44 = fileId;
  itemFile = 0;
  itemsWritten = 0;
  arrayVersion = 1;
  fileVersion = 2;
  Output_WriteFormatted(0, 0, headerFile, (int)aIncludeModulde, 0);
  portItemCount = 0;
  result = Rules_OpenConstructCodeFile(v41, (int)v40, 1, 0);
  moduleFile = result;
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
                itemFile,
                v41,
                v44,
                v40,
                &fileVersion,
                arrayVersion,
                v42,
                (char)aStructDefmod_0,
                *(const char **)(*(_DWORD *)(g_ClipsDefmoduleCompilerItem + 20) + 4),
                0,
                0);
        v13 = v10;
        itemFile = v10;
        if ( !v10 )
          break;
        Output_WriteFormatted(v12, v11, v10, (int)asc_50D6C8, itemsInFile);
        Compiler_WriteSymbolReference(v13, *Enum, v14);
        Output_WriteFormatted(v16, v15, v13, (int)aNull_30, itemsInFile);
        Output_WriteFormatted(v44, itemsWritten, v13, (int)aSD_1D, **(_DWORD **)(g_ClipsDefmoduleCompilerItem + 20));
        itemList = Module_GetItemList();
        itemIndex = 0;
        theItem = itemList;
        while ( 1 )
        {
          v19 = Module_GetItemCount();
          if ( v19 <= v20 || !theItem )
            break;
          v22 = *(_DWORD *)(theItem + 20);
          ++itemsWritten;
          if ( v22 )
            (*(void (__fastcall **)(int, int))(theItem + 20))(maxIndices, Enum[6]);
          else
            Output_WriteFormatted(v21, 0, moduleFile, (int)aNull_18, itemsInFile);
          v23 = Module_GetItemCount();
          if ( v24 >= v23 )
          {
            if ( Enum[7] )
              Output_WriteFormatted(v25, v24, moduleFile, (int)asc_50D6E8, itemsInFile);
          }
          else
          {
            Output_WriteFormatted(v25, v24, moduleFile, (int)asc_50D6E4, itemsInFile);
          }
          theItem = *(_DWORD *)(theItem + 28);
          ++itemIndex;
        }
        if ( Enum[3] )
        {
          Output_WriteFormatted(
            itemFile,
            *(_DWORD *)(*(_DWORD *)(g_ClipsDefmoduleCompilerItem + 20) + 8),
            itemFile,
            (int)aSD_DD_9,
            *(_DWORD *)(*(_DWORD *)(g_ClipsDefmoduleCompilerItem + 20) + 8));
          for ( i = Enum[3]; i; ++portItemCount )
            i = *(_DWORD *)(i + 12);
        }
        else
        {
          Output_WriteFormatted(v21, v20, itemFile, (int)aNull_31, itemsInFile);
        }
        if ( Enum[4] )
        {
          Output_WriteFormatted(
            itemFile,
            *(_DWORD *)(*(_DWORD *)(g_ClipsDefmoduleCompilerItem + 20) + 8),
            itemFile,
            (int)aSD_DD_9,
            *(_DWORD *)(*(_DWORD *)(g_ClipsDefmoduleCompilerItem + 20) + 8));
          for ( j = Enum[4]; j; ++portItemCount )
            j = *(_DWORD *)(j + 12);
        }
        else
        {
          Output_WriteFormatted(v28, v27, itemFile, (int)aNull_31, itemsInFile);
        }
        Output_WriteFormatted(v30, v29, itemFile, (int)a0Ld, Enum[6]);
        if ( Enum[7] )
          Output_WriteFormatted(
            itemFile,
            *(_DWORD *)(*(_DWORD *)(g_ClipsDefmoduleCompilerItem + 20) + 4),
            itemFile,
            (int)aSD_DD_10,
            *(_DWORD *)(*(_DWORD *)(g_ClipsDefmoduleCompilerItem + 20) + 4));
        else
          Output_WriteFormatted(v31, 0, itemFile, (int)aNull_32, itemsInFile);
        ++itemsInFile;
        itemFile = Rules_ConstructCodeFileClose(itemFile, &itemsInFile, maxIndices, &arrayVersion, 0, 0);
        Enum = (int *)Module_NextEnum((int)Enum);
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
      Output_WriteFormatted(v33, v32, moduleFile, (int)Lexer_ArrayClose, itemsInFile);
      fclose_(v34);
      if ( portItemCount )
        return Compiler_WritePortItemTableFile(v41, v40, v44, v42, maxIndices, &fileVersion);
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
  int v7; // eax
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
  const char *v29; // [esp+18h] [ebp-1Ch]
  const char *v30; // [esp+1Ch] [ebp-18h]
  int v31; // [esp+20h] [ebp-14h]
  int v32; // [esp+24h] [ebp-10h]

  v30 = fileName;
  v29 = fileID;
  v31 = headerFP;
  v32 = imageID;
  theDefmodule = 0;
  thePortItem = 0;
  count = 0;
  importChecked = 0;
  exportChecked = 0;
  arrayVersion = 1;
  fp = 0;
  thePortItem = (int *)Module_NextPortItemEnum(&theDefmodule, (int *)&thePortItem, &exportChecked, &importChecked);
  if ( thePortItem )
  {
    while ( 1 )
    {
      v7 = Rules_ConstructCodeFileOpen(
             fp,
             v30,
             v32,
             v29,
             fileVersion,
             arrayVersion,
             v31,
             (char)aStructPortitem,
             *(const char **)(*(_DWORD *)(g_ClipsDefmoduleCompilerItem + 20) + 8),
             0,
             0);
      portItemFile = v7;
      fp = v7;
      if ( !v7 )
        break;
      Output_WriteFormatted(v9, v8, v7, (int)asc_50D6C8, theDefmodule);
      Compiler_WriteSymbolReference(portItemFile, *thePortItem, v11);
      Output_WriteFormatted(v13, v12, portItemFile, (int)asc_50D6E4, theDefmodule);
      Compiler_WriteSymbolReference(portItemFile, thePortItem[1], v14);
      Output_WriteFormatted(v16, v15, portItemFile, (int)asc_50D6E4, theDefmodule);
      Compiler_WriteSymbolReference(portItemFile, thePortItem[2], v17);
      Output_WriteFormatted(v19, v18, portItemFile, (int)asc_50D6E4, theDefmodule);
      if ( thePortItem[3] )
        Output_WriteFormatted(v32, (count + 1) % maxIndices, portItemFile, (int)aSD_DD_10, *(_DWORD *)(*(_DWORD *)(g_ClipsDefmoduleCompilerItem + 20) + 8));
      else
        Output_WriteFormatted(v21, v20, portItemFile, (int)aNull_32, theDefmodule);
      ++count;
      Rules_ConstructCodeFileClose(fp, &count, maxIndices, &arrayVersion, 0, 0);
      thePortItem = (int *)Module_NextPortItemEnum(&theDefmodule, (int *)&thePortItem, &exportChecked, &importChecked);
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
      *thePortItem = *(_DWORD *)(*thePortItem + 12);
    currentPortItem = *thePortItem;
    if ( *thePortItem )
      return currentPortItem;
    if ( !*importChecked )
    {
      *thePortItem = *(_DWORD *)(*theDefmodule + 12);
      *importChecked = 1;
      if ( !*thePortItem )
      {
        *thePortItem = *(_DWORD *)(*theDefmodule + 16);
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
    *thePortItem = *(_DWORD *)(*theDefmodule + 16);
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
unsigned int  Rules_EvalObjectSlotBoundVariableEqual(int theValue, int theResult, int a3, double a4)
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
  int v15; // [esp+1Ch] [ebp-8h]

  v15 = a3;
  compareInfo = *(_DWORD *)(theValue + 16);
  if ( (*(_BYTE *)(compareInfo + 1) & 2) != 0 )
  {
    Parser_ParseForm(*(__int16 **)(g_ClipsCurrentExpression + 6), &v12, compareInfo, a4);
    boundField = *(__int16 **)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10);
  }
  else
  {
    boundField = *(__int16 **)(g_ClipsCurrentExpression + 6);
    if ( (*(_DWORD *)(g_ObjectPatternActiveClassNode + 4) & 0xFC) == 0x10 )
    {
      theSegment = *(_DWORD *)(g_ObjectPatternActiveClassNode + 8);
      if ( (*(_BYTE *)(compareInfo + 1) & 4) != 0 )
      {
        comparisonType = *(__int16 *)(theSegment + 6 * (*(_DWORD *)compareInfo & 0x7F) + 14);
        fieldIndex = *(_DWORD *)compareInfo & 0x7F;
      }
      else
      {
        comparisonType = *(__int16 *)(theSegment + 6 * (*(_DWORD *)(theSegment + 6) - ((*(_DWORD *)compareInfo & 0x7F) + 1)) + 14);
        fieldIndex = *(_DWORD *)(theSegment + 6) - ((*(_DWORD *)compareInfo & 0x7F) + 1);
      }
      fieldValue = *(_DWORD *)(theSegment + 6 * fieldIndex + 16);
    }
    else
    {
      comparisonType = *(_DWORD *)(g_ObjectPatternActiveClassNode + 4) << 24 >> 26;
      fieldValue = *(_DWORD *)(g_ObjectPatternActiveClassNode + 8);
    }
    comparisonValue = fieldValue;
  }
  if ( *boundField == comparisonType && comparisonValue == *(_DWORD *)(boundField + 1) )
    resultBits = *(_DWORD *)compareInfo << 24;
  else
    resultBits = *(_DWORD *)compareInfo << 23;
  result = resultBits >> 31;
  *(_DWORD *)(theResult + 4) = 2;
  if ( result )
    *(_DWORD *)(theResult + 8) = g_ClipsTrueSymbol;
  else
    *(_DWORD *)(theResult + 8) = g_ClipsFalseSymbol;
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
  matchVar = *(_DWORD *)(theValue + 16);
  Rules_ResolveJoinBindingRecord((unsigned __int8)*(_DWORD *)(matchVar + 4) - 1, &theInstance, v6);
  Rules_FetchObjectSlotFieldSimpleCore(v3, theInstance, (int)v3, matchVar);
  return 1;
}
// 4D8B66: variable 'v3' is possibly undefined

//----- (004D8B90) --------------------------------------------------------
signed int  Rules_FetchObjectSlotFieldRecord(int theValue, _DWORD *theResult)
{
  Rules_FetchObjectSlotFieldRecordCore(theResult, (_DWORD *)g_ClipsObjectReteCurrentInstance, *(_DWORD *)(theValue + 16), (_DWORD *)g_ObjectPatternMarkerListHead);
  return 1;
}
// 51B478: using guessed type int dword_51B478;
// 51B484: using guessed type int dword_51B484;

//----- (004D8BD0) --------------------------------------------------------
signed int  Rules_FetchObjectSlotFieldSimple(int theValue, _DWORD *theResult, int theMarks)
{
  Rules_FetchObjectSlotFieldSimpleCore(theResult, (_DWORD *)g_ClipsObjectReteCurrentInstance, theMarks, *(_DWORD *)(theValue + 16));
  return 1;
}
// 51B478: using guessed type int dword_51B478;

//----- (004D8C00) --------------------------------------------------------
signed int  Rules_EvalObjectSlotIndexInRange(int theValue, int theResult)
{
  int rangeBitmap; // ecx
  unsigned int minLength; // eax

  *(_DWORD *)(theResult + 4) = 2;
  *(_DWORD *)(theResult + 8) = g_ClipsFalseSymbol;
  rangeBitmap = *(_DWORD *)(theValue + 16);
  minLength = *(_DWORD *)rangeBitmap & 0x7FFF;
  if ( minLength > g_ObjectPatternMatchFieldCount || *(char *)(rangeBitmap + 1) < 0 && minLength < g_ObjectPatternMatchFieldCount )
    return 0;
  *(_DWORD *)(theResult + 8) = g_ClipsTrueSymbol;
  return 1;
}
// 51B480: using guessed type int dword_51B480;
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (004D8C60) --------------------------------------------------------
unsigned int  Rules_EvalObjectSlotFieldsEqual(int theValue, int theResult)
{
  unsigned int *compareInfo; // eax
  int slotNameMap; // esi
  int slotArray; // ecx
  int firstSlot; // ebx
  int secondSlot; // ecx
  unsigned int resultBits; // eax
  unsigned int result; // eax

  compareInfo = *(unsigned int **)(theValue + 16);
  slotNameMap = *(_DWORD *)(*(_DWORD *)(g_ClipsObjectReteCurrentInstance + 44) + 60);
  slotArray = *(_DWORD *)(g_ClipsObjectReteCurrentInstance + 72);
  firstSlot = *(_DWORD *)(slotArray + 4 * *(_DWORD *)(slotNameMap + 4 * (*compareInfo & 0x7FFF)) - 4);
  secondSlot = *(_DWORD *)(slotArray + 4 * *(_DWORD *)(slotNameMap + 4 * ((2 * *compareInfo) >> 17)) - 4);
  if ( *(_DWORD *)(firstSlot + 4) << 24 >> 26 == *(_DWORD *)(secondSlot + 4) << 24 >> 26 && *(_DWORD *)(firstSlot + 8) == *(_DWORD *)(secondSlot + 8) )
    resultBits = *compareInfo << 16;
  else
    resultBits = *compareInfo;
  result = resultBits >> 31;
  *(_DWORD *)(theResult + 4) = 2;
  if ( result )
    *(_DWORD *)(theResult + 8) = g_ClipsTrueSymbol;
  else
    *(_DWORD *)(theResult + 8) = g_ClipsFalseSymbol;
  return result;
}
// 51B478: using guessed type int dword_51B478;
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (004D8CF0) --------------------------------------------------------
unsigned int  Rules_EvalObjectSlotElementFieldEqual(int theValue, int theResult)
{
  unsigned int *compareInfo; // esi
  int fieldPtr; // eax
  int secondSlot; // edx
  unsigned int resultBits; // eax
  unsigned int result; // eax

  compareInfo = *(unsigned int **)(theValue + 16);
  fieldPtr = Rules_ResolveObjectSlotFieldPointer(g_ClipsObjectReteCurrentInstance, *compareInfo & 0x7FFF, compareInfo[1] & 0x7F, compareInfo[1] << 24 >> 31);
  secondSlot = *(_DWORD *)(*(_DWORD *)(g_ClipsObjectReteCurrentInstance + 72)
                 + 4 * *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsObjectReteCurrentInstance + 44) + 60) + 4 * ((2 * *compareInfo) >> 17))
                 - 4);
  if ( *(_WORD *)fieldPtr == *(_DWORD *)(secondSlot + 4) << 24 >> 26 && *(_DWORD *)(fieldPtr + 2) == *(_DWORD *)(secondSlot + 8) )
    resultBits = *compareInfo << 16;
  else
    resultBits = *compareInfo;
  result = resultBits >> 31;
  *(_DWORD *)(theResult + 4) = 2;
  if ( result )
    *(_DWORD *)(theResult + 8) = g_ClipsTrueSymbol;
  else
    *(_DWORD *)(theResult + 8) = g_ClipsFalseSymbol;
  return result;
}
// 51B478: using guessed type int dword_51B478;
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (004D8D90) --------------------------------------------------------
unsigned int  Rules_EvalObjectSlotElementsEqual(int theValue, int theResult)
{
  unsigned int *compareInfo; // esi
  __int16 *firstField; // ebp
  __int16 *secondField; // eax
  unsigned int resultBits; // eax
  unsigned int result; // eax

  compareInfo = *(unsigned int **)(theValue + 16);
  firstField = (__int16 *)Rules_ResolveObjectSlotFieldPointer(g_ClipsObjectReteCurrentInstance, *compareInfo & 0x7FFF, compareInfo[1] & 0x7F, compareInfo[1] << 24 >> 31);
  secondField = (__int16 *)Rules_ResolveObjectSlotFieldPointer(g_ClipsObjectReteCurrentInstance, (2 * *compareInfo) >> 17, compareInfo[1] << 17 >> 25, compareInfo[1] << 16 >> 31);
  if ( *firstField == *secondField && *(_DWORD *)(firstField + 1) == *(_DWORD *)(secondField + 1) )
    resultBits = *compareInfo << 16;
  else
    resultBits = *compareInfo;
  result = resultBits >> 31;
  *(_DWORD *)(theResult + 4) = 2;
  if ( result )
    *(_DWORD *)(theResult + 8) = g_ClipsTrueSymbol;
  else
    *(_DWORD *)(theResult + 8) = g_ClipsFalseSymbol;
  return result;
}
// 51B478: using guessed type int dword_51B478;
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (004D8E30) --------------------------------------------------------
unsigned int  Rules_EvalJoinObjectSlotFieldsEqual(int theValue, int theResult, int theBinds)
{
  _DWORD *v4; // ecx
  int firstSlot; // edi
  unsigned int *v6; // ecx
  int secondSlot; // eax
  unsigned int resultBits; // eax
  unsigned int result; // eax
  int firstInstance; // [esp+0h] [ebp-1Ch] BYREF
  int secondInstance; // [esp+4h] [ebp-18h] BYREF
  _DWORD marksBuffer[5]; // [esp+8h] [ebp-14h] BYREF

  marksBuffer[3] = theBinds;
  Rules_ResolveJoinBindingRecord((unsigned __int8)*(_DWORD *)(*(_DWORD *)(theValue + 16) + 4) - 1, &firstInstance, marksBuffer);
  firstSlot = *(_DWORD *)(4 * *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(firstInstance + 44) + 60) + 4 * (*v4 & 0x7FFF))
                 + *(_DWORD *)(firstInstance + 72)
                 - 4);
  Rules_ResolveJoinBindingRecord((v4[1] << 16 >> 24) - 1, &secondInstance, marksBuffer);
  secondSlot = *(_DWORD *)(*(_DWORD *)(secondInstance + 72)
                 + 4 * *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(secondInstance + 44) + 60) + 4 * ((2 * *v6) >> 17))
                 - 4);
  if ( *(_DWORD *)(firstSlot + 4) << 24 >> 26 == *(_DWORD *)(secondSlot + 4) << 24 >> 26 && *(_DWORD *)(firstSlot + 8) == *(_DWORD *)(secondSlot + 8) )
    resultBits = *v6 << 16;
  else
    resultBits = *v6;
  result = resultBits >> 31;
  *(_DWORD *)(theResult + 4) = 2;
  if ( result )
    *(_DWORD *)(theResult + 8) = g_ClipsTrueSymbol;
  else
    *(_DWORD *)(theResult + 8) = g_ClipsFalseSymbol;
  return result;
}
// 4D8E53: variable 'v4' is possibly undefined
// 4D8E8B: variable 'v6' is possibly undefined
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (004D8F10) --------------------------------------------------------
unsigned int  Rules_EvalJoinObjectSlotElementFieldEqual(int theValue, int theResult, int theBinds)
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
  compareInfo = *(_DWORD **)(theValue + 16);
  Rules_ResolveJoinBindingRecord((unsigned __int8)compareInfo[1] - 1, &firstInstance, marksBuffer);
  Rules_ResolveObjectSlotFieldPointer(firstInstance, *compareInfo & 0x7FFF, compareInfo[1] << 9 >> 25, *compareInfo >> 31);
  Rules_ResolveJoinBindingRecord((compareInfo[1] << 16 >> 24) - 1, &secondInstance, marksBuffer);
  secondSlot = *(_DWORD *)(4 * *(_DWORD *)(4 * ((unsigned int)(2 * *compareInfo) >> 17) + *(_DWORD *)(*(_DWORD *)(secondInstance + 44) + 60))
                 + *(_DWORD *)(secondInstance + 72)
                 - 4);
  if ( *(_WORD *)firstFieldPtr == *(_DWORD *)(secondSlot + 4) << 24 >> 26 && *(_DWORD *)(firstFieldPtr + 2) == *(_DWORD *)(secondSlot + 8) )
    resultBits = *compareInfo << 16;
  else
    resultBits = compareInfo[1] << 8;
  result = resultBits >> 31;
  *(_DWORD *)(theResult + 4) = 2;
  if ( result )
    *(_DWORD *)(theResult + 8) = g_ClipsTrueSymbol;
  else
    *(_DWORD *)(theResult + 8) = g_ClipsFalseSymbol;
  return result;
}
// 4D8F9C: variable 'v5' is possibly undefined
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (004D9000) --------------------------------------------------------
unsigned int  Rules_EvalJoinObjectSlotElementsEqual(int theValue, int theResult)
{
  unsigned int *compareInfo; // esi
  __int16 *firstField; // ebp
  __int16 *secondField; // eax
  unsigned int resultBits; // eax
  unsigned int result; // eax
  int firstInstance; // [esp+0h] [ebp-20h] BYREF
  int secondInstance; // [esp+4h] [ebp-1Ch] BYREF
  _DWORD marksBuffer[6]; // [esp+8h] [ebp-18h] BYREF

  compareInfo = *(unsigned int **)(theValue + 16);
  Rules_ResolveJoinBindingRecord((unsigned __int8)compareInfo[1] - 1, &firstInstance, marksBuffer);
  firstField = (__int16 *)Rules_ResolveObjectSlotFieldPointer(firstInstance, *compareInfo & 0x7FFF, compareInfo[1] << 9 >> 25, compareInfo[1] << 8 >> 31);
  Rules_ResolveJoinBindingRecord((compareInfo[1] << 16 >> 24) - 1, &secondInstance, marksBuffer);
  secondField = (__int16 *)Rules_ResolveObjectSlotFieldPointer(firstInstance, (2 * *compareInfo) >> 17, (2 * compareInfo[1]) >> 25, (unsigned __int64)compareInfo[1] >> 31);
  if ( *firstField == *secondField && *(_DWORD *)(firstField + 1) == *(_DWORD *)(secondField + 1) )
    resultBits = *compareInfo << 16;
  else
    resultBits = *compareInfo;
  result = resultBits >> 31;
  *(_DWORD *)(theResult + 4) = 2;
  if ( result )
    *(_DWORD *)(theResult + 8) = g_ClipsTrueSymbol;
  else
    *(_DWORD *)(theResult + 8) = g_ClipsFalseSymbol;
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
  if ( *(char *)(matchVar + 3) < 0 )
  {
    returnValue[1] = 7;
    returnValue[2] = theInstance;
  }
  else if ( (*(_WORD *)matchVar & 0x7FFF) != 0 )
  {
    slotNameId = *(_DWORD *)matchVar & 0x7FFF;
    if ( slotNameId == 1 )
    {
      returnValue[1] = 8;
      result = (_DWORD *)result[7];
      returnValue[2] = result;
    }
    else
    {
      slotOffset = 4 * (*(_DWORD *)(*(_DWORD *)(result[11] + 60) + 4 * slotNameId) - 1);
      slotArrayBase = result[18];
      slotPtr = (int *)(slotArrayBase + slotOffset);
      if ( result[5] )
      {
        if ( !g_Rules_JoinOperationInProgress )
        {
          slotIndex = ((int)slotPtr - slotArrayBase) >> 2;
          basisSlot = 12 * slotIndex + result[5];
          if ( *(_DWORD *)(basisSlot + 8) )
            slotPtr = &basisSlot;
        }
      }
      if ( (*(_BYTE *)(matchVar + 4) & 1) != 0 )
      {
        returnValue[1] = *(_DWORD *)(*slotPtr + 4) << 24 >> 26;
        result = *(_DWORD **)(*slotPtr + 8);
        fieldType = returnValue[1];
        returnValue[2] = result;
        if ( fieldType == 4 )
        {
          returnValue[3] = 0;
          result = (_DWORD *)(*(_DWORD *)(*(_DWORD *)(*slotPtr + 8) + 6) - 1);
          returnValue[4] = result;
        }
      }
      else
      {
        fieldPosition = Rules_ComputeObjectMultifieldSegmentOffset(extentMarks, *slotPtr, &extentSize, (unsigned int)(2 * *(_DWORD *)matchVar) >> 24);
        fieldIndex = fieldPosition - 1;
        if ( extentSize == -1 )
        {
          slotValue = *slotPtr;
          if ( (**(_BYTE **)*slotPtr & 2) != 0 )
          {
            returnValue[1] = *(__int16 *)(*(_DWORD *)(slotValue + 8) + 6 * fieldIndex + 14);
            result = *(_DWORD **)(*(_DWORD *)(*slotPtr + 8) + 6 * fieldIndex + 16);
          }
          else
          {
            returnValue[1] = *(_DWORD *)(slotValue + 4) << 24 >> 26;
            result = *(_DWORD **)(*slotPtr + 8);
          }
          returnValue[2] = result;
        }
        else
        {
          returnValue[1] = 4;
          returnValue[2] = *(_DWORD *)(*slotPtr + 8);
          returnValue[3] = fieldIndex;
          result = (_DWORD *)(extentSize + fieldPosition - 2);
          returnValue[4] = result;
        }
      }
    }
  }
  else
  {
    returnValue[1] = 2;
    result = (_DWORD *)Rules_GetConstructNameSymbol(theInstance[11]);
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
  slotOffset = 4 * (*(_DWORD *)(*(_DWORD *)(theInstance[11] + 60) + 4 * (*(_DWORD *)matchVar & 0x7FFF)) - 1);
  slotArrayBase = theInstance[18];
  slotPtr = (_DWORD *)(slotArrayBase + slotOffset);
  if ( theInstance[5] )
  {
    if ( !g_Rules_JoinOperationInProgress )
    {
      basisSlotBuffer[0] = 12 * (((int)slotPtr - slotArrayBase) >> 2) + theInstance[5];
      if ( *(_DWORD *)(basisSlotBuffer[0] + 8) )
        slotPtr = basisSlotBuffer;
    }
  }
  slotValue = *(_DWORD *)(*slotPtr + 8);
  fieldsStart = slotValue + 14;
  if ( *(char *)(matchVar + 1) >= 0 )
  {
    fieldOffset = 3 * (*(_DWORD *)(slotValue + 6) - (((unsigned int)(2 * *(_DWORD *)matchVar) >> 25) + 1));
    result[1] = *(__int16 *)(fieldsStart + 2 * fieldOffset);
    result[2] = *(_DWORD *)(fieldsStart + 2 * fieldOffset + 2);
  }
  else if ( *(char *)(matchVar + 2) >= 0 )
  {
    fieldIndex = *(_DWORD *)matchVar << 9 >> 25;
    result[1] = *(__int16 *)(fieldsStart + 6 * fieldIndex);
    result[2] = *(_DWORD *)(fieldsStart + 6 * fieldIndex + 2);
  }
  else
  {
    result[1] = 4;
    result[2] = slotValue;
    result[3] = *(_DWORD *)matchVar << 9 >> 25;
    result[4] = *(_DWORD *)(slotValue + 6) - (((unsigned int)(2 * *(_DWORD *)matchVar) >> 25) + 1);
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
  for ( i = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)slotPtr + 8) + 12); markerList; markerList = (_DWORD *)markerList[4] )
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
    markerList = (_DWORD *)markerList[4];
    adjustedIndex += markerSpan;
  }
  return adjustedIndex;
}

//----- (004D9430) --------------------------------------------------------
int  Rules_ResolveObjectSlotFieldPointer(int theInstance, int slotNameID, int fieldIndex, int fromBeginning)
{
  int segment; // eax
  int fieldsBase; // edx

  segment = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(theInstance + 72)
                             + 4 * *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(theInstance + 44) + 60) + 4 * slotNameID)
                             - 4)
                 + 8);
  fieldsBase = segment + 14;
  if ( fromBeginning )
    return fieldsBase + 6 * fieldIndex;
  else
    return fieldsBase + 6 * (*(_DWORD *)(segment + 6) - fieldIndex - 1);
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
void Fpu_ClearExceptions()
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

  Parser_NextToken(readSource, (int)theToken);
  if ( theToken[0] == 92 || theToken[0] == 91 )
  {
    Parser_ReportSyntaxError();
    return 0;
  }
  else
  {
    v4 = AST_AllocNode();
    *(_DWORD *)v4 = 17;
    topNode = v4;
    BYTE1(v4) = *(_BYTE *)(v4 + 8);
    *(_DWORD *)(topNode + 32) = 0;
    *(_DWORD *)(topNode + 40) = 1;
    *(_BYTE *)(topNode + 8) = BYTE1(v4) & 0xFE;
    nameNode = (_DWORD *)AST_AllocNode();
    *(_DWORD *)(topNode + 68) = nameNode;
    *nameNode = 2;
    *(_BYTE *)(*(_DWORD *)(topNode + 68) + 8) &= ~1u;
    *(_DWORD *)(*(_DWORD *)(topNode + 68) + 4) = *theDeftemplate;
    errorFlag[0] = 0;
    firstSlot = Lexer_ParseRuleRHS(readSource, theToken, errorFlag, (int)theDeftemplate);
    if ( errorFlag[0] )
    {
      AST_FreeNode(firstSlot);
      AST_FreeNode(topNode);
      return 0;
    }
    else
    {
      *(_DWORD *)(topNode + 64) = firstSlot;
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
  int v11; // eax
  int v13; // edx
  int v14; // edx
  int position; // [esp+0h] [ebp-1Ch] BYREF
  int v16; // [esp+4h] [ebp-18h]
  _DWORD *v17; // [esp+8h] [ebp-14h]
  unsigned int *lastSlot; // [esp+Ch] [ebp-10h]

  v16 = theDeftemplate;
  v17 = error;
  firstSlot = 0;
  tokenType = *theToken;
  lastSlot = 0;
  if ( tokenType == 101 )
    return firstSlot;
  while ( 1 )
  {
    IO_OutNewline();
    IO_OutWriteToken(asc_50D750);
    IO_OutWriteToken((char *)theToken[2]);
    if ( *theToken != 100 || (Parser_NextToken(readSource, (int)theToken), *theToken != 2) )
    {
      *v17 = 1;
      Parser_ReportSyntaxError();
LABEL_12:
      v11 = firstSlot;
      goto LABEL_13;
    }
    slotPtr = Lexer_FindTemplateSlot(v16, theToken[1], &position);
    if ( !slotPtr )
    {
      v13 = v16;
      *v17 = 1;
      Rules_ReportInvalidSlotError(v8, *(_DWORD *)(*(_DWORD *)v13 + 16));
      goto LABEL_12;
    }
    if ( Lexer_CheckDuplicateSlotName(firstSlot, theToken[1]) == 1 )
    {
      *v17 = 1;
      goto LABEL_12;
    }
    nextSlot = Lexer_ParseSlotValueList(readSource, (int)theToken, v17, (int)slotPtr, position + 1);
    if ( *v17 )
      break;
    if ( lastSlot )
      lastSlot[16] = (unsigned int)nextSlot;
    else
      firstSlot = (int)nextSlot;
    while ( nextSlot[16] )
      nextSlot = (unsigned int *)nextSlot[16];
    lastSlot = nextSlot;
    Parser_NextToken(readSource, (int)theToken);
    if ( *theToken == 101 )
      return firstSlot;
  }
  AST_FreeNode(firstSlot);
  v11 = v14;
LABEL_13:
  AST_FreeNode(v11);
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
  if ( (*(_BYTE *)(theSlot + 4) & 1) != 0 )
  {
    nextSlot = Rules_ParsePatternFieldList(readSource, (int *)theToken, v8, 1, position - 1, *(int **)(theSlot + 8), 1);
    if ( !nextSlot )
    {
      *error = 1;
      return 0;
    }
  }
  else
  {
    restrictionNode = Rules_ParsePatternFieldList(readSource, (int *)theToken, *(_DWORD *)theSlot, 0, position - 1, *(int **)(theSlot + 8), 0);
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
  if ( *(_DWORD *)theToken == 101 )
  {
    if ( !nextSlot[17] && (*(_BYTE *)(theSlot + 4) & 1) != 0 )
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
    IO_OutWriteToken(*(char **)(theToken + 8));
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
    existingName = *(_DWORD *)(theSlots + 36);
    if ( slotName == existingName )
      break;
    theSlots = *(_DWORD *)(theSlots + 64);
    if ( !theSlots )
      return 0;
  }
  Rules_ReportAlreadyParsed(existingName, *(_DWORD *)(existingName + 16));
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
    return Rules_BuildConjunctionFromPatternList((int)theLHS);
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
  theNode = Lexer_ParsePatternCE(readSource, 2, (int)Lexer_Token_Arrow, a5, 1, (int)theToken, ruleName);
  v10 = (int)theNode;
  v12 = theNode;
  if ( *error == 1 )
  {
    AST_FreeNode((int)theNode);
    return 0;
  }
  else
  {
    AST_Append(*error, v9);
    result = (_DWORD *)Lexer_ParsePatternCEList(2, error, Lexer_Token_Arrow, readSource, a5);
    if ( *error == 1 )
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
int  Lexer_ParseDeclareOptions(_DWORD *error, double a2)
{
  int salienceParsed; // ebx
  int v4; // edx
  int v5; // ecx
  int v6; // ecx
  int autoFocusParsed; // ebp
  int v8; // ecx
  int result; // eax
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // edx
  _DWORD theToken[7]; // [esp+0h] [ebp-1Ch] BYREF

  IO_OutWriteToken(asc_50D764);
  salienceParsed = 0;
  Parser_NextToken(v5, v4);
  autoFocusParsed = 0;
  if ( theToken[0] == 100 )
  {
    while ( 1 )
    {
      Parser_NextToken(v6, (int)theToken);
      if ( theToken[0] != 2 )
      {
LABEL_3:
        Parser_ReportSyntaxError();
LABEL_4:
        *error = 1;
LABEL_5:
        result = AST_Free(g_ClipsParsedFormAst);
        g_ClipsParsedFormAst = 0;
        return result;
      }
      if ( !strcmp_(v8, aSalience) )
      {
        if ( salienceParsed )
          goto LABEL_18;
        Lexer_ParseSalienceOption(error, a2);
        salienceParsed = 1;
      }
      else
      {
        if ( strcmp_(v10, aAutoFocus) )
          goto LABEL_3;
        if ( autoFocusParsed )
        {
LABEL_18:
          Rules_ReportAlreadyParsed(v10, 0);
          goto LABEL_4;
        }
        autoFocusParsed = 1;
        Lexer_ParseAutoFocusOption(v10);
      }
      if ( *error )
        goto LABEL_5;
      Parser_NextToken(v11, (int)theToken);
      if ( theToken[0] != 101 )
      {
        IO_OutNewline();
        IO_OutWriteToken(asc_50D764);
        IO_OutWriteToken((char *)theToken[2]);
        AST_Free(g_ClipsParsedFormAst);
        g_ClipsParsedFormAst = v13;
        result = Parser_ReportSyntaxError();
        *error = 1;
        return result;
      }
      Parser_NextToken(v12, (int)theToken);
      if ( theToken[0] == 101 )
        break;
      if ( theToken[0] != 100 )
      {
        AST_Free(g_ClipsParsedFormAst);
        g_ClipsParsedFormAst = 0;
        result = Parser_ReportSyntaxError();
        *error = 1;
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
    *error = 1;
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
int  Lexer_ParseSalienceOption(_DWORD *error, double a2)
{
  int v2; // ecx
  int result; // eax
  _DWORD *v4; // edx
  int v5; // ecx
  int salienceValue; // ecx
  int parsedType; // [esp+0h] [ebp-1Ch]
  int parsedValueNode; // [esp+4h] [ebp-18h]

  IO_OutWriteToken(asc_50D764);
  result = Parser_ParseSingleExpression(v2, 0, v2);
  g_ClipsParsedFormAst = result;
  if ( result )
  {
    Lexer_ErrorRecover(0);
    if ( Parser_ParseForm((__int16 *)g_ClipsParsedFormAst, v4, v5, a2) )
    {
      result = Rules_SalienceInformationError();
      *error = 1;
    }
    else if ( parsedType == 1 )
    {
      salienceValue = *(_DWORD *)(parsedValueNode + 16);
      if ( salienceValue > 10000 || salienceValue < -10000 )
      {
        result = Rules_SalienceRangeError();
        *error = 1;
      }
      else
      {
        result = g_ClipsParsedFormAst;
        if ( *(_WORD *)g_ClipsParsedFormAst == 1 )
        {
          result = AST_Free(g_ClipsParsedFormAst);
          g_ClipsParsedFormAst = 0;
        }
        g_CLIPS_CurrentRuleSalience = salienceValue;
      }
    }
    else
    {
      result = Rules_SalienceNonIntegerError();
      *error = 1;
    }
  }
  else
  {
    *error = 1;
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
int  Lexer_ParseAutoFocusOption(int readSource)
{
  int v2; // edx
  int v3; // ecx
  int result; // eax
  int v5; // ecx
  _DWORD *errorPtr; // ecx
  int tokenType; // [esp+0h] [ebp-14h]

  IO_OutWriteToken(asc_50D764);
  Parser_NextToken(readSource, v2);
  if ( tokenType != 2 )
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
    *errorPtr = 1;
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
_DWORD * Lexer_ParsePatternCE(int readSource, int terminator, int terminatorString, double a4, int allowDeclaration, int firstToken, int ruleName)
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
  int theToken; // [esp+0h] [ebp-18h] BYREF

  if ( firstToken )
    qmemcpy(&theToken, (const void *)firstToken, 12);
  else
    Parser_NextToken(readSource, (int)&theToken);
  if ( theToken != 100 )
  {
    if ( theToken == 15 )
    {
      result = (_DWORD *)Lexer_ParsePatternBinding((int)v9, v9);
      if ( *v11 != 1 )
        return result;
LABEL_33:
      AST_FreeNode((int)result);
      return 0;
    }
    if ( terminator == theToken && !strcmp_(v9, terminatorString) )
      return 0;
LABEL_15:
    Parser_ReportSyntaxError();
    *v14 = 1;
    return 0;
  }
  Parser_NextToken(readSource, (int)&theToken);
  if ( theToken != 2 )
    goto LABEL_15;
  if ( allowDeclaration && !strcmp_(v12, aDeclare) )
  {
    if ( !ruleName )
      Rules_ReportSystemError((int)v12, 1);
    Lexer_ParseDeclareOptions(v12, a4);
    result = 0;
    if ( *v13 == 1 )
      goto LABEL_33;
  }
  else if ( !strcmp_(v12, aTest_0) )
  {
    result = (_DWORD *)Lexer_ParseTestCE(readSource, v15, (int)v15);
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
    result = (_DWORD *)Lexer_ParseConnectiveCE(v17, readSource, a4);
    if ( *v18 == 1 )
      goto LABEL_33;
  }
  else
  {
    result = Rules_DispatchPatternTypeParser(&theToken, (int)v17, v17);
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
signed int  Lexer_ParseConnectiveCE(_DWORD *error, int readSource, double a3)
{
  int connectorValue; // esi
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  char *connectorString; // eax
  int v8; // edx
  signed int v9; // ecx
  signed int v10; // edx
  int v11; // ecx
  signed int theNode; // ebp
  int logicalBits; // edi
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
  int savedNegatedFlag; // [esp+4h] [ebp-18h]
  int logicalCE; // [esp+8h] [ebp-14h]

  Rules_IncrementIndentDepth(5);
  connectorValue = 0;
  logicalCE = 0;
  if ( !strcmp_(v4, aOr_1) )
  {
    connectorValue = 82;
    connectorString = asc_50D870;
    goto LABEL_4;
  }
  if ( !strcmp_(v5, aAnd_1) )
  {
    connectorValue = 81;
    connectorString = asc_50D764;
LABEL_4:
    IO_OutWriteToken(connectorString);
    goto LABEL_5;
  }
  if ( !strcmp_(v6, aNot_1) )
  {
    connectorValue = 83;
    connectorString = asc_50D764;
    goto LABEL_4;
  }
  if ( !strcmp_(v15, aExists_0) )
  {
    AST_Append(v17, v16);
    connectorValue = 86;
  }
  else if ( !strcmp_(v17, aForall_0) )
  {
    AST_Append(v19, v18);
    connectorValue = 87;
  }
  else if ( !strcmp_(v19, aLogical_0) )
  {
    AST_Append(v21, v20);
    connectorValue = 81;
    logicalCE = 1;
  }
LABEL_5:
  if ( g_Parser_InsideNegatedCEFlag && logicalCE )
  {
    Rules_PrintErrorID((int)aRulelhs, 1, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aTheLogicalCeCa, v22);
    *error = 1;
    return 0;
  }
  savedNegatedFlag = g_Parser_InsideNegatedCEFlag;
  if ( connectorValue == 83 || connectorValue == 86 || connectorValue == 87 )
    g_Parser_InsideNegatedCEFlag = 1;
  Lexer_ParsePatternCEList(101, error, asc_50D94C, readSource, a3);
  g_Parser_InsideNegatedCEFlag = savedNegatedFlag;
  Rules_DecrementIndentDepth(5);
  if ( *error == 1 )
  {
    AST_FreeNode(v8);
    return 0;
  }
  if ( logicalCE )
    AST_MarkLogicalCEChain(v8);
  if ( !v9 )
  {
    Parser_ReportSyntaxError();
    *error = 1;
    return 0;
  }
  if ( connectorValue == 83 && *(_DWORD *)(v9 + 68) || connectorValue == 87 && !*(_DWORD *)(v9 + 68) )
  {
    Parser_ReportSyntaxError();
    AST_FreeNode(v23);
    *error = 1;
    return 0;
  }
  if ( (connectorValue == 81 || connectorValue == 82) && !*(_DWORD *)(v9 + 68) )
  {
    *(_BYTE *)(v9 + 8) &= ~2u;
    result = v9;
    *(_DWORD *)(v9 + 8) |= 2 * (logicalCE & 1);
    return result;
  }
  v10 = AST_AllocNode();
  theNode = v10;
  *(_BYTE *)(v10 + 8) &= ~2u;
  logicalBits = 2 * (logicalCE & 1);
  *(_DWORD *)(v10 + 8) |= logicalBits;
  if ( connectorValue == 81 || connectorValue == 82 || connectorValue == 83 )
  {
    *(_DWORD *)v10 = connectorValue;
    *(_DWORD *)(v10 + 64) = v11;
    return v10;
  }
  if ( connectorValue != 86 )
  {
    if ( connectorValue == 87 )
    {
      *(_DWORD *)v10 = 83;
      v24 = *(_DWORD *)(v11 + 68);
      *(_DWORD *)(v11 + 68) = 0;
      v25 = (_DWORD *)AST_AllocNode();
      *(_DWORD *)(v26 + 64) = v25;
      *v25 = 81;
      v27 = *(_DWORD *)(v26 + 64);
      *(_BYTE *)(v27 + 8) &= ~2u;
      *(_DWORD *)(v27 + 8) |= logicalBits;
      *(_DWORD *)(*(_DWORD *)(v26 + 64) + 64) = v28;
      v29 = AST_AllocNode();
      v30 = v24;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v31 + 64) + 64) + 68) = v29;
      **(_DWORD **)(*(_DWORD *)(*(_DWORD *)(v31 + 64) + 64) + 68) = 83;
      v32 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v31 + 64) + 64) + 68);
      *(_BYTE *)(v32 + 8) &= ~2u;
      *(_DWORD *)(v32 + 8) |= logicalBits;
      v33 = *(_DWORD *)(v24 + 68);
      v34 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v31 + 64) + 64) + 68);
      if ( v33 )
      {
        v43 = (_DWORD *)AST_AllocNode();
        *(_DWORD *)(v34 + 64) = v43;
        *v43 = 81;
        v44 = *(_DWORD *)(v34 + 64);
        *(_BYTE *)(v44 + 8) &= ~2u;
        *(_DWORD *)(v44 + 8) |= logicalBits;
        *(_DWORD *)(*(_DWORD *)(v34 + 64) + 64) = v45;
      }
      else
      {
        *(_DWORD *)(v34 + 64) = v30;
      }
      return theNode;
    }
    return v10;
  }
  *(_DWORD *)v10 = 83;
  v35 = (_DWORD *)AST_AllocNode();
  *(_DWORD *)(v36 + 64) = v35;
  *v35 = 83;
  v38 = *(_DWORD *)(v36 + 64);
  *(_BYTE *)(v38 + 8) &= ~2u;
  *(_DWORD *)(v38 + 8) |= logicalBits;
  if ( *(_DWORD *)(v37 + 68) )
  {
    v39 = AST_AllocNode();
    *(_DWORD *)(*(_DWORD *)(v40 + 64) + 64) = v39;
    **(_DWORD **)(*(_DWORD *)(v40 + 64) + 64) = 81;
    v41 = *(_DWORD *)(*(_DWORD *)(v40 + 64) + 64);
    *(_BYTE *)(v41 + 8) &= ~2u;
    *(_DWORD *)(v41 + 8) |= logicalBits;
    *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v40 + 64) + 64) + 64) = v42;
  }
  else
  {
    *(_DWORD *)(*(_DWORD *)(v36 + 64) + 64) = v37;
  }
  return theNode;
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
int  Lexer_ParsePatternCEList(int terminator, _DWORD *error, char *terminatorString, int readSource, double a5)
{
  int lastNode; // edi
  int newNode; // eax
  int v8; // edx
  int v10; // edx
  int v11; // ecx
  int head; // [esp+8h] [ebp-10h]

  lastNode = 0;
  head = 0;
  while ( 1 )
  {
    newNode = Lexer_ParsePatternCE(readSource, terminator, (int)terminatorString, a5, 0, 0, 0);
    if ( *error )
    {
      AST_FreeNode(head);
      return 0;
    }
    if ( !newNode )
      break;
    if ( lastNode )
      *(_DWORD *)(lastNode + 68) = newNode;
    else
      head = newNode;
    AST_Append(0, newNode);
    lastNode = v8;
  }
  IO_OutNewline();
  IO_OutNewline();
  if ( terminator != 101 )
    AST_Append(v11, v10);
  IO_OutWriteToken(terminatorString);
  return head;
}
// 4DA929: variable 'v8' is possibly undefined
// 4DA95F: variable 'v11' is possibly undefined
// 4DA95F: variable 'v10' is possibly undefined

//----- (004DA980) --------------------------------------------------------
int  Lexer_ParseTestCE(int readSource, _DWORD *error, int a3)
{
  _DWORD *theNode; // eax
  __int16 *theExpression; // eax
  __int16 *expressionCopy; // eax
  int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v13; // ecx
  _DWORD theToken[6]; // [esp+0h] [ebp-18h] BYREF

  theToken[4] = a3;
  IO_OutWriteToken(asc_50D764);
  theNode = (_DWORD *)AST_AllocNode();
  *theNode = 84;
  theExpression = (__int16 *)Parser_ParseRequiredFunctionCall(readSource, (int)theNode);
  expressionCopy = Rules_CECloneRestrictionExpr(theExpression);
  *(_DWORD *)(v8 + 56) = expressionCopy;
  AST_Free(v9);
  if ( *(_DWORD *)(v10 + 56) )
  {
    Parser_NextToken(readSource, (int)theToken);
    if ( theToken[0] == 101 )
    {
      return v11;
    }
    else
    {
      Parser_ReportSyntaxError();
      *error = 1;
      AST_FreeNode(v13);
      return 0;
    }
  }
  else
  {
    *error = 1;
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
int  Lexer_ParsePatternBinding(int readSource, _DWORD *error)
{
  int v3; // edx
  int v4; // ecx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  int tokenType; // [esp+0h] [ebp-18h]
  int v11; // [esp+14h] [ebp-4h]

  v11 = readSource;
  if ( g_Parser_InsideNegatedCEFlag )
  {
    Rules_PrintErrorID((int)aRulelhs, 2, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAPatternCeCann, v8);
    *error = 1;
    return 0;
  }
  else
  {
    IO_OutWriteToken(asc_50D764);
    Parser_NextToken(v4, v3);
    if ( tokenType == 2 && !strcmp_(v5, asc_50D9B0) )
    {
      IO_OutWriteToken(asc_50D764);
      Parser_NextToken(v7, v6);
    }
    Parser_ReportSyntaxError();
    *error = 1;
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
  int nodeType; // ecx
  int v3; // edx

  for ( i = result; i; i = *(_DWORD *)(i + 68) )
  {
    while ( 1 )
    {
      BYTE1(result) = *(_BYTE *)(i + 8) | 2;
      nodeType = *(_DWORD *)i;
      *(_BYTE *)(i + 8) = BYTE1(result);
      if ( nodeType != 81 && nodeType != 82 && nodeType != 83 )
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
_DWORD * Rules_DispatchPatternTypeParser(_DWORD *theToken, int a2, _DWORD *error)
{
  int v5; // ecx
  signed int newNode; // eax
  char nodeFlags; // dl
  int patternParser; // ecx
  _DWORD *theNode; // ebx
  int v10; // ecx
  int parsedPattern; // eax
  int v13; // ecx

  if ( *theToken != 2 || !strcmp_(a2, asc_50D9C8) || !strcmp_(v5, asc_50D9CC) )
  {
    Parser_ReportSyntaxError();
    *error = 1;
    return 0;
  }
  newNode = AST_AllocNode();
  nodeFlags = *(_BYTE *)(newNode + 8);
  *(_DWORD *)newNode = 80;
  *(_BYTE *)(newNode + 8) = nodeFlags & 0xFE;
  patternParser = g_PatternParserListHead;
  theNode = (_DWORD *)newNode;
  if ( !g_PatternParserListHead )
  {
LABEL_7:
    *error = 1;
    Parser_ReportSyntaxError();
    AST_FreeNode((int)theNode);
    return 0;
  }
  while ( !(*(int (**)(void))(patternParser + 12))() )
  {
    patternParser = *(_DWORD *)(v10 + 92);
    if ( !patternParser )
      goto LABEL_7;
  }
  theNode[6] = v10;
  parsedPattern = (*(int (__fastcall **)(int, _DWORD *))(v10 + 16))(v10, theToken);
  theNode[16] = parsedPattern;
  if ( parsedPattern )
  {
    AST_PropagateDepthTag(theNode, v13);
    return theNode;
  }
  else
  {
    *error = 1;
    AST_FreeNode((int)theNode);
    return 0;
  }
}
// 4DAB66: variable 'v5' is possibly undefined
// 4DAB99: variable 'v10' is possibly undefined
// 4DAC0B: variable 'v13' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51B348: using guessed type int dword_51B348;

//----- (004DAC20) --------------------------------------------------------
_DWORD * AST_PropagateDepthTag(_DWORD *result, int depth)
{
  _DWORD *i; // ecx
  int childNode; // edx

  for ( i = result; i; i = (_DWORD *)i[17] )
  {
    childNode = i[16];
    i[6] = depth;
    if ( childNode )
      result = (_DWORD *)AST_PropagateDepthTag(childNode, depth);
    if ( i[14] )
      result = (_DWORD *)AST_PropagateDepthTag(i[14], depth);
  }
  return result;
}
// 4DAC35: variable 'i' is possibly undefined

//----- (004DAC60) --------------------------------------------------------
_DWORD * AST_MarkNodeFieldBound(_DWORD *result, int theBsaveID)
{
  *(_BYTE *)(*result + 12) |= 2u;
  result[3] = theBsaveID;
  return result;
}

//----- (004DAC70) --------------------------------------------------------
_DWORD * AST_ExtractPatternBindingInfo(_DWORD *result, int theConstruct)
{
  int nextConstruct; // ecx

  *result = *(_DWORD *)(*(_DWORD *)theConstruct + 12) << 16 >> 18;
  result[1] = *(_DWORD *)(**(_DWORD **)(theConstruct + 8) + 24);
  nextConstruct = *(_DWORD *)(theConstruct + 16);
  if ( nextConstruct )
    result[2] = *(_DWORD *)(nextConstruct + 12);
  else
    result[2] = -1;
  return result;
}

//----- (004DACB0) --------------------------------------------------------
int  Rules_BuildIndexedSlotDescriptor(int result, _DWORD *theConstruct, int moduleItemArray, int moduleItemSize, int constructSize, int constructArray)
{
  int nameSymbol; // ecx
  int nextIndex; // ebp

  theConstruct[2] = *(_DWORD *)(result + 4) * moduleItemSize + moduleItemArray;
  nameSymbol = *(_DWORD *)(g_ClipsBloadSymbolPointerArray + 4 * *(_DWORD *)result);
  *theConstruct = nameSymbol;
  ++*(_DWORD *)(nameSymbol + 4);
  nextIndex = *(_DWORD *)(result + 8);
  if ( nextIndex == -1 )
  {
    theConstruct[4] = 0;
  }
  else
  {
    result = nextIndex * constructSize;
    theConstruct[4] = nextIndex * constructSize + constructArray;
  }
  theConstruct[1] = 0;
  theConstruct[3] = 0;
  return result;
}
// 54E674: using guessed type int dword_54E674;

//----- (004DAD10) --------------------------------------------------------
int  Rules_ReleaseSymbolReference(int *symbolPtr, int a2)
{
  return Rules_DecrementSymbolCount(*symbolPtr, a2);
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
_DWORD * Module_UpdateItemHeader(_DWORD *result, _DWORD *theHeader, int itemArray, int itemSize)
{
  int firstItemIndex; // esi
  int firstItemOffset; // esi
  int lastItemOffset; // ebx

  *theHeader = 32 * *result + g_ClipsModuleArrayBase;
  firstItemIndex = result[1];
  if ( firstItemIndex == -1 )
  {
    theHeader[1] = 0;
    theHeader[2] = 0;
  }
  else
  {
    firstItemOffset = itemSize * firstItemIndex;
    lastItemOffset = result[2] * itemSize;
    result = (_DWORD *)(itemArray + firstItemOffset);
    theHeader[1] = itemArray + firstItemOffset;
    theHeader[2] = lastItemOffset + itemArray;
  }
  return result;
}
// 51C704: using guessed type int dword_51C704;

//----- (004DADC0) --------------------------------------------------------
_DWORD * Module_AssignBsaveItemHeaderIndices(_DWORD *result, _DWORD *theHeader)
{
  int firstItem; // ecx

  *result = *(_DWORD *)(*theHeader + 24);
  firstItem = theHeader[1];
  if ( firstItem )
  {
    result[1] = *(_DWORD *)(firstItem + 12);
    result[2] = *(_DWORD *)(theHeader[2] + 12);
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
  int importConstructType; // edx
  int importItemName; // ebp
  _DWORD *k; // eax
  int exportConstructType; // ebp
  int exportItemName; // ebp

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
      importConstructType = j[1];
      if ( importConstructType )
        *(_DWORD *)(importConstructType + 12) |= 2u;
      importItemName = j[2];
      if ( importItemName )
        *(_DWORD *)(importItemName + 12) |= 2u;
    }
    for ( k = (_DWORD *)i[4]; k; k = (_DWORD *)k[3] )
    {
      ++g_ClipsBloadPortItemCount;
      if ( *k )
        *(_DWORD *)(*k + 12) |= 2u;
      exportConstructType = k[1];
      if ( exportConstructType )
        *(_DWORD *)(exportConstructType + 12) |= 2u;
      exportItemName = k[2];
      if ( exportItemName )
        *(_DWORD *)(exportItemName + 12) |= 2u;
    }
    result = (_DWORD *)Module_NextEnum((int)i);
  }
  return result;
}
// 51C6F8: using guessed type int dword_51C6F8;
// 51C6FC: using guessed type int dword_51C6FC;

//----- (004DAEC0) --------------------------------------------------------
const void * Module_BsaveWriteHeaderCounts(int fp, int a2)
{
  int v2; // ecx
  int v3; // ecx
  _DWORD spaceNeeded[4]; // [esp+0h] [ebp-10h] BYREF

  spaceNeeded[2] = a2;
  spaceNeeded[0] = 8;
  Rules_BsaveWriteBlock(4, fp, spaceNeeded);
  Rules_BsaveWriteBlock(4, v2, &g_ClipsBsaveModuleCount);
  return Rules_BsaveWriteBlock(4, v3, &g_ClipsBloadPortItemCount);
}
// 4DAEEA: variable 'v2' is possibly undefined
// 4DAEFB: variable 'v3' is possibly undefined
// 51C6F8: using guessed type int dword_51C6F8;
// 51C6FC: using guessed type int dword_51C6FC;

//----- (004DAF10) --------------------------------------------------------
int  Module_BsaveWriteModuleRecords(int filePtr)
{
  int v2; // ecx
  _DWORD *i; // ecx
  int nextModuleIndex; // ebp
  int v5; // eax
  int v6; // ecx
  int m; // edi
  _DWORD *n; // ecx
  int importTypeSymbol; // eax
  int importNameSymbol; // ebx
  int v11; // ecx
  _DWORD *ii; // ecx
  int exportTypeSymbol; // eax
  int exportNameSymbol; // ebx
  int v15; // ecx
  int result; // eax
  int j; // eax
  int k; // eax
  int nameIndex; // [esp+0h] [ebp-40h] BYREF
  int importListIndex; // [esp+4h] [ebp-3Ch]
  int exportListIndex; // [esp+8h] [ebp-38h]
  int nextIndex; // [esp+Ch] [ebp-34h]
  int bsaveId; // [esp+10h] [ebp-30h]
  int portModuleName; // [esp+14h] [ebp-2Ch] BYREF
  int portConstructType; // [esp+18h] [ebp-28h]
  int portConstructName; // [esp+1Ch] [ebp-24h]
  int portNextIndex; // [esp+20h] [ebp-20h]
  int space[7]; // [esp+24h] [ebp-1Ch] BYREF

  space[0] = 16 * g_ClipsBloadPortItemCount + 20 * g_ClipsBsaveModuleCount;
  Rules_BsaveWriteBlock(4, filePtr, space);
  g_ClipsBsaveModuleCount = v2;
  g_ClipsBloadPortItemCount = v2;
  for ( i = (_DWORD *)Module_NextEnum(0); i; i = (_DWORD *)Module_NextEnum(v6) )
  {
    nextModuleIndex = g_ClipsBsaveModuleCount + 1;
    v5 = *(_DWORD *)(*i + 12) << 16 >> 18;
    ++g_ClipsBsaveModuleCount;
    nameIndex = v5;
    if ( i[7] )
      nextIndex = nextModuleIndex;
    else
      nextIndex = -1;
    if ( i[3] )
    {
      importListIndex = g_ClipsBloadPortItemCount;
      for ( j = i[3]; j; j = *(_DWORD *)(j + 12) )
        ++g_ClipsBloadPortItemCount;
    }
    else
    {
      importListIndex = -1;
    }
    if ( i[4] )
    {
      exportListIndex = g_ClipsBloadPortItemCount;
      for ( k = i[4]; k; k = *(_DWORD *)(k + 12) )
        ++g_ClipsBloadPortItemCount;
    }
    else
    {
      exportListIndex = -1;
    }
    bsaveId = i[6];
    Rules_BsaveWriteBlock(20, filePtr, &nameIndex);
  }
  g_ClipsBloadPortItemCount = 0;
  for ( m = Module_NextEnum(0); m; m = Module_NextEnum(m) )
  {
    for ( n = *(_DWORD **)(m + 12); n; n = *(_DWORD **)(v11 + 12) )
    {
      ++g_ClipsBloadPortItemCount;
      if ( *n )
        portModuleName = *(_DWORD *)(*n + 12) << 16 >> 18;
      else
        portModuleName = -1;
      importTypeSymbol = n[1];
      if ( importTypeSymbol )
        portConstructType = *(_DWORD *)(importTypeSymbol + 12) << 16 >> 18;
      else
        portConstructType = -1;
      importNameSymbol = n[2];
      if ( importNameSymbol )
        portConstructName = *(_DWORD *)(importNameSymbol + 12) << 16 >> 18;
      else
        portConstructName = -1;
      if ( n[3] )
        portNextIndex = g_ClipsBloadPortItemCount;
      else
        portNextIndex = -1;
      Rules_BsaveWriteBlock(16, filePtr, &portModuleName);
    }
    for ( ii = *(_DWORD **)(m + 16); ii; ii = *(_DWORD **)(v15 + 12) )
    {
      ++g_ClipsBloadPortItemCount;
      if ( *ii )
        portModuleName = *(_DWORD *)(*ii + 12) << 16 >> 18;
      else
        portModuleName = -1;
      exportTypeSymbol = ii[1];
      if ( exportTypeSymbol )
        portConstructType = *(_DWORD *)(exportTypeSymbol + 12) << 16 >> 18;
      else
        portConstructType = -1;
      exportNameSymbol = ii[2];
      if ( exportNameSymbol )
        portConstructName = *(_DWORD *)(exportNameSymbol + 12) << 16 >> 18;
      else
        portConstructName = -1;
      if ( ii[3] )
        portNextIndex = g_ClipsBloadPortItemCount;
      else
        portNextIndex = -1;
      Rules_BsaveWriteBlock(16, filePtr, &portModuleName);
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
  _DWORD space[3]; // [esp+0h] [ebp-Ch] BYREF

  space[2] = a1;
  Rules_BloadReadBlock((uintptr_t)space, 4u);
  Rules_BloadReadBlock((uintptr_t)&g_ClipsBsaveModuleCount, 4u);
  result = Rules_BloadReadBlock((uintptr_t)&g_ClipsBloadPortItemCount, 4u);
  if ( g_ClipsBsaveModuleCount )
  {
    space[0] = 32 * g_ClipsBsaveModuleCount;
    result = Mem_HeapAllocWithRetry((_DWORD *)(32 * g_ClipsBsaveModuleCount));
    g_ClipsModuleArrayBase = result;
    if ( g_ClipsBloadPortItemCount )
    {
      space[0] = 16 * g_ClipsBloadPortItemCount;
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
  int space; // [esp-8h] [ebp-8h] BYREF

  result = Rules_BloadReadBlock((uintptr_t)&space, 4u);
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
int  Module_BloadFixupModuleRecord(_DWORD *bsaveModule, int moduleIndex)
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

  module_offset = 32 * moduleIndex;
  module = g_ClipsModuleArrayBase + module_offset;
  *(_DWORD *)module = *(_DWORD *)(4 * *bsaveModule + g_ClipsBloadSymbolPointerArray);
  ++*(_DWORD *)(*(_DWORD *)module + 4);
  parent_index = bsaveModule[3];
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
      value = ((int (*)(int))(uintptr_t)(unsigned int)*(_DWORD *)(constraint + 16))(moduleIndex);
    else
      value = 0;
    *(_DWORD *)(constraint_offset + *(_DWORD *)(module + 8)) = value;
    constraint_offset += 4;
    ++constraint_index;
    constraint = *(_DWORD *)(constraint + 28);
  }
  *(_DWORD *)(module + 4) = 0;
  import_index = bsaveModule[1];
  if ( import_index == -1 )
    *(_DWORD *)(module + 12) = 0;
  else
    *(_DWORD *)(module + 12) = 16 * import_index + g_Defmodule_PortItemArrayPtr;
  export_index = bsaveModule[2];
  if ( export_index == -1 )
    *(_DWORD *)(module + 16) = 0;
  else
    *(_DWORD *)(module + 16) = 16 * export_index + g_Defmodule_PortItemArrayPtr;
  result = bsaveModule[4];
  *(_DWORD *)(module + 24) = result;
  return result;
}
// 51C700: using guessed type int dword_51C700;
// 51C704: using guessed type int dword_51C704;
// 54E674: using guessed type int dword_54E674;

//----- (004DB470) --------------------------------------------------------
int  Module_BloadFixupPortItemRecord(_DWORD *bsavePortItem, int portItemIndex)
{
  int constructTypeIndex; // ebp
  int portOffset; // ecx
  int itemNameIndex; // esi
  int v5; // ecx
  int nextIndex; // ebp
  int v7; // edx
  int result; // eax

  if ( *bsavePortItem == -1 )
  {
    *(_DWORD *)(g_Defmodule_PortItemArrayPtr + 16 * portItemIndex) = 0;
  }
  else
  {
    *(_DWORD *)(g_Defmodule_PortItemArrayPtr + 16 * portItemIndex) = *(_DWORD *)(4 * *bsavePortItem + g_ClipsBloadSymbolPointerArray);
    ++*(_DWORD *)(*(_DWORD *)(g_Defmodule_PortItemArrayPtr + 16 * portItemIndex) + 4);
  }
  constructTypeIndex = bsavePortItem[1];
  portOffset = 16 * portItemIndex;
  if ( constructTypeIndex == -1 )
  {
    *(_DWORD *)(portOffset + g_Defmodule_PortItemArrayPtr + 4) = 0;
  }
  else
  {
    *(_DWORD *)(portOffset + g_Defmodule_PortItemArrayPtr + 4) = *(_DWORD *)(g_ClipsBloadSymbolPointerArray + 4 * constructTypeIndex);
    ++*(_DWORD *)(*(_DWORD *)(portOffset + g_Defmodule_PortItemArrayPtr + 4) + 4);
  }
  itemNameIndex = bsavePortItem[2];
  v5 = 16 * portItemIndex;
  if ( itemNameIndex == -1 )
  {
    *(_DWORD *)(v5 + g_Defmodule_PortItemArrayPtr + 8) = 0;
  }
  else
  {
    *(_DWORD *)(g_Defmodule_PortItemArrayPtr + v5 + 8) = *(_DWORD *)(g_ClipsBloadSymbolPointerArray + 4 * itemNameIndex);
    ++*(_DWORD *)(*(_DWORD *)(v5 + g_Defmodule_PortItemArrayPtr + 8) + 4);
  }
  nextIndex = bsavePortItem[3];
  v7 = 16 * portItemIndex;
  result = g_Defmodule_PortItemArrayPtr;
  if ( nextIndex == -1 )
    *(_DWORD *)(v7 + g_Defmodule_PortItemArrayPtr + 12) = 0;
  else
    *(_DWORD *)(v7 + g_Defmodule_PortItemArrayPtr + 12) = g_Defmodule_PortItemArrayPtr + 16 * nextIndex;
  return result;
}
// 51C700: using guessed type int dword_51C700;
// 54E674: using guessed type int dword_54E674;

//----- (004DB590) --------------------------------------------------------
int Module_ClearBloadData()
{
  int moduleIndex; // ebx
  int moduleOffset; // ecx
  int v2; // ecx
  int *i; // edx
  int importConstructType; // eax
  int *j; // edx
  int exportConstructType; // eax
  int itemCount; // eax
  int v8; // ecx
  int v9; // ecx
  int result; // eax

  moduleIndex = 0;
  if ( g_ClipsBsaveModuleCount > 0 )
  {
    moduleOffset = 0;
    do
    {
      Rules_DecrementSymbolCount(*(_DWORD *)(moduleOffset + g_ClipsModuleArrayBase), moduleOffset);
      for ( i = *(int **)(v2 + g_ClipsModuleArrayBase + 12); i; i = (int *)i[3] )
      {
        if ( *i )
          Rules_DecrementSymbolCount(*i, v2);
        importConstructType = i[1];
        if ( importConstructType )
          Rules_DecrementSymbolCount(importConstructType, v2);
        if ( i[2] )
          Rules_DecrementSymbolCount(i[2], v2);
      }
      for ( j = *(int **)(v2 + g_ClipsModuleArrayBase + 16); j; j = (int *)j[3] )
      {
        if ( *j )
          Rules_DecrementSymbolCount(*j, v2);
        exportConstructType = j[1];
        if ( exportConstructType )
          Rules_DecrementSymbolCount(exportConstructType, v2);
        if ( j[2] )
          Rules_DecrementSymbolCount(j[2], v2);
      }
      itemCount = Module_GetItemCount();
      ++moduleIndex;
      Mem_SmallBlockFree(*(_DWORD **)(v8 + g_ClipsModuleArrayBase + 8), 4 * itemCount);
      moduleOffset = v9 + 32;
    }
    while ( moduleIndex < g_ClipsBsaveModuleCount );
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
signed int  Rules_CheckConstraintParseConflicts(int constraints, __int16 *theExp)
{
  _WORD *maxValue; // edx
  int v5; // ecx

  if ( (*(_DWORD *)constraints & 1) == 1 )
    goto LABEL_2;
  if ( (*(_BYTE *)(constraints + 1) & 4) != 0 && (*(_BYTE *)constraints & 2) == 0 )
  {
    Rules_ReportAttributeConflict((int)theExp, (int)aAllowedSymbols);
    return 0;
  }
  if ( (*(_BYTE *)(constraints + 1) & 8) != 0 && (*(_BYTE *)constraints & 4) == 0 )
  {
    Rules_ReportAttributeConflict((int)theExp, (int)aAllowedStrings);
    return 0;
  }
  if ( (*(_BYTE *)(constraints + 1) & 0x20) != 0 && (*(_BYTE *)constraints & 0x10) == 0 )
  {
    Rules_ReportAttributeConflict((int)theExp, (int)aAllowedInteger);
    return 0;
  }
  if ( (*(_BYTE *)(constraints + 1) & 0x10) != 0 && (*(_BYTE *)constraints & 8) == 0 )
  {
    Rules_ReportAttributeConflict((int)theExp, (int)aAllowedFloatsN);
    return 0;
  }
  if ( (*(_BYTE *)(constraints + 1) & 0x40) != 0 && (*(_BYTE *)constraints & 0x20) == 0 )
  {
    Rules_ReportAttributeConflict((int)theExp, (int)aAllowedInstanc);
    return 0;
  }
  if ( (*(_BYTE *)(constraints + 1) & 2) != 0 && (theExp = *(__int16 **)(constraints + 6)) != 0 )
  {
    while ( !Rules_CheckValueAgainstConstraint(*theExp, *(_DWORD *)(theExp + 1), constraints) )
    {
      theExp = *(__int16 **)(v5 + 10);
      if ( !theExp )
        goto LABEL_2;
    }
    Rules_ReportAttributeConflict(v5, (int)aAllowedValues);
    return 0;
  }
  else
  {
LABEL_2:
    maxValue = *(_WORD **)(constraints + 14);
    if ( (!maxValue
       || (*(_BYTE *)constraints & 1) != 0
       || (*maxValue != 1 || (*(_BYTE *)constraints & 0x10) != 0) && (**(_WORD **)(constraints + 14) || (*(_BYTE *)constraints & 8) != 0))
      && (!*(_DWORD *)(constraints + 10)
       || (*(_BYTE *)constraints & 1) != 0
       || (**(_WORD **)(constraints + 10) != 1 || (*(_BYTE *)constraints & 0x10) != 0)
       && (**(_WORD **)(constraints + 10) || (*(_BYTE *)constraints & 8) != 0)) )
    {
      return 1;
    }
    else
    {
      Rules_ReportAttributeConflict((int)theExp, (int)aRange_0);
      return 0;
    }
  }
}
// 4DB7A1: variable 'v5' is possibly undefined

//----- (004DB850) --------------------------------------------------------
signed int __fastcall Rules_ReportAttributeConflict(int attribute1, int attribute2)
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
  Output_Write((int)g_IO_LogicalNameTable_WError[0], attribute2, v6);
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
BOOL  Rules_IsConstraintAttributeKeyword(int constraintName)
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

  return !strcmp_(constraintName, aType_0)
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
int  Rules_ParseStandardConstraintAttribute(char *readSource, const char *constraintName, _BYTE *parsedConstraints, int constraints, int multipleValuesAllowed)
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

  if ( Rules_TestConstraintAttributeParsedFlag((int)constraintName, parsedConstraints) )
  {
    Rules_ReportAlreadyParsed(0, (int)aAttribute);
    return 0;
  }
  else
  {
    if ( !strcmp_(0, aRange_0) || !strcmp_(v8, aCardinality) )
    {
      Rules_ParseRangeOrCardinalityAttribute((int)readSource, constraints, constraintName, parsedConstraints, readSource, multipleValuesAllowed);
    }
    else if ( !strcmp_(v10, aType_0) )
    {
      Rules_ParseTypeAttribute((int)readSource, v11);
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
      Rules_ParseAllowedValuesAttribute((int)readSource, constraintName, (int)parsedConstraints, constraints);
    }
    Rules_MarkConstraintAttributeParsed(parsedConstraints, (int)constraintName);
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
int  Rules_OverlayConstraint(int result, int cdst, int *csrc)
{
  char *pc; // edi
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

  pc = (char *)result;
  v4 = cdst;
  if ( (*(_BYTE *)result & 1) == 0 )
  {
    v17 = *csrc;
    *(_BYTE *)cdst &= ~1u;
    *(_DWORD *)cdst |= v17 & 1;
    v18 = *csrc;
    *(_BYTE *)cdst &= ~2u;
    *(_DWORD *)cdst |= v18 & 2;
    v19 = *csrc;
    *(_BYTE *)cdst &= ~4u;
    *(_DWORD *)cdst |= v19 & 4;
    v20 = *csrc;
    *(_BYTE *)cdst &= ~8u;
    *(_DWORD *)cdst |= v20 & 8;
    v21 = *csrc;
    *(_BYTE *)cdst &= ~0x10u;
    *(_DWORD *)cdst |= v21 & 0x10;
    v22 = *csrc;
    *(_BYTE *)cdst &= ~0x20u;
    *(_DWORD *)cdst |= v22 & 0x20;
    v23 = *csrc;
    *(_BYTE *)cdst &= ~0x40u;
    *(_DWORD *)cdst |= v23 & 0x40;
    v24 = *csrc;
    *(_BYTE *)cdst &= ~0x80u;
    *(_DWORD *)cdst |= v24 & 0x80;
    v25 = *csrc;
    *(_BYTE *)(cdst + 1) &= ~1u;
    result = v25 & 0x100;
    *(_DWORD *)cdst |= result;
  }
  if ( (*pc & 2) == 0 )
  {
    AST_Free(*(_DWORD *)(cdst + 10));
    AST_Free(*(_DWORD *)(v6 + 14));
    v7 = AST_CloneNodeList(*(int *)((char *)csrc + 10));
    *(_DWORD *)(v8 + 10) = v7;
    result = AST_CloneNodeList(*(int *)((char *)csrc + 14));
    *(_DWORD *)(v4 + 14) = result;
  }
  v9 = pc[1];
  if ( (v9 & 1) == 0 )
  {
    v10 = *pc;
    if ( (*pc & 4) != 0
      || (v10 & 8) != 0
      || (v10 & 0x10) != 0
      || (v10 & 0x40) != 0
      || (v10 & 0x20) != 0
      || v10 < 0
      || (v9 & 2) != 0 )
    {
      if ( (*pc & 4) == 0 && (*((_BYTE *)csrc + 1) & 4) != 0 )
      {
        *(_BYTE *)(v4 + 1) |= 4u;
        result = Rules_MergeConstraintValueList(2, v4, (int)csrc);
      }
      if ( (*pc & 8) == 0 && (*((_BYTE *)csrc + 1) & 8) != 0 )
      {
        *(_BYTE *)(v4 + 1) |= 8u;
        result = Rules_MergeConstraintValueList(3, v4, (int)csrc);
      }
      if ( (*pc & 0x10) == 0 )
      {
        BYTE1(result) = *((_BYTE *)csrc + 1);
        if ( (result & 0x400) != 0 && (result & 0x800) != 0 )
        {
          *(_BYTE *)(v4 + 1) |= 0xCu;
          Rules_MergeConstraintValueList(2, v4, (int)csrc);
          result = Rules_MergeConstraintValueList(3, v26, (int)csrc);
        }
      }
      if ( (*pc & 0x40) == 0 && (*((_BYTE *)csrc + 1) & 0x20) != 0 )
      {
        *(_BYTE *)(v4 + 1) |= 0x20u;
        result = Rules_MergeConstraintValueList(1, v4, (int)csrc);
      }
      if ( (*pc & 0x20) == 0 && (*((_BYTE *)csrc + 1) & 0x10) != 0 )
      {
        *(_BYTE *)(v4 + 1) |= 0x10u;
        result = Rules_MergeConstraintValueList(0, v4, (int)csrc);
      }
      if ( *pc >= 0 )
      {
        v27 = *((_BYTE *)csrc + 1);
        if ( (v27 & 0x20) != 0 && (v27 & 0x10) != 0 )
        {
          *(_BYTE *)(v4 + 1) |= 0x30u;
          Rules_MergeConstraintValueList(1, v4, (int)csrc);
          result = Rules_MergeConstraintValueList(0, v28, (int)csrc);
        }
      }
      if ( (pc[1] & 2) == 0 && (*((_BYTE *)csrc + 1) & 0x40) != 0 )
      {
        *(_BYTE *)(v4 + 1) |= 0x40u;
        result = Rules_MergeConstraintValueList(8, v4, (int)csrc);
        if ( (pc[1] & 4) != 0 )
          return result;
        goto LABEL_39;
      }
    }
    else
    {
      v11 = *csrc;
      *(_BYTE *)(v4 + 1) &= ~2u;
      *(_DWORD *)v4 |= v11 & 0x200;
      v12 = *csrc;
      *(_BYTE *)(v4 + 1) &= ~4u;
      *(_DWORD *)v4 |= v12 & 0x400;
      v13 = *csrc;
      *(_BYTE *)(v4 + 1) &= ~8u;
      *(_DWORD *)v4 |= v13 & 0x800;
      v14 = *csrc;
      *(_BYTE *)(v4 + 1) &= ~0x10u;
      *(_DWORD *)v4 |= v14 & 0x1000;
      v15 = *csrc;
      *(_BYTE *)(v4 + 1) &= ~0x20u;
      *(_DWORD *)v4 |= v15 & 0x2000;
      v16 = *csrc;
      *(_BYTE *)(v4 + 1) &= ~0x40u;
      *(_DWORD *)v4 |= v16 & 0x4000;
      result = AST_CloneNodeList(*(int *)((char *)csrc + 6));
      *(_DWORD *)(v4 + 6) = result;
    }
  }
  if ( (pc[1] & 4) == 0 )
  {
LABEL_39:
    AST_Free(*(_DWORD *)(v4 + 18));
    AST_Free(*(_DWORD *)(v29 + 22));
    v30 = AST_CloneNodeList(*(int *)((char *)csrc + 18));
    *(_DWORD *)(v31 + 18) = v30;
    result = AST_CloneNodeList(*(int *)((char *)csrc + 22));
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
signed int  Rules_MergeConstraintValueList(signed int result, int cdst, int csrc)
{
  signed int theType; // edi
  __int16 *i; // ecx
  int v6; // ecx

  theType = result;
  for ( i = *(__int16 **)(csrc + 6); i; i = *(__int16 **)(v6 + 10) )
  {
    while ( 1 )
    {
      result = *i;
      if ( result == theType )
        break;
      i = *(__int16 **)(i + 5);
      if ( !i )
        return result;
    }
    result = AST_NewNode(result, *(_DWORD *)(i + 1));
    *(_DWORD *)(result + 10) = *(_DWORD *)(cdst + 6);
    *(_DWORD *)(cdst + 6) = result;
  }
  return result;
}
// 4DBE71: variable 'v6' is possibly undefined

//----- (004DBE80) --------------------------------------------------------
signed int  Rules_ParseAllowedValuesAttribute(int readSource, const char *constraintName, int parsedConstraints, int constraints)
{
  char *v5; // ecx
  int error; // edi
  int constantParsed; // esi
  char v8; // ah
  char v9; // al
  _BYTE *v11; // ecx
  int v12; // ecx
  _BYTE *v13; // ecx
  char *v14; // edx
  char *v15; // ecx
  _BYTE *v16; // ecx
  unsigned int restrictionType; // eax
  signed int lastValue; // ebx
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
  _DWORD theToken[2]; // [esp+1E0h] [ebp-2Ch] BYREF
  char *tempPtr; // [esp+1ECh] [ebp-20h]
  const char *v34; // [esp+1F0h] [ebp-1Ch]
  int v35; // [esp+1F4h] [ebp-18h]
  signed int newValue; // [esp+1F8h] [ebp-14h]
  int variableParsed; // [esp+1FCh] [ebp-10h]

  v34 = constraintName;
  v35 = constraints;
  error = 0;
  constantParsed = 0;
  variableParsed = 0;
  if ( !strcmp_(parsedConstraints, aAllowedValues) )
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
        tempPtr = aAllowedSymbols;
      }
      else if ( (v9 & 8) != 0 )
      {
        tempPtr = aAllowedStrings;
      }
      else if ( (v9 & 0x10) != 0 )
      {
        tempPtr = aAllowedLexemes;
      }
      else if ( (v9 & 0x40) != 0 )
      {
        tempPtr = aAllowedInteg_0;
      }
      else if ( (v9 & 0x20) != 0 )
      {
        tempPtr = aAllowedFloats;
      }
      else if ( v9 >= 0 )
      {
        if ( (v5[1] & 2) != 0 )
          tempPtr = aAllowedInstanc;
      }
      else
      {
        tempPtr = aAllowedNumbers;
      }
      Rules_ReportAttributeCannotCombine((int)v5, (int)tempPtr);
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
  restrictionType = Rules_GetAllowedAttributeTokenCode((int)v34);
  Rules_SetConstraintAllowedTypeFlag(restrictionType, v35, 1);
  lastValue = *(_DWORD *)(v35 + 6);
  if ( lastValue )
  {
    while ( *(_DWORD *)(lastValue + 10) )
      lastValue = *(_DWORD *)(lastValue + 10);
  }
  IO_OutWriteToken(asc_50DB38);
  Parser_NextToken(readSource, v19);
  if ( theToken[0] != 101 )
  {
    while ( 1 )
    {
      IO_OutWriteToken(asc_50DB38);
      if ( theToken[0] < 2u )
        break;
      if ( theToken[0] <= 2u )
      {
        if ( v21 == 103 || v21 == 2 )
          goto LABEL_69;
        v23 = v21 == 111;
        goto LABEL_67;
      }
      if ( theToken[0] < 8u )
      {
        if ( theToken[0] != 3 )
          goto LABEL_101;
        if ( v21 == 103 || v21 == theToken[0] )
          goto LABEL_69;
        v23 = v21 == 111;
        goto LABEL_67;
      }
      if ( theToken[0] <= 8u )
      {
        if ( v21 != 103 )
        {
          v23 = v21 == 8;
          goto LABEL_67;
        }
LABEL_69:
        constantParsed = 1;
        goto LABEL_70;
      }
      if ( theToken[0] != 15 )
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
      variableParsed = 1;
LABEL_70:
      if ( error )
      {
        Rules_PrintErrorID((int)aCstrnpsr, 4, 1);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aValueDoesNotMa, v25);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)v34, v26);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAttribute_0, v27);
        return 0;
      }
      if ( constantParsed && variableParsed )
      {
        sprintf_(v28, "%s attribute", v34);
        Parser_ReportSyntaxError();
        return 0;
      }
      v24 = AST_NewNode(theToken[0], theToken[1]);
      newValue = v24;
      if ( lastValue )
        *(_DWORD *)(lastValue + 10) = v24;
      else
        *(_DWORD *)(v35 + 6) = v24;
      Parser_NextToken(readSource, (int)theToken);
      lastValue = newValue;
      if ( theToken[0] == 101 )
        goto LABEL_76;
    }
    if ( theToken[0] )
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
      error = 1;
    goto LABEL_69;
  }
LABEL_76:
  if ( constantParsed || variableParsed )
  {
    if ( variableParsed )
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
signed int __fastcall Rules_ReportAttributeCannotCombine(int attribute1, int attribute2)
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
  Output_Write((int)g_IO_LogicalNameTable_WError[0], attribute2, v7);
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
signed int  Rules_ParseTypeAttribute(int readSource, int constraints)
{
  int typeParsed; // edi
  int v4; // edx
  int variableParsed; // ebx
  int v6; // ecx
  signed int theType; // eax
  int v8; // ecx
  _BYTE *v9; // ecx
  _DWORD theToken[7]; // [esp+0h] [ebp-1Ch] BYREF

  theToken[5] = constraints;
  IO_OutWriteToken(asc_50DB38);
  typeParsed = 0;
  Parser_NextToken(readSource, v4);
  variableParsed = 0;
  while ( theToken[0] != 101 )
  {
    IO_OutWriteToken(asc_50DB38);
    if ( theToken[0] == 2 )
    {
      if ( variableParsed == 1 )
        goto LABEL_11;
      theType = Rules_GetTypeNameTokenCode(*(_DWORD *)(theToken[1] + 16));
      if ( theType < 0 || Rules_UpdateCETypeFlag(theType, v8) )
        goto LABEL_11;
      typeParsed = 1;
      *v9 &= ~1u;
    }
    else
    {
      if ( theToken[0] != 15 || strcmp_(v6, a_variable) || typeParsed || variableParsed )
        goto LABEL_11;
      variableParsed = 1;
    }
    Parser_NextToken(readSource, (int)theToken);
  }
  IO_OutNewline();
  IO_OutNewline();
  IO_OutWriteToken(asc_50DB94);
  if ( typeParsed || variableParsed )
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
        int readSource,
        int constraints,
        const char *constraintName,
        _BYTE *parsedConstraints,
        char *conflictName,
        int multipleValuesAllowed)
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
  _BYTE minMsgBuffer[120]; // [esp+0h] [ebp-10Ch] BYREF
  _BYTE maxMsgBuffer[120]; // [esp+78h] [ebp-94h] BYREF
  int tokenType; // [esp+F0h] [ebp-1Ch] BYREF
  int tokenValue; // [esp+F4h] [ebp-18h]
  const char *v26; // [esp+FCh] [ebp-10h]

  v26 = constraintName;
  if ( !strcmp_(constraintName, aRange_0) )
  {
    v8 = 1;
    *parsedConstraints |= 2u;
    if ( (parsedConstraints[1] & 1) != 0 || (v17 = *parsedConstraints, (char)*parsedConstraints < 0) || (v17 & 0x40) != 0 || (v17 & 0x20) != 0 )
    {
      if ( (parsedConstraints[1] & 1) != 0 )
      {
        conflictName = aAllowedValues;
      }
      else
      {
        LOBYTE(v8) = *parsedConstraints;
        if ( (*parsedConstraints & 0x40) != 0 )
        {
          conflictName = aAllowedInteg_0;
        }
        else if ( (v8 & 0x20) != 0 )
        {
          conflictName = aAllowedFloats;
        }
        else if ( (v8 & 0x80u) != 0 )
        {
          conflictName = aAllowedNumbers;
        }
      }
      Rules_ReportAttributeCannotCombine(v8, (int)conflictName);
      return 0;
    }
  }
  else
  {
    parsedConstraints[1] |= 4u;
    if ( !multipleValuesAllowed )
    {
      Rules_PrintErrorID((int)aCstrnpsr, 5, 1);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aTheCardinality, v15);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCanOnlyBeUsedW, v16);
      return 0;
    }
  }
  IO_OutWriteToken(asc_50DB38);
  Parser_NextToken(readSource, v10);
  if ( tokenType == 1 || !tokenType && v11 )
  {
    if ( v11 )
    {
      AST_Free(*(_DWORD *)(constraints + 10));
      *(_DWORD *)(constraints + 10) = AST_NewNode(tokenType, tokenValue);
    }
    else
    {
      AST_Free(*(_DWORD *)(constraints + 18));
      *(_DWORD *)(constraints + 18) = AST_NewNode(tokenType, tokenValue);
    }
  }
  else if ( tokenType != 15 || strcmp_(v11, a_variable) )
  {
    sprintf_(minMsgBuffer, "%s attribute", v26);
    Parser_ReportSyntaxError();
    return 0;
  }
  IO_OutWriteToken(asc_50DB38);
  Parser_NextToken(readSource, v12);
  if ( tokenType == 1 || !tokenType && v13 )
  {
    if ( v13 )
    {
      AST_Free(*(_DWORD *)(constraints + 14));
      *(_DWORD *)(constraints + 14) = AST_NewNode(tokenType, tokenValue);
    }
    else
    {
      AST_Free(*(_DWORD *)(constraints + 22));
      *(_DWORD *)(constraints + 22) = AST_NewNode(tokenType, tokenValue);
    }
  }
  else if ( tokenType != 15 || strcmp_(v13, a_variable) )
  {
    sprintf_(maxMsgBuffer, "%s attribute", v26);
    Parser_ReportSyntaxError();
    return 0;
  }
  Parser_NextToken(readSource, (int)&tokenType);
  if ( tokenType == 101 )
  {
    if ( v14 )
    {
      if ( Rules_CompareBoundedCEValues(
             **(__int16 **)(constraints + 10),
             *(_DWORD *)(*(_DWORD *)(constraints + 10) + 2),
             *(_DWORD *)(*(_DWORD *)(constraints + 14) + 2),
             **(__int16 **)(constraints + 14)) != 1 )
        return 1;
      Rules_PrintErrorID((int)aCstrnpsr, 2, 1);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aMinimumRangeVa, v18);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOrEqualToTheMa, v19);
      return 0;
    }
    else
    {
      if ( Rules_CompareBoundedCEValues(
             **(__int16 **)(constraints + 18),
             *(_DWORD *)(*(_DWORD *)(constraints + 18) + 2),
             *(_DWORD *)(*(_DWORD *)(constraints + 22) + 2),
             **(__int16 **)(constraints + 22)) != 1 )
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
int  Rules_GetAllowedAttributeTokenCode(int constraintName)
{
  int v1; // ecx
  int result; // eax
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx

  if ( !strcmp_(constraintName, aAllowedValues) )
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
int  Rules_GetTypeNameTokenCode(int typeName)
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

  if ( !strcmp_(typeName, aSymbol_7) )
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
int  Rules_TestConstraintAttributeParsedFlag(int constraintName, _DWORD *parsedConstraints)
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

  if ( !strcmp_(constraintName, aType_0) )
    return *parsedConstraints & 1;
  if ( !strcmp_(v3, aRange_0) )
    return *parsedConstraints << 30 >> 31;
  if ( !strcmp_(v5, aCardinality) )
    return *parsedConstraints << 21 >> 31;
  if ( !strcmp_(v6, aAllowedValues) )
    return *parsedConstraints << 23 >> 31;
  if ( !strcmp_(v7, aAllowedSymbols) )
    return *parsedConstraints << 29 >> 31;
  if ( !strcmp_(v8, aAllowedStrings) )
    return *parsedConstraints << 28 >> 31;
  if ( !strcmp_(v9, aAllowedLexemes) )
    return *parsedConstraints << 27 >> 31;
  if ( !strcmp_(v10, aAllowedInstanc) )
    return *parsedConstraints << 22 >> 31;
  if ( !strcmp_(v11, aAllowedInteg_0) )
    return *parsedConstraints << 25 >> 31;
  if ( !strcmp_(v12, aAllowedFloats) )
    return *parsedConstraints << 26 >> 31;
  if ( !strcmp_(v13, aAllowedNumbers) )
    return *parsedConstraints << 24 >> 31;
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
unsigned int  Rules_SetConstraintAllowedTypeFlag(unsigned int result, int constraints, char value)
{
  int flagBit; // ecx
  int v4; // ebp
  int v5; // esi
  int v6; // ebx

  flagBit = value & 1;
  v4 = flagBit << 12;
  v5 = flagBit << 13;
  v6 = flagBit << 10;
  if ( result < 3 )
  {
    if ( result )
    {
      if ( result > 1 )
      {
        *(_BYTE *)(constraints + 1) &= ~4u;
        *(_DWORD *)constraints |= v6;
      }
      else
      {
        *(_BYTE *)(constraints + 1) &= ~0x20u;
        *(_DWORD *)constraints |= v5;
      }
    }
    else
    {
      *(_BYTE *)(constraints + 1) &= ~0x10u;
      *(_DWORD *)constraints |= v4;
    }
    return result;
  }
  if ( result <= 3 )
  {
LABEL_14:
    *(_BYTE *)(constraints + 1) &= ~8u;
    *(_DWORD *)constraints |= flagBit << 11;
    return result;
  }
  if ( result < 0x67 )
  {
    if ( result == 8 )
    {
      *(_BYTE *)(constraints + 1) &= ~0x40u;
      *(_DWORD *)constraints |= flagBit << 14;
    }
    return result;
  }
  if ( result <= 0x67 )
  {
    *(_BYTE *)(constraints + 1) &= ~2u;
    *(_DWORD *)constraints |= flagBit << 9;
    return result;
  }
  if ( result >= 0x6E )
  {
    if ( result <= 0x6E )
    {
      *(_BYTE *)(constraints + 1) &= ~0x20u;
      *(_DWORD *)constraints |= v5;
      *(_BYTE *)(constraints + 1) &= ~0x10u;
      *(_DWORD *)constraints |= v4;
      return result;
    }
    if ( result == 111 )
    {
      *(_BYTE *)(constraints + 1) &= ~4u;
      *(_DWORD *)constraints |= v6;
      goto LABEL_14;
    }
  }
  return result;
}

//----- (004DCE50) --------------------------------------------------------
int  Rules_MarkConstraintAttributeParsed(_BYTE *parsedConstraints, int constraintName)
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

  result = strcmp_(constraintName, aRange_0);
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
                      parsedConstraints[1] |= 1u;
                  }
                  else
                  {
                    *parsedConstraints |= 0x80u;
                  }
                }
                else
                {
                  *parsedConstraints |= 0x20u;
                }
              }
              else
              {
                *parsedConstraints |= 0x40u;
              }
            }
            else
            {
              *parsedConstraints |= 0x10u;
            }
          }
          else
          {
            *parsedConstraints |= 8u;
          }
        }
        else
        {
          *parsedConstraints |= 4u;
        }
      }
      else
      {
        parsedConstraints[1] |= 4u;
      }
    }
    else
    {
      *parsedConstraints |= 1u;
    }
  }
  else
  {
    *parsedConstraints |= 2u;
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
signed int  Rules_CEDetectDuplicatePatternBinding(_DWORD *patternPtr)
{
  _DWORD *thePattern; // edi
  int referringNode; // ebp
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  char *errorMsg; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int *theList; // ebp
  int *tempList; // esi
  int v16; // ecx
  int errorFlag; // [esp+4h] [ebp-1Ch]

  thePattern = patternPtr;
  errorFlag = 0;
  if ( !patternPtr )
    return errorFlag;
  while ( *thePattern == 80 )
  {
    if ( thePattern[1] )
    {
      referringNode = thePattern[5];
      if ( referringNode )
      {
        errorFlag = 1;
        if ( *(_DWORD *)(referringNode + 32) == -1 )
        {
          Rules_PrintErrorID((int)aAnalysis, 1, 1);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDuplicatePatte, v3);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(thePattern[1] + 16), v4);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFoundInCe_0, v5);
          Rules_PrintLongInteger(v6, thePattern[2] << 19 >> 25);
          errorMsg = a__26;
        }
        else
        {
          Rules_PrintErrorID((int)aAnalysis, 2, 1);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aPatternAddress, v10);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(thePattern[1] + 16), v11);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUsedInCe, v12);
          Rules_PrintLongInteger(v13, thePattern[2] << 19 >> 25);
          errorMsg = aWasPreviouslyB;
        }
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)errorMsg, v7);
      }
    }
    if ( Rules_CEPropagateVariableBindingCheck((int)thePattern) )
      return 1;
LABEL_9:
    thePattern = (_DWORD *)thePattern[17];
    if ( !thePattern )
      return errorFlag;
  }
  if ( *thePattern != 84 )
    goto LABEL_9;
  Rules_CEFindUnboundVariableReference(thePattern[14], 0, 0, thePattern[2] << 19 >> 25, 0);
  theList = Rules_ClonePatternPositionConstraintList((int *)thePattern[14]);
  tempList = theList;
  if ( !theList )
  {
LABEL_17:
    AST_FreeNode((int)theList);
    if ( v16 )
      errorFlag = 1;
    else
      thePattern[13] = AST_CloneFieldAccessSubtreePN(thePattern[14]);
    goto LABEL_9;
  }
  while ( !Rules_CEScanBranchesForVariableMatch((int)thePattern, (int)thePattern, 15, 0, tempList[1], tempList, 0) )
  {
    tempList = (int *)tempList[16];
    if ( !tempList )
      goto LABEL_17;
  }
  AST_FreeNode((int)theList);
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
signed int  Rules_CEPropagateVariableBindingCheck(int thePattern)
{
  int theField; // ecx
  int *multifieldHeader; // esi
  int nodeType; // edx
  int *v6; // ecx

  theField = thePattern;
  multifieldHeader = 0;
  if ( !thePattern )
    return 0;
  do
  {
    while ( 1 )
    {
      if ( (*(_BYTE *)(theField + 8) & 4) != 0 )
      {
        multifieldHeader = (int *)theField;
        theField = *(_DWORD *)(theField + 68);
      }
      if ( theField )
      {
        nodeType = *(_DWORD *)theField;
        if ( *(_DWORD *)theField == 15 || nodeType == 16 || nodeType == 80 && *(_DWORD *)(theField + 4) )
        {
          if ( Rules_CEBindPatternAddressVariable(theField, multifieldHeader, thePattern) )
            return 1;
        }
        else if ( Rules_CEValidateFieldConstraintUsage((_DWORD *)theField, multifieldHeader, thePattern) )
        {
          return 1;
        }
      }
      if ( theField )
        break;
      theField = (int)multifieldHeader;
LABEL_10:
      theField = *(_DWORD *)(theField + 64);
      if ( !theField )
        return 0;
    }
    if ( *(_DWORD *)(theField + 64) || !multifieldHeader )
      goto LABEL_10;
    v6 = multifieldHeader;
    multifieldHeader = 0;
    theField = v6[16];
  }
  while ( theField );
  return 0;
}
// 4DD14B: variable 'v1' is possibly undefined

//----- (004DD1A0) --------------------------------------------------------
signed int  Rules_CEBindPatternAddressVariable(int thePattern, int *multifieldHeader, int patternHead)
{
  _BYTE *theConstraints; // eax
  int theType; // [esp+0h] [ebp-18h]
  int theValue; // [esp+4h] [ebp-14h]

  if ( *(_DWORD *)thePattern == 80 )
  {
    theValue = *(_DWORD *)(thePattern + 4);
    theType = 15;
    if ( (*(_BYTE *)(thePattern + 8) & 0x10) != 0 )
      AST_DecrementNodeRefCount(*(_DWORD **)(thePattern + 16));
    theConstraints = (_BYTE *)Rules_CreateLHSParseNode();
    *(_DWORD *)(thePattern + 16) = theConstraints;
    *theConstraints &= ~1u;
    **(_BYTE **)(thePattern + 16) |= 0x40u;
    *(_BYTE *)(*(_DWORD *)(thePattern + 16) + 1) |= 1u;
    *(_BYTE *)(thePattern + 8) |= 0x10u;
  }
  else
  {
    theType = *(_DWORD *)thePattern;
    theValue = *(_DWORD *)(thePattern + 4);
  }
  if ( *(_DWORD *)thePattern == 80 )
    return Rules_CEScanBranchesForVariableMatch(patternHead, thePattern, theType, (int)multifieldHeader, theValue, (int *)thePattern, 1);
  Rules_CEFindBoundVariableOccurrence(*(_DWORD *)(thePattern + 68), theType, (int *)thePattern, theValue, *(_DWORD *)(patternHead + 44), 1, 0);
  if ( !Rules_CEValidateFieldConstraintUsage((_DWORD *)thePattern, multifieldHeader, patternHead) )
    return Rules_CEScanBranchesForVariableMatch(patternHead, thePattern, theType, (int)multifieldHeader, theValue, (int *)thePattern, 1);
  else
    return 1;
}

//----- (004DD260) --------------------------------------------------------
signed int  Rules_CEScanBranchesForVariableMatch(
        int patternHead,
        int theNode,
        int theType,
        int multifieldNodesList,
        int theVariable,
        int *theReference,
        signed int assignReference)
{
  if ( multifieldNodesList && Rules_CEFindBoundVariableOccurrence(*(_DWORD *)(multifieldNodesList + 64), theType, theReference, theVariable, *(_DWORD *)(patternHead + 44), assignReference, 0)
    || Rules_CEFindBoundVariableOccurrence(*(_DWORD *)(theNode + 64), theType, theReference, theVariable, *(_DWORD *)(patternHead + 44), assignReference, 0) )
  {
LABEL_9:
    Rules_ReportVariableFieldTypeConflict();
    return 1;
  }
  if ( *(_DWORD *)patternHead == 80 || *(_DWORD *)patternHead == 84 )
  {
    if ( (*(_BYTE *)(patternHead + 8) & 1) != 0
      || *(_DWORD *)(patternHead + 44) > *(_DWORD *)(patternHead + 48)
      || !Rules_CEFindBoundVariableOccurrence(*(_DWORD *)(patternHead + 68), theType, theReference, theVariable, *(_DWORD *)(patternHead + 44), assignReference, *(_DWORD *)patternHead == 84) )
    {
      return 0;
    }
    goto LABEL_9;
  }
  return 0;
}

//----- (004DD330) --------------------------------------------------------
signed int  Rules_CEValidateFieldConstraintUsage(_DWORD *thePattern, int *multifieldHeader, int patternHead)
{
  int *tempList; // esi
  int v6; // ecx
  signed int theList; // [esp+0h] [ebp-18h]

  if ( *thePattern == 80 )
    return 0;
  theList = Rules_IntersectConnectedCEConstraints((int)thePattern);
  tempList = (int *)theList;
  if ( theList )
  {
    while ( !Rules_CEScanBranchesForVariableMatch(patternHead, (int)thePattern, *tempList, (int)multifieldHeader, tempList[1], tempList, 0) )
    {
      tempList = (int *)tempList[16];
      if ( !tempList )
        goto LABEL_6;
    }
    AST_FreeNode(theList);
    return 1;
  }
  else
  {
LABEL_6:
    AST_FreeNode(theList);
    if ( Rules_CEValidateLiteralAgainstConstraints((int)thePattern, *(_DWORD *)(patternHead + 8) << 19 >> 25, v6) )
    {
      return 1;
    }
    else if ( Rules_ComputeConnectedCEConstraintGroup((int)thePattern, multifieldHeader, patternHead) )
    {
      return 1;
    }
    else
    {
      AST_BuildClassHierarchyFieldAccessTest(thePattern, patternHead);
      return 0;
    }
  }
}
// 4DD390: variable 'v6' is possibly undefined

//----- (004DD3F0) --------------------------------------------------------
signed int  Rules_CEFindBoundVariableOccurrence(
        int fieldList,
        int theType,
        int *theReference,
        int theVariable,
        int nandDepth,
        signed int assignReference,
        int allowMixing)
{
  int theField; // esi
  int testExpression; // edx
  _BYTE *newConstraints; // eax
  _DWORD *v12; // ecx
  char nodeFlags; // dl
  int rightField; // eax
  signed int result; // eax

  theField = fieldList;
  if ( fieldList )
  {
    while ( 1 )
    {
      testExpression = *(_DWORD *)(theField + 56);
      if ( testExpression )
      {
        Rules_CEFindBoundVariableOccurrence(testExpression, theType, (int)theReference, theVariable, nandDepth, assignReference, 1);
      }
      else
      {
        if ( (*(_DWORD *)theField == 15 || *(_DWORD *)theField == 16) && theVariable == *(_DWORD *)(theField + 4) )
        {
          if ( !allowMixing && (theType == 15 && *(_DWORD *)theField == 16 || theType == 16 && *(_DWORD *)theField == 15) )
            return 1;
          if ( theReference[4] && (*(_BYTE *)(theField + 8) & 1) == 0 )
          {
            newConstraints = Rules_IntersectConstraints(theReference[4], *(_DWORD *)(theField + 16));
            nodeFlags = *(_BYTE *)(theField + 8);
            *(_DWORD *)(theField + 16) = newConstraints;
            if ( (nodeFlags & 0x10) != 0 )
              AST_DecrementNodeRefCount(v12);
            *(_BYTE *)(theField + 8) |= 0x10u;
          }
          if ( !assignReference || *(_DWORD *)(theField + 20) && theReference[7] != *(_DWORD *)(theField + 28) && theReference[6] != *(_DWORD *)(theField + 24) )
            goto LABEL_18;
        }
        else
        {
          if ( *(_DWORD *)theField != 80 )
            goto LABEL_18;
          if ( theVariable != *(_DWORD *)(theField + 4) )
            goto LABEL_18;
          result = assignReference;
          if ( assignReference != 1 )
            goto LABEL_18;
          if ( theType == 16 )
            return result;
        }
        *(_DWORD *)(theField + 20) = theReference;
      }
LABEL_18:
      rightField = *(_DWORD *)(theField + 64);
      if ( rightField && Rules_CEFindBoundVariableOccurrence(rightField, theType, (int)theReference, theVariable, nandDepth, assignReference, allowMixing) )
        return 1;
      if ( (*(_DWORD *)theField == 80 || *(_DWORD *)theField == 84) && nandDepth > *(_DWORD *)(theField + 48) )
        return 0;
      theField = *(_DWORD *)(theField + 68);
      if ( !theField )
        return 0;
    }
  }
  return 0;
}
// 4DD3F0: could not find valid save-restore pair for ebx
// 4DD472: variable 'v12' is possibly undefined

//----- (004DD580) --------------------------------------------------------
signed int  Rules_CEValidateLiteralAgainstConstraints(int theNode, int whichCE, int a3)
{
  int theField; // esi
  int slotName; // ebp
  unsigned int *andField; // esi
  unsigned int fieldType; // ebx
  signed int violationCode; // eax
  unsigned int *orField; // [esp+0h] [ebp-20h]
  int theConstraints; // [esp+4h] [ebp-1Ch]
  int fieldPosition; // [esp+8h] [ebp-18h]

  if ( (*(_BYTE *)(theNode + 8) & 4) != 0 )
  {
    theField = *(_DWORD *)(theNode + 68);
    if ( theField )
    {
      while ( !Rules_CEValidateLiteralAgainstConstraints(theField, whichCE, a3) )
      {
        theField = *(_DWORD *)(theField + 64);
        if ( !theField )
          return 0;
      }
      return 1;
    }
    return 0;
  }
  fieldPosition = *(_DWORD *)(theNode + 32);
  theConstraints = *(_DWORD *)(theNode + 16);
  slotName = *(_DWORD *)(theNode + 36);
  orField = *(unsigned int **)(theNode + 68);
  if ( !orField )
    return 0;
  while ( 2 )
  {
    andField = orField;
    do
    {
      if ( (*andField == 15 || *andField == 16) && !andField[5] )
      {
        Rules_ReportUnboundVariableUsage(andField[1], 0, slotName, whichCE, fieldPosition);
        return 1;
      }
      fieldType = *andField;
      if ( *andField == 93 || fieldType == 94 )
      {
        if ( Rules_CEFindUnboundVariableReference(andField[14], 0, slotName, whichCE, fieldPosition) )
          return 1;
      }
      else if ( fieldType < 4 || fieldType == 8 )
      {
        if ( Rules_StaticConstraintCheckingEnabled() )
        {
          violationCode = Rules_CheckValueAgainstConstraint(*andField, andField[1], theConstraints);
          if ( violationCode )
          {
            Rules_PrintConstraintViolationMessage((int)aALiteralRestri, 0, whichCE, 0, slotName, fieldPosition, violationCode, theConstraints, 1);
            return 1;
          }
        }
      }
      andField = (unsigned int *)andField[16];
    }
    while ( andField );
    orField = (unsigned int *)orField[17];
    if ( orField )
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
int  Rules_CEFindUnboundVariableReference(int exprPtr, int theExpression, int slotName, int whichCE, int theField)
{
  int currentExpr; // esi
  int result; // eax
  int nodeType; // ecx
  int count; // [esp+0h] [ebp-18h] BYREF
  int savedExpression; // [esp+4h] [ebp-14h]
  int argNumber; // [esp+8h] [ebp-10h]

  currentExpr = exprPtr;
  savedExpression = theExpression;
  argNumber = 1;
  if ( !exprPtr )
    return 0;
  while ( 1 )
  {
    if ( *(_DWORD *)currentExpr == 15 )
    {
      if ( !*(_DWORD *)(currentExpr + 20) )
        break;
      if ( Rules_ConstraintIsUnmatchable(*(char **)(currentExpr + 16)) && Rules_StaticConstraintCheckingEnabled() )
      {
        Rules_PrintVariableBindingConstraintViolation(*(_DWORD *)(currentExpr + 4), savedExpression, whichCE, argNumber, slotName, theField);
        return currentExpr;
      }
      goto LABEL_6;
    }
    if ( *(_DWORD *)currentExpr == 16 && !*(_DWORD *)(currentExpr + 20) )
      break;
    nodeType = *(_DWORD *)currentExpr;
    if ( *(_DWORD *)currentExpr == 13 )
    {
      if ( !Rules_FindImportExportConstruct(aDefglobal_6, &count, *(_BYTE **)(*(_DWORD *)(currentExpr + 4) + 16), 1, 0) )
        break;
    }
    else if ( nodeType == 10 || nodeType == 11 || nodeType == 12 )
    {
      if ( *(_DWORD *)(currentExpr + 68) )
      {
        result = Rules_CEFindUnboundVariableReference(*(_DWORD *)(currentExpr + 68), currentExpr, slotName, whichCE, theField);
        if ( result )
          return result;
      }
    }
LABEL_6:
    currentExpr = *(_DWORD *)(currentExpr + 64);
    ++argNumber;
    if ( !currentExpr )
      return 0;
  }
  Rules_ReportUnboundVariableUsage(*(_DWORD *)(currentExpr + 4), savedExpression, slotName, whichCE, theField);
  return currentExpr;
}

//----- (004DD820) --------------------------------------------------------
signed int  Rules_ReportUnboundVariableUsage(int theVariable, int theExpression, int slotName, int whichCE, int theField)
{
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int clonedExpression; // eax
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
  Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(theVariable + 16), v8);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_50DE28, v9);
  if ( theExpression )
  {
    clonedExpression = Rules_CECloneBindingList(theExpression);
    AST_Free(*(_DWORD *)(clonedExpression + 10));
    *(_DWORD *)(v12 + 10) = 0;
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFoundInTheExpr, v12);
    Rules_PrintFieldExprList((signed int)g_IO_LogicalNameTable_WError[0], v13);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_50DE48, v14);
    AST_Free(v15);
  }
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aWasReferencedI, v10);
  Rules_PrintLongInteger(v16, whichCE);
  if ( slotName )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSlot_8, v17);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(slotName + 16), v20);
  }
  else if ( theField > 0 )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aField_1, v17);
    Rules_PrintLongInteger(v19, theField);
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
signed int  Rules_ReportConstraintReferenceConflict(int theVariable, int whichCE, int theField)
{
  int v5; // ecx
  char *contextText; // edx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v12; // ecx
  int v13; // ecx

  Rules_PrintErrorID((int)aRulecstr, 1, 1);
  if ( theVariable )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aVariable__0, v5);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(theVariable + 16), v12);
    contextText = aInCe;
  }
  else
  {
    contextText = aPattern_0;
  }
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)contextText, v5);
  Rules_PrintLongInteger(v7, whichCE);
  if ( v8 )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSlot_9, v8);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(v13 + 16), v13);
  }
  else
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aField_2, 0);
    Rules_PrintLongInteger(v9, theField);
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
int  Rules_DeriveCEFieldCardinalityConstraint(int theNode)
{
  int minFields; // ecx
  signed int maxFields; // ebx
  int posInfinity; // esi
  _DWORD *i; // edx
  int constraintNode; // eax
  _DWORD *newConstraint; // edi
  signed int v8; // ecx
  int *minValue; // eax
  __int16 maxType; // ax
  int *maxValueNode; // edx
  char nodeFlags; // bh
  int v13; // edx
  int result; // eax
  char *v15; // edx
  int theConstraint; // edi
  int minBound; // edi
  int j; // eax
  int maxBound; // edi

  minFields = 0;
  maxFields = 0;
  posInfinity = 0;
  if ( (*(_BYTE *)(theNode + 8) & 4) == 0 )
    return 0;
  for ( i = *(_DWORD **)(theNode + 68); i; i = (_DWORD *)i[16] )
  {
    if ( *i == 15 || *i == 17 )
    {
      ++minFields;
      ++maxFields;
    }
    else
    {
      theConstraint = i[4];
      if ( !theConstraint )
        goto LABEL_22;
      minBound = *(_DWORD *)(*(_DWORD *)(theConstraint + 18) + 2);
      if ( minBound != g_Clips_NegativeInfinitySymbol )
        minFields += *(_DWORD *)(minBound + 16);
      for ( j = *(_DWORD *)(i[4] + 22); *(_DWORD *)(j + 10); j = *(_DWORD *)(j + 10) )
        ;
      maxBound = *(_DWORD *)(j + 2);
      if ( maxBound != g_ClipsPositiveInfinitySymbol )
        maxFields += *(_DWORD *)(maxBound + 16);
      else
LABEL_22:
        posInfinity = 1;
    }
  }
  if ( *(_DWORD *)(theNode + 16) )
    constraintNode = Rules_CloneLHSParseNode(*(int **)(theNode + 16));
  else
    constraintNode = Rules_CreateLHSParseNode();
  newConstraint = (_DWORD *)constraintNode;
  AST_Free(*(_DWORD *)(constraintNode + 18));
  AST_Free(*(_DWORD *)((char *)newConstraint + 22));
  minValue = Rules_AddIntegerValue(v8);
  *(_DWORD *)((char *)newConstraint + 18) = AST_NewNode(1, (int)minValue);
  if ( posInfinity )
  {
    maxType = 2;
    maxValueNode = (int *)g_ClipsPositiveInfinitySymbol;
  }
  else
  {
    maxValueNode = Rules_AddIntegerValue(maxFields);
    maxType = 1;
  }
  *(_DWORD *)((char *)newConstraint + 22) = AST_NewNode(maxType, (int)maxValueNode);
  Rules_IntersectConstraints(*(_DWORD *)(theNode + 16), (int)newConstraint);
  if ( (*(_BYTE *)(theNode + 8) & 0x10) != 0 )
    AST_DecrementNodeRefCount(*(_DWORD **)(theNode + 16));
  AST_DecrementNodeRefCount(newConstraint);
  nodeFlags = *(_BYTE *)(theNode + 8);
  *(_DWORD *)(theNode + 16) = v13;
  *(_BYTE *)(theNode + 8) = nodeFlags | 0x10;
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
signed int  Rules_ComputeConnectedCEConstraintGroup(int theNode, int *multifieldNodesList, int patternHead)
{
  int andField; // ebx
  int branchConstraint; // ecx
  _BYTE *returnConstraint; // esi
  int v6; // ecx
  _DWORD *v7; // edi
  _DWORD *v8; // ebx
  int cleanupField; // esi
  int v10; // ecx
  _DWORD *v11; // ebx
  _DWORD *v12; // ecx
  __int16 *constantExpr; // esi
  _BYTE *constantConstraint; // edi
  int v16; // ecx
  _DWORD *v17; // ebp
  int accumConstraints; // [esp+Ch] [ebp-18h]
  int orField; // [esp+10h] [ebp-14h]

  accumConstraints = 0;
  orField = *(_DWORD *)(theNode + 68);
  if ( !orField )
    goto LABEL_15;
  do
  {
    andField = orField;
    branchConstraint = 0;
    do
    {
      if ( (*(_BYTE *)(andField + 8) & 1) != 0 )
        goto LABEL_8;
      if ( *(_DWORD *)andField == 94 )
      {
        if ( **(_DWORD **)(andField + 56) != 10 )
          goto LABEL_8;
        returnConstraint = Rules_ApplyCEKeywordFlags();
        v7 = (_DWORD *)v6;
        Rules_IntersectConstraints(v6, (int)returnConstraint);
        AST_DecrementNodeRefCount(v7);
        goto LABEL_7;
      }
      if ( Rules_TagIsConstantType(*(_DWORD *)andField) )
      {
        constantExpr = (__int16 *)AST_NewNode(*(_DWORD *)andField, *(_DWORD *)(andField + 4));
        constantConstraint = Rules_BuildLHSNodeFromToken(constantExpr);
        v17 = (_DWORD *)v16;
        Rules_IntersectConstraints(v16, (int)constantConstraint);
        AST_DecrementNodeRefCount(v17);
        AST_DecrementNodeRefCount(constantConstraint);
        AST_Free((int)constantExpr);
      }
      else if ( *(_DWORD *)(andField + 16) )
      {
        returnConstraint = (_BYTE *)branchConstraint;
        Rules_IntersectConstraints(branchConstraint, *(_DWORD *)(andField + 16));
LABEL_7:
        AST_DecrementNodeRefCount(returnConstraint);
      }
LABEL_8:
      andField = *(_DWORD *)(andField + 64);
    }
    while ( andField );
    v8 = (_DWORD *)branchConstraint;
    Rules_IntersectConstraints(branchConstraint, *(_DWORD *)(theNode + 16));
    cleanupField = orField;
    AST_DecrementNodeRefCount(v8);
    do
    {
      if ( (*(_BYTE *)(cleanupField + 8) & 1) != 0 && Rules_TagIsConstantType(*(_DWORD *)cleanupField) )
        Rules_RemoveConstantFromConstraint(*(_DWORD *)cleanupField, *(_DWORD *)(cleanupField + 4), v10);
      cleanupField = *(_DWORD *)(cleanupField + 64);
    }
    while ( cleanupField );
    v11 = (_DWORD *)accumConstraints;
    accumConstraints = Rules_UnionConstraints(accumConstraints, v10);
    AST_DecrementNodeRefCount(v11);
    AST_DecrementNodeRefCount(v12);
    orField = *(_DWORD *)(orField + 68);
  }
  while ( orField );
LABEL_15:
  if ( accumConstraints )
  {
    if ( (*(_BYTE *)(theNode + 8) & 0x10) != 0 )
      AST_DecrementNodeRefCount(*(_DWORD **)(theNode + 16));
    *(_DWORD *)(theNode + 16) = accumConstraints;
    *(_BYTE *)(theNode + 8) |= 0x10u;
  }
  if ( Rules_CheckAndReportUnmatchableFieldConstraint() )
    return 1;
  if ( !multifieldNodesList || *(_DWORD *)(theNode + 64) || !Rules_DeriveCEFieldCardinalityConstraint((int)multifieldNodesList) )
    return 0;
  Rules_PrintConstraintViolationMessage((int)aTheGroupOfRest, 0, *(_DWORD *)(patternHead + 8) << 19 >> 25, 0, multifieldNodesList[9], multifieldNodesList[8], 5, multifieldNodesList[4], 1);
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
signed int  Rules_PrintVariableBindingConstraintViolation(int theVariable, int theExpression, int whichCE, int whichArgument, int slotName, int theField)
{
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int clonedExpression; // eax
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
  Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(theVariable + 16), v9);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCausedTheTypeR, v10);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aForArgument_0, v11);
  Rules_PrintLongInteger(v12, whichArgument);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOfTheExpressio, v13);
  clonedExpression = Rules_CECloneBindingList(theExpression);
  AST_Free(*(_DWORD *)(clonedExpression + 10));
  *(_DWORD *)(v15 + 10) = 0;
  Rules_PrintFieldExprList((signed int)g_IO_LogicalNameTable_WError[0], (__int16 *)v15);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_50DFD4, v16);
  AST_Free(v17);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v18, v19);
  Rules_PrintLongInteger(v20, whichCE);
  if ( slotName )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSlot_9, v21);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(slotName + 16), v25);
  }
  else
  {
    v22 = theField;
    if ( theField > 0 )
    {
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aField_2, theField);
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
_DWORD * Rules_MergeConstraintListsByFieldIndex(_DWORD *theList, _DWORD *newItems)
{
  _DWORD *theItem; // ebx
  _DWORD *tempList; // ecx
  _DWORD *nextItem; // edi
  int v6; // ecx
  int v7; // edx
  int v8; // ecx

  theItem = newItems;
  if ( newItems )
  {
    do
    {
      tempList = theList;
      nextItem = (_DWORD *)theItem[16];
      theItem[16] = 0;
      if ( theList )
      {
        while ( tempList[1] != theItem[1] )
        {
          tempList = (_DWORD *)tempList[16];
          if ( !tempList )
            goto LABEL_5;
        }
        Rules_IntersectConstraints(tempList[4], theItem[4]);
        AST_DecrementNodeRefCount(*(_DWORD **)(v6 + 16));
        *(_DWORD *)(v8 + 16) = v7;
        AST_FreeNode((int)theItem);
      }
LABEL_5:
      if ( !tempList )
      {
        theItem[16] = theList;
        theList = theItem;
      }
      theItem = nextItem;
    }
    while ( nextItem );
  }
  return theList;
}
// 4DDF81: variable 'v6' is possibly undefined
// 4DDF8B: variable 'v7' is possibly undefined
// 4DDF8B: variable 'v8' is possibly undefined
// 4DDF95: variable 'v4' is possibly undefined

//----- (004DDFC0) --------------------------------------------------------
signed int  Rules_IntersectConstraintListsByFieldIndex(int theList1, int theList2)
{
  int theNode; // ecx
  signed int theHead; // edi
  int otherNode; // edx
  signed int tempNode; // ebx
  int v7; // ecx
  int v8; // edx
  int v9; // edx

  theNode = theList1;
  theHead = 0;
  if ( theList1 )
  {
    do
    {
      otherNode = theList2;
      if ( theList2 )
      {
        while ( *(_DWORD *)(theNode + 4) != *(_DWORD *)(otherNode + 4) )
        {
          otherNode = *(_DWORD *)(otherNode + 64);
          if ( !otherNode )
            goto LABEL_5;
        }
        tempNode = AST_AllocNode();
        *(_BYTE *)(tempNode + 8) |= 0x10u;
        *(_DWORD *)(tempNode + 4) = *(_DWORD *)(v7 + 4);
        *(_DWORD *)(tempNode + 16) = Rules_UnionConstraints(*(_DWORD *)(v7 + 16), *(_DWORD *)(v8 + 16));
        *(_DWORD *)(tempNode + 64) = theHead;
        theHead = tempNode;
      }
LABEL_5:
      *(_DWORD *)(theNode + 64) = 0;
      AST_FreeNode(theNode);
      theNode = v9;
    }
    while ( v9 );
  }
  AST_FreeNode(theList2);
  return theHead;
}
// 4DDFEC: variable 'v7' is possibly undefined
// 4DDFF2: variable 'v8' is possibly undefined
// 4DE00A: variable 'v2' is possibly undefined
// 4DE016: variable 'v9' is possibly undefined

//----- (004DE040) --------------------------------------------------------
_DWORD * Rules_ClonePatternPositionConstraintList(int *theExpression)
{
  int *expPtr; // ecx
  _DWORD *i; // edx
  int nodeType; // esi
  signed int newNode; // eax
  int v5; // ecx
  int *referringNode; // edi
  _DWORD *theConstraint; // ebx
  _DWORD *v8; // edx
  _DWORD *tmpList; // eax
  _DWORD *v11; // edx

  expPtr = theExpression;
  for ( i = 0; expPtr; expPtr = (int *)expPtr[17] )
  {
    if ( expPtr[16] )
    {
      tmpList = (_DWORD *)Rules_ClonePatternPositionConstraintList(expPtr[16]);
      i = Rules_MergeConstraintListsByFieldIndex(tmpList, v11);
    }
    nodeType = *expPtr;
    if ( *expPtr == 15 )
    {
      newNode = AST_AllocNode();
      referringNode = *(int **)(v5 + 20);
      theConstraint = (_DWORD *)newNode;
      if ( referringNode )
        nodeType = *referringNode;
      *(_DWORD *)newNode = nodeType;
      *(_DWORD *)(newNode + 4) = *(_DWORD *)(v5 + 4);
      *(_BYTE *)(newNode + 8) |= 0x10u;
      *(_DWORD *)(newNode + 16) = Rules_CloneLHSParseNode(*(int **)(v5 + 16));
      i = Rules_MergeConstraintListsByFieldIndex(theConstraint, v8);
    }
  }
  return i;
}
// 4DE0A1: variable 'v11' is possibly undefined
// 4DE054: variable 'v1' is possibly undefined
// 4DE060: variable 'v5' is possibly undefined
// 4DE084: variable 'v8' is possibly undefined

//----- (004DE0B0) --------------------------------------------------------
signed int  Rules_IntersectConnectedCEConstraints(int theNode)
{
  int first; // ebp
  int orField; // esi
  int list1; // edi
  int andField; // ecx
  _DWORD *list2; // ebx
  _DWORD *clonedList; // eax
  signed int result; // eax

  first = 1;
  orField = *(_DWORD *)(theNode + 68);
  list1 = 0;
  if ( !orField )
    return list1;
  do
  {
    while ( 1 )
    {
      andField = orField;
      list2 = 0;
      do
      {
        if ( *(_DWORD *)andField == 94 || *(_DWORD *)andField == 93 )
        {
          clonedList = Rules_ClonePatternPositionConstraintList(*(int **)(andField + 56));
          list2 = Rules_MergeConstraintListsByFieldIndex(list2, clonedList);
        }
        andField = *(_DWORD *)(andField + 64);
      }
      while ( andField );
      if ( !first )
        break;
      list1 = (int)list2;
      first = 0;
      orField = *(_DWORD *)(orField + 68);
      if ( !orField )
        return list1;
    }
    result = Rules_IntersectConstraintListsByFieldIndex(list1, (int)list2);
    list1 = result;
    orField = *(_DWORD *)(orField + 68);
  }
  while ( orField );
  return result;
}
// 4DE0CA: conditional instruction was optimized away because esi.4!=0
// 4DE0E6: variable 'v4' is possibly undefined

//----- (004DE130) --------------------------------------------------------
signed int  Rules_CheckRHSActionsAgainstCEConstraints(signed int result, int theLHS)
{
  int argNumber; // edi
  int theExpression; // esi
  int nextExpression; // ecx
  signed int exprPtr; // [esp+0h] [ebp-20h]
  int lastOne; // [esp+4h] [ebp-1Ch]
  int theFunction; // [esp+8h] [ebp-18h]

  if ( result )
  {
    exprPtr = result;
    while ( 2 )
    {
      argNumber = 1;
      theExpression = *(_DWORD *)(exprPtr + 6);
      if ( *(_WORD *)exprPtr == 10 )
      {
        lastOne = exprPtr;
        theFunction = *(_DWORD *)(exprPtr + 2);
      }
      else
      {
        theFunction = 0;
      }
      while ( theExpression )
      {
        if ( Rules_CheckFieldRestrictionAgainstRHSAction(theExpression, lastOne, theFunction, argNumber, theLHS) )
          return 1;
        *(_DWORD *)(theExpression + 10) = 0;
        ++argNumber;
        if ( Rules_CheckRHSActionsAgainstCEConstraints(theExpression, theLHS) )
          return 1;
        *(_DWORD *)(theExpression + 10) = nextExpression;
        theExpression = nextExpression;
      }
      exprPtr = *(_DWORD *)(exprPtr + 10);
      if ( exprPtr )
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
signed int  Rules_CheckFieldRestrictionAgainstRHSAction(int theExpression, int lastOne, int theFunction, int argNumber, int theLHS)
{
  int errorFlag; // ebx
  _DWORD *v10; // ecx
  _DWORD *theCE; // eax
  int newParseNode; // eax
  int namedContextConstraint; // eax
  int v14; // edx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int nextOne; // ebx
  int v22; // ecx
  _DWORD *v23; // ecx
  char *constraint4; // [esp+0h] [ebp-18h]
  _DWORD *constraint3; // [esp+4h] [ebp-14h]
  _BYTE *constraint1; // [esp+8h] [ebp-10h]

  errorFlag = 0;
  if ( *(_WORD *)theExpression != 15 || !theFunction )
    return 0;
  Rules_GetArgRestrictionType(theFunction, argNumber);
  constraint1 = Rules_ApplyPatternKeywordFlags();
  theCE = Rules_FindCEByIndex(*(_DWORD *)(theExpression + 2), v10);
  if ( theCE )
  {
    if ( *theCE == 16 )
    {
      newParseNode = Rules_CreateLHSParseNode();
      Rules_UpdateCETypeFlag(4u, newParseNode);
    }
    else if ( theCE[4] )
    {
      Rules_CloneLHSParseNode((int *)theCE[4]);
    }
    else
    {
      Rules_CreateLHSParseNode();
    }
  }
  namedContextConstraint = Rules_GetNamedContextValue(*(_DWORD *)(theExpression + 2));
  constraint3 = (_DWORD *)Rules_UnionConstraints(namedContextConstraint, v14);
  constraint4 = Rules_IntersectConstraints((int)constraint3, (int)constraint1);
  if ( Rules_ConstraintIsUnmatchable(constraint4) )
  {
    if ( Rules_StaticConstraintCheckingEnabled() )
    {
      Rules_PrintErrorID((int)aRulecstr, 3, 1);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aPreviousVariab, v15);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(*(_DWORD *)(theExpression + 2) + 16), v16);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCausedTheTypeR, v17);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aForArgument_0, v18);
      Rules_PrintLongInteger(v19, argNumber);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOfTheExpressio, v20);
      nextOne = *(_DWORD *)(lastOne + 10);
      *(_DWORD *)(lastOne + 10) = 0;
      Rules_PrintFieldExprList((signed int)g_IO_LogicalNameTable_WError[0], (__int16 *)lastOne);
      *(_DWORD *)(lastOne + 10) = nextOne;
      errorFlag = 1;
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFoundInTheRule, v22);
    }
  }
  AST_DecrementNodeRefCount(constraint1);
  AST_DecrementNodeRefCount(v23);
  AST_DecrementNodeRefCount(constraint3);
  AST_DecrementNodeRefCount(constraint4);
  return errorFlag;
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
_DWORD * Rules_BuildJoinTestExpressionChain(int logicalJoin, _DWORD *theLHS, _DWORD *lastNode)
{
  _DWORD *lastJoin; // esi
  int v4; // edx
  int currentDepth; // edi
  _DWORD *currentPattern; // ecx
  int depthCursor; // eax
  int patternEntity; // eax
  int v9; // ebx
  __int64 v10; // rax
  int rhsEntry; // ebp
  int v12; // ecx
  int depthOffset; // ebp
  _WORD *newJoin; // eax
  int v15; // edx
  int v16; // ecx
  int v18; // ecx
  int joinStack[33]; // [esp+4h] [ebp-BCh] BYREF
  int v21; // [esp+88h] [ebp-38h]
  BOOL isLogical; // [esp+8Ch] [ebp-34h]
  int v23; // [esp+90h] [ebp-30h]
  int i; // [esp+94h] [ebp-2Ch]
  int patternDepth; // [esp+98h] [ebp-28h]
  int currentCE; // [esp+9Ch] [ebp-24h]
  int patternDepthOffset; // [esp+A0h] [ebp-20h]
  _DWORD *thePattern; // [esp+A4h] [ebp-1Ch]
  int tryToReuse; // [esp+A8h] [ebp-18h]

  v21 = logicalJoin;
  thePattern = theLHS;
  Rules_MergeRedundantFieldAccessNodes(theLHS, lastNode);
  lastJoin = 0;
  tryToReuse = v4;
  currentCE = v4;
  currentDepth = v4;
  for ( i = 0; thePattern; ++currentCE )
  {
    if ( !thePattern[17] )
      i = 1;
    currentPattern = thePattern;
    depthCursor = currentDepth;
    while ( currentDepth < currentPattern[11] )
    {
      ++depthCursor;
      ++currentDepth;
      joinStack[depthCursor - 1] = (int)lastJoin;
    }
    patternEntity = currentPattern[6];
    v23 = *(_DWORD *)(patternEntity + 8);
    v9 = v21;
    v10 = ((__int64 (*)(void))*(_DWORD *)(patternEntity + 24))();
    rhsEntry = v10;
    isLogical = currentCE == v9;
    if ( HIDWORD(v10) == 1 )
      LODWORD(v10) = *(_DWORD *)(v10 + 8);
    else
      LODWORD(v10) = lastJoin[5];
    patternDepth = thePattern[12];
    if ( tryToReuse == 1
      && Rules_FindExistingJoinTestNode((_DWORD *)v10, rhsEntry, thePattern[2] & 1, SHIDWORD(v10), isLogical, (__int16 *)thePattern[13], patternDepth, currentDepth, i, (int)&joinStack[1]) )
    {
      if ( Rules_GetWatchItemState((int)aCompilations) == 1 && Rules_GetLoadInProgress() )
        Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aJ, v12);
      lastJoin = (_DWORD *)v12;
    }
    else
    {
      joinStack[0] = thePattern[2] & 1;
      tryToReuse = 0;
      newJoin = (_WORD *)Rules_InternJoinTestNode(thePattern[13], lastJoin, 0, rhsEntry, joinStack[0]);
      v15 = v23 & 7;
      *newJoin &= 0xFE3Fu;
      lastJoin = newJoin;
      *(_DWORD *)newJoin |= v15 << 6;
    }
    depthOffset = 4 * currentDepth;
    patternDepthOffset = 4 * patternDepth;
    while ( depthOffset > patternDepthOffset )
    {
      depthOffset -= 4;
      --currentDepth;
      if ( !lastJoin[5] )
      {
        tryToReuse = 0;
        goto LABEL_19;
      }
      if ( tryToReuse )
      {
        if ( Rules_GetWatchItemState((int)aCompilations) == 1 && Rules_GetLoadInProgress() )
        {
          Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aJ, v16);
          lastJoin = (_DWORD *)lastJoin[5];
        }
        else
        {
          lastJoin = (_DWORD *)lastJoin[5];
        }
      }
      else
      {
LABEL_19:
        lastJoin = (_DWORD *)Rules_InternJoinTestNode(0, (_DWORD *)joinStack[depthOffset / 4u], 1, (int)lastJoin, 0);
      }
    }
    thePattern = (_DWORD *)thePattern[17];
  }
  if ( Rules_GetWatchItemState((int)aCompilations) != 1 || !Rules_GetLoadInProgress() )
    return lastJoin;
  Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)asc_50E03C, v18);
  return lastJoin;
}
// 4DE3A3: variable 'v4' is possibly undefined
// 4DE4C8: variable 'v12' is possibly undefined
// 4DE5AF: variable 'v16' is possibly undefined
// 4DE616: variable 'v18' is possibly undefined
// 51A61C: using guessed type char *off_51A61C[3];

//----- (004DE630) --------------------------------------------------------
_DWORD * Rules_MergeRedundantFieldAccessNodes(_DWORD *result, _DWORD *lastNode)
{
  _DWORD *i; // ebx
  int scanNode; // ecx
  _DWORD *testCE; // ecx
  int v5; // edx
  int v6; // edx

  for ( i = result; i; i = (_DWORD *)i[17] )
  {
    if ( (i[2] & 1) != 0 )
    {
      scanNode = 0;
    }
    else
    {
      lastNode = i;
      scanNode = i[17];
    }
    while ( scanNode )
    {
      result = *(_DWORD **)(scanNode + 44);
      if ( result != (_DWORD *)i[11] || (*(_DWORD *)(scanNode + 8) & 1) != 0 )
      {
        lastNode = (_DWORD *)scanNode;
        scanNode = *(_DWORD *)(scanNode + 68);
      }
      else
      {
        if ( *(_DWORD *)scanNode == 80 )
          break;
        if ( *(_DWORD *)scanNode == 84 )
        {
          i[13] = AST_MergeFieldAccessNodes((_DWORD *)i[13], *(_DWORD **)(scanNode + 52));
          testCE[13] = 0;
          v5 = testCE[17];
          testCE[17] = 0;
          lastNode[17] = v5;
          lastNode[12] = testCE[12];
          result = (_DWORD *)AST_FreeNode((int)testCE);
          scanNode = v6;
        }
        else
        {
          Rules_ReportSystemError(scanNode, 1);
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
        _DWORD *listOfJoins,
        int rhsStruct,
        int negatedRHS,
        int firstJoin,
        int a5,
        __int16 *joinTest,
        int endDepth,
        int currentDepth,
        int isLastPattern,
        int joinStack)
{
  _DWORD *theJoin; // esi

  theJoin = listOfJoins;
  if ( !listOfJoins )
    return 0;
  do
  {
    while ( 1 )
    {
      if ( rhsStruct == theJoin[4] && Rules_JoinTestNodeMatches((int)theJoin, firstJoin, a5, negatedRHS, joinTest, endDepth, currentDepth, isLastPattern, joinStack) )
        return theJoin;
      if ( !firstJoin )
        break;
      theJoin = (_DWORD *)theJoin[8];
      if ( !theJoin )
        return 0;
    }
    theJoin = (_DWORD *)theJoin[7];
  }
  while ( theJoin );
  return 0;
}

//----- (004DE750) --------------------------------------------------------
BOOL  Rules_JoinTestNodeMatches(
        int theJoin,
        int firstJoin,
        int a3,
        int negatedRHS,
        __int16 *joinTest,
        int endDepth,
        int currentDepth,
        int isLastPattern,
        int joinStack)
{
  int currentJoin; // esi
  int depthCursor; // ecx
  int stackPtr; // eax
  int v13; // eax

  currentJoin = theJoin;
  if ( firstJoin != (*(_DWORD *)theJoin & 1)
    || *(_DWORD *)theJoin << 28 >> 31 != negatedRHS
    || a3 == 1 && (*(_BYTE *)theJoin & 2) == 0 && *(_DWORD *)(theJoin + 8)
    || AST_NodeListsEqual(*(__int16 **)(theJoin + 12), joinTest) != 1 )
  {
    return 0;
  }
  stackPtr = joinStack + 4 * depthCursor;
  while ( endDepth < depthCursor )
  {
    currentJoin = *(_DWORD *)(currentJoin + 20);
    if ( !currentJoin || (*(_BYTE *)currentJoin & 4) == 0 || *(_DWORD *)(stackPtr - 8) != *(_DWORD *)(currentJoin + 24) )
      return 0;
    stackPtr -= 4;
    --depthCursor;
  }
  if ( isLastPattern && (*(_DWORD *)(currentJoin + 36) || *(_DWORD *)(currentJoin + 8)) )
    return 0;
  return isLastPattern || (v13 = *(_DWORD *)(currentJoin + 20)) == 0 || (*(_BYTE *)v13 & 4) == 0 || currentJoin != *(_DWORD *)(v13 + 16);
}
// 4DE79F: variable 'v10' is possibly undefined

//----- (004DE810) --------------------------------------------------------
int  Rules_InternJoinTestNode(int joinTest, _DWORD *lhsEntry, int joinFromTheRight, int rhsEntry, char negatedRHS)
{
  _DWORD *freeListEntry; // ecx
  signed int newJoin; // edx
  int v10; // edx
  int v11; // ecx
  int hashedJoinTest; // eax
  int v13; // edx
  __int16 v14; // si
  int v16; // ecx
  char v17; // al
  int incrementalResetFlag; // [esp+0h] [ebp-10h]

  if ( Rules_GetWatchItemState((int)aCompilations) == 1 && Rules_GetLoadInProgress() )
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aJ_0, v16);
  freeListEntry = *(_DWORD **)(g_ClipsMemoryTable + 160);
  if ( freeListEntry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 160);
    *(_DWORD *)(g_ClipsMemoryTable + 160) = *freeListEntry;
    newJoin = g_ClipsMemFreeListTemp;
  }
  else
  {
    newJoin = Mem_HeapAllocWithRetry(40);
  }
  *(_BYTE *)newJoin &= ~4u;
  *(_DWORD *)newJoin |= 4 * (joinFromTheRight & 1);
  *(_BYTE *)newJoin &= ~8u;
  *(_DWORD *)(newJoin + 8) = 0;
  *(_DWORD *)(newJoin + 20) = 0;
  *(_DWORD *)newJoin |= 8 * (negatedRHS & 1);
  incrementalResetFlag = Rules_GetIncrementalReset() & 1;
  *(_BYTE *)v10 &= ~0x10u;
  *(_DWORD *)v10 |= 16 * incrementalResetFlag;
  *(_BYTE *)v10 &= ~2u;
  *(_DWORD *)(v10 + 36) = 0;
  hashedJoinTest = AST_AddHashedNodeChain(joinTest, v10, v11);
  *(_DWORD *)(v13 + 12) = hashedJoinTest;
  *(_DWORD *)(v13 + 24) = lhsEntry;
  if ( lhsEntry )
  {
    *(_BYTE *)v13 &= ~1u;
    v17 = (*lhsEntry << 16 >> 25) + 1;
    *(_BYTE *)(v13 + 1) &= 1u;
    *(_DWORD *)v13 |= (v17 & 0x7F) << 9;
    *(_DWORD *)(v13 + 28) = lhsEntry[5];
    lhsEntry[5] = v13;
  }
  else
  {
    v14 = *(_WORD *)v13 & 0x1FE;
    *(_DWORD *)(v13 + 28) = 0;
    *(_WORD *)v13 = v14;
    *(_WORD *)v13 = v14 | 0x201;
  }
  *(_DWORD *)(v13 + 16) = rhsEntry;
  if ( joinFromTheRight )
  {
    *(_DWORD *)(v13 + 32) = 0;
    *(_DWORD *)(rhsEntry + 20) = v13;
  }
  else
  {
    *(_DWORD *)(v13 + 32) = *(_DWORD *)(rhsEntry + 8);
    *(_DWORD *)(rhsEntry + 8) = v13;
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
int ** Defgeneric_InitializeFromRestrictionString(int theDefgeneric, int a2)
{
  int **result; // eax
  _DWORD *v3; // ecx
  __int16 actionExpr; // [esp+0h] [ebp-14h] BYREF
  int **exprValue; // [esp+2h] [ebp-12h]
  int v6; // [esp+6h] [ebp-Eh]
  int v7; // [esp+Ah] [ebp-Ah]
  int v8; // [esp+10h] [ebp-4h]

  v8 = a2;
  result = Rules_MakeSymbol(*(_BYTE **)(*(_DWORD *)theDefgeneric + 16));
  if ( result )
  {
    actionExpr = 10;
    exprValue = result;
    v7 = 0;
    v6 = 0;
    return (int **)Method_ParseWildcardRestrictionString(v3, *(char **)((char *)result + 17), (int)v3, &actionExpr);
  }
  return result;
}
// 4DE9E9: variable 'v3' is possibly undefined

//----- (004DEA00) --------------------------------------------------------
int  Method_ParseWildcardRestrictionString(_DWORD *theDefgeneric, char *restrictionString, int a3, _DWORD *theActions)
{
  _DWORD *v4; // edx
  signed int v5; // eax
  int defaultRestriction; // esi
  _DWORD *v7; // ecx
  _DWORD *defaultTypeInfo; // ecx
  int v9; // ecx
  _DWORD *v10; // eax
  __int16 *v11; // eax
  unsigned int *v12; // eax
  int v14; // ecx
  int restrictionList; // esi
  int restrictionCount; // edi
  char *v17; // ebp
  char *v18; // eax
  char v19; // al
  _DWORD *typeInfo; // ecx
  _DWORD *v21; // ebx
  signed int newRestriction; // eax
  int argCount; // ebp
  char *charPtr; // edi
  int v25; // ebx
  _DWORD *wildcardTypeInfo; // edi
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
  signed int wildcardRestriction; // eax
  int wildcardArgCount; // edi
  __int16 *v42; // eax
  unsigned int *v43; // eax
  int excessRestrictions; // eax
  __int16 *v45; // eax
  unsigned int *v46; // eax
  _DWORD *optionalTypeInfo; // ecx
  _DWORD *v48; // ebx
  signed int optionalRestriction; // eax
  char v50; // dh
  __int16 *v51; // eax
  unsigned int *v52; // eax
  signed int lastRequiredRestriction; // [esp+0h] [ebp-44h]
  int methodPosition; // [esp+4h] [ebp-40h] BYREF
  int createMinimumMethod; // [esp+8h] [ebp-3Ch]
  _DWORD *v56; // [esp+Ch] [ebp-38h]
  char *v57; // [esp+10h] [ebp-34h]
  int minArgs; // [esp+14h] [ebp-30h]
  int maxArgs; // [esp+18h] [ebp-2Ch]
  int optionalArgs; // [esp+1Ch] [ebp-28h]
  _DWORD *v61; // [esp+20h] [ebp-24h]
  int v62; // [esp+24h] [ebp-20h]
  signed int lastRestriction; // [esp+28h] [ebp-1Ch]
  int charIndex; // [esp+2Ch] [ebp-18h]
  char v65; // [esp+30h] [ebp-14h]
  char v66; // [esp+31h] [ebp-13h]
  char defaultTypeChar; // [esp+34h] [ebp-10h]

  v61 = theDefgeneric;
  v57 = restrictionString;
  v56 = theActions;
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
      v65 = *v57;
      minArgs = atoi_(a3);
    }
    if ( v57[1] == 42 )
    {
      maxArgs = -1;
    }
    else
    {
      v65 = v57[1];
      maxArgs = atoi_(v14);
    }
    if ( v57[2] )
    {
      defaultTypeChar = v57[2];
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
      v17 = &v57[charIndex];
      do
      {
        if ( *v17 )
        {
          v18 = &v57[charIndex];
          ++v17;
          ++charIndex;
          v19 = *v18;
        }
        else
        {
          v19 = defaultTypeChar;
        }
        v65 = v19;
        typeInfo = Method_BuildTypeRestrictionRecordFromFlags();
        v21 = *(_DWORD **)(g_ClipsMemoryTable + 56);
        if ( v21 )
        {
          g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 56);
          *(_DWORD *)(g_ClipsMemoryTable + 56) = *v21;
          newRestriction = g_ClipsMemFreeListTemp;
        }
        else
        {
          newRestriction = Mem_HeapAllocWithRetry((_DWORD *)0xE);
        }
        *(_DWORD *)(newRestriction + 10) = 0;
        *(_DWORD *)(newRestriction + 6) = typeInfo;
        if ( restrictionList )
          *(_DWORD *)(lastRestriction + 10) = newRestriction;
        else
          restrictionList = newRestriction;
        ++restrictionCount;
        lastRestriction = newRestriction;
      }
      while ( restrictionCount < minArgs );
    }
    lastRequiredRestriction = lastRestriction;
    argCount = minArgs;
    v62 = minArgs + 1;
    createMinimumMethod = 1;
    optionalArgs = 0;
    charPtr = &v57[charIndex];
    if ( v57[charIndex] )
    {
      while ( charPtr[1] || v62 != maxArgs )
      {
        optionalTypeInfo = Method_BuildTypeRestrictionRecordFromFlags();
        v48 = *(_DWORD **)(g_ClipsMemoryTable + 56);
        if ( v48 )
        {
          g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 56);
          *(_DWORD *)(g_ClipsMemoryTable + 56) = *v48;
          optionalRestriction = g_ClipsMemFreeListTemp;
        }
        else
        {
          optionalRestriction = Mem_HeapAllocWithRetry((_DWORD *)0xE);
        }
        *(_DWORD *)(optionalRestriction + 10) = 0;
        *(_DWORD *)(optionalRestriction + 6) = optionalTypeInfo;
        if ( restrictionList )
          *(_DWORD *)(lastRestriction + 10) = optionalRestriction;
        else
          restrictionList = optionalRestriction;
        lastRestriction = optionalRestriction;
        ++argCount;
        ++charPtr;
        ++v62;
        ++optionalArgs;
        v50 = *charPtr;
        ++charIndex;
        if ( v50 || argCount == maxArgs )
        {
          Method_FindInsertionIndex((int)v61, restrictionList, 0, argCount, (unsigned int *)&methodPosition);
          v51 = (__int16 *)AST_PackNodeChain(v56);
          v52 = Defgeneric_AddMethod(v61, 0, 0, methodPosition, restrictionList, argCount, 0, 0, v51, 0, 1);
          *((_BYTE *)v52 + 24) |= 1u;
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
      v25 = maxArgs;
      wildcardTypeInfo = Method_BuildTypeRestrictionRecordFromFlags();
      if ( v25 != -1 )
      {
        Symbol = Rules_MakeSymbol(asc_50E04C);
        v28 = AST_NewNode(10, (int)Symbol);
        *(_DWORD *)(v29 + 4) = v28;
        v30 = Rules_MakeSymbol(aLength_1);
        v31 = AST_NewNode(10, (int)v30);
        v33 = optionalArgs;
        *(_DWORD *)(*(_DWORD *)(v32 + 4) + 6) = v31;
        v34 = AST_NewProcParamNode(v33 + minArgs + 1);
        *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v35 + 4) + 6) + 6) = v34;
        v36 = Rules_AddIntegerValue(v25 - minArgs - v33);
        v37 = AST_NewNode(1, (int)v36);
        *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v38 + 4) + 6) + 10) = v37;
      }
      v39 = *(_DWORD **)(g_ClipsMemoryTable + 56);
      if ( v39 )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 56);
        *(_DWORD *)(g_ClipsMemoryTable + 56) = *v39;
        wildcardRestriction = g_ClipsMemFreeListTemp;
      }
      else
      {
        wildcardRestriction = Mem_HeapAllocWithRetry((_DWORD *)0xE);
      }
      *(_DWORD *)(wildcardRestriction + 10) = 0;
      *(_DWORD *)(wildcardRestriction + 6) = wildcardTypeInfo;
      if ( restrictionList )
        *(_DWORD *)(lastRestriction + 10) = wildcardRestriction;
      else
        restrictionList = wildcardRestriction;
      wildcardArgCount = optionalArgs + minArgs + 1;
      Method_FindInsertionIndex((int)v61, restrictionList, g_ClipsTrueSymbol, wildcardArgCount, (unsigned int *)&methodPosition);
      v42 = (__int16 *)AST_PackNodeChain(v56);
      v43 = Defgeneric_AddMethod(v61, 0, 0, methodPosition, restrictionList, wildcardArgCount, 0, g_ClipsTrueSymbol, v42, 0, 0);
      *((_BYTE *)v43 + 24) |= 1u;
    }
    if ( createMinimumMethod )
    {
      if ( lastRequiredRestriction )
      {
        excessRestrictions = *(_DWORD *)(lastRequiredRestriction + 10);
        *(_DWORD *)(lastRequiredRestriction + 10) = 0;
        Method_FreeRestrictionChain(excessRestrictions);
      }
      Method_FindInsertionIndex((int)v61, restrictionList, 0, minArgs, (unsigned int *)&methodPosition);
      v45 = (__int16 *)AST_PackNodeChain(v56);
      v46 = Defgeneric_AddMethod(v61, 0, 0, methodPosition, restrictionList, minArgs, 0, 0, v45, 0, 1);
      *((_BYTE *)v46 + 24) |= 1u;
    }
    return Method_FreeRestrictionChain(restrictionList);
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
    defaultRestriction = v5;
    v7 = *(_DWORD **)(g_ClipsMemoryTable + 48);
    if ( v7 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
      *(_DWORD *)(g_ClipsMemoryTable + 48) = *v7;
      defaultTypeInfo = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      defaultTypeInfo = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0xC);
    }
    Method_PackRestrictionTypes(defaultTypeInfo, 0);
    *(_DWORD *)(v9 + 4) = 0;
    *(_DWORD *)(defaultRestriction + 10) = 0;
    v10 = v56;
    *(_DWORD *)(defaultRestriction + 6) = v9;
    v11 = (__int16 *)AST_PackNodeChain(v10);
    v12 = Defgeneric_AddMethod(v61, 0, 0, 0, defaultRestriction, 1, 0, g_ClipsTrueSymbol, v11, 0, 0);
    *((_BYTE *)v12 + 24) |= 1u;
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
_DWORD *Method_BuildTypeRestrictionRecordFromFlags()
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

  freeListEntry = *(_DWORD **)(g_ClipsMemoryTable + 48);
  typeExprList = 0;
  if ( freeListEntry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
    *(_DWORD *)(g_ClipsMemoryTable + 48) = *freeListEntry;
    allocatedBlock = g_ClipsMemFreeListTemp;
  }
  else
  {
    allocatedBlock = Mem_HeapAllocWithRetry((_DWORD *)0xC);
  }
  restrictionRecord = (_DWORD *)allocatedBlock;
  *(_DWORD *)(allocatedBlock + 4) = 0;
  keywordFlags = Rules_ApplyPatternKeywordFlags();
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
  typeExprList = Method_AddTypeRestrictionNode(0, lexemeClassName, lexemeTypeCode);
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
  typeExprList = Method_AddTypeRestrictionNode(v11, numberClassName, numberTypeCode);
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
  typeExprList = Method_AddTypeRestrictionNode(v14, instanceClassName, instanceTypeCode);
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
  typeExprList = Method_AddTypeRestrictionNode(v17, addressClassName, addressTypeCode);
LABEL_21:
  if ( flagsBitmap[1] < 0 )
    typeExprList = Method_AddTypeRestrictionNode(typeExprList, 0, 4);
LABEL_23:
  AST_DecrementNodeRefCount(flagsBitmap);
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
    result = AST_NewNode(0, (int)theClass);
  }
  else
  {
    result = AST_NewNode(0, g_ClipsPrimitiveTypeClassMap[typeCode]);
  }
  *(_DWORD *)(result + 10) = nextNode;
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
  int v23; // eax
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
  classNameSymbol = Rules_GetConstructNameAndComment(readSource, (int)&g_ParserCurrentTokenType, 0, aDefmessageHa_2, 0, asc_50E0A8, 1, 0, 1);
  if ( !classNameSymbol )
    return 1;
  lookupClass = Class_LookupByQualifiedName(*(_BYTE **)(classNameSymbol + 16));
  handlerClass = lookupClass;
  if ( !lookupClass )
  {
    Rules_PrintErrorID((int)aMsgpsr, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAClassMustBeDe, v21);
    return 1;
  }
  if ( lookupClass == (int *)g_Class_InstanceName || lookupClass == (int *)g_Class_InstanceAddress || lookupClass == **(int ***)(g_Class_InstanceName + 36) )
  {
    Rules_PrintErrorID((int)aMsgpsr, 8, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aMessageHandl_1, v22);
    v23 = Rules_GetConstructNameString((int)handlerClass);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], v23, v24);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__13, v25);
    return 1;
  }
  if ( MessageHandler_AnyHandlerBusy((int)lookupClass) )
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
  handlerNameSymbol = g_ClipsParserTokenValue;
  Parser_NextToken(readSource, (int)&g_ParserCurrentTokenType);
  if ( g_ParserCurrentTokenType == 100 )
    goto LABEL_17;
  IO_OutWriteToken(asc_50E190);
  if ( g_ParserCurrentTokenType != 3 )
  {
    if ( g_ParserCurrentTokenType == 2 )
    {
      handlerType = MessageHandler_TypeIndexFromKeyword((int)aDefmessageHa_2);
      if ( handlerType == 4 )
        return 1;
      Parser_NextToken(readSource, (int)&g_ParserCurrentTokenType);
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
  IO_OutWriteToken((char *)g_ClipsScanTokenPrintForm);
  foundHandler = Class_FindMessageHandler(handlerClass, v9, handlerType);
  handler = foundHandler;
  if ( Rules_GetLoadInProgress() && Rules_GetWatchCompilations() )
  {
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aHandler, v12);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], *(_DWORD *)(handlerNameSymbol + 16), v13);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)asc_50E190, v14);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)g_MessageHandlerTypeNames[handlerType], v15);
    if ( foundHandler )
      statusText = aRedefined__0;
    else
      statusText = aDefined__0;
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)statusText, v16);
  }
  if ( foundHandler && (*foundHandler & 1) != 0 )
  {
    Rules_PrintErrorID((int)aMsgpsr, 3, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSystemMessageH, v28);
    return 1;
  }
  else
  {
    selfParamNode = AST_NewNode(2, g_MessageHandler_SelfSymbol);
    handlerParams = Parser_ParseProcParameters(readSource, &g_ParserCurrentTokenType, &wildcardSymbol, selfParamNode, &minParams, &maxParams, &parseError, (int (*)(void))MessageHandler_CheckParamNotSelfReference);
    paramsToFree = handlerParams;
    if ( parseError )
    {
      return 1;
    }
    else
    {
      AST_Append((int)handlerClass, v19);
      g_ClipsParseReturnContext = 1;
      handlerActions = (__int16 *)Parser_ParseProcActions(
                         (int)aMessageHandl_2,
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
          IO_OutWriteToken((char *)g_ClipsScanTokenPrintForm);
          IO_OutWriteToken(asc_50E1FC);
          if ( handler )
          {
            AST_DeinstallNodeChain((__int16 *)handler[7]);
            AST_FreePackedNodeChain(handler[7]);
            if ( handler[8] )
              Mem_SmallBlockFree((_DWORD *)handler[8], strlen((const char *)handler[8]) + 1);
          }
          else
          {
            handler = Class_InsertMessageHandlerRecord(handlerClass, handlerNameSymbol, handlerType);
            ++*(_DWORD *)(handler[2] + 4);
          }
          AST_Free(paramsToFree);
          handler[4] = minParams;
          handler[5] = maxParams;
          handler[6] = localVarCount;
          actionsInstallPtr = handlerActions;
          handler[7] = handlerActions;
          AST_InstallNodeChain(actionsInstallPtr);
          if ( Mem_GetAllocFlag() )
            handler[8] = 0;
          else
            handler[8] = Rules_CopyPPBuffer();
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

  slotDescPtr = (_BYTE *)result;
  slotFlags = *(_BYTE *)(result + 1);
  if ( (slotFlags & 8) != 0 || (slotFlags & 0x10) != 0 )
  {
    className = *(const char **)(**(_DWORD **)(result + 4) + 16);
    slotName = *(const char **)(*(_DWORD *)(*(_DWORD *)(result + 8) + 12) + 16);
    bufferSize = strlen(className) + 2 * strlen(slotName) + 80;
    Mem_SmallBlockAlloc(bufferSize);
    savedLoadInProgress = Rules_GetLoadInProgress();
    Rules_SetLoadInProgress(0);
    Mem_SetAllocFlag(v4, v3);
    if ( (slotDescPtr[1] & 8) != 0 )
    {
      sprintf_(v5, "%s get-%s () ?self:%s)", className, slotName, slotName);
      if ( IO_OpenStringSource((int)aDefaultPublicH, v7, 0) )
      {
        MessageHandler_ParseDefinition((int)aDefaultPublicH);
        Rules_DestroyPPBuffer();
        IO_CloseStringRouter((int)aDefaultPublicH);
      }
    }
    if ( (slotDescPtr[1] & 0x10) != 0 )
    {
      if ( (*slotDescPtr & 2) != 0 )
        paramPrefix = aAccessorSetterMultifieldParamPrefix;
      else
        paramPrefix = aAccessorSetterSinglefieldParamPrefix;
      sprintf_(v6, "%s put-%s (%svalue) (bind ?self:%s ?value))", className, slotName, paramPrefix, slotName);
      if ( IO_OpenStringSource((int)aDefaultPublicH, v9, 0) )
      {
        MessageHandler_ParseDefinition((int)aDefaultPublicH);
        Rules_DestroyPPBuffer();
        IO_CloseStringRouter((int)aDefaultPublicH);
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

  if ( strncmp_(paramName, aSelf_0) || *(_BYTE *)(v1 + 4) != 58 )
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
signed int  MessageHandler_ResolveSelfSlotGetRef(int varExpr, int theClass, int varName)
{
  int v6; // edx
  int v7; // ecx
  int slotDesc; // eax
  int v9; // ecx
  int tokenType; // [esp+0h] [ebp-1Ch]
  int tokenValue; // [esp+4h] [ebp-18h]

  if ( *(_WORD *)varExpr != 15 && *(_WORD *)varExpr != 16 )
    return 0;
  if ( strncmp_(varName, aSelf_0) )
    return 0;
  if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(varExpr + 2) + 16) + 4) != 58 )
    return 0;
  IO_OpenStringSource((int)aHndVar, (const char *)(*(_DWORD *)(*(_DWORD *)(varExpr + 2) + 16) + 5), 0);
  Rules_GetPPBufferStatus();
  Rules_SetPPBufferStatus(0);
  Parser_NextToken((int)aHndVar, v6);
  Rules_SetPPBufferStatus(v7);
  IO_CloseStringRouter((int)aHndVar);
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
  int v4; // ecx
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

  if ( !strcmp_(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(bindExpr + 6) + 2) + 16), aSelf_0) )
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
             tokenType != 102) )
  {
    valueExprChain = *(int **)(*(_DWORD *)(bindExpr + 6) + 10);
    slotDesc = MessageHandler_BuildSlotAccessNode(theClass, tokenType, 1, tokenValue, valueExprChain);
    if ( slotDesc )
    {
      AST_NewSlotReferenceNode(59, v12, slotDesc);
      *(_DWORD *)(*(_DWORD *)(bindExpr + 6) + 10) = 0;
      AST_Free(*(_DWORD *)(bindExpr + 6));
      result = 1;
      *(_DWORD *)(bindExpr + 6) = valueExprChain;
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
      Rules_PrintErrorID((int)aMsgpsr, 6, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoSuchSlot_0, v12);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(slotSymbol + 16), v13);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInClass_1, v14);
      classNameStr = Rules_GetConstructNameString(theClass);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], classNameStr, v16);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFor_selfRefere, v17);
      return 0;
    }
    else
    {
      slotDesc = *(_DWORD *)(4 * slotIndex + *(_DWORD *)(theClass + 56));
      if ( (*(_BYTE *)(slotDesc + 1) & 4) != 0 || theClass == *(_DWORD *)(slotDesc + 4) )
      {
        if ( !v7 )
          return slotDesc;
        if ( (*(_BYTE *)slotDesc & 0x10) != 0 && (*(_BYTE *)slotDesc & 0x20) == 0 )
        {
          MessageHandler_ReportSlotWriteAccessDenied(*(_DWORD *)(slotSymbol + 16), 0);
          return 0;
        }
        else
        {
          if ( !Rules_StaticConstraintCheckingEnabled() )
            return slotDesc;
          violationCode = Rules_CheckFieldExprListAgainstConstraint(writeExpression, *(_DWORD *)(slotDesc + 20));
          if ( !violationCode )
            return slotDesc;
          Rules_PrintErrorID((int)aCstrnchk_2, 1, 0);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpressionFor, (int)aDirectSlotWrit);
          Instance_PrintSlotErrorContext((int)g_IO_LogicalNameTable_WError[0], slotDesc, v18, 0);
          Rules_PrintConstraintViolationMessage(0, 0, 0, 0, 0, 0, violationCode, *(_DWORD *)(slotDesc + 20), 0);
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
int  AST_NewSlotReferenceNode(__int16 refType, int theExpr, int slotDesc)
{
  _WORD *v4; // ecx
  int result; // eax
  int v6; // ecx
  __int16 handlerSlotRef; // [esp+0h] [ebp-10h] BYREF
  int slotID; // [esp+2h] [ebp-Eh]
  int savedExpr; // [esp+Ch] [ebp-4h]

  savedExpr = theExpr;
  Mem_AllocArray(&handlerSlotRef, 6);
  handlerSlotRef = *(_WORD *)(*(_DWORD *)(slotDesc + 4) + 24);
  slotID = *(_DWORD *)(*(_DWORD *)(slotDesc + 8) + 8);
  *v4 = refType;
  result = Rules_AddBitmapValue(&handlerSlotRef, 6);
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
int  Rules_DefinstancesBloadModuleReference(int moduleIndex)
{
  return 12 * moduleIndex + g_DefinstancesBloadModuleRefArray;
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
__int16  Rules_MarkDefinstancesExpressionUsage(_DWORD *theDefinstances)
{
  int bsaveIndex; // edx
  int v2; // ecx
  int v3; // ecx

  bsaveIndex = g_Definstances_Count++;
  AST_MarkNodeFieldBound(theDefinstances, bsaveIndex);
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
__int16 * Rules_BsaveWriteDefinstancesExpression(int theDefinstances, int filePtr)
{
  return Rules_BsaveWriteExpression(*(__int16 **)(theDefinstances + 24), filePtr);
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
      moduleItemRecord = Module_FindItemByName((int)aDefinstances_0);
      theModuleItem = (_DWORD *)Module_GetItem(v4, *(_DWORD *)(moduleItemRecord + 4));
      Module_AssignBsaveItemHeaderIndices(itemHeaderBuffer, theModuleItem);
      Rules_BsaveWriteBlock(12, filePtr, itemHeaderBuffer);
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
const void * Rules_BsaveWriteDefinstancesRecord(int theDefinstances, int filePtr, int a3)
{
  int v4; // ecx
  _DWORD bsaveRecord[3]; // [esp-Ch] [ebp-18h] BYREF
  int expressionIndex; // [esp+0h] [ebp-Ch]
  int v8; // [esp+4h] [ebp-8h]

  v8 = a3;
  AST_ExtractPatternBindingInfo(bsaveRecord, theDefinstances);
  if ( *(_DWORD *)(v4 + 24) )
  {
    expressionIndex = g_ClipsExpressionNodeIndex;
    g_ClipsExpressionNodeIndex += AST_CountTreeNodes(*(_DWORD *)(v4 + 24));
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
int __thiscall Rules_BloadAllocateDefinstancesArrays(void *this)
{
  int result; // eax
  _DWORD spaceBuffer[4]; // [esp+0h] [ebp-10h] BYREF

  spaceBuffer[2] = this;
  result = Rules_BloadReadBlock((uintptr_t)spaceBuffer, 4u);
  if ( spaceBuffer[0] )
  {
    Rules_BloadReadBlock((uintptr_t)&g_Clips_DefinstancesCount, 4u);
    result = Rules_BloadReadBlock((uintptr_t)&g_Definstances_Count, 4u);
    if ( g_Clips_DefinstancesCount )
    {
      spaceBuffer[0] = 12 * g_Clips_DefinstancesCount;
      result = Mem_HeapAllocWithRetry((_DWORD *)(12 * g_Clips_DefinstancesCount));
      g_DefinstancesBloadModuleRefArray = result;
      if ( g_Definstances_Count )
      {
        spaceBuffer[0] = 28 * g_Definstances_Count;
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
  return Module_UpdateItemHeader(bsaveData, (_DWORD *)(12 * itemIndex + g_DefinstancesBloadModuleRefArray), g_ClipsDefinstancesBloadArray, 28);
}
// 51C70C: using guessed type int dword_51C70C;
// 54E914: using guessed type int dword_54E914;

//----- (004DFFC0) --------------------------------------------------------
int  Rules_BloadRefreshDefinstancesExpression(int bsaveBuffer, int itemIndex)
{
  _DWORD *theDefinstances; // edi
  int result; // eax

  theDefinstances = (_DWORD *)(g_ClipsDefinstancesBloadArray + 28 * itemIndex);
  Rules_BuildIndexedSlotDescriptor(bsaveBuffer, theDefinstances, g_DefinstancesBloadModuleRefArray, 12, 28, g_ClipsDefinstancesBloadArray);
  if ( *(_DWORD *)(bsaveBuffer + 12) == -1 )
  {
    result = 0;
    theDefinstances[5] = 0;
    theDefinstances[6] = 0;
  }
  else
  {
    result = g_ClipsPackedExpressionArray + 14 * *(_DWORD *)(bsaveBuffer + 12);
    theDefinstances[5] = 0;
    theDefinstances[6] = result;
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
        Rules_ReleaseSymbolReference((int *)(recordOffset + g_ClipsDefinstancesBloadArray), recordOffset);
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
int Rules_RegisterDefinstancesCodeGenerator()
{
  int result; // eax

  result = Rules_AddCodeGeneratorItem((int)aDefinstances_1, 0, 0, (int)Compiler_RegisterDefinstancesModuleAssigner, (int)Compiler_WriteDefinstancesToCode, 2);
  g_DefinstancesCodeGenItem = result;
  return result;
}
// 54E918: using guessed type int dword_54E918;

//----- (004E0120) --------------------------------------------------------
int  Rules_WriteDefinstancesModuleReference(int theFile, int count)
{
  return Output_WriteFormatted(count, **(_DWORD **)(g_DefinstancesCodeGenItem + 20), theFile, (int)aMihsSD_DD_7, **(_DWORD **)(g_DefinstancesCodeGenItem + 20));
}
// 54E918: using guessed type int dword_54E918;

//----- (004E0160) --------------------------------------------------------
signed int Compiler_RegisterDefinstancesModuleAssigner()
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
  Output_WriteFormatted(0, 1, imageID, (int)aIncludeDefins_, 1);
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
             (char)aDefinstances_m,
             **(const char ***)(g_DefinstancesCodeGenItem + 20),
             0,
             0);
      openedModuleFile = v7;
      if ( !v7 )
      {
        Compiler_CloseDefinstancesCodeFiles(0, definstancesFile, v8, maxIndices);
        return 0;
      }
      Compiler_WriteDefinstancesModuleHeaderToCode(v7, Enum, maxIndices);
      moduleFile = Rules_ConstructCodeFileClose(openedModuleFile, &moduleArrayCount, maxIndices, &moduleArrayVersion, 0, 0);
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
              (char)aDefinstances_3,
              *(const char **)(*(_DWORD *)(g_DefinstancesCodeGenItem + 20) + 4),
              0,
              0);
      openedDefinstancesFile = v11;
      if ( !v11 )
        break;
      Compiler_WriteDefinstancesConstructToCode(v11, theDefinstances, maxIndices, moduleCount);
      ++definstancesArrayCount;
      definstancesFile = Rules_ConstructCodeFileClose(openedDefinstancesFile, &definstancesArrayCount, maxIndices, &definstancesArrayVersion, 0, 0);
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

  Output_WriteFormatted(maxIndices, theModule, theFile, (int)asc_50E3D0, v9);
  Rules_WriteConstructModuleItemHeaderToCode(theFile, v4, v5, g_Clips_DefinstancesModuleItemIndex, *(_DWORD *)(*(_DWORD *)(g_DefinstancesCodeGenItem + 20) + 4));
  return Output_WriteFormatted(v7, v6, theFile, (int)asc_50E3D4, v10);
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
int  Compiler_WriteDefinstancesConstructToCode(int theFile, int theDefinstances, int maxIndices, int moduleCount)
{
  int *itemNames; // eax
  DWORD constructPrefix; // ebp
  signed int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  char v15; // [esp+0h] [ebp-Ch]
  char v16; // [esp+0h] [ebp-Ch]
  char v17; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(maxIndices, theDefinstances, theFile, (int)asc_50E3D0, v15);
  itemNames = *(int **)(g_DefinstancesCodeGenItem + 20);
  constructPrefix = *itemNames;
  Rules_WriteConstructHeaderToCode(theFile, theDefinstances, v8, moduleCount, *itemNames, itemNames[1]);
  Output_WriteFormatted(v10, v9, theFile, (int)a0_2, v16);
  Rules_ExpressionToCode(theFile, *(__int16 **)(theDefinstances + 24), v11, constructPrefix);
  return Output_WriteFormatted(v13, v12, theFile, (int)asc_50E3D4, v17);
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
char * Parser_ParseInstanceQueryNoAction(int top, int readSource)
{
  char *result; // eax
  char *insQuerySetVars; // esi
  int v5; // edx
  int v6; // ecx
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int queryInputToken[7]; // [esp+0h] [ebp-1Ch] BYREF

  queryInputToken[5] = readSource;
  result = (char *)Parser_ParseInstanceQueryRestrictions(top, queryInputToken);
  insQuerySetVars = result;
  if ( result )
  {
    Rules_IncrementIndentDepth(3);
    AST_Append(v6, v5);
    if ( Parser_ParseInstanceQueryTestExpression(v7, v7) )
    {
      Rules_DecrementIndentDepth(3);
      Parser_NextToken(v9, v8);
      if ( queryInputToken[0] == 101 )
      {
        Parser_ReplaceInstanceQuerySlotReferences(insQuerySetVars, *(_DWORD *)(top + 6), 0, 1);
        AST_Free((int)insQuerySetVars);
        return (char *)top;
      }
      else
      {
        Parser_ReportSyntaxError();
        AST_Free(top);
        AST_Free((int)insQuerySetVars);
        return 0;
      }
    }
    else
    {
      Rules_DecrementIndentDepth(3);
      AST_Free((int)insQuerySetVars);
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
char * Parser_ParseInstanceQueryAction(int top, int readSource)
{
  char *result; // eax
  char *insQuerySetVars; // esi
  int v5; // edx
  int v6; // ecx
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int v10; // ecx
  int v11; // edx
  int v12; // ecx
  int queryInputToken[7]; // [esp+0h] [ebp-1Ch] BYREF

  queryInputToken[5] = readSource;
  result = (char *)Parser_ParseInstanceQueryRestrictions(top, queryInputToken);
  insQuerySetVars = result;
  if ( result )
  {
    Rules_IncrementIndentDepth(3);
    AST_Append(v6, v5);
    if ( Parser_ParseInstanceQueryTestExpression(v7, v7) && (AST_Append(v9, v8), Parser_ParseInstanceQueryActionExpression(top, v10, (int)insQuerySetVars)) )
    {
      Rules_DecrementIndentDepth(3);
      Parser_NextToken(v12, v11);
      if ( queryInputToken[0] == 101 )
      {
        Parser_ReplaceInstanceQuerySlotReferences(insQuerySetVars, *(_DWORD *)(top + 6), 0, 1);
        Parser_ReplaceInstanceQuerySlotReferences(insQuerySetVars, *(_DWORD *)(*(_DWORD *)(top + 6) + 10), 0, 0);
        AST_Free((int)insQuerySetVars);
        return (char *)top;
      }
      else
      {
        Parser_ReportSyntaxError();
        AST_Free(top);
        AST_Free((int)insQuerySetVars);
        return 0;
      }
    }
    else
    {
      Rules_DecrementIndentDepth(3);
      AST_Free((int)insQuerySetVars);
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
int  Parser_ParseInstanceQueryRestrictions(int top, int *queryInputToken)
{
  int insQuerySetVars; // edi
  int v5; // edx
  int v6; // ecx
  int v7; // ecx
  int initialTokenType; // ebx
  int v10; // ecx
  int varScan; // eax
  signed int memberVarNode; // eax
  int v13; // ecx
  signed int classExp; // eax
  signed int lastClassExp; // ebx
  int v16; // ecx
  signed int nextClassExp; // eax
  signed int delimiterExp; // eax
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // edx
  signed int v24; // edx
  int parseError; // [esp+0h] [ebp-20h] BYREF
  signed int lastOne; // [esp+4h] [ebp-1Ch]
  signed int lastInsQuerySetVars; // [esp+8h] [ebp-18h]
  int classExpChain; // [esp+Ch] [ebp-14h]

  insQuerySetVars = 0;
  lastInsQuerySetVars = 0;
  parseError = 0;
  IO_OutWriteToken(asc_50E3F8);
  classExpChain = 0;
  Parser_NextToken(v6, v5);
  initialTokenType = *queryInputToken;
  lastOne = 0;
  if ( initialTokenType == 100 && (Parser_NextToken(v7, (int)queryInputToken), *queryInputToken == 100) )
  {
    while ( *queryInputToken == 100 )
    {
      Parser_NextToken(v10, (int)queryInputToken);
      if ( *queryInputToken != 15 )
        goto LABEL_2;
      varScan = insQuerySetVars;
      if ( insQuerySetVars )
      {
        while ( *(_DWORD *)(varScan + 2) != queryInputToken[1] )
        {
          varScan = *(_DWORD *)(varScan + 10);
          if ( !varScan )
            goto LABEL_12;
        }
        Rules_PrintErrorID((int)aInsqypsr, 1, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDuplicateIns_0, v20);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(**(_DWORD **)(top + 2) + 16), v21);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__27, v22);
        goto LABEL_3;
      }
LABEL_12:
      memberVarNode = AST_NewNode(15, queryInputToken[1]);
      if ( insQuerySetVars )
        *(_DWORD *)(lastInsQuerySetVars + 10) = memberVarNode;
      else
        insQuerySetVars = memberVarNode;
      lastInsQuerySetVars = memberVarNode;
      IO_OutWriteToken(asc_50E3F8);
      classExp = Parser_ParseArgument(v13, &parseError, v13);
      lastClassExp = classExp;
      classExpChain = classExp;
      if ( parseError )
        goto LABEL_3;
      if ( !classExp )
        goto LABEL_2;
      if ( !Rules_ReplaceClassNameWithClassReference(classExp) )
        goto LABEL_3;
      IO_OutWriteToken(asc_50E3F8);
      while ( 1 )
      {
        nextClassExp = Parser_ParseArgument(v16, &parseError, v16);
        if ( !nextClassExp )
          break;
        if ( !Rules_ReplaceClassNameWithClassReference(nextClassExp) )
          goto LABEL_3;
        *(_DWORD *)(lastClassExp + 10) = v23;
        IO_OutWriteToken(asc_50E3F8);
        lastClassExp = v24;
      }
      if ( parseError )
        goto LABEL_3;
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(asc_50E444);
      delimiterExp = AST_NewNode(2, g_InternedSym_Qds);
      *(_DWORD *)(lastClassExp + 10) = delimiterExp;
      if ( *(_DWORD *)(top + 6) )
        *(_DWORD *)(lastOne + 10) = classExpChain;
      else
        *(_DWORD *)(top + 6) = classExpChain;
      lastOne = delimiterExp;
      IO_OutWriteToken(asc_50E3F8);
      Parser_NextToken(v19, (int)queryInputToken);
      classExpChain = 0;
    }
    if ( *queryInputToken != 101 )
      goto LABEL_2;
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken(asc_50E444);
    return insQuerySetVars;
  }
  else
  {
LABEL_2:
    Parser_ReportSyntaxError();
LABEL_3:
    AST_Free(classExpChain);
    AST_Free(top);
    AST_Free(insQuerySetVars);
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
signed int  Rules_ReplaceClassNameWithClassReference(int theExp)
{
  int *theDefclass; // eax
  int v4; // ecx

  if ( *(_WORD *)theExp != 2 )
    return 1;
  theDefclass = Class_LookupByQualifiedName(*(_BYTE **)(*(_DWORD *)(theExp + 2) + 16));
  if ( theDefclass )
  {
    *(_WORD *)theExp = 57;
    *(_DWORD *)(theExp + 2) = theDefclass;
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
signed int __fastcall Parser_ParseInstanceQueryTestExpression(int top, int readSource)
{
  int oldBindList; // ebx
  _DWORD *v4; // edx
  int v5; // ecx
  signed int queryTest; // eax
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v14; // ecx

  oldBindList = Parser_GetLoopContextStack();
  Parser_SetLoopContextStack(0);
  queryTest = Parser_ParseArgument(readSource, v4, v5);
  if ( queryTest )
  {
    *(_DWORD *)(queryTest + 10) = *(_DWORD *)(v7 + 6);
    *(_DWORD *)(v7 + 6) = queryTest;
    if ( Parser_LoopContextStackIsEmpty() )
    {
      Parser_SetLoopContextStack(oldBindList);
      return 1;
    }
    else
    {
      Parser_FreeLoopContextStack();
      Parser_SetLoopContextStack(oldBindList);
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
    Parser_SetLoopContextStack(oldBindList);
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
signed int  Parser_ParseInstanceQueryActionExpression(int top, int readSource, int insQuerySetVars)
{
  int oldBindList; // edi
  int v6; // ecx
  signed int queryAction; // eax
  int v8; // ecx
  _DWORD *currentBind; // edx
  _DWORD *prevBind; // eax
  int setVar; // ecx
  int v13; // edx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  _DWORD parseError[5]; // [esp+0h] [ebp-14h] BYREF

  parseError[0] = 0;
  oldBindList = Parser_GetLoopContextStack();
  Parser_SetLoopContextStack(0);
  g_ParserBreakContextFlag = 1;
  g_ClipsParseReturnContext = *(_DWORD *)g_ClipsParseContextSaveStack;
  queryAction = Parser_ParseArgument(readSource, parseError, v6);
  g_ParserBreakContextFlag = 0;
  if ( parseError[0] == 1 )
  {
    Parser_SetLoopContextStack(v8);
    AST_Free(top);
    return 0;
  }
  else if ( queryAction )
  {
    *(_DWORD *)(queryAction + 10) = *(_DWORD *)(*(_DWORD *)(top + 6) + 10);
    *(_DWORD *)(*(_DWORD *)(top + 6) + 10) = queryAction;
    currentBind = (_DWORD *)Parser_GetLoopContextStack();
    prevBind = 0;
    if ( currentBind )
    {
      while ( 1 )
      {
        setVar = insQuerySetVars;
        if ( insQuerySetVars )
          break;
LABEL_7:
        prevBind = currentBind;
        currentBind = (_DWORD *)currentBind[2];
        if ( !currentBind )
          goto LABEL_8;
      }
      while ( *(_DWORD *)(setVar + 2) != *currentBind )
      {
        setVar = *(_DWORD *)(setVar + 10);
        if ( !setVar )
          goto LABEL_7;
      }
      Parser_FreeLoopContextStack();
      Parser_SetLoopContextStack(oldBindList);
      Rules_PrintErrorID((int)aInsqypsr, v13, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotRebindIn, v14);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(*(_DWORD *)(v15 + 2) + 16), v15);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInFunction_3, v16);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(**(_DWORD **)(top + 2) + 16), v17);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__27, v18);
      AST_Free(top);
      return 0;
    }
    else
    {
LABEL_8:
      if ( prevBind )
        prevBind[2] = oldBindList;
      else
        Parser_SetLoopContextStack(oldBindList);
      return 1;
    }
  }
  else
  {
    Parser_SetLoopContextStack(v8);
    Parser_ReportSyntaxError();
    AST_Free(top);
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
char * Parser_ReplaceInstanceQuerySlotReferences(char *varList, int bodyExp, signed int ndepth, int sdirect)
{
  char *result; // eax
  int v8; // ecx
  int v9; // edx
  int i; // ecx
  int *depthValue; // eax
  signed int depthExpr; // ebx
  signed int v13; // ecx
  int *posnValue; // eax
  signed int childDepth; // ecx
  int childSdirect; // ebx
  signed int nestedDepth; // [esp+0h] [ebp-1Ch]
  int **Symbol; // [esp+4h] [ebp-18h]
  int querySlotSymbol; // [esp+8h] [ebp-14h]

  Symbol = Rules_MakeSymbol(aQueryInstanc_0);
  result = (char *)Rules_MakeSymbol(aQueryInstanc_1);
  querySlotSymbol = (int)result;
  if ( v9 )
  {
    result = (char *)(v8 + 1);
    nestedDepth = v8 + 1;
    do
    {
      if ( *(_WORD *)bodyExp == 15 )
      {
        result = varList;
        for ( i = 0; result; ++i )
        {
          if ( *(_DWORD *)(result + 2) == *(_DWORD *)(bodyExp + 2) )
            break;
          result = *(char **)(result + 10);
        }
        if ( result )
        {
          *(_DWORD *)(bodyExp + 2) = Symbol;
          *(_WORD *)bodyExp = 10;
          depthValue = Rules_AddIntegerValue(ndepth);
          depthExpr = AST_NewNode(1, (int)depthValue);
          posnValue = Rules_AddIntegerValue(v13);
          result = (char *)AST_NewNode(1, (int)posnValue);
          *(_DWORD *)(depthExpr + 10) = result;
          *(_DWORD *)(bodyExp + 6) = depthExpr;
        }
        else if ( sdirect == 1 )
        {
          result = (char *)Parser_ResolveInstanceQuerySlotReference((int)varList, bodyExp, ndepth, querySlotSymbol);
        }
      }
      if ( *(_DWORD *)(bodyExp + 6) )
      {
        if ( Rules_IsInstanceSetQueryFunctionCall(bodyExp) )
        {
          childDepth = nestedDepth;
          childSdirect = sdirect;
        }
        else
        {
          childSdirect = sdirect;
          childDepth = ndepth;
        }
        result = (char *)Parser_ReplaceInstanceQuerySlotReferences((int)varList, *(_DWORD *)(bodyExp + 6), childDepth, childSdirect);
      }
      bodyExp = *(_DWORD *)(bodyExp + 10);
    }
    while ( bodyExp );
  }
  return result;
}
// 4E0AFE: variable 'v9' is possibly undefined
// 4E0B04: variable 'v8' is possibly undefined
// 4E0B58: variable 'v13' is possibly undefined

//----- (004E0BD0) --------------------------------------------------------
const char * Parser_ResolveInstanceQuerySlotReference(int varList, int theExp, signed int ndepth, int querySlotSymbol)
{
  const char *varName; // ebp
  const char *result; // eax
  unsigned int nameLen; // kr04_4
  int colonIndex; // esi
  int varNode; // ecx
  signed int j; // edi
  int v10; // edx
  int v11; // ecx
  int *depthValue; // eax
  int *posnValue; // eax
  __int16 tokenType; // [esp+0h] [ebp-2Ch]
  int tokenValue; // [esp+4h] [ebp-28h]
  const char *i; // [esp+1Ch] [ebp-10h]

  varName = *(const char **)(*(_DWORD *)(theExp + 2) + 16);
  result = 0;
  nameLen = strlen(varName) + 1;
  if ( (int)(nameLen - 1) >= 3 )
  {
    colonIndex = nameLen - 3;
    if ( (int)(nameLen - 3) >= 1 )
    {
      for ( i = &varName[colonIndex]; ; --i )
      {
        result = i;
        if ( *i == 58 )
        {
          result = (const char *)(colonIndex >= 1);
          if ( colonIndex >= 1 )
          {
            varNode = varList;
            for ( j = 0; varNode; ++j )
            {
              result = (const char *)(strncmp_(varNode, varName) != 0);
              if ( !result )
                break;
              varNode = *(_DWORD *)(varNode + 10);
            }
            if ( varNode )
              break;
          }
        }
        if ( --colonIndex < 1 )
          return result;
      }
      IO_OpenStringSource((int)aQueryVar, &varName[colonIndex + 1], 0);
      Rules_GetPPBufferStatus();
      Rules_SetPPBufferStatus(0);
      Parser_NextToken((int)aQueryVar, v10);
      Rules_SetPPBufferStatus(v11);
      IO_CloseStringRouter((int)aQueryVar);
      *(_WORD *)theExp = 10;
      *(_DWORD *)(theExp + 2) = querySlotSymbol;
      depthValue = Rules_AddIntegerValue(ndepth);
      *(_DWORD *)(theExp + 6) = AST_NewNode(1, (int)depthValue);
      posnValue = Rules_AddIntegerValue(j);
      *(_DWORD *)(*(_DWORD *)(theExp + 6) + 10) = AST_NewNode(1, (int)posnValue);
      result = (const char *)AST_NewNode(tokenType, tokenValue);
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(theExp + 6) + 10) + 10) = result;
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
BOOL  Rules_IsInstanceSetQueryFunctionCall(int theExp)
{
  int *( *theFunction)(int, double); // eax
  BOOL result; // eax

  result = 0;
  if ( *(_WORD *)theExp == 10 )
  {
    theFunction = *(int *( **)(int, double))(*(_DWORD *)(theExp + 2) + 9);
    if ( theFunction == InstanceQuery_AnyInstancep
      || (char *)theFunction == (char *)InstanceQuery_FindInstance
      || (char *)theFunction == (char *)InstanceQuery_FindAllInstances
      || (char *)theFunction == (char *)InstanceQuery_DoForInstance
      || (char *)theFunction == (char *)InstanceQuery_DoForAllInstances
      || (char *)theFunction == (char *)InstanceQuery_DelayedDoForAllInstances )
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
int  Compiler_WriteObjectPatternSecondaryIndexRef(int theNode, int theFile, int imageID)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( theNode )
    return Output_WriteFormatted(
             imageID,
             *(_DWORD *)(*(_DWORD *)(g_ObjectPatternNetworkCodeGenItem + 20) + 4),
             theFile,
             (int)aSD_DD_11,
             *(_DWORD *)(*(_DWORD *)(g_ObjectPatternNetworkCodeGenItem + 20) + 4));
  else
    return Output_WriteFormatted(imageID, theFile, theFile, (int)aNull_33, v4);
}
// 4E0DA0: variable 'v4' is possibly undefined
// 54E91C: using guessed type int dword_54E91C;

//----- (004E0DF0) --------------------------------------------------------
int Compiler_AssignObjectPatternAndRuleCodeIndices()
{
  _DWORD *patternNode; // eax
  int i; // ecx
  int v2; // ecx
  int result; // eax
  int j; // edx

  patternNode = (_DWORD *)Rules_GetObjectPatternNetworkRoot();
  for ( i = 0; patternNode; i = v2 + 1 )
  {
    patternNode[9] = i;
    patternNode = Rules_GetNextObjectPatternNode(patternNode);
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
int  Compiler_WriteObjectPatternNetworkSetupCode(int theFile, int maxIndices)
{
  int v3; // edx
  int v4; // ecx
  int alphaListHead; // eax
  int v6; // ecx
  int v8; // edx
  int v9; // ecx
  char v10; // [esp+0h] [ebp-Ch]
  char v11; // [esp+0h] [ebp-Ch]

  if ( Rules_GetObjectPatternNetworkRoot() )
  {
    Rules_GetObjectPatternNetworkRoot();
    alphaListHead = Rules_GetReactiveRuleList();
    Output_WriteFormatted(*(_DWORD *)(alphaListHead + 40), *(_DWORD *)(alphaListHead + 40), theFile, (int)aSetobjectnetwo, **(_DWORD **)(g_ObjectPatternNetworkCodeGenItem + 20));
    return Output_WriteFormatted(
             *(_DWORD *)(*(_DWORD *)(g_ObjectPatternNetworkCodeGenItem + 20) + 4),
             v6 % maxIndices,
             theFile,
             (int)aSetobjectnet_0,
             *(_DWORD *)(*(_DWORD *)(g_ObjectPatternNetworkCodeGenItem + 20) + 4));
  }
  else
  {
    Output_WriteFormatted(v4, v3, theFile, (int)aSetobjectnet_1, v10);
    return Output_WriteFormatted(v9, v8, theFile, (int)aSetobjectnet_2, v11);
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
int  Compiler_WriteObjectPatternsAndRulesToCode(const char *fileName, int a2, DWORD fileID, int headerFile, int maxIndices)
{
  int result; // eax

  result = Compiler_WriteObjectPatternNodesToCode(fileName, a2, fileID, headerFile, maxIndices, 1);
  if ( result )
  {
    result = Compiler_WriteReactiveRulesToCode(fileName, a2, fileID, headerFile, maxIndices, result);
    if ( result )
      return 1;
  }
  return result;
}

//----- (004E0F80) --------------------------------------------------------
int  Compiler_WriteObjectPatternValueIndexRef(int patternNode, int outFile, int maxIndices)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( patternNode )
    return Output_WriteFormatted(maxIndices, **(_DWORD **)(g_ObjectPatternNetworkCodeGenItem + 20), outFile, (int)aSD_DD_11, **(_DWORD **)(g_ObjectPatternNetworkCodeGenItem + 20));
  else
    return Output_WriteFormatted(maxIndices, outFile, outFile, (int)aNull_33, v4);
}
// 4E0F90: variable 'v4' is possibly undefined
// 54E91C: using guessed type int dword_54E91C;

//----- (004E0FD0) --------------------------------------------------------
int  Compiler_WriteObjectPatternNodesToCode(const char *fileName, char a2, DWORD fileID, int headerFile, int maxIndices, int version)
{
  int v7; // edx
  int v8; // ecx
  int result; // eax
  int v10; // edx
  int patternFile; // esi
  int rootNode; // eax
  int v13; // edx
  int v14; // ecx
  _DWORD *patternNode; // edi
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
  _DWORD *nextNode; // eax
  int nextIndexInFile; // edx
  int v30; // ecx
  int nextVersion; // eax
  int v33; // [esp+0h] [ebp-24h]
  char v34; // [esp+0h] [ebp-24h]
  char v35; // [esp+0h] [ebp-24h]
  char v36; // [esp+0h] [ebp-24h]
  char v37; // [esp+0h] [ebp-24h]
  char v38; // [esp+0h] [ebp-24h]
  char v39; // [esp+0h] [ebp-24h]
  int newHeader; // [esp+Ch] [ebp-18h]
  int indexInFile; // [esp+10h] [ebp-14h]
  int arrayVersion; // [esp+14h] [ebp-10h]

  if ( !Rules_GetObjectPatternNetworkRoot() )
    return 1;
  Output_WriteFormatted(v8, v7, headerFile, (int)aIncludeObjrt_0, a2);
  result = Rules_OpenConstructCodeFile(fileName, v10, version, fileID);
  patternFile = result;
  if ( result )
  {
    rootNode = Rules_GetObjectPatternNetworkRoot();
    v14 = 1;
    patternNode = (_DWORD *)rootNode;
    newHeader = 1;
    arrayVersion = 1;
    indexInFile = 1;
    if ( rootNode )
    {
      do
      {
        if ( newHeader )
        {
          Output_WriteFormatted(**(_DWORD **)(g_ObjectPatternNetworkCodeGenItem + 20), arrayVersion, patternFile, (int)aObject_pattern, **(_DWORD **)(g_ObjectPatternNetworkCodeGenItem + 20));
          Output_WriteFormatted(headerFile, **(_DWORD **)(g_ObjectPatternNetworkCodeGenItem + 20), headerFile, (int)aExternObject_p, **(_DWORD **)(g_ObjectPatternNetworkCodeGenItem + 20));
          newHeader = 0;
        }
        Output_WriteFormatted(v14, v13, patternFile, (int)a0UUUU0lU, (*patternNode & 2) != 0);
        Rules_WriteExpressionRefToCode(patternFile, (__int16 *)patternNode[3], maxIndices, fileID);
        Output_WriteFormatted(v16, patternFile, patternFile, (int)asc_50E654, v33);
        Compiler_WriteObjectPatternValueIndexRef(patternNode[4], v17, maxIndices);
        Output_WriteFormatted(v18, patternFile, patternFile, (int)asc_50E654, v34);
        Compiler_WriteObjectPatternValueIndexRef(patternNode[5], v19, maxIndices);
        Output_WriteFormatted(v20, patternFile, patternFile, (int)asc_50E654, v35);
        Compiler_WriteObjectPatternValueIndexRef(patternNode[6], v21, maxIndices);
        Output_WriteFormatted(v22, patternFile, patternFile, (int)asc_50E654, v36);
        Compiler_WriteObjectPatternValueIndexRef(patternNode[7], v23, maxIndices);
        Output_WriteFormatted(v24, patternFile, patternFile, (int)asc_50E654, v37);
        Compiler_WriteObjectPatternSecondaryIndexRef(patternNode[8], v25, maxIndices);
        Output_WriteFormatted(v27, v26, patternFile, (int)a0l_0, v38);
        nextNode = Rules_GetNextObjectPatternNode(patternNode);
        nextIndexInFile = indexInFile + 1;
        patternNode = nextNode;
        indexInFile = nextIndexInFile;
        if ( nextIndexInFile <= maxIndices && nextNode )
        {
          Output_WriteFormatted(maxIndices, nextIndexInFile, patternFile, (int)asc_50E664, v39);
        }
        else
        {
          Output_WriteFormatted(maxIndices, nextIndexInFile, patternFile, (int)asc_50E660, v39);
          fclose_(v30);
          indexInFile = 1;
          nextVersion = version + 1;
          v13 = arrayVersion + 1;
          ++version;
          ++arrayVersion;
          if ( patternNode )
          {
            result = Rules_OpenConstructCodeFile(fileName, v33, nextVersion, fileID);
            patternFile = result;
            if ( !result )
              return result;
            newHeader = 1;
          }
        }
      }
      while ( patternNode );
    }
    return version;
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
int  Compiler_WriteReactiveRulesToCode(const char *fileName, int a2, DWORD fileID, int headerFile, int maxIndices, int version)
{
  int v7; // edx
  int result; // eax
  int alphaFile; // esi
  int v10; // ecx
  int *alphaNode; // edi
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
  int nextVersion; // ebx
  int savedHeaderFile; // [esp+0h] [ebp-24h]
  char v30; // [esp+0h] [ebp-24h]
  char v31; // [esp+0h] [ebp-24h]
  char v32; // [esp+0h] [ebp-24h]
  char v33; // [esp+0h] [ebp-24h]
  char v34; // [esp+0h] [ebp-24h]
  char v35; // [esp+0h] [ebp-24h]
  char v36; // [esp+0h] [ebp-24h]
  int newHeader; // [esp+Ch] [ebp-18h]
  int arrayVersion; // [esp+10h] [ebp-14h]
  int indexInFile; // [esp+14h] [ebp-10h]

  savedHeaderFile = headerFile;
  if ( !Rules_GetReactiveRuleList() )
    return version;
  result = Rules_OpenConstructCodeFile(fileName, v7, version, fileID);
  alphaFile = result;
  if ( result )
  {
    alphaNode = (int *)Rules_GetReactiveRuleList();
    newHeader = 1;
    arrayVersion = 1;
    indexInFile = 1;
    if ( !alphaNode )
      return version;
    do
    {
      if ( newHeader )
      {
        Output_WriteFormatted(
          *(_DWORD *)(*(_DWORD *)(g_ObjectPatternNetworkCodeGenItem + 20) + 4),
          arrayVersion,
          alphaFile,
          (int)aObject_alpha_n,
          *(_DWORD *)(*(_DWORD *)(g_ObjectPatternNetworkCodeGenItem + 20) + 4));
        Output_WriteFormatted(
          savedHeaderFile,
          *(_DWORD *)(*(_DWORD *)(g_ObjectPatternNetworkCodeGenItem + 20) + 4),
          savedHeaderFile,
          (int)aExternObject_a,
          *(_DWORD *)(*(_DWORD *)(g_ObjectPatternNetworkCodeGenItem + 20) + 4));
        newHeader = 0;
      }
      Output_WriteFormatted(v10, (int)alphaNode, alphaFile, (int)asc_50E6B4, savedHeaderFile);
      Rules_PrintPatternNetworkNodeTrace(alphaFile, v12, maxIndices);
      Output_WriteFormatted(v14, v13, alphaFile, (int)a0l_1, v30);
      Compiler_WriteBitMapReference(alphaFile, alphaNode[5], v15);
      Output_WriteFormatted(v17, v16, alphaFile, (int)asc_50E654, v31);
      Compiler_WriteBitMapReference(alphaFile, alphaNode[6], v18);
      Output_WriteFormatted(v19, alphaFile, alphaFile, (int)asc_50E654, v32);
      Compiler_WriteObjectPatternValueIndexRef(alphaNode[7], v20, maxIndices);
      Output_WriteFormatted(v21, alphaFile, alphaFile, (int)asc_50E654, v33);
      Compiler_WriteObjectPatternSecondaryIndexRef(alphaNode[8], v22, maxIndices);
      Output_WriteFormatted(v23, alphaFile, alphaFile, (int)asc_50E654, v34);
      Compiler_WriteObjectPatternSecondaryIndexRef(alphaNode[9], v24, maxIndices);
      Output_WriteFormatted(v26, v25, alphaFile, (int)a0l_0, v35);
      alphaNode = (int *)alphaNode[9];
      if ( ++indexInFile <= maxIndices && alphaNode )
      {
        Output_WriteFormatted(v27, maxIndices, alphaFile, (int)asc_50E664, v36);
      }
      else
      {
        Output_WriteFormatted(v27, maxIndices, alphaFile, (int)asc_50E660, v36);
        fclose_(1);
        indexInFile = v10;
        nextVersion = v10 + version;
        version += v10;
        arrayVersion += v10;
        if ( alphaNode )
        {
          result = Rules_OpenConstructCodeFile(fileName, a2, nextVersion, fileID);
          alphaFile = result;
          if ( !result )
            return result;
          newHeader = 1;
        }
      }
    }
    while ( alphaNode );
    return version;
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
int __fastcall Rules_BuildSlotBoundTestNode(int a1, int theNode)
{
  return Rules_BuildSlotConstraintBitmapTestNode(1, theNode);
}

//----- (004E1430) --------------------------------------------------------
int  Rules_BuildSlotBoundTestExpression(int theNode)
{
  int v2; // ecx

  AST_NewNode(0, 0);
  Rules_BuildSlotConstraintBitmapTestNode(1, theNode);
  return v2;
}
// 4E144C: variable 'v2' is possibly undefined

//----- (004E1460) --------------------------------------------------------
signed int  Rules_BuildSlotRangeTestNode(int selfNode, int referringNode)
{
  return Rules_BuildDualSlotConstraintBitmapTestNode(1, selfNode, referringNode);
}

//----- (004E1480) --------------------------------------------------------
signed int Rules_BuildMultifieldIndexTestNode()
{
  int slotNode; // ecx
  int bitmapFlags; // esi
  int bitmapValue; // eax
  signed int lengthTestNode; // edi
  _DWORD *v4; // ecx
  int eqBitmapValue; // eax
  signed int eqTestNode; // edi
  int *v8; // ecx
  int savedNodeType; // ebp
  _DWORD *v10; // ecx
  int nodeValue; // edx
  unsigned int fieldCountBits; // eax
  _DWORD bitmapBuffer[7]; // [esp+0h] [ebp-1Ch] BYREF

  Mem_AllocArray(bitmapBuffer, 4);
  if ( (*(_BYTE *)(slotNode + 8) & 1) != 0 )
    BYTE1(bitmapBuffer[0]) |= 1u;
  else
    LOBYTE(bitmapBuffer[0]) |= 0x80u;
  if ( (*(_BYTE *)(slotNode + 9) & 0x40) != 0 && (*(_WORD *)(slotNode + 10) & 0x1FC0) != 0 && (*(_DWORD *)(slotNode + 8) & 0x3F8000) != 0
    || *(_DWORD *)(slotNode + 40) < 2u )
  {
    BYTE1(bitmapBuffer[0]) |= 2u;
    eqBitmapValue = Rules_AddBitmapValue(bitmapBuffer, 4);
    eqTestNode = AST_NewNode(50, eqBitmapValue);
    *(_DWORD *)(eqTestNode + 6) = AST_NewNode(0, 0);
    savedNodeType = *v8;
    *v8 = 15;
    Rules_BuildSlotConstraintBitmapTestNode(0, (int)v8);
    nodeValue = v10[1];
    *v10 = savedNodeType;
    *(_DWORD *)(*(_DWORD *)(eqTestNode + 6) + 10) = AST_NewNode(savedNodeType, nodeValue);
    return eqTestNode;
  }
  else
  {
    bitmapFlags = bitmapBuffer[0] | 0x400;
    if ( (*(_BYTE *)(slotNode + 9) & 0x40) != 0 )
    {
      if ( (*(_DWORD *)(slotNode + 8) & 0x3F8000) != 0 )
      {
        fieldCountBits = *(_DWORD *)(slotNode + 12) << 18;
        LOBYTE(bitmapBuffer[0]) &= 0x80u;
        bitmapBuffer[0] |= fieldCountBits >> 25;
      }
      else
      {
        bitmapBuffer[0] |= 0x400u;
        LOWORD(bitmapFlags) = bitmapFlags & 0xFF80;
        bitmapBuffer[0] = *(_DWORD *)(slotNode + 12) & 0x7F | bitmapFlags;
      }
    }
    else
    {
      bitmapBuffer[0] |= 0x400u;
    }
    bitmapValue = Rules_AddBitmapValue(bitmapBuffer, 4);
    lengthTestNode = AST_NewNode(50, bitmapValue);
    *(_DWORD *)(lengthTestNode + 6) = AST_NewNode(*v4, v4[1]);
    return lengthTestNode;
  }
}
// 4E14AC: simplified comparisons for 'ebx.4': ==0 || ==1 became <2u
// 4E1497: variable 'v0' is possibly undefined
// 4E14E8: variable 'v4' is possibly undefined
// 4E154B: variable 'v8' is possibly undefined
// 4E155F: variable 'v10' is possibly undefined

//----- (004E15D0) --------------------------------------------------------
int __fastcall mblen_(int theNode, int a2)
{
  (void)a2;
  return Rules_BuildSlotConstraintBitmapTestNode(0, theNode);
}

//----- (004E15E0) --------------------------------------------------------
int  Rules_BuildSlotUnboundTestExpression(int theNode)
{
  int v2; // ecx

  AST_NewNode(0, 0);
  Rules_BuildSlotConstraintBitmapTestNode(0, theNode);
  return v2;
}
// 4E15F9: variable 'v2' is possibly undefined

//----- (004E1600) --------------------------------------------------------
int __fastcall mblen__0(int selfNode, int referringNode)
{
  return Rules_BuildDualSlotConstraintBitmapTestNode(0, selfNode, referringNode);
}

//----- (004E1610) --------------------------------------------------------
_DWORD * Rules_AppendFieldCardinalityBitmapTest(_DWORD *result)
{
  int slotNode; // ecx
  int fieldCount; // eax
  int bitmapValue; // eax
  _DWORD *testNode; // eax
  int v5; // ecx
  int v6; // ecx
  unsigned int multifieldCount; // eax
  _DWORD bitmapBuffer[4]; // [esp+0h] [ebp-10h] BYREF

  if ( (result[3] & 0x3F80) != 0 || *result == 15 || *result == 17 )
  {
    Mem_AllocArray(bitmapBuffer, 4);
    if ( *(_DWORD *)slotNode == 16 || *(_DWORD *)slotNode == 18 || (*(_WORD *)(slotNode + 10) & 0x1FC0) != 0 )
      BYTE1(bitmapBuffer[0]) &= ~0x80u;
    else
      BYTE1(bitmapBuffer[0]) |= 0x80u;
    if ( *(_DWORD *)slotNode == 15 || *(_DWORD *)slotNode == 17 )
    {
      fieldCount = *(_DWORD *)(slotNode + 12) << 18 >> 25;
      LOWORD(bitmapBuffer[0]) &= 0x8000u;
      bitmapBuffer[0] |= ((_WORD)fieldCount + 1) & 0x7FFF;
    }
    else
    {
      multifieldCount = *(_DWORD *)(slotNode + 12) << 18;
      LOWORD(bitmapBuffer[0]) &= 0x8000u;
      bitmapBuffer[0] |= (multifieldCount >> 25) & 0x7FFF;
    }
    bitmapValue = Rules_AddBitmapValue(bitmapBuffer, 4);
    testNode = (_DWORD *)AST_NewNode(49, bitmapValue);
    result = AST_MergeFieldAccessNodes(testNode, *(_DWORD **)(v5 + 52));
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
  int bitmapValue; // eax
  _DWORD *lengthTestNode; // eax
  int v4; // ecx
  _DWORD *result; // eax
  int v6; // ecx
  _WORD matchLengthBitmap[4]; // [esp+0h] [ebp-Ch] BYREF
  int v8; // [esp+8h] [ebp-4h]

  v8 = a1;
  Mem_AllocArray(matchLengthBitmap, 4);
  HIBYTE(matchLengthBitmap[0]) |= 0x80u;
  matchLengthBitmap[0] &= 0x8000u;
  bitmapValue = Rules_AddBitmapValue(matchLengthBitmap, 4);
  lengthTestNode = (_DWORD *)AST_NewNode(49, bitmapValue);
  result = AST_MergeFieldAccessNodes(lengthTestNode, *(_DWORD **)(v4 + 52));
  *(_DWORD *)(v6 + 52) = result;
  return result;
}
// 4E173C: variable 'v4' is possibly undefined
// 4E1744: variable 'v6' is possibly undefined

//----- (004E1750) --------------------------------------------------------
int  Rules_BuildSlotConstraintBitmapTestNode(int joinTest, int theNode)
{
  __int16 *v3; // ecx
  int v4; // eax
  __int16 var1NodeType; // ax
  int result; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  __int16 var2NodeType; // ax
  int v13; // ecx
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  unsigned int matchVar1Bitmap; // [esp+0h] [ebp-20h] BYREF
  char v21; // [esp+4h] [ebp-1Ch]
  int matchVar2Bitmap; // [esp+8h] [ebp-18h] BYREF
  int v23; // [esp+Ch] [ebp-14h]

  Mem_AllocArray(&matchVar1Bitmap, 8);
  Mem_AllocArray(&matchVar2Bitmap, 8);
  if ( joinTest )
  {
    matchVar1Bitmap = ((unsigned __int8)*(_DWORD *)(theNode + 28) << 15) | matchVar1Bitmap & 0xFF807FFF;
    v8 = *(_DWORD *)(theNode + 28);
    LOBYTE(v23) = 0;
    v23 |= (unsigned __int8)v8;
  }
  if ( *(int *)(theNode + 40) < 0 )
  {
    HIBYTE(matchVar1Bitmap) |= 0x80u;
    if ( !joinTest )
      goto LABEL_13;
    goto LABEL_10;
  }
  if ( (*(_BYTE *)(theNode + 12) & 0x7F) == 0
    && (*(_WORD *)(theNode + 12) & 0x3F80) == 0
    && (*(_DWORD *)(theNode + 8) & 0x3F8000) == 0
    && (*(_WORD *)(theNode + 10) & 0x1FC0) == 0
    && ((*(_BYTE *)(theNode + 9) & 0x40) == 0 || *(_DWORD *)theNode == 16 || *(_DWORD *)theNode == 18) )
  {
    v21 |= 1u;
    v4 = *(_DWORD *)(theNode + 40);
    LOWORD(matchVar1Bitmap) = matchVar1Bitmap & 0x8000;
    matchVar1Bitmap |= v4 & 0x7FFF;
    if ( !joinTest )
      goto LABEL_13;
LABEL_10:
    var1NodeType = 47;
LABEL_11:
    *v3 = var1NodeType;
    result = Rules_AddBitmapValue(&matchVar1Bitmap, 8);
    *(_DWORD *)(v7 + 2) = result;
    return result;
  }
  if ( (*(_DWORD *)theNode == 17 || *(_DWORD *)theNode == 15)
    && ((*(_DWORD *)(theNode + 8) & 0x3F8000) == 0 || (*(_WORD *)(theNode + 10) & 0x1FC0) == 0) )
  {
    v9 = *(_DWORD *)(theNode + 40);
    LOWORD(matchVar2Bitmap) = matchVar2Bitmap & 0x8000;
    matchVar2Bitmap |= v9 & 0x7FFF;
    if ( (*(_DWORD *)(theNode + 8) & 0x3F8000) != 0 )
    {
      BYTE2(matchVar2Bitmap) |= 0x80u;
      v17 = *(_DWORD *)(theNode + 12) << 18 >> 25;
      HIBYTE(matchVar2Bitmap) &= 0x80u;
      v11 = (v17 & 0x7F) << 24;
    }
    else
    {
      BYTE1(matchVar2Bitmap) |= 0x80u;
      v10 = *(_DWORD *)(theNode + 12);
      BYTE2(matchVar2Bitmap) &= 0x80u;
      v11 = (v10 & 0x7F) << 16;
    }
    matchVar2Bitmap |= v11;
    if ( joinTest )
      var2NodeType = 48;
    else
      var2NodeType = 46;
    goto LABEL_22;
  }
  if ( *(_DWORD *)theNode != 18 && *(_DWORD *)theNode != 16
    || (*(_DWORD *)(theNode + 8) & 0x3F8000) != 0
    || (*(_WORD *)(theNode + 10) & 0x1FC0) != 0 )
  {
    v18 = *(_DWORD *)(theNode + 40);
    LOWORD(matchVar1Bitmap) = matchVar1Bitmap & 0x8000;
    matchVar1Bitmap |= v18 & 0x7FFF;
    v19 = (unsigned __int8)*(_DWORD *)(theNode + 32);
    HIWORD(matchVar1Bitmap) &= 0x807Fu;
    matchVar1Bitmap |= v19 << 23;
    if ( joinTest )
      goto LABEL_10;
LABEL_13:
    var1NodeType = 45;
    goto LABEL_11;
  }
  v14 = *(_DWORD *)(theNode + 40);
  LOWORD(matchVar2Bitmap) = matchVar2Bitmap & 0x8000;
  matchVar2Bitmap |= v14 & 0x7FFF | 0x808000;
  v15 = *(_DWORD *)(theNode + 12) & 0x7F;
  BYTE2(matchVar2Bitmap) &= 0x80u;
  matchVar2Bitmap |= v15 << 16;
  v16 = *(_DWORD *)(theNode + 12) << 18 >> 25;
  HIBYTE(matchVar2Bitmap) &= 0x80u;
  matchVar2Bitmap |= (v16 & 0x7F) << 24;
  if ( joinTest )
    var2NodeType = 48;
  else
    var2NodeType = 46;
LABEL_22:
  *v3 = var2NodeType;
  result = Rules_AddBitmapValue(&matchVar2Bitmap, 8);
  *(_DWORD *)(v13 + 2) = result;
  return result;
}
// 4E17EA: variable 'v3' is possibly undefined
// 4E17F4: variable 'v7' is possibly undefined
// 4E18CE: variable 'v13' is possibly undefined

//----- (004E1A40) --------------------------------------------------------
BOOL  Rules_IsMultiplyConstrainedSlot(int theNode)
{
  return *(_DWORD *)theNode != 18
      && *(_DWORD *)theNode != 16
      && *(int *)(theNode + 40) >= 2
      && ((*(_BYTE *)(theNode + 9) & 0x40) == 0
       || (*(_BYTE *)(theNode + 8) & 4) == 0
       && ((*(_DWORD *)(theNode + 8) & 0x3F8000) == 0 || (*(_WORD *)(theNode + 10) & 0x1FC0) == 0));
}
// 4E1A53: simplified comparisons for 'ebx.4': <0 || ==0 became <1
// 4E1A53: simplified comparisons for 'ebx.4': <1 || ==1 became <2

//----- (004E1A90) --------------------------------------------------------
signed int  Rules_BuildDualSlotConstraintBitmapTestNode(int joinTest, int selfNode, int referringNode)
{
  int v5; // ecx
  int compareSymbol; // edx
  signed int compareCallNode; // ebp
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
  int jnVars1; // [esp+0h] [ebp-3Ch] BYREF
  int v52; // [esp+4h] [ebp-38h]
  int pnVars2; // [esp+8h] [ebp-34h] BYREF
  int v54; // [esp+Ch] [ebp-30h]
  int pnVars3; // [esp+10h] [ebp-2Ch] BYREF
  int v56; // [esp+14h] [ebp-28h]
  int jnVars2; // [esp+18h] [ebp-24h] BYREF
  int v58; // [esp+1Ch] [ebp-20h]
  int jnVars3; // [esp+20h] [ebp-1Ch] BYREF
  int v60; // [esp+24h] [ebp-18h]
  _DWORD pnVars1[5]; // [esp+28h] [ebp-14h] BYREF

  if ( Rules_IsMultiplyConstrainedSlot(selfNode) && Rules_IsMultiplyConstrainedSlot(referringNode) )
  {
    if ( (*(_BYTE *)(v10 + 9) & 0x40) == 0 && (*(_BYTE *)(referringNode + 9) & 0x40) == 0 )
    {
      Mem_AllocArray(pnVars1, 4);
      Mem_AllocArray(&jnVars1, 8);
      if ( (*(_BYTE *)(v11 + 8) & 1) != 0 )
      {
        HIBYTE(jnVars1) |= 0x80u;
        HIBYTE(pnVars1[0]) = HIBYTE(pnVars1[0]) & 0x7F | 0x80;
      }
      else
      {
        BYTE1(jnVars1) |= 0x80u;
        BYTE1(pnVars1[0]) = BYTE1(pnVars1[0]) & 0x7F | 0x80;
      }
      v12 = *(_DWORD *)(v11 + 40);
      LOWORD(jnVars1) = jnVars1 & 0x8000;
      jnVars1 |= v12 & 0x7FFF;
      v13 = *(_DWORD *)(v11 + 40);
      LOWORD(pnVars1[0]) &= 0x8000u;
      pnVars1[0] |= v13 & 0x7FFF;
      v14 = *(_DWORD *)(referringNode + 40);
      HIWORD(jnVars1) &= 0x8000u;
      jnVars1 |= (v14 & 0x7FFF) << 16;
      v15 = *(_DWORD *)(referringNode + 40);
      HIWORD(pnVars1[0]) &= 0x8000u;
      pnVars1[0] |= (v15 & 0x7FFF) << 16;
      if ( joinTest )
      {
        v16 = *(_DWORD *)(v11 + 28);
        LOBYTE(v52) = 0;
        v52 |= (unsigned __int8)v16;
        v17 = *(_DWORD *)(referringNode + 28);
        BYTE1(v52) = 0;
        v52 |= (unsigned __int8)v17 << 8;
        v18 = Rules_AddBitmapValue(&jnVars1, 8);
        return AST_NewNode(52, v18);
      }
      else
      {
        v19 = Rules_AddBitmapValue(pnVars1, 4);
        return AST_NewNode(51, v19);
      }
    }
    if ( (*(_BYTE *)(v5 + 9) & 0x40) == 0 || (*(_BYTE *)(referringNode + 9) & 0x40) == 0 )
    {
      Mem_AllocArray(&pnVars2, 8);
      Mem_AllocArray(&jnVars2, 8);
      if ( (*(_BYTE *)(v20 + 8) & 1) != 0 )
      {
        BYTE2(v58) |= 0x80u;
        HIBYTE(pnVars2) = HIBYTE(pnVars2) & 0x7F | 0x80;
      }
      else
      {
        BYTE1(jnVars2) |= 0x80u;
        BYTE1(pnVars2) = BYTE1(pnVars2) & 0x7F | 0x80;
      }
      v22 = v58;
      v21 = jnVars2 & 0xFFFF8000;
      v23 = pnVars2 & 0xFFFF8000;
      LOBYTE(v22) = 0;
      if ( (*(_BYTE *)(v20 + 9) & 0x40) != 0 )
      {
        jnVars2 = v21 | *(_DWORD *)(v20 + 40) & 0x7FFF;
        pnVars2 = *(_DWORD *)(v20 + 40) & 0x7FFF | v23;
        v24 = *(_DWORD *)(referringNode + 40);
        HIWORD(jnVars2) &= 0x8000u;
        jnVars2 |= (v24 & 0x7FFF) << 16;
        v25 = *(_DWORD *)(referringNode + 40);
        HIWORD(pnVars2) &= 0x8000u;
        pnVars2 |= (v25 & 0x7FFF) << 16;
        if ( joinTest )
        {
          v58 = (unsigned __int8)*(_DWORD *)(v20 + 28) | v22;
          v26 = *(_DWORD *)(referringNode + 28);
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
        HIBYTE(jnVars2) |= 0x80u;
        LOBYTE(v54) = v54 & 0x7F | 0x80;
        v28 = *(_DWORD *)(v20 + 12);
      }
      else
      {
        jnVars2 = v21 | *(_DWORD *)(referringNode + 40) & 0x7FFF;
        pnVars2 = *(_DWORD *)(referringNode + 40) & 0x7FFF | v23;
        v32 = *(_DWORD *)(v20 + 40);
        HIWORD(jnVars2) &= 0x8000u;
        jnVars2 |= (v32 & 0x7FFF) << 16;
        v33 = *(_DWORD *)(v20 + 40) & 0x7FFF;
        HIWORD(pnVars2) &= 0x8000u;
        pnVars2 |= v33 << 16;
        if ( joinTest )
        {
          v58 = (unsigned __int8)*(_DWORD *)(referringNode + 28) | v22;
          v34 = *(_DWORD *)(v20 + 28);
          BYTE1(v58) = 0;
          v58 |= (unsigned __int8)v34 << 8;
        }
        v27 = v58 & 0xFF80FFFF;
        if ( (*(_DWORD *)(referringNode + 8) & 0x3F8000) != 0 )
        {
          v35 = (unsigned __int8)(*(_DWORD *)(referringNode + 12) << 18 >> 24) >> 1;
          LOBYTE(v54) = v54 & 0x80;
          v58 = (v35 << 16) | v27;
          v54 |= v35;
LABEL_25:
          if ( joinTest )
          {
            v31 = Rules_AddBitmapValue(&jnVars2, 8);
            return AST_NewNode(54, v31);
          }
          else
          {
            v36 = Rules_AddBitmapValue(&pnVars2, 8);
            return AST_NewNode(53, v36);
          }
        }
        HIBYTE(jnVars2) |= 0x80u;
        LOBYTE(v54) = v54 & 0x7F | 0x80;
        v28 = *(_DWORD *)(referringNode + 12);
      }
      v29 = v28 & 0x7F;
      v58 = (v29 << 16) | v27;
      LOBYTE(v54) = v54 & 0x80;
      v30 = v29 & 0x7F;
LABEL_24:
      v54 |= v30;
      goto LABEL_25;
    }
    Mem_AllocArray(&pnVars3, 8);
    Mem_AllocArray(&jnVars3, 8);
    if ( (*(_BYTE *)(v37 + 8) & 1) != 0 )
    {
      HIBYTE(jnVars3) |= 0x80u;
      HIBYTE(pnVars3) = HIBYTE(pnVars3) & 0x7F | 0x80;
    }
    else
    {
      BYTE1(jnVars3) |= 0x80u;
      BYTE1(pnVars3) = BYTE1(pnVars3) & 0x7F | 0x80;
    }
    v38 = *(_DWORD *)(v37 + 40);
    LOWORD(jnVars3) = jnVars3 & 0x8000;
    jnVars3 |= v38 & 0x7FFF;
    v39 = *(_DWORD *)(v37 + 40);
    LOWORD(pnVars3) = pnVars3 & 0x8000;
    pnVars3 |= v39 & 0x7FFF;
    v40 = *(_DWORD *)(referringNode + 40);
    HIWORD(jnVars3) &= 0x8000u;
    jnVars3 |= (v40 & 0x7FFF) << 16;
    v41 = *(_DWORD *)(referringNode + 40);
    HIWORD(pnVars3) &= 0x8000u;
    pnVars3 |= (v41 & 0x7FFF) << 16;
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
    if ( (*(_DWORD *)(referringNode + 8) & 0x3F8000) != 0 )
    {
      v46 = (unsigned __int8)(*(_DWORD *)(referringNode + 12) << 18 >> 24) >> 1;
      HIBYTE(v60) &= 0x80u;
      v60 |= v46 << 24;
    }
    else
    {
      HIBYTE(v60) |= 0x80u;
      BYTE1(v56) = BYTE1(v56) & 0x7F | 0x80;
      v45 = *(_DWORD *)(referringNode + 12) & 0x7F;
      HIBYTE(v60) &= 0x80u;
      v60 |= v45 << 24;
      v46 = v45 & 0x7F;
    }
    BYTE1(v56) &= 0x80u;
    v56 |= v46 << 8;
    if ( joinTest )
    {
      v47 = *(_DWORD *)(v37 + 28);
      LOBYTE(v60) = 0;
      v60 |= (unsigned __int8)v47;
      v48 = *(_DWORD *)(referringNode + 28);
      BYTE1(v60) = 0;
      v60 |= (unsigned __int8)v48 << 8;
      v49 = Rules_AddBitmapValue(&jnVars3, 8);
      return AST_NewNode(56, v49);
    }
    else
    {
      v50 = Rules_AddBitmapValue(&pnVars3, 8);
      return AST_NewNode(55, v50);
    }
  }
  else
  {
    if ( (*(_BYTE *)(v5 + 8) & 1) != 0 )
      compareSymbol = g_ClipsSymbolNeq;
    else
      compareSymbol = g_ClipsSymbolEq;
    compareCallNode = AST_NewNode(10, compareSymbol);
    *(_DWORD *)(compareCallNode + 6) = AST_NewNode(0, 0);
    Rules_BuildSlotConstraintBitmapTestNode(joinTest, v8);
    *(_DWORD *)(*(_DWORD *)(compareCallNode + 6) + 10) = AST_NewNode(0, 0);
    Rules_BuildSlotConstraintBitmapTestNode(joinTest, referringNode);
    return compareCallNode;
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
  int slotBitmap; // ebx
  int alphaIndex; // edx
  _DWORD *result; // eax
  int patternIndex; // edx
  _DWORD *nextLevelNode; // esi

  if ( Rules_IsBloaded() )
  {
    Rules_ConstructQueuePush(g_ReactiveRuleBloadCount);
    Rules_ConstructQueuePush(g_ObjectPatternNetworkBloadCount);
  }
  g_ReactiveRuleBloadCount = 0;
  for ( i = (_DWORD *)Rules_GetReactiveRuleList(); i; i = (_DWORD *)i[9] )
  {
    *(_BYTE *)(i[5] + 12) |= 2u;
    slotBitmap = i[6];
    if ( slotBitmap )
      *(_BYTE *)(i[6] + 12) = *(_BYTE *)(slotBitmap + 12) | 2;
    alphaIndex = g_ReactiveRuleBloadCount++;
    i[10] = alphaIndex;
  }
  g_ObjectPatternNetworkBloadCount = 0;
  result = (_DWORD *)Rules_GetObjectPatternNetworkRoot();
  if ( result )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        patternIndex = g_ObjectPatternNetworkBloadCount++;
        nextLevelNode = (_DWORD *)result[4];
        result[9] = patternIndex;
        if ( !nextLevelNode )
          break;
        result = nextLevelNode;
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
const void * Rules_BsaveObjectPatternNetworkCounts(int filePtr, int a2)
{
  int v2; // ecx
  int v3; // ecx
  _DWORD spaceBuffer[4]; // [esp+0h] [ebp-10h] BYREF

  spaceBuffer[2] = a2;
  spaceBuffer[0] = 8;
  Rules_BsaveWriteBlock(4, filePtr, spaceBuffer);
  Rules_BsaveWriteBlock(4, v2, &g_ReactiveRuleBloadCount);
  return Rules_BsaveWriteBlock(4, v3, &g_ObjectPatternNetworkBloadCount);
}
// 4E232A: variable 'v2' is possibly undefined
// 4E233B: variable 'v3' is possibly undefined
// 51C718: using guessed type int dword_51C718;
// 51C71C: using guessed type int dword_51C71C;

//----- (004E2350) --------------------------------------------------------
const void * Rules_BsaveObjectPatternNetworkRecords(int outFile)
{
  int i; // ecx
  _DWORD *alphaNode; // ecx
  int slotBitmapRef; // edx
  int patternNodeRef; // edi
  int patternIndex; // eax
  int nextAlphaPtr; // ebp
  int nextAlphaIdx; // eax
  int nextTerminalPtr; // eax
  int nextTerminalIdx; // eax
  int v11; // ecx
  int currentPattern; // ecx
  unsigned int v13; // eax
  int v14; // eax
  int v15; // eax
  _DWORD *v16; // ecx
  int nextLevelPtr; // ebx
  int nextLevelIndex; // eax
  int lastLevelPtr; // edi
  int lastLevelIndex; // eax
  int leftNodePtr; // ebp
  int leftNodeIndex; // eax
  int rightNodePtr; // eax
  int rightNodeIndex; // eax
  int alphaPtr; // edx
  int alphaNodeIndex; // eax
  const void *result; // eax
  _DWORD *traverseNode; // ecx
  _DWORD bsavePatternRecord[8]; // [esp+0h] [ebp-58h] BYREF
  _BYTE bsaveAlphaRecord[8]; // [esp+20h] [ebp-38h] BYREF
  int classBitmapIndex; // [esp+28h] [ebp-30h]
  int slotBitmapIndex; // [esp+2Ch] [ebp-2Ch]
  int patternNodeIndex; // [esp+30h] [ebp-28h]
  int nextAlphaIndex; // [esp+34h] [ebp-24h]
  int nextTerminalIndex; // [esp+38h] [ebp-20h]
  int v36[7]; // [esp+3Ch] [ebp-1Ch] BYREF

  v36[0] = 32 * g_ObjectPatternNetworkBloadCount + 28 * g_ReactiveRuleBloadCount;
  Rules_BsaveWriteBlock(4, outFile, v36);
  for ( i = Rules_GetReactiveRuleList(); i; i = *(_DWORD *)(v11 + 36) )
  {
    Rules_BsavePackSharedRecordHeader((int)bsaveAlphaRecord, i);
    classBitmapIndex = *(_DWORD *)(alphaNode[5] + 12) << 16 >> 18;
    slotBitmapRef = alphaNode[6];
    if ( slotBitmapRef )
      slotBitmapIndex = *(_DWORD *)(slotBitmapRef + 12) << 16 >> 18;
    else
      slotBitmapIndex = -1;
    patternNodeRef = alphaNode[7];
    if ( patternNodeRef )
      patternIndex = *(_DWORD *)(patternNodeRef + 36);
    else
      patternIndex = -1;
    patternNodeIndex = patternIndex;
    nextAlphaPtr = alphaNode[8];
    if ( nextAlphaPtr )
      nextAlphaIdx = *(_DWORD *)(nextAlphaPtr + 40);
    else
      nextAlphaIdx = -1;
    nextAlphaIndex = nextAlphaIdx;
    nextTerminalPtr = alphaNode[9];
    if ( nextTerminalPtr )
      nextTerminalIdx = *(_DWORD *)(nextTerminalPtr + 40);
    else
      nextTerminalIdx = -1;
    nextTerminalIndex = nextTerminalIdx;
    Rules_BsaveWriteBlock(28, outFile, bsaveAlphaRecord);
  }
  currentPattern = Rules_GetObjectPatternNetworkRoot();
  while ( currentPattern )
  {
    v13 = *(_DWORD *)currentPattern << 30;
    LOBYTE(bsavePatternRecord[0]) &= ~1u;
    bsavePatternRecord[0] |= v13 >> 31;
    v14 = *(_DWORD *)currentPattern << 21 >> 24;
    LOWORD(bsavePatternRecord[0]) &= 0xFC03u;
    bsavePatternRecord[0] |= 4 * (unsigned __int8)v14;
    bsavePatternRecord[0] = ((unsigned __int8)(*(_DWORD *)currentPattern << 13 >> 24) << 10) | bsavePatternRecord[0] & 0xFFFC03FF;
    v15 = *(_DWORD *)currentPattern << 29 >> 31;
    LOBYTE(bsavePatternRecord[0]) &= ~2u;
    bsavePatternRecord[0] |= 2 * (v15 & 1);
    bsavePatternRecord[1] = *(_DWORD *)(currentPattern + 8);
    bsavePatternRecord[2] = AST_GetHashedNodeIndex(*(__int16 **)(currentPattern + 12));
    nextLevelPtr = v16[4];
    if ( nextLevelPtr )
      nextLevelIndex = *(_DWORD *)(nextLevelPtr + 36);
    else
      nextLevelIndex = -1;
    bsavePatternRecord[3] = nextLevelIndex;
    lastLevelPtr = v16[5];
    if ( lastLevelPtr )
      lastLevelIndex = *(_DWORD *)(lastLevelPtr + 36);
    else
      lastLevelIndex = -1;
    bsavePatternRecord[4] = lastLevelIndex;
    leftNodePtr = v16[6];
    if ( leftNodePtr )
      leftNodeIndex = *(_DWORD *)(leftNodePtr + 36);
    else
      leftNodeIndex = -1;
    bsavePatternRecord[5] = leftNodeIndex;
    rightNodePtr = v16[7];
    if ( rightNodePtr )
      rightNodeIndex = *(_DWORD *)(rightNodePtr + 36);
    else
      rightNodeIndex = -1;
    bsavePatternRecord[6] = rightNodeIndex;
    alphaPtr = v16[8];
    if ( alphaPtr )
      alphaNodeIndex = *(_DWORD *)(alphaPtr + 40);
    else
      alphaNodeIndex = -1;
    bsavePatternRecord[7] = alphaNodeIndex;
    result = Rules_BsaveWriteBlock(32, outFile, bsavePatternRecord);
    if ( traverseNode[4] )
    {
      currentPattern = traverseNode[4];
    }
    else
    {
      while ( !traverseNode[7] )
      {
        traverseNode = (_DWORD *)traverseNode[5];
        if ( !traverseNode )
          return result;
      }
      currentPattern = traverseNode[7];
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
  int space; // [esp+0h] [ebp-8h] BYREF

  result = Rules_BloadReadBlock((uintptr_t)&space, 4u);
  if ( space )
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
int  Rules_RefreshBloadedReactiveRuleRecord(int *bsaveAlpha, int itemIndex)
{
  int record; // ecx
  int reactive_slots_index; // ebp
  int reactive_slots; // eax
  int direct_super_index; // eax
  int result; // eax
  int superclass_index; // ebx
  int role_symbol; // eax
  int superclass; // ebx

  record = 44 * itemIndex + g_ReactiveRuleArrayPtr;
  Rules_BloadUnpackSharedRecordHeader(record, bsaveAlpha);
  *(_DWORD *)(record + 16) = 0;
  *(_DWORD *)(record + 20) = *(_DWORD *)(g_ClipsBloadBitmapPointerTable + 4 * bsaveAlpha[2]);
  if ( bsaveAlpha[3] == -1 )
  {
    *(_DWORD *)(record + 24) = 0;
  }
  else
  {
    role_symbol = *(_DWORD *)(g_ClipsBloadBitmapPointerTable + 4 * bsaveAlpha[3]);
    *(_DWORD *)(record + 24) = role_symbol;
    ++*(_DWORD *)(role_symbol + 4);
  }
  ++*(_DWORD *)(*(_DWORD *)(record + 20) + 4);
  reactive_slots_index = bsaveAlpha[4];
  if ( reactive_slots_index == -1 )
    reactive_slots = 0;
  else
    reactive_slots = 40 * reactive_slots_index + g_ObjectPatternNetworkArrayPtr;
  *(_DWORD *)(record + 28) = reactive_slots;
  direct_super_index = bsaveAlpha[5];
  if ( direct_super_index == -1 )
    result = 0;
  else
    result = g_ReactiveRuleArrayPtr + 44 * direct_super_index;
  *(_DWORD *)(record + 32) = result;
  superclass_index = bsaveAlpha[6];
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
int * Class_ResolveSystemSlotTemplate(_DWORD *bsaveData, int itemIndex)
{
  int *result; // eax
  int v4; // ebx
  int v5; // ebx
  int v6; // edi
  int v7; // ebx
  int v8; // ebx
  int v9; // edi
  int networkTestIndex; // ebp
  _DWORD *bsaveFields; // edx
  int networkTest; // ecx
  int nextLevelIndex; // ecx
  int nextLevel; // ecx
  int lastLevelIndex; // ebx
  int lastLevel; // ecx
  int leftNodeIndex; // esi
  int leftNode; // ecx
  int rightNodeIndex; // edi
  int rightNode; // ecx
  int alphaNodeIndex; // ebp
  int alphaNode; // edx

  result = (int *)(40 * itemIndex + g_ObjectPatternNetworkArrayPtr);
  *(_BYTE *)result &= ~1u;
  v4 = *bsaveData;
  *(_BYTE *)result &= ~2u;
  *result |= 2 * (v4 & 1);
  v5 = *bsaveData << 22 >> 24;
  *(_WORD *)result &= 0xF807u;
  v6 = (8 * (unsigned __int8)v5) | *result;
  *result = v6;
  v7 = (unsigned __int8)(*bsaveData << 14 >> 24) << 11;
  *result = v6 & 0xFFF807FF;
  *result = v7 | v6 & 0xFFF807FF;
  v8 = *bsaveData << 30 >> 31;
  *(_BYTE *)result &= ~4u;
  v9 = *result;
  result[1] = 0;
  *result = (4 * (v8 & 1)) | v9;
  result[2] = bsaveData[1];
  networkTestIndex = bsaveData[2];
  bsaveFields = bsaveData;
  if ( networkTestIndex == -1 )
    networkTest = 0;
  else
    networkTest = g_ClipsPackedExpressionArray + 14 * networkTestIndex;
  result[3] = networkTest;
  nextLevelIndex = bsaveFields[3];
  if ( nextLevelIndex == -1 )
    nextLevel = 0;
  else
    nextLevel = g_ObjectPatternNetworkArrayPtr + 40 * nextLevelIndex;
  result[4] = nextLevel;
  lastLevelIndex = bsaveFields[4];
  if ( lastLevelIndex == -1 )
    lastLevel = 0;
  else
    lastLevel = g_ObjectPatternNetworkArrayPtr + 40 * lastLevelIndex;
  result[5] = lastLevel;
  leftNodeIndex = bsaveFields[5];
  if ( leftNodeIndex == -1 )
    leftNode = 0;
  else
    leftNode = g_ObjectPatternNetworkArrayPtr + 40 * leftNodeIndex;
  result[6] = leftNode;
  rightNodeIndex = bsaveFields[6];
  if ( rightNodeIndex == -1 )
    rightNode = 0;
  else
    rightNode = g_ObjectPatternNetworkArrayPtr + 40 * rightNodeIndex;
  result[7] = rightNode;
  alphaNodeIndex = bsaveFields[7];
  if ( alphaNodeIndex == -1 )
  {
    result[9] = 0;
    result[8] = 0;
  }
  else
  {
    alphaNode = g_ReactiveRuleArrayPtr + 44 * alphaNodeIndex;
    result[9] = 0;
    result[8] = alphaNode;
  }
  return result;
}
// 51C720: using guessed type int dword_51C720;
// 51C724: using guessed type int dword_51C724;
// 54E688: using guessed type int dword_54E688;

//----- (004E2970) --------------------------------------------------------
int Class_ClearClassIDTable()
{
  int alphaIndex; // ecx
  int recordOffset; // edx
  int v2; // edx
  int v3; // ecx

  alphaIndex = 0;
  if ( g_ReactiveRuleBloadCount > 0 )
  {
    recordOffset = 0;
    do
    {
      Rules_DecrementBitmapCount(*(_DWORD *)(recordOffset + g_ReactiveRuleArrayPtr + 20), alphaIndex);
      if ( *(_DWORD *)(v2 + g_ReactiveRuleArrayPtr + 24) )
        Rules_DecrementBitmapCount(*(_DWORD *)(v2 + g_ReactiveRuleArrayPtr + 24), v3);
      alphaIndex = v3 + 1;
      recordOffset = v2 + 44;
    }
    while ( alphaIndex < g_ReactiveRuleBloadCount );
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
int  Class_ParseSuperclasses(int readSource, int className)
{
  int **linkHead; // esi
  int **linkTail; // ebp
  int v6; // edx
  int **linkScan; // eax
  int *superclass; // eax
  int *theClass; // ecx
  _DWORD *v11; // edx
  int **newLink; // eax
  _DWORD *freeNode; // edx
  signed int packedLinks; // eax
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // eax
  int v22; // ecx
  int v23; // ecx

  linkHead = 0;
  linkTail = 0;
  if ( g_ParserCurrentTokenType == 100
    && (Parser_NextToken(readSource, (int)&g_ParserCurrentTokenType), g_ParserCurrentTokenType == 2)
    && g_ClipsParserTokenValue == g_Symbol_IsA )
  {
    IO_OutWriteToken(asc_50E6E8);
    Parser_NextToken(readSource, v6);
    if ( g_ParserCurrentTokenType == 101 )
    {
LABEL_23:
      if ( linkHead )
      {
        IO_OutNewline();
        IO_OutNewline();
        IO_OutWriteToken(asc_50E7F8);
        freeNode = *(_DWORD **)(g_ClipsMemoryTable + 24);
        if ( freeNode )
        {
          g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 24);
          *(_DWORD *)(g_ClipsMemoryTable + 24) = *freeNode;
          Class_PackClassLinkList(g_ClipsMemFreeListTemp, linkHead);
        }
        else
        {
          packedLinks = Mem_HeapAllocWithRetry((_DWORD *)6);
          Class_PackClassLinkList(packedLinks, linkHead);
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
          Mem_ReturnListToFreePool(linkHead);
          return 0;
        }
        if ( Rules_FindModuleSeparator(*(_BYTE **)(className + 16)) )
        {
          Module_ReportIllegalSpecifierError();
          Mem_ReturnListToFreePool(linkHead);
          return 0;
        }
        if ( className == g_ClipsParserTokenValue )
        {
          Rules_PrintErrorID((int)aInherpsr, 1, 0);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAClassMayNotHa, v16);
          Mem_ReturnListToFreePool(linkHead);
          return 0;
        }
        linkScan = linkHead;
        if ( linkHead )
          break;
LABEL_14:
        superclass = Class_LookupInScope(*(_BYTE **)(g_ClipsParserTokenValue + 16));
        theClass = superclass;
        if ( !superclass )
        {
          Rules_PrintErrorID((int)aInherpsr, 3, 0);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAClassMustBe_0, v18);
          Mem_ReturnListToFreePool(linkHead);
          return 0;
        }
        if ( superclass == (int *)g_Class_InstanceName || superclass == (int *)g_Class_InstanceAddress || superclass == **(int ***)(g_Class_InstanceName + 36) )
        {
          Rules_PrintErrorID((int)aInherpsr, 6, 0);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAUserDefinedCl, v19);
          v21 = Rules_GetConstructNameString(v20);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], v21, (int)g_IO_LogicalNameTable_WError[0]);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__28, v22);
          Mem_ReturnListToFreePool(linkHead);
          return 0;
        }
        v11 = *(_DWORD **)(g_ClipsMemoryTable + 32);
        if ( v11 )
        {
          g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
          *(_DWORD *)(g_ClipsMemoryTable + 32) = *v11;
          newLink = (int **)g_ClipsMemFreeListTemp;
        }
        else
        {
          newLink = (int **)Mem_HeapAllocWithRetry((_DWORD *)8);
        }
        *newLink = theClass;
        if ( linkHead )
          linkTail[1] = (int *)newLink;
        else
          linkHead = newLink;
        linkTail = newLink;
        newLink[1] = 0;
        IO_OutWriteToken(asc_50E6E8);
        Parser_NextToken(readSource, (int)&g_ParserCurrentTokenType);
        if ( g_ParserCurrentTokenType == 101 )
          goto LABEL_23;
      }
      while ( g_ClipsParserTokenValue != **linkScan )
      {
        linkScan = (int **)linkScan[1];
        if ( !linkScan )
          goto LABEL_14;
      }
      Rules_PrintErrorID((int)aInherpsr, 2, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAClassMayInher, v17);
      Mem_ReturnListToFreePool(linkHead);
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
int  Class_BuildPrecedenceList(int theClass, unsigned __int16 *superclassLinks)
{
  _DWORD *allSuperclasses; // eax
  _DWORD *partialOrderList; // esi
  _DWORD *v4; // ecx
  _DWORD *classOrderNode; // eax
  int superOffset; // ebp
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
  _DWORD *currentNode; // edx
  _DWORD *v18; // ebx
  _DWORD *prevNode; // ecx
  _DWORD *dependencyLink; // ebp
  int *removedNode; // ebp
  _DWORD *v22; // edi
  int *precedenceLink; // eax
  int classPtr; // edi
  _DWORD *v25; // edx
  signed int v26; // eax
  int *oldListHead; // edx
  _DWORD *v28; // ecx
  signed int packedLinksMem; // ecx
  int v30; // ecx
  _DWORD *v32; // ebp
  _DWORD *v33; // eax
  int *precedenceTail; // [esp+8h] [ebp-24h]
  int *precedenceList; // [esp+Ch] [ebp-20h]
  int *scanNode; // [esp+14h] [ebp-18h]

  allSuperclasses = Class_CollectAllSuperclasses(0, superclassLinks);
  partialOrderList = allSuperclasses;
  if ( theClass )
  {
    v4 = *(_DWORD **)(g_ClipsMemoryTable + 64);
    if ( v4 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
      *(_DWORD *)(g_ClipsMemoryTable + 64) = *v4;
      classOrderNode = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      classOrderNode = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x10);
    }
    classOrderNode[1] = 0;
    classOrderNode[2] = 0;
    classOrderNode[3] = partialOrderList;
    *classOrderNode = theClass;
    scanNode = (int *)classOrderNode[3];
    partialOrderList = classOrderNode;
    Class_AddPrecedenceDependency(classOrderNode, theClass, 0, superclassLinks);
  }
  else
  {
    scanNode = allSuperclasses;
  }
  while ( scanNode )
  {
    superOffset = 0;
    Class_AddPrecedenceDependency(partialOrderList, *scanNode, 0, (unsigned __int16 *)(*scanNode + 34));
    for ( i = 0; ; i = v9 )
    {
      v8 = *scanNode;
      if ( i >= *(unsigned __int16 *)(*scanNode + 34) )
        break;
      v9 = i + 1;
      v10 = i + 1;
      v11 = *(_DWORD *)(*(_DWORD *)(v8 + 36) + superOffset);
      superOffset += 4;
      Class_AddPrecedenceDependency(partialOrderList, v11, v10, (unsigned __int16 *)(v8 + 34));
    }
    scanNode = (int *)scanNode[3];
  }
  v12 = 0;
  v13 = 0;
  while ( v12 < *superclassLinks )
  {
    v14 = v12 + 1;
    v15 = v12 + 1;
    v16 = *(_DWORD *)(*(_DWORD *)(superclassLinks + 1) + v13);
    v13 += 4;
    Class_AddPrecedenceDependency(partialOrderList, v16, v15, superclassLinks);
    v12 = v14;
  }
  currentNode = partialOrderList;
  v18 = 0;
  prevNode = 0;
  precedenceTail = 0;
  precedenceList = 0;
  if ( partialOrderList )
  {
    do
    {
      if ( !currentNode )
      {
        currentNode = partialOrderList;
        v18 = (_DWORD *)v18[3];
        prevNode = 0;
      }
      if ( currentNode[1] )
      {
        prevNode = currentNode;
        currentNode = (_DWORD *)currentNode[3];
      }
      else
      {
        while ( 1 )
        {
          dependencyLink = (_DWORD *)currentNode[2];
          if ( !dependencyLink )
            break;
          currentNode[2] = dependencyLink[1];
          --*(_DWORD *)(*dependencyLink + 4);
          g_ClipsMemFreeListTemp = (int)dependencyLink;
          *dependencyLink = *(_DWORD *)(g_ClipsMemoryTable + 32);
          *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
        }
        removedNode = currentNode;
        if ( prevNode )
          prevNode[3] = currentNode[3];
        else
          partialOrderList = (_DWORD *)currentNode[3];
        v18 = prevNode;
        v22 = *(_DWORD **)(g_ClipsMemoryTable + 32);
        currentNode = (_DWORD *)currentNode[3];
        if ( v22 )
        {
          g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
          *(_DWORD *)(g_ClipsMemoryTable + 32) = *v22;
          precedenceLink = (int *)g_ClipsMemFreeListTemp;
        }
        else
        {
          precedenceLink = (int *)Mem_HeapAllocWithRetry((_DWORD *)8);
        }
        classPtr = *removedNode;
        precedenceLink[1] = 0;
        *precedenceLink = classPtr;
        g_ClipsMemFreeListTemp = (int)removedNode;
        *removedNode = *(_DWORD *)(g_ClipsMemoryTable + 64);
        *(_DWORD *)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
        if ( precedenceList )
          precedenceTail[1] = (int)precedenceLink;
        else
          precedenceList = precedenceLink;
        precedenceTail = precedenceLink;
      }
    }
    while ( currentNode != v18 );
  }
  if ( partialOrderList )
  {
    Rules_PrintErrorID((int)aInherpsr, 5, 0);
    Class_PrintClassNameList((int)g_IO_LogicalNameTable_WError[0], (int)aPartialPrecede, precedenceList);
    Class_ReportPrecedenceLoop(partialOrderList);
    do
    {
      while ( 1 )
      {
        v32 = (_DWORD *)partialOrderList[2];
        if ( !v32 )
          break;
        partialOrderList[2] = v32[1];
        g_ClipsMemFreeListTemp = (int)v32;
        *v32 = *(_DWORD *)(g_ClipsMemoryTable + 32);
        *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
      }
      v33 = partialOrderList;
      partialOrderList = (_DWORD *)partialOrderList[3];
      g_ClipsMemFreeListTemp = (int)v33;
      *v33 = *(_DWORD *)(g_ClipsMemoryTable + 64);
      *(_DWORD *)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
    }
    while ( partialOrderList );
    Mem_ReturnListToFreePool(precedenceList);
    return 0;
  }
  else
  {
    if ( !theClass )
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
      oldListHead = precedenceList;
      precedenceList = (int *)v26;
      *(_DWORD *)(v26 + 4) = oldListHead;
    }
    *precedenceList = 0;
    v28 = *(_DWORD **)(g_ClipsMemoryTable + 24);
    if ( v28 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 24);
      *(_DWORD *)(g_ClipsMemoryTable + 24) = *v28;
      packedLinksMem = g_ClipsMemFreeListTemp;
    }
    else
    {
      packedLinksMem = Mem_HeapAllocWithRetry((_DWORD *)6);
    }
    Class_PackClassLinkList(packedLinksMem, precedenceList);
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
_DWORD * Class_PackClassLinkList(int packedLinks, _DWORD *linkList)
{
  _DWORD *countScan; // eax
  int i; // edx
  _DWORD *copyScan; // eax
  int v7; // edx
  int arrayOffset; // ecx
  _DWORD *result; // eax
  __int16 v10; // dx

  countScan = linkList;
  for ( i = 0; countScan; ++i )
    countScan = (_DWORD *)countScan[1];
  if ( i )
    *(_DWORD *)(packedLinks + 2) = Mem_SmallBlockAlloc(4 * i);
  else
    *(_DWORD *)(packedLinks + 2) = 0;
  copyScan = linkList;
  v7 = 0;
  if ( linkList )
  {
    arrayOffset = 0;
    do
    {
      *(_DWORD *)(*(_DWORD *)(packedLinks + 2) + arrayOffset) = *copyScan;
      ++v7;
      copyScan = (_DWORD *)copyScan[1];
      arrayOffset += 4;
    }
    while ( copyScan );
  }
  result = Mem_ReturnListToFreePool(linkList);
  *(_WORD *)packedLinks = v10;
  return result;
}
// 4E30F7: variable 'v10' is possibly undefined

//----- (004E3110) --------------------------------------------------------
_DWORD * Class_CollectAllSuperclasses(_DWORD *orderList, unsigned __int16 *superclasses)
{
  int linkOffset; // edi
  _DWORD *existingOrder; // eax
  _DWORD *i; // ecx
  _DWORD *freeListEntry; // ebx
  _DWORD *newOrder; // eax
  int superclass; // edx
  unsigned int superIndex; // [esp+0h] [ebp-18h]

  linkOffset = 0;
  superIndex = 0;
  while ( *superclasses > superIndex )
  {
    existingOrder = orderList;
    for ( i = 0; existingOrder; existingOrder = (_DWORD *)existingOrder[3] )
    {
      if ( *existingOrder == *(_DWORD *)(linkOffset + *(_DWORD *)(superclasses + 1)) )
        break;
      i = existingOrder;
    }
    if ( existingOrder )
    {
      linkOffset += 4;
      ++superIndex;
    }
    else
    {
      freeListEntry = *(_DWORD **)(g_ClipsMemoryTable + 64);
      if ( freeListEntry )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
        *(_DWORD *)(g_ClipsMemoryTable + 64) = *freeListEntry;
        newOrder = (_DWORD *)g_ClipsMemFreeListTemp;
      }
      else
      {
        newOrder = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x10);
      }
      superclass = *(_DWORD *)(*(_DWORD *)(superclasses + 1) + linkOffset);
      newOrder[3] = 0;
      newOrder[2] = 0;
      newOrder[1] = 0;
      *newOrder = superclass;
      if ( i )
        i[3] = newOrder;
      else
        orderList = newOrder;
      orderList = (_DWORD *)Class_CollectAllSuperclasses((int)orderList, *(_DWORD *)(linkOffset + *(_DWORD *)(superclasses + 1)) + 34);
      linkOffset += 4;
      ++superIndex;
    }
  }
  return orderList;
}
// 4E3197: variable 'i' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004E31E0) --------------------------------------------------------
__int16  Class_AddPrecedenceDependency(_DWORD *classList, int theClass, unsigned int startIndex, unsigned __int16 *superclassLinks)
{
  int v7; // ecx
  int i; // esi
  __int16 result; // ax
  _DWORD *freeNode; // edx
  _DWORD *superNode; // eax
  _DWORD *newDependency; // ecx
  _DWORD *classNode; // [esp+0h] [ebp-10h]

  classNode = Class_FindClassLinkNode(classList, theClass);
  for ( i = 4 * v7; ; i += 4 )
  {
    result = *superclassLinks;
    if ( startIndex >= *superclassLinks )
      break;
    freeNode = *(_DWORD **)(g_ClipsMemoryTable + 32);
    if ( freeNode )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
      *(_DWORD *)(g_ClipsMemoryTable + 32) = *freeNode;
    }
    else
    {
      Mem_HeapAllocWithRetry((_DWORD *)8);
    }
    superNode = Class_FindClassLinkNode(classList, *(_DWORD *)(*(_DWORD *)(superclassLinks + 1) + i));
    *newDependency = superNode;
    newDependency[1] = classNode[2];
    classNode[2] = newDependency;
    ++startIndex;
    ++*(_DWORD *)(*newDependency + 4);
  }
  return result;
}
// 4E31F4: variable 'v7' is possibly undefined
// 4E3230: variable 'v12' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004E3270) --------------------------------------------------------
_DWORD * Class_FindClassLinkNode(_DWORD *result, int theClass)
{
  for ( ; result; result = (_DWORD *)result[3] )
  {
    if ( theClass == *result )
      break;
  }
  return result;
}

//----- (004E3280) --------------------------------------------------------
signed int  Class_ReportPrecedenceLoop(_DWORD *orderList)
{
  _DWORD *i; // ecx
  _DWORD *j; // edi
  int supportList; // ebx
  _DWORD *supportedOrder; // edx
  _DWORD *freedLink; // eax
  int v6; // eax
  _DWORD *freeListEntry; // esi
  _DWORD *newLink; // eax
  _DWORD *k; // ebx
  int *m; // esi
  int v11; // ecx
  int v12; // ecx

  for ( i = orderList; orderList; orderList = (_DWORD *)orderList[3] )
    orderList[1] = 0;
  for ( j = i; j; j = (_DWORD *)j[3] )
  {
    if ( j[1] )
    {
      v6 = j[2];
      supportList = *(_DWORD *)(v6 + 4);
      *(_DWORD *)(v6 + 4) = 0;
    }
    else
    {
      supportList = j[2];
      j[2] = 0;
    }
    while ( supportList )
    {
      supportedOrder = Class_FindClassLinkNode(i, **(_DWORD **)supportList);
      if ( !supportedOrder[1] )
      {
        freeListEntry = *(_DWORD **)(g_ClipsMemoryTable + 32);
        if ( freeListEntry )
        {
          g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
          *(_DWORD *)(g_ClipsMemoryTable + 32) = *freeListEntry;
          newLink = (_DWORD *)g_ClipsMemFreeListTemp;
        }
        else
        {
          newLink = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)8);
        }
        *newLink = j;
        newLink[1] = supportedOrder[2];
        supportedOrder[1] = 1;
        supportedOrder[2] = newLink;
      }
      freedLink = (_DWORD *)supportList;
      supportList = *(_DWORD *)(supportList + 4);
      g_ClipsMemFreeListTemp = (int)freedLink;
      *freedLink = *(_DWORD *)(g_ClipsMemoryTable + 32);
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
signed int  Class_PrintClassNameList(int logicalName, int headerMessage, int *classLinks)
{
  int v3; // ecx

  v3 = logicalName;
  if ( headerMessage )
    Output_Write(logicalName, headerMessage, logicalName);
  while ( classLinks )
  {
    Output_Write(v3, (int)asc_50E6E8, v3);
    Class_PrintName(*classLinks, 0);
    classLinks = (int *)classLinks[1];
  }
  return Output_Write(v3, (int)asc_50E840, v3);
}
// 4E3415: variable 'v3' is possibly undefined

//----- (004E3440) --------------------------------------------------------
int * Class_ParseSlot(
        char *readSource,
        _DWORD *slotList,
        int multiSlot,
        unsigned __int16 *precedenceList,
        double a5,
        int fieldSlot)
{
  int slot; // esi
  int *result; // eax
  _BYTE *v11; // ecx
  int insertedList; // ebp
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int v18; // ebx
  char *v19; // eax
  int parseStatus; // eax
  __int16 *v21; // ecx
  char slotFlagsByte; // cl
  int v23; // ecx
  signed int accessFacet; // eax
  int v25; // ecx
  signed int storageFacet; // eax
  int v27; // ecx
  signed int propagationFacet; // eax
  int v29; // ecx
  signed int sourceFacet; // eax
  int v31; // ecx
  signed int matchFacet; // eax
  int v33; // ecx
  signed int visibilityFacet; // eax
  int v35; // ecx
  signed int createAccessorFacet; // eax
  signed int overrideFacet; // eax
  int v38; // ecx
  int v39; // eax
  __int16 parsedConstraint; // [esp+0h] [ebp-1Ch] BYREF
  int overrideMessageSymbol; // [esp+4h] [ebp-18h] BYREF
  unsigned __int16 *savedPrecList; // [esp+8h] [ebp-14h]
  char specbits[16]; // [esp+Ch] [ebp-10h] BYREF

  savedPrecList = precedenceList;
  IO_OutWriteToken(asc_50E844);
  specbits[1] = 0;
  specbits[0] = 0;
  Parser_NextToken((int)readSource, (int)&g_ParserCurrentTokenType);
  if ( g_ParserCurrentTokenType != 2 || g_ClipsParserTokenValue == g_Symbol_IsA || g_ClipsParserTokenValue == g_Clips_NameSymbol )
  {
    Class_DeleteSlotList((int)slotList);
    Parser_ReportSyntaxError();
    return 0;
  }
  slot = Class_NewSlot((_DWORD *)g_ClipsParserTokenValue);
  result = Class_InsertSlot(slotList, slot);
  insertedList = (int)result;
  if ( !result )
    return result;
  if ( multiSlot )
    *v11 |= 2u;
  if ( fieldSlot )
    specbits[0] |= 2u;
  Parser_NextToken((int)readSource, (int)&g_ParserCurrentTokenType);
  Rules_IncrementIndentDepth(3);
  Rules_ResetConstraintParsedFlags(&parsedConstraint);
  if ( g_ParserCurrentTokenType == 100 )
  {
    while ( 1 )
    {
      IO_OutNewline();
      AST_Append(v14, v13);
      IO_OutWriteToken(asc_50E858);
      Parser_NextToken((int)readSource, v15);
      if ( g_ParserCurrentTokenType != 2 )
        goto LABEL_11;
      if ( !strcmp_(v16, aDefault_2) )
        break;
      if ( !strcmp_(v17, aDefaultDynam_1) )
      {
        v18 = slot;
        BYTE1(v17) = specbits[0] | 0x80;
        v19 = readSource;
        specbits[0] |= 0x80u;
        goto LABEL_18;
      }
      if ( !strcmp_(v17, aAccess) )
      {
        accessFacet = Class_ParseSimpleFacet(
                (int)readSource,
                (int)specbits,
                2,
                (int)aAccess,
                (int)aReadWrite,
                (int)aReadOnly,
                (int)aInitializeOnly,
                0,
                0);
        switch ( accessFacet )
        {
          case -1:
            goto LABEL_12;
          case 1:
            *(_BYTE *)slot |= 0x10u;
            break;
          case 2:
            *(_BYTE *)slot |= 0x20u;
            break;
        }
      }
      else if ( !strcmp_(v23, aStorage) )
      {
        storageFacet = Class_ParseSimpleFacet((int)readSource, (int)specbits, 0, (int)aStorage, (int)aLocal_0, (int)aShared, 0, 0, 0);
        if ( storageFacet == -1 )
          goto LABEL_12;
        *(_BYTE *)slot &= ~1u;
        *(_DWORD *)slot |= storageFacet & 1;
      }
      else if ( !strcmp_(v25, aPropagation) )
      {
        propagationFacet = Class_ParseSimpleFacet((int)readSource, (int)specbits, 3, (int)aPropagation, (int)aInherit_2, (int)aNoInherit, 0, 0, 0);
        if ( propagationFacet == -1 )
          goto LABEL_12;
        *(_BYTE *)slot &= ~8u;
        *(_DWORD *)slot |= 8 * (propagationFacet & 1);
      }
      else if ( !strcmp_(v27, aSource) )
      {
        sourceFacet = Class_ParseSimpleFacet((int)readSource, (int)specbits, 4, (int)aSource, (int)aExclusive, (int)aComposite, 0, 0, 0);
        if ( sourceFacet == -1 )
          goto LABEL_12;
        *(_BYTE *)slot &= ~4u;
        *(_DWORD *)slot |= 4 * (sourceFacet & 1);
      }
      else if ( !strcmp_(v29, aPatternMatch_1) )
      {
        matchFacet = Class_ParseSimpleFacet((int)readSource, (int)specbits, 5, (int)aPatternMatch_1, (int)aNonReactive_0, (int)aReactive_0, 0, 0, 0);
        if ( matchFacet == -1 )
          goto LABEL_12;
        *(_BYTE *)(slot + 1) &= ~2u;
        *(_DWORD *)slot |= (matchFacet & 1) << 9;
      }
      else if ( !strcmp_(v31, aVisibility) )
      {
        visibilityFacet = Class_ParseSimpleFacet((int)readSource, (int)specbits, 8, (int)aVisibility, (int)aPrivate, (int)aPublic, 0, 0, 0);
        if ( visibilityFacet == -1 )
          goto LABEL_12;
        *(_BYTE *)(slot + 1) &= ~4u;
        *(_DWORD *)slot |= (visibilityFacet & 1) << 10;
      }
      else if ( !strcmp_(v33, aCreateAccessor) )
      {
        createAccessorFacet = Class_ParseSimpleFacet(
                (int)readSource,
                (int)specbits,
                9,
                (int)aCreateAccessor,
                (int)aRead_0,
                (int)aWrite,
                (int)aReadWrite,
                (int)aNone_2,
                0);
        if ( createAccessorFacet == -1 )
          goto LABEL_12;
        if ( !createAccessorFacet || createAccessorFacet == 2 )
          *(_BYTE *)(slot + 1) |= 8u;
        if ( createAccessorFacet == 1 || createAccessorFacet == 2 )
          *(_BYTE *)(slot + 1) |= 0x10u;
      }
      else
      {
        if ( strcmp_(v35, aOverrideMessag) )
        {
          if ( !Rules_IsConstraintAttributeKeyword(*(_DWORD *)(g_ClipsParserTokenValue + 16)) )
            goto LABEL_11;
          parseStatus = Rules_ParseStandardConstraintAttribute(readSource, *(const char **)(g_ClipsParserTokenValue + 16), &parsedConstraint, *(_DWORD *)(slot + 20), 1);
          goto LABEL_19;
        }
        overrideFacet = Class_ParseSimpleFacet((int)readSource, (int)specbits, 10, (int)aOverrideMessag, 0, 0, 0, (int)aDefault_3, &overrideMessageSymbol);
        if ( overrideFacet == -1 )
          goto LABEL_12;
        if ( overrideFacet == 4 )
        {
          Rules_DecrementSymbolCount(*(_DWORD *)(slot + 12), v38);
          v39 = overrideMessageSymbol;
          *(_DWORD *)(slot + 12) = overrideMessageSymbol;
          ++*(_DWORD *)(v39 + 4);
        }
        *(_BYTE *)(slot + 1) |= 0x20u;
      }
LABEL_20:
      Parser_NextToken((int)readSource, (int)&g_ParserCurrentTokenType);
      if ( g_ParserCurrentTokenType != 100 )
        goto LABEL_21;
    }
    v18 = slot;
    v19 = readSource;
LABEL_18:
    parseStatus = Class_ParseDefaultFacet((int)v19, specbits, v17, v18, a5);
LABEL_19:
    if ( !parseStatus )
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
    Class_DeleteSlotList(insertedList);
    return 0;
  }
  if ( (*(_BYTE *)slot & 4) != 0 )
    Class_BuildCompositeFacets(slot, savedPrecList, (int)&parsedConstraint, specbits);
  if ( !Class_CheckForFacetConflicts(slot, (int)&parsedConstraint) || !Rules_CheckConstraintParseConflicts(*(_DWORD *)(slot + 20), v21) || !Class_EvaluateSlotDefaultValue((int *)slot, specbits, a5) )
    goto LABEL_12;
  slotFlagsByte = *(_BYTE *)slot;
  if ( (*(_BYTE *)slot & 0x40) == 0 && (slotFlagsByte & 0x10) != 0 && (slotFlagsByte & 0x20) == 0 )
    *(_BYTE *)slot = slotFlagsByte | 1;
  *(_DWORD *)(slot + 20) = AST_InternNode(*(_DWORD **)(slot + 20));
  Rules_DecrementIndentDepth(3);
  return (int *)insertedList;
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
  int theSlot; // eax
  int v7; // edx

  for ( i = result; i; *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp )
  {
    Class_ReleaseSlotName(*(_DWORD **)(*(_DWORD *)i + 8));
    Rules_DecrementSymbolCount(*(_DWORD *)(*(_DWORD *)v2 + 12), v3);
    AST_DecrementNodeRefCount(*(_DWORD **)(*(_DWORD *)v4 + 20));
    theSlot = *(_DWORD *)v5;
    if ( (**(_BYTE **)v5 & 0x40) != 0 )
    {
      AST_DeinstallNodeChain(*(__int16 **)(theSlot + 16));
      AST_FreePackedNodeChain(*(_DWORD *)(*(_DWORD *)v7 + 16));
    }
    else if ( *(_DWORD *)(theSlot + 16) )
    {
      Rules_ValueDeinstall(*(_DWORD *)(theSlot + 16), i);
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
int  Class_NewSlot(_DWORD *slotNameSymbol)
{
  _DWORD *freeListEntry; // edx
  signed int slot; // ecx
  __int16 v4; // dx
  int parseNode; // eax
  int v6; // ecx
  int v7; // edx
  unsigned int *slotNameRecord; // eax
  int v9; // ecx
  unsigned int overrideMessage; // eax

  freeListEntry = *(_DWORD **)(g_ClipsMemoryTable + 176);
  if ( freeListEntry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 176);
    *(_DWORD *)(g_ClipsMemoryTable + 176) = *freeListEntry;
    slot = g_ClipsMemFreeListTemp;
  }
  else
  {
    slot = Mem_HeapAllocWithRetry((_DWORD *)0x2C);
  }
  *(_DWORD *)(slot + 24) = 0;
  v4 = *(_WORD *)slot;
  *(_DWORD *)(slot + 4) = 0;
  *(_DWORD *)(slot + 16) = 0;
  *(_WORD *)slot = v4 | 0x240;
  *(_WORD *)slot = v4 & 0xC000 | 0x240;
  parseNode = Rules_CreateLHSParseNode();
  *(_DWORD *)(v6 + 20) = parseNode;
  slotNameRecord = Class_InternSlotName(slotNameSymbol, v7, 0);
  *(_DWORD *)(v9 + 8) = slotNameRecord;
  overrideMessage = slotNameRecord[4];
  *(_DWORD *)(v9 + 12) = overrideMessage;
  ++*(_DWORD *)(overrideMessage + 4);
  return v9;
}
// 4E3AAF: variable 'v6' is possibly undefined
// 4E3AB4: variable 'v7' is possibly undefined
// 4E3AB9: variable 'v9' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004E3AE0) --------------------------------------------------------
int * Class_InsertSlot(_DWORD *slotList, int theSlot)
{
  int v3; // ecx
  _DWORD *freeListEntry; // edx
  int *result; // eax
  int newLink; // esi
  _DWORD *scanLink; // eax
  _DWORD *prevLink; // edx
  int v9; // edx
  int v10; // ecx

  v3 = theSlot;
  freeListEntry = *(_DWORD **)(g_ClipsMemoryTable + 32);
  if ( freeListEntry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
    *(_DWORD *)(g_ClipsMemoryTable + 32) = *freeListEntry;
    result = (int *)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = (int *)Mem_HeapAllocWithRetry((_DWORD *)8);
  }
  result[1] = 0;
  newLink = (int)result;
  *result = v3;
  if ( slotList )
  {
    scanLink = slotList;
    while ( *(_DWORD *)(v3 + 8) != *(_DWORD *)(*scanLink + 8) )
    {
      prevLink = scanLink;
      scanLink = (_DWORD *)scanLink[1];
      if ( !scanLink )
      {
        prevLink[1] = newLink;
        return slotList;
      }
    }
    *(_DWORD *)(newLink + 4) = slotList;
    Class_DeleteSlotList(newLink);
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
        int readSource,
        int specbits,
        signed int facetBit,
        int facetName,
        int value1,
        int value2,
        int value3,
        int varName,
        _DWORD *facetSymbolicValue)
{
  _BYTE *specbitBytePtr; // ebx
  int bitMask; // eax
  int v13; // edx
  int v14; // ecx
  int rtnCode; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx

  specbitBytePtr = (_BYTE *)(((facetBit - (__CFSHL__(facetBit >> 31, 3) + 8 * (facetBit >> 31))) >> 3) + specbits);
  bitMask = 1 << (facetBit % 8);
  if ( (*specbitBytePtr & (unsigned __int8)bitMask) != 0 )
  {
    Rules_PrintErrorID((int)aClsltpsr, 2, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], facetName, v17);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFacetAlreadySp, v18);
    return -1;
  }
  *specbitBytePtr |= bitMask;
  IO_OutWriteToken(asc_50E844);
  Parser_NextToken(readSource, v13);
  if ( g_ParserCurrentTokenType == 15 )
  {
    if ( varName && !strcmp_(v14, varName) )
      goto LABEL_5;
  }
  else if ( g_ParserCurrentTokenType == 2 )
  {
    if ( facetSymbolicValue )
    {
      *facetSymbolicValue = g_ClipsParserTokenValue;
      goto LABEL_5;
    }
    if ( !strcmp_(v14, value1) || !strcmp_(v19, value2) || value3 && !strcmp_(v20, value3) )
    {
LABEL_5:
      Parser_NextToken(readSource, (int)&g_ParserCurrentTokenType);
      if ( g_ParserCurrentTokenType == 101 )
        return rtnCode;
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
signed int  Class_ParseDefaultFacet(int readSource, _BYTE *specbits, int a3, int theSlot, double a5)
{
  _DWORD *defaultList; // eax
  int v8; // ecx
  int v9; // edx
  int parseError; // [esp+0h] [ebp-18h] BYREF
  int noneExists; // [esp+4h] [ebp-14h] BYREF
  _DWORD deriveExists[4]; // [esp+8h] [ebp-10h] BYREF

  deriveExists[3] = a3;
  if ( (*specbits & 0x40) != 0 )
  {
    Rules_PrintErrorID((int)aClsltpsr, 2, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDefaultFacetAl, v8);
    return 0;
  }
  *specbits |= 0x40u;
  parseError = 0;
  defaultList = (_DWORD *)Rules_ParseDefaultAttribute(readSource, 1, 0, *specbits & 0x80, a5, &noneExists, deriveExists, &parseError);
  if ( parseError == 1 )
    return 0;
  if ( noneExists || deriveExists[0] )
  {
    if ( !noneExists )
    {
      *specbits &= ~0x40u;
      return 1;
    }
    *(_WORD *)theSlot |= 0x180u;
  }
  else
  {
    *(_DWORD *)(theSlot + 16) = AST_PackNodeChain(defaultList);
    AST_Free(v9);
    AST_InstallNodeChain(*(__int16 **)(theSlot + 16));
    *(_BYTE *)theSlot |= 0x80u;
  }
  return 1;
}
// 4E3D9D: variable 'v8' is possibly undefined
// 4E3DB7: variable 'v9' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004E3DE0) --------------------------------------------------------
__int16  Class_BuildCompositeFacets(int slot, unsigned __int16 *precedenceList, int parsedConstraint, _BYTE *specbits)
{
  unsigned int superIndex; // ecx
  int arrayOffset; // ebx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  __int16 *packedDefault; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  _BYTE *candidateSlot; // eax
  _DWORD *freeListEntry; // edi
  void *defaultCopy; // eax
  _BYTE *compositeSlot; // [esp+8h] [ebp-Ch]

  superIndex = 1;
  arrayOffset = 4;
  while ( 1 )
  {
    LOWORD(v8) = *precedenceList;
    if ( superIndex >= *precedenceList )
      break;
    candidateSlot = (_BYTE *)Class_FindSlotBySymbol(*(_DWORD *)(arrayOffset + *(_DWORD *)(precedenceList + 1)), *(_DWORD *)(*(_DWORD *)(slot + 8) + 12));
    compositeSlot = candidateSlot;
    if ( candidateSlot )
    {
      v8 = (*candidateSlot & 8) == 0;
      if ( v8 )
        break;
      arrayOffset += 4;
      ++superIndex;
    }
    else
    {
      arrayOffset += 4;
      ++superIndex;
    }
  }
  if ( compositeSlot )
  {
    if ( *(char *)slot >= 0 && (char)*compositeSlot < 0 )
    {
      v9 = *(_DWORD *)compositeSlot;
      *(_BYTE *)slot &= ~0x40u;
      *(_DWORD *)slot |= v9 & 0x40;
      LOBYTE(superIndex) = *(_BYTE *)(slot + 1) & 0xFE;
      v10 = *(_DWORD *)compositeSlot;
      *(_BYTE *)(slot + 1) = superIndex;
      *(_DWORD *)slot |= v10 & 0x100;
      BYTE1(superIndex) = *(_BYTE *)slot | 0x80;
      *(_BYTE *)slot = BYTE1(superIndex);
      if ( *((_DWORD *)compositeSlot + 4) )
      {
        if ( (superIndex & 0x4000) != 0 )
        {
          packedDefault = (__int16 *)AST_PackNodeChain(*((_DWORD **)compositeSlot + 4));
          *(_DWORD *)(slot + 16) = packedDefault;
          AST_InstallNodeChain(packedDefault);
        }
        else
        {
          freeListEntry = *(_DWORD **)(g_ClipsMemoryTable + 96);
          if ( freeListEntry )
          {
            g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 96);
            *(_DWORD *)(g_ClipsMemoryTable + 96) = *freeListEntry;
            defaultCopy = (void *)g_ClipsMemFreeListTemp;
          }
          else
          {
            defaultCopy = (void *)Mem_HeapAllocWithRetry((_DWORD *)0x18);
          }
          *(_DWORD *)(slot + 16) = defaultCopy;
          qmemcpy(defaultCopy, *((const void **)compositeSlot + 4), 0x18u);
          Rules_ValueInstall(*(_DWORD *)(slot + 16), 0);
        }
      }
    }
    if ( (*specbits & 2) == 0 )
    {
      v12 = *(_DWORD *)compositeSlot;
      *(_BYTE *)slot &= ~2u;
      *(_DWORD *)slot |= v12 & 2;
    }
    if ( (*specbits & 1) == 0 )
    {
      v13 = *(_DWORD *)compositeSlot;
      *(_BYTE *)slot &= ~1u;
      *(_DWORD *)slot |= v13 & 1;
    }
    if ( (*specbits & 4) == 0 )
    {
      BYTE1(superIndex) = *(_BYTE *)slot & 0xEF;
      v14 = *(_DWORD *)compositeSlot;
      *(_BYTE *)slot = BYTE1(superIndex);
      *(_DWORD *)slot |= v14 & 0x10;
      v15 = *(_DWORD *)compositeSlot;
      *(_BYTE *)slot &= ~0x20u;
      *(_DWORD *)slot |= v15 & 0x20;
    }
    if ( (*specbits & 0x20) == 0 )
    {
      v16 = *(_DWORD *)compositeSlot;
      *(_BYTE *)(slot + 1) &= ~2u;
      *(_DWORD *)slot |= v16 & 0x200;
    }
    if ( (specbits[1] & 1) == 0 )
    {
      LOBYTE(superIndex) = *(_BYTE *)(slot + 1) & 0xFB;
      v17 = *(_DWORD *)compositeSlot;
      *(_BYTE *)(slot + 1) = superIndex;
      *(_DWORD *)slot |= v17 & 0x400;
    }
    if ( (specbits[1] & 2) == 0 )
    {
      v18 = *(_DWORD *)compositeSlot;
      *(_BYTE *)(slot + 1) &= ~8u;
      *(_DWORD *)slot |= v18 & 0x800;
      v19 = *(_DWORD *)compositeSlot;
      *(_BYTE *)(slot + 1) &= ~0x10u;
      *(_DWORD *)slot |= v19 & 0x1000;
    }
    if ( (specbits[1] & 4) == 0 && (compositeSlot[1] & 0x20) != 0 )
    {
      Rules_DecrementSymbolCount(*(_DWORD *)(slot + 12), superIndex);
      v20 = *((_DWORD *)compositeSlot + 3);
      *(_DWORD *)(slot + 12) = v20;
      ++*(_DWORD *)(v20 + 4);
      *(_BYTE *)(slot + 1) |= 0x20u;
    }
    LOWORD(v8) = Rules_OverlayConstraint(parsedConstraint, *(_DWORD *)(slot + 20), *((int **)compositeSlot + 5));
  }
  return v8;
}
// 4E3E0C: variable 'v27' is possibly undefined
// 4E3F75: variable 'v6' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004E4040) --------------------------------------------------------
signed int  Class_CheckForFacetConflicts(int slotDesc, int parsedConstraints)
{
  int v2; // ecx
  int v3; // ecx
  int *minIntValue; // eax
  signed int minExprNode; // eax
  int v6; // ecx
  int *maxIntValue; // eax
  signed int maxExprNode; // eax
  char accessBits; // dl
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx

  v2 = slotDesc;
  if ( (*(_BYTE *)slotDesc & 2) == 0 )
  {
    if ( (*(_BYTE *)(parsedConstraints + 1) & 4) != 0 )
    {
      Rules_PrintErrorID((int)aClsltpsr, 3, 1);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCardinalityFac, v11);
      return 0;
    }
    AST_Free(*(_DWORD *)(*(_DWORD *)(slotDesc + 20) + 18));
    AST_Free(*(_DWORD *)(*(_DWORD *)(v3 + 20) + 22));
    minIntValue = Rules_AddIntegerValue(1);
    minExprNode = AST_NewNode(1, (int)minIntValue);
    *(_DWORD *)(*(_DWORD *)(v6 + 20) + 18) = minExprNode;
    maxIntValue = Rules_AddIntegerValue(1);
    maxExprNode = AST_NewNode(1, (int)maxIntValue);
    *(_DWORD *)(*(_DWORD *)(v2 + 20) + 22) = maxExprNode;
  }
  if ( (*(_BYTE *)(v2 + 1) & 1) != 0 && (*(_BYTE *)v2 & 0x10) != 0 )
  {
    Rules_PrintErrorID((int)aClsltpsr, 4, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aReadOnlySlotsM, v12);
    return 0;
  }
  else if ( (*(_BYTE *)v2 & 0x10) != 0 && ((accessBits = *(_BYTE *)(v2 + 1), (accessBits & 0x10) != 0) || (accessBits & 0x20) != 0) )
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
signed int  Class_EvaluateSlotDefaultValue(int *slotDesc, char *specBits, double a3)
{
  _DWORD *freeListNode; // ecx
  _DWORD *defaultBuffer; // eax
  int slotFlags; // ebx
  int v7; // ecx
  int savedGuardFlag; // edi
  int v10; // edx
  int v11; // ecx
  int evalStatus; // edx
  int v13; // ecx
  int v14; // edx
  _DWORD *freeNode; // ebx
  void *valueCopy; // eax
  signed int violationCode; // esi
  int v18; // ecx
  _DWORD defaultValue[11]; // [esp+0h] [ebp-2Ch] BYREF

  if ( *specBits >= 0 )
    *(_BYTE *)slotDesc &= ~0x40u;
  if ( (*((_BYTE *)slotDesc + 1) & 1) != 0 )
    return 1;
  if ( (*(_BYTE *)slotDesc & 0x40) != 0 )
  {
    if ( !Rules_StaticConstraintCheckingEnabled() )
      return 1;
    violationCode = Rules_CheckFieldExprListAgainstConstraint((int *)slotDesc[4], slotDesc[5]);
    if ( !violationCode )
      return 1;
    Rules_PrintErrorID((int)aCstrnchk_3, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpressionFo_0, (int)aDynamicDefault);
    Instance_PrintSlotErrorContext((int)g_IO_LogicalNameTable_WError[0], (int)slotDesc, v18, 0);
    Rules_PrintConstraintViolationMessage(0, 0, 0, 0, 0, 0, violationCode, slotDesc[5], 0);
    return 0;
  }
  else
  {
    if ( (*specBits & 0x40) == 0 )
    {
      if ( *(char *)slotDesc < 0 )
        return 1;
      freeListNode = *(_DWORD **)(g_ClipsMemoryTable + 96);
      if ( freeListNode )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 96);
        *(_DWORD *)(g_ClipsMemoryTable + 96) = *freeListNode;
        defaultBuffer = (_DWORD *)g_ClipsMemFreeListTemp;
      }
      else
      {
        defaultBuffer = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x18);
      }
      slotFlags = *slotDesc;
      slotDesc[4] = (int)defaultBuffer;
      Rules_DeriveDefaultFromConstraints((char *)slotDesc[5], defaultBuffer, (unsigned int)(slotFlags << 30) >> 31);
LABEL_10:
      Rules_ValueInstall(slotDesc[4], v7);
      return 1;
    }
    savedGuardFlag = Rules_GetReentryGuardFlag();
    Rules_SetReentryGuardFlag(1);
    Rules_StaticConstraintCheckingEnabled();
    Rules_SetDynamicConstraintChecking(v11, v10);
    evalStatus = Parser_ParseSlotDefaultOrRestriction((unsigned int)(*slotDesc << 30) >> 31, slotDesc[4], defaultValue, a3);
    if ( evalStatus )
      evalStatus = Instance_ValidateSlotValueConstraints(defaultValue, (int)slotDesc, 0);
    Rules_SetDynamicConstraintChecking(v13, evalStatus);
    Rules_SetReentryGuardFlag(savedGuardFlag);
    if ( v14 )
    {
      AST_DeinstallNodeChain((__int16 *)slotDesc[4]);
      AST_FreePackedNodeChain(slotDesc[4]);
      freeNode = *(_DWORD **)(g_ClipsMemoryTable + 96);
      if ( freeNode )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 96);
        *(_DWORD *)(g_ClipsMemoryTable + 96) = *freeNode;
        valueCopy = (void *)g_ClipsMemFreeListTemp;
      }
      else
      {
        valueCopy = (void *)Mem_HeapAllocWithRetry((_DWORD *)0x18);
      }
      slotDesc[4] = (int)valueCopy;
      qmemcpy(valueCopy, defaultValue, 0x18u);
      v7 = 0;
      goto LABEL_10;
    }
    *(_BYTE *)slotDesc |= 0x40u;
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
_DWORD * CRT_ResizeHeapBlockLocked(_DWORD *heapBlock, unsigned int newSize, unsigned int a3)
{
  unsigned int v6[4]; // [esp-Ch] [ebp-10h] BYREF

  v6[2] = a3;
  g_CRT_StaticLock2AcquireHook();
  if ( CRT_ResizeHeapBlockInPlace(__DS__, heapBlock, v6, newSize, heapBlock) )
  {
    g_CRT_StaticLock2ReleaseHook();
    return 0;
  }
  else
  {
    g_CRT_StaticLock2ReleaseHook();
    return heapBlock;
  }
}
// 485379: using guessed type _DWORD nullsub_8();
// 51A584: using guessed type _DWORD (*off_51A584)();
// 51A58C: using guessed type _DWORD (*off_51A58C)();

//----- (004E4CA7) --------------------------------------------------------
signed int  CRT_ResizeHeapBlockInPlace(
        __int16 dataSegment,
        _DWORD *blockPtr,
        unsigned int *bytesNeededPtr,
        unsigned int requestedSize,
        _DWORD *i)
{
  unsigned int alignedSize; // eax
  unsigned int blockSize; // edx
  unsigned int growAmount; // eax
  unsigned int *j; // ebx
  unsigned int neighborSize; // ebp
  int v11; // ebp
  unsigned int *heapRover; // edx
  unsigned int leftoverSize; // eax
  unsigned int *splitBlock; // ebx
  unsigned int shrinkAmount; // edx
  unsigned int newHeaderSize; // ebx
  unsigned int *blockHeader; // [esp+4h] [ebp-18h]
  unsigned int prevFreeLink; // [esp+8h] [ebp-14h]
  unsigned int nextFreeLink; // [esp+Ch] [ebp-10h]

  alignedSize = requestedSize + 11;
  LOBYTE(alignedSize) = (requestedSize + 11) & 0xF8;
  if ( alignedSize >= requestedSize )
  {
    if ( alignedSize < 0x10 )
      alignedSize = 16;
  }
  else
  {
    alignedSize = -1;
  }
  blockHeader = blockPtr - 1;
  blockSize = *(blockPtr - 1);
  LOBYTE(blockSize) = blockSize & 0xFE;
  if ( alignedSize <= blockSize )
  {
    shrinkAmount = blockSize - alignedSize;
    if ( shrinkAmount >= 0x10 )
    {
      newHeaderSize = alignedSize;
      LOBYTE(newHeaderSize) = alignedSize | 1;
      LOBYTE(shrinkAmount) = shrinkAmount | 1;
      *blockHeader = newHeaderSize;
      *(unsigned int *)((char *)blockHeader + alignedSize) = shrinkAmount;
      if ( __DS__ == dataSegment )
      {
        for ( i = (_DWORD *)g_CRT_HeapSegmentListHead; i[2] && (i > blockPtr || (_DWORD *)((char *)i + *i) <= blockPtr); i = (_DWORD *)i[2] )
          ;
      }
      ++i[6];
      nfree_(blockHeader);
    }
    return 0;
  }
  else
  {
    growAmount = alignedSize - blockSize;
    for ( j = (unsigned int *)((char *)blockHeader + blockSize); ; j = (unsigned int *)((char *)j + neighborSize) )
    {
      *bytesNeededPtr = growAmount;
      neighborSize = *j;
      if ( *j == -1 )
        return 2;
      if ( (neighborSize & 1) != 0 )
        break;
      nextFreeLink = j[2];
      prevFreeLink = j[1];
      if ( __DS__ == dataSegment )
      {
        for ( i = (_DWORD *)g_CRT_HeapSegmentListHead; i[2] && (i > blockPtr || (_DWORD *)((char *)i + *i) <= blockPtr); i = (_DWORD *)i[2] )
          ;
      }
      heapRover = (unsigned int *)i[3];
      if ( j == heapRover )
        i[3] = heapRover[1];
      if ( neighborSize >= *bytesNeededPtr )
      {
        leftoverSize = neighborSize - *bytesNeededPtr;
        if ( leftoverSize >= 0x10 )
        {
          splitBlock = (unsigned int *)((char *)j + *bytesNeededPtr);
          *splitBlock = leftoverSize;
          splitBlock[1] = prevFreeLink;
          splitBlock[2] = nextFreeLink;
          *(_DWORD *)(prevFreeLink + 8) = splitBlock;
          *(_DWORD *)(nextFreeLink + 4) = splitBlock;
          v11 = 0;
          *blockHeader += *bytesNeededPtr;
          g_CRT_HeapCoalesceStateByte = 0;
          return v11;
        }
      }
      *(_DWORD *)(prevFreeLink + 8) = nextFreeLink;
      *(_DWORD *)(nextFreeLink + 4) = prevFreeLink;
      *blockHeader += neighborSize;
      --i[7];
      g_CRT_HeapCoalesceStateByte = 0;
      if ( neighborSize >= *bytesNeededPtr )
        return 0;
      growAmount = *bytesNeededPtr - neighborSize;
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
  int threadDataMgmtDisabled; // edx
  int alignedDataSize; // eax
  void *v4; // esp
  int threadDataBlock; // ecx
  HANDLE ownThreadHandle; // ebx
  int v8; // ecx
  _BYTE sehFrame[8]; // [esp+0h] [ebp-10h] BYREF
  void (*startAddress)(void); // [esp+8h] [ebp-8h]
  HANDLE hObject; // [esp+Ch] [ebp-4h]

  startAddress = *(void (**)(void))lpThreadParameter;
  threadDataMgmtDisabled = g_CrtThreadDataMgmtDisabledFlag;
  hObject = (HANDLE)**((_DWORD **)lpThreadParameter + 4);
  if ( g_CrtThreadDataMgmtDisabledFlag
    || (alignedDataSize = g_CRT_ThreadDataBlockSize + 3,
        LOBYTE(alignedDataSize) = (g_CRT_ThreadDataBlockSize + 3) & 0xFC,
        v4 = alloca(alignedDataSize),
        memset_(sehFrame, 0),
        *(_DWORD *)(threadDataBlock + 240) = g_CRT_ThreadDataBlockSize,
        CRT_CreateAndAttachThreadData(threadDataBlock, threadDataBlock)) )
  {
    ownThreadHandle = hObject;
    *(_DWORD *)(g_CrtThreadDataAccessor(v1, threadDataMgmtDisabled) + 222) = ownThreadHandle;
    SetEvent(*((HANDLE *)lpThreadParameter + 3));
    CRT_InstallUnhandledExceptionFilter((int)sehFrame, v8);
    g_CRT_ThreadStartupHook();
    startAddress();
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
HANDLE  CRT_BeginThread(int startAddress, int stackSize, int argList)
{
  int v3; // ecx
  HANDLE result; // eax
  DWORD CurrentThreadId; // eax
  CHAR eventName[32]; // [esp+0h] [ebp-50h] BYREF
  _DWORD Parameter[3]; // [esp+20h] [ebp-30h] BYREF
  HANDLE hHandle; // [esp+2Ch] [ebp-24h]
  HANDLE *v10; // [esp+30h] [ebp-20h]
  HANDLE Thread; // [esp+34h] [ebp-1Ch] BYREF
  DWORD ThreadId[6]; // [esp+38h] [ebp-18h] BYREF

  v3 = startAddress;
  if ( dwTlsIndex == -1 )
  {
    result = (HANDLE)CRT_AllocateTlsIndex();
    if ( !result )
      return result;
    CRT_InitializeThreadAndFileHandleHooks();
  }
  Parameter[0] = v3;
  Parameter[1] = argList;
  Parameter[2] = GetCurrentThread();
  strcpy(eventName, "__bgnthd");
  CurrentThreadId = GetCurrentThreadId();
  Str_FormatSignedRadixDigits(CurrentThreadId, &eventName[8], 0x10u);
  hHandle = CreateEventA(0, 0, 0, eventName);
  v10 = &Thread;
  Thread = CreateThread(0, (stackSize + 4095) & 0xFFFFF000, (LPTHREAD_START_ROUTINE)CRT_ThreadStartTrampoline, Parameter, 0, ThreadId);
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
_DWORD * AST_BuildClassHierarchyFieldAccessTest(_DWORD *fieldNode, int patternNode)
{
  int bottomChain; // edi
  _DWORD *pnTestTail; // ebp
  _DWORD *jnTestTail; // edi
  _DWORD *chainNode; // esi
  int v6; // ecx
  _DWORD *v7; // esi
  int referringNode; // ecx
  int v9; // edx
  _DWORD *crossPatternTest; // eax
  _DWORD *result; // eax
  _DWORD *intraPatternTest; // eax
  _DWORD *pnTests; // [esp+0h] [ebp-30h] BYREF
  _DWORD *jnTests; // [esp+4h] [ebp-2Ch] BYREF
  int v15; // [esp+8h] [ebp-28h]
  _DWORD *v16; // [esp+Ch] [ebp-24h]
  int homogeneousFlag; // [esp+10h] [ebp-20h]
  _DWORD *pnTestHead; // [esp+14h] [ebp-1Ch]
  _DWORD *i; // [esp+18h] [ebp-18h]

  v16 = fieldNode;
  v15 = patternNode;
  homogeneousFlag = 1;
  pnTests = 0;
  jnTests = 0;
  if ( !fieldNode )
  {
    Rules_ReportSystemError(0, 3);
    IO_RunRouterExitCallbacks();
  }
  bottomChain = v16[17];
  if ( bottomChain && *(_DWORD *)(bottomChain + 68) )
    homogeneousFlag = AST_IsFieldAccessHomogeneousAcrossHierarchy(v16[17], v16[7]);
  pnTestTail = 0;
  jnTestTail = 0;
  pnTestHead = 0;
  chainNode = (_DWORD *)v16[17];
  for ( i = 0; chainNode; chainNode = (_DWORD *)chainNode[17] )
  {
    AST_AccumulateFieldAccessTestChain(chainNode, homogeneousFlag, (signed int *)&jnTests, (signed int *)&pnTests);
    if ( pnTests )
    {
      if ( pnTestTail )
        *(_DWORD *)((char *)pnTestTail + 10) = pnTests;
      else
        pnTestHead = pnTests;
      pnTestTail = pnTests;
    }
    if ( jnTests )
    {
      if ( jnTestTail )
        *(_DWORD *)((char *)jnTestTail + 10) = jnTests;
      else
        i = jnTests;
      jnTestTail = jnTests;
    }
  }
  if ( pnTestHead && *(_DWORD *)((char *)pnTestHead + 10) )
  {
    pnTestHead = (_DWORD *)AST_NewNode(10, g_ClipsSymbolOr);
    *(_DWORD *)((char *)pnTestHead + 6) = v6;
  }
  v7 = i;
  if ( i && *(_DWORD *)((char *)i + 10) )
  {
    i = (_DWORD *)AST_NewNode(10, g_ClipsSymbolOr);
    *(_DWORD *)((char *)i + 6) = v7;
  }
  if ( *v16 == 16 || *v16 == 15 )
  {
    referringNode = v16[5];
    if ( referringNode )
    {
      v9 = v16[5];
      if ( *(_DWORD *)(referringNode + 28) == v16[7] )
      {
        intraPatternTest = (_DWORD *)AST_InvokeFieldAccessValidator((int)v16, (int)v16);
        pnTestHead = AST_MergeFieldAccessNodes(intraPatternTest, pnTestHead);
      }
      else if ( *(int *)(v9 + 28) > 0 )
      {
        crossPatternTest = (_DWORD *)AST_BuildCrossClassFieldAccessTest((int)v16, v9);
        i = AST_MergeFieldAccessNodes(crossPatternTest, i);
      }
    }
  }
  v16[13] = pnTestHead;
  result = AST_MergeFieldAccessNodes(*(_DWORD **)(v15 + 52), i);
  *(_DWORD *)(v15 + 52) = result;
  return result;
}
// 4E52B5: variable 'v6' is possibly undefined
// 54E664: using guessed type int dword_54E664;

//----- (004E53B0) --------------------------------------------------------
_DWORD * AST_AccumulateFieldAccessTestChain(_DWORD *result, int homogeneousFlag, signed int *jnTests, signed int *pnTests)
{
  int currentNode; // esi
  _DWORD *pnResult; // [esp+0h] [ebp-18h] BYREF
  _DWORD *jnResult; // [esp+4h] [ebp-14h] BYREF
  int homogeneousCopy; // [esp+8h] [ebp-10h]

  currentNode = (int)result;
  homogeneousCopy = homogeneousFlag;
  *pnTests = 0;
  *jnTests = 0;
  if ( result )
  {
    do
    {
      AST_DispatchFieldAccessNodeBuild(currentNode, homogeneousCopy, &jnResult, &pnResult);
      *pnTests = (signed int)AST_MergeFieldAccessNodes((_DWORD *)*pnTests, pnResult);
      result = AST_MergeFieldAccessNodes((_DWORD *)*jnTests, jnResult);
      *jnTests = (signed int)result;
      currentNode = *(_DWORD *)(currentNode + 64);
    }
    while ( currentNode );
  }
  return result;
}

//----- (004E5420) --------------------------------------------------------
int  AST_DispatchFieldAccessNodeBuild(int theNode, int homogeneousFlag, _DWORD *jnTestOut, _DWORD *pnTestOut)
{
  int result; // eax
  unsigned int nodeType; // edx
  _DWORD *v7; // ecx
  _DWORD *v8; // ecx
  _DWORD *v9; // ecx
  int referringNode; // eax
  _DWORD *v11; // ecx

  result = homogeneousFlag;
  *pnTestOut = 0;
  *jnTestOut = 0;
  nodeType = *(_DWORD *)theNode;
  if ( *(_DWORD *)theNode == 3 || nodeType == 2 || nodeType == 8 || nodeType < 2 )
  {
    if ( result == 1 )
    {
      result = AST_BuildFieldAccessNodePN(theNode);
      *pnTestOut = result;
    }
    else
    {
      result = AST_BuildFieldAccessNodeJN(theNode);
      *v7 = result;
    }
  }
  else
  {
    switch ( nodeType )
    {
      case 0x5Du:
        if ( result == 1 && AST_IsFieldPositionConsistent(*(_DWORD **)(theNode + 56), *(_DWORD *)(theNode + 28)) == 1 )
        {
          result = AST_BuildNegatedFieldAccessNodeJN(theNode);
          *pnTestOut = result;
        }
        else
        {
          result = AST_BuildNegatedFieldAccessNodePN(theNode);
          *v8 = result;
        }
        break;
      case 0x5Eu:
        if ( result == 1 && AST_IsFieldPositionConsistent(*(_DWORD **)(theNode + 56), *(_DWORD *)(theNode + 28)) == 1 )
        {
          result = AST_BuildFieldAccessComparisonNodeJN(theNode);
          *pnTestOut = result;
        }
        else
        {
          result = AST_BuildFieldAccessComparisonNodePN(theNode);
          *v9 = result;
        }
        break;
      case 0xFu:
      case 0x10u:
        if ( result == 1 && (referringNode = *(_DWORD *)(theNode + 20)) != 0 && *(_DWORD *)(referringNode + 28) == *(_DWORD *)(theNode + 28) )
        {
          result = AST_InvokeFieldAccessValidator(theNode, (int)jnTestOut);
          *pnTestOut = result;
        }
        else
        {
          result = AST_BuildCrossClassFieldAccessTest(theNode, *(_DWORD *)(theNode + 20));
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
int  AST_BuildFieldAccessNodePN(int theNode)
{
  int patternType; // eax
  int eqSymbol; // edx
  signed int callNode; // ebx
  int v5; // ecx
  _DWORD *valueNode; // ecx

  patternType = *(_DWORD *)(theNode + 24);
  if ( *(_DWORD *)(patternType + 48) )
    return (*(int (**)(void))(patternType + 48))();
  if ( (*(_BYTE *)(theNode + 8) & 1) != 0 )
    eqSymbol = g_ClipsSymbolNeq;
  else
    eqSymbol = g_ClipsSymbolEq;
  callNode = AST_NewNode(10, eqSymbol);
  *(_DWORD *)(callNode + 6) = (*(int (**)(void))(*(_DWORD *)(v5 + 24) + 56))();
  *(_DWORD *)(*(_DWORD *)(callNode + 6) + 10) = AST_NewNode(*valueNode, valueNode[1]);
  return callNode;
}
// 4E5536: variable 'v5' is possibly undefined
// 4E5544: variable 'v6' is possibly undefined
// 54E658: using guessed type int dword_54E658;
// 54E668: using guessed type int dword_54E668;

//----- (004E5570) --------------------------------------------------------
int  AST_BuildFieldAccessNodeJN(int theNode)
{
  int patternType; // eax
  int eqSymbol; // edx
  signed int callNode; // ebx
  int v5; // ecx
  _DWORD *valueNode; // ecx

  patternType = *(_DWORD *)(theNode + 24);
  if ( *(_DWORD *)(patternType + 32) )
    return (*(int (**)(void))(patternType + 32))();
  if ( (*(_BYTE *)(theNode + 8) & 1) != 0 )
    eqSymbol = g_ClipsSymbolNeq;
  else
    eqSymbol = g_ClipsSymbolEq;
  callNode = AST_NewNode(10, eqSymbol);
  *(_DWORD *)(callNode + 6) = (*(int (**)(void))(*(_DWORD *)(v5 + 24) + 40))();
  *(_DWORD *)(*(_DWORD *)(callNode + 6) + 10) = AST_NewNode(*valueNode, valueNode[1]);
  return callNode;
}
// 4E5596: variable 'v5' is possibly undefined
// 4E55A4: variable 'v6' is possibly undefined
// 54E658: using guessed type int dword_54E658;
// 54E668: using guessed type int dword_54E668;

//----- (004E55D0) --------------------------------------------------------
int  AST_BuildNegatedFieldAccessNodePN(int theNode)
{
  int result; // eax
  int v2; // edx
  int innerTest; // ecx

  result = AST_CloneFieldAccessSubtreePN(*(_DWORD *)(theNode + 56));
  if ( (*(_BYTE *)(v2 + 8) & 1) != 0 )
  {
    result = AST_NewNode(10, g_ClipsNotSymbol);
    *(_DWORD *)(result + 6) = innerTest;
  }
  return result;
}
// 4E55DE: variable 'v2' is possibly undefined
// 4E55F9: variable 'v3' is possibly undefined
// 54E660: using guessed type int dword_54E660;

//----- (004E5600) --------------------------------------------------------
int  AST_BuildNegatedFieldAccessNodeJN(int theNode)
{
  int result; // eax
  int v2; // edx
  int innerTest; // ecx

  result = AST_CloneFieldAccessSubtreeJN(*(_DWORD *)(theNode + 56));
  if ( (*(_BYTE *)(v2 + 8) & 1) != 0 )
  {
    result = AST_NewNode(10, g_ClipsNotSymbol);
    *(_DWORD *)(result + 6) = innerTest;
  }
  return result;
}
// 4E560E: variable 'v2' is possibly undefined
// 4E5629: variable 'v3' is possibly undefined
// 54E660: using guessed type int dword_54E660;

//----- (004E5630) --------------------------------------------------------
int  AST_BuildFieldAccessComparisonNodePN(int theField)
{
  int convertedExpr; // esi
  int v2; // ecx
  int compareSymbol; // edx
  int v4; // ecx
  __int64 v5; // rax

  convertedExpr = AST_CloneFieldAccessSubtreePN(*(_DWORD *)(theField + 56));
  if ( (*(_BYTE *)(v2 + 8) & 1) != 0 )
    compareSymbol = g_ClipsSymbolNeq;
  else
    compareSymbol = g_ClipsSymbolEq;
  AST_NewNode(10, compareSymbol);
  v5 = ((__int64 (*)(void))*(_DWORD *)(*(_DWORD *)(v4 + 24) + 40))();
  *(_DWORD *)(HIDWORD(v5) + 6) = v5;
  *(_DWORD *)(v5 + 10) = convertedExpr;
  return HIDWORD(v5);
}
// 4E5640: variable 'v2' is possibly undefined
// 4E5658: variable 'v4' is possibly undefined
// 54E658: using guessed type int dword_54E658;
// 54E668: using guessed type int dword_54E668;

//----- (004E5680) --------------------------------------------------------
int  AST_BuildFieldAccessComparisonNodeJN(int theField)
{
  int convertedExpr; // esi
  int v2; // ecx
  int compareSymbol; // edx
  int v4; // ecx
  __int64 v5; // rax

  convertedExpr = AST_CloneFieldAccessSubtreeJN(*(_DWORD *)(theField + 56));
  if ( (*(_BYTE *)(v2 + 8) & 1) != 0 )
    compareSymbol = g_ClipsSymbolNeq;
  else
    compareSymbol = g_ClipsSymbolEq;
  AST_NewNode(10, compareSymbol);
  v5 = ((__int64 (*)(void))*(_DWORD *)(*(_DWORD *)(v4 + 24) + 56))();
  *(_DWORD *)(HIDWORD(v5) + 6) = v5;
  *(_DWORD *)(v5 + 10) = convertedExpr;
  return HIDWORD(v5);
}
// 4E5690: variable 'v2' is possibly undefined
// 4E56A8: variable 'v4' is possibly undefined
// 54E658: using guessed type int dword_54E658;
// 54E668: using guessed type int dword_54E668;

//----- (004E56D0) --------------------------------------------------------
int  AST_CloneFieldAccessSubtreePN(int result)
{
  int currentNode; // edx
  _DWORD *freeListEntry; // ebx
  signed int newExpr; // ecx
  int nextArgExpr; // eax
  int v5; // ecx
  int v6; // edx
  int argListExpr; // eax
  _DWORD *v8; // edx
  int v9; // ecx
  int resultExpr; // ebx

  currentNode = result;
  if ( result )
  {
    freeListEntry = *(_DWORD **)(g_ClipsMemoryTable + 56);
    if ( freeListEntry )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 56);
      *(_DWORD *)(g_ClipsMemoryTable + 56) = *freeListEntry;
      newExpr = g_ClipsMemFreeListTemp;
    }
    else
    {
      newExpr = Mem_HeapAllocWithRetry((_DWORD *)0xE);
    }
    *(_WORD *)newExpr = *(_WORD *)currentNode;
    *(_DWORD *)(newExpr + 2) = *(_DWORD *)(currentNode + 4);
    nextArgExpr = AST_CloneFieldAccessSubtreePN(*(_DWORD *)(currentNode + 64));
    *(_DWORD *)(v5 + 10) = nextArgExpr;
    argListExpr = AST_CloneFieldAccessSubtreePN(*(_DWORD *)(v6 + 68));
    *(_DWORD *)(v9 + 6) = argListExpr;
    resultExpr = v9;
    if ( *v8 == 15 || *v8 == 16 )
    {
      (*(void (**)(void))(*(_DWORD *)(v8[5] + 24) + 36))();
    }
    else if ( *(_WORD *)v9 == 13 )
    {
      Defglobal_ResolveGlobalVariableReference(v9, v9);
      return resultExpr;
    }
    return resultExpr;
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
  int currentNode; // edx
  _DWORD *freeListEntry; // ebx
  signed int newExpr; // ecx
  int nextArgExpr; // eax
  int v5; // ecx
  int v6; // edx
  int argListExpr; // eax
  _DWORD *v8; // edx
  int v9; // ecx
  int resultExpr; // ebx

  currentNode = result;
  if ( result )
  {
    freeListEntry = *(_DWORD **)(g_ClipsMemoryTable + 56);
    if ( freeListEntry )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 56);
      *(_DWORD *)(g_ClipsMemoryTable + 56) = *freeListEntry;
      newExpr = g_ClipsMemFreeListTemp;
    }
    else
    {
      newExpr = Mem_HeapAllocWithRetry((_DWORD *)0xE);
    }
    *(_WORD *)newExpr = *(_WORD *)currentNode;
    *(_DWORD *)(newExpr + 2) = *(_DWORD *)(currentNode + 4);
    nextArgExpr = AST_CloneFieldAccessSubtreeJN(*(_DWORD *)(currentNode + 64));
    *(_DWORD *)(v5 + 10) = nextArgExpr;
    argListExpr = AST_CloneFieldAccessSubtreeJN(*(_DWORD *)(v6 + 68));
    *(_DWORD *)(v9 + 6) = argListExpr;
    resultExpr = v9;
    if ( *v8 == 15 || *v8 == 16 )
    {
      (*(void (**)(void))(*(_DWORD *)(v8[5] + 24) + 52))();
    }
    else if ( *(_WORD *)v9 == 13 )
    {
      Defglobal_ResolveGlobalVariableReference(v9, v9);
      return resultExpr;
    }
    return resultExpr;
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
int  AST_BuildCrossClassFieldAccessTest(int selfNode, int referringNode)
{
  int selfPatternType; // eax
  int referringPatternType; // edx
  int compareSymbol; // edx
  int v7; // ecx
  __int64 v8; // rax
  __int64 v9; // rax

  selfPatternType = *(_DWORD *)(selfNode + 24);
  if ( !*(_DWORD *)(selfPatternType + 44) )
    return 0;
  referringPatternType = *(_DWORD *)(referringNode + 24);
  if ( !*(_DWORD *)(referringPatternType + 44) )
    return 0;
  if ( *(_DWORD *)(selfPatternType + 44) == *(_DWORD *)(referringPatternType + 44) )
    return (*(int (**)(void))(selfPatternType + 44))();
  if ( (*(_BYTE *)(selfNode + 8) & 1) != 0 )
    compareSymbol = g_ClipsSymbolNeq;
  else
    compareSymbol = g_ClipsSymbolEq;
  AST_NewNode(10, compareSymbol);
  v8 = ((__int64 (*)(void))*(_DWORD *)(*(_DWORD *)(v7 + 24) + 40))();
  *(_DWORD *)(HIDWORD(v8) + 6) = v8;
  v9 = ((__int64 (*)(void))*(_DWORD *)(*(_DWORD *)(referringNode + 24) + 40))();
  *(_DWORD *)(*(_DWORD *)(HIDWORD(v9) + 6) + 10) = v9;
  return HIDWORD(v9);
}
// 4E5829: variable 'v7' is possibly undefined
// 54E658: using guessed type int dword_54E658;
// 54E668: using guessed type int dword_54E668;

//----- (004E5870) --------------------------------------------------------
int  AST_InvokeFieldAccessValidator(int theField, int jnTest)
{
  int patternType; // ecx

  patternType = *(_DWORD *)(theField + 24);
  if ( *(_DWORD *)(patternType + 60) )
    return (*(int (__cdecl **)(int))(patternType + 60))(jnTest);
  else
    return 0;
}

//----- (004E5890) --------------------------------------------------------
int  AST_IsFieldAccessHomogeneousAcrossHierarchy(int nodeChain, int whichPattern)
{
  int chainNode; // esi
  int fieldNode; // ecx
  int nodeType; // edx
  int result; // eax

  chainNode = nodeChain;
  if ( !nodeChain )
    return 1;
  while ( 1 )
  {
    fieldNode = chainNode;
    if ( chainNode )
      break;
LABEL_6:
    chainNode = *(_DWORD *)(chainNode + 68);
    if ( !chainNode )
      return 1;
  }
  while ( 1 )
  {
    nodeType = *(_DWORD *)fieldNode;
    if ( *(_DWORD *)fieldNode == 15 || nodeType == 16 )
      break;
    if ( nodeType == 93 || nodeType == 94 )
    {
      result = AST_IsFieldPositionConsistent(*(_DWORD **)(fieldNode + 56), whichPattern);
      if ( !result )
        return result;
    }
LABEL_5:
    fieldNode = *(_DWORD *)(fieldNode + 64);
    if ( !fieldNode )
      goto LABEL_6;
  }
  if ( whichPattern == *(_DWORD *)(*(_DWORD *)(fieldNode + 20) + 28) )
    goto LABEL_5;
  return 0;
}
// 4E58B0: variable 'v4' is possibly undefined

//----- (004E58F0) --------------------------------------------------------
int  AST_IsFieldPositionConsistent(_DWORD *theNode, int whichPattern)
{
  _DWORD *currentNode; // ecx
  int result; // eax
  int v5; // ecx

  currentNode = theNode;
  if ( !theNode )
    return 1;
  while ( *currentNode != 15 && *currentNode != 16 || whichPattern == *(_DWORD *)(currentNode[5] + 28) )
  {
    result = AST_IsFieldPositionConsistent(currentNode[17], whichPattern);
    if ( !result )
      return result;
    currentNode = *(_DWORD **)(v5 + 64);
    if ( !currentNode )
      return 1;
  }
  return 0;
}
// 4E5921: variable 'v5' is possibly undefined

//----- (004E5C90) --------------------------------------------------------
unsigned int  CRT_StrToXLong(unsigned __int8 *numStr, int *endPtr, int signedFlag, signed int requestedBase)
{
  signed int radix; // esi
  unsigned __int8 *i; // edx
  unsigned __int8 hexPrefixChar; // cl
  unsigned __int8 v9; // bh
  unsigned int value; // ebx
  int digitPtr; // edx
  unsigned int prevValue; // eax
  char signChar; // ch
  unsigned __int8 *digitsStart; // [esp+4h] [ebp-18h]
  int digit; // [esp+8h] [ebp-14h]
  int signedFlagSaved; // [esp+Ch] [ebp-10h]

  radix = requestedBase;
  signedFlagSaved = signedFlag;
  if ( endPtr )
    *endPtr = (int)numStr;
  for ( i = numStr; (IsTable[(unsigned __int8)(*i + 1)] & 2) != 0; ++i )
    ;
  BYTE1(signedFlag) = *i;
  if ( *i == 43 || BYTE1(signedFlag) == 45 )
    ++i;
  if ( requestedBase )
  {
    if ( requestedBase < 2 || requestedBase > 36 )
    {
      _set_errno_((int)numStr);
      return 0;
    }
    if ( requestedBase == 16 )
      goto LABEL_21;
  }
  else
  {
    if ( *i == 48 )
    {
      hexPrefixChar = i[1];
      if ( hexPrefixChar == 120 || hexPrefixChar == 88 )
      {
        radix = 16;
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
      radix = 8;
    else
      radix = 10;
  }
LABEL_25:
  digitsStart = i;
  LOBYTE(signedFlag) = 0;
  value = 0;
  while ( 1 )
  {
    digit = CRT_DigitCharToValue(*i, (int)i, signedFlag);
    if ( digit >= radix )
      break;
    if ( value > (unsigned int)g_StrToLongOverflowLimitTable[radix] )
      LOBYTE(signedFlag) = 1;
    prevValue = value;
    value = digit + radix * value;
    if ( value < prevValue )
      LOBYTE(signedFlag) = 1;
    i = (unsigned __int8 *)(digitPtr + 1);
  }
  if ( (unsigned __int8 *)digitPtr == digitsStart )
    digitPtr = (int)numStr;
  if ( endPtr )
    *endPtr = digitPtr;
  if ( (signedFlagSaved != 1 || value < 0x80000000 || value == 0x80000000 && BYTE1(signedFlag) == 45) && !(_BYTE)signedFlag )
  {
    if ( BYTE1(signedFlag) == 45 )
      return -value;
    return value;
  }
  else
  {
    _set_errno_((int)numStr);
    if ( signedFlagSaved )
    {
      if ( signChar == 45 )
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
unsigned int  CRT_StrToULongRadix(unsigned __int8 *numStr, int *endPtr, signed int base)
{
  return CRT_StrToXLong(numStr, endPtr, 1, base);
}

//----- (004E5DE1) --------------------------------------------------------
int  CRT_DigitCharToValue(unsigned __int8 digitChar, int a2, int a3)
{
  unsigned __int8 lowerChar; // al

  if ( digitChar >= 0x30u && digitChar <= 0x39u )
    return digitChar - 48;
  lowerChar = tolower_(a3, a2);
  if ( lowerChar >= 0x61u && lowerChar <= 0x69u )
    return lowerChar - 87;
  if ( lowerChar >= 0x6Au && lowerChar <= 0x72u || lowerChar >= 0x73u && lowerChar <= 0x7Au )
    return lowerChar - 87;
  return 37;
}
// 4852ED: using guessed type int __fastcall tolower_(_DWORD, _DWORD);

//----- (004E5F8A) --------------------------------------------------------
void  CRT_PutEnvEntryA(_BYTE *envString, _BYTE *i, int a3)
{
  int entryIndex; // ebp
  _DWORD *newTable; // eax
  int v5; // eax
  int foundIndex; // eax
  int v7; // edx
  int v8; // ecx
  int v9; // eax
  void *v10; // eax
  unsigned int v11; // ecx
  int v12; // eax
  int v13; // ecx
  int tableBytes; // [esp+4h] [ebp-20h]
  int envTable; // [esp+8h] [ebp-1Ch]

  if ( envString )
  {
    if ( *envString )
    {
      for ( i = envString + 1; *i && *i != 61; ++i )
        ;
    }
    if ( *i )
    {
      entryIndex = i[1] == 0;
      envTable = g_CRT_EnvVarPointerArray;
      if ( g_CRT_EnvVarPointerArray )
      {
        foundIndex = CRT_FindEnvVarIndexA(envString, entryIndex, a3);
        if ( entryIndex )
          goto LABEL_23;
        if ( foundIndex > 0 )
        {
          entryIndex = foundIndex - 1;
          goto LABEL_22;
        }
        entryIndex = -foundIndex;
        v8 = -4 * foundIndex;
        tableBytes = -4 * foundIndex + 8;
        v9 = 1 - foundIndex + tableBytes;
        if ( g_RuntimeGrowableByteFlagArrayPtr )
        {
          v12 = nrealloc_(v8, v9);
          envTable = v12;
          if ( !v12 )
            goto LABEL_23;
          memmove_((void *)(uintptr_t)(v12 + tableBytes), (const void *)(uintptr_t)g_RuntimeGrowableByteFlagArrayPtr, (size_t)entryIndex);
          g_RuntimeGrowableByteFlagArrayPtr = v13;
        }
        else
        {
          v10 = (void *)nmalloc_(v8, v7);
          envTable = (int)v10;
          if ( !v10 )
            goto LABEL_23;
          qmemcpy(v10, (const void *)g_CRT_EnvVarPointerArray, v11);
          g_RuntimeGrowableByteFlagArrayPtr = (int)v10 + tableBytes;
          memset_(0, 0);
        }
        g_CRT_EnvVarPointerArray = envTable;
        *(_DWORD *)(envTable + 4 * entryIndex + 4) = 0;
        goto LABEL_22;
      }
      if ( i[1] )
      {
        newTable = (_DWORD *)nmalloc_(a3, i);
        envTable = (int)newTable;
        if ( newTable )
        {
          g_CRT_EnvVarPointerArray = (int)newTable;
          *newTable = 0;
          v5 = (int)(newTable + 2);
          *(_DWORD *)(v5 - 4) = 0;
          g_RuntimeGrowableByteFlagArrayPtr = v5;
LABEL_22:
          *(_DWORD *)(envTable + 4 * entryIndex) = envString;
          *(_BYTE *)(g_RuntimeGrowableByteFlagArrayPtr + entryIndex) = 0;
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
int  CRT_FindEnvVarIndexA(_BYTE *envName, int deleteFlag, int a3)
{
  _DWORD *tableEntry; // esi
  _BYTE *i; // ebx
  int v7; // eax
  int v8; // eax
  _BYTE *v9; // edx
  int entryIndex; // edi
  _DWORD *j; // ecx
  int entryCount; // esi
  int v13; // ecx
  unsigned __int8 *flagBytePtr; // eax

  tableEntry = (_DWORD *)g_CRT_EnvVarPointerArray;
LABEL_20:
  if ( !*tableEntry )
    return (g_CRT_EnvVarPointerArray - (int)tableEntry) >> 2;
  for ( i = envName; ; ++i )
  {
    if ( !*i || (v7 = toupper_(a3), v8 = toupper_(v7), a3 != v8) )
    {
      ++tableEntry;
      goto LABEL_20;
    }
    if ( *v9 == 61 )
      break;
  }
  entryIndex = ((int)tableEntry - g_CRT_EnvVarPointerArray) >> 2;
  if ( !deleteFlag )
    return entryIndex + 1;
  for ( j = tableEntry; *j; ++j )
    *j = j[1];
  if ( g_RuntimeGrowableByteFlagArrayPtr )
  {
    if ( *(_BYTE *)(entryIndex + g_RuntimeGrowableByteFlagArrayPtr) )
      nfree_(j);
    entryCount = ((int)j - g_CRT_EnvVarPointerArray) >> 2;
    memmove_(j, (const void *)(uintptr_t)g_RuntimeGrowableByteFlagArrayPtr, (size_t)entryCount);
    g_RuntimeGrowableByteFlagArrayPtr = v13;
    if ( entryIndex < entryCount )
    {
      flagBytePtr = (unsigned __int8 *)(entryIndex + g_RuntimeGrowableByteFlagArrayPtr);
      do
      {
        *flagBytePtr = flagBytePtr[1];
        ++flagBytePtr;
        ++entryIndex;
      }
      while ( entryIndex < entryCount );
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
signed int  CRT_PutEnvEntryW(_WORD *envString, _WORD *i)
{
  bool v4; // al
  BOOL removeFlag; // ebx
  _DWORD *allocatedTable; // eax
  int v7; // ecx
  int v8; // eax
  int entryIndex; // esi
  int foundIndex; // eax
  int v11; // edx
  int v12; // eax
  int newTable; // ebp
  int v14; // ecx
  int v15; // eax
  int flagArrayPtr; // ebp
  int tableBytes; // [esp+0h] [ebp-20h]

  if ( !envString )
    return -1;
  if ( *envString )
  {
    for ( i = envString + 1; *i && *i != 61; ++i )
      ;
  }
  if ( !*i )
    return -1;
  v4 = i[1] == 0;
  removeFlag = v4;
  if ( g_CrtWideEnvironTable )
  {
    foundIndex = CRT_FindEnvVarIndexW(envString, v4, g_CrtWideEnvironTable);
    if ( !removeFlag )
    {
      if ( foundIndex > 0 )
      {
        entryIndex = foundIndex - 1;
        goto LABEL_22;
      }
      entryIndex = -foundIndex;
      v11 = 1 - foundIndex;
      tableBytes = -4 * foundIndex + 8;
      v12 = 1 - foundIndex + tableBytes;
      if ( g_RuntimeGrowableByteFlagArrayPtr )
      {
        v15 = nrealloc_(v7, v12);
        if ( !v15 )
          return -1;
        flagArrayPtr = v15 + tableBytes;
        memmove_((void *)(uintptr_t)v15, (const void *)(uintptr_t)g_RuntimeGrowableByteFlagArrayPtr, (size_t)entryIndex);
        g_RuntimeGrowableByteFlagArrayPtr = flagArrayPtr;
      }
      else
      {
        newTable = nmalloc_(v7, v11);
        if ( !newTable )
          return -1;
        memcpy_(newTable, g_CrtWideEnvironTable);
        g_RuntimeGrowableByteFlagArrayPtr = newTable + tableBytes;
        memset_(v14, 0);
      }
      g_CrtWideEnvironTable = v7;
      *(_DWORD *)(v7 + 4 * entryIndex + 4) = 0;
      goto LABEL_22;
    }
  }
  else if ( i[1] )
  {
    allocatedTable = (_DWORD *)nmalloc_(0, i);
    v7 = (int)allocatedTable;
    if ( allocatedTable )
    {
      g_CrtWideEnvironTable = (int)allocatedTable;
      *allocatedTable = 0;
      v8 = (int)(allocatedTable + 2);
      entryIndex = 0;
      *(_DWORD *)(v8 - 4) = 0;
      g_RuntimeGrowableByteFlagArrayPtr = v8;
LABEL_22:
      *(_DWORD *)(v7 + 4 * entryIndex) = envString;
      *(_BYTE *)(entryIndex + g_RuntimeGrowableByteFlagArrayPtr) = 0;
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
int  CRT_FindEnvVarIndexW(_WORD *envName, int deleteFlag, int a3)
{
  _DWORD *tableEntry; // esi
  _WORD *i; // ebx
  int v7; // eax
  __int16 v8; // ax
  _WORD *v9; // edx
  int entryIndex; // edi
  _DWORD *j; // ecx
  int entryCount; // esi
  int v13; // ecx
  _BYTE *flagBytePtr; // eax

  tableEntry = (_DWORD *)g_CrtWideEnvironTable;
LABEL_20:
  if ( !*tableEntry )
    return (g_CrtWideEnvironTable - (int)tableEntry) >> 2;
  for ( i = envName; ; ++i )
  {
    if ( !*i || (v7 = towupper_(a3), v8 = towupper_(v7), (_WORD)a3 != v8) )
    {
      ++tableEntry;
      goto LABEL_20;
    }
    if ( *v9 == 61 )
      break;
  }
  entryIndex = ((int)tableEntry - g_CrtWideEnvironTable) >> 2;
  if ( !deleteFlag )
    return entryIndex + 1;
  for ( j = tableEntry; *j; ++j )
    *j = j[1];
  if ( g_RuntimeGrowableByteFlagArrayPtr )
  {
    if ( *(_BYTE *)(entryIndex + g_RuntimeGrowableByteFlagArrayPtr) )
      nfree_(j);
    entryCount = ((int)j - g_CrtWideEnvironTable) >> 2;
    memmove_(j, (const void *)(uintptr_t)g_RuntimeGrowableByteFlagArrayPtr, (size_t)entryCount);
    g_RuntimeGrowableByteFlagArrayPtr = v13;
    flagBytePtr = (_BYTE *)(entryIndex + v13);
    while ( entryIndex < entryCount )
    {
      ++entryIndex;
      *flagBytePtr = flagBytePtr[1];
      ++flagBytePtr;
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
DWORD __cdecl CRT_SpawnveLaunchProcess(int spawnMode, int a2, LPSTR lpCommandLine, LPVOID lpEnvironment, int a5)
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
  if ( spawnMode )
  {
    if ( spawnMode == 3 )
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
const CHAR * CRT_SetEnvironmentVariableCompat(const WCHAR *wideName, const WCHAR *wideValue, int a3)
{
  const CHAR *result; // eax
  int valueLen; // eax
  int v6; // edx
  int v7; // ecx
  const CHAR *ansiName; // ebp
  const CHAR *ansiValue; // esi
  int nameLen; // eax
  int v11; // edx
  int v12; // ecx
  int v13; // ecx
  int v14; // edx
  int v15; // ecx

  if ( HIWORD(g_WindowsVersionDword) < 0x8000u )
    return (const CHAR *)SetEnvironmentVariableW(wideName, wideValue);
  valueLen = wcslen_(a3, wideValue);
  result = (const CHAR *)nmalloc_(2 * valueLen + 1, v6);
  ansiName = result;
  if ( result )
  {
    if ( wideValue )
    {
      nameLen = wcslen_(v7, result);
      ansiValue = (const CHAR *)nmalloc_(2 * nameLen + 1, v11);
      if ( !ansiValue )
        goto LABEL_9;
    }
    else
    {
      ansiValue = 0;
    }
    if ( wcstombs_(v7, wideName) == -1 )
    {
      nfree_(v12);
      if ( !ansiValue )
        return 0;
LABEL_9:
      nfree_(v7);
      return 0;
    }
    if ( ansiValue && wcstombs_(v12, wideValue) == -1 )
      goto LABEL_9;
    SetEnvironmentVariableA(ansiName, ansiValue);
    nfree_(v13);
    if ( ansiValue )
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
signed int  CRT_GetOsHandleFromFd(int fd, int a2)
{
  if ( fd >= 0 && fd <= (unsigned int)g_CRT_MaxFileDescriptor )
    return *(_DWORD *)(4 * fd + g_CRT_OsHandleTable);
  _set_errno_(a2);
  return -1;
}
// 51A768: using guessed type int dword_51A768;
// 51AED0: using guessed type int dword_51AED0;

//----- (004E7EB8) --------------------------------------------------------
unsigned int  CRT_MbcsBackUpOverLeadByte(unsigned int stringStart, unsigned int currentPos)
{
  unsigned __int8 *scanPtr; // eax

  if ( stringStart >= currentPos )
    return 0;
  scanPtr = (unsigned __int8 *)(currentPos - 1);
  if ( g_CRT_MbcsCodePageActive && (g_Clips_DbcsLeadByteTable[*scanPtr] & 1) != 0 )
    return currentPos - 2;
  do
    --scanPtr;
  while ( stringStart <= (unsigned int)scanPtr && g_CRT_MbcsCodePageActive && (g_Clips_DbcsLeadByteTable[*scanPtr] & 1) != 0 );
  return currentPos - 1 - (int)(currentPos - (_DWORD)scanPtr) % 2;
}
// 54E718: using guessed type int dword_54E718;

//----- (004E7F2D) --------------------------------------------------------
int  CRT_IsExtendedMbcsLeadByte(int a1, int a2)
{
  unsigned int mbChar; // edx

  if ( !ismbclegal_(a2, a1) )
    return IsTable[(unsigned __int8)(mbChar + 1)] & 0x80;
  return mbChar >= 0x8281 && mbChar <= 0x829A;
}
// 4E7F3F: variable 'v2' is possibly undefined
// 4E800B: using guessed type int __fastcall ismbclegal_(_DWORD, _DWORD);

//----- (004E7F70) --------------------------------------------------------
char * CRT_StrNCpyMbcsSafe(char *dest, const char *src, unsigned int count)
{
  const char *srcPtr; // esi
  unsigned int srcSize; // kr04_4
  unsigned int srcLen; // ecx
  char *destPtr; // edi
  char curChar; // al
  char nextChar; // al

  srcPtr = src;
  srcSize = strlen(src) + 1;
  srcLen = srcSize - 1;
  if ( g_CRT_MbcsCodePageActive && (g_Clips_DbcsLeadByteTable[(unsigned __int8)src[count]] & 1) != 0 && count < srcLen )
    --count;
  if ( srcSize > count )
  {
    qmemcpy(dest, src, count);
  }
  else
  {
    destPtr = dest;
    do
    {
      curChar = *srcPtr;
      *destPtr = *srcPtr;
      if ( !curChar )
        break;
      nextChar = srcPtr[1];
      srcPtr += 2;
      destPtr[1] = nextChar;
      destPtr += 2;
    }
    while ( nextChar );
    if ( srcLen != count )
      memset_(srcLen, 0);
  }
  return dest;
}
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 54E718: using guessed type int dword_54E718;

// nfuncs=4362 queued=3899 decompiled=3899 lumina nreq=0 worse=0 better=0
// Remaining decompiler scars are tracked in docs/archive/COMPILATION_PROGRESS.md and are no longer fatal to parsing.
