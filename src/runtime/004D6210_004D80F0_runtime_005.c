/* Generated from src/recovered/runtime/004D0560_legacy_runtime.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "runtime_internal.h"
#include "runtime_state.h"
#include "runtime_shared_state.h"
#include "../clips/clips_api.h"
#include "../media/media_api.h"
/* CLASH95_GENERATED_INCLUDES_END */

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

  result = (_DWORD *)(uintptr_t)Class_ResolveNamedSlot(a3, theDefclass, slotName);
  if ( result )
  {
    theConstraint = (_DWORD *)(uintptr_t)result[5];
    if ( theConstraint && (*theConstraint & 1) == 0 )
    {
      typeBits1 = 0;
      typeBits0 = 0;
      typeCount = 0;
      if ( (*(_BYTE *)(uintptr_t)result[5] & 2) != 0 )
      {
        typeCount = 1;
        typeBits0 = 4;
      }
      if ( (*(_BYTE *)(uintptr_t)result[5] & 4) != 0 )
      {
        ++typeCount;
        typeBits0 |= 8u;
      }
      if ( (*(_BYTE *)(uintptr_t)result[5] & 8) != 0 )
      {
        ++typeCount;
        typeBits0 |= 1u;
      }
      if ( (*(_BYTE *)(uintptr_t)result[5] & 0x10) != 0 )
      {
        ++typeCount;
        typeBits0 |= 2u;
      }
      if ( (*(_BYTE *)(uintptr_t)result[5] & 0x20) != 0 )
      {
        ++typeCount;
        typeBits1 |= 1u;
      }
      if ( (*(_BYTE *)(uintptr_t)result[5] & 0x40) != 0 )
      {
        ++typeCount;
        typeBits0 |= 0x80u;
      }
      if ( *(char *)(uintptr_t)result[5] < 0 )
      {
        ++typeCount;
        typeBits0 |= 0x20u;
      }
      if ( (*(_BYTE *)(uintptr_t)(result[5] + 1) & 1) != 0 )
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
    *(_DWORD *)(uintptr_t)(a3 + 16) = typeCount - 1;
    bitIndex = 0;
    result = Rules_CreateEphemeralMultifield(typeCount);
    *(_DWORD *)(uintptr_t)(a3 + 8) = result;
    if ( v8 >= 1 )
    {
      typeIndex = 0;
      fieldOffset = 0;
      lastFieldOffset = 6 * v8 - 6;
      do
      {
        result = (_DWORD *)(uintptr_t)(unsigned __int8)*(&typeBits0 + ((bitIndex - (__CFSHL__(bitIndex >> 31, 3) + 8 * (bitIndex >> 31))) >> 3));
        if ( ((unsigned __int8)(1 << (bitIndex % 8)) & (unsigned __int8)(intptr_t)result) != 0 )
        {
          *(_WORD *)(uintptr_t)(fieldOffset + *(_DWORD *)(uintptr_t)(a3 + 8) + 14) = 2;
          fieldOffset += 6;
          result = (_DWORD *)(uintptr_t)Rules_GetConstructNameSymbol(g_ClipsPrimitiveTypeClassMap[typeIndex]);
          *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(a3 + 8) + fieldOffset + 10) = result;
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

  result = Class_ResolveNamedSlot((int)(intptr_t)a3, theDefclass, slotName);
  if ( result )
  {
    theConstraint = *(_DWORD *)(uintptr_t)(result + 20);
    if ( theConstraint && (v5 = *(_DWORD *)(uintptr_t)(result + 20), *(_DWORD *)(uintptr_t)(theConstraint + 6)) )
    {
      valueCount = AST_CountTreeNodes(*(_DWORD *)(uintptr_t)(v5 + 6));
      a3[4] = valueCount - 1;
      a3[2] = Rules_CreateEphemeralMultifield(valueCount);
      result = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v7 + 20) + 6);
      if ( result )
      {
        fieldOffset = 0;
        do
        {
          *(_WORD *)(uintptr_t)(fieldOffset + a3[2] + 14) = *(_WORD *)(uintptr_t)result;
          *(_DWORD *)(uintptr_t)(a3[2] + fieldOffset + 16) = *(_DWORD *)(uintptr_t)(result + 2);
          result = *(_DWORD *)(uintptr_t)(result + 10);
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

  result = Class_ResolveNamedSlot((int)(intptr_t)a3, theDefclass, slotName);
  if ( result )
  {
    theConstraint = (char *)(uintptr_t)*(_DWORD *)(uintptr_t)(result + 20);
    if ( theConstraint && ((constraintFlags = *theConstraint, (*theConstraint & 1) != 0) || (constraintFlags & 8) != 0 || (constraintFlags & 0x10) != 0 ? (hasRange = 1) : (hasRange = 0), hasRange) )
    {
      a3[4] = 1;
      a3[2] = Rules_CreateEphemeralMultifield(2);
      *(_WORD *)(uintptr_t)(a3[2] + 14) = *(_WORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v8 + 20) + 10);
      *(_DWORD *)(uintptr_t)(a3[2] + 16) = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v8 + 20) + 10) + 2);
      *(_WORD *)(uintptr_t)(a3[2] + 20) = *(_WORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v8 + 20) + 14);
      result = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v8 + 20) + 14) + 2);
      *(_DWORD *)(uintptr_t)(a3[2] + 22) = result;
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

  result = (_DWORD *)(uintptr_t)Class_ResolveNamedSlot(a3, theDefclass, slotName);
  if ( result )
  {
    if ( (*(_BYTE *)result & 2) != 0 )
    {
      *(_DWORD *)(uintptr_t)(a3 + 16) = 1;
      theMultifield = Rules_CreateEphemeralMultifield(2);
      *(_DWORD *)(uintptr_t)(a3 + 8) = theMultifield;
      theConstraint = *(_DWORD *)(uintptr_t)(v5 + 20);
      if ( theConstraint )
      {
        *(_WORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(a3 + 8) + 14) = *(_WORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(theConstraint + 18);
        *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(a3 + 8) + 16) = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v5 + 20) + 18) + 2);
        *(_WORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(a3 + 8) + 20) = *(_WORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v5 + 20) + 22);
        result = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v5 + 20) + 22) + 2);
        *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(a3 + 8) + 22) = result;
      }
      else
      {
        *((_WORD *)theMultifield + 7) = 1;
        *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(a3 + 8) + 16) = g_CLIPS_IntegerZeroValueNode;
        *(_WORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(a3 + 8) + 20) = 2;
        result = (_DWORD *)(uintptr_t)g_ClipsPositiveInfinitySymbol;
        *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(a3 + 8) + 22) = g_ClipsPositiveInfinitySymbol;
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
    return (_DWORD *)(uintptr_t)queryFunction();
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
  while ( *(unsigned __int16 *)(uintptr_t)(theDefclass + 40) > subclassIndex )
  {
    theSubclass = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theDefclass + 42) + linkOffset);
    if ( (*(_BYTE *)(uintptr_t)(theSubclass + byteIndex + 108) & (unsigned __int8)(1 << bitIndex)) == 0 )
    {
      ++subclassCount;
      *(_BYTE *)(uintptr_t)(theSubclass + byteIndex + 108) |= 1 << bitIndex;
      if ( inheritFlag )
      {
        if ( *(_WORD *)(uintptr_t)(theSubclass + 40) )
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
  while ( *(unsigned __int16 *)(uintptr_t)(theDefclass + 40) > subclassIndex )
  {
    theSubclass = *(_DWORD *)(uintptr_t)(linkOffset + *(_DWORD *)(uintptr_t)(theDefclass + 42));
    if ( (*(_BYTE *)(uintptr_t)(theSubclass + byteIndex + 108) & (unsigned __int8)(1 << bitIndex)) == 0 )
    {
      *(_BYTE *)(uintptr_t)(theSubclass + byteIndex + 108) |= 1 << bitIndex;
      *(_WORD *)(uintptr_t)(multifieldValue + 6 * (fieldPosition++ - 1) + 14) = 2;
      classNameSymbol = Rules_GetConstructNameSymbol(theSubclass);
      *(_DWORD *)(uintptr_t)(fieldOffset + multifieldValue + 16) = classNameSymbol;
      if ( inheritFlag )
      {
        if ( *(_WORD *)(uintptr_t)(theSubclass + 40) )
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
    slotIndex = Instance_ResolveSlotIndex(v6, (int)(intptr_t)slotSymbol);
    if ( slotIndex == -1 )
    {
      Instance_ReportNoSuchSlotError(v8, v8);
      Lexer_ErrorRecover(1);
      Rules_SetMultifieldErrorValue(result);
      return 0;
    }
    else
    {
      *(_DWORD *)(uintptr_t)(result + 4) = 4;
      *(_DWORD *)(uintptr_t)(result + 12) = 0;
      return *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theDefclass + 56) + 4 * slotIndex);
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
void Math_CompareAbsToEpsilon(void)
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
  int versionAfterSymbols; // eax
  const char *v5; // ecx
  int versionAfterFloats; // eax
  const char *v7; // ecx
  int versionAfterIntegers; // eax
  const char *v9; // ecx
  int versionAfterBitmaps; // eax
  const char *v11; // ecx

  Rules_SetAtomicValueIndices(1);
  Compiler_WriteConstantsReferenceFile(v1, imageID);
  versionAfterSymbols = Compiler_WriteSymbolTableFile(v3, v2);
  versionAfterFloats = Compiler_WriteFloatTableFile(v5, versionAfterSymbols);
  versionAfterIntegers = Compiler_WriteIntegerTableFile(v7, versionAfterFloats);
  versionAfterBitmaps = Compiler_WriteBitMapTableFile(v9, versionAfterIntegers);
  return Compiler_WriteBitMapValuesFile(v11, versionAfterBitmaps);
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
  bucket = (_DWORD **)(uintptr_t)symbolTable;
  do
  {
    for ( i = *bucket; i; ++symbolCount )
      i = (_DWORD *)(uintptr_t)*i;
    ++bucket;
  }
  while ( bucket != (_DWORD **)(uintptr_t)(symbolTable + 4052) );
  if ( !symbolCount )
    return version;
  for ( j = 1;
        j <= symbolCount / g_ClipsCodeMaxIndicesPerArray + 1;
        Output_WriteFormatted(j + 1, g_ConstructsToCImageId, g_ClipsCodeHeaderFile, (int)(intptr_t)aExternStructSy, g_ConstructsToCImageId) )
  {
    ;
  }
  outFile = Rules_OpenConstructCodeFile(fileName, 1, version, 1u);
  if ( !outFile )
    return -1;
  entriesThisFile = 0;
  bucketPtr = (_DWORD *)(uintptr_t)symbolTable;
  for ( k = 0; k < 1013; ++k )
  {
    symbolNode = (_DWORD *)(uintptr_t)*bucketPtr;
    if ( *bucketPtr )
    {
      do
      {
        if ( newHeader )
        {
          Output_WriteFormatted(outFile, 0, outFile, (int)(intptr_t)aStructSymbolha, g_ConstructsToCImageId);
          newHeader = v8;
        }
        if ( *symbolNode )
          Output_WriteFormatted(outFile, g_ClipsCodeMaxIndicesPerArray, outFile, (int)(intptr_t)aSD_DD_2, g_ConstructsToCImageId);
        else
          Output_WriteFormatted(outFile, v8, outFile, (int)(intptr_t)aNull_8, (char)(intptr_t)bucketPtr);
        ++entriesThisFile;
        Output_WriteFormatted(v12, k, v12, (int)(intptr_t)aLd000D, symbolNode[1] + 1);
        Compiler_WriteEscapedStringLiteral(v13, symbolNode[4], v13, entriesThisFile);
        if ( ++writtenCount == symbolCount || entriesThisFile >= g_ClipsCodeMaxIndicesPerArray )
        {
          Output_WriteFormatted(v14, symbolCount, v14, (int)(intptr_t)asc_50D12C, (char)(intptr_t)bucketPtr);
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
          Output_WriteFormatted(v14, symbolCount, v14, (int)(intptr_t)asc_50D134, (char)(intptr_t)bucketPtr);
        }
        symbolNode = (_DWORD *)(uintptr_t)*symbolNode;
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
  bucket = (_DWORD **)(uintptr_t)bitmapTable;
  do
  {
    for ( i = *bucket; i; ++bitmapCount )
      i = (_DWORD *)(uintptr_t)*i;
    ++bucket;
  }
  while ( bucket != (_DWORD **)(uintptr_t)(bitmapTable + 668) );
  if ( !bitmapCount )
    return version;
  for ( j = 1; j <= bitmapCount / g_ClipsCodeMaxIndicesPerArray + 1; ++j )
    Output_WriteFormatted(g_ClipsCodeMaxIndicesPerArray, g_ClipsCodeHeaderFile, g_ClipsCodeHeaderFile, (int)(intptr_t)aExternStructBi, g_ConstructsToCImageId);
  outFile = Rules_OpenConstructCodeFile(fileName, 1, version, j);
  if ( !outFile )
    return -1;
  entriesThisFile = 0;
  bucketPtr = (int **)(uintptr_t)bitmapTable;
  for ( k = 0; k < 167; ++k )
  {
    for ( m = *bucketPtr; m; m = (int *)(uintptr_t)*m )
    {
      if ( newHeader )
      {
        Output_WriteFormatted(arrayVersion, outFile, outFile, (int)(intptr_t)aStructBitmapha, g_ConstructsToCImageId);
        newHeader = 0;
      }
      if ( *m )
      {
        if ( entriesThisFile + 1 < g_ClipsCodeMaxIndicesPerArray )
          Output_WriteFormatted(g_ConstructsToCImageId, outFile, outFile, (int)(intptr_t)aBD_DD, g_ConstructsToCImageId);
        else
          Output_WriteFormatted(v9, outFile, outFile, (int)(intptr_t)aBD_DD, g_ConstructsToCImageId);
      }
      else
      {
        Output_WriteFormatted(v9, outFile, outFile, (int)(intptr_t)aNull_8, (char)(intptr_t)bucketPtr);
      }
      Output_WriteFormatted(g_ConstructsToCImageId, v12, v12, (int)(intptr_t)aLd000DCharLD_D, m[1] + 1);
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
        Output_WriteFormatted(bitmapCount, v13, v13, (int)(intptr_t)asc_50D12C, (char)(intptr_t)bucketPtr);
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
        Output_WriteFormatted(bitmapCount, v13, v13, (int)(intptr_t)asc_50D134, (char)(intptr_t)bucketPtr);
      }
    }
    v9 = (int)(intptr_t)++bucketPtr;
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
  int fullWords; // edx
  int wordIndex; // edi
  unsigned int byteBase; // ebp
  unsigned int byteInWord; // edx
  unsigned int byteIndex; // eax
  int v17; // ecx
  char byteVal; // bl
  int newWordsThisFile; // edi
  int v20; // ecx
  DWORD nextArrayVersion; // ebp
  char wordBytesBase; // [esp+1h] [ebp-45h]
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
  bucket = (int **)(uintptr_t)bitmapTable;
  newHeader = 1;
  arrayVersion = 1;
  totalWordCount = 0;
  wordsWritten = 0;
  do
  {
    for ( i = *bucket; i; i = (int *)(uintptr_t)*i )
    {
      bitmapSize = *((_WORD *)i + 10);
      wordTotal = (bitmapSize >> 2) + totalWordCount;
      totalWordCount = wordTotal;
      if ( (bitmapSize & 3) != 0 )
        totalWordCount = wordTotal + 1;
    }
    ++bucket;
  }
  while ( bucket != (int **)(uintptr_t)(bitmapTable + 668) );
  if ( !totalWordCount )
    return versionCounter;
  for ( j = 1;
        j <= totalWordCount / g_ClipsCodeMaxIndicesPerArray + 1;
        Output_WriteFormatted(j + 1, g_ClipsCodeHeaderFile, g_ClipsCodeHeaderFile, (int)(intptr_t)aExternUnsigned, g_ConstructsToCImageId) )
  {
    wordBytesBase = HIBYTE(j);
  }
  outFile = Rules_OpenConstructCodeFile(savedFileName, 1, versionCounter, bitmapTable);
  if ( !outFile )
    return -1;
  bucketPtr = (int **)(uintptr_t)bitmapTable;
  wordsThisFile = 0;
  for ( k = 0; k < 167; ++k )
  {
    for ( m = *bucketPtr; m; m = (int *)(uintptr_t)*m )
    {
      if ( newHeader )
      {
        wordBytesBase = HIBYTE(arrayVersion);
        Output_WriteFormatted(0, outFile, outFile, (int)(intptr_t)aUnsignedLongLD, g_ConstructsToCImageId);
        newHeader = v9;
      }
      sizeBytes = *((_WORD *)m + 10);
      fullWords = sizeBytes >> 2;
      wordCount = fullWords;
      if ( (sizeBytes & 3) != 0 )
        wordCount = fullWords + 1;
      wordIndex = 0;
      if ( wordCount > 0 )
      {
        byteBase = 0;
        do
        {
          if ( wordIndex > 0 )
            Output_WriteFormatted(v9, fullWords, outFile, (int)(intptr_t)asc_50D1F8, wordValue);
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
            byteVal = *(_BYTE *)(uintptr_t)(v17 + byteIndex++);
            *(&wordBytesBase + byteInWord) = byteVal;
          }
          while ( byteInWord < 4 );
          Output_WriteFormatted(v17, outFile, outFile, (int)(intptr_t)a0xLxl, wordValue);
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
        Output_WriteFormatted(v9, fullWords, outFile, (int)(intptr_t)asc_50D204, wordValue);
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
        Output_WriteFormatted(outFile, fullWords, outFile, (int)(intptr_t)asc_50D208, wordValue);
      }
    }
    v9 = (int)(intptr_t)++bucketPtr;
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
  int newWrittenCount; // ecx
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
  bucket = (_DWORD **)(uintptr_t)floatTable;
  do
  {
    for ( i = *bucket; i; ++floatCount )
      i = (_DWORD *)(uintptr_t)*i;
    ++bucket;
  }
  while ( bucket != (_DWORD **)(uintptr_t)(floatTable + 2012) );
  if ( !floatCount )
    return version;
  for ( j = 1; j <= floatCount / g_ClipsCodeMaxIndicesPerArray + 1; ++j )
    Output_WriteFormatted(g_ClipsCodeMaxIndicesPerArray, floatCount % g_ClipsCodeMaxIndicesPerArray, g_ClipsCodeHeaderFile, (int)(intptr_t)aExternStructFl, g_ConstructsToCImageId);
  outFile = Rules_OpenConstructCodeFile(fileName, 1, version, 1u);
  if ( !outFile )
    return -1;
  entriesThisFile = 0;
  bucketIndex = 0;
  bucketPtr = (double **)(uintptr_t)floatTable;
  do
  {
    for ( k = *bucketPtr; k; k = *(double **)k )
    {
      if ( newHeader )
      {
        Output_WriteFormatted(g_ConstructsToCImageId, outFile, outFile, (int)(intptr_t)aStructFloathas, g_ConstructsToCImageId);
        newHeader = 0;
      }
      if ( *(_DWORD *)k )
        Output_WriteFormatted(g_ClipsCodeMaxIndicesPerArray, outFile, outFile, (int)(intptr_t)aFD_DD, g_ConstructsToCImageId);
      else
        Output_WriteFormatted(v8, outFile, outFile, (int)(intptr_t)aNull_8, floatTable);
      Output_WriteFormatted(bucketIndex, v11, v11, (int)(intptr_t)aLd000D, *((_DWORD *)k + 1) + 1);
      floatStr = Rules_FloatToSymbol(v12, k[2]);
      Output_WriteFormatted(v15, v14, v14, (int)(intptr_t)aS_11, floatStr);
      ++entriesThisFile;
      newWrittenCount = writtenCount + 1;
      writtenCount = newWrittenCount;
      if ( newWrittenCount == floatCount || entriesThisFile >= g_ClipsCodeMaxIndicesPerArray )
      {
        ++arrayVersion;
        Output_WriteFormatted(newWrittenCount, v16, v16, (int)(intptr_t)asc_50D12C, floatTable);
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
        Output_WriteFormatted(newWrittenCount, v16, v16, (int)(intptr_t)asc_50D134, floatTable);
      }
    }
    v8 = (int)(intptr_t)++bucketPtr;
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
  bucket = (_DWORD **)(uintptr_t)integerTable;
  do
  {
    for ( i = *bucket; i; ++integerCount )
      i = (_DWORD *)(uintptr_t)*i;
    ++bucket;
  }
  while ( bucket != (_DWORD **)(uintptr_t)(integerTable + 668) );
  if ( !integerCount )
    return version;
  for ( j = 1; j <= integerCount / g_ClipsCodeMaxIndicesPerArray + 1; ++j )
    Output_WriteFormatted(g_ClipsCodeMaxIndicesPerArray, integerCount % g_ClipsCodeMaxIndicesPerArray, g_ClipsCodeHeaderFile, (int)(intptr_t)aExternStructIn, g_ConstructsToCImageId);
  outFile = Rules_OpenConstructCodeFile(fileName, 1, version, 1u);
  if ( !outFile )
    return -1;
  entriesThisFile = 0;
  bucketIndex = 0;
  bucketPtr = (_DWORD *)(uintptr_t)integerTable;
  do
  {
    integerNode = (_DWORD *)(uintptr_t)*bucketPtr;
    if ( *bucketPtr )
    {
      do
      {
        if ( newHeader )
        {
          Output_WriteFormatted(g_ConstructsToCImageId, outFile, outFile, (int)(intptr_t)aStructIntegerh, g_ConstructsToCImageId);
          newHeader = 0;
        }
        if ( *integerNode )
          Output_WriteFormatted(g_ClipsCodeMaxIndicesPerArray, outFile, outFile, (int)(intptr_t)aID_DD, g_ConstructsToCImageId);
        else
          Output_WriteFormatted(v8, outFile, outFile, (int)(intptr_t)aNull_8, integerTable);
        Output_WriteFormatted(bucketIndex, v11, v11, (int)(intptr_t)aLd000D, integerNode[1] + 1);
        Output_WriteFormatted(v13, v12, v12, (int)(intptr_t)aLd, integerNode[4]);
        ++entriesThisFile;
        if ( ++writtenCount == integerCount || entriesThisFile >= g_ClipsCodeMaxIndicesPerArray )
        {
          Output_WriteFormatted(integerCount, v14, v14, (int)(intptr_t)asc_50D12C, integerTable);
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
          Output_WriteFormatted(integerCount, v14, v14, (int)(intptr_t)asc_50D134, integerTable);
        }
        integerNode = (_DWORD *)(uintptr_t)*integerNode;
      }
      while ( integerNode );
    }
    v8 = (int)(intptr_t)++bucketPtr;
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
  int currentSymbolIndex; // ecx
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
  int currentBitmapIndex; // ecx
  int bitmapIndex; // ecx
  int v30; // edx
  int v31; // ecx
  char v32; // [esp+0h] [ebp-18h]
  char v33; // [esp+0h] [ebp-18h]
  char v34; // [esp+0h] [ebp-18h]
  char v35; // [esp+0h] [ebp-18h]

  symbolTable = (int *)(uintptr_t)Rules_GetSymbolTable();
  result = Rules_OpenConstructCodeFile(fileName, 1, 1, imageID);
  symbolFile = result;
  if ( result )
  {
    Output_WriteFormatted(g_ConstructsToCImageId, result, g_ClipsCodeHeaderFile, (int)(intptr_t)aExternStruct_0, g_ConstructsToCImageId);
    Output_WriteFormatted(0, v6, v6, (int)(intptr_t)aStructSymbol_0, g_ConstructsToCImageId);
    do
    {
      Compiler_WriteSymbolReference(symbolFile, *symbolTable, symbolIndex);
      if ( currentSymbolIndex != 1012 )
        Output_WriteFormatted(currentSymbolIndex, currentSymbolIndex + 1, symbolFile, (int)(intptr_t)asc_50D208, v32);
      symbolIndex = currentSymbolIndex + 1;
      ++symbolTable;
    }
    while ( symbolIndex < 1013 );
    Output_WriteFormatted(symbolIndex, 1, symbolFile, (int)(intptr_t)asc_50D204, v32);
    fclose_(0);
    floatTable = (int *)(uintptr_t)Rules_GetFloatTable();
    result = Rules_OpenConstructCodeFile(fileName, v10, 2, imageID);
    floatFile = result;
    if ( result )
    {
      Output_WriteFormatted(v11, result, g_ClipsCodeHeaderFile, (int)(intptr_t)aExternStruct_1, g_ConstructsToCImageId);
      Output_WriteFormatted(0, v13, v13, (int)(intptr_t)aStructFloath_0, g_ConstructsToCImageId);
      do
      {
        if ( *floatTable )
          Compiler_WriteFloatReference(floatFile, *floatTable);
        else
          Output_WriteFormatted(v15, v14, floatFile, (int)(intptr_t)aNull_9, v33);
        v14 = floatIndex + 1;
        if ( floatIndex != 502 )
          Output_WriteFormatted(floatIndex, v14, floatFile, (int)(intptr_t)asc_50D208, v33);
        v15 = floatIndex + 1;
        ++floatTable;
      }
      while ( v15 < 503 );
      Output_WriteFormatted(v15, 1, floatFile, (int)(intptr_t)asc_50D204, v33);
      fclose_(0);
      integerTable = Rules_GetIntegerTable();
      result = Rules_OpenConstructCodeFile(fileName, v18, 3, integerTable);
      integerFile = result;
      if ( result )
      {
        Output_WriteFormatted(g_ConstructsToCImageId, result, g_ClipsCodeHeaderFile, (int)(intptr_t)aExternStruct_2, g_ConstructsToCImageId);
        integerIndex = 0;
        Output_WriteFormatted(integerTable, v21, v21, (int)(intptr_t)aStructIntege_0, g_ConstructsToCImageId);
        do
        {
          if ( *integerEntry )
            Compiler_WriteIntegerReference(integerFile, *integerEntry);
          else
            Output_WriteFormatted((int)(intptr_t)integerEntry, 0, integerFile, (int)(intptr_t)aNull_9, v34);
          if ( integerIndex != 166 )
            Output_WriteFormatted(v23, integerIndex + 1, integerFile, (int)(intptr_t)asc_50D208, v34);
          ++integerIndex;
          integerEntry = (int *)(uintptr_t)(v23 + 4);
        }
        while ( integerIndex < 167 );
        Output_WriteFormatted((int)(intptr_t)integerEntry, 1, integerFile, (int)(intptr_t)asc_50D204, v34);
        fclose_(0);
        bitmapTable = (int *)(uintptr_t)Rules_GetBitmapTable();
        result = Rules_OpenConstructCodeFile(fileName, v25, 4, integerTable);
        bitmapFile = result;
        if ( result )
        {
          Output_WriteFormatted(g_ConstructsToCImageId, result, g_ClipsCodeHeaderFile, (int)(intptr_t)aExternStruct_3, g_ConstructsToCImageId);
          Output_WriteFormatted(0, v27, v27, (int)(intptr_t)aStructBitmap_0, g_ConstructsToCImageId);
          do
          {
            Compiler_WriteBitMapReference(bitmapFile, *bitmapTable, currentBitmapIndex);
            v30 = bitmapIndex + 1;
            if ( bitmapIndex != 166 )
              Output_WriteFormatted(bitmapIndex, v30, bitmapFile, (int)(intptr_t)asc_50D208, v35);
            currentBitmapIndex = bitmapIndex + 1;
            ++bitmapTable;
          }
          while ( currentBitmapIndex < 167 );
          Output_WriteFormatted(currentBitmapIndex, v30, bitmapFile, (int)(intptr_t)asc_50D204, v35);
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
             *(_DWORD *)(uintptr_t)(theSymbol + 12) << 16 >> 18,
             (*(_DWORD *)(uintptr_t)(theSymbol + 12) << 16 >> 18) % (unsigned int)g_ClipsCodeMaxIndicesPerArray,
             fp,
             (int)(intptr_t)aSD_DD_3,
             g_ConstructsToCImageId);
  else
    return Output_WriteFormatted(a3, 0, fp, (int)(intptr_t)aNull_9, v4);
}
// 4D7AEE: variable 'v4' is possibly undefined
// 51ACF0: using guessed type int dword_51ACF0;
// 54E6D0: using guessed type int dword_54E6D0;

//----- (004D7B40) --------------------------------------------------------
int  Compiler_WriteFloatReference(int fp, int theFloat)
{
  return Output_WriteFormatted(
           *(_DWORD *)(uintptr_t)(theFloat + 12) << 16 >> 18,
           (*(_DWORD *)(uintptr_t)(theFloat + 12) << 16 >> 18) % (unsigned int)g_ClipsCodeMaxIndicesPerArray,
           fp,
           (int)(intptr_t)aFD_DD_0,
           g_ConstructsToCImageId);
}
// 51ACF0: using guessed type int dword_51ACF0;
// 54E6D0: using guessed type int dword_54E6D0;

//----- (004D7B90) --------------------------------------------------------
int  Compiler_WriteIntegerReference(int fp, int theInteger)
{
  return Output_WriteFormatted(
           *(_DWORD *)(uintptr_t)(theInteger + 12) << 16 >> 18,
           (*(_DWORD *)(uintptr_t)(theInteger + 12) << 16 >> 18) % (unsigned int)g_ClipsCodeMaxIndicesPerArray,
           fp,
           (int)(intptr_t)aID_DD_0,
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
             *(_DWORD *)(uintptr_t)(theBitMap + 12) << 16 >> 18,
             (*(_DWORD *)(uintptr_t)(theBitMap + 12) << 16 >> 18) % (unsigned int)g_ClipsCodeMaxIndicesPerArray,
             fp,
             (int)(intptr_t)aBD_DD_0,
             g_ConstructsToCImageId);
  else
    return Output_WriteFormatted(a3, 0, fp, (int)(intptr_t)aNull_9, v4);
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

  Output_WriteFormatted(a3, a2, fp, (int)(intptr_t)asc_50D454, a4);
  charIndex = 0;
  lengthPlusOne = strlen(str) + 1;
  charPtr = (const char *)(uintptr_t)(lengthPlusOne - 1);
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
      charPtr = (const char *)(uintptr_t)(v11 + 1);
    }
    while ( charIndex < (int)(lengthPlusOne - 1) );
  }
  return Output_WriteFormatted((int)(intptr_t)charPtr, (int)(intptr_t)str, fp, (int)(intptr_t)asc_50D454, v13);
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
  int nextConstraintsWritten; // edx
  int nextIndexInFile; // ecx
  int v35; // ecx
  int newVersion; // ebx
  int savedFileId; // [esp+0h] [ebp-30h]
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

  savedFileId = fileId;
  newHeader = 1;
  version = 1;
  arrayVersion = 1;
  bucketOffset = 0;
  numberOfConstraints = 0;
  do
  {
    for ( i = *(_DWORD *)(uintptr_t)(g_ConstraintHashTable + bucketOffset); i; ++numberOfConstraints )
    {
      *(_WORD *)(uintptr_t)(i + 4) = numberOfConstraints;
      i = *(_DWORD *)(uintptr_t)(i + 30);
    }
    bucketOffset += 4;
  }
  while ( bucketOffset != 668 );
  if ( !Rules_DynamicConstraintCheckingEnabled() && numberOfConstraints )
  {
    Rules_PrintWarningID((int)(intptr_t)aCstrncmp, 1, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WWarning[0], (int)(intptr_t)aConstraintsA_0, v8);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WWarning[0], (int)(intptr_t)aWhenDynamicC_0, v9);
    return -1;
  }
  if ( !numberOfConstraints )
    return -1;
  arrayIndex = 1;
  for ( j = maxIndices; arrayIndex <= numberOfConstraints / j + 1; Output_WriteFormatted(j, numberOfConstraints % j, headerFile, (int)(intptr_t)aExternConstrai, imageId) )
    ++arrayIndex;
  outputFile = Rules_OpenConstructCodeFile(fileName, savedFileId, 1, imageId);
  if ( !outputFile )
    return -1;
  indexInFile = 0;
  constraintsWritten = 0;
  hashOffset = 0;
  do
  {
    v15 = hashOffset;
    for ( k = *(_DWORD *)(uintptr_t)(hashOffset + g_ConstraintHashTable); k; k = *(_DWORD *)(uintptr_t)(k + 30) )
    {
      if ( newHeader )
      {
        Output_WriteFormatted(0, arrayVersion, outputFile, (int)(intptr_t)aConstraint_rec, imageId);
        newHeader = v13;
      }
      Output_WriteFormatted(v13, v15, outputFile, (int)(intptr_t)aDDDDDDDDDDDDDD, *(_BYTE *)(uintptr_t)k & 1);
      Output_WriteFormatted(v18, v17, outputFile, (int)(intptr_t)a0, savedFileId);
      Rules_WriteExpressionRefToCode(outputFile, (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(k + 6), maxIndices, imageId);
      Output_WriteFormatted(v20, v19, outputFile, (int)(intptr_t)asc_50D54C, v38);
      Rules_WriteExpressionRefToCode(outputFile, (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(k + 10), maxIndices, imageId);
      Output_WriteFormatted(v22, v21, outputFile, (int)(intptr_t)asc_50D54C, v39);
      Rules_WriteExpressionRefToCode(outputFile, (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(k + 14), maxIndices, imageId);
      Output_WriteFormatted(v24, v23, outputFile, (int)(intptr_t)asc_50D54C, v40);
      Rules_WriteExpressionRefToCode(outputFile, (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(k + 18), maxIndices, imageId);
      Output_WriteFormatted(v26, v25, outputFile, (int)(intptr_t)asc_50D54C, v41);
      Rules_WriteExpressionRefToCode(outputFile, (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(k + 22), maxIndices, imageId);
      Output_WriteFormatted(v28, v27, outputFile, (int)(intptr_t)aNull_10, v42);
      if ( *(_DWORD *)(uintptr_t)(k + 30) )
      {
        if ( indexInFile + 1 < maxIndices )
          Output_WriteFormatted(arrayVersion, maxIndices, outputFile, (int)(intptr_t)aCD_DD, imageId);
        else
          Output_WriteFormatted(v30, maxIndices, outputFile, (int)(intptr_t)aCD_DD, imageId);
      }
      else
      {
        Output_WriteFormatted(v30, v29, outputFile, (int)(intptr_t)aNull_11, v43);
      }
      Output_WriteFormatted(v32, v31, outputFile, (int)(intptr_t)aDD_1, *(_DWORD *)(uintptr_t)(k + 34));
      nextConstraintsWritten = constraintsWritten + 1;
      nextIndexInFile = indexInFile + 1;
      constraintsWritten = nextConstraintsWritten;
      ++indexInFile;
      if ( numberOfConstraints == nextConstraintsWritten || nextIndexInFile >= maxIndices )
      {
        Output_WriteFormatted(nextIndexInFile, nextConstraintsWritten, outputFile, (int)(intptr_t)asc_50D578, v43);
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
        Output_WriteFormatted(nextIndexInFile, nextConstraintsWritten, outputFile, (int)(intptr_t)asc_50D580, v43);
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
    return Output_WriteFormatted(*(unsigned __int16 *)(uintptr_t)(constraintPtr + 4), *(unsigned __int16 *)(uintptr_t)(constraintPtr + 4) % maxIndices, codeFile, (int)(intptr_t)aCD_DD_0, imageId);
  else
    return Output_WriteFormatted(maxIndices, constraintPtr, codeFile, (int)(intptr_t)aNull_21, v8);
}
// 4D80AB: variable 'a3' is possibly undefined
// 4D80AB: variable 'a2' is possibly undefined
// 4D80AB: variable 'v8' is possibly undefined

//----- (004D80F0) --------------------------------------------------------
int Compiler_RegisterModuleCodeItem(void)
{
  int result; // eax

  result = Rules_AddCodeGeneratorItem((int)(intptr_t)aDefmodule_2, 200, (int)(intptr_t)Compiler_WriteModuleListSetupCode, (int)(intptr_t)Compiler_AssignModuleIndices, (int)(intptr_t)Compiler_WriteModuleTableFile, 3);
  g_ClipsDefmoduleCompilerItem = result;
  return result;
}
// 4D8120: using guessed type int sub_4D8120();
// 54E908: using guessed type int dword_54E908;
