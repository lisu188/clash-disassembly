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

//----- (004B76F0) --------------------------------------------------------
int PP_MakeConst26(void)
{
  int v0; // ecx
  int packedWord; // eax
  int v2; // edx
  unsigned __int8 v3; // al
  _DWORD bitmap[5]; // [esp+0h] [ebp-14h] BYREF

  Mem_AllocArray(bitmap, 4);
  if ( *(int *)(uintptr_t)(v0 + 40) <= 0 )
  {
    LOBYTE(bitmap[0]) |= 1u;
    bitmap[0] &= 0xFFFC0001;
    return Rules_AddBitmapValue(bitmap, 4);
  }
  packedWord = bitmap[0];
  LOBYTE(packedWord) = bitmap[0] & 0xFC;
  if ( *(int *)(uintptr_t)(v0 + 32) > 0 )
  {
    bitmap[0] = packedWord;
    v2 = (unsigned __int8)(*(_DWORD *)(uintptr_t)(v0 + 40) - 1);
    bitmap[0] = (v2 << 10) | packedWord & 0xFFFC03FF;
    LOWORD(v2) = ((_WORD)v2 << 10) | packedWord & 3;
    v3 = *(_DWORD *)(uintptr_t)(v0 + 32) - 1;
    LOWORD(bitmap[0]) = v2;
    bitmap[0] |= 4 * v3;
    return Rules_AddBitmapValue(bitmap, 4);
  }
  LOBYTE(packedWord) = packedWord | 2;
  bitmap[0] = packedWord;
  bitmap[0] = ((unsigned __int8)(*(_DWORD *)(uintptr_t)(v0 + 40) - 1) << 10) | packedWord & 0xFFFC03FF;
  LOWORD(bitmap[0]) &= 0xFC03u;
  return Rules_AddBitmapValue(bitmap, 4);
}
// 4B7705: variable 'v0' is possibly undefined

//----- (004B77D0) --------------------------------------------------------
int __fastcall PP_MakeConst27(int a1, int a2)
{
  int v2; // ecx
  int v3; // eax
  _DWORD v5[3]; // [esp+0h] [ebp-Ch] BYREF

  v5[2] = a1;
  Mem_AllocArray(v5, 4);
  v3 = *(_DWORD *)(uintptr_t)(v2 + 40);
  LOBYTE(v5[0]) = 0;
  v5[0] |= (unsigned __int8)(v3 - 1);
  return Rules_AddBitmapValue(v5, 4);
}
// 4B77E5: variable 'v2' is possibly undefined

//----- (004B7810) --------------------------------------------------------
int PP_MakeConst28(void)
{
  _DWORD *fieldNode; // ecx
  unsigned __int8 fieldMax; // al
  int fieldValue; // eax
  int valueLowBits; // eax
  int valueHighBits; // eax
  int v6; // eax
  _DWORD bitmapData[5]; // [esp+0h] [ebp-14h] BYREF

  Mem_AllocArray(bitmapData, 4);
  fieldMax = fieldNode[10] - 1;
  BYTE2(bitmapData[0]) = 0;
  bitmapData[0] |= fieldMax << 16;
  if ( *fieldNode == 17 || *fieldNode == 15 )
  {
    if ( (fieldNode[2] & 0x3F8000) != 0 )
    {
      LOBYTE(bitmapData[0]) |= 2u;
      LOWORD(bitmapData[0]) &= 0xFE02u;
      v6 = fieldNode[3];
      BYTE1(bitmapData[0]) &= 1u;
      bitmapData[0] |= (unsigned __int8)((unsigned int)(v6 << 18) >> 24) >> 1 << 9;
    }
    else
    {
      LOBYTE(bitmapData[0]) = bitmapData[0] & 0xFC | 1;
      fieldValue = fieldNode[3];
      LOWORD(bitmapData[0]) &= 0xFE03u;
      bitmapData[0] |= 4 * (fieldValue & 0x7F);
      BYTE1(bitmapData[0]) &= 1u;
    }
    return Rules_AddBitmapValue(bitmapData, 4);
  }
  else
  {
    LOBYTE(bitmapData[0]) |= 3u;
    valueLowBits = fieldNode[3] & 0x7F;
    LOWORD(bitmapData[0]) &= 0xFE03u;
    bitmapData[0] |= 4 * valueLowBits;
    valueHighBits = fieldNode[3] << 18 >> 25;
    BYTE1(bitmapData[0]) &= 1u;
    bitmapData[0] |= (valueHighBits & 0x7F) << 9;
    return Rules_AddBitmapValue(bitmapData, 4);
  }
}
// 4B7825: variable 'v0' is possibly undefined

//----- (004B7940) --------------------------------------------------------
signed int __fastcall Rules_BuildFieldRangeConstraintNode(int firstField, int secondField)
{
  int v3; // ecx
  char v4; // al
  char v5; // al
  int v6; // eax
  int comparisonSymbol; // edx
  signed int testNode; // eax
  int v10; // ecx
  signed int v11; // eax
  int v12; // edx
  int v13; // ecx
  signed int v14; // eax
  int v15; // edx
  _DWORD bitmapData[4]; // [esp+0h] [ebp-10h] BYREF

  Mem_AllocArray(bitmapData, 4);
  if ( (*(_BYTE *)(uintptr_t)(v3 + 9) & 0x40) != 0
    || *(int *)(uintptr_t)(v3 + 40) <= 0
    || (*(_BYTE *)(uintptr_t)(secondField + 9) & 0x40) != 0
    || *(int *)(uintptr_t)(secondField + 40) <= 0 )
  {
    if ( (*(_BYTE *)(uintptr_t)(v3 + 8) & 1) != 0 )
      comparisonSymbol = g_ClipsSymbolNeq;
    else
      comparisonSymbol = g_ClipsSymbolEq;
    testNode = AST_NewNode(10, comparisonSymbol);
    v11 = PP_MakeLowTierConst(v10, testNode, v10);
    *(_DWORD *)(uintptr_t)(v12 + 6) = v11;
    v14 = PP_MakeLowTierConst(secondField, v12, v13);
    *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v15 + 6) + 10) = v14;
    return v15;
  }
  else
  {
    LOBYTE(bitmapData[0]) &= 0xFCu;
    v4 = *(_DWORD *)(uintptr_t)(v3 + 40) - 1;
    LOWORD(bitmapData[0]) &= 0xFE03u;
    bitmapData[0] |= 4 * (v4 & 0x7F);
    v5 = *(_DWORD *)(uintptr_t)(secondField + 40) - 1;
    BYTE1(bitmapData[0]) &= 1u;
    bitmapData[0] |= (v5 & 0x7F) << 9;
    if ( (*(_BYTE *)(uintptr_t)(v3 + 8) & 1) != 0 )
      LOBYTE(bitmapData[0]) |= 2u;
    else
      LOBYTE(bitmapData[0]) |= 1u;
    v6 = Rules_AddBitmapValue(bitmapData, 4);
    return AST_NewNode(22, v6);
  }
}
// 4B7956: variable 'v3' is possibly undefined
// 4B7A1C: variable 'v10' is possibly undefined
// 4B7A21: variable 'v12' is possibly undefined
// 4B7A26: variable 'v13' is possibly undefined
// 4B7A2B: variable 'v15' is possibly undefined
// 54E658: using guessed type int dword_54E658;
// 54E668: using guessed type int dword_54E668;

//----- (004B7A50) --------------------------------------------------------
signed int  Rules_BuildFieldRangeOrValueConstraintNode(int firstField, int secondField)
{
  int v4; // ecx
  char firstFieldMax; // al
  unsigned int packedBits; // eax
  int valueBitmapValue; // eax
  int firstFlags; // eax
  _DWORD *v10; // ecx
  char firstRangeMax; // al
  int v12; // eax
  int secondFieldValue; // eax
  int rangeBitmapValue; // eax
  int comparisonSymbol; // edx
  signed int testNode; // eax
  int v17; // ecx
  signed int firstConstNode; // eax
  int v19; // edx
  int v20; // ecx
  signed int secondConstNode; // eax
  int v22; // edx
  unsigned int rangeBitmapData; // [esp+0h] [ebp-20h] BYREF
  int rangeBitmapHigh; // [esp+4h] [ebp-1Ch]
  _DWORD bitmapData[6]; // [esp+8h] [ebp-18h] BYREF

  if ( (*(_BYTE *)(uintptr_t)(firstField + 9) & 0x40) != 0
    || *(int *)(uintptr_t)(firstField + 40) <= 0
    || (*(_BYTE *)(uintptr_t)(secondField + 9) & 0x40) != 0
    || *(int *)(uintptr_t)(secondField + 40) <= 0 )
  {
    if ( *(int *)(uintptr_t)(firstField + 40) <= 0
      || *(_DWORD *)(uintptr_t)firstField != 15
      || (firstFlags = *(_DWORD *)(uintptr_t)(firstField + 8), (firstFlags & 0x3F8000) != 0)
      && ((firstFlags & 0x3F8000) != 0x8000 || (*(_WORD *)(uintptr_t)(firstField + 10) & 0x1FC0) != 0)
      || *(int *)(uintptr_t)(secondField + 40) <= 0
      || *(_DWORD *)(uintptr_t)secondField != 15
      || (*(_DWORD *)(uintptr_t)(secondField + 8) & 0x3F8000) != 0 && (*(_WORD *)(uintptr_t)(secondField + 10) & 0x1FC0) != 0 )
    {
      if ( (*(_BYTE *)(uintptr_t)(firstField + 8) & 1) != 0 )
        comparisonSymbol = g_ClipsSymbolNeq;
      else
        comparisonSymbol = g_ClipsSymbolEq;
      testNode = AST_NewNode(10, comparisonSymbol);
      firstConstNode = PP_ParsePrimary(v17, testNode, v17);
      *(_DWORD *)(uintptr_t)(v19 + 6) = firstConstNode;
      secondConstNode = PP_ParsePrimary(secondField, v19, v20);
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v22 + 6) + 10) = secondConstNode;
      return v22;
    }
    else
    {
      Mem_AllocArray(&rangeBitmapData, 8);
      LOBYTE(rangeBitmapData) = rangeBitmapData & 0xFC;
      firstRangeMax = v10[10] - 1;
      LOWORD(rangeBitmapData) = rangeBitmapData & 0xFE03;
      rangeBitmapData |= 4 * (firstRangeMax & 0x7F);
      v12 = (unsigned __int8)*(_DWORD *)(uintptr_t)(secondField + 28);
      HIWORD(rangeBitmapData) &= 0xFE01u;
      rangeBitmapData |= v12 << 17;
      LOBYTE(v12) = *(_DWORD *)(uintptr_t)(secondField + 40) - 1;
      HIBYTE(rangeBitmapData) &= 1u;
      rangeBitmapData |= (unsigned __int8)v12 << 25;
      if ( (v10[2] & 0x3F8000) != 0 )
      {
        BYTE1(rangeBitmapData) &= ~2u;
        rangeBitmapData = ((unsigned __int8)(v10[3] << 18 >> 24) >> 1 << 10) | rangeBitmapData & 0xFFFE03FF;
      }
      else
      {
        BYTE1(rangeBitmapData) |= 2u;
        rangeBitmapData = ((v10[3] & 0x7F) << 10) | rangeBitmapData & 0xFFFE03FF;
      }
      if ( (*(_DWORD *)(uintptr_t)(secondField + 8) & 0x3F8000) != 0 )
      {
        LOBYTE(rangeBitmapHigh) = rangeBitmapHigh & 0xFE;
        secondFieldValue = *(_DWORD *)(uintptr_t)(secondField + 12) << 18 >> 25;
      }
      else
      {
        LOBYTE(rangeBitmapHigh) = rangeBitmapHigh | 1;
        secondFieldValue = *(_DWORD *)(uintptr_t)(secondField + 12);
      }
      rangeBitmapHigh |= 2 * (secondFieldValue & 0x7F);
      if ( (v10[2] & 1) != 0 )
        LOBYTE(rangeBitmapData) = rangeBitmapData | 2;
      else
        LOBYTE(rangeBitmapData) = rangeBitmapData | 1;
      rangeBitmapValue = Rules_AddBitmapValue(&rangeBitmapData, 8);
      return AST_NewNode(24, rangeBitmapValue);
    }
  }
  else
  {
    Mem_AllocArray(bitmapData, 4);
    LOBYTE(bitmapData[0]) &= 0xFCu;
    firstFieldMax = *(_DWORD *)(uintptr_t)(v4 + 40) - 1;
    LOWORD(bitmapData[0]) &= 0xFE03u;
    bitmapData[0] |= 4 * (firstFieldMax & 0x7F);
    bitmapData[0] = ((unsigned __int8)*(_DWORD *)(uintptr_t)(secondField + 28) << 9) | bitmapData[0] & 0xFFFE01FF;
    packedBits = bitmapData[0] & 0xFF01FFFF;
    if ( *(int *)(uintptr_t)(secondField + 32) >= 0 )
      packedBits |= (((unsigned __int8)*(_DWORD *)(uintptr_t)(secondField + 40) - 1) & 0x7F) << 17;
    bitmapData[0] = packedBits;
    if ( (*(_BYTE *)(uintptr_t)(v4 + 8) & 1) != 0 )
      LOBYTE(bitmapData[0]) |= 2u;
    else
      LOBYTE(bitmapData[0]) |= 1u;
    valueBitmapValue = Rules_AddBitmapValue(bitmapData, 4);
    return AST_NewNode(23, valueBitmapValue);
  }
}
// 4B7C33: masking with 0x1 was optimized away because %var_1C.1 <= 0x1
// 4B7A9B: variable 'v4' is possibly undefined
// 4B7B88: variable 'v10' is possibly undefined
// 4B7CA6: variable 'v17' is possibly undefined
// 4B7CAB: variable 'v19' is possibly undefined
// 4B7CB0: variable 'v20' is possibly undefined
// 4B7CB5: variable 'v22' is possibly undefined
// 54E658: using guessed type int dword_54E658;
// 54E668: using guessed type int dword_54E668;

//----- (004B7D50) --------------------------------------------------------
int  Rules_ParseOrderedFactPattern(int readSource, int theToken)
{
  signed int patternNode; // esi
  char v5; // ah
  _DWORD *relationNode; // eax
  unsigned int *fieldList; // eax

  patternNode = AST_AllocNode();
  *(_DWORD *)(uintptr_t)patternNode = 17;
  v5 = *(_BYTE *)(uintptr_t)(patternNode + 8);
  *(_DWORD *)(uintptr_t)(patternNode + 32) = -1;
  *(_DWORD *)(uintptr_t)(patternNode + 40) = 1;
  *(_BYTE *)(uintptr_t)(patternNode + 8) = v5 & 0xFE;
  relationNode = (_DWORD *)(uintptr_t)AST_AllocNode();
  *(_DWORD *)(uintptr_t)(patternNode + 68) = relationNode;
  *relationNode = 2;
  *(_BYTE *)(uintptr_t)(*(_DWORD *)(uintptr_t)(patternNode + 68) + 8) &= ~1u;
  *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(patternNode + 68) + 4) = *(_DWORD *)(uintptr_t)(theToken + 4);
  IO_OutWriteToken(asc_509EB8);
  Parser_NextToken(readSource, theToken);
  if ( *(_DWORD *)(uintptr_t)theToken == 92 || *(_DWORD *)(uintptr_t)theToken == 91 )
  {
    AST_FreeNode(patternNode);
    Parser_ReportSyntaxError();
    return 0;
  }
  else
  {
    fieldList = Rules_ParsePatternFieldList(readSource, (int *)(uintptr_t)theToken, 0, 1, 1u, 0, 1);
    if ( fieldList )
    {
      *(_DWORD *)(uintptr_t)(patternNode + 64) = fieldList;
      if ( *(_DWORD *)(uintptr_t)theToken == 101 )
      {
        if ( !fieldList[17] )
        {
          IO_OutNewline();
          IO_OutNewline();
          IO_OutWriteToken(asc_509EEC);
        }
        return patternNode;
      }
      else
      {
        IO_OutNewline();
        IO_OutWriteToken(asc_509EB8);
        IO_OutWriteToken(*(char **)(uintptr_t)(theToken + 8));
        Parser_ReportSyntaxError();
        AST_FreeNode(patternNode);
        return 0;
      }
    }
    else
    {
      AST_FreeNode(patternNode);
      return 0;
    }
  }
}

//----- (004B7E60) --------------------------------------------------------
int __fastcall Rules_CreateInitialFactPatternNode(int a1, int a2)
{
  _DWORD *patternNode; // eax
  _DWORD *relationNode; // eax
  int v4; // edx
  int v5; // ecx
  signed int *initialFactSymbol; // eax
  int v7; // edx
  int v9; // ecx
  int currentModule; // eax
  int Name; // eax
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  signed int *deftemplateSymbol; // eax
  char v16; // dl
  _DWORD v17[4]; // [esp+0h] [ebp-10h] BYREF

  v17[2] = a1;
  if ( !Rules_FindImportExportConstruct(aDeftemplate_7, v17, aInitialFact, 1, 0) )
  {
    Rules_PrintWarningID((int)(intptr_t)aFactlhs, 1, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WWarning[0], (int)(intptr_t)aCreatingImplie, v9);
    currentModule = Module_GetCurrent();
    Name = Module_GetName(currentModule);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WWarning[0], Name, (int)(intptr_t)g_IO_LogicalNameTable_WWarning[0]);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WWarning[0], (int)(intptr_t)a__22, v12);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WWarning[0], (int)(intptr_t)aYouProbablyWan, v13);
    deftemplateSymbol = Str_Intern(aInitialFact, v14);
    Rules_CreateDeftemplateRecord((int)(intptr_t)deftemplateSymbol, v16);
  }
  patternNode = (_DWORD *)(uintptr_t)AST_AllocNode();
  *patternNode = 17;
  patternNode[8] = 0;
  patternNode[10] = 1;
  relationNode = (_DWORD *)(uintptr_t)AST_AllocNode();
  *(_DWORD *)(uintptr_t)(v4 + 68) = relationNode;
  *relationNode = 2;
  initialFactSymbol = Str_Intern(aInitialFact, v5);
  *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v7 + 68) + 4) = initialFactSymbol;
  return v7;
}
// 4B7EE0: variable 'v9' is possibly undefined
// 4B7F08: variable 'v12' is possibly undefined
// 4B7F17: variable 'v13' is possibly undefined
// 4B7F23: variable 'v14' is possibly undefined
// 4B7F28: variable 'v16' is possibly undefined
// 4B7EA3: variable 'v4' is possibly undefined
// 4B7EB1: variable 'v5' is possibly undefined
// 4B7EB6: variable 'v7' is possibly undefined
// 51A610: using guessed type char *off_51A610[6];

//----- (004B7F50) --------------------------------------------------------
int  Rules_ParseFactPatternRelation(int readSource, int theToken, int a3)
{
  int v5; // edx
  int deftemplate; // eax
  _BYTE *templateName; // ebx
  int currentModule; // eax
  _DWORD v10[5]; // [esp+0h] [ebp-14h] BYREF

  v10[3] = a3;
  if ( Rules_FindModuleSeparator(*(_BYTE **)(uintptr_t)(*(_DWORD *)(uintptr_t)(theToken + 4) + 16)) )
  {
    Module_ReportIllegalSpecifierError();
    return 0;
  }
  deftemplate = Rules_FindImportExportConstruct(aDeftemplate_7, v10, *(_BYTE **)(uintptr_t)(*(_DWORD *)(uintptr_t)(v5 + 4) + 16), 1, 0);
  if ( v10[0] > 1 )
  {
    Rules_ReportAmbiguousReferenceError((int)(intptr_t)aDeftemplate_7, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theToken + 4) + 16));
    return 0;
  }
  if ( !deftemplate )
  {
    templateName = *(_BYTE **)(uintptr_t)(*(_DWORD *)(uintptr_t)(theToken + 4) + 16);
    currentModule = Module_GetCurrent();
    if ( Rules_FindImportExportConflict(aDeftemplate_7, currentModule, templateName) )
    {
      Lexer_WarnImpliedTemplate((int)(intptr_t)aImpliedDefte_0, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theToken + 4) + 16), 0);
      return 0;
    }
    deftemplate = Rules_CreateDeftemplateRecord(*(_DWORD *)(uintptr_t)(theToken + 4), 1);
  }
  if ( (*(_BYTE *)(uintptr_t)(deftemplate + 24) & 1) != 0 )
    return Rules_ParseOrderedFactPattern(readSource, theToken);
  else
    return Rules_ParseDeftemplateFactPattern(readSource, (_DWORD *)(uintptr_t)deftemplate);
}
// 4B7F6F: variable 'v5' is possibly undefined

//----- (004B8030) --------------------------------------------------------
int * Rules_AddReservedPatternSymbol(int symbolName, int constructName)
{
  int v2; // ecx
  _DWORD *freeEntry; // ebx
  int *result; // eax

  v2 = symbolName;
  freeEntry = *(_DWORD **)(uintptr_t)(g_ClipsMemoryTable + 48);
  if ( freeEntry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = *freeEntry;
    result = (int *)(uintptr_t)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = (int *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0xC);
  }
  *result = v2;
  result[1] = constructName;
  result[2] = g_Rules_ReservedPatternSymbolList;
  g_Rules_ReservedPatternSymbolList = (int)(intptr_t)result;
  return result;
}
// 4B8050: variable 'v2' is possibly undefined
// 51B350: using guessed type int dword_51B350;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B8080) --------------------------------------------------------
int __fastcall Rules_IsReservedPatternSymbol(int symbolName, int constructName)
{
  int item; // ecx
  int storedConstruct; // edx
  int result; // eax

  item = g_Rules_ReservedPatternSymbolList;
  if ( !item )
    return 0;
  while ( strcmp_(symbolName, *(_DWORD *)(uintptr_t)item) )
  {
    item = *(_DWORD *)(uintptr_t)(item + 8);
    if ( !item )
      return 0;
  }
  storedConstruct = *(_DWORD *)(uintptr_t)(item + 4);
  if ( !storedConstruct )
    return 1;
  if ( !constructName )
    return 1;
  result = strcmp_(constructName, storedConstruct);
  if ( result )
    return 1;
  return result;
}
// 4B809E: variable 'v4' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51B350: using guessed type int dword_51B350;

//----- (004B80D0) --------------------------------------------------------
signed int __fastcall Rules_PrintReservedSymbolErrorMessage(int symbolName, int constructName)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx

  Rules_PrintErrorID((int)(intptr_t)aPattern, 1, 1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aTheSymbol, v3);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v4, v4);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aHasSpecialMean, v5);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aAndMayNotBeUse, v6);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], constructName, v7);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__8, v8);
}
// 4B80F2: variable 'v3' is possibly undefined
// 4B80FE: variable 'v4' is possibly undefined
// 4B810D: variable 'v5' is possibly undefined
// 4B811C: variable 'v6' is possibly undefined
// 4B8128: variable 'v7' is possibly undefined
// 4B8137: variable 'v8' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004B8140) --------------------------------------------------------
int  Rules_FindPatternParser(_DWORD *parserCursor, _DWORD *entityPtr)
{
  int current; // edx
  int callback_table; // edx
  int callback_address; // eax
  int result; // eax

  current = *parserCursor;
  if ( current )
  {
    if ( entityPtr )
    {
      callback_table = *(_DWORD *)(uintptr_t)(current + 4);
      callback_address = *(_DWORD *)(uintptr_t)(callback_table + 20);
      result = ((int (__fastcall *)(int))(uintptr_t)(unsigned int)callback_address)(*entityPtr);
      *entityPtr = result;
      if ( result )
        return result;
      result = *(_DWORD *)(uintptr_t)(current + 92);
      *parserCursor = result;
    }
    else
    {
      Rules_ReportSystemError(parserCursor, 1);
      result = IO_RunRouterExitCallbacks();
    }
  }
  else
  {
    result = g_PatternParserListHead;
    *parserCursor = g_PatternParserListHead;
    *entityPtr = 0;
  }
  while ( !*entityPtr )
  {
    current = *parserCursor;
    if ( !current )
      break;
    callback_table = *(_DWORD *)(uintptr_t)(current + 4);
    callback_address = *(_DWORD *)(uintptr_t)(callback_table + 20);
    result = ((int (__fastcall *)(int))(uintptr_t)(unsigned int)callback_address)(*entityPtr);
    *entityPtr = result;
    if ( result )
      break;
    result = *(_DWORD *)(uintptr_t)(current + 92);
    *parserCursor = result;
  }
  return result;
}
// 51B348: using guessed type int dword_51B348;

//----- (004B81C0) --------------------------------------------------------
int  Rules_DeletePatternNetworkForType(int result, int *a2, int a3)
{
  int v3; // ecx

  if ( g_CLIPS_PatternParserTableByTypeId[result] )
  {
    Rules_ReleaseJoinNetworkNodeChain(*a2);
    return (*(int (__cdecl **)(int))(uintptr_t)(*(int *)((char *)g_CLIPS_PatternParserTableByTypeId + v3) + 28))(a3);
  }
  return result;
}
// 4B81DA: variable 'v3' is possibly undefined
// 54E820: using guessed type int dword_54E820[];

//----- (004B81F0) --------------------------------------------------------
signed int  Rules_AddPatternParser(
        int name,
        int priority,
        int recognizeFunction,
        int entityType,
        int parseFunction,
        int postAnalysisFunction,
        int addPatternFunction,
        int removePatternFunction,
        int genJNConstantFunction,
        int replaceGetJNValueFunction,
        int genGetJNValueFunction,
        int genCompareJNValuesFunction,
        int genPNConstantFunction,
        int replaceGetPNValueFunction,
        int genGetPNValueFunction,
        int genComparePNValuesFunction,
        int returnUserDataFunction,
        int copyUserDataFunction,
        int markIRPatternFunction,
        int incrementalResetFunction,
        int initialPatternFunction,
        int codeReferenceFunction)
{
  int prevNode; // ecx
  _DWORD *freeEntry; // ebp
  _DWORD *newParser; // eax
  int parserIndex; // edx
  int newParserAddr; // ebx
  int listHead; // edi
  int node; // eax

  prevNode = 0;
  if ( g_PatternParserCount >= 8 )
    return 0;
  freeEntry = *(_DWORD **)(uintptr_t)(g_ClipsMemoryTable + 384);
  if ( freeEntry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 384);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 384) = *freeEntry;
    newParser = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
  }
  else
  {
    newParser = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x60);
  }
  newParser[1] = entityType;
  newParser[3] = recognizeFunction;
  newParser[22] = priority;
  *newParser = name;
  newParser[4] = parseFunction;
  newParser[5] = postAnalysisFunction;
  newParser[6] = addPatternFunction;
  newParser[7] = removePatternFunction;
  newParser[8] = genJNConstantFunction;
  newParser[9] = replaceGetJNValueFunction;
  newParser[10] = genGetJNValueFunction;
  newParser[11] = genCompareJNValuesFunction;
  newParser[12] = genPNConstantFunction;
  newParser[13] = replaceGetPNValueFunction;
  newParser[14] = genGetPNValueFunction;
  newParser[15] = genComparePNValuesFunction;
  newParser[16] = returnUserDataFunction;
  newParser[17] = copyUserDataFunction;
  newParser[18] = markIRPatternFunction;
  newParser[19] = incrementalResetFunction;
  newParser[20] = initialPatternFunction;
  newParser[21] = codeReferenceFunction;
  parserIndex = g_PatternParserCount;
  newParser[2] = g_PatternParserCount;
  ++parserIndex;
  newParserAddr = (int)(intptr_t)newParser;
  listHead = g_PatternParserListHead;
  g_Rules_PatternParserTable[parserIndex] = (int)(intptr_t)newParser;
  g_PatternParserCount = parserIndex;
  if ( !listHead )
  {
    newParser[23] = 0;
    g_PatternParserListHead = (int)(intptr_t)newParser;
    return 1;
  }
  node = listHead;
  do
  {
    if ( priority >= *(_DWORD *)(uintptr_t)(node + 88) )
      break;
    prevNode = node;
    node = *(_DWORD *)(uintptr_t)(node + 92);
  }
  while ( node );
  if ( !prevNode )
  {
    *(_DWORD *)(uintptr_t)(newParserAddr + 92) = g_PatternParserListHead;
    g_PatternParserListHead = newParserAddr;
    return 1;
  }
  *(_DWORD *)(uintptr_t)(newParserAddr + 92) = node;
  *(_DWORD *)(uintptr_t)(prevNode + 92) = newParserAddr;
  return 1;
}
// 4B82E8: conditional instruction was optimized away because edi.4!=0
// 4B8303: variable 'v24' is possibly undefined
// 51B348: using guessed type int dword_51B348;
// 51B34C: using guessed type int dword_51B34C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E81C: using guessed type int dword_54E81C[];

//----- (004B8360) --------------------------------------------------------
int  Rules_FindPatternParserByName(int name)
{
  int node; // ecx
  int current; // ecx

  node = g_PatternParserListHead;
  if ( !g_PatternParserListHead )
    return 0;
  while ( strcmp_(node, name) )
  {
    node = *(_DWORD *)(uintptr_t)(current + 92);
    if ( !node )
      return 0;
  }
  return current;
}
// 4B837C: variable 'v3' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51B348: using guessed type int dword_51B348;

//----- (004B8390) --------------------------------------------------------
int  Rules_GetPatternParserByTypeID(int typeId)
{
  return g_CLIPS_PatternParserTableByTypeId[typeId];
}
// 54E820: using guessed type int dword_54E820[];

//----- (004B83A0) --------------------------------------------------------
int  Rules_PrintPatternNetworkNodeTrace(int logicalName, int patternNode, int a3)
{
  int v6; // ecx
  int v7; // edx
  int v8; // edx
  int v9; // ecx
  char v11; // [esp+0h] [ebp-Ch]
  char v12; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(a3, patternNode, logicalName, (int)(intptr_t)aNullNull, v11);
  if ( *(_DWORD *)(uintptr_t)(v7 + 8) )
    Output_WriteFormatted(
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefruleCodeGenItem + 20) + 8),
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(patternNode + 8) + 4) % a3,
      logicalName,
      (int)(intptr_t)aSD_DD_4,
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefruleCodeGenItem + 20) + 8));
  else
    Output_WriteFormatted(v6, 0, logicalName, (int)(intptr_t)aNull_15, v12);
  return Output_WriteFormatted(v9, v8, logicalName, (int)(intptr_t)aDDD00DD, *(_BYTE *)(uintptr_t)(patternNode + 12) & 1);
}
// 4B83B1: variable 'v11' is possibly undefined
// 4B83B6: variable 'v7' is possibly undefined
// 4B83C6: variable 'v6' is possibly undefined
// 4B83C6: variable 'v12' is possibly undefined
// 4B8403: variable 'v9' is possibly undefined
// 4B8403: variable 'v8' is possibly undefined
// 54E884: using guessed type int dword_54E884;

//----- (004B8450) --------------------------------------------------------
signed int  Rules_PatternChainHasActiveType80Callback(_DWORD *patternList)
{
  _DWORD *node; // edx
  int parser; // ebx

  node = patternList;
  if ( !patternList )
    return 0;
  while ( 1 )
  {
    if ( *node == 80 )
    {
      parser = node[6];
      if ( parser )
      {
        if ( *(_DWORD *)(uintptr_t)(parser + 20) && (*(int (**)(void))(uintptr_t)(parser + 20))() )
          break;
      }
    }
    node = (_DWORD *)(uintptr_t)node[17];
    if ( !node )
      return 0;
  }
  return 1;
}
// 4B8478: variable 'v1' is possibly undefined

//----- (004B8490) --------------------------------------------------------
unsigned int * Rules_ParsePatternFieldList(
        int readSource,
        int *theToken,
        int theSlot,
        int multifieldSlot,
        unsigned int slotNumber,
        int *slotConstraint,
        int startPosition)
{
  int tokenType; // ebx
  signed int newField; // eax
  unsigned int *fieldNode; // ebx
  int lastField; // ecx
  int node; // ebx
  int constraintNode; // eax
  int nodeType; // ebp
  signed int wrapperNode; // eax
  char nodeFlags; // dh
  int v19; // esi
  int v20; // ecx
  int *v21; // eax
  signed int v22; // eax
  int v23; // ecx
  int *v24; // eax
  int errorFlag; // [esp+0h] [ebp-28h] BYREF
  int startIndex; // [esp+4h] [ebp-24h]
  int slotSymbol; // [esp+8h] [ebp-20h]
  unsigned int *fieldList; // [esp+Ch] [ebp-1Ch]
  int multifieldMode; // [esp+10h] [ebp-18h]
  int multiFieldCount; // [esp+14h] [ebp-14h]
  int singleFieldCount; // [esp+18h] [ebp-10h]

  multifieldMode = multifieldSlot;
  slotSymbol = theSlot;
  fieldList = 0;
  singleFieldCount = 0;
  errorFlag = 0;
  multiFieldCount = 0;
  tokenType = *theToken;
  startIndex = startPosition;
  if ( tokenType == 101 )
  {
LABEL_24:
    if ( !fieldList && !multifieldMode )
    {
      Parser_ReportSyntaxError();
      return 0;
    }
    node = (int)(intptr_t)fieldList;
    if ( !fieldList )
    {
LABEL_33:
      if ( multifieldMode )
      {
        wrapperNode = AST_AllocNode();
        *(_DWORD *)(uintptr_t)wrapperNode = 18;
        nodeFlags = *(_BYTE *)(uintptr_t)(wrapperNode + 8);
        *(_DWORD *)(uintptr_t)(wrapperNode + 16) = slotConstraint;
        *(_BYTE *)(uintptr_t)(wrapperNode + 8) = nodeFlags | 4;
        *(_DWORD *)(uintptr_t)(wrapperNode + 68) = fieldList;
        *(_DWORD *)(uintptr_t)(wrapperNode + 36) = slotSymbol;
        *(_DWORD *)(uintptr_t)(wrapperNode + 40) = slotNumber;
        *(_DWORD *)(uintptr_t)(wrapperNode + 32) = startIndex;
        fieldList = (unsigned int *)(uintptr_t)wrapperNode;
        Rules_ComputePatternFieldPositions(*(_DWORD **)(uintptr_t)(wrapperNode + 68));
      }
      return fieldList;
    }
    while ( !slotConstraint )
    {
      if ( *(_DWORD *)(uintptr_t)node == 15 )
      {
        constraintNode = Rules_CreateLHSParseNode();
LABEL_30:
        *(_DWORD *)(uintptr_t)(node + 16) = constraintNode;
        AST_Free(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(node + 16) + 18));
        AST_Free(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(node + 16) + 22));
        *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(node + 16) + 18) = AST_NewNode(2, g_Clips_NegativeInfinitySymbol);
        *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(node + 16) + 22) = AST_NewNode(2, g_ClipsPositiveInfinitySymbol);
        nodeType = *(_DWORD *)(uintptr_t)node;
        *(_BYTE *)(uintptr_t)(node + 8) |= 0x10u;
        if ( nodeType == 18 || nodeType == 16 )
        {
          v19 = Rules_CreateLHSParseNode();
          Rules_UpdateCETypeFlag(4u, v19);
          *(_BYTE *)(uintptr_t)(v20 + 2) &= ~1u;
          *(_DWORD *)(uintptr_t)(v20 + 26) = *(_DWORD *)(uintptr_t)(node + 16);
          *(_DWORD *)(uintptr_t)(node + 16) = v20;
          if ( g_ClipsPositiveInfinitySymbol != *(_DWORD *)(uintptr_t)(*(int *)((char *)slotConstraint + 22) + 2) )
          {
            AST_Free(*(_DWORD *)(uintptr_t)(v20 + 22));
            v21 = Rules_AddIntegerValue(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(int *)((char *)slotConstraint + 22) + 2) + 16) - singleFieldCount);
            v22 = AST_NewNode(1, (int)(intptr_t)v21);
            *(_DWORD *)(uintptr_t)(v23 + 22) = v22;
          }
          if ( multiFieldCount == 1 && g_Clips_NegativeInfinitySymbol != *(_DWORD *)(uintptr_t)(*(int *)((char *)slotConstraint + 18) + 2) )
          {
            AST_Free(*(_DWORD *)(uintptr_t)(v19 + 18));
            v24 = Rules_AddIntegerValue(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(int *)((char *)slotConstraint + 18) + 2) + 16) - singleFieldCount);
            *(_DWORD *)(uintptr_t)(v19 + 18) = AST_NewNode(1, (int)(intptr_t)v24);
          }
        }
      }
      node = *(_DWORD *)(uintptr_t)(node + 64);
      if ( !node )
        goto LABEL_33;
    }
    constraintNode = Rules_CloneLHSParseNode(slotConstraint);
    goto LABEL_30;
  }
  while ( 1 )
  {
    if ( *theToken == 17 || *theToken == 18 )
    {
      newField = AST_AllocNode();
      *(_DWORD *)(uintptr_t)newField = *theToken;
      fieldNode = (unsigned int *)(uintptr_t)newField;
      *(_BYTE *)(uintptr_t)(newField + 8) &= ~1u;
      Parser_NextToken(readSource, (int)(intptr_t)theToken);
    }
    else
    {
      fieldNode = Rules_ParseConnectedConstraint(readSource, &errorFlag);
      if ( !fieldNode )
      {
        AST_FreeNode((int)(intptr_t)fieldList);
        return 0;
      }
    }
    if ( *theToken != 101 && multifieldMode == 1 )
    {
      IO_OutNewline();
      IO_OutWriteToken(asc_50A02C);
      IO_OutWriteToken((char *)(uintptr_t)theToken[2]);
    }
    if ( *fieldNode == 17 || *fieldNode == 15 )
      ++singleFieldCount;
    else
      ++multiFieldCount;
    fieldNode[9] = slotSymbol;
    fieldNode[10] = slotNumber;
    fieldNode[8] = startPosition++;
    if ( !multifieldMode )
      break;
    if ( lastField )
      *(_DWORD *)(uintptr_t)(lastField + 64) = fieldNode;
    else
      fieldList = fieldNode;
    if ( *theToken == 101 )
      goto LABEL_24;
  }
  if ( slotConstraint )
  {
    fieldNode[4] = (unsigned int)(intptr_t)slotConstraint;
  }
  else if ( *fieldNode == 15 )
  {
    fieldNode[4] = Rules_CreateLHSParseNode();
  }
  else
  {
    fieldNode[4] = multifieldMode;
  }
  return fieldNode;
}
// 4B85A2: variable 'v12' is possibly undefined
// 4B86E3: variable 'v20' is possibly undefined
// 4B8726: variable 'v23' is possibly undefined
// 54DD60: using guessed type int dword_54DD60;
// 54DD68: using guessed type int dword_54DD68;

//----- (004B8780) --------------------------------------------------------
int  Rules_ComputePatternFieldPositions(_DWORD *fieldList)
{
  _DWORD *node; // edx
  int result; // eax
  int multifieldCount; // ecx
  char singleFieldIndex; // di
  char i; // si
  int fieldNode; // edx
  int v8; // ebp
  unsigned int v9; // ecx
  char v10; // bh
  int v11; // ebp
  __int16 v12; // cx
  int v13; // ebp
  int v14; // ecx
  int subField; // ebx
  bool j; // zf
  int v17; // ecx
  int v18; // ecx
  unsigned int v19; // ebp
  int v20; // ecx
  int v21; // ecx
  char singleFieldsAfter; // [esp+4h] [ebp-28h]
  char singleFieldsRemaining; // [esp+8h] [ebp-24h]
  int multifieldsAfter; // [esp+Ch] [ebp-20h]
  char multifieldsRemaining; // [esp+10h] [ebp-1Ch]

  node = fieldList;
  result = 0;
  multifieldCount = 0;
  singleFieldIndex = 0;
  for ( i = 0; node; node = (_DWORD *)(uintptr_t)node[16] )
  {
    if ( *node == 15 || *node == 17 )
      ++result;
    else
      ++multifieldCount;
  }
  fieldNode = (int)(intptr_t)fieldList;
  if ( fieldList )
  {
    multifieldsAfter = multifieldCount - 1;
    multifieldsRemaining = multifieldCount;
    singleFieldsRemaining = result;
    singleFieldsAfter = result - 1;
    do
    {
      *(_BYTE *)(uintptr_t)(fieldNode + 12) &= 0x80u;
      v8 = singleFieldIndex & 0x7F | *(_DWORD *)(uintptr_t)(fieldNode + 12);
      v9 = *(_DWORD *)(uintptr_t)(fieldNode + 8) & 0xFFC07FFF;
      *(_DWORD *)(uintptr_t)(fieldNode + 8) = v9;
      *(_DWORD *)(uintptr_t)(fieldNode + 8) = ((i & 0x7F) << 15) | v9;
      v10 = *(_BYTE *)(uintptr_t)(fieldNode + 9);
      *(_DWORD *)(uintptr_t)(fieldNode + 12) = v8;
      v11 = *(_DWORD *)(uintptr_t)fieldNode;
      *(_BYTE *)(uintptr_t)(fieldNode + 9) = v10 | 0x40;
      if ( v11 == 15 || v11 == 17 )
      {
        v12 = *(_WORD *)(uintptr_t)(fieldNode + 10);
        *(_WORD *)(uintptr_t)(fieldNode + 12) &= 0xC07Fu;
        v13 = ((singleFieldsAfter & 0x7F) << 7) | *(_DWORD *)(uintptr_t)(fieldNode + 12);
        *(_WORD *)(uintptr_t)(fieldNode + 10) = v12 & 0xE03F;
        v14 = *(_DWORD *)(uintptr_t)(fieldNode + 8);
        result = (multifieldsRemaining & 0x7F) << 22;
        *(_DWORD *)(uintptr_t)(fieldNode + 12) = v13;
        *(_DWORD *)(uintptr_t)(fieldNode + 8) = result | v14;
      }
      else
      {
        *(_WORD *)(uintptr_t)(fieldNode + 12) &= 0xC07Fu;
        *(_DWORD *)(uintptr_t)(fieldNode + 12) |= (singleFieldsRemaining & 0x7F) << 7;
        *(_WORD *)(uintptr_t)(fieldNode + 10) &= 0xE03Fu;
        result = (multifieldsAfter & 0x7F) << 22;
        *(_DWORD *)(uintptr_t)(fieldNode + 8) |= result;
      }
      subField = *(_DWORD *)(uintptr_t)(fieldNode + 68);
      for ( j = subField == 0; subField; j = subField == 0 )
      {
        result = subField;
        if ( !j )
        {
          do
          {
            v17 = *(_DWORD *)(uintptr_t)(fieldNode + 12);
            *(_BYTE *)(uintptr_t)(result + 12) &= 0x80u;
            *(_DWORD *)(uintptr_t)(result + 12) |= v17 & 0x7F;
            v18 = *(_DWORD *)(uintptr_t)(fieldNode + 12);
            *(_WORD *)(uintptr_t)(result + 12) &= 0xC07Fu;
            *(_DWORD *)(uintptr_t)(result + 12) |= v18 & 0x3F80;
            v19 = *(_DWORD *)(uintptr_t)(result + 8) & 0xFFC07FFF;
            v20 = *(_DWORD *)(uintptr_t)(fieldNode + 8) & 0x3F8000;
            *(_DWORD *)(uintptr_t)(result + 8) = v19;
            *(_DWORD *)(uintptr_t)(result + 8) = v20 | v19;
            v21 = *(_DWORD *)(uintptr_t)(fieldNode + 8);
            *(_WORD *)(uintptr_t)(result + 10) &= 0xE03Fu;
            *(_DWORD *)(uintptr_t)(result + 8) |= v21 & 0x1FC00000;
            *(_BYTE *)(uintptr_t)(result + 9) |= 0x40u;
            result = *(_DWORD *)(uintptr_t)(result + 64);
          }
          while ( result );
        }
        subField = *(_DWORD *)(uintptr_t)(subField + 68);
      }
      if ( *(_DWORD *)(uintptr_t)fieldNode == 15 || *(_DWORD *)(uintptr_t)fieldNode == 17 )
      {
        ++singleFieldIndex;
        --singleFieldsRemaining;
        --singleFieldsAfter;
      }
      else
      {
        ++i;
        result = --multifieldsAfter;
        --multifieldsRemaining;
      }
      fieldNode = *(_DWORD *)(uintptr_t)(fieldNode + 64);
    }
    while ( fieldNode );
  }
  return result;
}

//----- (004B8970) --------------------------------------------------------
unsigned int * Rules_ParseConnectedConstraint(int readSource, _DWORD *errorFlag)
{
  int v3; // ecx
  unsigned int *andChain; // ebp
  unsigned int *orChain; // edi
  int *token; // ecx
  char v8; // ah
  unsigned int *term; // eax
  int v10; // ecx
  signed int v11; // eax
  unsigned int v12; // ebx
  char v13; // dl
  int v14; // ecx
  unsigned int *topNode; // [esp+4h] [ebp-1Ch]
  int connectorType; // [esp+8h] [ebp-18h]

  andChain = Rules_ParseSingleFieldConstraintTerm(readSource, errorFlag);
  orChain = andChain;
  if ( *errorFlag == 1 )
    return 0;
  Parser_NextToken(readSource, v3);
  if ( *andChain != 15 && *andChain != 16 || (v8 = *((_BYTE *)andChain + 8), (v8 & 1) != 0) || *token == 92 )
  {
    v11 = AST_AllocNode();
    v12 = *andChain;
    topNode = (unsigned int *)(uintptr_t)v11;
    *(_DWORD *)(uintptr_t)(v11 + 68) = andChain;
    v13 = *(_BYTE *)(uintptr_t)(v11 + 8) & 0xFE;
    *(_DWORD *)(uintptr_t)v11 = (v12 == 16) + 17;
    *(_BYTE *)(uintptr_t)(v11 + 8) = v13;
  }
  else
  {
    topNode = andChain;
    andChain = 0;
    *((_BYTE *)orChain + 8) = v8 | 8;
    orChain = 0;
  }
  while ( *token == 92 || *token == 91 )
  {
    connectorType = *token;
    Parser_NextToken(readSource, (int)(intptr_t)token);
    term = Rules_ParseSingleFieldConstraintTerm(readSource, errorFlag);
    if ( *errorFlag == 1 )
    {
      AST_FreeNode((int)(intptr_t)topNode);
      return 0;
    }
    if ( connectorType == 92 )
    {
      if ( andChain )
        andChain[17] = (unsigned int)(intptr_t)term;
      else
        topNode[17] = (unsigned int)(intptr_t)term;
      andChain = term;
      orChain = term;
      Parser_NextToken(readSource, v10);
    }
    else if ( connectorType == 91 )
    {
      if ( orChain )
      {
        orChain[16] = (unsigned int)(intptr_t)term;
      }
      else
      {
        andChain = term;
        topNode[17] = (unsigned int)(intptr_t)term;
      }
      orChain = term;
      Parser_NextToken(readSource, v10);
    }
    else
    {
      Rules_ReportSystemError(v10, 1);
      IO_RunRouterExitCallbacks();
      Parser_NextToken(readSource, v14);
    }
  }
  if ( !Rules_CheckMixedWildcardConstraint(topNode) )
    return topNode;
  *errorFlag = 1;
  AST_FreeNode((int)(intptr_t)topNode);
  return 0;
}
// 4B899D: variable 'v3' is possibly undefined
// 4B89BA: variable 'v7' is possibly undefined
// 4B8A2A: variable 'v10' is possibly undefined
// 4B8AC4: variable 'v14' is possibly undefined

//----- (004B8B10) --------------------------------------------------------
signed int  Rules_CheckMixedWildcardConstraint(_DWORD *constraintNode)
{
  BOOL hasMultifield; // esi
  int hasSingleField; // ebx
  int hasConstant; // edi
  int *term; // edx
  _BYTE *v6; // eax
  int v7; // ecx
  int *i; // [esp+0h] [ebp-24h]
  int v9; // [esp+4h] [ebp-20h]
  int v10; // [esp+8h] [ebp-1Ch]

  hasMultifield = 0;
  hasSingleField = 0;
  hasConstant = 0;
  v10 = 0;
  v9 = 0;
  if ( *constraintNode == 15 )
    hasSingleField = 1;
  else
    hasMultifield = *constraintNode == 16;
  for ( i = (int *)(uintptr_t)constraintNode[17]; i; i = (int *)(uintptr_t)i[17] )
  {
    term = i;
    do
    {
      if ( *term == 15 )
      {
        hasSingleField = 1;
        goto LABEL_7;
      }
      if ( *term == 16 )
      {
        hasMultifield = 1;
        goto LABEL_7;
      }
      if ( Rules_TagIsConstantType(*term) )
      {
        hasConstant = 1;
        goto LABEL_7;
      }
      if ( *term == 94 )
      {
        v6 = Rules_ApplyCEKeywordFlags();
        if ( (*v6 & 1) != 0 )
          goto LABEL_22;
        if ( (char)v6[1] < 0 )
        {
          v9 = 1;
LABEL_22:
          AST_DecrementNodeRefCount(v6);
          goto LABEL_7;
        }
        v10 = 1;
        AST_DecrementNodeRefCount(v6);
      }
LABEL_7:
      term = (int *)(uintptr_t)term[16];
    }
    while ( term );
  }
  if ( !hasSingleField && !hasConstant && !v10 )
    return 0;
  if ( !hasMultifield && !v9 )
    return 0;
  Rules_PrintErrorID((int)(intptr_t)aPattern, 2, 1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aSingleAndMulti, v7);
  return 1;
}
// 4B8B48: conditional instruction was optimized away because %var_24.4!=0
// 4B8B56: variable 'v4' is possibly undefined
// 4B8C3D: variable 'v7' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004B8C60) --------------------------------------------------------
unsigned int * Rules_ParseSingleFieldConstraintTerm(int readSource, _DWORD *errorFlag)
{
  signed int v4; // eax
  unsigned int *token; // ecx
  signed int nodeAddr; // edi
  _DWORD *v7; // edx
  unsigned int *node; // ebx
  unsigned int tokenType; // eax
  int v11; // ecx
  __int16 *v12; // eax
  int v13; // ecx
  __int16 *v14; // eax
  int v15; // ecx

  v4 = AST_AllocNode();
  nodeAddr = v4;
  node = (unsigned int *)(uintptr_t)v4;
  if ( *v7 == 90 )
  {
    Parser_NextToken(readSource, (int)(intptr_t)token);
    *(_BYTE *)(uintptr_t)(nodeAddr + 8) |= 1u;
  }
  else
  {
    *(_BYTE *)(uintptr_t)(v4 + 8) &= ~1u;
  }
  tokenType = *token;
  *node = *token;
  if ( tokenType == 2 )
  {
    if ( !strcmp_(token, asc_50A08C) )
    {
      v12 = (__int16 *)(uintptr_t)Parser_ParseRequiredFunctionCall(readSource, v11);
      if ( v12 )
      {
        *node = 94;
        node[14] = (unsigned int)(intptr_t)Rules_CECloneRestrictionExpr(v12);
        AST_Free(v13);
        return node;
      }
    }
    else
    {
      if ( strcmp_(v11, asc_50A090) )
      {
LABEL_5:
        node[1] = token[1];
        return node;
      }
      v14 = (__int16 *)(uintptr_t)Parser_ParseRequiredFunctionCall(readSource, (int)(intptr_t)token);
      if ( v14 )
      {
        *node = 93;
        node[14] = (unsigned int)(intptr_t)Rules_CECloneRestrictionExpr(v14);
        AST_Free(v15);
        return node;
      }
    }
    *errorFlag = 1;
    AST_FreeNode((int)(intptr_t)node);
    return 0;
  }
  if ( tokenType == 15 || tokenType == 16 || tokenType < 2 || tokenType == 3 || tokenType == 8 )
    goto LABEL_5;
  Parser_ReportSyntaxError();
  *errorFlag = 1;
  AST_FreeNode((int)(intptr_t)node);
  return 0;
}
// 4B8D4F: simplified comparisons for 'eax.4': ==0 || ==1 became <2u
// 4B8C71: variable 'v7' is possibly undefined
// 4B8C83: variable 'v5' is possibly undefined
// 4B8CC7: variable 'v11' is possibly undefined
// 4B8CE2: variable 'v13' is possibly undefined
// 4B8D38: variable 'v15' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004B8D90) --------------------------------------------------------
int * Rules_BuildConjunctionFromPatternList(int patternList)
{
  int *v2; // eax
  _DWORD *v3; // ecx
  int *rootNode; // edi
  int *andOrNormalized; // eax
  _DWORD *v6; // ecx
  int *fullyNormalized; // eax
  int *node; // edi
  _DWORD *i; // edx
  _DWORD *newAndNode; // eax
  int v11; // ecx
  int v12; // edx
  int *andNode; // ebx
  int conjunctNode; // eax
  int j; // edx
  int updatedFlags; // ebp
  int testNode; // eax
  int v18; // edx
  int *wrapperNode; // eax
  int v20; // edx

  v2 = (int *)(uintptr_t)AST_AllocNode();
  rootNode = v2;
  *v2 = 81;
  if ( patternList )
  {
    v2[16] = patternList;
  }
  else
  {
    testNode = Rules_CEAllocTestNode();
    *(_DWORD *)(uintptr_t)(v18 + 64) = testNode;
  }
  andOrNormalized = Rules_NormalizeNestedConnectives(rootNode, v3, 1);
  fullyNormalized = Rules_NormalizeNestedConnectives(andOrNormalized, v6, 2);
  node = fullyNormalized;
  if ( *fullyNormalized == 82 )
  {
    for ( i = (_DWORD *)(uintptr_t)fullyNormalized[16]; i; i = (_DWORD *)(uintptr_t)i[17] )
    {
      if ( *i != 81 )
      {
        newAndNode = (_DWORD *)(uintptr_t)AST_AllocNode();
        *newAndNode = 81;
        newAndNode[16] = v12;
        newAndNode[17] = *(_DWORD *)(uintptr_t)(v12 + 68);
        *(_DWORD *)(uintptr_t)(v12 + 68) = 0;
        if ( v11 )
          *(_DWORD *)(uintptr_t)(v11 + 68) = newAndNode;
        else
          node[16] = (int)(intptr_t)newAndNode;
        i = newAndNode;
      }
    }
  }
  else if ( *fullyNormalized != 81 )
  {
    wrapperNode = (int *)(uintptr_t)AST_AllocNode();
    *wrapperNode = 81;
    node = wrapperNode;
    wrapperNode[16] = v20;
  }
  Rules_FinalizeConjunctionChain(node);
  if ( *node == 82 )
    andNode = (int *)(uintptr_t)node[16];
  else
    andNode = node;
  while ( andNode )
  {
    conjunctNode = andNode[16];
    for ( j = 1; conjunctNode; conjunctNode = *(_DWORD *)(uintptr_t)(conjunctNode + 68) )
    {
      if ( (*(_BYTE *)(uintptr_t)(conjunctNode + 8) & 0x20) != 0 )
      {
        *(_WORD *)(uintptr_t)(conjunctNode + 8) &= 0xE03Fu;
        updatedFlags = ((j++ & 0x7F) << 6) | *(_DWORD *)(uintptr_t)(conjunctNode + 8);
        *(_DWORD *)(uintptr_t)(conjunctNode + 8) = updatedFlags;
      }
    }
    Rules_CEAssignJoinDepth((_DWORD *)(uintptr_t)andNode[16], 1);
    andNode = (int *)(uintptr_t)andNode[17];
  }
  return node;
}
// 4B8DBC: variable 'v3' is possibly undefined
// 4B8DC8: variable 'v6' is possibly undefined
// 4B8DF5: variable 'v12' is possibly undefined
// 4B8E09: variable 'v11' is possibly undefined
// 4B8E82: variable 'v18' is possibly undefined
// 4B8EA1: variable 'v20' is possibly undefined
